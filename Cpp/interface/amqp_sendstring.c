//
// exmaple usage : 
// on the cosumer side run 2 instances of the python script: consume.py
//   ./consume.py localhost dfm
//   ./consume.py localhost hello
// on the producer side run the following bash line 
// for i in dfm hello ; do ./producer 10.248.30.162 5672 "" "$i" "hello $i" ; done
//
//
//
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include "utils.h"

int main(int argc, char const *const *argv)
{
  char const *hostname;
  int port, status;
  char const *exchange;
  char const *routingkey;
  char const *messagebody;
  amqp_socket_t *socket = NULL;
  amqp_connection_state_t conn; 
  amqp_rpc_reply_t amqp_reply;

  if (argc < 6) {
    fprintf(stderr, "Usage: amqp_sendstring host port exchange routingkey messagebody\n");
    return 1;
  }

  hostname = argv[1];
  port = atoi(argv[2]);
  exchange = argv[3];
  routingkey = argv[4];
  messagebody = argv[5];


  // 1. create a socket and connection objects.
  conn = amqp_new_connection();

  socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    die("creating TCP socket");
  }


  // 2. connect to the broker
  status = amqp_socket_open(socket, hostname, port);
  if (status) {
    die("opening TCP socket");
  }

  // 3. login to the broker
  amqp_reply = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
  die_on_amqp_error(amqp_reply, "Logging in");


  // 4. open a channel to the broker
  amqp_channel_open(conn, 1);

  amqp_reply = amqp_get_rpc_reply(conn);
  die_on_amqp_error(amqp_reply, "Opening channel");

  // 5. send the string
  {
    amqp_basic_properties_t props;

    // _flag = AMQP_BASIC_CONTENT_TYPE_FLAG 
    //         AMQP_BASIC_DELIVERY_MODE_FLAG
    //         AMQP_BASIC_TIMESTAMP_FLAG
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | 
                   AMQP_BASIC_DELIVERY_MODE_FLAG;

    // content_type = amqp_cstring_bytes("text/json");
    props.content_type = amqp_cstring_bytes("text/plain");

    //  delivery_mode = 1 non persistent delivery mode
    //  delivery_mode = 2 persistent delivery mode 
    props.delivery_mode = 2; 

    die_on_error(amqp_basic_publish(conn,
                                    1,
                                    amqp_cstring_bytes(exchange),
                                    amqp_cstring_bytes(routingkey),
                                    0,
                                    0,
                                    &props,
                                    amqp_cstring_bytes(messagebody)),
                 "Publishing");
  }


  // 6. close channel, connection and free connection+socket.
  die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
  die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
  die_on_error(amqp_destroy_connection(conn), "Ending connection");
  return 0;
}
