#include <stdafx.h>

#include <ExceptionAnalytics.h>

ExceptionAnalytics::ExceptionAnalytics( std::string p_func ) throw() : exception() {
	m_func = p_func;
}
ExceptionAnalytics::~ExceptionAnalytics() throw() {
	// Do nothing.
}

const char* ExceptionAnalytics::what() const throw() {
	std::string what = "Experiment - Exception: " + m_func;
	return what.c_str();
}