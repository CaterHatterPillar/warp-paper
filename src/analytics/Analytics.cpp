#include <stdafx.h>

#include <Deviant.h>
#include <Analytics.h>

Analytics::Analytics() {

}
Analytics::~Analytics() {
	// Do nothing.
}

int Analytics::run() {
	Analytic analytic;

	DoubleList c, ref;
	loadMatrix( g_pathC, c );
	loadMatrix( g_pathRef, ref );

	Deviant deviant;
	deviant.establishDeviations( analytic, c, ref );

	free( c.list );
	free( ref.list );

	return 0; // temp
}

void Analytics::loadMatrix( std::string p_filepath, DoubleList& io_list ) {
	std::string temp;
	unsigned precision, rows, cols;
	
	std::ifstream mxg( p_filepath );
	if( mxg.is_open() ) {
		mxg >> temp >> precision >> temp >> rows >> temp >> cols; // We're not really interested in this data.

		io_list.num = rows * cols;
		io_list.list = (double*)malloc( sizeof( double ) * io_list.num );

		unsigned i = 0;
		while( mxg.eof()==false ) {
			mxg >> io_list.list[ i ];
			i++;
		}
	} else {
		throw ExceptionAnalytics( "Could not open file " + p_filepath + "!" );
	}
}