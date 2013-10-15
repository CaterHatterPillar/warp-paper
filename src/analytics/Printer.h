#ifndef DV2549_ANALYTICS_PRINTER_H
#define DV2549_ANALYTICS_PRINTER_H

class Printer {
public:
	Printer( Analytic p_analytics );
	~Printer();

	void init( std::string filepath );
protected:
private:
	Analytic m_analytic;
};

#endif // DV2549_ANALYTICS_PRINTER_H