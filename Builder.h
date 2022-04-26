#pragma once
#include <iostream>
#include <memory>

//Строитель — это порождающий паттерн проектирования, который позволяет создавать сложные объекты пошагово.
//Строитель даёт возможность использовать один и тот же код строительства для получения разных представлений объектов.

//на линуксе имеются ворнинги на Margherita_ConcreteBuilder и Spicy_ConcreteBuilder
//return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...)); this call could return NULL

using std::cout;
using std::endl;

//Product
class Pizza_Product final
{
public:
	~Pizza_Product() = default;
	void setDough(const std::string_view dough) { m_dough = dough; }
	void setSauce(const std::string_view sauce) { m_sauce = sauce; }
	void setTopping(const std::string_view topping) { m_topping = topping; }

	void taste() const
	{
		std::cout << "Pizza with "
			<< m_dough << " dough, "
			<< m_sauce << " sauce and "
			<< m_topping << " topping. Mmmmmmm." << std::endl;
	}
private:
	std::string m_dough;
	std::string m_sauce;
	std::string m_topping;
};

//Builder
class Pizza_Builder
{
public:
	virtual ~Pizza_Builder() = default;

	[[nodiscard]] std::unique_ptr<Pizza_Product> getPizza()
	{
		return std::move(m_pizza);
	}
	//for dir
	void createNewPizza()
	{
		m_pizza = std::make_unique<Pizza_Product>();
	}

	virtual void buildDough() const = 0;
	virtual void buildSauce() const = 0;
	virtual void buildTop() const = 0;

protected:
	std::unique_ptr<Pizza_Product> m_pizza{};
};


//Concrete builder
class Margherita_ConcreteBuilder final : public Pizza_Builder
{
public:
	void buildDough() const override { m_pizza->setDough("cross"); }
	void buildSauce() const override { m_pizza->setSauce("tomato"); }
	void buildTop() const override { m_pizza->setTopping("mozzarella + basil"); }
};

class Spicy_ConcreteBuilder final : public Pizza_Builder
{
public:
	void buildDough() const override { m_pizza->setDough("pan baked"); }
	void buildSauce() const override { m_pizza->setSauce("tomato + chilli"); }
	void buildTop() const override { m_pizza->setTopping("pepperoni + salami"); }
};

//Director
//class is complete a pizza
class Cook_Director final
{
public:
	void tastePizza() const
	{
		m_pizzaBuilder->getPizza()->taste();
	}

	void makePizza(std::unique_ptr<Pizza_Builder> pb)
	{
		m_pizzaBuilder = std::move(pb);
		m_pizzaBuilder->createNewPizza();
		m_pizzaBuilder->buildDough();
		m_pizzaBuilder->buildSauce();
		m_pizzaBuilder->buildTop();
	}
private:
	std::unique_ptr<Pizza_Builder> m_pizzaBuilder;
};


/*
	auto dir = std::make_unique<Cook_Director>(Cook_Director{});

	auto pizzaMargherita = std::make_unique<Margherita_ConcreteBuilder>();
	auto pizzaSpicy = std::make_unique<Spicy_ConcreteBuilder>();

	dir->makePizza(std::move(pizzaMargherita));
	dir->tastePizza();

	dir->makePizza(std::move(pizzaSpicy));
	dir->tastePizza();


	output:
	Pizza with cross dough, tomato sauce and mazzarela + basil topping. Mmmmmmm.
	Pizza with pan baked dough, tomato + chilli sauce and pepperoni + salami topping. Mmmmmmm.
*/
