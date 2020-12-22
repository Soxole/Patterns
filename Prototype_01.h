#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// Паттерн Прототип
//
// Назначение: Позволяет копировать объекты, не вдаваясь в подробности их реализации.

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;


enum class Type : size_t
{
	PROTOTYPE_1,
	PROTOTYPE_2
};

/**
 * Пример класса, имеющего возможность клонирования. Мы посмотрим как происходит
 * клонирование значений полей разных типов.
 */

class Prototype {
public:
	Prototype() = default;
	Prototype(const string &right_prototype_name)
		: m_prototypeName(right_prototype_name), m_prototypeField(0.0f)
	{
	}
	virtual ~Prototype() = default;
	//virtual Prototype *Clone() const = 0;
	void Method(const float &prototype_field) 
	{
		m_prototypeField = prototype_field;
		std::cout << "Call Method from " << m_prototypeName << " with field : " << prototype_field << "\n";
	}
	virtual std::unique_ptr<Prototype> Clone() const = 0;


protected:
	string m_prototypeName{};
	float m_prototypeField{0.0f};
};

/**
 * ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method
 * In this example all data members of Prototype Class are in the Stack. If you
 * have pointers in your properties for ex: String* name_ ,you will need to
 * implement the Copy-Constructor to make sure you have a deep copy from the
 * clone method
 */
class ConcretePrototype1 : public Prototype 
{
	
public:
	ConcretePrototype1(const string &prototype_name, const float &concrete_prototype_field)
		: Prototype(prototype_name), concrete_prototype_field1_(concrete_prototype_field)
	{
	}

	/**
	 * Notice that Clone method return a Pointer to a new ConcretePrototype1
	 * replica. so, the client (who call the clone method) has the responsability
	 * to free that memory. I you have smart pointer knowledge you may prefer to
	 * use unique_pointer here.
	 */
	[[nodiscard]] std::unique_ptr<Prototype> Clone() const noexcept override 
	{
		return std::make_unique<ConcretePrototype1>(*this);
	}
private:
	[[maybe_unused]] float concrete_prototype_field1_{0.f};

};

class ConcretePrototype2 final : public Prototype 
{
public:
	ConcretePrototype2(const string &prototype_name, const float &concrete_prototype_field)
		: Prototype(prototype_name), concrete_prototype_field2_(concrete_prototype_field) 
	{
	}
	[[nodiscard]] std::unique_ptr<Prototype> Clone() const noexcept override  
	{
		return std::make_unique<ConcretePrototype2>(*this);
	}
private:
	[[maybe_unused]] float concrete_prototype_field2_{0.f};

};
/*
 * In PrototypeFactory you have two concrete prototypes, one for each concrete
 * prototype class, so each time you want to create a bullet , you can use the
 * existing ones and clone those.
 */
class PrototypeFactory {
public:
	~PrototypeFactory() = default;

	PrototypeFactory()
	{
		m_prototypes[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1 ", 50.f);
		m_prototypes[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2 ", 60.f);
	}

	/**
	 * Be carefull of free all memory allocated. Again, if you have smart pointers
	 * knowelege will be better to use it here.
	 */

	/**
	 * Notice here that you just need to specify the type of the prototype you
	 * want and the method will create from the object with this type.
	 */
	std::unique_ptr<Prototype> CreatePrototype(const Type type)
	{
		return m_prototypes[type]->Clone();
	}
private:
	std::unordered_map<Type, std::unique_ptr<Prototype>> m_prototypes;
};


/*
void Client(PrototypeFactory &prototype_factory) 
{
	std::cout << "Let's create a Prototype 1\n";

	auto prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
	prototype->Method(90);

	std::cout << "\n";
	std::cout << "Let's create a Prototype 2 \n";

	prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
	prototype->Method(10);
}

int main()
{
	auto Prototype_factory = make_unique<PrototypeFactory>();
    Client(*Prototype_factory);

    return 0;
}
*/