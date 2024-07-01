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

#include "visitor_01.h"

using namespace std::string_literals;

constexpr int number_comp = 2;
void client_code(std::array<std::shared_ptr<Component>, number_comp> const &components,
	std::shared_ptr<Visitor> &&client_code_visitors) {
	for (auto &&it : components)
		it->accept(std::move(*client_code_visitors));
}


int main() {
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot

	std::array<std::shared_ptr<Component>, number_comp> components;
	components[0] = std::make_shared<ConcreteComponent_a>();
	components[1] = std::make_shared<ConcreteComponent_b>();


	std::cout << "The client code works with all visitors via the base Visitor interface:\n";
	auto main_visitor_1 = std::make_shared<ConcreteVisitor_1>();
	client_code(components, std::move(main_visitor_1));


	std::cout << "\nIt allows the same client code to work with different types of visitors:\n";
	auto main_visitor_2 = std::make_shared<ConcreteVisitor_2>();
	client_code(components, std::move(main_visitor_2));


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