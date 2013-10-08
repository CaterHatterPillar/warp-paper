#ifndef DV2549_EXPERIMENT_WIN_H
#define DV2549_EXPERIMENT_WIN_H

// Magic numbers and bad jokes:
static const unsigned g_windowWidth		= 800;
static const unsigned g_windowHeight	= 800;

static const LPCTSTR g_windowTitle		= "Experiment";
static const LPCTSTR g_windowClassName	= "ExperimentWindow";

class Win {
public:
	Win( HINSTANCE	p_hInstance,
		HINSTANCE	p_hInstancePrev,
		LPWSTR		p_lpCmdLine,
		int			p_nCmdShow );
	~Win();

	HRESULT init();

	// This method is totally off limits. Hands off.
	static LRESULT CALLBACK wWinProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
protected:
private:
	HRESULT initWindow();

	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	HINSTANCE	m_hInstancePrev;
	LPWSTR		m_lpCmdLine;
	int			m_nCmdShow;
};

#endif // DV2549_EXPERIMENT_WIN_H