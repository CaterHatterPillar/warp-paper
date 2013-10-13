#ifndef DV2549_EXPERIMENT_READER_H
#define DV2549_EXPERIMENT_READER_H

#include <Case.h>
#include <Matrix.h>

template < class T >
class Reader {
public:
	Reader() {
	}
	~Reader() {
		// Do nothing.
	}

	static bool loadCase( Case< T >& io_case ) {
		bool validCase = false;

		Matrix< T >* mA = loadMxg( g_mxgPath + g_mxgA );
		Matrix< T >* mB = loadMxg( g_mxgPath + g_mxgB );
		Matrix< T >* mRef = loadMxg( g_mxgPath + g_mxgRef );
		if( mA!=nullptr && mB!=nullptr && mRef!=nullptr ) {
			io_case.m_a = mA;
			io_case.m_b = mB;
			io_case.m_ref = mRef;
			validCase = true;
		}
		return validCase;
	}
protected:
private:
	static Matrix< T >* loadMxg( std::string p_pathMxg ) {
		Matrix< T >* matrix = nullptr;

		int precision;
		unsigned rows, cols;

		std::ifstream mxg( p_pathMxg );
		if( mxg.is_open() ) {
			mxg >> precision >> rows >> cols;
			
			unsigned i = 0;
			T* m = MatrixAlloc< T >( rows, cols );
			while( mxg.eof()==false ) {
				mxg >> m[ i ];
				i++;
			}

			matrix = new Matrix< T >( m, rows, cols );
			MatrixFree( m ); // Matrix copies the passed data, so be sure to free memory.
		}

		return matrix;
	}
};

#endif // DV2549_EXPERIMENT_READER_H