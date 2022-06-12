//checking leaks
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <crtdbg.h>   //for malloc and free
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

#include "decorator_02.h"


int main() {
    _CrtMemState sOld;
    _CrtMemState sNew;
    _CrtMemState sDiff;
    _CrtMemCheckpoint(&sOld); //take a snapshot






    std::unique_ptr<Widget> a_widget{ std::make_unique<BorderDecorator>(
                                                std::make_unique<BorderDecorator>(
                                                    std::make_unique<ScrollDecorator>(
                                                        std::make_unique<TextField>(80, 24)))) };
    a_widget->draw();







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