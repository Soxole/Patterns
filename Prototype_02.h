#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <array>


using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;



class Stooge
{
public:
	virtual void slap_stick() = 0;
	virtual unique_ptr<Stooge> clone() = 0;
};


class Larry : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Larry " << endl;
	}
	virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Larry>();
	}
	virtual~Larry() = default;
};

class Moe : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Moe " << endl;
	}
	virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Moe>();
	}
	virtual~Moe() = default;
};


class Factory
{
public:
	static inline unique_ptr<Stooge> make_stooge(int choice)
	{
		return s_prototypes[choice]->clone();
	}

protected:
	static inline std::array<unique_ptr<Stooge>, 3> s_prototypes = {
		nullptr, make_unique<Larry>(), make_unique<Moe>()
	};

};


/*
int main()
	vector<unique_ptr<Stooge>> vec;
	vec.push_back(make_unique<Larry>());
	vec.emplace_back(make_unique<Moe>());

	for (const auto &it : vec)
		it->slap_stick();




*/
