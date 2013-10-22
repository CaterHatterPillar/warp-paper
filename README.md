dv2549
======
Performance analysis of emulated GPGPU-kernels.
------

The compiled article may be found here:
https://dl.dropboxusercontent.com/u/42347914/dv2549/article.pdf

The raw data used throughout the material can be found under branch dv2549_data:
https://github.com/CaterHatterPillar/dv2549/tree/dv2549_data

### matrixgen ###
matrixgen is a tool utilizing C++ AMP along with C++ AMP RNG to generate a couple of randomized matrices (A&B), and from said matrices compile a reference matrix (Ref) making out the product matrix of the two.

#### matrixgen compile ####
1.	Uncompress amp_rng-1.0.zip in dv2549/lib/matrixgen/amp_rng-1.0/. This is the third party library used to generate random values in a C++ AMP-kernel.
2.	Compile matrixgen using Visual Studio 2012 in any one of the two configurations (Debug or Release).

#### matrixgen use ####
*	Compilation of matrixgen results in matrixgen.exe located in any one of the configurational directories (Debug/ or Release/) in dv2549/bin/matrixgen/.
*	matrixgen is run from command-line (or from within Visual Studio with default-set arguments) with the following options:
	*	PRECISION [ INT, FLOAT ] - What data-type is to be generated.
	*	DIM - Dimensions of the quadratic matrices desired.
	*	MIN - Minimum values in the matrices.
	*	MAX - Max values in the matrices.
*	Running matrixgen results in three .mxg-files located under the /mxg/-directory. The files named a.mxg and b.mxg, respectively, make out the two randomized matrices. ref.mxg is the matrix product of ab.

### experiment ###
experiment uses DirectCompute to multiply the generated matrices A and B into a product matrix C. experiment then compares the resulting matrix to the reference matrix (Ref) created by matrixgen.

#### experiment compile ####
1.	Compile experiment using Visual Studio 2012 in any one of the two configuraions (Debug or Relase).
2.	Copy d3dcompiler_46.dll from Windows Kits/8.0/Redist/D3D/x86 into dv2549/bin/experiment/Debug/ and dv2549/bin/experiment/Release/.

#### experiment use ####
*	Compilation of experiment results in experiment.exe along with compiled DirectCompute-kernels located in any one of the configurational directories (Debug/ or Release/) in dv2549/bin/experiment/.
*	experiment is run from command-line (or from within Visual Studio with default-set arguments) with he following options:
	*	KERNEL [ BASIC, TILE ] - What kernel is to be run. Supports a very basic implementation (BASIC) and one utilizing shared memory (TILE).
	*	ACCELERATION [ HARD, SOFT, WARP ] - Dictates what driver type to instantiate the DirectX device with.
	*	PRECISION [ INT, FLOAT ] - What data-type is loaded and used thruought the experiment.
*	Running experiment results in a .res-file located under the /res/-directory. This file contains analytic data of the execution, such as the time taken to dispatch the kernel.
*	If running experiment from outside of Visual Studio, d3dcompiler_46.dll must be have been copied from Windows Kits/8.0/Redist/D3D/x86/ into the configurational directory from which experiment.exe is run.

### analytics ###
analytics is a smaller utility developed to compose data surrounding possible precisional deviations in-between matrices C and Ref. analytics compiles the minimum- and maximum-deviation encountered, as well as to calculate the standard deviation of said precisional deviation. In turn, analytics outputs this information to an intermediate file.

#### analytics compile ####
Compile analytics using Visual Studio 2012 in any one of the two configuraions (Debug or Relase).

#### analytics use ####
Simply run analytics.exe. analytics takes no arguments or flags, but assumes existant c.mxg and ref.mxg.


### dv2549.py ###
dv2549.py is a Python script that runs the matrixgen and experiment a set amount of times with varying configurations. The scripts purpose is to collect the output of experiment and compile research data.
When dv2549.py has been run, results will be collected in - sequence - under dv2549/. Results collected are the following:
*	Kernel dispatch time (ms)
*	Precision deviation minimum
*	Precision deviation maximum
*	Precision deviation standard

#### dv2549.py use ####
1.	Move the script into the configurational folder of experiment being used (dv2549/bin/experiment/Debug or dv2549/bin/experiment/Release).
2.	Make sure experiment.exe has been compiled sucessfully.
3.	Make sure matrixgen.exe and analytics.exe have both been compiled in Release-mode (dv2549/bin/matrixgen/Release/ & dv2549/bin/analytics/Release/).
4.	Run dv2549.py using Python 3.4 or later.
