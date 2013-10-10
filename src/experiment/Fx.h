#ifndef DV2549_EXPERIMENT_FX_H
#define DV2549_EXPERIMENT_FX_H

class Kernel;

class Fx {
public:
	Fx();
	~Fx();

	HRESULT init( ID3D11Device* p_device );

	void tempSet( ID3D11DeviceContext* p_devcon );
	void tempUnset( ID3D11DeviceContext* p_devcon );

protected:
private:
	Kernel* m_kernel;
};

#endif // DV2549_EXPERIMENT_FX_H