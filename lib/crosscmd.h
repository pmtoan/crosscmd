#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "../modules/unix_x86_64_linux_tcp_socket.h"
#include "../modules/utils_time.h"
#include "../modules/utils_file.h"
#include "../modules/utils_string.h"
#include "../modules/crypto.h"

#define __DEF_PORT__	45678
#define __DEF_KEY__		"gthare!@"

#define __DEF_KEY_LEN__			8
#define __DEF_CMD_LEN__			512
#define __DEF_OPTION_LEN__		1024
#define __DEF_MAX_MSG_LEN__		1545

/*
*	COMMAND_SYNC_REQUEST format message
*	[8 bytes] 	[max 512 bytes] 	[max 1024 bytes]
*	   key 		 cmd   				 	option
*	max len = 1024 + 512 + 8 + NULL = 1545 bytes
*/

typedef struct COMMAND_SYNC_REQUEST
{
	char* key;	// key use for security, 8 bytes
	char* command;	// command only, should use full path
	char* option;	// command option
	char* command_line;	// full command with option
}CMD_REQ;

/*************************************************/
CMD_REQ cmd_req_init();
void cmd_req_free(CMD_REQ* req);
CMD_REQ cmd_req_parse(const char* msg);
void cmd_req_print(CMD_REQ req);
char* cmd_req_compose(const char* key, const char* cmd, const char* opt);
/*************************************************/

CMD_REQ cmd_req_init()
{
	/*
	*	@todo: initialize and allocate memory for CNMD_REQ structure
	*	@return: A CMD_REQ structure initialized
	*/
	CMD_REQ req;
	req.key = (char*)malloc(__DEF_KEY_LEN__ + 1);
	req.command = (char*)malloc(__DEF_CMD_LEN__ + 1);
	req.option = (char*)malloc(__DEF_OPTION_LEN__ + 1);
	req.command_line = (char*)malloc(__DEF_CMD_LEN__ + __DEF_OPTION_LEN__ + 1/* */ + 1/*\0*/);;
	return req;
}

void cmd_req_free(CMD_REQ* req)
{
	if (req->key != NULL) free(req->key);
	if (req->command != NULL) free(req->command);
	if (req->option != NULL) free(req->option);
	if (req->command_line != NULL) free(req->command_line);
}

void cmd_req_print(CMD_REQ req)
{
	printf("Key:      %s\n", req.key);
	printf("Cmd:      %s\n", req.command);
	printf("Options:  %s\n", req.option);
	printf("Cmd_line: %s\n", req.command_line);
}

CMD_REQ cmd_req_parse(const char* msg)
{
	CMD_REQ req = cmd_req_init();
	int i;
	int j = 0;
	/* Parse key */
	for (i = 0; i < __DEF_KEY_LEN__; i++)
		req.key[i] = msg[i];
	req.key[i] = 0;

	/* Parse command */
	for (i; i < __DEF_CMD_LEN__ + __DEF_KEY_LEN__; i++)
	{
		req.command[j] = msg[i];
		j++;
	}
	req.command[j] = 0;
	j = 0;

	/* Parse command options */
	for (i; i < __DEF_MAX_MSG_LEN__; i++)
	{
		req.option[j] = msg[i];
		j++;
	}
	req.option[j] = 0;

	/* Compose full command to executed */
	sprintf(req.command_line, "%s %s", req.command, req.option);

	return req;
}

char* cmd_req_compose(const char* key, const char* cmd, const char* opt)
{
	char* req = (char*)malloc(__DEF_MAX_MSG_LEN__);
	sprintf(req, "%8s%-512s%-1024s", key, cmd, opt);
	return req;
}
