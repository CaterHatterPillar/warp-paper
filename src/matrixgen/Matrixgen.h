#ifndef DV2549_MATRIXGEN_MATRIXGEN_H
#define DV2549_MATRIXGEN_MATRIXGEN_H

template< class T >
class Ampersand;
template< class T >
class Matrix;

class Matrixgen {
public:
	Matrixgen( unsigned p_dim );
	~Matrixgen();

	bool run();
protected:
	void matrixPopulate();
	void matrixCalculate();
	void matrixSaveToDisk();
private:
	unsigned m_dim;

	Matrix< int >* m_a;
	Matrix< int >* m_b;
	Matrix< int >* m_c;

	Ampersand< int >* m_amp;
};
// http://msdn.microsoft.com/en-us/library/hh873134.aspx

#endif // DV2549_MATRIXGEN_MATRIXGEN_H