#ifndef DV2549_EXPERIMENT_CONF_H
#define DV2549_EXPERIMENT_CONF_H

#define BLOCK_SIZE 16

static const LPCWSTR g_fxMultIntBasic	= L"MultIntBasic.cso";
static const LPCWSTR g_fxMultFloatBasic = L"MultFloatBasic.cso";

static const std::string g_resPath = "../../../res/";
static const std::string g_mxgPath = "../../../mxg/"; // Path to mxg-dir.
static const std::string g_mxgA = "a.mxg";
static const std::string g_mxgB = "b.mxg";
static const std::string g_mxgC = "c.mxg";
static const std::string g_mxgRef = "ref.mxg";

// These three enums are hacks spread throughout the application.
// Try to get tid of them.
enum ExperimentPrecisions {
	ExperimentPrecisions_INT	= 0,
	ExperimentPrecisions_FLOAT	= 1
};

// Please note that SOFT makes use of the REFERENCE-driver, rather than the SOFTWARE-driver.
enum ExperimentAccelerations {
	ExperimentAccelerations_HARD	= 1, // D3D_DRIVER_TYPE_HARDWARE
	ExperimentAccelerations_SOFT	= 2, // D3D_DRIVER_TYPE_REFERENCE
	ExperimentAccelerations_WARP	= 5	 // D3D_DRIVER_TYPE_WARP
};

enum ExperimentFxs {
	ExperimentFxs_MULT_BASIC = 0
};

struct ExperimentConf {
	ExperimentConf() { }
	ExperimentConf( ExperimentFxs p_f, ExperimentAccelerations p_a, ExperimentPrecisions p_p ) {
		confFx				= p_f;
		confAcceleration	= p_a;
		confPrecision		= p_p;
	}
	~ExperimentConf() { }

	ExperimentPrecisions	confPrecision;
	ExperimentAccelerations confAcceleration;
	ExperimentFxs			confFx;
};

/*
typedef enum D3D_DRIVER_TYPE { 
D3D_DRIVER_TYPE_UNKNOWN    = 0,
D3D_DRIVER_TYPE_HARDWARE   = ( D3D_DRIVER_TYPE_UNKNOWN + 1 ),
D3D_DRIVER_TYPE_REFERENCE  = ( D3D_DRIVER_TYPE_HARDWARE + 1 ),
D3D_DRIVER_TYPE_NULL       = ( D3D_DRIVER_TYPE_REFERENCE + 1 ),
D3D_DRIVER_TYPE_SOFTWARE   = ( D3D_DRIVER_TYPE_NULL + 1 ),
D3D_DRIVER_TYPE_WARP       = ( D3D_DRIVER_TYPE_SOFTWARE + 1 )
} D3D_DRIVER_TYPE;*/
// http://msdn.microsoft.com/en-us/library/windows/desktop/ff476328%28v=vs.85%29.aspx

#endif // DV2549_EXPERIMENT_CONF_H