#include "process_info.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

using namespace std;


ProcessInfo get_process(int pid, const char* basedir) {
	ProcessInfo process_info;
	stringstream ss;
	ss<<basedir<<"/"<<pid<<"/stat";
	string joined_str=ss.str();
	ifstream stat_file(joined_str.c_str());
	if(!stat_file){
		cerr <<"Unable to read from"<< joined_str <<endl;
		return ProcessInfo();
	}
	stat_file>>process_info.pid;
	string comm_str;
	do { 
		stat_file >> comm_str;
	}while (comm_str.back()!=')');
	strcpy(process_info.comm,comm_str.c_str());

	stat_file
		>>process_info.state
		>>process_info.ppid
		>>process_info.pgrp
		>>process_info.session
		>>process_info.tty_nr
		>>process_info.tpgid
		>>process_info.flags
		>>process_info.minflt
		>>process_info.cminflt
		>>process_info.majflt
		>>process_info.cmajflt
		>>process_info.utime
		>>process_info.stime
		>>process_info.cutime
		>>process_info.cstime
		>>process_info.priority
		>>process_info.nice
		>>process_info.num_threads
		>>process_info.itrealvalue
		>>process_info.starttime
		>>process_info.vsize
		>>process_info.rss
		>>process_info.rsslim
		>>process_info.startcode
		>>process_info.endcode
		>>process_info.startstack
		>>process_info.kstkesp
		>>process_info.kstkeip
		>>process_info.signal
		>>process_info.blocked
		>>process_info.sigignore
		>>process_info.sigcatch
		>>process_info.wchan
		>>process_info.nswap
		>>process_info.cnswap
		>>process_info.exit_signal
		>>process_info.processor
		>>process_info.rt_priority
		>>process_info.policy
		>>process_info.delayacct_blkio_ticks
		>>process_info.guest_time
		>>process_info.cguest_time;
	

	ss=stringstream();
	ss<<basedir<<"/"<<pid<<"/statm";
	joined_str=ss.str();
	ifstream statm_file(joined_str.c_str());
	if(!statm_file){
		cerr <<"Unable to read from " << joined_str<<endl;
		exit(EXIT_FAILURE);
	}	
	statm_file
		>>process_info.size
		>>process_info.resident
		>>process_info.share
		>>process_info.trs
		>>process_info.lrs
		>>process_info.drs
		>>process_info.dt;
	ss=stringstream();

	ss<<basedir<<"/"<<pid<<"/cmdline";
	joined_str=ss.str();
	ifstream cmd_file(joined_str.c_str());
	if(!cmd_file){
		cerr <<"Unable to read from " << joined_str<<endl;
		exit(EXIT_FAILURE);
	}
	cmd_file>>process_info.command_line;
	
	if(process_info.command_line==""){
	
		ss=stringstream();
		ss<<basedir<<"/"<<pid<<"/comm";
		joined_str=ss.str();
		ifstream comm_file(joined_str.c_str());
		if(!comm_file){
			cerr <<"Unable to read from " << joined_str<<endl;
			exit(EXIT_FAILURE);
		}
		comm_file>>process_info.command_line;


	}
	
	for(size_t i=0;i<process_info.command_line.length(); i++){
		if(process_info.command_line.at(i)=='\0'){
			if(i==process_info.command_line.length()-1){
				process_info.command_line.pop_back();
			}
			else{
				process_info.command_line.at(i)=' ';
			}

		}



	}
	
	ss=stringstream();
	ss<<basedir<<"/"<<pid<<"/status";
	joined_str=ss.str();
	ifstream status_file(ss.str());
	if(!status_file){
		cerr <<"Unable to read from " << joined_str<<endl;
		exit(EXIT_FAILURE);
	}
	while(status_file.good()){
		string substr;
		status_file>>substr;
		if(substr.find("Tgid")!=string::npos){
			status_file>>process_info.tgid;	
		break;

		}

	}


	ss=stringstream();	
	ss<<basedir<<"/"<<pid<<"/task";
	joined_str=ss.str();
	process_info.threads=get_all_processes(joined_str.c_str());
	process_info.total_time=process_info.stime+process_info.utime;
	process_info.cpu_percent=0;

	return process_info;
}


vector<ProcessInfo> get_all_processes(const char* basedir) {
	DIR * dir;
	struct dirent *directory;
	dir=opendir(basedir);
	vector<ProcessInfo> all_processes;
	if(dir){
		while((directory=readdir(dir))!=NULL){
			int pid=atol(directory->d_name);
			if(pid<=0){
				continue;
			}
				all_processes.push_back(get_process(pid,basedir));	
			
		}
	}
	
	
	closedir(dir);
	return all_processes;
}
