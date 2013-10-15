#include <stdafx.h>

#include <Printer.h>

Printer::Printer( Analytic p_analytic ) {
	m_analytic = p_analytic;
}
Printer::~Printer() {
	// Do nothing.
}

void Printer::init( std::string filepath ) {
	std::ofstream res;
	res.open( filepath );
	if( res.is_open()==true ) {
		res << "DeviationMax:\t"	<< m_analytic.deviationMax	<< "\n" 
			<< "DeviationMin:\t"	<< m_analytic.deviationMin	<< "\n" 
			<< "DeviationStd:\t"	<< m_analytic.deviationStandard;
		res.close();
	} else {
		throw ExceptionAnalytics( "Could not open " + filepath + " for writing." );
	}
}