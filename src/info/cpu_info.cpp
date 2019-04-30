#include "cpu_info.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


vector<CpuInfo> get_cpu_info() {
	ifstream getcpu_file(PROC_ROOT "/stat");
	if(!getcpu_file){
		cerr<< "Unable to read from /proc/stat" <<endl;
		exit(EXIT_FAILURE);
	}
	string substr;
	vector<CpuInfo> cpu_info_vector;
	while(getcpu_file.good()){
		getcpu_file>>substr;
		if(substr.find("cpu")!=string::npos){
			CpuInfo cpu_info;
			getcpu_file>>cpu_info.user_time;
			getcpu_file>>cpu_info.nice_time;
			getcpu_file>>cpu_info.system_time;
			getcpu_file>>cpu_info.idle_time;
			getcpu_file>>cpu_info.io_wait_time;
			getcpu_file>>cpu_info.irq_time;
			getcpu_file>>cpu_info.softirq_time;
			getcpu_file>>cpu_info.steal_time;
			getcpu_file>>cpu_info.guest_time;
			getcpu_file>>cpu_info.guest_nice_time;

			cpu_info_vector.push_back(cpu_info);	
		}
		else{
			getline(getcpu_file,substr);
		}

	}

	return cpu_info_vector;
}


CpuInfo operator -(const CpuInfo& lhs, const CpuInfo& rhs) {
	CpuInfo cpu_info;

	cpu_info.user_time=lhs.user_time-rhs.user_time;
	cpu_info.nice_time=lhs.nice_time-rhs.nice_time;
	cpu_info.system_time=lhs.system_time-rhs.system_time;
	cpu_info.idle_time=lhs.idle_time-rhs.idle_time;
	cpu_info.io_wait_time=lhs.io_wait_time-rhs.io_wait_time;
	cpu_info.irq_time=lhs.irq_time-rhs.irq_time;
	cpu_info.softirq_time=lhs.softirq_time-rhs.softirq_time;
	cpu_info.steal_time=lhs.steal_time-rhs.steal_time;
	cpu_info.guest_time=lhs.guest_time-rhs.guest_time;
	cpu_info.guest_nice_time=lhs.guest_nice_time-rhs.guest_nice_time;



  return cpu_info;
}
