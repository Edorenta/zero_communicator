#ifdef __APPLE__
    #include "/Users/pde-rent/.brew/Cellar/zeromq/4.2.3/include/zhelpers.h"
#else
    #include "include/zhelpers.h"
#endif

#include <unistd.h>

int main (void)
{
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    char *sub_id[2] = {"sub 1", "sub 2"};
    zmq_bind (publisher, "tcp://*:5563");

    while (1) {
        //  Write two messages, each with an envelope and content
        s_sendmore (publisher, sub_id[0]);
        s_send (publisher, "Hello");
        s_sendmore (publisher, sub_id[1]);
        s_send (publisher, "World");
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    free(sub_id[0]);
    free(sub_id[1]);
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}