#pragma once
#include <iostream>
#include <memory>
#include <string>

//TITLE: Mediator

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
	virtual void notify(std::shared_ptr<BaseComponent> sender, std::string event) = 0;
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
class Component_1 : public BaseComponent, public std::enable_shared_from_this<Component_1>
{
public:

	std::shared_ptr<Component_1> set_component()
	{
		auto tmp_component = std::make_shared<Component_1>();
		return shared_from_this();
	}

	void make_up_A()
	{
		std::cout << "Component 1 make up A.\n";
		this->m_mediator_->notify(set_component(), "A"); //this
	}
	void make_up_B()
	{
		std::cout << "Component 1 make up B.\n";
		this->m_mediator_->notify(set_component(), "B"); //this
	}
};

//component 2
class Component_2 final : public BaseComponent, public std::enable_shared_from_this<Component_2>
{
public:
	std::shared_ptr<Component_2> set_component()
	{
		auto tmp_component = std::make_shared<Component_2>();
		return shared_from_this();
	}

	void make_up_C()
	{
		std::cout << "Component 2 make up C.\n";
		this->m_mediator_->notify(set_component(), "C"); //this
	}

	void make_up_D()
	{
		std::cout << "Component 2 make up D.\n";
		this->m_mediator_->notify(set_component(), "D"); //this
	}
};

//хранит 2 указателя на Component_1 and Component_2
class ConcreteMediator : public Mediator, public std::enable_shared_from_this<ConcreteMediator>
{
public:
	ConcreteMediator() = default;
	
	//explicit ConcreteMediator(std::shared_ptr<Component_1> component_1, std::shared_ptr<Component_2> component_2)
	//	: m_component_1_(component_1), m_component_2_(component_2)
	//{
	//	//Любая попытка вызова shared_from_this из конструктора приведет к bad_weak_ptr исключению.
	//	m_component_1_->set_mediator(this); //this
	//	m_component_2_->set_mediator(this); //this
	//	
	//}
	
	void set_component_1(std::shared_ptr<Component_1> sp)
	{
		m_component_1_ = std::move(sp);
		this->m_component_1_->set_mediator(shared_from_this());
	}

	void set_component_2(std::shared_ptr<Component_2> sp2)
	{
		m_component_2_ = std::move(sp2);
		m_component_2_->set_mediator(shared_from_this());
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
}
 */