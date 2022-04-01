#ifndef TCP_SERVER_MULTITHREAD_LOGIC_RESPONSE_H
#define TCP_SERVER_MULTITHREAD_LOGIC_RESPONSE_H

#define SERVER_RESP_HEADER_1 "HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: "
#define SERVER_RESP_HEADER_2 "\r\nAccept-Ranges: bytes\r\nConnection: close\r\n\r\n"
#define SERVER_RESP_START "<html><head><title>KIV/PSI server</title></head><body>"
#define SERVER_RESP_CMD_1 "<hr><h1>hello content</h1><p>This is content of hello page. So I am just here to say hello!</p><hr>"
#define SERVER_RESP_CMD_2 "<hr><h1>creator content</h1><p>This is content of creator page. Creator of this server is Ondrej Drtina, all rights reserved.</p><hr>"
#define SERVER_RESP_CMD_3 "<hr><h1>github content</h1><p>This is content of github page. Feel free to visit my github at <a href=\"https://github.com/drtinao\">https://github.com/drtinao</a></p><hr>"
#define SERVER_RESP_ERR "<h1>error page</h1>"
#define SERVER_RESP_END "</body></html>\r\n"

/* ____________________________________________________________________________

    Function prototypes
   ____________________________________________________________________________
*/
char * gen_page_header(int cont_length);
char * gen_page_start();
char * gen_hello_cmd_resp();
char * gen_creator_cmd_resp();
char * gen_github_cmd_resp();
char * gen_error_resp();
char * gen_page_end();

#endif //TCP_SERVER_MULTITHREAD_LOGIC_RESPONSE_H
