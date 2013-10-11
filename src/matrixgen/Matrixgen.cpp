#include <stdafx.h>

#include <Matrix.h>
#include <Matrixgen.h>
#include <Ampersand.h>

Matrixgen::Matrixgen( unsigned p_dim, unsigned p_min, unsigned p_max ) {
	m_dim = p_dim;
	m_min = p_min;
	m_max = p_max;

	m_a = new Matrix< int >(10,10);//( p_dim, p_dim );
	m_b = new Matrix< int >(10,10);//( p_dim, p_dim );
	m_c = new Matrix< int >(10,10);//( p_dim, p_dim );

	m_amp = new Ampersand< int >(  );
}
Matrixgen::~Matrixgen() {
	assert( m_a );
	assert( m_b );
	assert( m_c );

	assert( m_amp );

	delete m_a;
	delete m_b;
	delete m_c;

	delete m_amp;
}

bool Matrixgen::run() {
	bool success = true;

	m_amp->matrixPopulate( m_a, m_min, m_max );
	m_amp->matrixPopulate( m_b, m_min, m_max );
	
	getchar();

	return success;
}

void Matrixgen::matrixPopulate() {
}
void Matrixgen::matrixCalculate() {

}
void Matrixgen::matrixSaveToDisk() {

}