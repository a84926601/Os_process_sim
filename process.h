#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#endif // PROCESS_H
using namespace std;

class process{
public:
    process();
    process(string,int,int);
    void setStatus(int);
    void execute();
    string getName();
    int getStatus();
private:
    string processName;
    int processStatus,remainingWork;
};
