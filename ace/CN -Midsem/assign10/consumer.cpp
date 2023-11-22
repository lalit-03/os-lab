#include <bits/stdc++.h>
#include <windows.h>
#include <cstdlib>
using namespace std;
#define SHARED_MEMORY_SIZE 8192
#define BUFFER_SIZE 200
int main(){
    HANDLE fmapping = OpenFileMapping(
        FILE_MAP_READ,
        FALSE,
        (LPCTSTR)"SharedMemory"
    );
    LPCTSTR sharedmem = (LPCTSTR)MapViewOfFile(
        fmapping,
        FILE_MAP_READ,
        0,
        0,
        0
    );
    int count=0;
    cout<<"Consumer is reading from the shared memory: \n"<<"The Catalan numbers are - ";
    while(((unsigned long long *)sharedmem)[count]!=0){
        cout<<((unsigned long long*)sharedmem)[count]<<" ";
        count++;
    }
    UnmapViewOfFile(sharedmem);
    CloseHandle(fmapping);
    return 0;
}