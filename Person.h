#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>

using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::vector;
using std::cout;
using std::endl;

class Person
{
public:
	string name;
	shared_ptr<Person> mother;
	shared_ptr<Person> father;
	vector<weak_ptr<Person>> kids;

	Person(const string &n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
		:name(n), mother(m), father(f) {
	}
	~Person() { cout << "delete " << endl; }
};


//функция из примера (не main())
//shared_ptr<Person> initFamily(const string &name)
//{
//	shared_ptr<Person> mom(make_shared<Person>(name + "'s mom"));
//	shared_ptr<Person> dad(make_shared<Person>(name + "'s dad"));
//	shared_ptr<Person> kid(make_shared<Person>(name, mom, dad));
//	mom->kids.emplace_back(kid);
//	dad->kids.emplace_back(kid);
//
//	return kid;
//}