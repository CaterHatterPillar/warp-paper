#include <stdafx.h>

#include <Win.h>
#include <UtilWin.h>

Win::Win( HINSTANCE	p_hInstance,
		 HINSTANCE	p_hInstancePrev,
		 LPWSTR		p_lpCmdLine,
		 int		p_nCmdShow ) {
	m_hInstance		= p_hInstance;
	m_hInstancePrev = p_hInstancePrev;
	m_lpCmdLine		= p_lpCmdLine;
	m_nCmdShow		= p_nCmdShow;

	m_hWnd = nullptr;
}
Win::~Win() {
	// Do nothing.
}

HRESULT Win::init() {
	HRESULT hr = initWindow();
	return hr;
}

unsigned Win::getWidth() {
	RECT rct; GetClientRect( m_hWnd, &rct );
	unsigned width = rct.right - rct.left;
	return width;
}
unsigned Win::getHeight() {
	RECT rct; GetClientRect( m_hWnd, &rct );
	unsigned height = rct.bottom - rct.top;
	return height;
}
HWND Win::getHWnd() const {
	return m_hWnd;
}

HRESULT Win::initWindow() {
	HRESULT hr = E_FAIL;

	WNDCLASSEX wcex;
	ZeroMemory( &wcex, sizeof( wcex ) ); // Use ZeroMemory to save some lines of code, and make up for it with a redundant comment.
	wcex.cbSize			= sizeof( WNDCLASSEX ); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = Win::wWinProc;
	wcex.hInstance      = m_hInstance;
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground  = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = g_windowClassName;

	LPTSTR lastMethod = "RegisterClassEx";
	if( RegisterClassEx( &wcex )!=0 ) { // Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function.
		RECT rct = { 0, 0, g_windowWidth, g_windowHeight };
		AdjustWindowRect( &rct, WS_OVERLAPPEDWINDOW, FALSE );

		lastMethod = "CreateWindow";
		m_hWnd = CreateWindow(
			g_windowClassName,
			g_windowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rct.right	- rct.left,
			rct.bottom	- rct.top,
			NULL,
			NULL,
			m_hInstance,
			NULL);
		if( m_hWnd!=NULL ) { // Return value of CreateWindow is NULL if failed.
			ShowWindow( m_hWnd, m_nCmdShow );
			hr = S_OK;
		}
	}
	if( hr!=S_OK ) {
		GetLastErrorAndTerminateProcess( lastMethod );
	}
	return hr;
}

LRESULT CALLBACK Win::wWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	HDC hdc;
	PAINTSTRUCT ps;
	LRESULT lResult = 0;
	switch ( message ) {
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_KEYDOWN:
		if( wParam==VK_ESCAPE ) {
			PostQuitMessage( 0 );
		}
		break;
	default:
		lResult = DefWindowProc( hWnd, message, wParam, lParam );
		break;
	}
	return lResult;
}