#ifndef DV2549_FXS_COMMONFLOAT_H
#define DV2549_FXS_COMMONFLOAT_H

#include <Common.fx>

StructuredBuffer< float > mA : register( t0 );
StructuredBuffer< float > mB : register( t1 );

RWBuffer< float > mC : register( u0 );

#endif // DV2549_FXS_COMMONFLOAT_H