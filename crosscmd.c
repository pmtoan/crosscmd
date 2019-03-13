/*
*   Cross commandline server daemon
*   Author:         Minh Toan (phamminhtoan304@gmail.com)
*   Dependencies:   no dependencies
*   Build:          gcc -std=gnu99 -o crosscmd croscmd.c
*/

#include "lib/controller.h"

/* This function handle signal (Ctrl+C) from keyboard */
void signal_handler(int sig);

/* Global variable: server socket and process's pid */
int server;
pid_t pid_first;
pid_t pid_second;

int main(int argc, char const *argv[])
{
    /* Set a signal, program exit when press Ctrl+C */
	signal(SIGINT,signal_handler);

    /* Open listener and bind to socket
    * __DEF_PORT__ defined in lib/crosscmd.h*/
    server = unix_x86_64_linux_tcp_socket_open_listener(__DEF_PORT__);
    _("%s - [INFO] Crosscmd server running on 0::%d\n", time_get_timestamp(), __DEF_PORT__);

    /* Prepare for client connection information storage */
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect;
    char* message = (char*)malloc(__SIZE_EXTRA__);
    while(1)
    {
        /* Connect with client and get information */
        connect = accept(server,(struct sockaddr *)&client_addr,&address_size);
        struct sockaddr_in *coming = (struct sockaddr_in *)&client_addr;
        unsigned char *ip = (unsigned char *)&coming->sin_addr.s_addr;
        unsigned short port = coming->sin_port;

        if (connect < 0)
        {
            /* Can't accept connection from client */
            _("%s - [ERROR] Can't connect with %d.%d.%d.%d:%d\n",
                time_get_timestamp(),
                ip[0], ip[1], ip[2], ip[3], port);
            continue;
        }
        /* Connected with client */
        _("%s - [INFO] Connected with %d.%d.%d.%d:%-6d\n",
            time_get_timestamp(),
            ip[0], ip[1], ip[2], ip[3], port);

        pid_first = fork(); // for first child process
        if (pid_first == 0)
        {
            /* In first child process, call fork again and exit immediately */
            signal(SIGINT, SIG_DFL); // clear signal
            pid_second = fork(); // fork second child process
            if (pid_second == 0)
            {
                /* In second child process, handle request from client */
            	signal(SIGINT, SIG_DFL); // clear signal
            	unix_x86_64_linux_tcp_socket_read_msg(connect, message, __DEF_MAX_MSG_LEN__);
                message = crypto_decrypt(message, 11); // modules/crypto.h
            	unix_x86_64_linux_tcp_socket_send_msg(connect, crypto_encrypt(controller_control(message), 11));
            	close(connect); // close connection
            }
            /* Close connection and exit */
            close(connect);
            exit(0);
        }
        /* Wait for first child process, this time is trivial*/
        wait(NULL);
        close(connect);
    }
}

void signal_handler(int sig)
{
    _("\n%s - [INFO] Crosscmd server exit\n", time_get_timestamp());
    close(server);
    exit(0);
}
