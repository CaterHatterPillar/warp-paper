#ifndef DV2549_MATRIXGEN_UTIL_H
#define DV2549_MATRIXGEN_UTIL_H

#ifdef MATRIXGEN_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void CrudeMemoryLeakDetection();
#endif // MATRIXGEN_DEBUG

template < class T >
T** MatrixAlloc( unsigned p_rows, unsigned p_cols ) {
	T** matrix;
	matrix = (T**)calloc( p_cols, sizeof( T* ) );
	for( unsigned i = 0; i < p_cols; i++ ) {
		matrix[ i ] = (T*)calloc( p_rows, sizeof( T ) );
	}
	return matrix;
}

class Util {
public:
	Util();
	~Util();

	static std::string toString( int p_int );
	static std::string toString( unsigned p_uint );

	static const char* toStringC( int p_int );
	static const char* toStringC( unsigned p_uint );

	static int toInt( std::string p_string );
};

#endif // DV2549_MATRIXGEN_UTIL_H