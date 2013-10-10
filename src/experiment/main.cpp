#include <stdafx.h>

#include <Experiment.h>

// Entry point to the application:
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	Experiment experiment( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
	HRESULT hr = experiment.init();
	
	int retVal = 0;
	if( hr==S_OK ) {
		retVal = experiment.run( 0, nullptr );
	} else {
		retVal = (int)hr;
	}
	return retVal;
}