#ifndef DV2549_EXPERIMENT_COGFX_H
#define DV2549_EXPERIMENT_COGFX_H

struct ID3D11Device;
class Fx;

class CogFx {
public:
	CogFx( ExperimentConf p_conf );
	~CogFx();

	HRESULT init( ID3D11Device* p_device );

	Fx* getKernel() const;
protected:
	HRESULT initBasic( ID3D11Device* p_device );
private:
	ExperimentConf m_conf;

	Fx* m_kernel;
};

#endif // DV2549_EXPERIMENT_FX_H