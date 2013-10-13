#ifndef DV2549_EXPERIMENT_DX_H
#define DV2549_EXPERIMENT_DX_H

#include <Fx.h>
#include <Cb.h>
#include <Win.h>
#include <Case.h>
#include <CogFx.h>
#include <CogCb.h>
#include <BufSrv.h>
#include <BufUav.h>
#include <TimerDx.h> // These includes are ugly. Fix.

enum ExperimentAccelerations {
	ExperimentAccelerations_HARDWARE,
	ExperimentAccelerations_SOFTWARE,
	ExperimentAccelerations_WARP
};

template < class T >
class Dx {
public:
	Dx( Case< T >& p_case ) {
		m_case = &p_case;

		m_cogFx = nullptr;
		m_cogCb = nullptr;

		m_bufC = nullptr;
		m_srvA = nullptr;
		m_srvB = nullptr;
		m_uavC = nullptr;

		m_timer = nullptr;
	}
	~Dx() {
		ASSERT_DELETE( m_cogFx );
		ASSERT_DELETE( m_cogCb );

		ASSERT_DELETE( m_bufC );
		ASSERT_DELETE( m_srvA );
		ASSERT_DELETE( m_srvB );
		ASSERT_DELETE( m_uavC );
	
		ASSERT_DELETE( m_timer );
	}

	HRESULT init( Win* p_win ) {
		HRESULT hr = initD3D( p_win );
		if( SUCCEEDED( hr ) ) {
			hr = initBuf();
		}
		if( SUCCEEDED( hr ) ) {
			m_cogFx = new CogFx();
			hr = m_cogFx->init( m_d3d.device );
		}
		if( SUCCEEDED( hr ) ) {
			m_cogCb = new CogCb();
			hr = m_cogCb->init( m_d3d.device );
		}
		if( SUCCEEDED( hr ) ) {
			m_timer = new TimerDx();
			hr = m_timer->init( m_d3d.device );
		}
		return hr;
	}
	double run() {
		// Set resources:
		m_cogFx->getKernel()->set( m_d3d.devcon );

		ID3D11ShaderResourceView* srvs[ 2 ] = { m_srvA->getSrv(), m_srvB->getSrv() };
		ID3D11UnorderedAccessView* uavs[ 1 ] = { m_uavC->getUav() };
		m_d3d.devcon->CSSetShaderResources( 0, 2, srvs );
		m_d3d.devcon->CSSetUnorderedAccessViews( 0, 1, uavs, NULL );

		CbMatrixProperties cb;
		cb.aRows = m_case->a->getNumRows();
		cb.aCols = m_case->a->getNumCols();
		cb.bRows = m_case->b->getNumRows();
		cb.bCols = m_case->b->getNumCols();
		cb.cRows = m_case->ref->getNumRows();
		cb.cCols = m_case->ref->getNumCols();
		m_cogCb->updateMatrixProps( m_d3d.devcon, cb );
		m_cogCb->setMatrixProps( m_d3d.devcon );

		// Time and dispatch kernel:
		m_timer->start( m_d3d.devcon );
		m_d3d.devcon->Dispatch( m_case->a->getNumRows(), m_case->b->getNumCols(), 1 );
		m_timer->stop( m_d3d.devcon );

		// Retrieve the data:
		m_d3d.devcon->CopyResource( m_bufC->getBuf(), m_uavC->getBuf() );
		D3D11_MAPPED_SUBRESOURCE mapRsrc;
		m_d3d.devcon->Map( m_bufC->getBuf(), 0, D3D11_MAP_READ, 0, &mapRsrc );
		m_case->c = new Matrix< T >( (T*)mapRsrc.pData, m_case->ref->getNumRows(), m_case->ref->getNumRows() );
		m_d3d.devcon->Unmap( m_bufC->getBuf(), 0 );

		return m_timer->time( m_d3d.devcon );
	}
protected:
	HRESULT initD3D(  Win* p_win ) {
		UtilDx::DescDeviceSwapChain desc; ZERO_MEM( desc );
		desc.hWnd		= p_win->getHWnd();
		desc.hWndWidth	= p_win->getWidth();
		desc.hWndHeight = p_win->getHeight();
		desc.driverType = D3D_DRIVER_TYPE_HARDWARE; // This ought to be passed through as an argument.
		HRESULT hr = UtilDx::createDeviceSwapChain( desc );
		m_d3d.device		= desc.device;
		m_d3d.devcon		= desc.devcon;
		m_d3d.swapChain	= desc.swapChain;
		return hr;
	}
	HRESULT initBuf() {
		Matrix< T >* mA = m_case->a;
		Matrix< T >* mB = m_case->b;
		Matrix< T >* mRef = m_case->ref;

		m_srvA = new BufSrv< T >( mA->get(), mA->getNum() );
		HRESULT hr = m_srvA->init( m_d3d.device );
		if( SUCCEEDED( hr ) ) {
			m_srvB = new BufSrv< T >( mB->get(), mB->getNum() );
			hr = m_srvB->init( m_d3d.device );
		}
		if( SUCCEEDED( hr ) ) {
			m_uavC = new BufUav< T >( mRef->getNum() );
			hr = m_uavC->init( m_d3d.device );
		}
		if( SUCCEEDED( hr ) ) {
			D3D11_BUFFER_DESC desc; ZERO_MEM( desc );
			m_uavC->getBuf()->GetDesc( &desc );
			desc.Usage			= D3D11_USAGE_STAGING;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.BindFlags		= 0;
			desc.MiscFlags		= 0;
			m_bufC = new Buf< T >();
			hr = m_bufC->initBuf( m_d3d.device, desc );
		}
		return hr;
	}
private:
	Case< T >* m_case;

	// Core
	D3D m_d3d;
	CogFx* m_cogFx;
	CogCb* m_cogCb;

	// Buffers
	Buf< T >* m_bufC;
	BufSrv< T >* m_srvA;
	BufSrv< T >* m_srvB;
	BufUav< T >* m_uavC;

	// Utility
	TimerDx* m_timer;
};

#endif //DV2549_EXPERIMENT_DX_H

/*
typedef enum D3D_DRIVER_TYPE { 
D3D_DRIVER_TYPE_UNKNOWN    = 0,
D3D_DRIVER_TYPE_HARDWARE   = ( D3D_DRIVER_TYPE_UNKNOWN + 1 ),
D3D_DRIVER_TYPE_REFERENCE  = ( D3D_DRIVER_TYPE_HARDWARE + 1 ),
D3D_DRIVER_TYPE_NULL       = ( D3D_DRIVER_TYPE_REFERENCE + 1 ),
D3D_DRIVER_TYPE_SOFTWARE   = ( D3D_DRIVER_TYPE_NULL + 1 ),
D3D_DRIVER_TYPE_WARP       = ( D3D_DRIVER_TYPE_SOFTWARE + 1 )
} D3D_DRIVER_TYPE;
*/

// Just checking to see whether or not the timer works correctly.
/*char text[256];
sprintf_s(
text,
sizeof( text ),
"KernelTest frame-time: %f",
m_timer->time( m_devcon ) );
SetWindowText( m_win->getHWnd(), text );
}*/

// http://msdn.microsoft.com/en-us/library/windows/desktop/ff476328%28v=vs.85%29.aspx