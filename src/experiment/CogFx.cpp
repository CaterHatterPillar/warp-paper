#include <stdafx.h>

#include <CogFx.h>
#include <FxCs.h>

CogFx::CogFx( ExperimentConf p_conf ) {
	m_conf = p_conf;
	
	m_mult = nullptr;
}
CogFx::~CogFx() {
	ASSERT_DELETE( m_mult );
}

HRESULT CogFx::init( ID3D11Device* p_device ) {
	return initMult( p_device );;
}

Fx* CogFx::getKernel() const {
	return m_mult;
}

HRESULT CogFx::initMult( ID3D11Device* p_device ) {
	// This method can easily be made not-so-extremely-ugly by creating a simple desc-object.
	LPCWSTR kernel = L"UnknownFx";
	switch( m_conf.confFx ) {
	case ExperimentFxs_MULT_BASIC:
		switch( m_conf.confPrecision ) {
		case ExperimentPrecisions_INT:
			kernel = g_fxMultIntBasic;
			break;
		case ExperimentPrecisions_FLOAT:
			kernel = g_fxMultFloatBasic;
			break;
		}
		break;
	case ExperimentFxs_MULT_TILE:
		switch( m_conf.confPrecision ) {
		case ExperimentPrecisions_INT:
			kernel = g_fxMultIntTile;
			break;
		case ExperimentPrecisions_FLOAT:
			kernel = g_fxMultFloatTile;
			break;
		}
		break;
	default:
		throw 0;
		break;
	}
	m_mult = new FxCs( kernel );
	return m_mult->init( p_device );
}