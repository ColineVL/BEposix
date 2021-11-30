/* Standard C Headers */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

/* Thread pool header file */

#include "threadpool.h"

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Mon serveur web</title>"
"<body bgcolor=lightgreen><h1>Hello from my own web server !</h1></body></html>\r\n";

/******************************************************************************/
/* processing the request                                                     */
/******************************************************************************/
void process_request ( /* to be completed  */  ) {

}

/******************************************************************************/
/* dispatching the requests                                                   */
/******************************************************************************/
void dispatch_requests ( /* to be completed  */ ) {
 
}

/******************************************************************************/
/* function main                                                              */
/******************************************************************************/

int main(int argc, char **argv) {
  
    printf ("\x1B[32m %s \x1B[0m%s", "[MAIN]", "Start processing\n");

    /*--------------------------------------------------------------------------*/
    /* Initialize a thread pool of size 10                                       */
    /*--------------------------------------------------------------------------*/
    pthread_pool_t *thread_pool = pthread_pool_init (10);  
    
     /* Leave some time for the threadpool to finish its initialization */
    sleep (1);


    /*--------------------------------------------------------------------------*/
    /* Initialize web server                                                    */
    /*--------------------------------------------------------------------------*/
  
    /*--------------------------------------------------------------------------*/
    /* Process incoming requests                                                */
    /*--------------------------------------------------------------------------*/
 
  return EXIT_SUCCESS;
}
