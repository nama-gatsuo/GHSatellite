import https from 'https'
import fetch from 'node-fetch'

export default class ApiHandler {
    constructor(udpPort, socketIo){

        const item_num = 50;

        this.url = 'https://api.github.com/events';
        /* use own token */
        this.url += '?access_token=2bd8ac40da75af79216f63ca3a2f86f4cd85416b';
        this.url += '&per_page=' + item_num;

        this.cache = [];
        this.cache_size = 100;

        this.queue = [];

        this.que_interval = 100;
        this.req_interval = 1000;

        this.udpPort = udpPort;
        this.io = socketIo;

        this.filterTarget = {
            'Push': false,
            'Create': false,
            'Issues': false,
            'IssueComment': false,
            'PullRequest': false,
            'PullRequestReviewComment': false,
            'Watch': false,
            'Delete': false,
            'Fork': false
        };
    }

    init() {
        setInterval(() => { this.req(this.url); }, this.req_interval);
        setTimeout(() => { this.dequeue(); }, 2000);
        console.log('running...');
        console.log('Stop: ctrl + c')
    }

    setFilter(e, isActive) {
        this.filterTarget[e] = isActive;
    }

    async req(url) {
        try {
            const r = await fetch(url);
            const json = await r.json();

            let data_new = [];
            let cnt_new = 0;

            for (let i = 0; i < json.length; i++) {

                let id = json[i].id;
                let ci = this.cache.indexOf(id);
                if (ci < 0) {
                    cnt_new++;
                    this.cache.push(id);

                    let d = {};
                    d.id = json[i].id;
                    let s = json[i].type;
                    d.event = s.substr(0, s.length-5);
                    d.actor = json[i].actor.login;
                    d.img = json[i].actor.avatar_url;
                    d.repo = json[i].repo.name;
                    d.date = json[i].created_at;

                    data_new.push(d);

                }

            }

            if (this.cache.length > this.cache_size) {
                this.cache = this.cache.slice(this.cache.length - this.cache_size, this.cache.length);
            }

            this.que_interval = cnt_new === 0 ? 100 : Math.floor(1000 / cnt_new);

            data_new.forEach((el, i, arry) => {
                arry[i].delta = this.que_interval;
            });
            this.queue = this.queue.concat(data_new);

        } catch (err) {
            console.log(err);
        }
    }

    dequeue() {

        let wait_time = 500;

        if (this.queue.length > 0) {
            let c = this.queue[0];
            wait_time = this.queue[0].delta;
            this.sendOsc(c);
            this.queue.shift();
        }

        // next queue
        setTimeout(() => {
            this.dequeue();
        }, wait_time);
    }

    async sendOsc(d) {
        let args = [
            //{ type: 's', value: d.id },
            { type: 's', value: d.event },
            { type: 's', value: d.actor },
            //{ type: 's', value: d.img },
            { type: 's', value: d.repo }
        ];

        if (!(this.filterTarget[d.event])) {
            await this.udpPort.send({
                address: '/new',
                args: args
            }, '127.0.0.1', 7402);
        }

        await this.io.emit('new', { event: d.event });

    }

};
