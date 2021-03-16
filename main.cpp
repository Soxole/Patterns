//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include "observer_01.h"
#include "Composite.h"
/*
#include "mediator_01.h"
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



void client_code(const shared_ptr<IComponent> &component) {
	std::cout << "RESULT: " << component->operation();
}

void client_code2(const shared_ptr<IComponent> &component1, shared_ptr<IComponent> component2) {
	if (component1->isComposite())
	{
		component1->addComp(move(component2));
	}
	std::cout << "RESULT: " << component1->operation();
}

int main() noexcept
{
	shared_ptr<IComponent> tree{ make_shared<Composite>() };
	
	shared_ptr<IComponent> simple{ make_shared<Leaf>() };
	std::cout << "Client: I've got a simple component:\n";
	client_code(simple);
	cout << "\n";

	shared_ptr<IComponent> branch{ make_shared<Composite>() };
	shared_ptr<IComponent> leaf_1{ make_shared<Leaf>() };
	shared_ptr<IComponent> leaf_2{ make_shared<Leaf>() };
	shared_ptr<IComponent> leaf_3{ make_shared<Leaf>() };

	branch->addComp(leaf_1);
	branch->addComp(leaf_2);
	shared_ptr<IComponent> branch2{ make_shared<Composite>() };
	branch2->addComp(leaf_3);
	tree->addComp(branch);
	tree->addComp(branch2);

	std::cout << "Client: Now I've got a composite tree:\n";
	client_code(tree);
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	
	client_code2(tree, simple);
	std::cout << "\n";
	
	
	std::cout << endl;
	return 0;
}