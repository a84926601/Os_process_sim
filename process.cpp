#include <string>

#include "process.h"

using namespace std;

process::process(){
    processName="null";
    processStatus=stop;
    remainingWork=0;
}
process::process(string name,int status,int work){
    processName=name;
    processStatus=ready;
    remainingWork=work;
}
string process::getName(){
    return processName;
}
int process::getStatus(){
    return processStatus;
}
int process::getWork(){
    return remainingWork;
}
