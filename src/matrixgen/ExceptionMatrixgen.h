#ifndef DV2549_MATRIXGEN_EXCEPTIONMATRIXGEN_H
#define DV2549_MATRIXGEN_EXCEPTIONMATRIXGEN_H

class ExceptionMatrixgen : public std::exception {
public:
	ExceptionMatrixgen( std::string p_func ) throw();
	virtual ~ExceptionMatrixgen() throw();

	virtual const char* what() const throw();
private:
	std::string m_func;
};

#endif // DV2549_MATRIXGEN_EXCEPTIONMATRIXGEN_H