#include <stdafx.h>

#include <CogFx.h>
#include <FxCs.h>

CogFx::CogFx( ExperimentConf p_conf ) {
	m_conf = p_conf;
	
	m_kernel = nullptr;
}
CogFx::~CogFx() {
	ASSERT_DELETE( m_kernel );
}

HRESULT CogFx::init( ID3D11Device* p_device ) {
	HRESULT hr = S_OK;
	switch( m_conf.confFx ) {
	case ExperimentFxs_MULT_BASIC:
		hr = initBasic( p_device );
		break;
	default:
		throw ExceptionExperiment( "Encountered unknown enum in CogFx::init!" );
		break;
	}
	return hr;
}

Fx* CogFx::getKernel() const {
	return m_kernel;
}

HRESULT CogFx::initBasic( ID3D11Device* p_device ) {
	switch( m_conf.confPrecision ) {
	case ExperimentPrecisions_INT:
		m_kernel = new FxCs( g_fxMultIntBasic );
		break;
	case ExperimentPrecisions_FLOAT:
		m_kernel = new FxCs( g_fxMultFloatBasic );
		break;
	default:
		throw ExceptionExperiment( "Encountered unknown enum in CogFx::initBasic!" );
		break;
	}
	return m_kernel->init( p_device );
}