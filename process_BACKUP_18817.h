#ifndef PROCESS_H
#define PROCESS_H
#endif // PROCESS_H
#include <string>
using namespace std;

class process{
public:
    process();
    process(string,int,int);
    void setStatus(int);
    void execute();
    string getName();
    int getStatus();
    int getWork();
private:
    string processName;
    int processStatus,remainingWork;
};
