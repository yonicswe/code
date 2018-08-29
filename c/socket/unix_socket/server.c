/**************************************************************************/
/* This example program provides code for a server application that uses     */
/* AF_UNIX address family                                                 */
/**************************************************************************/

/**************************************************************************/
/* Header files needed for this sample program                            */
/**************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

/**************************************************************************/
/* Constants used by this program                                         */
/**************************************************************************/
#define SERVER_PATH     "/tmp/server"
#define BUFFER_LENGTH    250
#define FALSE              0
#define TRUE               1

void
termination_handler (int signum)
{
   printf("server : signal handler %d\n", signum);
   unlink(SERVER_PATH);

}
     

void server_signal_register(void)
{
   struct sigaction new_action;
   struct sigaction old_action;

   // Set up the structure to specify the new action.
   new_action.sa_handler = termination_handler;
   sigemptyset (&new_action.sa_mask);
   new_action.sa_flags = 0;


   // find out if SIGINT is not ignored.
   sigaction (SIGINT, NULL, &old_action);

   if (old_action.sa_handler != SIG_IGN)
   {
      // SIGINT is not ignored lets register a handler for it.
      sigaction (SIGINT, &new_action, NULL);
   }

   // find out if SIGHUP is not ignored.
   sigaction (SIGHUP, NULL, &old_action);

   if (old_action.sa_handler != SIG_IGN)
   {
      // SIGHUP is not ignored lets register a handler for it.  
      sigaction (SIGHUP, &new_action, NULL);
   }

   // find out if SIGTERM is not ignored.
   sigaction (SIGTERM, NULL, &old_action);

   if (old_action.sa_handler != SIG_IGN)
   {
      // SIGTERM is not ignored lets register a handler for it.  
      sigaction (SIGTERM, &new_action, NULL);
   }
}


void main()
{
   /***********************************************************************/
   /* Variable and structure definitions.                                 */
   /***********************************************************************/
   int    sd=-1, sd2=-1;
   int    rc, length;
   char   buffer[BUFFER_LENGTH];
   struct sockaddr_un serveraddr;


   server_signal_register();

   /***********************************************************************/
   /* A do/while(FALSE) loop is used to make error cleanup easier.  The   */
   /* close() of each of the socket descriptors is only done once at the  */
   /* very end of the program.                                            */
   /***********************************************************************/

      /********************************************************************/
      /* The socket() function returns a socket descriptor, which represents   */
      /* an endpoint.  The statement also identifies that the UNIX        */
      /* address family with the stream transport (SOCK_STREAM) will be   */
      /* used for this socket.                                            */
      /********************************************************************/
      sd = socket(AF_UNIX, SOCK_STREAM, 0);
      if (sd < 0)
      {
         perror("socket() failed");
         goto exit_server;
      }

      /********************************************************************/
      /* After the socket descriptor is created, a bind() function gets a */
      /* unique name for the socket.                                      */
      /********************************************************************/
      memset(&serveraddr, 0, sizeof(serveraddr));
      serveraddr.sun_family = AF_UNIX;
      strcpy(serveraddr.sun_path, SERVER_PATH);

      rc = bind(sd, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr));
      if (rc < 0)
      {
         perror("bind() failed");
         goto exit_server;
      }

      /********************************************************************/
      /* The listen() function allows the server to accept incoming       */
      /* client connections.  In this example, the backlog is set to 10.  */
      /* This means that the system will queue 10 incoming connection     */
      /* requests before the system starts rejecting the incoming         */
      /* requests.                                                        */
      /********************************************************************/
      printf("server : setting socket to listen\n");
      rc = listen(sd, 10);
      if (rc< 0)
      {
         perror("listen() failed");
         goto exit_server;
      }


      /********************************************************************/
      /* The server uses the accept() function to accept an incoming      */
      /* connection request.  The accept() call will block indefinitely   */
      /* waiting for the incoming connection to arrive.                   */
      /********************************************************************/
   do 
   {
      sd2 = accept(sd, NULL, NULL);
      if (sd2 < 0)
      {
         perror("accept() failed");
         break;
      }

      printf("server : accepted connection: %d\n", sd2);

      /********************************************************************/
      /* In this example we know that the client will send 250 bytes of   */
      /* data over.  Knowing this, we can use the SO_RCVLOWAT socket      */
      /* option and specify that we don't want our recv() to wake up      */
      /* until all 250 bytes of data have arrived.                        */
      /********************************************************************/
      length = BUFFER_LENGTH;
      rc = setsockopt(sd2, SOL_SOCKET, SO_RCVLOWAT,
                                          (char *)&length, sizeof(length));
      if (rc < 0)
      {
         perror("setsockopt(SO_RCVLOWAT) failed");
         goto exit_server;
      }
      /****************************************************/
      /* Receive that 250 bytes data from the client */
      /****************************************************/
      rc = recv(sd2, buffer, sizeof(buffer), 0);
      if (rc < 0)
      {
         perror("recv() failed");
         break;
      } 
//       printf("server : %d bytes of data were received\n", rc);
      if (rc == 0 ||
          rc < sizeof(buffer))
      {
         printf("server : The client closed the connection before all of the\n");
         printf("server : ata was sent\n");
         break;
      }

      /********************************************************************/
      /* Echo the data back to the client                                 */
      /********************************************************************/
      rc = send(sd2, buffer, sizeof(buffer), 0);
      if (rc < 0)
      {
         perror("server : send() failed");
         break;
      }

      /********************************************************************/
      /* Program complete                                                 */
      /********************************************************************/

   } while (TRUE); //(FALSE);

exit_server:
   /***********************************************************************/
   /* Close down any open socket descriptors                              */
   /***********************************************************************/
   if (sd != -1)
      close(sd);

   if (sd2 != -1)
      close(sd2);

    /***********************************************************************/
   /* Remove the UNIX path name from the file system                      */
   /***********************************************************************/
   unlink(SERVER_PATH);
}
