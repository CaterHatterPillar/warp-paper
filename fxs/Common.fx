#ifndef DV2549_FXS_COMMON_H
#define DV2549_FXS_COMMON_H

cbuffer CbMatrixProperties : register( b0 ) {
	uint aRows;
	uint aCols;

	uint bRows;
	uint bCols;

	uint cRows;
	uint cCols;

	uint pad[ 2 ];
};

#endif // DV2549_FXS_COMMON_H

/*uint3 blockID			: SV_GroupID,
uint threadIDBlockIndex : SV_GroupIndex,
uint3 threadIDDispatch	: SV_DispatchThreadID,
uint3 threadIDBlock		: SV_GroupThreadID*/