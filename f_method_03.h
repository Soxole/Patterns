#pragma once
#include <iostream>
#include <memory>

using std::cout;
using std::endl;


// Product
class Warrior
{
public:
	virtual ~Warrior() {}
	virtual void info() const = 0;
};

class Infantryman : public Warrior
{
public:
	void info() const override
	{
		cout << "Infantryman" << endl;
	}
};

class Archer : public Warrior
{
public:
	void info() const override
	{
		cout << "Archer" << endl;
	}
};

class Horseman final : public Warrior
{
public:
	void info() const override
	{
		cout << "Horseman" << endl;
	}
};


// Factory
class Factory
{
public:
	virtual ~Factory() {}
	virtual std::unique_ptr<Warrior> createWarrior() = 0;
};

class InfantryFactory : public Factory
{
public:
	[[nodiscard]] std::unique_ptr<Warrior> createWarrior() override
	{
		return std::make_unique<Infantryman>();
	}
};

class ArchersFactory : public Factory
{
public:
	[[nodiscard]] std::unique_ptr<Warrior> createWarrior()override
	{
		return std::make_unique<Archer>();
	}
};

class CavalryFactory final : public Factory
{
public:
	[[nodiscard]] std::unique_ptr<Warrior> createWarrior() override
	{
		return std::make_unique<Horseman>();
	}
};

/*
	vector<unique_ptr<Warrior>> warriors;

	unique_ptr<Factory> infantry_factory{ make_unique<InfantryFactory>() };
	unique_ptr<Factory> archers_factory{make_unique<ArchersFactory>()};
	warriors.emplace_back(infantry_factory->createWarrior());
	warriors.emplace_back(archers_factory->createWarrior());

	for (const auto &it : warriors)
		it->info();

*/