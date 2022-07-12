#pragma once
#include <memory>
#include <string>

/*
Цепочка обязанностей — это поведенческий паттерн, позволяющий передавать запрос
по цепочке потенциальных обработчиков, пока один из них не обработает запрос.
*/

class IHandler
{
public:
	IHandler() = default;
	IHandler(const IHandler &) = default;
	IHandler &operator=(const IHandler &) = default;
	IHandler(IHandler &&) noexcept = default;
	IHandler &operator=(IHandler &&) noexcept = default;
	virtual ~IHandler() = default;

	virtual std::shared_ptr<IHandler> set_next(std::shared_ptr<IHandler> handler) = 0;
	virtual std::string handle(std::string request) = 0;
};

class AbstractHandler : public IHandler
{
public:
	AbstractHandler() : m_next_handler(nullptr) { }

	std::shared_ptr<IHandler> set_next(std::shared_ptr<IHandler> handler) override {
		m_next_handler = handler;
		return m_next_handler;
	}

	[[nodiscard]] std::string handle(std::string request) override {
		if (m_next_handler)
			return m_next_handler->handle(request);
		return "";
	}
private:
	std::shared_ptr<IHandler> m_next_handler;
};

//concrete handler #1
class MonkeyHandler final : public AbstractHandler
{
public:
	[[nodiscard]] std::string handle(std::string request) override {
		if (request == "Banana")
			return "Monkey: I'll eat the " + request + ".\n";
		return AbstractHandler::handle(request);
	}
};

//concrete handler #2
class SquirrelHandler final : public AbstractHandler
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

//main()
#if 0

void clientCode(IHandler &handler) {
	std::vector food{ "Nut", "Banana", "Cup of coffee" };
	for (const auto &it : food) {
		std::cout << "Client: Who wants a " << it << "?\n";
		const std::string res = handler.handle(it);
		if (!res.empty()) {
			std::cout << " " << res;
		}
		else
			std::cout << " " << it << " was left untouched.\n";
	}
}

int main()
{
	auto monkey = std::make_unique<MonkeyHandler>();
	auto squirrel = std::make_shared<SquirrelHandler>();
	auto dog = std::make_unique<DogHandler>();
	monkey->set_next(squirrel);

	std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
	clientCode(*monkey);
	std::cout << "\n";
	std::cout << "Subchain: Squirrel > Dog\n\n";
	clientCode(*squirrel);
}

#endif
