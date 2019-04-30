#include "memory_info.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


MemoryInfo get_memory_info() {
	ifstream meminfo_file(PROC_ROOT "/meminfo");
	if(!meminfo_file){
		cerr<< "Unable to read from /proc/meminfo" <<endl;
		exit(EXIT_FAILURE);
	}


	MemoryInfo mem_info;
	string substr;
	while(meminfo_file.good()){
		meminfo_file>>substr;
		if(substr=="MemTotal:"){
			meminfo_file>>mem_info.total_memory>>substr;
		}
		else if(substr=="MemFree:"){
			meminfo_file>>mem_info.free_memory>>substr;  
		}
		else if(substr=="Buffers:"){
			meminfo_file>>mem_info.buffers_memory>>substr;
		}
		else if(substr=="Cached:"){
			meminfo_file>>mem_info.cached_memory>>substr;
		}
		else if(substr=="SwapTotal:"){
			meminfo_file>>mem_info.total_swap>>substr;
		}
		else if(substr=="SwapFree:"){
			meminfo_file>>mem_info.free_swap>>substr;
		}
		else{
			meminfo_file>>substr>>substr;
		}
	}
	mem_info.used_memory=mem_info.total_memory-mem_info.free_memory-mem_info.buffers_memory-mem_info.cached_memory;
	
  return mem_info;
}
