#ifndef DV2549_FXS_KERNELMULT_FX
#define DV2549_FXS_KERNELMULT_FX

#define BLOCK_SIZE_X 1
#define BLOCK_SIZE_Y 1

StructuredBuffer< int > mA : register( t0 );
StructuredBuffer< int > mB : register( t1 );
RWBuffer< int > mC : register( u0 );

cbuffer CbMatrixProperties : register( b0 ) {
	uint aRows;
	uint aCols;

	uint bRows;
	uint bCols;

	uint cRows;
	uint cCols;

	uint pad[ 2 ];
};

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

#endif // DV2549_FXS_KERNELMULT_FX

/*uint3 blockID			: SV_GroupID,
uint threadIDBlockIndex : SV_GroupIndex,
uint3 threadIDDispatch	: SV_DispatchThreadID,
uint3 threadIDBlock		: SV_GroupThreadID*/