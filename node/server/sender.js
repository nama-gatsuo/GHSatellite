'use strict';

Object.defineProperty(exports, "__esModule", {
    value: true
});

var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

var _osc = require('osc');

var _osc2 = _interopRequireDefault(_osc);

var _https = require('https');

var _https2 = _interopRequireDefault(_https);

var _nodeFetch = require('node-fetch');

var _nodeFetch2 = _interopRequireDefault(_nodeFetch);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var Sender = function () {
    function Sender() {
        _classCallCheck(this, Sender);

        var item_num = 50;

        this.url = 'https://api.github.com/events';
        this.url += '?access_token=2bd8ac40da75af79216f63ca3a2f86f4cd85416b';
        this.url += '&per_page=' + item_num;

        this.cache = [];
        this.cache_size = 100;

        this.queue = [];

        this.que_interval = 100;
        this.req_interval = 1000;

        this.udpPort = new _osc2.default.UDPPort({
            localAddress: '0.0.0.0',
            localPort: 7401,
            metadata: true
        });
        this.udpPort.open();
    }

    _createClass(Sender, [{
        key: 'init',
        value: function init() {
            var _this = this;

            setInterval(function () {
                _this.req(_this.url);
            }, this.req_interval);
            setTimeout(function () {
                _this.dequeue();
            }, 2000);
            console.log('running...');
        }
    }, {
        key: 'req',
        value: async function req(url) {
            var _this2 = this;

            try {
                var r = await (0, _nodeFetch2.default)(url);
                var json = await r.json();

                var data_new = [];
                var cnt_new = 0;

                for (var i = 0; i < json.length; i++) {

                    var id = json[i].id;
                    var ci = this.cache.indexOf(id);
                    if (ci < 0) {
                        cnt_new++;
                        this.cache.push(id);

                        var d = {};
                        d.id = json[i].id;
                        var s = json[i].type;
                        d.event = s.substr(0, s.length - 5);
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

                //console.log('new:', cnt_new);
                this.que_interval = cnt_new === 0 ? 100 : Math.floor(1000 / cnt_new);
                //console.log('delta:', this.que_interval);

                data_new.forEach(function (el, i, arry) {
                    arry[i].delta = _this2.que_interval;
                });
                this.queue = this.queue.concat(data_new);

                //console.log('----');
            } catch (err) {
                console.log(err);
            }
        }
    }, {
        key: 'dequeue',
        value: function dequeue() {
            var _this3 = this;

            var wait_time = 500;

            if (this.queue.length > 0) {
                var c = this.queue[0];
                wait_time = this.queue[0].delta;
                this.sendOsc(c);
                this.queue.shift();
            }

            // next queue
            setTimeout(function () {
                _this3.dequeue();
            }, wait_time);
        }
    }, {
        key: 'sendOsc',
        value: async function sendOsc(d) {
            var args = [
            //{ type: 's', value: d.id },
            { type: 's', value: d.event }, { type: 's', value: d.actor },
            //{ type: 's', value: d.img },
            { type: 's', value: d.repo }];

            await this.udpPort.send({
                address: '/new',
                args: args
            }, '127.0.0.1', 7402);

            //console.log(args);
        }
    }]);

    return Sender;
}();

exports.default = Sender;
;
//# sourceMappingURL=sender.js.map
