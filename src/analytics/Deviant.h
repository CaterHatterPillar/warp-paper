#ifndef DV2549_ANALYTICS_DEVIANT_H
#define DV2549_ANALYTICS_DEVIANT_H

class Deviant {
public:
	Deviant();
	~Deviant();

	void establishDeviations( Analytic& io_analytic, DoubleList p_c, DoubleList p_ref );
protected:
private:
	void calculateDeviations( Analytic& io_analytic, DoubleList p_devs );
	void getDeviations( DoubleList p_c, DoubleList p_ref, DoubleList& io_devs );
};

#endif // DV2549_ANALYTICS_DEVIANT_H