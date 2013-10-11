#ifndef DV2549_MATRIXGEN_AMPERSAND_H
#define DV2549_MATRIXGEN_AMPERSAND_H

template < class T >
class Matrix;

#include <amp_tinymt_rng.h>

template < class T >
class Ampersand {
public:
	Ampersand() {
		concurrency::accelerator default_device;
		std::wcout << std::endl << L"Initializing C++ AMP with device: " << default_device.get_description() + L".";
		if( default_device==concurrency::accelerator( concurrency::accelerator::direct3d_ref) ) {
			std::cout << std::endl << "Warning. Running C++ AMP using a slow emulator.";
		}

		srand( time( 0 ) );
	}
	~Ampersand() {
		// Do nothing.
	}

	template < class T >
	void matrixPopulate( Matrix< T >* p_matrix, int p_min, int p_max ) {
		unsigned rows = p_matrix->getNumRows();
		unsigned cols = p_matrix->getNumCols();
		T** matrix = p_matrix->get();

		// Initialize RNG:
		long seed = rand();
		const int rank = 2; // ?
		concurrency::extent< rank > e_size( rows, cols );
		tinymt_collection< rank > rng( e_size, seed );
		char ref[50];
		sprintf_s( ref, "%d", &matrix );
		std::cout << std::endl << "C++ AMP RNG initialized with seed: " + Util::toString( seed ) + "." << std::endl << "Proceeding to generate random numbers for matrix: " + std::string( ref ) + ".";
	
		concurrency::array_view< T, 2 > a( rows, cols, *matrix );
		parallel_for_each(
			a.extent,
			[=]( concurrency::index< 2 > idx ) restrict( amp ) {
				int row = idx[ 0 ];
				int col = idx[ 1 ];

				auto t = rng[ idx ];
				float random = t.next_single(); // Gives a floating point in-between 0-1.
				a[ idx ] = int( concurrency::precise_math::nearbyint( random * p_max + p_min ) );
			}
		);
		a.synchronize();
	
		std::cout << std::endl;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				std::cout << a(row, col) << "  ";
			}
			std::cout << "\n";
		}
	}
	// http://amprng.codeplex.com/SourceControl/latest#test/main.cpp
protected:
private:
};

#endif // DV2549_MATRIXGEN_AMPERSAND_H