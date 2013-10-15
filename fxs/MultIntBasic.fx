#ifndef DV2549_FXS_MULTINTBASIC_FX
#define DV2549_FXS_MULTINTBASIC_FX

#include <CommonInt.fx>

#define BLOCK_SIZE_X 1
#define BLOCK_SIZE_Y 1

[ numthreads( BLOCK_SIZE_X, BLOCK_SIZE_Y, 1 ) ]
void main( uint3 tIdDispatch : SV_DispatchThreadID ) {
	if( tIdDispatch.x >= bRows || tIdDispatch.y >= aCols ) {
		return;
	}
	
	float sum = 0;
	for( uint i = 0; i < aRows; i++ ) {
		uint idxA = tIdDispatch.y * aRows + i;
		uint idxB = tIdDispatch.x + i * bRows;
		sum += mA[ idxA ] * mB[ idxB ];
	}
	mC[ tIdDispatch.y * cRows + tIdDispatch.x ] = sum;
}

#endif // DV2549_FXS_MULTINTBASIC_FX