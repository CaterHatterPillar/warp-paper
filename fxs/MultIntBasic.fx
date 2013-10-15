#ifndef DV2549_FXS_MULTINTBASIC_FX
#define DV2549_FXS_MULTINTBASIC_FX

#include <CommonInt.fx>

[ numthreads( BLOCK_SIZE, BLOCK_SIZE, 1 ) ]
void main( uint3 tIdx : SV_GroupThreadID, uint3 bIdx : SV_GroupID ) {
	const uint row = bIdx.y * BLOCK_SIZE + tIdx.y;
	const uint col = bIdx.x * BLOCK_SIZE + tIdx.x;
	if( row >= cRows || col >= cCols ) {
		return;
	}
	
	float sum = 0;
	for( uint i = 0; i < aRows; i++ ) {
		uint idxA = row * aRows + i;
		uint idxB = col + bRows * i;
		sum += mA[ idxA ] * mB[ idxB ];
	}
	mC[ row * cRows + col ] = sum;
}

#endif // DV2549_FXS_MULTINTBASIC_FX