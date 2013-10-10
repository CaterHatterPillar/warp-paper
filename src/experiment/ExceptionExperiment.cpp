#include <stdafx.h>

ExceptionExperiment::ExceptionExperiment( std::string p_func ) throw() : exception() {
	m_func = p_func;
}
ExceptionExperiment::~ExceptionExperiment() throw() {
	// Do nothing.
}

const char* ExceptionExperiment::what() const throw() {
	std::string what = "Experiment - Exception: " + m_func;
	return what.c_str();
}