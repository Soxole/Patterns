#pragma once
#include <iostream>
#include <memory>

//Base class abstract
class BaseTank
{
public:
	virtual void draw() = 0;
	virtual ~BaseTank() = default;
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


//������� � �������������
//***************************************************************************************
class TankFactory
{
public:
	enum class eTankType
	{
		T34_USA,
		T34_USSR
	};
	
	static std::unique_ptr<BaseTank> createTank(eTankType object);
};
//***************************************************************************************


//������� �������� ��������
inline std::unique_ptr<BaseTank> TankFactory::createTank(eTankType object)
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