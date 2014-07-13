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
		Matrix< T >* mRef = loadMxgb( g_mxgPath + g_mxgRef );
		if( mA!=nullptr && mB!=nullptr && mRef!=nullptr ) {
			io_case.a = mA;
			io_case.b = mB;
			io_case.ref = mRef;
			validCase = true;
		}
		return validCase;
	}
protected:
private:
	static Matrix< T >* loadMxg( std::string p_pathMxg ) {
		Matrix< T >* matrix = nullptr;

		std::string temp;
		int precision;
		unsigned rows, cols;

		std::ifstream mxg( p_pathMxg );
		if( mxg.is_open() ) {
			mxg >> temp >> precision >> temp >> rows >> temp >> cols;
			
			unsigned i = 0;
			T* m = MatrixAlloc< T >( rows, cols );
			while( mxg.eof()==false ) {
				mxg >> m[ i ];
				i++;
			}

			matrix = new Matrix< T >( m, rows, cols );
			MatrixFree( m ); // Matrix copies the passed data, so be sure to free memory.
		} else {
			MessageboxError( p_pathMxg + " not found!" );
		}

		return matrix;
	}
	static Matrix< T >* loadMxgb( std::string p_pathMxgb ) {
		Matrix< T >* matrix = nullptr;

		std::ifstream mxgb( p_pathMxgb, std::ios_base::binary );
		if( mxgb.is_open() ) {
			unsigned preRowCol[3];
			for( unsigned i = 0; i<3; i++ ) {
				mxgb.read( (char*)&preRowCol[i], sizeof(unsigned) );
			}

			unsigned i = 0;
			T* m = MatrixAlloc< T >( preRowCol[1], preRowCol[2] );
			unsigned numElements = preRowCol[1] * preRowCol[2];
			for( unsigned i = 0; i<numElements; i++ ) {
				mxgb.read((char*)&m[i], sizeof(matrix[i]));
			}

			matrix = new Matrix< T >( m, preRowCol[1], preRowCol[2] );
			MatrixFree( m ); // Matrix copies the passed data, so be sure to free memory.
		} else {
			MessageboxError( p_pathMxgb + " not found!" );
		}

		return matrix;
	}
};

#endif // DV2549_EXPERIMENT_READER_H