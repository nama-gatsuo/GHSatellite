# GHSatellite
## Dependency
Tested on
* OS: Windows 10 Home ver.1803
* Node.js v8.11.1
* openFrameworks
    * master banch on github at [this commit](https://github.com/openframeworks/openFrameworks/tree/c274c7fb51b4ae0552cd4cdb00475458aeeb610a)
    * with Viual Studio 2017(v141)

## Bulid
### node Server
```sh
$ cd node
$ npm install
$ gulp
```
### openFrameworks
* open by "[Projector Generator](https://github.com/openframeworks/openFrameworks/blob/c274c7fb51b4ae0552cd4cdb00475458aeeb610a/docs/projectgenerator.md)" and do **Update** this directory.
* open `GHSatellite.sln` by Visual Studio 2017 and **Build** (ctrl + shift + b)

## Run
Double clicking `start.bat` then automatically node server and oF app will start.
