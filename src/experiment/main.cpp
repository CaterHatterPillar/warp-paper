#include <stdafx.h>

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	MSG msgWin = { 0 };
	while( WM_QUIT!=msgWin.message ) {
		if( PeekMessage( &msgWin, NULL, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msgWin );
			DispatchMessage( &msgWin );
		} else {
			// Do things.
		}
	}
	return (int)msgWin.wParam;
}

/*int main( int argc, char *argv[] ) {
	return 0;
}*/