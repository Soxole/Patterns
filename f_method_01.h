#pragma once
#include <iostream>
#include <memory>

//An abstract base class 
class BaseTank
{
public:
	virtual void draw() const = 0;
	virtual ~BaseTank() = default;
};

//product 1
class T34usa : public BaseTank
{
public:
	void draw() const override { std::cout << "I'm heavy tank T34(USA)" << '\n'; }
};

//product 2
class T34ussr : public BaseTank
{
public:
	void draw() const override { std::cout << "I'm heavy tank T34(USSR)" << '\n'; }
};

//fabric method 
class TankFactory
{
public:
	enum class eTankType
	{
		T34_USA,
		T34_USSR
	};

	static std::unique_ptr<BaseTank> createTank(eTankType const &object)
	{
		switch (object)
		{
		case eTankType::T34_USA:
			return std::make_unique<T34usa>();
		case eTankType::T34_USSR:
			return std::make_unique<T34ussr>();
		}
		return {};
	}
};

/*
	auto tank = TankFactory::createTank(TankFactory::eTankType::T34_USA);
	tank->draw();
	auto tank2 = TankFactory::createTank(TankFactory::eTankType::T34_USSR);
	tank2->draw();
 */