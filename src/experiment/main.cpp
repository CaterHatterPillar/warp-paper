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
	if( numArgs==1 ) { // Program name not included.
		LPWSTR precision = args[ 0 ];

		if( wcscmp( precision, L"INT" )==0 ) {
			Experiment< int > experiment( winfo );
			HRESULT hr = experiment.init();
			if( SUCCEEDED( hr ) ) {
				retVal = experiment.run( 0, nullptr );
			} else {
				retVal = (int)hr;
			}
		} else if( precision==L"FLOAT" ) {
			MessageboxError( "Float-precision has not yet been implemented." );
		} else {
			MessageboxError( "The specified datatype is not supported." );
		}
	}
	// Don't forget to clean up:
	delete winfo;

	return retVal;
}