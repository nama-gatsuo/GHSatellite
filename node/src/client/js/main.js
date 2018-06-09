import Graph from './Graph'

var getId = e => {
    let index = 0;
    //TODO: 'other' handling
    if (e === 'Push') index = 0;
    else if (e === 'Create') index = 1;
    else if (e === 'Issues') index = 2;
    else if (e === 'IssueComment') index = 3;
    else if (e === 'PullRequest') index = 4;
    else if (e === 'PullRequestReviewComment') index = 5;
    else if (e === 'Watch') index = 6;
    else if (e === 'Delete') index = 7;
    else if (e === 'Fork') index = 8;

    return index;
}


let socket = io();
let items = document.getElementsByClassName("item");

// create graph
let g = new Graph();

// add listner of each item
for (let i = 0; i < items.length; i++) {
    items[i].addEventListener('touchstart', e => {
        e.preventDefault();
        e.currentTarget.classList.toggle('active');

        let t = e.currentTarget.children[1].textContent.replace(/\s+/g, '');
        let b = e.currentTarget.classList.contains('active');

        socket.emit('filter', {
            'event': t,
            'enabled': b
        });
        g.setVisible(getId(t), b);

    }, true);

    // default active
    items[i].classList.add('active');
}

// handling new data from server
socket.on('new', e => { g.add(getId(e.event)); });

// disable scroll
document.ontouchmove = e => {
    e.preventDefault();
};
