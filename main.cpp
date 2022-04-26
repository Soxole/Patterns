#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <crtdbg.h>   //for malloc and free

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>


#include "Builder_05.h"
/*
#include "Abstract_Factrory_01.h"
#include "abstract_factory_02.h"
#include "f_method_02.h"
#include "f_method_03.h"
#include "facade_01.h"
#include "Composite.h"
#include "visitor_01.h"
#include "visitor_02.h"
#include "template_method_01.h"
#include "Strategy_01.h"
#include "state_01.h"
#include "mediator_01.h"
#include "observer_01.h"
#include "cor_01.h"
#include "memento_01.h"
#include "iterator_01.h"
#include "decorater_01.h"
#include "proxy_01.h"
#include "bridge_02.h"
#include "Bridge_01.h"
#include "Adapter_02.h"
#include "Adapter_01.h"
#include "singletone_02.h"
#include <unordered_set>
#include "Prototype_01.h"
#include "Prototype_02.h"
#include "builder_04.h"
#include "Builder_two.h"
#include "f_method_02.h"
#include "decarotor_02.h"
#include "Composite_02.h"
#include "Stack_temp.h"
#include "Person.h"
#include "Singletone.h"
#include "Builder_03.h"
#include "Builder_05.h"
*/




int main()  // NOLINT(bugprone-exception-escape)
{
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
//-----------------------------------------------------------------------------------------------------

	Director director;
	director.setBuilder(std::make_unique<AudiQ7Diesel>());

	std::unique_ptr<Car> audiQ7(std::make_unique<Car>());
	audiQ7 = director.makeCar();
	audiQ7->print_info();

	std::cout << std::endl;
	std::cout << std::endl;

	director.setBuilder(std::make_unique<AudiTTGasoline>());
	std::unique_ptr<Car> audiTT(std::make_unique<Car>());
	audiTT = director.makeCar();
	audiTT->print_info();


//-----------------------------------------------------------------------------------------------------
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