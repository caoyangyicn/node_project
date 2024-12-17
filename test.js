const {
    log,
    write
} = console;
const { returnValue, readFileUtf8, existsSync } = File;
const {getHostname, getOSInformation, getCPUInfo } = OS
log("Hello World");
// returnValue((aaa)=> {
//     log(aaa);
// });
// log(getHostname(11111));
// log(getOSInformation());
// log(getCPUInfo());
// let result = readFileUtf8("../test.js");
// log(result);
log(existsSync("../test.js"));