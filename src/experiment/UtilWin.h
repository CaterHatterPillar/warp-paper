#ifndef DV2549_EXPERIMENT_UTILWIN_H
#define DV2549_EXPERIMENT_UTILWIN_H

#include <strsafe.h>

struct Winfo {
public:
	Winfo( HINSTANCE p_hInstance, HINSTANCE p_hInstancePrev, LPWSTR p_lpCmdLine, int p_nCmdShow );
	~Winfo();

	HINSTANCE hInstance;
	HINSTANCE hInstancePrev;
	LPWSTR lpCmdLine;
	int nCmdShow;
protected:
private:
};

void MessageboxError( std::string p_what );

void GetLastErrorAndTerminateProcess( LPTSTR p_function );

#endif // DV2549_EXPERIMENT_UTILWIN_H