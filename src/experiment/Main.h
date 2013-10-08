#ifndef DV2549_EXPERIMENT_MAIN_H
#define DV2549_EXPERIMENT_MAIN_H

class Win;

class Main {
public:
	Main( Win* p_win );
	~Main();

	// Consider remoing the Windows message loop, as time is optimally spent entirely on the experiment
	// and not on listening to keystrokes, etc.
	int main( int argc, char *argv[] );
protected:
private:
	Win* m_win;
};

#endif // DV2549_EXPERIMENT_MAIN_H