#pragma once
#include <iostream>
#include <memory>
#include <vector>

//Паттерн Builder определяет процесс поэтапного конструирования сложного объекта, в результате которого могут получаться разные представления этого объекта.



using std::cout;
using std::endl;

class Pizza_Product
{
public:
	void setDough(const std::string dough) { m_dough = dough; }
	void setSauce(const std::string sauce) { m_sauce = sauce; }
	void setTopping(const std::string topping) { m_topping = topping; }

	void taste() const
	{
		std::cout << "Pizza with " << m_dough << " dough, "
			<< m_sauce << " sauce and "
			<< m_topping << " topping. Mmmmmmm." << std::endl;
	}
private:
	std::string m_dough;
	std::string m_sauce;
	std::string m_topping;
};
//////////////////////////////////////////////////////////////////////////////////
class Pizza_Bilder
{
public:
	virtual ~Pizza_Bilder() = default;
	Pizza_Product *getPizza()
	{
		return m_pizza.release();
	}
	void createNewPizza()
	{
		m_pizza = std::make_unique<Pizza_Product>();
	}

	virtual void buildDough() = 0;
	virtual void buildSauce() = 0;
	virtual void buildTop() = 0;

protected:
	std::unique_ptr<Pizza_Product> m_pizza;	
};
////////////////////////////////////////////////////////////////////////////////

//конкретные строители
class Margherita_ConcreteBuilder : public Pizza_Bilder
{
public:
	virtual void buildDough() override { m_pizza->setDough("cross"); }
	virtual void buildSauce() override { m_pizza->setSauce("tomato"); }
	virtual void buildTop() override { m_pizza->setTopping("mazzarela+basil"); }
};

class Spicy_ConcreteBuilder : public Pizza_Bilder
{
public:
	virtual void buildDough() override { m_pizza->setDough("pan baked"); }
	virtual void buildSauce() override { m_pizza->setSauce("tomato+chilli"); }
	virtual void buildTop() override { m_pizza->setTopping("pepperoni+salami"); }
};
//////////////////////////////////////////////////////////////////////////////////

class Cook_Director
{
public:
	void tastePizza() { m_pizzaBuilder->getPizza()->taste(); }

	void makePizza(Pizza_Bilder *pb)
	{
		m_pizzaBuilder = pb;
		m_pizzaBuilder->createNewPizza();
		m_pizzaBuilder->buildDough();
		m_pizzaBuilder->buildSauce();
		m_pizzaBuilder->buildTop();
	}
private:
	Pizza_Bilder *m_pizzaBuilder;
};



