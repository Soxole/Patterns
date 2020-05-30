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

