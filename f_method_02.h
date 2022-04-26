#pragma once
#include <string>
#include <memory>
#include <iostream>


//TITLE_: Fabric_method
/*
Фабричный метод — это порождающий паттерн проектирования, который решает проблему создания различных продуктов,
без указания конкретных классов продуктов.
Фабричный метод задаёт метод, который следует использовать вместо вызова оператора new для создания объектов-продуктов.
Подклассы могут переопределить этот метод, чтобы изменять тип создаваемых продуктов.
*/

using namespace std::string_literals;

class I_Product
{
public:
	virtual ~I_Product() = default;
	[[nodiscard]] virtual std::string lineOperation() const = 0;
};

//product 1
class ConcreteProduct_1 : public I_Product
{
public:
	[[nodiscard]] std::string lineOperation() const override
	{
		return "Result of the ConcreteProduct_1"s;
	}
};

//product 2
class ConcreteProduct_2 final : public I_Product
{
public:
	[[nodiscard]] std::string lineOperation() const override
	{
		return "Result of the ConcreteProduct_2"s;
	}
};

//Fabric methods
class Creator
{
public:
	virtual ~Creator() = default;
	[[nodiscard]] virtual std::unique_ptr<I_Product> factoryMethod() const = 0;

	void someOperation() const
	{
		//call the constructor from factoryMethod
		const auto product = factoryMethod();
		std::cout << "Creator: The same creator's code "s + product->lineOperation() << '\n';
	}
};

class ConcreteCreator_1 : public Creator
{
public:
	[[nodiscard]] std::unique_ptr<I_Product> factoryMethod() const override
	{
		return std::make_unique<ConcreteProduct_1>();
	}
};

class ConcreteCreator_2 final : public Creator
{
public:
	[[nodiscard]] std::unique_ptr<I_Product> factoryMethod() const override
	{
		return std::make_unique<ConcreteProduct_2>();
	}
};

/*
void clientCode(std::unique_ptr<Creator> const creator) {
	std::cout << "Client: I'm not aware of the creator's class, but it still works.\n";
	creator->someOperation();
}

	std::unique_ptr<Creator> creator{ std::make_unique<ConcreteCreator_1>() };
	clientCode(std::move(creator));
	std::unique_ptr<Creator> creator_two{ std::make_unique<ConcreteCreator_2>() };
	clientCode(std::move(creator_two));

*/