# TopEmulator
This program is an emulator of the 'top' command in Bash. The program will read the proc/ filesystem to gather real system data and the ncurses library to help display the data. By default, processes are sorted by CPU%, but the program also supports sorting by: 
* PID
* MEM
* TIME

using the --sort-key or -s flags. The program also offers a variable delay (default: 1000ms) that can be set with the --delay or -d flags. 
