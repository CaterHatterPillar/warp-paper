#ifndef DV2549_MATRIXGEN_AMPHACK_H
#define DV2549_MATRIXGEN_AMPHACK_H

template < class T >
class Matrix;

static const unsigned TileSize = 1;

/* 
Using Amphack to seperate all C++ AMP RNG-code from the include-hell caused by severe templating.
Encountered hopeless link-errors when including C++ AMP RNG.
Get rid of this hack!
*/

class Amphack {
public:
	// Tile theses implementations in order to be able to generate larger matrices:
	static void Amp_MatrixPopulate( Matrix< int >* p_matrix, int p_min, int p_max );
	static void Amp_MatrixPopulate( Matrix< float >* p_matrix, int p_min, int p_max );

	static void Amp_MatrixMultiply( Matrix< int >* p_c, Matrix< int >* p_a, Matrix< int >* p_b );
	static void Amp_MatrixMultiply( Matrix< float >* p_c, Matrix< float >* p_a, Matrix< float >* p_b );
protected:
private:
};

#endif // DV2549_MATRIXGEN_AMPHACK_H