#include <stdafx.h>

#include <Matrix.h>
#include <Matrixgen.h>
#include <Ampersand.h>

Matrixgen::Matrixgen( unsigned p_dim, unsigned p_min, unsigned p_max ) {
	m_dim = p_dim;
	m_min = p_min;
	m_max = p_max;
}
Matrixgen::~Matrixgen() {
	// Do nothing.
}

bool Matrixgen::run() {
	bool success = true;

	Matrix< int >* m_a = new Matrix< int >(10,10);
	Matrix< int >* m_b = new Matrix< int >(10,10);
	Matrix< int >* m_c = new Matrix< int >(10,10);
	Ampersand< int >* m_amp = new Ampersand< int >();

	m_amp->matrixPopulate( m_a, m_min, m_max );
	m_amp->matrixPopulate( m_b, m_min, m_max );

	getchar();

	delete m_a;
	delete m_b;
	delete m_c;
	delete m_amp;
	
	return success;
}

void Matrixgen::matrixPopulate() {
}
void Matrixgen::matrixCalculate() {

}
void Matrixgen::matrixSaveToDisk() {

}