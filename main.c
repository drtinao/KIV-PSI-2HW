#include <stdio.h>

#include "logic_server.h"

#define MAIN_WRONG_PARAM_COUNT "EXITING - WRONG PARAMETERS COUNT... PLEASE ENTER PORT NUMBER."
#define MAIN_INVALID_PORT "Invalid port number entered!"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int check_args_count(int argc, char *argv[]);

int main(int argc, char *argv[]){
    /* perform check for parameters count */
    if(check_args_count(argc, argv) != EXIT_SUCCESS){
        printf(MAIN_WRONG_PARAM_COUNT);
        return EXIT_FAILURE;
    }else{ /* parameter count ok, port number should be present */
        if(try_port_assign(argv[1]) != EXIT_SUCCESS){ /* is number entered? */
            printf(MAIN_INVALID_PORT);
            return EXIT_FAILURE;
        }
    }

    start_server();

    return EXIT_SUCCESS;
}

/* ____________________________________________________________________________
    int check_args_count(int argc, char *argv[])

    Function checks the number of parameters given to the program.
    Two arguments expected (= user given name of port).

    Function returns:
    a) 0 - if number of parameters == 2
    b) 1 - if number of parameters != 2
   ____________________________________________________________________________
*/
int check_args_count(int argc, char *argv[]) {
    if(argc == 2) {
        return EXIT_SUCCESS;
    }else {
        return EXIT_FAILURE;
    }
}

