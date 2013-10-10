#ifndef DV2549_EXPERIMENT_COMMONDX_H
#define DV2549_EXPERIMENT_COMMONDX_H

#include <d3d11.h>
#include <D3D11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>

#define ASSERT_RELEASE( arg ) assert( arg ); arg->Release(); arg = nullptr;

#endif // DV2549_EXPERIMENT_COMMONDX_H