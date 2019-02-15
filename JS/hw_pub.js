var zmq = require('zeromq')
var publisher = zmq.socket('pub')

publisher.bind('tcp://*:5563', function(err) {
  if(err)
    console.log(err)
  else
    console.log('Listening on 5563...')
})

setInterval(function() {
  //if you pass an array, send() uses SENDMORE flag automatically
  publisher.send(["sub 1", "Hello"]);
  //if you want, you can set it explicitly
  publisher.send("sub 2", zmq.ZMQ_SNDMORE);
  publisher.send("World");
},1000);