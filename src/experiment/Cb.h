#ifndef DV2549_EXPERIMENT_CB_H
#define DV2549_EXPERIMENT_CB_H

template < class T >
class Cb {
public:
	Cb() {
		m_buf = nullptr;
	}
	~Cb() {
		ASSERT_RELEASE( m_buf );
	}

	HRESULT init( ID3D11Device* p_device ) {
		HRESULT hr = S_FALSE;
		unsigned cbSize = sizeof( T );
		if( ( cbSize % 16 )!=0 ) {
			throw ExceptionExperiment( "Constant buffer not multiple of 16!" );
		} else {
			D3D11_BUFFER_DESC desc; ZERO_MEM( desc );
			desc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
			desc.ByteWidth		= cbSize;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.Usage			= D3D11_USAGE_DYNAMIC;
			hr = p_device->CreateBuffer( &desc, NULL, &m_buf );
		}
		return hr;
	}

	ID3D11Buffer* get() const {
		return m_buf;
	}
protected:
private:
	ID3D11Buffer* m_buf;
};

#endif // DV2549_EXPERIMENT_CB_H