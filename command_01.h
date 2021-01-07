// ReSharper disable CppInconsistentNaming
#pragma once
#include <iostream>
#include <string>

/*
	Команда — это поведенческий паттерн, позволяющий заворачивать запросы или простые операции в отдельные объекты.
	Используйте паттерн Command если:
		Система управляется событиями. При появлении такого события (запроса) необходимо выполнить определенную последовательность действий.
		Необходимо параметризировать объекты выполняемым действием, ставить запросы в очередь или поддерживать операции отмены (undo) и
		повтора (redo) действий.
		Нужен объектно-ориентированный аналог функции обратного вызова в процедурном программировании.

 */



//interface
class Command_i
{
public:
	virtual ~Command_i() = default;
	virtual void execute() const = 0;
};

//a simple command
class SimpleCommand : public Command_i
{
public:
	explicit SimpleCommand(std::string &&pay_load) : m_pay_load(std::forward<std::string>(pay_load))
	{
	}
	void execute() const override
	{
		std::cout << "SimpleCommand: See, I can do simple things like printing (" << m_pay_load << ")\n";
	}

private:
	std::string m_pay_load;
};

//receiver: the function with output 
class Receiver
{
public:
	void doSomething(const std::string_view a) const
	{
		std::cout << "Receiver: Working on (" << a << ".)\n";
	}
};

//a big command: 1 pointer to the Receiver and two strings (a, b)
class ComplexCommand : public Command_i
{
public:
	ComplexCommand(std::unique_ptr<Receiver> receiver, std::string &&a, std::string &&b)
		: m_receiver_(std::move(receiver)), m_a(std::forward<std::string>(a)), m_b(std::forward<std::string>(b))
	{
	}
	void execute() const override
	{
		std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
		m_receiver_->doSomething(m_a);
		m_receiver_->doSomething(m_b);
	}
private:
	std::unique_ptr<Receiver> m_receiver_;
	std::string m_a;
	std::string m_b;
};

//invoker: 2 pointers to the class Command_i
class Invoker
{
public:
	~Invoker() = default;

	//the func receives a smart pointer <SimpleCommand> and <ComplexCommand>; <Command_i> = <SimpleCommand> 
	void set_on_start(std::unique_ptr<Command_i> command)
	{
		m_on_start_ = std::move(command);
	}

	void set_on_finish(std::unique_ptr<Command_i> command)
	{
		m_on_finish_ = std::move(command);
	}

	void do_something_important() const
	{
		std::cout << "Invoker: Does anybody want something done before I begin?\n";
		if (m_on_start_)
		{
			m_on_start_->execute();
		}
		std::cout << "Invoker: ...doing something really important...\n";
		std::cout << "Invoker: Does anybody want something done after I finish?\n";
		if (m_on_finish_)
		{
			m_on_finish_->execute();
		}
	}

private:
	std::unique_ptr<Command_i> m_on_start_;
	std::unique_ptr<Command_i> m_on_finish_;
};

/*
  	auto invoker_main = make_unique<Invoker>();
	invoker_main->set_on_start(make_unique<SimpleCommand>("Say Hi"));
	auto receiver_main = unique_ptr<Receiver>();
	invoker_main->set_on_finish(make_unique<ComplexCommand>(move(receiver_main), 
		"Send email", "Save report"));
	invoker_main->do_something_important();

 */