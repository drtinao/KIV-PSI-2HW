#ifndef TCP_SERVER_MULTITHREAD_LOGIC_SERVER_H
#define TCP_SERVER_MULTITHREAD_LOGIC_SERVER_H

#define SERVER_SOCKET_CREATE_ERROR "Error while creating server socket, exiting!\n"
#define SERVER_SOCKET_CREATE_OK "Socket created OK!\n"
#define SERVER_BINDING_ERROR "Error while binding socket!\n"
#define SERVER_BINDING_OK "Binding OK!\n"
#define SERVER_LISTEN_ERROR "Error while trying to listen!\n"
#define SERVER_LISTEN_OK "Listening OK!\n"
#define SERVER_THREAD_CREATE_OK "Creating thread for new client OK!\n"
#define SERVER_THREAD_CREATE_ERROR "Error while creating thread for new client!\n"
#define SERVER_WAIT_CLIENT "Ready for client connection!\n"
#define SERVER_ACCEPT_CON "New client connection accepted!\n"
#define SERVER_CLOSED_CON "Closing thread, client disconnected!\n"
#define SERVER_MAX_CLIENT_NUM 50
#define SERVER_MES_BUF_SIZE 1000

#define SERVER_REC_MES_FIRST_LINE_CONT  "GET"
#define SERVER_REC_MES_FIRST_LINE_FULL "Received first line of client request: %s\n"
#define SERVER_REC_MES_FIRST_LINE_OK "First line of request contains GET request, OK!\n"
#define SERVER_REC_MES_FIRST_LINE_ERROR "Error while finding GET request in first line of request!\n"
#define SERVER_PARSE_REQ_START "Parsing individual user_get requests - START\n"
#define SERVER_PARSE_INDIV_MES_START "Parsing command - START\n"
#define SERVER_PARSE_INDIV_MES_TEXT "Parsing command: %s\n"
#define SERVER_PARSE_INDIV_MES_END "Parsing command - END\n"
#define SERVER_PARSE_INDIV_GET_OK "Command contains user_get=, continue, OK!\n"
#define SERVER_PARSE_INDIV_GET_CONT "user_get="
#define SERVER_PARSE_REQ_END "Parsing individual user_get requests - END\n"

#define SERVER_VALID_CMD_1 "hello"
#define SERVER_VALID_CMD_2 "creator"
#define SERVER_VALID_CMD_3 "github"

#define SERVER_PORT_NUM_BASE 10
#define SERVER_LISTEN_PORT "Listening on port no.: %d\n"

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
int start_server();
int try_port_assign(char *second_param);
void * client_handler_thread(void *arg);

#endif //TCP_SERVER_MULTITHREAD_LOGIC_SERVER_H
