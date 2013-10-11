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

	Matrix< float >* m_a;
	Matrix< float >* m_b;
	Matrix< float >* m_c;

	Ampersand< float >* m_amp;
};

#endif // DV2549_MATRIXGEN_MATRIXGEN_H