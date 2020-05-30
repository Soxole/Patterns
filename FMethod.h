#pragma once
#include <iostream>
#include <memory>
#include <vector>

//Base class abstract
class BaseTank
{
public:
	virtual void draw() = 0;
};


//product 1
class T34usa : public BaseTank
{
public:
	void draw() override { std::cout << "I'm heavy tank T34(USA)" << std::endl; }
};

//product 2
class T34ussr : public BaseTank
{
public:
	void draw() override { std::cout << "I'm heavy tank T34(USSR)" << std::endl; }
};


//Фабрика с производством
//***************************************************************************************
class TankFactory
{
public:
	enum class eTankType
	{
		T34_USA,
		T34_USSR
	};
	
	static std::unique_ptr<BaseTank> createTnak(eTankType object);
};
//***************************************************************************************


//функция создания объектов
std::unique_ptr<BaseTank> TankFactory::createTnak(eTankType object)
{
	switch (object)
	{
	case TankFactory::eTankType::T34_USA:
		return std::make_unique<T34usa>();
		break;
	case TankFactory::eTankType::T34_USSR:
		return std::make_unique<T34ussr>();
		break;
	}
	return 0;
}