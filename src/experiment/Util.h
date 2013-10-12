#ifndef DV2549_EXPERIMENT_UTIL_H
#define DV2549_EXPERIMENT_UTIL_H

#ifdef EXPERIMENT_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
void CrudeMemoryLeakDetection();
#endif // EXPERIMENT_DEBUG

template < class T >
T* MatrixAlloc( unsigned p_rows, unsigned p_cols ) {
	return (T*)calloc( p_rows * p_cols, sizeof( T ) );
}
template < class T >
void MatrixFree( T* p_matrix ) {
	free( p_matrix );
}

class Util {
public:
	static std::string toString( int p_int );
	static std::string toString( unsigned p_uint );

	static const char* toStringC( int p_int );
	static const char* toStringC( unsigned p_uint );

	static int toInt( std::string p_string );
};

#endif // DV2549_EXPERIMENT_UTIL_H