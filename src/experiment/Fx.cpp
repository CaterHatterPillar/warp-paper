#include <stdafx.h>

#include <Fx.h>

Fx::Fx( LPCWSTR p_kernelPath ) {
	m_kernelPath = p_kernelPath;

	m_blob = nullptr;
}
Fx::~Fx() {
	assert( m_blob );
	m_blob->Release();
}

HRESULT Fx::init( ID3D11Device* p_device ) {
	HRESULT hr = S_OK;
	hr = D3DReadFileToBlob( m_kernelPath, &m_blob );
	if( hr!=S_OK ) {
		// Fix this, this is terrible:
		std::wstring location = L"Kernel::init D3DReadFileToBlob ";
		std::wstring failed = L" Failed!";
		std::wstring errorMsg = location + static_cast<std::wstring>( m_kernelPath ) + failed;
		std::string std( errorMsg.begin(), errorMsg.end() );
		MessageboxError( std );
	}

	return hr;
}