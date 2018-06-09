import ApiHandler from './ApiHandler'
import Server from './Server'

let s = new Server();
let a = new ApiHandler(s.server);
a.init();
