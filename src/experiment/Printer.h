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
		bool success = true;
		success = printC();
		if( success==true ) {
			success = printRes();
		}
		return success;
	}
protected:
	bool printC() {
		std::string filename = g_mxgC;

		Matrix< T >* matrix = m_case->c;

		bool success = true;
		std::ofstream mxgb( g_mxgPath + filename, std::ios_base::binary );
		if( mxgb.is_open()==true ) {
			unsigned precision = (int)m_precision;
			unsigned rows = matrix->getNumRows();
			unsigned cols = matrix->getNumCols();
			
			mxgb.write( (const char*)&precision, sizeof(unsigned) ); // Ignore utility text since no human will be reading this, and the format won't be portable.
			mxgb.write( (const char*)&rows, sizeof(unsigned) );
			mxgb.write( (const char*)&cols, sizeof(unsigned) );

			unsigned numElements = rows * cols;
			T* m = matrix->get();
			for( unsigned i = 0; i<numElements; i++ ) {
				mxgb.write( (const char*)&m[i], sizeof(m[i]) );
			}
			mxgb.close();
		} else {
			throw ExceptionExperiment( "Could not open " + g_mxgPath + filename + " for writing." );
			success = false;
		}

		return success;
	}
	bool printRes() {
		std::string filename = g_resPath + "resExperiment.res";
		
		bool success = true;
		std::ofstream res;
		res.open( filename );
		if( res.is_open()==true ) {
			unsigned rows = m_case->c->getNumRows();
			unsigned cols = m_case->c->getNumCols();

			double ms = m_case->ms;
			unsigned precision = (int)m_precision;
			bool equalToRef = m_case->equalToRef;
			
			res << "Equal:\t"		<< (int)equalToRef	<< "\n" 
				<< "TimeMs:\t"		<< ms				<< "\n" 
				<< "Precision:\t"	<< precision		<< "\n" 
				<< "Rows:\t"		<< rows				<< "\n" 
				<< "Cols:\t"		<< cols;
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