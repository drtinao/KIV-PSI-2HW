#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <string.h>

#include "logic_server.h"
#include "logic_response.h"

int port_number = -1;

/* ____________________________________________________________________________
    int start_server()

    Function starts the main part of the server (listens for new connections etc.)

    Function returns:
    a) 0 - if everything went ok
    b) 1 - if something bad happened (cannot open socket, etc.)
   ____________________________________________________________________________
*/
int start_server(){
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int server_socket = 0;
    int client_socket = 0;
    int ret_value = 0;
    int len_addr = 0;
    pthread_t thread;

    /* create server socket - START */
    server_socket = socket(AF_INET, SOCK_STREAM, 0); /* TCP protocol used */
    if(server_socket < 0){
        printf(SERVER_SOCKET_CREATE_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_SOCKET_CREATE_OK);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    /* create server socket - END */

    /* bind server socket - START */
    if(bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        printf(SERVER_BINDING_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_BINDING_OK);
    }
    /* bind server socket - END */

    /* listen - START */
    ret_value = listen(server_socket, SERVER_MAX_CLIENT_NUM);
    if(ret_value < 0){
        printf(SERVER_LISTEN_ERROR);
        return EXIT_FAILURE;
    }else{
        printf(SERVER_LISTEN_OK);
    }
    /* listen - END */

    printf(SERVER_WAIT_CLIENT);
    while(1){
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &len_addr);
        printf(SERVER_ACCEPT_CON);

        if(pthread_create(&thread, NULL, client_handler_thread, (void *)&client_socket) != 0){
            printf(SERVER_THREAD_CREATE_ERROR);
            free(client_socket);
            continue;
        }else{
            printf(SERVER_THREAD_CREATE_OK);
        }
    }
}

/* ____________________________________________________________________________
    int try_port_assign(char *second_param)

    Function tries to convert char sequence entered by user as second parameter
    to int representing port number.

    Function returns:
    a) 0 - if user entered number as a port == 2
    b) 1 - if user entered invalid input != 2
   ____________________________________________________________________________
*/
int try_port_assign(char *second_param){
    int number_entered; /* will contain the numeric part of string which user entered */
    char* not_number_part; /* will contain the non-numeric part of string that user entered */
    number_entered = (int)strtol(second_param, &not_number_part, SERVER_PORT_NUM_BASE);
    if(*not_number_part) {
        return EXIT_FAILURE;
    }else{
        port_number = number_entered;
        printf(SERVER_LISTEN_PORT, port_number);
        return EXIT_SUCCESS;
    }
}

