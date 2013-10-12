#ifndef DV2549_EXPERIMENT_MATRIX_H
#define DV2549_EXPERIMENT_MATRIX_H

template < class T >
class Matrix {
public:
	Matrix( T* p_, unsigned p_rows, unsigned p_cols ) {
		m_ = p_;
		m_rows = p_rows;
		m_cols = p_cols;
	}
	~Matrix() {
		MatrixFree( m_ );
	}

	T* get() const {
		return m_;
	}
protected:
private:
	T* m_;
	unsigned m_rows;
	unsigned m_cols;
};

#endif // DV2549_EXPERIMENT_MATRIX_H