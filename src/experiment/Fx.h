#ifndef DV2549_EXPERIMENT_FX_H
#define DV2549_EXPERIMENT_FX_H

class Fx {
public:
	Fx( LPCWSTR p_kernelPath );
	virtual ~Fx();

	virtual HRESULT init( ID3D11Device* p_device );

	virtual void set( ID3D11DeviceContext* p_devcon )	= 0;
	virtual void unset( ID3D11DeviceContext* p_devcon ) = 0;
protected:
	ID3D10Blob* m_blob; // Contains compiled kernel.
private:
	LPCWSTR m_kernelPath; // Path to compiled shader.
};

#endif // DV2549_EXPERIMENT_FX_H