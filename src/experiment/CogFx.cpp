#include <stdafx.h>

#include <CogFx.h>
#include <FxCs.h>

CogFx::CogFx() {
	m_kernel = nullptr;
}
CogFx::~CogFx() {
	ASSERT_DELETE( m_kernel );
}

HRESULT CogFx::init( ID3D11Device* p_device ) {
	HRESULT hr = S_OK;

	m_kernel = new FxCs( PathKernelMult );
	hr = m_kernel->init( p_device );

	return hr;
}

Fx* CogFx::getKernel() const {
	return m_kernel;
}