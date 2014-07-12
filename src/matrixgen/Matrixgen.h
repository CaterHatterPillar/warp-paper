#ifndef DV2549_MATRIXGEN_MATRIXGEN_H
#define DV2549_MATRIXGEN_MATRIXGEN_H

enum MatrixgenPrecisions;

#include <Matrix.h>
#include <Reader.h>
#include <Printer.h>
#include <Ampersand.h>

template < class T >
class Matrixgen {
public:
	Matrixgen( MatrixgenPrecisions p_precision, unsigned p_dim, unsigned p_min, unsigned p_max, bool p_pop ) {
		m_precision = p_precision;
		m_dim = p_dim;
		m_min = p_min;
		m_max = p_max;
		m_pop = p_pop;
	}
	~Matrixgen() {
		assert( m_a ); delete m_a;
		assert( m_b ); delete m_b;
		assert( m_c ); delete m_c;
	}

	bool run() {
		bool success = true;

		Ampersand< T >* amp = new Ampersand< T >();
		if( m_pop==true ) { // if instructed to populate matrices
			m_a = new Matrix< T >( m_dim, m_dim );
			m_b = new Matrix< T >( m_dim, m_dim );

			amp->matrixPopulate( m_a, m_min, m_max );
			amp->matrixPopulate( m_b, m_min, m_max );
		} else { // load from file
			m_a = Reader< T >::loadMatrix( g_mxgPath + "a.mxg" );
			m_b = Reader< T >::loadMatrix( g_mxgPath + "b.mxg" );
			assert( m_a!=nullptr );
			assert( m_a!=nullptr );
		}

		m_c = new Matrix< T >( m_dim, m_dim );
		amp->matrixMultiply( m_c, m_a, m_b );

		Printer< T >* printer = nullptr;
		if( m_pop==true ) {
			printer = new Printer< T >( m_precision, m_a, m_b, m_c );
		} else {
			printer = new Printer< T >( m_precision, nullptr, nullptr, m_c );
		}
		success = printer->print();

		delete amp;
		delete printer;
		return success;
	}
protected:
private:
	MatrixgenPrecisions m_precision;
	unsigned m_dim;
	unsigned m_max;
	unsigned m_min;
	bool m_pop;

	Matrix< T >* m_a;
	Matrix< T >* m_b;
	Matrix< T >* m_c;
};
// http://msdn.microsoft.com/en-us/library/hh873134.aspx

#endif // DV2549_MATRIXGEN_MATRIXGEN_H