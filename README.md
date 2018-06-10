# GHSatellite
## About

## Dependency
Tested on
* OS
    * Windows 10 Home ver.1803
    * macOS High Sierra Version 10.13.5
* Node.js v8.11.1
* openFrameworks 0.10.0
    * master banch on github at [this commit](https://github.com/openframeworks/openFrameworks/tree/c274c7fb51b4ae0552cd4cdb00475458aeeb610a)
    * build with
        * Visual Studio 2017(v141)
        * Xcode Version 9.4
* font:
    * [noto-sans-normal-light](https://www.google.com/get/noto/) &copy; Google
    * [track](http://www.fontfabric.com/track-free-font/) &copy; [Gumpita Rahayu](https://www.behance.net/gumpita)


## Bulid
### node Server
1. get github api access token in [here](https://github.com/settings/tokens)
    * paste your token in [line 8](https://github.com/nama-gatsuo/GHSatellite/blob/master/node/src/server/ApiHandler.js#L8) in `node/src/server/ApiHandler.js`
2. install node module and build js file
```sh
$ cd node
$ npm install
$ gulp build
```

### openFrameworks
1. open by "[Projector Generator](https://github.com/openframeworks/openFrameworks/blob/c274c7fb51b4ae0552cd4cdb00475458aeeb610a/docs/projectgenerator.md)" and do **Update** this directory.
2. build **Release** version with IDE

## Run
Double clicking `start.bat`(Windows) / `start.command`(macOS) then automatically node server and oF app will start.
* access with HTTP to PORT 8080 then can get controller.
