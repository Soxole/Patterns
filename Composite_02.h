#pragma once
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class IComponent
{
public:
	virtual ~IComponent() = default;
	virtual void traverse() const = 0;
};

//leaf
class Leaf : public IComponent
{
public:
	explicit Leaf(const int val) : m_value(val)
	{ }

	void traverse() const override
	{
		cout << m_value << " ";
	}
private:
	int m_value;
};

//
class Composite final : public IComponent
{
public:
	void add(unique_ptr<IComponent> element)
	{
		m_children.emplace_back(move(element));
	}
	void traverse() const override
	{
		for (auto &&component : m_children)
		{
			cout << component << " ";
		}
	}
private:
	vector<unique_ptr<IComponent>> m_children;
	
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