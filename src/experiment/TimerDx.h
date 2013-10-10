#ifndef DV2549_EXPERIMENT_TIMERDX_H
#define DV2549_EXPERIMENT_TIMERDX_H

struct ID3D11Query;
struct ID3D11Device;
struct ID3D11DeviceContext;

class TimerDx {
public:
	TimerDx();
	~TimerDx();

	HRESULT init( ID3D11Device* p_device );

	void start( ID3D11DeviceContext* p_devcon );
	void stop( ID3D11DeviceContext* p_devcon );
	double time( ID3D11DeviceContext* p_devcon );
protected:
private:
	ID3D11Query* m_start;
	ID3D11Query* m_stop;
	ID3D11Query* m_disjoint;
};

#endif // DV2549_EXPERIMENT_TIMERDX_H