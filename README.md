dv2549
======
Performance analysis of emulated GPGPU-kernels.
------

### matrixgen
matrixgen is a tool utilizing C++ AMP along with C++ AMP RNG to generate a couple of randomized matrices (A&B), and from said matrices compile a reference matrix (Ref) making out the product matrix of the two.
------
## Compiling matrixgen
1.	Uncompress amp_rng-1.0.zip in dv2549/lib/matrixgen/amp_rng-1.0/. This is the third party library used to generate random values in a C++ AMP-kernel.
2.	Compile matrixgen using Visual Studio 2012 in any one of the two configurations (Debug or Release).
## Using matrixgen
*	Compilation of matrixgen results in matrixgen.exe located in any one of the configurational directories (Debug/ or Release/) in dv2549/bin/matrixgen/.
*	matrixgen is run from command-line (or from within Visual Studio with default-set arguments) with the following options:
**	DIM - Dimensions of the quadratic matrices desired.
**	MIN - Minimum values in the matrices.
**	MAX - Max values in the matrices.

### experiment
experiment uses DirectCompute to multiply the generated matrices A and B into a product matrix C. experiment then compares the resulting matrix to the reference matrix (Ref) created by matrixgen.
------
## Compiling experiment
## Using experiment

// d3dcompiler_46.dll frin Windows Kits/8.0/Redist/D3D/x86/ into bin/configuration