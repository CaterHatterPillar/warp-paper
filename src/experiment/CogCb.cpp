#include <stdafx.h>

#include <Cb.h>
#include <CogCb.h>
#include <CbDesc.h>

CogCb::CogCb() {
	m_cbMatrixProps = nullptr;
}
CogCb::~CogCb() {
	ASSERT_DELETE( m_cbMatrixProps );
}

HRESULT CogCb::init( ID3D11Device* p_device ) {
	m_cbMatrixProps = new Cb< CbMatrixProperties >();
	return m_cbMatrixProps->init( p_device );
}

HRESULT CogCb::updateMatrixProps( ID3D11DeviceContext* p_devcon, CbMatrixProperties p_new ) {
	ID3D11Buffer* cb = m_cbMatrixProps->get();
	
	D3D11_MAPPED_SUBRESOURCE mapSubRsrc;
	HRESULT hr = p_devcon->Map( cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSubRsrc );
	if( SUCCEEDED( hr ) ) {
		CbMatrixProperties* old = (CbMatrixProperties*)mapSubRsrc.pData;
		old->aRows = p_new.aRows;
		old->aCols = p_new.aCols;
		old->bRows = p_new.bRows;
		old->bCols = p_new.bCols;
		old->cRows = p_new.cRows;
		old->cCols = p_new.cCols;

		p_devcon->Unmap( cb, 0 );
	} else {
		MessageboxError( "Failed to map constant buffer!" );
	}
	return hr;
}
void CogCb::setMatrixProps( ID3D11DeviceContext* p_devcon ) {
	ID3D11Buffer* cb = m_cbMatrixProps->get();
	p_devcon->CSSetConstantBuffers( 0, 1, &cb );
}