#ifndef DV2549_EXPERIMENT_UTILDX_H
#define DV2549_EXPERIMENT_UTILDX_H

class UtilDx {
public:
	UtilDx();
	~UtilDx();

	struct DescDeviceSwapChain {
		HWND hWnd;
		unsigned hWndWidth;
		unsigned hWndHeight;

		D3D_DRIVER_TYPE driverType;

		ID3D11Device* device;
		ID3D11DeviceContext* devcon;
		IDXGISwapChain* swapChain;
	};
	static HRESULT createDeviceSwapChain( DescDeviceSwapChain& p_desc );
protected:
private:
};

#endif // DV2549_EXPERIMENT_UTILDX_H