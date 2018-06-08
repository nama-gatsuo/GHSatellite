import express from 'express'
import path from 'path'
import logger from 'morgan'
import http from 'http'

export default class Server {
    constructor() {

        this.express = express();
        this.express.use(logger('dev'));
        this.express.use(express.static(path.join(__dirname, '../client')));

    }
};
