#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <regex>
#include <sstream>
#include <numeric>
#include <cassert>
#include <cstdlib>
#include <random>
#include <chrono>
#include <cstdlib>
#include <bitset>
#include <stack>
#include <utility>
#include <type_traits>
#include <cstdarg>
#include <array>
#include "Stack_temp.h"
#include "Person.h"
//#include "Singletone.h"
//#include "Builder_three.h"
#include "Builder_two.h"
//#include "Builder.h"



using namespace std;


unsigned long long countChange(unsigned money, const std::vector<unsigned> &coins)
{
	std::vector<unsigned long long> ks(money + 1);	//заполн€етс€ нул€ми
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


template<typename T1>
constexpr auto GeneratorINT_DOUBLE(T1 a, T1 b)
{
	random_device rd;
	mt19937 mt(rd());

	using uniform_type = conditional_t
		<is_floating_point<T1>::value,
		uniform_real_distribution<T1>, //for floating point
		uniform_int_distribution<T1>>; //for integer

	uniform_type generator(a, b);
	return generator(mt);
}

template<typename Tl, typename T2 >
constexpr common_type_t<Tl, T2> Max2(Tl a, T2 b) //C++ 14 with _t at the end
{
	return b < a ? a : b;
}


template<typename T = int, typename T2>
T sum(T a, T2 b)
{
	return a + b;
}


template<typename... T>
void print(T const &... args)
{
	print(args...);
}

template<size_t... Idx, typename T>
void printIdx(T const &coll)
{
	print(coll[Idx]...);
}

template<typename T, typename... TN >
constexpr bool isHomogeneous(T, TN...)
{
	return (std::is_same_v<T, TN> && ...); // Ќачина€ с C++17
}

template<int N, int M>
bool lesss(char const(&a)[N], char const(&b)[M])
{
	for (int i = 0; i < N && i < M; ++i)
	{
		if (a[i] < b[i]) return true;
		if (b[i] < a[i]) return false;
	}
	return N < M;
}



int main()
{
	Director dir;
	RomanArmyBuilder ra_builder;
	CarthaginianArmyBuilder ca_builder;

	









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

