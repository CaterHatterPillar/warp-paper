#ifndef DV2549_EXPERIMENT_COGFX_H
#define DV2549_EXPERIMENT_COGFX_H

struct ID3D11Device;

class Fx;

class CogFx {
public:
	CogFx();
	~CogFx();

	HRESULT init( ID3D11Device* p_device );

	Fx* getKernel() const;
protected:
private:
	Fx* m_kernel;
};

#endif // DV2549_EXPERIMENT_FX_H