#include <stdafx.h>

ExceptionMatrixgen::ExceptionMatrixgen( std::string p_func ) throw() : exception() {
	m_func = p_func;
}
ExceptionMatrixgen::~ExceptionMatrixgen() throw() {
	// Do nothing.
}

const char* ExceptionMatrixgen::what() const throw() {
	std::string what = "Experiment - Exception: " + m_func;
	return what.c_str();
}