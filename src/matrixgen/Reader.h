#ifndef DV2549_MATRIXGEN_READER_H
#define DV2549_MATRIXGEN_READER_H

#include <Matrix.h>

template < class T >
class Reader {
public:
	Reader() {
	}
	~Reader() {
		// Do nothing.
	}

	static Matrix< T >* loadMatrix( std::string p_filename ) {
		std::string temp;
		int precision;
		unsigned rows, cols;
		Matrix< T >* matrix = nullptr;

		std::ifstream mxg( p_filename );
		if( mxg.is_open() ) {
			mxg >> temp >> precision >> temp >> rows >> temp >> cols;

			unsigned i = 0;
			matrix = new Matrix< T >( rows, cols );
			T* m = matrix->get();
			while( mxg.eof()==false ) {
				mxg >> m[ i ];
				i++;
			}
		}

		return matrix;
	}
protected:
private:
};

#endif // DV2549_MATRIXGEN_READER_H