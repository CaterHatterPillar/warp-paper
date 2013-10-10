#include <stdafx.h>

HRESULT UtilDx::createDeviceSwapChain( DescDeviceSwapChain& p_desc ) {
	HRESULT hr = S_OK;

	UINT deviceSwapChainFlags = 0;
#ifdef EXPERIMENT_DEBUG
	deviceSwapChainFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // EXPERIMENT_DEBUG

	DXGI_SWAP_CHAIN_DESC scd;
	ZERO_MEM( scd );
	scd.BufferCount			= 1;
	scd.OutputWindow		= p_desc.hWnd;
	scd.Windowed			= TRUE;
	scd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
	scd.SampleDesc.Count	= 1;
	scd.SampleDesc.Quality	= 0;
	scd.BufferDesc.Width	= p_desc.hWndWidth;
	scd.BufferDesc.Height	= p_desc.hWndHeight;
	scd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator	= 60;
	scd.BufferDesc.RefreshRate.Denominator	= 1;

	D3D_FEATURE_LEVEL validFeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};

	D3D_FEATURE_LEVEL sucessfulFeatureLevel;
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		p_desc.driverType,
		NULL,
		deviceSwapChainFlags,
		validFeatureLevels,
		ARRAYSIZE( validFeatureLevels ),
		D3D11_SDK_VERSION,
		&scd,
		&p_desc.swapChain,
		&p_desc.device,
		&sucessfulFeatureLevel,
		&p_desc.devcon );

	return hr;
}