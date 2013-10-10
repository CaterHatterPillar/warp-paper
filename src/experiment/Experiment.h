#ifndef DV2549_EXPERIMENT_EXPERIMENT_H
#define DV2549_EXPERIMENT_EXPERIMENT_H

class Dx;
class Win;

class Experiment {
public:
	Experiment( HINSTANCE p_hInstance, HINSTANCE p_hInstancePrev, LPWSTR p_lpCmdLine, int p_nCmdShow );
	~Experiment();
	
	HRESULT init();

	// Consider remoing the Windows message loop, as time is optimally spent entirely on the experiment
	// and not on listening to keystrokes, etc.
	int run( int argc, char *argv[] );
protected:
private:
	HRESULT initWin();
	HRESULT initDx();

	Win* m_win;
	Dx* m_dx;

	// Junk
	HINSTANCE m_hInstance;
	HINSTANCE m_hInstancePrev;
	LPWSTR m_lpCmdLine;
	int m_nCmdShow;
};

#endif // DV2549_EXPERIMENT_EXPERIMENT_H