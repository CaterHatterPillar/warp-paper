#include <stdafx.h>

#include "Win.h"
#include "Main.h"

// Entry point to the application:
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	int retVal = 0;

	Win* win = new Win( hInstance, hPrevInstance, lpCmdLine, nCmdShow );
	HRESULT hr = win->init();
	if( hr==S_OK ) {
		Main main( win );
		retVal = main.main( 0, nullptr );
	} else {
		retVal = (int)hr;
	}

	return retVal;
}

// So much more efficient these days...
/*int main( int argc, char *argv[] ) {
	return 0;
}*/