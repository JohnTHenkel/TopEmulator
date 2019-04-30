/**
 * Contains the main() routine of what will eventually be your version of top.
 */

#include <cstdlib>
#include <ncurses.h>
#include "info/system_info.h"
#include "utils/formatting.h"
#include <algorithm>
#include <unistd.h>
#include <getopt.h>
using namespace std;


/**
 * Gets a character from the user, waiting for however many milliseconds that
 * were passed to timeout() below. If the letter entered is q, this method will
 * exit the program.
 */
void exit_if_user_presses_q() {
  char c = getch();

  if (c == 'q') {
    endwin();
    exit(EXIT_SUCCESS);
  }
}

/**
 * Operators for comparing process infos.
 */
struct less_than_pid {
	inline bool operator() (const ProcessInfo& process1, const ProcessInfo& process2){
		return (process1.pid<process2.pid);
	}

};
struct greater_than_cpu {
	inline bool operator() (const ProcessInfo& process1, const ProcessInfo& process2){
		return (process1.cpu_percent>process2.cpu_percent);
	}

};
struct greater_than_mem {
	inline bool operator() (const ProcessInfo& process1, const ProcessInfo& process2){
		return (process1.rss>process2.rss);
	}

};
struct greater_than_time {
	inline bool operator() (const ProcessInfo& process1, const ProcessInfo& process2){
		return (process1.total_time>process2.total_time);
	}

};

/**
 * Function for calculating the utlization of each CPU.
 */

void calculate_cpu_percent(vector<ProcessInfo>& current,vector<ProcessInfo> past,CpuInfo delta){
	for (size_t i =0; i<current.size();i++){
		for(size_t j=0;j<past.size();j++){
			if (current.at(i).pid==past.at(j).pid){
					
					current.at(i).cpu_percent=static_cast<double>(current.at(i).total_time-past.at(j).total_time)/delta.total_time()*100.0;
			}
			
		}

	}

}
/**
 * Entry point for the program.
 */
int main(int argc, char** argv) {
  int delay=1000;
  int sort_order = 1;
  bool valid_sort=false;
  vector<string> sort_options={"PID","CPU","MEM","TIME"};
  static struct option long_options[]={
	  {"help",no_argument,NULL,'h'},
	  {"delay",required_argument,NULL,'d'},
	  {"sort-key",required_argument,NULL,'s'},
	  {0,0,0,0}
  };
  
  /**
   *Flag parsing with getopt_long
   */
  while(true){
	int option_index=0;
	int flag_char = getopt_long(argc,argv,"hd:s:",long_options,&option_index);

	if (flag_char==-1){
	break;
	}
	switch (flag_char){
		case 'h':
			cout <<"\nhelp: mytop\nTo run, enter ./mytop\nContains data relating to uptime, load averages, processes, threads,and memory.\nThe program has a delay of 1000ms and sorts by CPU% by default."<<endl;
			cout <<"To set the refresh time of the data, use flag --delay arg1 or -d arg1 where arg1 is the desired delay in ms.\nPassing in no arg will result in an error."<<endl;
			cout <<"To set the sort order of the process table, use flag --sort-key or -s with arguments 'PID','CPU','MEM', or 'TIME'"<<endl;
			cout <<"For help, use flag --help or -h."<<endl<<endl;
			exit(0);
		case 'd':
		
			delay=stoi(optarg);					
			break;
		case 's':{
			

			for (size_t i=0;i<sort_options.size();i++){
			
				if(optarg==sort_options.at(i)){
					sort_order=i;
					valid_sort=true;
					break;
				}
			}
			if(!valid_sort){
				cerr <<"Invalid sort option: "<<optarg<<endl;
				exit(1);
			}	
			break;
		}
		case '?':
			cerr<<"Invalid flag options."<<endl;
			exit(1);
		default:
			exit(EXIT_FAILURE);
	}


  }


  // ncurses initialization
  initscr();

  // Don't show a cursor.
  curs_set(FALSE);

  // Set getch to return after 1000 milliseconds; this allows the program to
  // immediately respond to user input while not blocking indefinitely.
  timeout(delay);


  SystemInfo current_info = get_system_info();
  SystemInfo past_info=get_system_info();

  while (true) {

    //Refresh the system info
    past_info=current_info;
    current_info=get_system_info();
    wclear(stdscr);

    // Display the data:

    //uptime data:
    printw(("top - up "+uptime_to_human(current_info.uptime)).c_str());
    //load average data:
    printw(" load average: %.2f %.2f %.2f ",current_info.load_average.one_min,current_info.load_average.five_mins,current_info.load_average.fifteen_mins);
    //Total process data:
    printw("\nTasks: %d total, %d running",current_info.num_processes,current_info.num_running);
    //Thread data:
    printw("\nThreads:%d ",current_info.num_threads);

    //Total amount of memory:
    MemoryInfo current_memory = current_info.memory_info;
    printw("\nKiB Mem : %u total, %u free, %u used",current_memory.total_memory,current_memory.free_memory,current_memory.used_memory);

    //Individual CPU data:
    for (size_t i = 0;i<current_info.cpus.size();i++){
	CpuInfo delta = current_info.cpus.at(i)-past_info.cpus.at(i);
	double user_percent=static_cast<double>((delta.user_time+delta.nice_time))/delta.total_time()*100;
	double system_percent=static_cast<double>(delta.total_system_time())/delta.total_time()*100;
	double idle_percent=static_cast<double>(delta.total_idle_time())/delta.total_time()*100;
	
	if(i==0){
		  printw("\nAll     : %.2f%% us, %.2f%% sy, %.2f%% id", user_percent,system_percent, idle_percent);
		  continue;
	}	
	 printw("\nCPU: %d  : %.2f%% us, %.2f%% sy, %.2f%% id",i-1, user_percent,system_percent, idle_percent);
    }


    //Calculate the process cpu percents:
    
    CpuInfo delta = current_info.cpus.at(1)-past_info.cpus.at(1);
    calculate_cpu_percent(current_info.processes, past_info.processes, delta);

    //Sort the processes acording to the specified sort order:
    switch(sort_order){
	case 0://Sort by PID
		sort(current_info.processes.begin(),current_info.processes.end(),less_than_pid());
		break;
	case 1://Sort by CPU
		sort(current_info.processes.begin(),current_info.processes.end(),greater_than_cpu());
		break;
	case 2://Sort by MEM
		sort(current_info.processes.begin(),current_info.processes.end(),greater_than_mem());
		break;
	case 3://Sort by TIME
		sort(current_info.processes.begin(),current_info.processes.end(),greater_than_time());
		break;
	default:
		break;

    }
       //Individual process data:

    printw("\nPID:\tRES\tSTATE\tCPU%%\tTIME\tCMD");   
    for(size_t i = 0; i<current_info.processes.size();i++){

	ProcessInfo current_process=current_info.processes.at(i);
	string time = clock_ticks_to_human(current_process.total_time);
	string rss = bytes_to_human(current_process.rss*sysconf(_SC_PAGESIZE));
	if(rss.length()==0) rss="0B";
	printw("\n%d\t%s\t%c\t%.2f\t%s\t%s",current_process.pid,rss.c_str(),current_process.state,current_process.cpu_percent,time.c_str(),current_process.comm);

    }
		    
    // Redraw the screen.
    refresh();



    // End the loop and exit if Q is pressed
    exit_if_user_presses_q();
  }

  // ncurses teardown
  endwin();

  return EXIT_SUCCESS;
}
