#ifndef DV2549_EXPERIMENT_PRINTER_H
#define DV2549_EXPERIMENT_PRINTER_H

template < class T >
class Printer {
public:
	Printer( MatrixgenPrecisions p_precision, Case< T >& p_case ) {
		m_precision = p_precision;
		m_case = &p_case;
	}
	~Printer() {
		// Do nothing.
	}

	bool print() {
		std::string filename = g_mxgC;

		Matrix< T >* matrix = m_case->m_c;

		bool sucess = true;
		std::ofstream mxg;
		mxg.open( g_mxgPath + filename );
		if( mxg.is_open()==true ) {
			unsigned precision = (int)m_precision;
			unsigned rows = matrix->getNumRows();
			unsigned cols = matrix->getNumCols();
			mxg << precision << "\n" << rows << "\n" << cols;

			unsigned numElements = rows * cols;
			T* m = matrix->get();
			for( unsigned i = 0; i<numElements; i++ ) {
				mxg << "\n" << m[ i ];
			}
		} else {
			sucess = false;
		}
		mxg.close();

		return sucess;
	}
protected:
private:
	MatrixgenPrecisions m_precision;
	Case< T >* m_case;
};

#endif // DV2549_EXPERIMENT_PRINTER_H