#ifndef DV2549_EXPERIMENT_COGCB_H
#define DV2549_EXPERIMENT_COGCB_H

template < class T >
class Cb;

#include <CbDesc.h>

class CogCb {
public:
	CogCb();
	~CogCb();

	HRESULT init( ID3D11Device* p_device );

	HRESULT updateMatrixProps( ID3D11DeviceContext* p_devcon, CbMatrixProperties p_new );
	void setMatrixProps( ID3D11DeviceContext* p_devcon );
protected:
private:
	Cb< CbMatrixProperties >* m_cbMatrixProps;
};

#endif // DV2549_EXPERIMENT_COGCB_H