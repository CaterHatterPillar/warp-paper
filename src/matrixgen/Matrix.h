#ifndef DV2549_MATRIXGEN_MATRIX_H
#define DV2549_MATRIXGEN_MATRIX_H

template < class T >
class Matrix {
public:
	Matrix( unsigned p_rows, unsigned p_cols ) {
		m_rows = p_rows;
		m_cols = p_cols;

		m_ = MatrixAlloc< T >( p_rows, p_cols );
		std::memset( m_, 0, sizeof( T ) * m_rows * m_cols );
	}
	~Matrix() {
		assert( m_ );
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

	std::string toString() {
		std::string string = "\n";
		for( int row = 0; row < m_rows; row++ ) {
			for( int col = 0; col < m_cols; col++ ) {
				string += Util::toString( m_[ row * m_rows + col ] ) + "  ";
			}
			string += "\n";
		}
		return string;
	}
protected:
private:
	T* m_;
	unsigned m_rows;
	unsigned m_cols;
};

#endif // DV2549_MATRIXGEN_MATRIX_H