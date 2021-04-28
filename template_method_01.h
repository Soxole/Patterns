#pragma once
#include <iostream>


/*
 Ўаблонный метод Ч это поведенческий паттерн проектировани€, который определ€ет скелет алгоритма,
 перекладыва€ ответственность за некоторые его шаги на подклассы. ѕаттерн позвол€ет подклассам
 переопредел€ть шаги алгоритма, не мен€€ его общей структуры.
 */

class AbstractClass
{
protected:
	void BaseOperation1() const {
		std::cout << "AbstractClass says: I am doing the bulk of the work\n";
	}
	void BaseOperation2() const {
		std::cout << "AbstractClass says: But I let subclasses override some operations\n";
	}
	void BaseOperation3() const {
		std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
	}

	virtual void RequiredOperations1() const = 0;
	virtual void RequiredOperation2() const = 0;
	//’уки предоставл€ют дополнительные точки расширени€ в некоторых критических местах алгоритма.
	virtual void Hook1() const {}
	virtual void Hook2() const {}

public:
	virtual ~AbstractClass() = default;
	void TemplateMethod() const				//template method
	{
		this->BaseOperation1();
		this->RequiredOperations1();
		this->BaseOperation2();
		this->Hook1();
		this->RequiredOperation2();
		this->BaseOperation3();
		this->Hook2();
	}
};

class ConcreteClass_1 : public AbstractClass
{
protected:
	void RequiredOperations1() const override {
		std::cout << "ConcreteClass1 says: Implemented Operation1\n";
	}
	void RequiredOperation2() const override {
		std::cout << "ConcreteClass1 says: Implemented Operation2\n";
	}
};

class ConcreteClass_2 final : public AbstractClass
{
protected:
	void RequiredOperations1() const override {
		std::cout << "ConcreteClass2 says: Implemented Operation1\n";
	}
	void RequiredOperation2() const override {
		std::cout << "ConcreteClass2 says: Implemented Operation2\n";
	}
	void Hook1() const override {
		std::cout << "ConcreteClass2 says: Overridden Hook1\n";
	}
};

/*
void client_code(unique_ptr<AbstractClass> const obj)
{
	obj->TemplateMethod();
}
int main()
{
	std::cout << "Same client code can work with different subclasses:\n";
	auto concrete_class_one = make_unique<ConcreteClass_1>();
	client_code(move(concrete_class_one));
	std::cout << '\n' << "Same client code can work with different subclasses:\n";
	auto concrete_class_two = make_unique<ConcreteClass_2>();
	client_code(move(concrete_class_two));
}
*/