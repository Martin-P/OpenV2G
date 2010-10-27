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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define EVSE 1
#define PEV  2

static char *help_string =
"%s: Valid parameters are:\n"
"  -v    - print the program version and exit\n"
"  -d    - daemonize this process\n"
"  -m<x> - mode of application with x=1 EVSE or x=2 PEV\n"
"  -h    - help\n";

extern void run_evse(unsigned int port);
extern void run_pev(unsigned int port);


static void arg_error(char *name)
{
    fprintf(stderr, help_string, name);
    exit(1);
}


int main_network_1(int argc, char *argv[])
{
    int fd0, fd1, fd2;
    int i, pid;
    int daemonize = 0;
    int mode = -1;
    unsigned int port = 7259; /* TODO port is fix, should be configurable */

    /* check arguments */
    if(argc == 1)
        arg_error("too few parameters");
    for (i = 1; i < argc; i++) {
        if ((argv[i][0] != '-') || (strlen(argv[i]) > 3)) {
            fprintf(stderr, "Invalid argument: '%s'\n", argv[i]);
            arg_error(argv[0]);
        }
        switch (argv[i][1]) {

        case 'd':
            daemonize = 1;
            break;

        case 'm':
            mode = atoi(&argv[i][2]);
            if(mode != EVSE && mode != PEV) {
                fprintf(stderr, "Invalid option: '%s'\n", argv[i]);
                arg_error(argv[0]);
            }
            break;

        case 'h' :
            fprintf(stdout, help_string, argv[0]);
            exit(0);

        case 'v':
            printf("%s Example 1: 0.0.1\n", argv[0]);
            exit(0);

        default:
            fprintf(stderr, "Invalid option: '%s'\n", argv[i]);
            arg_error(argv[0]);
        }
    }

    if (daemonize) {
        if ((pid = fork()) > 0) {
            exit(0);
        } else if (pid < 0) {
            printf("Error forking first fork\n");
            exit(1);
        } else {
              /* setsid() is necessary if we really want to demonize */
              if(setsid() == -1)
                  printf("Error setsid()\n");
              /* Second fork to really deamonize me. */
              if ((pid = fork()) > 0) {
                  exit(0);
              } else if (pid < 0) {
                  printf("Error forking second fork\n");
                  exit(1);
              }
        }
        /*  change working directory to root so we won't prevent file systems
         *  from being unmounted.
         */
        if(chdir("/") < 0) {
            ;
        }
        /* Attach file descriptors 0, 1, and 2 to /dev/null */
        fd0 = open("/dev/null", O_RDWR);
        fd1 = dup(0);
        fd2 = dup(0);
    }else {
        printf("+++Start EVSE/PEV Example+++\n\n");
    }

    if (mode == EVSE) {
        printf("+++Start EVSE on port: %i+++\n\n", port);
        run_evse(port);

    }else if (mode == PEV) {
        printf("+++Start PEV to port: %i+++\n\n", port);
        run_pev(port);
    }

    printf("+++Terminate EV2SE Example+++\n\n");
    return 0;
}
