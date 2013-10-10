#include <stdafx.h>

#include <Dx.h>
#include <Win.h>
#include <Experiment.h>

Experiment::Experiment( HINSTANCE p_hInstance, HINSTANCE p_hInstancePrev, LPWSTR p_lpCmdLine, int p_nCmdShow ) {
	m_hInstance = p_hInstance;
	m_hInstancePrev = p_hInstancePrev;
	m_lpCmdLine = p_lpCmdLine;
	m_nCmdShow = p_nCmdShow;
	
	m_dx = nullptr;
	m_win = nullptr;
}
Experiment::~Experiment() {
	delete m_win;
	delete m_dx;
}

HRESULT Experiment::init() {
	HRESULT hr = S_OK;
	hr = initWin();
	if( hr==S_OK ) {
		hr = initDx();
	}
	return hr;
}

int Experiment::run( int argc, char *argv[] ) {
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

HRESULT Experiment::initWin() {
	m_win = new Win( m_hInstance, m_hInstancePrev, m_lpCmdLine, m_nCmdShow );
	return m_win->init();
}
HRESULT Experiment::initDx() {
	HRESULT hr = S_OK;
	return hr;
}