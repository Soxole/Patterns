#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <utility>
#include "decorater_01.h"
/*
#include "decarotor_02.h"
#include "Prototype_01.h"
#include "Composite_02.h"
#include <span>
#include <vector>
#include <variant>
#include <regex>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <random>
#include "Bridge_01.h"
#include "Prototype_02.h"
#include "Adapter_02.h"
#include "Adapter_01.h"
#include <chrono>
#include <cstdlib>
#include <bitset>
#include <stack>
#include <type_traits>
#include <cstdarg>
#include <array>
#include <map>
#include <concepts>
#include "Abstract_Factrory.h"
#include "Stack_temp.h"
#include "Person.h"
#include "Singletone.h"
#include "Builder_two.h"
#include "Builder.h"
#include "Builder_03.h"
#include "Builder_05.h"
*/

using namespace std;
/*

unsigned long long countChange(unsigned money, const std::vector<unsigned> &coins)
{
	std::vector<unsigned long long> ks(money + 1);	//заполняется нулями
	ks[0] = 1;
	for (unsigned i : coins) {
		for (unsigned j = i; j <= money; j++) {
			ks[j] += ks[j - i];
			std::cout << "=> " << ks[j] << endl;
		}
	}
	copy(ks.begin(), ks.end(), ostream_iterator<unsigned long long>(std::cout, " ")); std::cout << endl;
	return ks[money];
}

using ull = unsigned long long;
ull exp_sum(unsigned int n)
{
	std::vector<ull> c(n + 1, 0); // array of coefficients of X^0 ... X^n
	c[0] = 1;  // start with 1X^0
	for (unsigned int k = 1; k <= n; ++k) // multiply by 1/(1-X^k)
		for (unsigned int i = 0; (i + k) <= n; ++i)
		{
			c[i + k] += c[i];
			std::cout << "==> " << c[i + k] << " += " << c[i] << endl;
		}
	return c[n];
}

//преобразовать в бинари
void convert(int val, vector<int> &binary)
{
	int temp = val % 2;

	if (val >= 2)
	{
		convert(val / 2, binary);
	}
	binary.emplace_back(temp);
	//cout << temp << " ";
}

namespace temp {

	enum class maxSize : int
	{
		sMAX = 100
	};
}

namespace std {
	enum class tmp : size_t
	{
		one,
		two,
		three
	};
}
*/




int main()
{
	/*unique_ptr<IComponent> simple = make_unique<ConcreteComponent>();
	std::cout << "Client: I've got a simple component:\n";
	cout << simple->operation() << "\n";
	cout << "\n\n";
	unique_ptr<IComponent> decorator_01 = make_unique<ConcreteDecorator_A>(make_unique<Decorator>(move(simple)));
	unique_ptr<IComponent> decorator_02 = make_unique<ConcreteDecorator_B>(make_unique<Decorator>(move(decorator_01)));
	std::cout << "Client: Now I've got a decorated component:\n";
	cout << decorator_02->operation() << "\n";*/

	unique_ptr<IComponent> decorator_03{ make_unique<Decorator>(
		make_unique<ConcreteDecorator_A>(
			make_unique<ConcreteDecorator_B>(
				make_unique<ConcreteComponent>()))) };

	cout << decorator_03->operation() << "\n";


	//std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	//ClientCode2(move(tree), move(simple));
	//std::cout << "\n";

	//random_device rd;
	//mt19937 mt;
	//uniform_int_distribution<int> gen(1, 10);
	//vector<int> vec(10);
	//int i = 1;	
	//string str;
	////vector<int> to_vec;
	//generate(vec.begin(), vec.end(), [&i] {return i++; });
	//shuffle(vec.begin(), vec.end(), rd);
	////auto sum = find_if(vec.begin(), vec.end(), [](int j) {return j > 5; });
	//nth_element(vec.begin(), vec.begin() + 3, vec.end());
	//copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " ")); cout << endl;


	std::cout << endl;
	return 0;
}

