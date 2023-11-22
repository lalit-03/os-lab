#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
using namespace std;
#define SHARED_MEMORY_SIZE 8192
#define BUFFER_SIZE 200
int main(int argc, char* argv[]){
    if(argc!=2){
        cout<<"Please enter the parameter n for Catalan numbers: \n";
        return 1;
    }
    int n=stoi(argv[1]);
    HANDLE fmapping = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        SHARED_MEMORY_SIZE,
        (LPCTSTR)"SharedMemory"
    );
    LPCTSTR sharedmem = (LPCTSTR)MapViewOfFile(
        fmapping,
        FILE_MAP_WRITE,
        0,
        0,
        SHARED_MEMORY_SIZE
    );
    int num=1;
    for(int i=0;i<n;i++){
        ((int *)sharedmem)[i]=num;
        num=num*(4*i+2)/(i+2);
    }
    Sleep(10000);
    UnmapViewOfFile(sharedmem);
    CloseHandle(fmapping);
    cout<<"Producer has successfully written "<<n<<" Catalan numbers to shared memory."<<"\n";
    return 0;
}