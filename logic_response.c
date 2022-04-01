#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic_response.h"

/* ____________________________________________________________________________
    char * gen_hello_cmd_resp()

    Function generates response (= basic web page content) to "hello" user command.

    Function returns:
    Pointer to char arr which represents content of basic web page.
   ____________________________________________________________________________
*/
char * gen_hello_cmd_resp(){
    char *hello_page_cont = malloc((strlen(SERVER_RESP_CMD_1) + 1) * sizeof(char));
    strcpy(hello_page_cont, SERVER_RESP_CMD_1);
    return hello_page_cont;
}

/* ____________________________________________________________________________
    char * gen_creator_cmd_resp()

    Function generates response (= basic web page content) to "creator" user command.

    Function returns:
    Pointer to char arr which represents content of basic web page.
   ____________________________________________________________________________
*/
char * gen_creator_cmd_resp(){
    char *creator_page_cont = malloc((strlen(SERVER_RESP_CMD_2) + 1) * sizeof(char));
    strcpy(creator_page_cont, SERVER_RESP_CMD_2);
    return creator_page_cont;
}

/* ____________________________________________________________________________
    char * gen_github_cmd_resp()

    Function generates response (= basic web page content) to "github" user command.

    Function returns:
    Pointer to char arr which represents content of basic web page.
   ____________________________________________________________________________
*/
char * gen_github_cmd_resp(){
    char *github_page_cont = malloc((strlen(SERVER_RESP_CMD_3) + 1) * sizeof(char));
    strcpy(github_page_cont, SERVER_RESP_CMD_3);
    return github_page_cont;
}

/* ____________________________________________________________________________
    char * gen_page_header(int cont_length)

    Function generates header of web page which should be passed to user.
    Ie. http response type, charset, etc.

    Function returns:
    Pointer to char arr which represents beginning of web page.
   ____________________________________________________________________________
*/
char * gen_page_header(int cont_length){
    char *page_header = NULL; /* complete page header which should be sent to user */
    int page_header_ptr_size = 0; /* actual size of data to which is pointed to by page_header pointer */
    char *int_to_str_buf = malloc(5 * sizeof(char)); /* buffer used for converting int to string */

    /* append beginning of response header */
    page_header = malloc((strlen(SERVER_RESP_HEADER_1) + 1) * sizeof(char));
    strcpy(page_header, SERVER_RESP_HEADER_1);
    page_header_ptr_size += (strlen(SERVER_RESP_HEADER_1) + 1) * sizeof(char);

    /* append content-length value */
    sprintf(int_to_str_buf, "%d", cont_length); /* convert int to string for append - to buffer */
    page_header = realloc(page_header, page_header_ptr_size + ((strlen(int_to_str_buf) + 1) * sizeof(char)));
    strcat(page_header, int_to_str_buf);
    page_header_ptr_size += (strlen(int_to_str_buf) + 1) * sizeof(char);
    free(int_to_str_buf); /* free conversion buffer */

    /* append rest of the response header */
    page_header = realloc(page_header, page_header_ptr_size + ((strlen(SERVER_RESP_HEADER_2) + 1) * sizeof(char)));
    strcat(page_header, SERVER_RESP_HEADER_2);
    page_header_ptr_size += (strlen(SERVER_RESP_HEADER_2) + 1) * sizeof(char);
    return page_header;
}

/* ____________________________________________________________________________
    char * gen_page_start()

    Function generates beginning of web page which should be passed to user.
    Ie. beginning html and head tags, etc.

    Function returns:
    Pointer to char arr which represents beginning of web page.
   ____________________________________________________________________________
*/
char * gen_page_start(){
    char *page_start = malloc((strlen(SERVER_RESP_START) + 1) * sizeof(char));
    strcpy(page_start, SERVER_RESP_START);
    return page_start;
}

/* ____________________________________________________________________________
    char * gen_page_end()

    Function generates end of web page which should be passed to user.
    Ie. ending body and html tags, etc.

    Function returns:
    Pointer to char arr which represents end of web page.
   ____________________________________________________________________________
*/
char * gen_page_end(){
    char *page_end = malloc((strlen(SERVER_RESP_END) + 1) * sizeof(char));
    strcpy(page_end, SERVER_RESP_END);
    return page_end;
}

/* ____________________________________________________________________________
    char * gen_error_resp()

    Function generates response (= basic web page content) when no valid cmd
    is encountered. Ie. error message.

    Function returns:
    Pointer to char arr which represents content of basic web page.
   ____________________________________________________________________________
*/
char * gen_error_resp(){
    char *error_page_cont = malloc((strlen(SERVER_RESP_ERR) + 1) * sizeof(char));
    strcpy(error_page_cont, SERVER_RESP_ERR);
    return error_page_cont;
}