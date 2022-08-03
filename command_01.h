#pragma once
#include <iostream>
#include <string>

/*
Команда — это поведенческий паттерн, позволяющий заворачивать запросы или
простые операции в отдельные объекты.
Это позволяет откладывать выполнение команд, выстраивать их в очереди,
а также хранить историю и делать отмену.
 */



 //interface
class ICommand
{
public:
	ICommand() = default;
	ICommand(ICommand const &) = default;
	ICommand &operator=(ICommand const &) = default;
	ICommand(ICommand &&) noexcept = default;
	ICommand &operator=(ICommand &&) noexcept = default;
	virtual ~ICommand() = default;

	virtual void execute() const = 0;
};

//a simple command
class SimpleCommand final : public ICommand
{
public:
	explicit SimpleCommand(std::string &&pay_load)
		: m_pay_load(std::move(pay_load)) {}

	void execute() const override {
		std::cout << "SimpleCommand: See, I can do simple things like printing ("
			<< m_pay_load << ")\n";
	}
private:
	std::string m_pay_load;
};

//receiver: the function with output 
class Receiver final
{
public:
	void doSomething(const std::string_view a) const {
		std::cout << "Receiver: Working on (" << a << ".)\n";
	}
	void doSomethingElse(const std::string_view b) const {
		std::cout << "Receiver: Also working on (" << b << ".)\n";
	}
};

class ComplexCommand final : public ICommand
{
public:
	ComplexCommand(std::unique_ptr<Receiver> receiver, std::string &&a, std::string &&b)
		: m_receiver_(std::move(receiver)), m_a(std::move(a)),
		m_b(std::move(b)) {}

	void execute() const override {
		std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
		m_receiver_->doSomething(m_a);
		m_receiver_->doSomethingElse(m_b);
	}
private:
	std::unique_ptr<Receiver> m_receiver_;
	std::string m_a;
	std::string m_b;
};

class Invoker final
{
public:
	void set_on_start(std::unique_ptr<ICommand> command) {
		m_on_start_ = std::move(command);
	}
	void set_on_finish(std::unique_ptr<ICommand> command) {
		m_on_finish_ = std::move(command);
	}

	void do_something_important() const {
		std::cout << "Invoker: Does anybody want something done before I begin?\n";
		if (m_on_start_) {
			m_on_start_->execute();
		}
		std::cout << "Invoker: ...doing something really important...\n";
		std::cout << "Invoker: Does anybody want something done after I finish?\n";
		if (m_on_finish_) {
			m_on_finish_->execute();
		}
	}
private:
	std::unique_ptr<ICommand> m_on_start_;
	std::unique_ptr<ICommand> m_on_finish_;
};


//main()
#if 0

const auto invoker_main = std::make_unique<Invoker>();
invoker_main->set_on_start(std::make_unique<SimpleCommand>("Say Hi"));
auto receiver_main = std::unique_ptr<Receiver>();
invoker_main->set_on_finish(std::make_unique<ComplexCommand>(move(receiver_main),
	"Send email", "Save report"));
invoker_main->do_something_important();

#endif
