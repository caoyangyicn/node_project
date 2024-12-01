const {
    log,
    write
} = console;
const { returnValue } = File;
log("Hello World");
returnValue((aaa)=> {
    log(aaa);
});