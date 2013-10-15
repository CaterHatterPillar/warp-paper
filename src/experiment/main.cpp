#include <stdafx.h>

#include <Experiment.h>

void MemleakDetect() {
#ifdef EXPERIMENT_DEBUG
	CrudeMemoryLeakDetection();
#endif // EXPERIMENT_DEBUG
}

int runExperiment( Winfo* p_winfo, ExperimentConf p_conf ) {
	int retVal = -1;
	HRESULT hr = S_OK;
	switch( p_conf.confPrecision ) {
	case ExperimentPrecisions_INT: {
		Experiment< int > experiment( p_winfo, p_conf );
		HRESULT hr = experiment.init();
		if( SUCCEEDED( hr ) ) {
			retVal = experiment.run( 0, nullptr );
		}
		break;
		}
	case ExperimentPrecisions_FLOAT: {
		Experiment< float > experiment( p_winfo, p_conf );
		HRESULT hr = experiment.init();
		if( SUCCEEDED( hr ) ) {
			retVal = experiment.run( 0, nullptr );
		}
		break;
		}
	}
	if( FAILED( hr ) ) {
		retVal = (int)hr;
	}
	return retVal;
}

ExperimentFxs lpwstrToFx( LPWSTR p_lpwstr ) {
	ExperimentFxs fx;
	if( wcscmp( p_lpwstr, L"BASIC" )==0 ) {
		fx = ExperimentFxs_MULT_BASIC;
	} else {
		MessageboxError( "The specified kernel is not supported." );
	}
	return fx;
}
ExperimentAccelerations lpwstrToAcceleration( LPWSTR p_lpwstr ) {
	ExperimentAccelerations acceleration;
	if( wcscmp( p_lpwstr, L"HARD" )==0 ) {
		acceleration = ExperimentAccelerations_HARD;
	} else if( wcscmp( p_lpwstr, L"SOFT" )==0 ) {
		acceleration = ExperimentAccelerations_SOFT;
	} else if( wcscmp( p_lpwstr, L"WARP" )==0 ) {
		acceleration = ExperimentAccelerations_WARP;
	} else {
		MessageboxError( "The specified driver acceleration is not supported." );
	}
	return acceleration;
}
ExperimentPrecisions lpwstrToPrecision( LPWSTR p_lpwstr ) {
	ExperimentPrecisions precision;
	if( wcscmp( p_lpwstr, L"INT" )==0 ) {
		precision = ExperimentPrecisions_INT;
	} else if( wcscmp( p_lpwstr, L"FLOAT" )==0 ) {
		precision = ExperimentPrecisions_FLOAT;
	} else {
		MessageboxError( "The specified datatype is not supported." );
	}
	return precision;
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	MemleakDetect();
	int retVal = 1;
	Winfo* winfo = new Winfo( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	int numArgs;
	LPWSTR* args = CommandLineToArgvW( lpCmdLine, &numArgs );
	if( numArgs==3 ) { // Program name not included.
		LPWSTR argFx	= args[ 0 ];
		LPWSTR argMode	= args[ 1 ];
		LPWSTR argPrec	= args[ 2 ];
		ExperimentFxs			confFx				= lpwstrToFx( argFx );
		ExperimentAccelerations confAcceleration	= lpwstrToAcceleration( argMode );
		ExperimentPrecisions	confPrecision		= lpwstrToPrecision( argPrec );
		ExperimentConf conf( confFx, confAcceleration, confPrecision );
		retVal = runExperiment( winfo, conf );
	} else {
		std::cerr << "Usage: " << "experiment" << " ACCELERATION [ HARD SOFT WARP ] PRECISION [ INT FLOAT ]" << std::endl;
	}
	// Don't forget to clean up:
	delete winfo;

	return retVal;
}