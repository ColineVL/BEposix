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

pthread_pool_t *thread_pool;

int one = 1;

struct socket_parameters
{
  int client_fd;
  struct sockaddr_in svr_addr, from;
  socklen_t sin_len;
  int sock;
  int port;
};

struct socket_parameters parameters;

char response[] = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                  "<!DOCTYPE html><html><head><title>Mon serveur web</title>"
                  "<body bgcolor=lightgreen><h1>Hello from my own web server !</h1></body></html>\r\n";

char response2[] = "1";

/******************************************************************************/
/* leader function processes the request                                                     */
/******************************************************************************/
void process_request(void *requete)
{
  int *client_fd = (int *)requete;
  int bufsize = 1024;
  char *buffer = malloc(bufsize);

  if (*client_fd == -1)
    perror("accept");

  recv(*client_fd, buffer, bufsize, 0);
  printf("%s\n", buffer);
  send(*client_fd, response, sizeof(response), 0);
  close(*client_fd);
  free(buffer);
}

void leader_process(pthread_pool_t *thread_pool)
{
  // quand je recupere une request
  parameters.client_fd = accept(parameters.sock, (struct sockaddr *)&parameters.from, &parameters.sin_len);
  // je nomme un follower leader
  pthread_pool_exec(thread_pool, leader_process, thread_pool);
  // je me casse pour deal with my request
  process_request((void *)&parameters.client_fd);
}

/******************************************************************************/
int main(int argc, char **argv)
{

  printf("\x1B[32m %s \x1B[0m%s", "[MAIN]", "Start processing\n");

  /*--------------------------------------------------------------------------*/
  /* Initialize a thraed pool of size 10                                       */
  /*--------------------------------------------------------------------------*/
  thread_pool = pthread_pool_init(10);

  parameters.sin_len = sizeof(parameters.from);
  parameters.sock = socket(AF_INET, SOCK_STREAM, 0);
  if (parameters.sock < 0)
    perror("socket");

  setsockopt(parameters.sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

  parameters.port = 1234;
  parameters.svr_addr.sin_family = AF_INET;
  parameters.svr_addr.sin_addr.s_addr = INADDR_ANY;
  parameters.svr_addr.sin_port = htons(parameters.port);

  /* Leave some time for the threadpool to finish its initialization */
  sleep(1);

  /*--------------------------------------------------------------------------*/
  /* Initialize web server                                                    */
  /*--------------------------------------------------------------------------*/

  if (bind(parameters.sock, (struct sockaddr *)&parameters.svr_addr, sizeof(parameters.svr_addr)) == -1)
  {
    close(parameters.sock);
    perror("bind");
  }

  listen(parameters.sock, 5);

  /*--------------------------------------------------------------------------*/
  /* Start leader thread                                                      */
  /*--------------------------------------------------------------------------*/
  pthread_pool_exec(thread_pool, leader_process, thread_pool);

  while (1)
  {
  }

  return EXIT_SUCCESS;
}
