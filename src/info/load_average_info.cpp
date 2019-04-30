#include "load_average_info.h"
#include <fstream>
#include <iostream>

using namespace std;


LoadAverageInfo get_load_average() {
	ifstream loadavg_file(PROC_ROOT "/loadavg");
	if(!loadavg_file){
		cerr << "Unable to read from /proc/loadavg"<<endl;
		exit(EXIT_FAILURE);
	}
	LoadAverageInfo load_avg;
	loadavg_file>>load_avg.one_min>>load_avg.five_mins>>load_avg.fifteen_mins;
	
  return load_avg;
}
