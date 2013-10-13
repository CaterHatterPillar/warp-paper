#ifndef DV2549_MATRIXGEN_PRINTER_H
#define DV2549_MATRIXGEN_PRINTER_H

#include <Matrix.h>

template < class T >
class Printer {
public:
	Printer( MatrixgenPrecisions p_precision, Matrix< T >* p_a, Matrix< T >* p_b, Matrix< T >* p_c ) {
		m_precision = p_precision;
		m_a = p_a;
		m_b = p_b;
		m_c = p_c;
	}
	~Printer() {
		// Do nothing.
	}

	bool print() {
		bool sucess = printToFile( "a.mxg", m_a );
		if( sucess==true ) {
			printToFile( "b.mxg", m_b );
		}
		if( sucess==true ) {
			printToFile( "ref.mxg", m_c );
		}
		return sucess;
	}
protected:
	bool printToFile( std::string p_filename, Matrix< T >* p_matrix ) {
		std::cout << "\n" << "Printing matrix to file: " + p_filename + ".";

		bool sucess = true;
		std::ofstream mxg;
		mxg.open( g_mxgPath + p_filename );
		if( mxg.is_open()==true ) {
			unsigned precision = (int)m_precision;
			unsigned rows = p_matrix->getNumRows();
			unsigned cols = p_matrix->getNumCols();
			mxg << precision << "\n" << rows << "\n" << cols;

			unsigned numElements = rows * cols;
			T* matrix = p_matrix->get();
			for( unsigned i = 0; i<numElements; i++ ) {
				mxg << "\n" << matrix[ i ];
			}
		} else {
			sucess = false;
		}
		mxg.close();

		return sucess;
	}
private:
	MatrixgenPrecisions m_precision;
	Matrix< T >* m_a;
	Matrix< T >* m_b;
	Matrix< T >* m_c;
};

#endif // DV2549_MATRIXGEN_PRINTER_H