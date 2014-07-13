#include <stdafx.h>

#include <Printer.h>
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

	// Write analytic
	Printer printer( analytic );
	printer.init( g_pathRes );

	free( c.list );
	free( ref.list );

	return 0;
}

void Analytics::loadMatrix( std::string p_filepath, DoubleList& io_list ) {
	unsigned precision, rows, cols;
	std::ifstream mxgb( p_filepath, std::ios_base::binary );
	if( mxgb.is_open()==true ) {
		mxgb.read( (char*)&precision, sizeof(unsigned) );
		mxgb.read( (char*)&rows, sizeof(unsigned) );
		mxgb.read( (char*)&cols, sizeof(unsigned) );

		io_list.num = rows * cols;
		io_list.list = (double*)malloc( sizeof( double ) * io_list.num );

		float f;
		for(unsigned i = 0; i<io_list.num; i++) {
			mxgb.read((char*)&f, sizeof(float));
			io_list.list[i] = (double)f;
		}
	} else {
		throw ExceptionAnalytics( "Could not open file " + p_filepath + "!" );
	}
}