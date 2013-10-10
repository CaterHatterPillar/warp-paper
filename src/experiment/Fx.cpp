#include <stdafx.h>

#include <Fx.h>
#include <KernelCS.h>

Fx::Fx() {
	m_kernel = nullptr;
}
Fx::~Fx() {
	assert( m_kernel );
	delete m_kernel;
}

HRESULT Fx::init( ID3D11Device* p_device ) {
	HRESULT hr = S_OK;

	m_kernel = new KernelCS( PathKernelTest );
	hr = m_kernel->init( p_device );

	return hr;
}

void Fx::tempSet( ID3D11DeviceContext* p_devcon ) {
	m_kernel->set( p_devcon );
}
void Fx::tempUnset( ID3D11DeviceContext* p_devcon ) {
	m_kernel->unset( p_devcon );
}