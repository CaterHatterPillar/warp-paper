#include <stdafx.h>

#include <Deviant.h>

Deviant::Deviant() {
	concurrency::accelerator default_device;
	std::wcout << std::endl << L"Initializing C++ AMP with device: " << default_device.get_description() + L".";
	if( default_device==concurrency::accelerator( concurrency::accelerator::direct3d_ref) ) {
		std::cout << std::endl << "Warning. Running C++ AMP using a slow emulator.";
	}
}
Deviant::~Deviant() {
	// Do nothing.
}

void Deviant::establishDeviations( Analytic& io_analytic, DoubleList p_c, DoubleList p_ref ) {
	DoubleList devs;
	
	getDeviations( p_c, p_ref, devs );
	calculateDeviations( io_analytic, devs );

	free( devs.list );
}

void Deviant::calculateDeviations( Analytic& io_analytic, DoubleList p_devs ) {
	std::vector< double > devs;
	devs.assign( p_devs.list, p_devs.list + p_devs.num );

	// Establish min- and max- deviation.
	auto itMax = std::max_element( std::begin( devs ), std::end( devs ) );
	auto itMin = std::min_element( std::begin( devs ), std::end( devs ) );
	io_analytic.deviationMax = *itMax;
	io_analytic.deviationMin = *itMin;

	// Establish standard deviation in an exciting, esoteric, manner:
	double sum = std::accumulate( devs.begin(), devs.end(), 0.0 );
	double mean = sum / devs.size();
	std::vector< double > diff( devs.size() );
	std::transform( devs.begin(), devs.end(), diff.begin(), std::bind2nd( std::minus< double >(), mean ) );
	double sqSum = std::inner_product( diff.begin(), diff.end(), diff.begin(), 0.0 );
	double std = std::sqrt( sqSum / devs.size() );
	io_analytic.deviationStandard = std;
}
void Deviant::getDeviations( DoubleList p_c, DoubleList p_ref, DoubleList& io_devs ) {
	std::cout << std::endl << "Compiling deviations...";
	io_devs.num = p_c.num; // hack
	io_devs.list = (double*)malloc( sizeof( double ) * io_devs.num );
	
	concurrency::array_view< double > iC( p_c.num, p_c.list ); 
	concurrency::array_view< double > iRef( p_ref.num, p_ref.list );
	concurrency::array_view< double > ioDevs( io_devs.num, io_devs.list );
	parallel_for_each(
		ioDevs.extent,
		[=]( concurrency::index< 1 > idx ) restrict( amp ) {
			int i = idx[ 0 ];
			double c = iC[ i ];
			double ref = iRef[ i ];
			ioDevs[ i ] = concurrency::precise_math::fabs( ref - c );
	}
	);
	ioDevs.synchronize();
}