#include <stdafx.h>

#include <Dx.h>
#include <Win.h>
#include <Case.h>
#include <Reader.h>
#include <Printer.h>
#include <Inspector.h>
#include <Experiment.h>

Experiment::Experiment( Winfo* p_winfo ) {
	m_winfo = p_winfo;
	
	m_dx = nullptr;
	m_win = nullptr;
}
Experiment::~Experiment() {
	ASSERT_DELETE( m_win );
	ASSERT_DELETE( m_dx );
}

HRESULT Experiment::init() {
	HRESULT hr = S_OK;

	hr = BOOL_TO_HRESULT( Reader< int >::loadCase( m_case ) );
	if( SUCCEEDED( hr ) ) {
		hr = initWin();
	}
	if( SUCCEEDED( hr ) ) {
		hr = initDx();
	}
	return hr;
}

int Experiment::run( int argc, char *argv[] ) {
	// Perform matrix multiplication of specified case using DirectCompute:
	m_dx->run();

	// Compare result to reference matrix compiled by C++ AMP:
	Inspection inspection; ZERO_MEM( inspection );
	Inspector< int > inspector( m_case );
	bool isEqual = inspector.inspect( inspection );

#ifdef EXPERIMENT_DEBUG
	Printer< int > printer( MatrixgenPrecisions_INTEGER, m_case );
	bool sucessfulPrint = printer.print();
#endif // EXPERIMENT_DEBUG

	// Obs, should rather return whether or not execution was sucessful - and write results to file.

	return !isEqual;
}

HRESULT Experiment::initWin() {
	m_win = new Win( m_winfo->hInstance, m_winfo->hInstancePrev, m_winfo->lpCmdLine, m_winfo->nCmdShow );
	return m_win->init();
}
HRESULT Experiment::initDx() {
	HRESULT hr = S_OK;
	m_dx = new Dx< int >( m_case );
	hr = m_dx->init( m_win );

	return hr;
}