#pragma once
#include <memory>
#include <string>



/*
Декоратор — это структурный паттерн, который позволяет добавлять объектам новые поведения на лету,
помещая их в объекты-обёртки.
Декоратор позволяет оборачивать объекты бесчисленное количество раз благодаря тому, что и обёртки,
и реальные оборачиваемые объекты имеют общий интерфейс.
*/



/**
 * Базовый интерфейс Компонента определяет поведение, которое изменяется
 * декораторами.
 */
class IComponent
{
public:
	virtual ~IComponent() = default;
	[[nodiscard]] virtual std::string operation() const = 0;
};

/**
 * Конкретные Компоненты предоставляют реализации поведения по умолчанию. Может
 * быть несколько вариаций этих классов.
 */
class ConcreteComponent : public IComponent
{
public:
	[[nodiscard]] std::string operation() const override
	{
		return "ConcreteComponent";
	}
};

/**
 * Базовый класс Декоратора следует тому же интерфейсу, что и другие компоненты.
 * Основная цель этого класса - определить интерфейс обёртки для всех конкретных
 * декораторов. Реализация кода обёртки по умолчанию может включать в себя поле
 * для хранения завёрнутого компонента и средства его инициализации.
 */
class Decorator : public IComponent
{
protected:
	std::unique_ptr<IComponent> m_component;

public:
	Decorator(std::unique_ptr<IComponent> component)
		:m_component(std::move(component)) 
	{ 
	}

	[[nodiscard]] std::string operation() const override
	{
		return m_component->operation();
	}
};

/**
 * Конкретные Декораторы вызывают обёрнутый объект и изменяют его результат некоторым образом.
 */
class ConcreteDecorator_A : public Decorator
{
public:
	ConcreteDecorator_A(std::unique_ptr<IComponent> component)
		:Decorator(std::move(component))
	{
	}

	[[nodiscard]] std::string operation() const override
	{
		return "ConcreteDecorator_A(" + Decorator::operation() + ")";
	}
};

class ConcreteDecorator_B final : public Decorator
{
public:
	ConcreteDecorator_B(std::unique_ptr<IComponent> component)
		:Decorator(std::move(component)) 
	{ 
	}
	[[nodiscard]] std::string operation() const override
	{
		return "ConcreteDecorator_B(" + Decorator::operation() + ")";
	}
};


/*
 void clientCode(const unique_ptr<IComponent> component)
{
	cout << "Result: " << component->operation();
}

	unique_ptr<IComponent> simple = make_unique<ConcreteComponent>();
	std::cout << "Client: I've got a simple component:\n";
	cout << simple->operation() << "\n";
	cout << "\n\n";
	 //--example 01
	unique_ptr<IComponent> decorator_01 = make_unique<ConcreteDecorator_A>(make_unique<Decorator>(move(simple)));
	//decorator_01->operation();
	unique_ptr<IComponent> decorator_02 = make_unique<ConcreteDecorator_B>(make_unique<Decorator>(move(decorator_01)));
	std::cout << "Client: Now I've got a decorated component:\n";

	//cout << decorator_01->operation() << "\n";
	cout << decorator_02->operation() << "\n";

	//--example 02
		unique_ptr<IComponent> decorator_03{ make_unique<ConcreteDecorator_A>(
			make_unique<ConcreteDecorator_B>(
					make_unique<ConcreteComponent>())) };
	//--example 03
		//unique_ptr<IComponent> decorator_03{ make_unique<Decorator>(
		//	make_unique<ConcreteDecorator_A>(
		//		make_unique<ConcreteDecorator_B>(
		//			make_unique<ConcreteComponent>()))) };

	cout << decorator_03->operation() << "\n";
 */