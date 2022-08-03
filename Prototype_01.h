#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

/*
Prototype is a creational design pattern that allows cloning objects, even complex ones, without coupling to
their specific classes.

All prototype classes should have a common interface that makes it possible to copy objects even if their
concrete classes are unknown. Prototype objects can produce full copies since objects of the same class
can access each other’s private fields.
*/

enum class Type : size_t
{
	PROTOTYPE_1,
	PROTOTYPE_2
};


class Prototype {
public:
	Prototype(std::string &&rightPrototypeName)
		: m_prototype_name_(rightPrototypeName) {}

	Prototype(const Prototype &) = default;
	virtual ~Prototype() = default;

	//virtual Prototype *Clone() const = 0;
	void Method(const float prototypeField) {
		m_prototype_field_ = prototypeField;
		std::cout << "Call Method from " << m_prototype_name_ << " with field : "
			<< prototypeField << "\n";
	}
	[[nodiscard]] virtual std::unique_ptr<Prototype> clone() const = 0;


protected:
	std::string m_prototype_name_;
	float m_prototype_field_{ 0.0f };
};

/**
 * ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method
 * In this example all data members of Prototype Class are in the Stack. If you
 * have pointers in your properties for ex: String* name_ ,you will need to
 * implement the Copy-Constructor to make sure you have a deep copy from the
 * clone method
 */
class ConcretePrototype1 final : public Prototype
{

public:
	ConcretePrototype1(std::string &&prototypeName, const float concretePrototypeField)
		: Prototype(std::move(prototypeName)), concrete_prototype_field1_(concretePrototypeField) {}

	/**
	 * Notice that Clone method return a Pointer to a new ConcretePrototype1
	 * replica. so, the client (who call the clone method) has the responsability
	 * to free that memory. I you have smart pointer knowledge you may prefer to
	 * use unique_pointer here.
	 */
	[[nodiscard]] std::unique_ptr<Prototype> clone() const override {
		return std::make_unique<ConcretePrototype1>(*this);
	}
private:
	[[maybe_unused]] float concrete_prototype_field1_{ .0f };

};

class ConcretePrototype2 final : public Prototype
{
public:
	ConcretePrototype2(std::string &&prototypeName, const float concretePrototypeField)
		: Prototype(std::move(prototypeName)), concrete_prototype_field2_(concretePrototypeField) {}
	[[nodiscard]] std::unique_ptr<Prototype> clone() const override {
		return std::make_unique<ConcretePrototype2>(*this);
	}
private:
	[[maybe_unused]] float concrete_prototype_field2_{ .0f };

};
/*
 * In PrototypeFactory you have two concrete prototypes, one for each concrete
 * prototype class, so each time you want to create a bullet , you can use the
 * existing ones and clone those.
 */
class PrototypeFactory final {
public:
	PrototypeFactory() {
		m_prototypes_[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1 ", 0.f);
		m_prototypes_[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2 ", 0.f);
	}

	/**
	 * Be carefull of free all memory allocated. Again, if you have smart pointers
	 * knowelege will be better to use it here.
	 */

	 /**
	  * Notice here that you just need to specify the type of the prototype you
	  * want and the method will create from the object with this type.
	  */
	std::unique_ptr<Prototype> createPrototype(const Type type) {
		return m_prototypes_[type]->clone();
	}
private:
	std::unordered_map<Type, std::unique_ptr<Prototype>> m_prototypes_;
};

//main()
#if 0
void Client(PrototypeFactory &prototype_factory) {
	std::cout << "Let's create a Prototype 1\n";

	auto prototype = prototype_factory.createPrototype(Type::PROTOTYPE_1);
	prototype->Method(90);

	std::cout << "\n";
	std::cout << "Let's create a Prototype 2 \n";

	prototype = prototype_factory.createPrototype(Type::PROTOTYPE_2);
	prototype->Method(10);
}

int main() {
	auto Prototype_factory = std::make_unique<PrototypeFactory>();
	Client(*Prototype_factory);

	return 0;
}
#endif

