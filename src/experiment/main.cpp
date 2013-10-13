#include <stdafx.h>

#include <Experiment.h>

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
#ifdef EXPERIMENT_DEBUG
	CrudeMemoryLeakDetection();
#endif // EXPERIMENT_DEBUG
	
	Winfo* winfo = new Winfo( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
	Experiment< int > experiment( winfo );
	HRESULT hr = experiment.init();
	
	int retVal = 0;
	if( SUCCEEDED( hr ) ) {
		retVal = experiment.run( 0, nullptr );
	} else {
		retVal = (int)hr;
	}
	
	// Don't forget to clean up:
	delete winfo;

	return retVal;
}

#define SDG