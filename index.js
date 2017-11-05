const net = require('net');
var addon = require('bindings')('PalAuth');
var crypto = require('crypto');

const client = new net.Socket();

const email = "";
const password = "";


client.connect(12345, "52.212.10.84", function(){
    console.log("connected");
    console.log();
    client.write(`LOGON\r\noperator: Server\r\napp-type: b\0t\r\ncapabilities: 4\r\nname: `+email+`\r\nprotocol-version: 2.4\r\n\r\n`);
});
let i = 0;

client.on('data', (data) => {
    console.log('Received: ' + data);
    console.log();

    if (i === 0) { // send auth
        const passwordBuffer = Buffer.from(password);
        const out = Buffer.alloc(32);
        authMsg = addon.authenticate(data, passwordBuffer, password.length, out);

        let authPacket = Buffer.from("AUTH\r\nEncryption-Type: 1\r\nOnline-Status: 1\r\nLast: 1\r\nContent-Length: 32\r\n\r\n");
        client.write(authPacket);
        client.write(out);
        i++;
    }
})