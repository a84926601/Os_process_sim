#include <string>

#include "process.h"

using namespace std;

process::process(){
    processName="null";
    processStatus=stop;
    remainingWork=0;
    usedClock=0;
}
process::process(string name,int work){
    processName=name;
    processStatus=ready;
    remainingWork=work;
    usedClock=0;
}
bool process::didRemainWork(){
    if(remainingWork>1)return true;
    else return false;
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
int process::getUsedClock(){
    return usedClock;
}
void process::execute(){
    processStatus=running;
    remainingWork--;
    usedClock++;
}
void process::setStatus(int status){
    processStatus=status;
    usedClock=0;
}
