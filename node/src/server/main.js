import ApiHandler from './ApiHandler'
import Server from './Server'
import socketIo from 'socket.io'
import osc from 'osc'

let udpPort_oF = new osc.UDPPort({
    localAddress: '0.0.0.0',
    localPort: 7401,
    metadata: true
});
udpPort_oF.open();

let s = new Server();

let io = socketIo.listen(s.server);

let a = new ApiHandler(udpPort_oF, io);
a.init();

io.sockets.on('connection', socket => {
    console.log('a user connected');

    socket.on('filter', msg => {
        console.log(msg.event, msg.enabled?'on':'off');
        let args = [
            { type: 's', value: msg.event },
            { type: 'i', value: msg.enabled?1:0 }
        ];

        udpPort_oF.send({
            address: '/filter',
            args: args
        }, '127.0.0.1', 7402);
    });

    socket.on('disconnect', () => {
        console.log('user disconnected');
    });
});
