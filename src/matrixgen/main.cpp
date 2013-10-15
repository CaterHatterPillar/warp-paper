#include <stdafx.h>

#include <Matrixgen.h>

void MemLeakDetect() {
#ifdef MATRIXGEN_DEBUG
	CrudeMemoryLeakDetection();
#endif // MATRIXGEN_DEBUG
}

int main( int argc, char* argv[] ) {
	MemLeakDetect();
	std::cout << "\n" << "---" << "\n" << "Matrixgen Utility" << "\n" << "---" << "\n";

	int result = 1;
	unsigned numExpectedArgs = 5; // First argument is the command invoking application.
	if( argc==numExpectedArgs ) {
		std::string precision( argv[ 1 ] );
		unsigned dim = atoi( argv[ 2 ] );
		unsigned min = atoi( argv[ 3 ] );
		unsigned max = atoi( argv[ 4 ] );

		if( precision=="INT" ) {
			// Generate matrix with integer precision.
			Matrixgen< int > mgen( MatrixgenPrecisions_INT, dim, min, max );
			result = (int)!mgen.run();
		} else if( precision=="FLOAT" ) {
			Matrixgen< float > mgen( MatrixgenPrecisions_FLOAT, dim, min, max );
			result = (int)!mgen.run();
			// Generate matrix with float precision.
		} else {
			std::cerr << "Unsupported precision: " << precision;
		}
	} else {
		std::cerr << "Usage: " << argv[ 0 ] << " PRECISION [ INT FLOAT ] DIM MIN MAX" << std::endl;
	}

	if( result==0 ) {
		std::cout << "\n" << "Matrixgen was run sucessfully.";
	} else {
		std::cout << "\n" << "Matrixgen encountered an error!";
	}

#ifdef MATRIXGEN_DEBUG
	getchar();
#endif // MATRIXGEN_DEBUG
	return result;
}