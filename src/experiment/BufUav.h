#ifndef DV2549_EXPERIMENT_BUFUAV_H
#define DV2549_EXPERIMENT_BUFUAV_H

template < class T >
class BufUav : public Buf< T > {
public:
	BufUav( unsigned p_tNum ) : Buf( p_tNum ) {
		m_uav = nullptr;
	}
	virtual ~BufUav() {
		ASSERT_RELEASE( m_uav );
	}

	HRESULT init( ID3D11Device* p_device, DXGI_FORMAT p_format ) { // hack!
		HRESULT hr = initBuf( p_device );
		if( SUCCEEDED( hr ) ) {
			hr = initUav( p_device, p_format );
		}
		return hr;
	}

	ID3D11UnorderedAccessView* getUav() const {
		return m_uav;
	}
protected:
private:
	HRESULT initBuf( ID3D11Device* p_device ) {
		D3D11_BUFFER_DESC desc; ZERO_MEM( desc );
		desc.ByteWidth	= getByteWidth();
		desc.BindFlags	= D3D11_BIND_UNORDERED_ACCESS;
		desc.Usage		= D3D11_USAGE_DEFAULT;

		return Buf::initBuf( p_device, desc );
	}
	HRESULT initUav( ID3D11Device* p_device, DXGI_FORMAT p_format ) {
		D3D11_UNORDERED_ACCESS_VIEW_DESC desc; ZERO_MEM( desc );
		desc.Format					= p_format;
		desc.ViewDimension			= D3D11_UAV_DIMENSION_BUFFER;
		desc.Buffer.FirstElement	= 0;
		desc.Buffer.NumElements		= m_tNum;
		return p_device->CreateUnorderedAccessView( m_buf, &desc, &m_uav );
	}

	ID3D11UnorderedAccessView* m_uav;
};

#endif // DV2549_EXPERIMENT_BUFUAV_H

// Something like this?
/*
DXGI_FORMAT uavFormat = DXGI_FORMAT_UNKNOWN;
switch( std::type_info( T ) ) {
case std::type_info( int ):
uavFormat = DXGI_FORMAT_R32_SINT;
break;
case std::type_info( float ):
uavFormat = DXGI_FORMAT_R32_FLOAT;
break;
}
*/