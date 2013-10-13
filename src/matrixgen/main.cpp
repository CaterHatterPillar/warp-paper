#include <stdafx.h>

#include <Matrixgen.h>

void MemLeakDetect() {
#ifdef MATRIXGEN_DEBUG
	CrudeMemoryLeakDetection();
#endif // MATRIXGEN_DEBUG
}

int main( int argc, char* argv[] ) {
	MemLeakDetect();

	int result = 1;
	unsigned numExpectedArgs = 4; // First argument is the command invoking application.
	if( argc==numExpectedArgs ) {
		unsigned dim = atoi( argv[ 1 ] );
		unsigned min = atoi( argv[ 2 ] );
		unsigned max = atoi( argv[ 3 ] );

		Matrixgen mgen( dim, min, max );
		result = (int)!mgen.run();
	} else {
		std::cerr << "Usage: " << argv[ 0 ] << " DIM MIN MAX" << std::endl;
	}
	return result;
}