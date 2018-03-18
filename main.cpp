#include <iostream>
#include <string>
#include <process.h>
using namespace std;

int main(int argc, char *argv[])
{
    process a("A",0,0);
    cout<<a.getName()<<endl;
    cout<<"Hello World!!\n";
    return 0;
}
