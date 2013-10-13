#ifndef DV2549_EXPERIMENT_CONF_H
#define DV2549_EXPERIMENT_CONF_H

static const LPCWSTR PathKernelMult = L"KernelMult.cso";

static const std::string g_resPath = "../../../res/";

static const std::string g_mxgPath = "../../../mxg/"; // Path to mxg-dir.
static const std::string g_mxgA = "a.mxg";
static const std::string g_mxgB = "b.mxg";
static const std::string g_mxgC = "c.mxg";
static const std::string g_mxgRef = "ref.mxg";

enum MatrixgenPrecisions {
	MatrixgenPrecisions_INTEGER = 0
};

#endif // DV2549_EXPERIMENT_CONF_H

/*
// This is terrible. Fix.
#ifdef EXPERIMENT_DEBUG
static const LPCWSTR PathKernelMult = L"../../bin/experiment/Debug/KernelMult.cso";
#else
static const LPCWSTR PathKernelMult = L"../../bin/experiment/Release/KernelMult.cso";
#endif // EXPERIMENT_DEBUG
*/