/* ____________________________________________________________________________
    void * client_handler_thread(void *arg)

    Function is started in new thread and handles new client connection.
    Ie. reads request from given client, writes response to socket and finally
    closes the connection.

    Function takes message from client browser and tries to parse
    get requests found in the request.

    Ie. according to GET request calls respective functions and finally builds
    a final response string which is sent to the client.
   ____________________________________________________________________________
*/
void * client_handler_thread(void *arg)
{
    char message_buffer[SERVER_MES_BUF_SIZE]; /* buffer for message received from client */
    int client_socket = *((int *)arg); /* get client socket from given args */
    int size_to_read = 0; /* size of message sent by client - check bef receive */

    while(1){
        ioctl(client_socket, FIONREAD, &size_to_read); /* check data size before read */
        if(size_to_read > 0 && size_to_read < SERVER_MES_BUF_SIZE){ /* got data to read which do not exceed message buffer size */
            read(client_socket, message_buffer, size_to_read);

            char *server_resp = NULL; /* complete response which should be sent to user */
            int server_resp_ptr_size = 0; /* actual size of data to which is pointed to by server_resp pointer */
            char *server_resp_temp = NULL; /* temp buffer used for swapping content of server_resp */
            int valid_cmd_count = 0; /* number of valid commands encountered within GET. Ie. starts with user_get= and continues with valid cmd */

            char *page_header = NULL; /* page header text */
            char *page_start = NULL; /* page head text */
            char *page_end = NULL; /* page end text </html> and so on */
            char *hello_cont = NULL; /* hello page text */
            char *creator_cont = NULL; /* creator page text */
            char *github_cont = NULL; /* github page text */
            char *error_cont = NULL; /* error page text */

            char *first_line = strtok(message_buffer, "\r\n"); /* get first line of client message - should contains GET */
            printf(SERVER_REC_MES_FIRST_LINE_FULL, first_line);
            if(strstr(SERVER_REC_MES_FIRST_LINE_CONT, SERVER_REC_MES_FIRST_LINE_CONT)){ /* first line contains GET, ok */
                printf(SERVER_REC_MES_FIRST_LINE_OK);
            }else{ /* no GET found on first line, error */
                printf(SERVER_REC_MES_FIRST_LINE_ERROR);
            }

            page_start = gen_page_start(); /* generate beginning of the page */
            server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(page_start) + 1) * sizeof(char));
            strcpy(server_resp, page_start);
            server_resp_ptr_size += (server_resp_ptr_size + strlen(page_start) + 1) * sizeof(char);
            free(page_start); /* free page start after copy */

            printf(SERVER_PARSE_REQ_START); /* parse indiv requests contained within GET - START */
            char *user_get = strtok(first_line, "? ");
            while(user_get){
                if(strstr(user_get, SERVER_PARSE_INDIV_GET_CONT)){ /* command contains user_get=, ok */
                    printf(SERVER_PARSE_INDIV_MES_START);
                    printf(SERVER_PARSE_INDIV_MES_TEXT, user_get);
                    printf(SERVER_PARSE_INDIV_GET_OK);
                    user_get += strlen(SERVER_PARSE_INDIV_GET_CONT); /* get command given after user_get= */
                    if(strstr(user_get, SERVER_VALID_CMD_1)){ /* valid command - hello world */
                        valid_cmd_count += 1;
                        hello_cont = gen_hello_cmd_resp();
                        server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(hello_cont) + 1) * sizeof(char));
                        strcat(server_resp, hello_cont);
                        server_resp_ptr_size += (strlen(hello_cont) + 1) * sizeof(char);
                        free(hello_cont); /* free hello page after cat */
                    }

                    if(strstr(user_get, SERVER_VALID_CMD_2)){ /* valid command - about creator */
                        valid_cmd_count += 1;
                        creator_cont = gen_creator_cmd_resp();
                        server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(creator_cont) + 1) * sizeof(char));
                        strcat(server_resp, creator_cont);
                        server_resp_ptr_size += (strlen(creator_cont) + 1) * sizeof(char);
                        free(creator_cont); /* free creator page after cat */
                    }

                    if(strstr(user_get, SERVER_VALID_CMD_3)){ /* valid command - github list */
                        valid_cmd_count += 1;
                        github_cont = gen_github_cmd_resp();
                        server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(github_cont) + 1) * sizeof(char));
                        strcat(server_resp, github_cont);
                        server_resp_ptr_size += (strlen(github_cont) + 1) * sizeof(char);
                        free(github_cont); /* free github page after cat */
                    }
                    printf(SERVER_PARSE_INDIV_MES_END);
                }
                user_get = strtok(NULL, "? ");
            }

            if(valid_cmd_count == 0){ /* no valid command detected, send error page */
                error_cont = gen_error_resp();
                server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(error_cont) + 1) * sizeof(char));
                strcat(server_resp, error_cont);
                server_resp_ptr_size += (strlen(error_cont) + 1) * sizeof(char);
                free(error_cont); /* free error page after cat */
            }
            printf(SERVER_PARSE_REQ_END); /* parse indiv requests contained within GET - END */

            page_end = gen_page_end(); /* generate page end */
            server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(page_end) + 1) * sizeof(char));
            strcat(server_resp, page_end);
            server_resp_ptr_size += (strlen(page_end) + 1) * sizeof(char);
            free(page_end); /* free page end after cat */

            /* copy content of server_resp to temp buffer, then put page_header into server_resp and append original content of server_resp */
            server_resp_temp = malloc((strlen(server_resp) + 1) * sizeof(char));
            strcpy(server_resp_temp, server_resp);

            page_header = gen_page_header(strlen(server_resp)); /* generate page header - needs to be generated at the end to know content-length */
            server_resp = realloc(server_resp, (server_resp_ptr_size + strlen(page_header) + 1) * sizeof(char));
            strcpy(server_resp, page_header);
            server_resp_ptr_size += (strlen(page_header) + 1) * sizeof(char);
            free(page_header); /* free page header after copy */
            strcat(server_resp, server_resp_temp);
            free(server_resp_temp); /* free temporary space */

            write(client_socket, server_resp, strlen(server_resp));
            free(server_resp);
            printf(SERVER_CLOSED_CON);
            pthread_exit(0);
        }
    }
}