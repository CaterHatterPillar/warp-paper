#ifndef DV2549_EXPERIMENT_KERNELCS_H
#define DV2549_EXPERIMENT_KERNELCS_H

#include <Kernel.h>

class KernelCS : public Kernel {
public:
	KernelCS( LPCWSTR p_kernelPath );
	virtual ~KernelCS();

	HRESULT init( ID3D11Device* p_device );

	void set( ID3D11DeviceContext* p_devcon );
	void unset( ID3D11DeviceContext* p_devcon );
protected:
private:
	ID3D11ComputeShader* m_cs;
};

#endif // DV2549_EXPERIMENT_KERNELCS_H