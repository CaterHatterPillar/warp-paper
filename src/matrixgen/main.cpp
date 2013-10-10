#include <stdafx.h>

static const unsigned NumExpectedArgs = 1;

int main( int argc, char* argv[] ) {
	int result = 0;
	unsigned numExpectedArgs = NumExpectedArgs + 1; // First argument is the command invoking application.
	if( argc==numExpectedArgs ) {
		// Generate matrix.
	} else {
		std::cerr << "Usage: " << argv[ 0 ] << " WIDTH" << std::endl;
		result = 1;
	}
	return result;
}