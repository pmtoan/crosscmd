#ifndef __C2SYNC_CONTROLLER_H__
#define __C2SYNC_CONTROLLER_H__

#include "crosscmd.h"

#define __DEF_LOG_PATH__	"/var/log/c2sync.log"

char* controller_control(const char* msg)
{
	CMD_REQ req = cmd_req_parse(msg);
	if (strcmp(req.key, __DEF_KEY__) != 0)
		return "unauthorized";
	system(req.command_line);
	return "executed";
}

void controller_control_ctl(
	const char* host,
	int port,
	const char* cmd,
	const char* opt)
{
	int num_host = string_count_cha(host, ',') + 1;
	char** hosts = string_split(host, ",", num_host - 1);
	for (int i = 0; i < num_host; ++i)
	{
		int sd = unix_x86_64_linux_tcp_socket_connect(hosts[i], port);
		char* msg = cmd_req_compose(__DEF_KEY__, cmd, opt);
		unix_x86_64_linux_tcp_socket_send_msg(sd, crypto_encrypt(msg, 11));
		sprintf(msg, "failed");
		unix_x86_64_linux_tcp_socket_read_msg(sd, msg, __SIZE_SMALL__);
		printf(
			"%s - %s:%d %s %s -> %s\n",
			time_get_timestamp(), hosts[i], port, cmd, opt,
			crypto_decrypt(msg, 11)
		);
		close(sd);
	}
}

#endif	// __C2SYNC_CONTROLLER_H__
