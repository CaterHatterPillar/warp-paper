#ifndef DV2549_EXPERIMENT_DX_H
#define DV2549_EXPERIMENT_DX_H

struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11UnorderedAccessView;

class Fx;
class Win;
class TimerDx;

enum ExperimentAccelerations {
	ExperimentAccelerations_HARDWARE,
	ExperimentAccelerations_SOFTWARE,
	ExperimentAccelerations_WARP
};

class Dx {
public:
	Dx();
	~Dx();

	HRESULT init( Win* p_win );
	void render();
protected:
private:
	HRESULT initD3D( Win* p_win );
	HRESULT initBackbuffer();

	D3D_DRIVER_TYPE getDriverType( ExperimentAccelerations p_acceleration );

	Fx* m_fx;
	Win* m_win; // temp, remove me
	TimerDx* m_timer;

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_devcon;
	IDXGISwapChain* m_swapChain;
	ID3D11Texture2D* m_backbufferTex;
	ID3D11UnorderedAccessView* m_backbufferUav;
};

#endif //DV2549_EXPERIMENT_DX_H