#ifndef DV2549_FXS_COMMON_H
#define DV2549_FXS_COMMON_H

#define BLOCK_SIZE 16

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