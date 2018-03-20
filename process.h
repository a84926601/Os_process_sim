#ifndef PROCESS_H
#define PROCESS_H
#endif // PROCESS_H

using namespace std;

enum ProcessStatus{ready,waiting,running,stop};

class process{
public:
    process();
    process(string,int);
    bool didRemainWork();
    void setStatus(int);
    void execute();
    string getName();
    int getStatus();
    int getWork();
    int getUsedClock();
private:
    string processName;
    int processStatus,remainingWork,usedClock;
};
