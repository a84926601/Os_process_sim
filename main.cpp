#ifdef __linux__ 
#include <unistd.h>
#include <termios.h>
#elif _WIN32
#include <conio.h>
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <fstream>

#include "process.h"

using namespace std;

int cpuLimit=0,programCount=0;
queue<process> programList;
process *pp=NULL;
string sWating="wating:";
bool showProcessStatus();
bool popUntilNonStop();
#ifdef __linux__
char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }
#endif

int main(int argc, char *argv[])
{
    string tmpname,line,filePath;
    int tempwork;
    cout<<"Input your file path:";  //home/payne/Os_process_sim/input.txt
    cin>>filePath;
    ifstream programsData(filePath, ios_base::in);
    getline(programsData, line);
    istringstream iss(line);
    iss>>tmpname>>cpuLimit;
    //Push program to ram
    while(getline(programsData, line)){
        istringstream iss(line);
        iss>>tmpname>>tempwork;
        programList.push(process(tmpname,tempwork));
        programCount++;
    }

    //Starting execute
    programList.front().setStatus(running);

    while(!showProcessStatus()){    //CPU clock
        popUntilNonStop();
        char gch=getch();
        if(gch!='\r'&&gch!='\n'){	//Windows<-/->Linux
            if(pp==NULL){
                cout<<"-----I/O-----"<<endl;
                pp=&(programList.front());
                programList.pop();
                programCount--;
                sWating+=(string(pp->getName())+"("+to_string(pp->getWork())+")");
                pp->setStatus(waiting);
            }
            else{
                cout<<"-----I/O complete-----"<<endl;
                sWating="wating:";
                pp->setStatus(ready);
                programList.push(*pp);
                programCount++;
                pp=NULL;
                programList.front().setStatus(running);
            }
        }
        else if(!programList.front().didRemainWork()){ //end work
            programList.front().execute();
            programList.front().setStatus(stop);
            programList.push(programList.front());
            programList.pop();
            if(popUntilNonStop()){
                programList.front().setStatus(running);
            }
        }
        //reach cpu limit
        else if(programList.front().getUsedClock()>=cpuLimit-1){
            programList.front().execute();
            programList.front().setStatus(ready);
            programList.push(programList.front());
            programList.pop();
            popUntilNonStop();
            programList.front().setStatus(running);
        }else programList.front().execute();
    }

    return 0;
}
bool popUntilNonStop(){
    int i=0;
    while(programList.front().getStatus()==stop){   //clean stop work
        programList.push(programList.front());
        programList.pop();
        i++;
        if(i>=programCount)return false;
    }
    return true;
}
bool showProcessStatus(){
    string sReady="ready:",sRunning="running:",sStop="exit:";
    bool allStop=true;
    for (int i=0;i<programCount;i++) {
        stringstream sstring;
        sstring<<programList.front().getName()<<"("<<programList.front().getWork()<<") ";
        switch(programList.front().getStatus()){
            case ready:
                sReady+=sstring.str();
                allStop=false;
                break;
            /*case waiting:
                sWating+=sstring.str();
                allStop=false;
                break;*/
            case running:
                sRunning+=sstring.str();
                allStop=false;
                break;
            case stop:
                sStop+=sstring.str();
                break;
        }
        programList.push(programList.front());  //keep process data
        programList.pop();
    }
    cout<<sReady<<endl<<sWating<<endl<<sRunning<<endl<<sStop<<endl;
    return allStop;
}
