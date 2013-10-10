#include <stdafx.h>

#include <Fx.h>
#include <Dx.h>
#include <Win.h>
#include <TimerDx.h>

Dx::Dx() {
	m_fx = nullptr;
	m_timer = nullptr;

	m_device = nullptr;
	m_devcon = nullptr;
	m_swapChain = nullptr;
	m_backbufferTex = nullptr;
	m_backbufferUav = nullptr;
}
Dx::~Dx() {
	ASSERT_DELETE( m_fx );
	ASSERT_DELETE( m_timer );

	ASSERT_RELEASE( m_device );
	ASSERT_RELEASE( m_devcon );
	ASSERT_RELEASE( m_swapChain );
	ASSERT_RELEASE( m_backbufferTex );
	ASSERT_RELEASE( m_backbufferUav );
}

HRESULT Dx::init( Win* p_win ) {
	HRESULT hr = S_OK;

	m_win = p_win;
	
	hr = initD3D( p_win );
	if( hr==S_OK ) {
		hr = initBackbuffer();
	}
	if( hr==S_OK ) {
		m_fx = new Fx();
		hr = m_fx->init( m_device );
	}
	if( hr==S_OK ) {
		m_timer = new TimerDx();
		hr = m_timer->init( m_device );
	}

	return hr;
}

void Dx::render() {
	ID3D11UnorderedAccessView* uavs[] = { m_backbufferUav };
	m_devcon->CSSetUnorderedAccessViews( 0, 1, uavs, NULL );

	m_fx->tempSet( m_devcon );
	m_timer->start( m_devcon );
	m_devcon->Dispatch( 25, 25, 1 );
	m_timer->stop( m_devcon );
	m_fx->tempUnset( m_devcon );

	m_swapChain->Present( 0, 0 );

	// Just checking to see whether or not the timer works correctly.
	char text[256];
	sprintf_s(
		text,
		sizeof( text ),
		"KernelTest frame-time: %f",
		m_timer->time( m_devcon ) );
	SetWindowText( m_win->getHWnd(), text );
}

HRESULT Dx::initD3D( Win* p_win ){
	HRESULT hr = S_OK;
	
	HWND winHWnd = p_win->getHWnd();
	unsigned winWidth = p_win->getWidth();
	unsigned winHeight = p_win->getHeight();

	UtilDx::DescDeviceSwapChain desc;
	ZERO_MEM( desc );
	desc.hWnd		= winHWnd;
	desc.hWndWidth	= winWidth;
	desc.hWndHeight = winHeight;
	desc.driverType = getDriverType( ExperimentAccelerations_HARDWARE );
	hr = UtilDx::createDeviceSwapChain( desc );
	m_device	= desc.device;
	m_devcon	= desc.devcon;
	m_swapChain = desc.swapChain;
	
	return hr;
}
HRESULT Dx::initBackbuffer() {
	HRESULT hr = S_OK;

	hr = m_swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&m_backbufferTex );
	if( hr==S_OK ) {
		hr = m_device->CreateUnorderedAccessView( m_backbufferTex, NULL, &m_backbufferUav );
	}

	return hr;
}

D3D_DRIVER_TYPE Dx::getDriverType( ExperimentAccelerations p_acceleration ) {
	D3D_DRIVER_TYPE dt = D3D_DRIVER_TYPE_UNKNOWN;
	switch( p_acceleration ) {
	case ExperimentAccelerations_HARDWARE:
		dt = D3D_DRIVER_TYPE_HARDWARE;
		break;
	case ExperimentAccelerations_SOFTWARE:
		dt = D3D_DRIVER_TYPE_SOFTWARE;
		break;
	case ExperimentAccelerations_WARP:
		dt = D3D_DRIVER_TYPE_WARP;
		break;
	default:
		throw ExceptionExperiment( "Encountered unknown ExperimentAccelerations-type: " + Util::toString( p_acceleration ) + "." );
		break;
	};
	return dt;
};
// http://msdn.microsoft.com/en-us/library/windows/desktop/ff476328%28v=vs.85%29.aspx