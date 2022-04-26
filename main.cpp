//checking leaks

#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <crtdbg.h>   //for malloc and free

int main() {
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld); //take a snapshot

 



    _CrtMemCheckpoint(&sNew); //take a snapshot 
    if (_CrtMemDifference(&sDiff, &sOld, &sNew)) // if there is a difference
    {
        OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
        _CrtMemDumpStatistics(&sDiff);
        OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
        _CrtMemDumpAllObjectsSince(&sOld);
        OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
        _CrtDumpMemoryLeaks();
    }

    return 0;
}