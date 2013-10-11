#ifndef DV2549_MATRIXGEN_MATRIX_H
#define DV2549_MATRIXGEN_MATRIX_H

template < class T >
class Matrix {
public:
	Matrix( unsigned p_rows, unsigned p_cols ) {
		m_rows = p_rows;
		m_cols = p_cols;

		m_ = MatrixAlloc< T >( p_rows, p_cols );
	}
	~Matrix() {
		assert( m_ );
		for( unsigned i = 0; i < m_cols; i++ ) {
			delete[] m_[ i ];
		}
		delete[] m_;
	}

	T** get() const {
		return m_;
	}
	unsigned getNumRows() const {
		return m_rows;
	}
	unsigned getNumCols() const {
		return m_cols;
	}
protected:
private:
	T** m_;
	unsigned m_rows;
	unsigned m_cols;
};

#endif // DV2549_MATRIXGEN_MATRIX_H