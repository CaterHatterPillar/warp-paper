#ifndef DV2549_EXPERIMENT_CASE_H
#define DV2549_EXPERIMENT_CASE_H

#include <Matrix.h>

template < class T >
struct Case {
	Case() {
		m_a = m_b = m_c = nullptr;
	}
	~Case() {
		ASSERT_DELETE( m_a );
		ASSERT_DELETE( m_b );
		ASSERT_DELETE( m_c );
	}

	Matrix< T >* m_a;
	Matrix< T >* m_b;
	Matrix< T >* m_c;

	// Execution time and other data.
};

#endif // DV2549_EXPERIMENT_CASE_H