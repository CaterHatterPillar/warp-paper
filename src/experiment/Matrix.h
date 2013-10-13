#ifndef DV2549_EXPERIMENT_MATRIX_H
#define DV2549_EXPERIMENT_MATRIX_H

template < class T >
class Matrix {
public:
	Matrix( T* p_, unsigned p_rows, unsigned p_cols ) {
		m_ = MatrixAlloc< T >( p_rows, p_cols );
		unsigned size = sizeof( T ) * p_rows * p_cols;
		memcpy( m_, p_, size );

		m_rows = p_rows;
		m_cols = p_cols;
	}
	~Matrix() {
		MatrixFree( m_ );
	}

	T* get() const {
		return m_;
	}
	unsigned getNumRows() const {
		return m_rows;
	}
	unsigned getNumCols() const {
		return m_cols;
	}
	unsigned getNum() const {
		return m_rows * m_cols;
	}
protected:
private:
	T* m_;
	unsigned m_rows;
	unsigned m_cols;
};

#endif // DV2549_EXPERIMENT_MATRIX_H