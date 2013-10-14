#ifndef DV2549_EXPERIMENT_PRINTER_H
#define DV2549_EXPERIMENT_PRINTER_H

#include <Case.h>

template < class T >
class Printer {
public:
	Printer( ExperimentPrecisions p_precision, Case< T >& p_case ) {
		m_precision = p_precision;
		m_case = &p_case;
	}
	~Printer() {
		// Do nothing.
	}

	bool print() {
		bool sucess = true;
#ifdef EXPERIMENT_DEBUG
		sucess = printC();
#endif // EXPERIMENT_DEBUG
		if( sucess==true ) {
			sucess = printRes();
		}
		return sucess;
	}
protected:
	bool printC() {
		std::string filename = g_mxgC;

		Matrix< T >* matrix = m_case->c;

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
			mxg.close();
		} else {
			throw ExceptionExperiment( "Could not open " + g_mxgPath + filename + " for writing." );
			sucess = false;
		}

		return sucess;
	}
	bool printRes() {
		std::string filename = "res.res";
		
		bool success = true;
		std::ofstream res;
		res.open( g_resPath + filename );
		if( res.is_open()==true ) {
			unsigned rows = m_case->c->getNumRows();
			unsigned cols = m_case->c->getNumCols();

			double ms = m_case->ms;
			unsigned precision = (int)m_precision;
			bool equalToRef = m_case->equalToRef;
			
			res << (int)equalToRef << "\n" << ms << "\n" << precision << "\n" << rows << "\n" << cols;
			res.close();
		} else {
			throw ExceptionExperiment( "Could not open " + g_resPath + filename + " for writing." );
			success = false;
		}
		return success;
	}
private:
	ExperimentPrecisions m_precision;
	Case< T >* m_case;
};

#endif // DV2549_EXPERIMENT_PRINTER_H