#include "formatting.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>

using namespace std;


string bytes_to_human(long long bytes){
long long leftover;
vector<string> units = {"B", "KiB", "MiB", "GiB"};
for(int i=3;i>=0;i--){
	leftover=bytes/(pow(1024,i));
	if(leftover>0){
		return to_string(leftover)+units.at(i);
	}

}


return "";
}


string clock_ticks_to_human(long long ticks){
	Time time;
	int clocks_per_second = sysconf(_SC_CLK_TCK);
	time.days=0;
	time.hours=ticks/clocks_per_second/3600;
	time.minutes=((ticks/clocks_per_second)%3600)/60;
	time.seconds=((ticks/clocks_per_second)%3600)%60;
	time.decimal=(((static_cast<double>(ticks)/clocks_per_second/3600-time.hours)*60-time.minutes)*60-time.seconds)*clocks_per_second;
	if(time.hours>0) time.decimal=0;	

return time.to_string();
}


string uptime_to_human(double uptime){
	long long utime=ceil(uptime);
	Time time;
	time.days=utime/(3600*24);
	time.hours=(utime%(3600*24))/3600;
	time.minutes=((utime%(3600*24))%3600)/60;
	time.seconds=(((utime%(3600*24))%3600)%60);
	time.decimal=0;	


return time.to_string();
}



