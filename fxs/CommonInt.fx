#ifndef DV2549_FXS_COMMONINT_H
#define DV2549_FXS_COMMONINT_H

#include <Common.fx>

StructuredBuffer< int > mA : register( t0 );
StructuredBuffer< int > mB : register( t1 );

RWBuffer< int > mC : register( u0 );

#endif // DV2549_FXS_COMMONINT_H