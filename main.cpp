#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <fstream>
#include <process.h>

using namespace std;
enum ProcessStatus{ready,waiting,running,stop};

int cpuLimit=0,programCount=0;
queue<process> programList;
bool showProcessStatus();

int main(int argc, char *argv[])
{
    string tmpname,line;
    int tempwork;
    ifstream programsData("/home/payne/Os_process_sim/input.txt", ios_base::in);
    //cout<<"Input your cpu process clock limit:";
    getline(programsData, line);
    istringstream iss(line);
    iss>>tmpname>>cpuLimit;
    //cout<<"Input your programs info(name workclock):\n";
    //Push program to ram
    while(getline(programsData, line)){
        iss.str(line);
        iss>>tmpname>>tempwork;
        programList.push(process(tmpname,ready,tempwork));
        programCount++;
        cout<<programCount<<endl;
    }

    //Starting execute
    while(!showProcessStatus()){


    }

    return 0;
}

bool showProcessStatus(){
    string sReady="ready:",sWating="wating:",sRunning="running",sStop="exit:";
    bool allStop=true;
    for (int i=0;i<programCount;i++) {
        stringstream sstring;
        sstring<<programList.front().getName()<<"("<<programList.front().getWork()<<") ";
        switch(programList.front().getStatus()){
            case ready:
                sReady+=sstring.str();
                allStop=false;
                break;
            case waiting:
                sWating+=sstring.str();
                allStop=false;
                break;
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
    return true;
}
