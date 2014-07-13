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
		bool success = true;
		if( success==true && m_a!=nullptr ) {
			success = printToFile( "a.mxg", m_a );
		}
		if( success==true && m_b!=nullptr ) {
			success = printToFile( "b.mxg", m_b );
		}
		if( success==true ) {
			printToFileBinary( "ref.mxgb", m_c );
		}
		return success;
	}
protected:
	bool printToFile( std::string p_filename, Matrix< T >* p_matrix ) {
		std::cout << "\n" << "Printing matrix to file: " << p_filename << ".";

		bool success = true;
		std::ofstream mxg;
		mxg.open( g_mxgPath + p_filename );
		if( mxg.is_open()==true ) {
			unsigned precision = (int)m_precision;
			unsigned rows = p_matrix->getNumRows();
			unsigned cols = p_matrix->getNumCols();
			mxg << "Precision:\t"	<< precision	<< "\n"
				<< "Rows:\t"		<< rows			<< "\n" 
				<< "Columns:\t"		<< cols;

			unsigned numElements = rows * cols;
			T* matrix = p_matrix->get();
			for( unsigned i = 0; i<numElements; i++ ) {
				mxg << "\n" << matrix[ i ];
			}
		} else {
			success = false;
		}
		mxg.close();

		return success;
	}
	bool printToFileBinary( std::string p_filename, Matrix< T >* p_matrix ) {
		std::cout << "\n" << "Printing matrix to file: " << p_filename << ".";

		std::ofstream mxgb( g_mxgPath + p_filename, std::ios_base::binary );
		bool success = mxgb.is_open();
		if( success==true ) {
			unsigned precision = (int)m_precision;
			unsigned rows = p_matrix->getNumRows();
			unsigned cols = p_matrix->getNumCols();

			mxgb.write( (const char*)&precision, sizeof(unsigned) ); // Ignore utility text since no human will be reading this, and the format won't be portable.
			mxgb.write( (const char*)&rows, sizeof(unsigned) );
			mxgb.write( (const char*)&cols, sizeof(unsigned) );

			unsigned numElements = rows * cols;
			T* matrix = p_matrix->get();
			for( unsigned i = 0; i<numElements; i++ ) {
				mxgb.write( (const char*)&matrix[i], sizeof(matrix[i]) );
			}
		}
		mxgb.close();

		return success;
	}
private:
	MatrixgenPrecisions m_precision;
	Matrix< T >* m_a;
	Matrix< T >* m_b;
	Matrix< T >* m_c;
};

#endif // DV2549_MATRIXGEN_PRINTER_H