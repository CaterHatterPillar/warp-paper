#ifndef DV2549_MATRIXGEN_MATRIXGEN_H
#define DV2549_MATRIXGEN_MATRIXGEN_H

enum MatrixgenPrecisions;

#include <Matrix.h>
#include <Printer.h>
#include <Ampersand.h>

template < class T >
class Matrixgen {
public:
	Matrixgen( MatrixgenPrecisions p_precision, unsigned p_dim, unsigned p_min, unsigned p_max ) {
		m_precision = p_precision;
		m_dim = p_dim;
		m_min = p_min;
		m_max = p_max;

		m_a = new Matrix< T >( m_dim, m_dim );
		m_b = new Matrix< T >( m_dim, m_dim );
		m_c = new Matrix< T >( m_dim, m_dim );
	}
	~Matrixgen() {
		assert( m_a ); delete m_a;
		assert( m_b ); delete m_b;
		assert( m_c ); delete m_c;
	}

	bool run() {
		bool success = true;

		Ampersand< T >* m_amp = new Ampersand< T >();
		m_amp->matrixPopulate( m_a, m_min, m_max );
		m_amp->matrixPopulate( m_b, m_min, m_max );
		m_amp->matrixMultiply( m_c, m_a, m_b );

		Printer< T >* m_printer = new Printer< T >( MatrixgenPrecisions_INTEGER, m_a, m_b, m_c );
		success = m_printer->print();

		delete m_amp;
		delete m_printer;
		return success;
	}
protected:
private:
	MatrixgenPrecisions m_precision;
	unsigned m_dim;
	unsigned m_max;
	unsigned m_min;

	Matrix< T >* m_a;
	Matrix< T >* m_b;
	Matrix< T >* m_c;
};
// http://msdn.microsoft.com/en-us/library/hh873134.aspx

#endif // DV2549_MATRIXGEN_MATRIXGEN_H