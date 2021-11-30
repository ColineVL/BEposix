/*****************************************************************************/
/* web_client.c                                                              */
/*                                                                           */
/* This program shows what the HTTP server sends to the client.  First,      */
/* it opens a TCP socket to the server.  Then, it sends the request          */
/* "GET <resource> HTTP/1.0\n\n" (the second newline is needed for the       */
/* "message-end" message.  Lastly it prints out the reply.                   */
/*                                                                           */
/* Example: ./web_client 127.0.0.1 1234                                      */
/*                                                                           */
/*****************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
//#include <resolv.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "utils.h"

#define MAXBUF  1024
#define PANIC(msg)  {perror(msg); abort();}

int main(int argc, char *argvs[])
{
  int sockfd, bytes_read;
  struct sockaddr_in dest;
  char buffer[MAXBUF];

  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    return -1;

  /*---Initialize server address/port struct---*/
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(1234); /*default HTTP Server port */
  dest.sin_addr.s_addr = inet_addr(argvs[1]);

  /*---Connect to server---*/
  CHECK_NZ ( connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) )

  sprintf(buffer, "GET %s HTTP/1.0\n\n", argvs[2]);
  send(sockfd, buffer, strlen(buffer), 0);

  /*---While there's data, read and print it---*/
  do
    {
      bzero(buffer, sizeof(buffer));
      bytes_read = recv(sockfd, buffer, sizeof(buffer), 0);
      if ( bytes_read > 0 )
        printf("%s", buffer);
    }
  while ( bytes_read > 0 );

  /*---Clean up---*/
  close(sockfd);

  return 0;
}
