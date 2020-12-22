#pragma once
#include <iostream>
#include <memory>
#include <vector>

//Паттерн Builder определяет процесс поэтапного конструирования сложного объекта,
//в результате которого могут получаться разные представления этого объекта.



using std::cout;
using std::endl;

class Pizza_Product
{
public:
	~Pizza_Product() = default;
	void setDough(const std::string &dough) { m_dough = dough; }
	void setSauce(const std::string &sauce) { m_sauce = sauce; }
	void setTopping(const std::string &topping) { m_topping = topping; }

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
//////////////////////////////////////////////////////////////////////////////////
class Pizza_Builder
{
public:
	virtual ~Pizza_Builder() = default;

	[[nodiscard]] Pizza_Product *getPizza()
	{
		return m_pizza.release();
	}
	void createNewPizza()
	{
		m_pizza = std::make_unique<Pizza_Product>();
	}

	virtual void buildDough() const = 0;
	virtual void buildSauce() const = 0;
	virtual void buildTop() const = 0;

protected:
	std::unique_ptr<Pizza_Product> m_pizza;
};
////////////////////////////////////////////////////////////////////////////////

//конкретные строители
class Margherita_ConcreteBuilder : public Pizza_Builder
{
public:
	void buildDough() const override { m_pizza->setDough("cross"); }
	void buildSauce() const override { m_pizza->setSauce("tomato"); }
	void buildTop() const override { m_pizza->setTopping("mazzarela + basil"); }
};

class Spicy_ConcreteBuilder : public Pizza_Builder
{
public:
	void buildDough() const override { m_pizza->setDough("pan baked"); }
	void buildSauce() const override { m_pizza->setSauce("tomato + chilli"); }
	void buildTop() const override { m_pizza->setTopping("pepperoni + salami"); }
};
//////////////////////////////////////////////////////////////////////////////////

class Cook_Director
{
public:
	void tastePizza() const
	{
		m_pizzaBuilder->getPizza()->taste();
	}

	void makePizza(Pizza_Builder *pb)
	{
		m_pizzaBuilder = pb;
		m_pizzaBuilder->createNewPizza();
		m_pizzaBuilder->buildDough();
		m_pizzaBuilder->buildSauce();
		m_pizzaBuilder->buildTop();
	}
private:
	Pizza_Builder *m_pizzaBuilder;
	//std::unique_ptr<Pizza_Builder> m_pizzaBuilder;
};


/*
	Cook_Director dir{};
	Margherita_ConcreteBuilder pizzaMargherita;
	Spicy_ConcreteBuilder pizzaSpicy;

	dir.makePizza(&pizzaMargherita);
	dir.tastePizza();

	dir.makePizza(&pizzaSpicy);
	dir.tastePizza();

*/
