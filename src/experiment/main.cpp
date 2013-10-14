#include <stdafx.h>

#include <Experiment.h>

void MemleakDetect() {
#ifdef EXPERIMENT_DEBUG
	CrudeMemoryLeakDetection();
#endif // EXPERIMENT_DEBUG
}

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	MemleakDetect();
	int retVal = 1;
	Winfo* winfo = new Winfo( hInstance, hPrevInstance, lpCmdLine, nCmdShow );

	int numArgs;
	LPWSTR* args = CommandLineToArgvW( lpCmdLine, &numArgs );
	if( numArgs==2 ) { // Program name not included.
		LPWSTR argMode = args[ 0 ];
		LPWSTR argPrec = args[ 1 ];

		ExperimentAccelerations acceleration = ExperimentAccelerations_WARP;
		if( wcscmp( argMode, L"HARD" )==0 ) {
			acceleration = ExperimentAccelerations_HARD;
		} else if( wcscmp( argMode, L"SOFT" )==0 ) {
			acceleration = ExperimentAccelerations_SOFT;
		}

		if( wcscmp( argPrec, L"INT" )==0 ) {
			Experiment< int > experiment( winfo, acceleration );
			HRESULT hr = experiment.init();
			if( SUCCEEDED( hr ) ) {
				retVal = experiment.run( 0, nullptr );
			} else {
				retVal = (int)hr;
			}
		} else if( wcscmp( argPrec, L"FLOAT" )==0 ) {
			MessageboxError( "Float-precision has not yet been implemented." );
		} else {
			MessageboxError( "The specified datatype is not supported." );
		}
	} else {
		std::cerr << "Usage: " << "experiment" << " ACCELERATION [ HARD SOFT WARP ] PRECISION [ INT FLOAT ]" << std::endl;
	}
	// Don't forget to clean up:
	delete winfo;

	return retVal;
}