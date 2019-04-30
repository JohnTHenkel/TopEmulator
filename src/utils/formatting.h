#pragma once
#include <string>
#include <iostream>
using namespace std;

/**
 * Takes a number of bytes as double and returns it as a human readable format
 * (e.g. B, KiB, MiB, GiB)
 */

string bytes_to_human(long long bytes);

/**
 * Takes a number of clock ticks and returns it as a human readable format
 * (e.g. "10:02.50")
 */

string clock_ticks_to_human(long long ticks);

struct Time {
	
	long long decimal;
	long long seconds;
	long long minutes;
	long long hours;
	long long days;
	
	string to_string(){
		string time_string="";
		if(days>0){
		       	time_string+= std::to_string(days) + " day";
			if(days>1) time_string+="s"; 
			time_string+=", ";
		}
		if(hours>24){
		       	time_string=std::to_string(hours) + "h";
			return time_string;
		}
		else if(hours>0) time_string+=std::to_string(hours)+":";
		if(minutes<10&&hours>0) time_string+="0";
		time_string+=std::to_string(minutes)+":";
		if(seconds<10) time_string+="0";
		time_string+=std::to_string(seconds);
		if (decimal>0) time_string+= "." + std::to_string(decimal);

		

			
		return time_string;
	}


};





/**
 * Takes a number of uptime and returns it as a human readable time
 * (e.g. "2 days, 20:15:10")
 */

string uptime_to_human(double uptime);
