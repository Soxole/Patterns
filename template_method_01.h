#pragma once
#include <iostream>

//TITLE: template method
/*
Шаблонный метод — это поведенческий паттерн проектирования, который определяет
скелет алгоритма, перекладывая ответственность за некоторые его шаги на подклассы.
Паттерн позволяет подклассам переопределять шаги алгоритма, не меняя его общей структуры

минусы:
-Вы жёстко ограничены скелетом существующего алгоритма.
-Вы можете нарушить принцип подстановки Барбары Лисков, изменяя базовое поведение
одного из шагов алгоритма через подкласс.
-С ростом количества шагов шаблонный метод становится слишком сложно поддерживать.
 */

class ITemplate
{
public:
	ITemplate() = default;
	ITemplate(ITemplate const &) = default;
	ITemplate &operator=(ITemplate const &) = default;
	ITemplate(ITemplate &&) noexcept = default;
	ITemplate &operator=(ITemplate &&) noexcept = default;
	virtual ~ITemplate() = default;

	void TemplateMethod() const {
		BaseOperation1();
		RequiredOperations1();
		BaseOperation2();
		Hook1();
		RequiredOperation2();
		BaseOperation3();
		Hook2();
	}
protected:
	void BaseOperation1() const {
		std::cout << "ITemplate says: I am doing the bulk of the work\n";
	}
	void BaseOperation2() const {
		std::cout << "ITemplate says: But I let subclasses override some operations\n";
	}
	void BaseOperation3() const {
		std::cout << "ITemplate says: But I am doing the bulk of the work anyway\n";
	}

	virtual void RequiredOperations1() const = 0;
	virtual void RequiredOperation2() const = 0;
	virtual void Hook1() const {}
	virtual void Hook2() const {}
};

class ConcreteTemplate_1 final : public ITemplate
{
protected:
	void RequiredOperations1() const override {
		std::cout << "ConcreteTemplate_1 says: Implemented Operation1\n";
	}
	void RequiredOperation2() const override {
		std::cout << "ConcreteTemplate_1 says: Implemented Operation2\n";
	}
};

class ConcreteTemplate_2 final : public ITemplate
{
protected:
	void RequiredOperations1() const override {
		std::cout << "ConcreteTemplate_2 says: Implemented Operation1\n";
	}
	void RequiredOperation2() const override {
		std::cout << "ConcreteTemplate_2 says: Implemented Operation2\n";
	}
	void Hook1() const override {
		std::cout << "ConcreteTemplate_2 says: Overridden Hook1\n";
	}
};

//main()
#if 0
void client_code(std::unique_ptr<ITemplate> obj)
{
	obj->TemplateMethod();
}
int main()
{
	std::cout << "Same client code can work with different subclasses:\n";
	auto concrete_class_one = std::make_unique<ConcreteTemplate_1>();
	client_code(std::move(concrete_class_one));
	std::cout << '\n' << "Same client code can work with different subclasses:\n";
	auto concrete_class_two = std::make_unique<ConcreteTemplate_2>();
	client_code(std::move(concrete_class_two));
}
#endif
