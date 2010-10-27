/*
 * Copyright (C) 2010 INSYS Microelectronics GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author  mlauterbach
 * @version 0.0.1
 *
 ********************************************************************/
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

fd_set master_fd; /* master fd list */
fd_set read_fds;  /* tmp fd list for select() */
int fdmax;        /* maximum file descriptor number */
int listen_fd;    /* file descriptor for TCP-Server */
int pev_fd;       /* file descriptor to PEV */


static void close_server(void)
{
    if(listen_fd == -1)
        return;
    tcflush(listen_fd, TCIOFLUSH);
    FD_CLR(listen_fd, &master_fd);
    close(listen_fd);
    listen_fd = -1;

    return;
}


static void init_server(void)
{
    listen_fd = -1;
    pev_fd = -1;
    FD_ZERO(&master_fd);
    FD_ZERO(&read_fds);

    return;
}


static void cleanup_server(void)
{
    close_server();
    if(pev_fd != -1) {
        close(pev_fd);
        pev_fd = -1;
    }
    return;
}


static int start_server(unsigned int port)
{

    int yes = 1;
    struct addrinfo hints;
    struct addrinfo *ai;
    char str_port[10];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    sprintf(str_port, "%d", port);
    if ((getaddrinfo(NULL, str_port, &hints, &ai)) != 0) {
        printf("ERROR: Could not get address info for the TCP listener: %s\n", strerror(errno));
        return -1;
    }

    listen_fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol); /* create the socket */
    if (listen_fd < 0) {
        printf("ERROR: Creation of TCP listen socket failed: %s\n", strerror(errno));
        listen_fd = -1;
        return 1;
    }

    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));     /* just some options */
    if (bind(listen_fd, ai->ai_addr, ai->ai_addrlen) < 0) {                 /* now we bind it to the port */
        printf("ERROR: Binding TCP listen socket failed: %s\n", strerror(errno));
        close(listen_fd);
        listen_fd = -1;
        return -1;

    }
    freeaddrinfo(ai);

    if (listen(listen_fd, 10) == -1) {  /* and put the socket in listen-mode */
        printf("ERROR: Listening on TCP listen socket failed: %s\n", strerror(errno));
        close(listen_fd);
        listen_fd = -1;
        return -1;
    }

    FD_SET(listen_fd, &master_fd);
    if(listen_fd > fdmax)
        fdmax = listen_fd;

    printf("DEBUG: TCP-Server fd:%i\n", listen_fd);
    return listen_fd;
}


static int accept_connection(void)
{

    struct sockaddr_in remoteaddr;
    socklen_t addrlen = sizeof remoteaddr;

    pev_fd = accept(listen_fd, (struct sockaddr *) &remoteaddr, &addrlen);
    if (pev_fd == -1) {
        printf("ERROR: Could not accept on TCP listen socket: %s\n", strerror(errno));
        return -1;
    }

    FD_SET(pev_fd, &master_fd);
    if (pev_fd > fdmax) {
        fdmax = pev_fd;
    }

    printf("PEV arrived .................... ;-)\n");
    close_server();
    return pev_fd;
}


static int handle_tcp_data(void)
{
    ssize_t read_bytes;
    uint8_t buffer[512];

    read_bytes = read(pev_fd, buffer, sizeof(buffer)); /* get data from PEV */
    if(read_bytes < 1) {
        if(errno != EAGAIN) {
            if(errno == EBADF)
                printf("ERROR: Reading from TCP failed: connection is gone\n");
            else
                printf("ERROR: Reading from TCP failed: %d: %s\n", errno, strerror(errno));
            printf("INFO: PEV gone\n");
            close(pev_fd);
            return -1;
        }
    }
    printf("INFO: number of bytes from PEV: %i\n", read_bytes);

    /* TODO give data to DoIP/EXI Parser and send response to PEV, if a complete EXI msg. was received */

    return 0;
}


void run_evse(unsigned int port)
{
    int sel;
    struct timeval tv;

    init_server();

    listen_fd = start_server(port);
    if (listen_fd == -1) {
        printf("ERROR: open_server failed\n");
        return;
    }

    for (;;) {

        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        FD_ZERO(&read_fds);
        read_fds = master_fd;

        sel = select(fdmax + 1, &read_fds, NULL, NULL, &tv);
        if(sel > 0) {
            if (FD_ISSET(listen_fd, &read_fds))
                accept_connection();
            if (FD_ISSET(pev_fd, &read_fds))
                if(handle_tcp_data() == -1) { /* PEV gone */
                    break;
                }
        }else if (sel == -1) {
            break;
        }
    }

    cleanup_server();
    return;
}
