#include <stdafx.h>

#include "UtilWin.h"

// Function declarations:
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow );
LRESULT CALLBACK wWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
HRESULT wWinWindow( HINSTANCE hInstance, int nCmdShow );

// Magic numbers and bad jokes:
static const unsigned g_windowWidth		= 800;
static const unsigned g_windowHeight	= 800;

static const LPCTSTR g_windowTitle		= "Experiment";
static const LPCTSTR g_windowClassName	= "ExperimentWindow";

// Global variables:
HWND		g_hWnd		= nullptr;
HINSTANCE	g_hInstance	= nullptr;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	HRESULT hr = wWinWindow( hInstance, nCmdShow );
	if( hr!=S_OK ) {
		return hr;
	}
	
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

HRESULT wWinWindow( HINSTANCE hInstance, int nCmdShow ) {
	HRESULT hr = E_FAIL;

	WNDCLASSEX wcex;
	ZeroMemory( &wcex, sizeof( wcex ) ); // Use ZeroMemory to save some lines of code, and make up for it with a redundant comment.
	wcex.cbSize			= sizeof( WNDCLASSEX ); 
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = wWinProc;
	wcex.hInstance      = hInstance;
	wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground  = (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = g_windowClassName;

	LPTSTR lastMethod = "RegisterClassEx";
	if( RegisterClassEx( &wcex )!=0 ) { // Registers a window class for subsequent use in calls to the CreateWindow or CreateWindowEx function.
		g_hInstance = hInstance;

		RECT rc = { 0, 0, g_windowWidth, g_windowHeight };
		AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

		lastMethod = "CreateWindow";
		g_hWnd = CreateWindow(
			g_windowClassName,
			g_windowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rc.right	- rc.left,
			rc.bottom	- rc.top,
			NULL,
			NULL,
			hInstance,
			NULL);
		if( g_hWnd!=NULL ) { // Return value of CreateWindow is NULL if failed.
			ShowWindow( g_hWnd, nCmdShow );
			hr = S_OK;
		}
	}
	if( hr!=S_OK ) {
		GetLastErrorAndTerminateProcess( lastMethod );
	}
	return hr;
}

LRESULT CALLBACK wWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
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

// So much more efficient these days...
/*int main( int argc, char *argv[] ) {
	return 0;
}*/