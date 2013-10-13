#ifndef DV2549_MATRIXGEN_AMPERSAND_H
#define DV2549_MATRIXGEN_AMPERSAND_H

template < class T >
class Matrix;

#include <Amphack.h>

/*
The constructor of Ampersand, as well as matrixPopulate - or any use of C++ AMP it seems - seems to cause memory leaks.
I'm not sure what causes it, whether or not it is expected behaviour or if I've done something wrong.
*/

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

	// This is ugly! Quick hack performed to get rid of obscure linker errors. Fix this! 
	template < class T >
	void matrixPopulate( Matrix< T >* p_matrix, int p_min, int p_max ) {
		throw ExceptionMatrixgen( "Non-supported datatype!" );
	}
	template <>
	void matrixPopulate( Matrix< int >* p_matrix, int p_min, int p_max ) {
		Amphack::Amp_MatrixPopulate( p_matrix, p_min, p_max );
	}
	template <>
	void matrixPopulate( Matrix< float >* p_matrix, int p_min, int p_max ) {
		Amphack::Amp_MatrixPopulate( p_matrix, p_min, p_max );
	}

	template < class T >
	void matrixMultiply( Matrix< T >* p_c, Matrix< T >* p_a, Matrix< T >* p_b ) {
		throw ExceptionMatrixgen( "Non-supported datatype!" );
	}
	template <>
	void matrixMultiply( Matrix< int >* p_c, Matrix< int >* p_a, Matrix< int >* p_b ) {
		Amphack::Amp_MatrixMultiply( p_c, p_a, p_b );
	}
	template <>
	void matrixMultiply( Matrix< float >* p_c, Matrix< float >* p_a, Matrix< float >* p_b ) {
		Amphack::Amp_MatrixMultiply( p_c, p_a, p_b );
	}
protected:
private:
};

#endif // DV2549_MATRIXGEN_AMPERSAND_H