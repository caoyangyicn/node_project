const {
    log,
    write
} = console;
const { returnValue } = File;
const {getHostname, getOSInformation, getCPUInfo } = OS
log("Hello World");
returnValue((aaa)=> {
    log(aaa);
});
log(getHostname(11111));
log(getOSInformation());
log(getCPUInfo());