#ifndef DV2549_EXPERIMENT_CBDESC_H
#define DV2549_EXPERIMENT_CBDESC_H

struct CbMatrixProperties {
	unsigned aRows;
	unsigned aCols;

	unsigned bRows;
	unsigned bCols;

	unsigned cRows;
	unsigned cCols;

	unsigned pad[ 2 ];
};

#endif // DV2549_EXPERIMENT_CBDESC_H