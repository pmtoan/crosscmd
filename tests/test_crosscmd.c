#include <stdio.h>
#include <stdlib.h>
#include "../lib/crosscmd.h"


int main(int argc, char const *argv[])
{
	system(cmd_req_parse(cmd_req_compose("toantoan", "/bin/ls", "-l")).command_line);
	return 0;
}