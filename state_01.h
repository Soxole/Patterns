#pragma once
#include <iostream>
#include <memory>
#include <typeinfo>


//TITLE: State
/*
Состояние — это поведенческий паттерн проектирования, который позволяет объектам менять поведение в зависимости от своего состояния.
Извне создаётся впечатление, что изменился класс объекта.
 */

class Context;

//class State is stored a smart pointer to <Context> 
class State
{
protected:
	std::shared_ptr<Context> m_context_;
public:
	virtual ~State() = default;

	virtual void handle1() = 0;
	virtual void handle2() = 0;

	//this method passes the formed classes of <Context> to a pointer m_context_
	void set_context(std::shared_ptr<Context> context)
	{
		m_context_ = std::move(context);
	}
};

//class Context is stored a smart pointer to <State>
class Context : public std::enable_shared_from_this<Context>
{
private:
	std::shared_ptr<State> m_state_;
public:
	Context() : m_state_(nullptr)
	{ }
	~Context() = default;

	void transition_to(const std::shared_ptr<State> &state)
	{
		std::cout << "Context: transition to " << typeid(*state).name() << ".\n"; //typeid.name()
		m_state_ = state;
		m_state_->set_context(shared_from_this()); //this
	}

	void request_1() const
	{
		m_state_->handle1();
	}
	void request_2() const
	{
		m_state_->handle2();
	}
};

//State A creates the state B through the call m_context_->transition_to
class ConcreteState_A : public State
{
public:
	ConcreteState_A() = default;
	void handle1() override; //this method is defined below; 

	void handle2() override
	{
		std::cout << "ConcreteStateA handles request2.\n";
	}
};
//State B creates the state A through the call m_context_->transition_to
class ConcreteState_B : public State
{
public:
	ConcreteState_B() = default;
	void handle1() override
	{
		std::cout << "ConcreteStateB handles request1.\n";
	}
	void handle2() override
	{
		std::cout << "ConcreteStateB handles request2.\n";
		std::cout << "ConcreteStateB wants to change the state of the context.\n";
		m_context_->transition_to(std::make_shared<ConcreteState_A>());
	}
};
inline void ConcreteState_A::handle1()
{
	std::cout << "ConcreteStateA handles request1.\n";
	std::cout << "ConcreteStateA wants to change the state of the context.\n";
	m_context_->transition_to(std::make_shared<ConcreteState_B>());
}

/*
void clientCode()
{
	auto main_context{std::make_shared<Context>()};
	main_context->transition_to(std::make_shared<ConcreteState_A>());
	main_context->request_1();
	main_context->request_2();
}

main()
{
	clientCode();
}
 */
