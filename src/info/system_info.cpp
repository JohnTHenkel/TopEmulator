#include "system_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

using namespace std;


double get_uptime() {
	ifstream uptime_file(PROC_ROOT "/uptime");
	if (!uptime_file){
		cerr << "Unable to read from /proc/uptime"<<endl;
		exit(EXIT_FAILURE);
	}
	double uptime;
	uptime_file>>uptime;
  return uptime;
}


SystemInfo get_system_info() {
	SystemInfo system_info;

	
	system_info.load_average=get_load_average();
	system_info.memory_info=get_memory_info();
	system_info.cpus=get_cpu_info();
	system_info.processes=get_all_processes(PROC_ROOT);

	system_info.num_processes=system_info.processes.size();
	system_info.num_threads=0;
	system_info.num_user_threads=0;
	system_info.num_kernel_threads=0;
	system_info.num_running=0;
	system_info.uptime=get_uptime();
	for(size_t i=0;i<system_info.num_processes;i++){
		
			
			
			
		if(system_info.processes.at(i).is_kernel_thread()){
			system_info.num_kernel_threads++;
		}
		
		if(system_info.processes.at(i).state=='R'){
			system_info.num_running++;
		}
		for (size_t j = 0; j<system_info.processes.at(i).threads.size();j++){
			if(system_info.processes.at(i).threads.at(j).is_user_thread()){
				system_info.num_user_threads++;
			}
		}
		
		
	}
	system_info.num_threads=system_info.num_user_threads+system_info.num_kernel_threads;
	return system_info;
}
