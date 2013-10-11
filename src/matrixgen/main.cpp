#include <stdafx.h>

#include <Matrixgen.h>

// static const unsigned NumExpectedArgs = 1;

int main( int argc, char* argv[] ) {
#ifdef MATRIXGEN_DEBUG
	CrudeMemoryLeakDetection();
#endif // MATRIXGEN_DEBUG

	// 1. Get arguments.
	// 2. Generate matrix.

	unsigned arg = 10;
	Matrixgen mgen( arg );
	bool sucess = mgen.run();
	return (int)sucess;
}

/*
int result = 0;
unsigned numExpectedArgs = NumExpectedArgs + 1; // First argument is the command invoking application.
if( argc==numExpectedArgs ) {
// Generate matrix.
} else {
std::cerr << "Usage: " << argv[ 0 ] << " WIDTH" << std::endl;
result = 1;
}
return result;
*/