#pragma once
#include <memory>
#include <string>



/*
Декоратор — это структурный паттерн проектирования, который позволяет динамически добавлять объектам
новую функциональность, оборачивая их в полезные «обёртки».
*/


class IComponent
{
public:
	virtual ~IComponent() = default;
	[[nodiscard]] virtual std::string operation() const = 0;
};


class ConcreteComponent final : public IComponent
{
public:
	[[nodiscard]] std::string operation() const override {
		return "ConcreteComponent";
	}
};

class Decorator : public IComponent
{
protected:
	std::unique_ptr<IComponent> m_component;
public:
	Decorator(std::unique_ptr<IComponent> component)
		: m_component(std::move(component)) {}

	[[nodiscard]] std::string operation() const override {
		return m_component->operation();
	}
};

class ConcreteDecorator_A final : public Decorator
{
public:
	ConcreteDecorator_A(std::unique_ptr<IComponent> component)
		: Decorator(std::move(component)) {}

	[[nodiscard]] std::string operation() const override {
		return "ConcreteDecorator_A(" + Decorator::operation() + ")";
	}
};

class ConcreteDecorator_B final : public Decorator
{
public:
	ConcreteDecorator_B(std::unique_ptr<IComponent> component)
		: Decorator(std::move(component)) {}
	[[nodiscard]] std::string operation() const override {
		return "ConcreteDecorator_B(" + Decorator::operation() + ")";
	}
};


//main()
#if 0
	void clientCode(const std::unique_ptr<IComponent> component) {
		std::cout << "Result: " << component->operation();
	}

	std::unique_ptr<IComponent> simple =
		std::make_unique<ConcreteComponent>();
	std::cout << "Client: I've got a simple component:\n";
	std::cout << simple->operation() << "\n";
	std::cout << "\n\n";
	//--example 01
	std::unique_ptr<IComponent> decorator_01 =
		std::make_unique<ConcreteDecorator_A>(std::move(simple));
	//clientCode(std::move(decorator_01));

	std::unique_ptr<IComponent> decorator_02 =
		std::make_unique<ConcreteDecorator_B>(
			std::make_unique<Decorator>(std::move(decorator_01)));
	std::cout << "Client: Now I've got a decorated component:\n";

	//Result: ConcreteDecorator_B(ConcreteDecorator_A(ConcreteComponent))
	clientCode(std::move(decorator_02));


	//--example 02
  //  std::unique_ptr<IComponent> decorator_03{ make_unique<ConcreteDecorator_A>(
		//make_unique<ConcreteDecorator_B>(
		//	std::make_unique<ConcreteComponent>())) };
	//--example 03
		//unique_ptr<IComponent> decorator_03{ make_unique<Decorator>(
		//	make_unique<ConcreteDecorator_A>(
		//		make_unique<ConcreteDecorator_B>(
		//			make_unique<ConcreteComponent>()))) };

	//std::cout << decorator_03->operation() << "\n";
#endif
