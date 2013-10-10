#ifndef DV2549_EXPERIMENT_CONF_H
#define DV2549_EXPERIMENT_CONF_H

// This is terrible. Fix.
#ifdef EXPERIMENT_DEBUG
static const LPCWSTR PathKernelTest = L"../../bin/experiment/Debug/KernelTest.cso";
#else
static const LPCWSTR PathKernelTest = L"../../bin/experiment/Release/KernelTest.cso";
#endif // EXPERIMENT_DEBUG

#endif // DV2549_EXPERIMENT_CONF_H
