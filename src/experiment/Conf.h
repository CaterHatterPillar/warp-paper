#ifndef DV2549_EXPERIMENT_CONF_H
#define DV2549_EXPERIMENT_CONF_H

static const LPCWSTR PathKernelMult = L"KernelMult.cso";

static const std::string g_resPath = "../../../res/";

static const std::string g_mxgPath = "../../../mxg/"; // Path to mxg-dir.
static const std::string g_mxgA = "a.mxg";
static const std::string g_mxgB = "b.mxg";
static const std::string g_mxgC = "c.mxg";
static const std::string g_mxgRef = "ref.mxg";

enum ExperimentPrecisions {
	ExperimentPrecisions_INTEGER	= 0,
	ExperimentPrecisions_FLOAT		= 1
};

// Please note that SOFT makes use of the REFERENCE-driver, rather than the SOFTWARE-driver.
enum ExperimentAccelerations {
	ExperimentAccelerations_HARD	= 1, // D3D_DRIVER_TYPE_HARDWARE
	ExperimentAccelerations_SOFT	= 2, // D3D_DRIVER_TYPE_REFERENCE
	ExperimentAccelerations_WARP	= 5	 // D3D_DRIVER_TYPE_WARP
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