#ifdef __APPLE__
    #include "/Users/pde-rent/.brew/Cellar/zeromq/4.2.3/include/zhelpers.h"
#else
    #include "include/zhelpers.h"
#endif

#include <stdio.h>

int main (void)
{
    //  Prepare our context and subscriber
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    char *sub_id = "sub 1";
    zmq_connect (subscriber, "tcp://localhost:5563");
    zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, sub_id, strlen(sub_id));

    while (1) {
        //  Read envelope with address
        char *address = s_recv (subscriber);
        //  Read message contents
        char *contents = s_recv (subscriber);
        printf ("[%s] %s\n", address, contents);
        free (address);
        free (contents);
    }
    //  We never get here, but clean up anyhow
    free(sub_id);
    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}