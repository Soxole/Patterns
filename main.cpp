//#define _CRT_SECURE_NO_WARNINGS
#include "windows.h"
#define _CRTDBG_MAP_ALLOC //to get more details
#include <crtdbg.h>   //for malloc and free

#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include "visitor_01.h"

/*
#include "visitor_02.h"
#include "template_method_01.h"
#include "Strategy_01.h"
#include "state_01.h"
#include "Composite.h"
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
#include "Builder.h"
#include "builder_04.h"
#include "abstract_factory_02.h"
#include "Abstract_Factrory.h"
#include "Builder_two.h"
#include "f_method_03.h"
#include "FMethod.h"
#include "facade_01.h"
#include "f_method_02.h"
#include "decarotor_02.h"
#include "Composite_02.h"
#include "Stack_temp.h"
#include "Person.h"
#include "Singletone.h"
#include "Builder_03.h"
#include "Builder_05.h"
*/

using namespace std;



/*
void client_code(const shared_ptr<IComponent> &component) {

	std::cout << "RESULT: " << component->operation();
}


void client_code2(shared_ptr<IComponent> &component1, shared_ptr<IComponent> &component2) {

	if (component1->isComposite()) {
		component1->addComp(component2);
	}
	std::cout << "RESULT: " << component1->operation();
}
*/

//void clientCode()
//{
//	auto m_context = make_unique<Context>(make_unique<ConcreteStrategy_A>());
//	std::cout << "Client: Strategy is set to normal sorting.\n";
//	m_context->do_some_business_logic();
//	std::cout << "\n";
//    std::cout << "Client: Strategy is set to reverse sorting.\n";
//	m_context->set_strategy(make_unique<ConcreteStrategy_B>());
//	m_context->do_some_business_logic();
//}

constexpr int number_comp = 2;
void client_code(array<shared_ptr<Component>, number_comp> const &components,
	shared_ptr<Visitor> &&client_code_visitors)
{
	for (auto &&it : components)
		it->accept(move(*client_code_visitors));
}

int main()  // NOLINT(bugprone-exception-escape)
{
	//--------------- for leaks (start) --------------------//
	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;
	_CrtMemCheckpoint(&sOld); //take a snapshot
	//--------------- below your code --------------------//



	//array<shared_ptr<Component>, number_comp> components = {make_shared<ConcreteComponent_a>(), make_shared<ConcreteComponent_b>()};
	
	array<shared_ptr<Component>, number_comp> components;
	components[0] = make_shared<ConcreteComponent_a>();
	components[1] = make_shared<ConcreteComponent_b>();


	std::cout << "The client code works with all visitors via the base Visitor interface:\n";
	auto main_visitor_1 = make_shared<ConcreteVisitor_1>();
	client_code(components, move(main_visitor_1));


	std::cout << "\nIt allows the same client code to work with different types of visitors:\n";
	auto main_visitor_2 = make_shared<ConcreteVisitor_2>();
	client_code(components, move(main_visitor_2));

	/*

	shared_ptr<IComponent> tree{ make_shared<Composite>() };
	shared_ptr<IComponent> simple{ make_shared<Leaf>() };
	std::cout << "Client: I've got a simple component:\n";

	client_code(simple);
	cout << "\n";

	shared_ptr<IComponent> branch{ make_shared<Composite>() };
	unique_ptr<IComponent> leaf_1{ make_unique<Leaf>() }; //once using
	unique_ptr<IComponent> leaf_2{ make_unique<Leaf>() };	//once using
	unique_ptr<IComponent> leaf_3{ make_unique<Leaf>() };	//once using

	branch->addComp(move(leaf_1));
	branch->addComp(move(leaf_2));

	shared_ptr<IComponent> branch2{ make_shared<Composite>() };

	branch2->addComp(move(leaf_3));
	tree->addComp(branch);
	tree->addComp(branch2);

	std::cout << "Client: Now I've got a composite tree:\n";
	client_code(tree);
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";

	client_code2(tree, simple);
	std::cout << "\n";
	*/

	//--------------- above your code) --------------------//
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
	//--------------- for leaks (end) --------------------//
	std::cout << endl;
	return 0;
}