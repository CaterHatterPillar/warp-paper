#ifndef DV2549_ANALYTICS_ANALYTICS_H
#define DV2549_ANALYTICS_ANALYTICS_H

class Analytics {
public:
	Analytics();
	~Analytics();

	int run();
protected:
private:
	void loadMatrix( std::string p_filepath, DoubleList& io_list );
};

#endif // DV2549_ANALYTICS_ANALYTICS_H