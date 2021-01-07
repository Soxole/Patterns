#pragma once
#include <memory>

using std::shared_ptr;

/*
Цепочка обязанностей — это поведенческий паттерн проектирования, который позволяет передавать
запросы последовательно по цепочке обработчиков. Каждый последующий обработчик решает,
может ли он обработать запрос сам и стоит ли передавать запрос дальше по цепи.
*/

class IHandler
{
public:
	virtual ~IHandler() = default;
	virtual shared_ptr<IHandler> set_next(shared_ptr<IHandler> handler) = 0;
	virtual std::string handle(std::string request) = 0;
};

class AbstractHandler : public IHandler
{
public:
	AbstractHandler() : m_next_handler(nullptr)
	{
	}
	shared_ptr<IHandler> set_next(shared_ptr<IHandler> handler) override {
		m_next_handler = handler;

		return m_next_handler;
	}

	[[nodiscard]] std::string handle(std::string request) override {
		if (m_next_handler)
			return m_next_handler->handle(request);

		return "";
	}

private:
	shared_ptr<IHandler> m_next_handler;
};
//concrete handler #1
class MonkeyHandler : public AbstractHandler
{
public:

	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "Banana")
			return "Monkey: I'll eat the " + request + ".\n";

		return AbstractHandler::handle(request);
	}
};
//concrete handler #2
class SquirreHandler : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "Nut")
			return "Squirrel: I'll eat the " + request + ".\n";

		return AbstractHandler::handle(request);
	}
};
//concrete handler #3
class DogHandler final : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "MeatBall")
			return "Dog: I'll eat the " + request + ".\n";

		return AbstractHandler::handle(request);
	}
};

/*
void clientCode(IHandler &handler)
{
	vector food{ "Nut", "Banana", "Cup of coffee" };
	for (const auto &it : food) {
		cout << "Client: Who wants a " << it << "?\n";
		const string res = handler.handle(it);
		if (!res.empty())
		{
			cout << " " << res;
		}
		else
			cout << " " << it << " was left untouched.\n";
	}
}

int main()
{
	auto monkey = make_unique<MonkeyHandler>();
	auto squirrel = make_shared<SquirreHandler>();
	auto dog = make_unique<DogHandler>();
	monkey->setNext(squirrel);

	cout << "Chain: Monkey > Squirrel > Dog\n\n";
	clientCode(*monkey);
	cout << "\n";
	cout << "Subchain: Squirrel > Dog\n\n";
	clientCode(*squirrel);
}

*/