#include <stdafx.h>
#include <time.h>

#include <Matrix.h>
#include <Matrixgen.h>
#include <Ampersand.h>

Matrixgen::Matrixgen( unsigned p_dim ) {
	m_dim = p_dim;

	m_a = new Matrix< float >(10,10);//( p_dim, p_dim );
	m_b = new Matrix< float >(10,10);//( p_dim, p_dim );
	m_c = new Matrix< float >(10,10);//( p_dim, p_dim );

	m_amp = new Ampersand< float >( time( NULL ) );
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

	m_amp->matrixPopulate( m_a, 0, 10 );
	getchar(); //temp

	return success;
}

void Matrixgen::matrixPopulate() {
}
void Matrixgen::matrixCalculate() {

}
void Matrixgen::matrixSaveToDisk() {

}