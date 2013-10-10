#ifndef DV2549_EXPERIMENT_EXCEPTIONEXPERIMENT_H
#define DV2549_EXPERIMENT_EXCEPTIONEXPERIMENT_H

class ExceptionExperiment : public std::exception {
public:
	ExceptionExperiment( std::string p_func ) throw();
	virtual ~ExceptionExperiment() throw();

	virtual const char* what() const throw();
private:
	std::string m_func;
};

#endif // DV2549_EXPERIMENT_EXCEPTIONEXPERIMENT_H