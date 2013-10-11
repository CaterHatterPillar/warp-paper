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

	Matrix< int >* mA = new Matrix< int >( 3 , 3 );
	Matrix< int >* mB = new Matrix< int >( 3 , 3 );
	Matrix< int >* mC = new Matrix< int >( 3 , 3 );
	Ampersand< int >* m_amp = new Ampersand< int >();

	m_amp->matrixPopulate( mA, m_min, m_max );
	m_amp->matrixPopulate( mB, m_min, m_max );
	m_amp->matrixMultiply( mC, mA, mB );

	std::cout << mA->toString() << std::endl << std::endl;
	std::cout << mB->toString() << std::endl << std::endl;
	std::cout << mC->toString() << std::endl << std::endl;

	getchar();

	delete mA;
	delete mB;
	delete mC;
	delete m_amp;
	
	return success;
}