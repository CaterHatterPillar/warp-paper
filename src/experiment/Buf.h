#ifndef DV2549_EXPERIMENT_BUF_H
#define DV2549_EXPERIMENT_BUF_H

template < class T >
class Buf {
public:
	Buf( unsigned p_tNum ) {
		m_tNum = p_tNum;
		m_tSize = sizeof( T );
		m_buf = nullptr;
	}
	Buf() {
		m_tNum = 0;
		m_tSize = sizeof( T );
		m_buf = nullptr;
	}
	virtual ~Buf() {
		ASSERT_RELEASE( m_buf );
	}

	virtual HRESULT init( ID3D11Device* p_device ) {
		return S_OK;
	}
	HRESULT initBuf( ID3D11Device* p_device, D3D11_BUFFER_DESC& p_desc ) {
		return p_device->CreateBuffer( &p_desc, NULL, &m_buf );
	}
	HRESULT initBuf( ID3D11Device* p_device, D3D11_BUFFER_DESC& p_desc, D3D11_SUBRESOURCE_DATA& p_initialData ) {
		return p_device->CreateBuffer( &p_desc, &p_initialData, &m_buf );
	}

	ID3D11Buffer* getBuf() const {
		return m_buf;
	}
protected:
	unsigned getByteWidth() const {
		return m_tSize * m_tNum;
	}

	unsigned m_tNum;
	unsigned m_tSize;
	ID3D11Buffer* m_buf;
private:
};

#endif // DV2549_EXPERIMENT_BUF_H