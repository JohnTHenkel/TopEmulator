#include "formatting.h"
#include "gtest/gtest.h"
#include <string>
using namespace std;



TEST(BytesToHuman, B){
	string bytes = bytes_to_human(900);
	EXPECT_EQ(bytes, "900B");
}
TEST(BytesToHuman,KiB){
	string bytes = bytes_to_human(900000);
	EXPECT_EQ(bytes, "878KiB");
}
TEST(BytesToHuman,MiB){
	string bytes = bytes_to_human(900000000);
	EXPECT_EQ(bytes, "858MiB");
}
TEST(BytesToHuman,GiB){
	string bytes = bytes_to_human(900000000000);
	EXPECT_EQ(bytes, "838GiB");
}




TEST(ClocksToHuman,Decimal){
	string time = clock_ticks_to_human(10ULL);
	EXPECT_EQ(time, "0:00.10");
}

TEST(ClocksToHuman,Seconds){
	string time = clock_ticks_to_human(250ULL);
	EXPECT_EQ(time, "0:02.50");
}

TEST(ClocksToHuman,Minutes){
	string time = clock_ticks_to_human(6250ULL);
	EXPECT_EQ(time, "1:02.50");
}

TEST(ClocksToHuman,Hours){
	string time = clock_ticks_to_human(366250ULL);
	EXPECT_EQ(time, "1:01:02");
}

TEST(ClocksToHuman,ManyHours){
	string time = clock_ticks_to_human(36000000ULL);
	EXPECT_EQ(time, "100h");
}




TEST(UptimeHumanReadable, Under24Hours){
	
	
	string uptime = uptime_to_human(72909.1);
       
	EXPECT_EQ (uptime,"20:15:10");


}

TEST (UptimeHumanReadable, 1Day){
	
	string uptime = uptime_to_human(86400.0+72909.1);
       
	EXPECT_EQ (uptime,"1 day, 20:15:10");



}

TEST (UptimeHumanReadable, 2Days){
	
	string uptime = uptime_to_human(2*86400.0+72909.1);
       
	EXPECT_EQ (uptime,"2 days, 20:15:10");


}






/*
string uptime_to_human(double uptime){

return string();
}


string clock_ticks_to_human(double ticks){

return string();
}


string uptime_to_human(double uptime){

return string();

}*/
