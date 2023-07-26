//checking leaks
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <crtdbg.h>   //for malloc and free
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include <numeric>
#include <array>

#include "composite.h"

using namespace std::string_literals;

void client_code(const std::shared_ptr<IComponent> &component) {

	std::cout << "RESULT: " << component->operation();
}

void client_code2(std::shared_ptr<IComponent> &&component1,
				  std::shared_ptr<IComponent> &&component2) {

	if (component1->isComposite()) {
		component1->addComp(std::move(component2));
	}
	std::cout << "RESULT: " << component1->operation();
}


int main() {
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot

	std::shared_ptr<IComponent> simple{ std::make_shared<Leaf>() };
	std::cout << "Client: I've got a simple component:\n";
	client_code(simple); //cl_1
	std::cout << "\n";

	std::shared_ptr<IComponent> tree{ std::make_shared<Composite>() };
	std::shared_ptr<IComponent> branch{ std::make_shared<Composite>() };
	std::unique_ptr<IComponent> leaf_1{ std::make_unique<Leaf>() }; //once using
	std::unique_ptr<IComponent> leaf_2{ std::make_unique<Leaf>() };	//once using
	std::unique_ptr<IComponent> leaf_3{ std::make_unique<Leaf>() };	//once using

	branch->addComp(move(leaf_1));
	branch->addComp(move(leaf_2));

	std::shared_ptr<IComponent> branch2{ std::make_shared<Composite>() };

	branch2->addComp(move(leaf_3));
	tree->addComp(move(branch));
	tree->addComp(move(branch2));

	std::cout << "Client: Now I've got a composite tree:\n";
	client_code(tree);	//cl_1
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";

	client_code2(move(tree), move(simple));	//cl_1
	std::cout << "\n";


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