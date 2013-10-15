#include <stdafx.h>

#include <amp_tinymt_rng.h>

#include <Matrix.h>
#include <Amphack.h>

void Amphack::Amp_MatrixPopulate( Matrix< int >* p_matrix, int p_min, int p_max ) {
	const unsigned rows = p_matrix->getNumRows();
	const unsigned cols = p_matrix->getNumCols();
	int* matrix = p_matrix->get();

	// Initialize RNG:
	long seed = rand();
	concurrency::extent< 2 > e_size( rows, cols );
	tinymt_collection< 2 > rng( e_size, seed );
	char ref[50]; sprintf_s( ref, "%d", matrix );
	std::cout << std::endl << "C++ AMP RNG initialized with seed: " + Util::toString( seed ) + "." << std::endl << "Proceeding to generate random numbers for matrix: " + std::string( ref ) + ".";

	concurrency::array_view< int, 2 > ioMatrix( rows, cols, matrix );
	parallel_for_each(
		ioMatrix.extent,
		[=]( concurrency::index< 2 > idx ) restrict( amp ) {
			int row = idx[ 0 ];
			int col = idx[ 1 ];

			auto t = rng[ idx ];
			float random = t.next_single(); // Gives a floating point in-between 0-1.
			ioMatrix[ row ][ col ] = int( concurrency::precise_math::nearbyint( random * p_max + p_min ) );
	}
	);
	ioMatrix.synchronize();
}
void Amphack::Amp_MatrixPopulate( Matrix< float >* p_matrix, int p_min, int p_max ) {
	const unsigned rows = p_matrix->getNumRows();
	const unsigned cols = p_matrix->getNumCols();
	float* matrix = p_matrix->get();

	// Initialize RNG:
	long seed = rand();
	concurrency::extent< 2 > e_size( rows, cols );
	tinymt_collection< 2 > rng( e_size, seed );
	char ref[50]; sprintf_s( ref, "%d", matrix );
	std::cout << std::endl << "C++ AMP RNG initialized with seed: " + Util::toString( seed ) + "." << std::endl << "Proceeding to generate random numbers for matrix: " + std::string( ref ) + ".";

	concurrency::array_view< float, 2 > ioMatrix( rows, cols, matrix );
	parallel_for_each(
		ioMatrix.extent,
		[=]( concurrency::index< 2 > idx ) restrict( amp ) {
			int row = idx[ 0 ];
			int col = idx[ 1 ];

			auto t = rng[ idx ];
			float random = t.next_single(); // Gives a floating point in-between 0-1.
			ioMatrix[ row ][ col ] = random * p_max + p_min;
	}
	);
	ioMatrix.synchronize();
}

void Amphack::Amp_MatrixMultiply( Matrix< int >* p_c, Matrix< int >* p_a, Matrix< int >* p_b ) {
	std::cout << std::endl << "Compiling reference matrix C=AB.";

	const unsigned rows = p_c->getNumRows();
	const unsigned cols = p_c->getNumCols();
	concurrency::array_view< int, 2 > iA( p_a->getNumRows(), p_a->getNumCols(), p_a->get() ); 
	concurrency::array_view< int, 2 > iB( p_b->getNumRows(), p_b->getNumCols(), p_b->get() );
	concurrency::array_view< int, 2 > ioC( p_c->getNumRows(), p_c->getNumCols(), p_c->get() );
	parallel_for_each(
		ioC.extent.tile< TileSize, TileSize >(),
		[=]( concurrency::tiled_index< TileSize, TileSize > tidx ) restrict( amp ) {
			int row = tidx.local[ 0 ];
			int col = tidx.local[ 1 ];	// Relative to tile.
			int rowG = tidx.global[ 0 ];
			int colG = tidx.global[ 1 ]; // Matrix index.

			int product = 0;
			for( unsigned i = 0; i < rows; i += TileSize ) {
				// Cooperatively load shared block data:
				tile_static int locA[ TileSize ][ TileSize ];
				tile_static int locB[ TileSize ][ TileSize ];
				locA[ row ][ col ] = iA( rowG, col + i );
				locB[ row ][ col ] = iB( row + i, colG );
				tidx.barrier.wait();

				for( int k = 0; k < TileSize; k++ ) {
					product += locA[ row ][ k ] * locB[ k ][ col ];
				}
				tidx.barrier.wait();
			}
			ioC[ tidx.global ] = product;
		}
		);
	ioC.synchronize();
}
void Amphack::Amp_MatrixMultiply( Matrix< float >* p_c, Matrix< float >* p_a, Matrix< float >* p_b ) {
	std::cout << std::endl << "Compiling reference matrix C=AB.";

	const unsigned rows = p_c->getNumRows();
	const unsigned cols = p_c->getNumCols();
	concurrency::array_view< float, 2 > iA( p_a->getNumRows(), p_a->getNumCols(), p_a->get() ); 
	concurrency::array_view< float, 2 > iB( p_b->getNumRows(), p_b->getNumCols(), p_b->get() );
	concurrency::array_view< float, 2 > ioC( p_c->getNumRows(), p_c->getNumCols(), p_c->get() );
	parallel_for_each(
		ioC.extent.tile< TileSize, TileSize >(),
		[=]( concurrency::tiled_index< TileSize, TileSize > tidx ) restrict( amp ) {
			int row = tidx.local[ 0 ];
			int col = tidx.local[ 1 ];	// Relative to tile.
			int rowG = tidx.global[ 0 ];
			int colG = tidx.global[ 1 ]; // Matrix index.

			float product = 0;
			for( unsigned i = 0; i < rows; i += TileSize ) {
				// Cooperatively load shared block data:
				tile_static float locA[ TileSize ][ TileSize ];
				tile_static float locB[ TileSize ][ TileSize ];
				locA[ row ][ col ] = iA( rowG, col + i );
				locB[ row ][ col ] = iB( row + i, colG );
				tidx.barrier.wait();

				for( int k = 0; k < TileSize; k++ ) {
					product += locA[ row ][ k ] * locB[ k ][ col ];
				}
				tidx.barrier.wait();
			}
			ioC[ tidx.global ] = product;
	}
	);
	ioC.synchronize();
}