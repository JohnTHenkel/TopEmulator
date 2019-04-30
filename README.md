NAME: John Henkel

FILES:
	README.MD: This file. Contains project information.
	.gitignore: Allows exclusion of files in git commits
	.gitmodules: Allows inclusion of google tests.
	makefile: Contains instructions on how to compile the binary
	proc.tar.bz2: Contains a snapshot of the proc filesystem.

	src/main.cpp: Contains functions related to displaying system data as well as parsing flags and sorting.

	src/info/cpu_info.cpp: Contains functions for reading into a CpuInfo struct from /proc/stat.
	src/info/cpu_info.h: Contains the CpuInfo struct and functions related to totaling the info.
	src/info/cpu_info_test.cpp: Contains functions to test that the CpuInfo is read correctly from proc.
	src/info/load_average_info.cpp: Contains functions for reading into a LoadAverageInfo struct from /proc/loadavg.
	src/info/load_average_info.h: Contains the LoadAverageInfo struct.
	src/info/load_average_info_tests.cpp: Contains functions to test that the LoadAverageInfo is read correctly from proc.
	src/info/memory_info.cpp: Contains functions for reading into a MemoryInfo struct from /proc/meminfo.
	src/info/memory_info.h: Contains the MemoryInfo struct.
	src/info/memory_info_tests.cpp: Contains functions to test that the MemoryInfo is read correctly from proc.
	src/info/process_info.cpp: Contains functions for reading into an individual ProcessInfo struct as well as getting all ProcessInfos.
	src/info/process_info.h: Contains the ProcessInfo struct and functions for determining thread information.
	src/info/process_info_tests.cpp: Contains functions to test that the ProcessInfo is read correctly from proc.
	src/info/system_info.cpp: Contains functions for reading data from the other structs and proc into a SystemInfo struct.
	src/info/system_info.h: Contains the SystemInfo struct.
	src/info/system_info_tests.cpp: Contains functions to test that the SystemInfo is read correctly from the various structs and proc.
	src/utils/README.md: Contains suggestions of utils to implement.
	src/utils/formatting.cpp: Contains functions to format various pieces of system information into a human readable format.
	src/utils/formatting.h Contains the Time struct which is used for displaying a variety of time values.
	src/utils/formatting_tests.cpp: Contains functions to test that all of the formatting functions are formatting data as expected.
		
UNUSUAL/INTERESTING FEATURS:
	The used memory calculation seems to result in odd values.
	Using Josh's post on piazza : @237

APPROXIMATE HOURS:
	Approximately 20 hours.

IDEAL TERMINAL SIZE:
	Resize to fit.

