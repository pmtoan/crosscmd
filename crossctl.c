/*
*   Cross commandline client control
*   Author:         Minh Toan (phamminhtoan304@gmail.com)
*   Dependencies:   no dependencies
*   Build:          gcc -std=gnu99 -o crossctl crossctl.c
*/

#include "lib/controller.h"

void print_help();

int main(int argc, char const *argv[])
{
	if (argc < 3 || !strstr(argv[1], "--hosts="))
	{
		/* Get list of host */
		print_help();
		exit(0);
	}

	char* hosts = string_split(argv[1], "=", 1)[1];
	controller_control_ctl(hosts, __DEF_PORT__, argv[2], argv[3]);

	return 0;
}

void print_help()
{
	printf("C2sync client control v1.0\n"
		"\nUsage\n"
		"\tc2synctl --hosts=host_list cmd option\n"
		"\nExample\n"
		"\tc2synctl --hosts=192.168.1.1,192.168.1.2,192.168.1.3 /bin/ls -lsah /\n"
		"\nOptions\n"
		"\t--hosts: list host ips seperated by ,\n"
	);
}