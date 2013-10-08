#include <stdafx.h>

#include "Win.h"
#include "Main.h"

Main::Main( Win* p_win ) {
	m_win = p_win;
}
Main::~Main() {
	// Do nothing.
}

int Main::main( int argc, char *argv[] ) {
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