#pragma once
#include <memory>
#include <iostream>

using std::shared_ptr;

class IHandler
{
public:
	virtual shared_ptr<IHandler> setNext(shared_ptr<IHandler> Handler) = 0;
	virtual std::string handle(std::string request) = 0;
};

class AbstractHandler : public IHandler
{
public:
	AbstractHandler() : m_next_handler(nullptr)
	{
	}
	[[nodiscard]] shared_ptr<IHandler> setNext(shared_ptr<IHandler> handler) override {
		m_next_handler = handler;

		return handler;
	}

	[[nodiscard]] std::string handle(std::string request) override {
		if (m_next_handler)
			return m_next_handler->handle(request);

		return {};
	}

private:
	shared_ptr<IHandler> m_next_handler;
};

class MonkeyHandler : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "Banana")
			return "Monkey: I'll eat the " + request + ".\n";
		else
			return AbstractHandler::handle(request);
	}
};

class SquirreHandler : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "Nut")
			return "Squirrel: I'll eat the " + request + ".\n";
		else
			return AbstractHandler::handle(request);
	}
};

class DogHandler : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "MeatBall")
			return "Dog: I'll eat the " + request + ".\n";
		else
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