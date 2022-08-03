#pragma once
#include <iostream>
#include <memory>

// Product
class Warrior
{
public:
	virtual ~Warrior() = default;
	virtual void info() const = 0;
};

class Infantryman final : public Warrior
{
public:
	void info() const override
	{
		std::cout << "Infantryman" << '\n';
	}
};

class Archer final : public Warrior
{
public:
	void info() const override
	{
		std::cout << "Archer" << '\n';
	}
};

class Horseman final : public Warrior
{
public:
	void info() const override
	{
		std::cout << "Horseman" << '\n';
	}
};


// Factory
class Factory
{
public:
	virtual ~Factory() = default;
	virtual std::unique_ptr<Warrior> createWarrior() = 0;
};

class InfantryFactory final : public Factory
{
public:
	[[nodiscard]] std::unique_ptr<Warrior> createWarrior() override
	{
		return std::make_unique<Infantryman>();
	}
};

class ArchersFactory final : public Factory
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


//main()
#if 0
	std::vector<std::unique_ptr<Warrior>> warriors;

	std::unique_ptr<Factory> infantry_factory{ std::make_unique<InfantryFactory>() };
	std::unique_ptr<Factory> archers_factory{std::make_unique<ArchersFactory>()};
	warriors.emplace_back(infantry_factory->createWarrior());
	warriors.emplace_back(archers_factory->createWarrior());

	for (const auto &it : warriors)
		it->info();
#endif
