import Graph from './Graph'

let labels = [];
var getId = e => { return labels.indexOf(e); }

let socket = io();
let items = document.getElementsByClassName("item");

// create graph
let g = new Graph();

// add listner of each item
for (let i = 0; i < items.length; i++) {
    items[i].addEventListener('touchstart', e => {

        e.preventDefault();
        e.currentTarget.classList.toggle('active');

        let t = e.currentTarget.id.split('-');
        let n = parseInt(t[0], 10);
        let b = e.currentTarget.classList.contains('active');
        let s = t[1];

        socket.emit('filter', {
            'event': s,
            'enabled': b
        });
        g.setVisible(n, b);

    }, true);

    let l = items[i].children[1].textContent.replace(/\s+/g, '');
    // default active
    items[i].id = i + '-' + l;
    items[i].classList.add('active');
    labels.push(l);
}

// handling new data from server
socket.on('new', e => { g.add(getId(e.event)); });

// disable scroll
document.ontouchmove = e => {
    e.preventDefault();
};
