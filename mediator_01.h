#pragma once

#include <iostream>
#include <memory>
#include <string>

//TITLE: Mediator
/*
 Посредник — это поведенческий паттерн, который упрощает коммуникацию между компонентами системы.
Посредник убирает прямые связи между отдельными компонентами, заставляя их общаться друг
с другом через себя.
Применимость: Пожалуй, самое популярное применение Посредника в C++ коде — это связь нескольких
компонентов GUI одной программы.
 */

class BaseComponent;

class Mediator
{
public:
	Mediator() = default;
	Mediator(Mediator const &) = default;
	Mediator &operator=(Mediator const &) = default;
	Mediator(Mediator &&) noexcept = default;
	Mediator &operator=(Mediator &&) noexcept = default;
	virtual ~Mediator() = default;

	virtual void notify(std::shared_ptr<BaseComponent> sender, std::string event) = 0;
};

//It's stored a weak pointer to Mediator
class BaseComponent
{
public:
	explicit BaseComponent(const std::shared_ptr<Mediator> &mediator = nullptr)
		: m_mediator_(mediator) {}

	void set_mediator(const std::shared_ptr<Mediator> &mediator) {
		m_mediator_ = mediator;
	}
protected:
	std::weak_ptr<Mediator> m_mediator_;
};

//component 1
class Component_1 final : public BaseComponent,
	public std::enable_shared_from_this<Component_1>
{
public:
	void make_up_A() {
		std::cout << "Component_1 make up A.\n";
		//lock() возвращает nullptr(shared_ptr, в котором он содержит nullptr), если объект уже удалили;
		//если нет, то возвращает std::shared_ptr на этот объект
		if (auto tmp = m_mediator_.lock())
			tmp->notify(shared_from_this(), "A"); //this
	}
	void make_up_B() {
		std::cout << "Component_1 make up B.\n";
		if (auto tmp = m_mediator_.lock())
			tmp->notify(shared_from_this(), "B"); //this
	}
};

//component 2
class Component_2 final : public BaseComponent,
	public std::enable_shared_from_this<Component_2>
{
public:
	void make_up_C() {
		std::cout << "Component_2 make up C.\n";
		if (auto tmp = m_mediator_.lock())
			tmp->notify(shared_from_this(), "C"); //this
	}

	void make_up_D() {
		std::cout << "Component_2 make up D.\n";
		if (auto tmp = m_mediator_.lock())
			tmp->notify(shared_from_this(), "D"); //this
	}
};

//It's stored 2 shared pointers to Component_1 and Component_2
class ConcreteMediator final : public Mediator,
	public std::enable_shared_from_this<ConcreteMediator>
{
public:
	ConcreteMediator() = default;

	void set_component_1(std::shared_ptr<Component_1> component_1) {
		m_component_1_ = std::move(component_1);
		m_component_1_->set_mediator(shared_from_this()); //this
	}

	void set_component_2(std::shared_ptr<Component_2> component_2) {
		m_component_2_ = std::move(component_2);
		m_component_2_->set_mediator(shared_from_this()); //this
	}

	void notify(std::shared_ptr<BaseComponent> sender, const std::string event) override {
		if (event == "A") {
			std::cout << "Mediator reacts on A and triggers following operations:\n";
			m_component_2_->make_up_C();
		}
		else if (event == "D") {
			std::cout << "Mediator reacts on D and triggers following operations:\n";
			m_component_1_->make_up_B();
			m_component_2_->make_up_C();
		}
	}
protected:
	std::shared_ptr<Component_1> m_component_1_;
	std::shared_ptr<Component_2> m_component_2_;
};

//main()
#if 0
void clientCode() {
	auto component_1 = std::make_shared<Component_1>();
	auto component_2 = std::make_shared<Component_2>();
	auto concreteMediator = std::make_shared<ConcreteMediator>();
	concreteMediator->set_component_1(component_1);
	concreteMediator->set_component_2(component_2);

	std::cout << "Client triggers operation A.\n";
	component_1->make_up_A();
	std::cout << "\n";
	std::cout << "Client triggers operation D.\n";
	component_2->make_up_D();
}

int main() {
	clientCode();
}
#endif

