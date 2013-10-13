#ifndef DV2549_EXPERIMENT_BUFSRV_H
#define DV2549_EXPERIMENT_BUFSRV_H

#include <Buf.h>

template < class T >
class BufSrv : public Buf< T > {
public:
	BufSrv( T* p_data, unsigned p_tNum ) : Buf( p_tNum ) {
		m_data = p_data;
		m_srv = nullptr;
	}
	virtual ~BufSrv() {
		ASSERT_RELEASE( m_srv );
	}

	HRESULT init( ID3D11Device* p_device ) {
		HRESULT hr = initBuf( p_device );
		if( SUCCEEDED( hr ) ) {
			hr = initSrv( p_device );
		}
		return hr;
	}

	ID3D11ShaderResourceView* getSrv() const {
		return m_srv;
	}
protected:
private:
	HRESULT initBuf( ID3D11Device* p_device ) {
		D3D11_BUFFER_DESC desc; ZERO_MEM( desc );
		desc.StructureByteStride = m_tSize;
		desc.ByteWidth			= getByteWidth();
		desc.MiscFlags			= D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
		desc.Usage				= D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA srData; ZERO_MEM( srData );
		srData.pSysMem = m_data;
		return Buf::initBuf( p_device, desc, srData );
	}
	HRESULT initSrv( ID3D11Device* p_device ) {
		D3D11_SHADER_RESOURCE_VIEW_DESC descSrv; ZERO_MEM( descSrv );
		descSrv.Format				= DXGI_FORMAT_UNKNOWN;
		descSrv.ViewDimension		= D3D11_SRV_DIMENSION_BUFFER;
		descSrv.Buffer.FirstElement	= 0; // Considering the struct has been cleared with ZeroMemory, this shouldn't need setting.
		descSrv.Buffer.NumElements	= m_tNum;
		return p_device->CreateShaderResourceView( m_buf, &descSrv, &m_srv );
	}

	T* m_data;
	ID3D11ShaderResourceView* m_srv;
};

#endif // DV2549_EXPERIMENT_BUFSRV_H