#ifndef DV2549_ANALYTICS_EXCEPTIONANALYTICS_H
#define DV2549_ANALYTICS_EXCEPTIONANALYTICS_H

class ExceptionAnalytics : public std::exception {
public:
	ExceptionAnalytics( std::string p_func ) throw();
	virtual ~ExceptionAnalytics() throw();

	virtual const char* what() const throw();
private:
	std::string m_func;
};

#endif // DV2549_EXPERIMENT_EXCEPTIONEXPERIMENT_H