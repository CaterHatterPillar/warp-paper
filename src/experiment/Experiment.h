#ifndef DV2549_EXPERIMENT_EXPERIMENT_H
#define DV2549_EXPERIMENT_EXPERIMENT_H

class Dx;
class Win;

class Experiment {
public:
	Experiment( Winfo* p_winfo );
	~Experiment();
	
	HRESULT init();

	// Consider removing the Windows message loop, as time is optimally spent entirely on the experiment
	// and not on listening to keystrokes, etc.
	int run( int argc, char *argv[] );
protected:
private:
	HRESULT initWin();
	HRESULT initDx();

	Win* m_win;
	Dx* m_dx;

	// Junk:
	Winfo* m_winfo;
};

#endif // DV2549_EXPERIMENT_EXPERIMENT_H