#include <stdafx.h>

#include <KernelCS.h>

KernelCS::KernelCS( LPCWSTR p_kernelPath ) : Kernel( p_kernelPath ) {
	m_cs = nullptr;
}
KernelCS::~KernelCS() {
	assert( m_cs );
	m_cs->Release();
}

HRESULT KernelCS::init( ID3D11Device* p_device ) {
	HRESULT hr = Kernel::init( p_device );
	if( hr==S_OK ) {
		hr = p_device->CreateComputeShader( 
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			nullptr,
			&m_cs );
	}
	return hr;
}

void KernelCS::set( ID3D11DeviceContext* p_devcon ) {
	p_devcon->CSSetShader( m_cs, nullptr, 0 );
}
void KernelCS::unset( ID3D11DeviceContext* p_devcon ) {
	p_devcon->CSSetShader( nullptr, nullptr, 0 );
}