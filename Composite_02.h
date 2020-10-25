#pragma once
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class IComponent
{
public:
	virtual void traverse() const = 0;
	virtual ~IComponent() = default;
};

//leaf
class Leaf : public IComponent
{
private:
	int value;
public:
	explicit Leaf(const int val) : value(val)
	{ }

	virtual void traverse() const override
	{
		cout << value << " ";
	}
};

//
class Composite final : public IComponent
{
private:
	vector<unique_ptr<IComponent>> children;
	
public:
	void add(unique_ptr<IComponent> element)
	{
		children.emplace_back(move(element));
	}
	virtual void traverse() const override
	{
		for (auto &&component : children)
		{
			cout << component << " ";
		}
	}
};


/*
 *не работает!!!! разобрать!
 *	Composite component[4];
	for (auto i = 0; i < 4; ++i)
	{
		component[i].add(make_unique<Leaf>(i));
	}
	
	for (auto j = 0; j < 4; ++j)
	{
		component[j].traverse();
	}
 * 
 */