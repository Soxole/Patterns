#pragma once
#include <iostream>
#include <memory>
#include <string>

//TITLE: Mediator
//TODO don't solve. HZ what happens
/*
Паттерн Mediator определяет объект, управляющий набором взаимодействующих объектов. Слабая связанность достигается
благодаря тому, что вместо непосредственного взаимодействия друг с другом коллеги общаются через объект-посредник.
Башня управления полетами в аэропорту хорошо демонстрирует этот паттерн.



 */

class BaseComponent;

class Mediator
{
public:
	virtual ~Mediator() = default;
	virtual void notify(std::shared_ptr<BaseComponent> sender, const std::string event) = 0;
};

//хранит указатель на mediator
class BaseComponent
{
public:
	~BaseComponent() = default;
	explicit BaseComponent(std::shared_ptr<Mediator> mediator = nullptr)
		: m_mediator_(std::move(mediator))
	{
	}

	void set_mediator(std::shared_ptr<Mediator> mediator)
	{
		this->m_mediator_ = std::move(mediator);
	}
protected:
	std::shared_ptr<Mediator> m_mediator_;
};

//component 1
class Component_1 : BaseComponent
{
public:

	void make_up_A()const
	{
		std::cout << "Component 1 make up A.\n";
		this->m_mediator_->notify(std::make_shared<BaseComponent>(), "A");
	}
	void make_up_B()const
	{
		std::cout << "Component 1 make up B.\n";
		this->m_mediator_->notify(std::shared_ptr<BaseComponent>(), "B");
	}
};

//component 2
class Component_2 final : public BaseComponent
{
public:
	void make_up_C()const
	{
		std::cout << "Component 2 make up C.\n";
		m_mediator_->notify(std::shared_ptr<BaseComponent>(), "C");
	}
	void make_up_D()const
	{
		std::cout << "Component 2 make up D.\n";
		m_mediator_->notify(std::shared_ptr<BaseComponent>(), "D");
	}
};

//хранит 2 указателя на Component
class ConcreteMediator : public Mediator
{
public:
	explicit ConcreteMediator(std::shared_ptr<Component_1> component_1, std::shared_ptr<Component_2> component_2)
		: m_component_1_(std::move(component_1)), m_component_2_(std::move(component_2))
	{
		this->m_component_1_->set_mediator(std::shared_ptr<Mediator>(std::make_shared<Mediator>()));
		m_component_2_->set_mediator(std::make_shared<Mediator>());
	}

	void notify(std::shared_ptr<BaseComponent> sender, const std::string event) override
	{
		if (event == "A")
		{
			std::cout << "Mediator reacts on A and triggers following operations:\n";
			m_component_2_->make_up_C();
		}
		if (event == "D")
		{
			std::cout << "Mediator reacts on D and triggers following operations:\n";
			m_component_1_->make_up_B();
			m_component_2_->make_up_C();
		}
	}
protected:
	std::shared_ptr<Component_1> m_component_1_;
	std::shared_ptr<Component_2> m_component_2_;
};

/*
 void clientCode()
{
	auto component_1 = make_shared<Component_1>();
	auto component_2 = make_shared<Component_2>();
	auto concreteMediator = make_shared<ConcreteMediator>(component_1, component_2);
	std::cout << "Client triggers operation A.\n";
	component_1->make_up_A();
	std::cout << "\n";
	std::cout << "Client triggers operation D.\n";
	component_2->make_up_D();
}

int main()
{
	clientCode();

 */