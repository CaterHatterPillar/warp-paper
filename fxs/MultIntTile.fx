#ifndef DV2549_FXS_MULTINTTILE_H
#define DV2549_FXS_MULTINTTILE_H

#include <CommonInt.fx>

groupshared int mAs[ BLOCK_SIZE ][ BLOCK_SIZE ];
groupshared int mBs[ BLOCK_SIZE ][ BLOCK_SIZE ];

[ numthreads( BLOCK_SIZE, BLOCK_SIZE, 1 ) ]
void main( uint3 tIdx : SV_GroupThreadID, uint3 bIdx : SV_GroupID ) {
	const uint row = bIdx.y * BLOCK_SIZE + tIdx.y;
	const uint col = bIdx.x * BLOCK_SIZE + tIdx.x;
	if( row >= cRows || col >= cCols ) {
		return;
	}
	
	int sum = 0;
	const uint blocks = aRows / BLOCK_SIZE;
	for( uint i = 0; i < blocks; i++ ) {
		mAs[ tIdx.y ][ tIdx.x ] = mA[ row * aRows + ( i * BLOCK_SIZE + tIdx.x ) ];
		mBs[ tIdx.y ][ tIdx.x ] = mB[ col + bRows * ( i * BLOCK_SIZE + tIdx.y ) ];
		GroupMemoryBarrierWithGroupSync();
	
		for( uint j = 0; j < BLOCK_SIZE; j++ ) {
			sum += mAs[ tIdx.y ][ j ] * mBs[ j ][ tIdx.x ];
		}
		GroupMemoryBarrierWithGroupSync();
	}
	mC[ row * cRows + col ] = sum;
}

#endif // DV2549_FXS_MULTINTTILE_H