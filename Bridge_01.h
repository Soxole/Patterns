#pragma once
#include <memory>
#include <string>

/*
Мост — это структурный паттерн проектирования, который разделяет один или
несколько классов на две отдельные иерархии — абстракцию и реализацию,
позволяя изменять их независимо друг от друга.
 */

class IImplementation
{
public:
	virtual~IImplementation() = default;
	[[nodiscard]] virtual std::string operationImplement() const = 0;
};


class ConcreatImplementA final : public IImplementation
{
public:
	[[nodiscard]] std::string operationImplement() const override {
		return "ConcreteImpA: Here's the result on the platform A.\n";
	}
};

class ConcreatImplementB final : public IImplementation
{
public:
	[[nodiscard]] std::string operationImplement() const override {
		return "ConcreteImpB: Here's the result on the platform B.\n";
	}
};


class Abstraction
{
public:
	Abstraction(std::unique_ptr<IImplementation> _upImpl)
		: m_upImpl(std::move(_upImpl)) {}

	~Abstraction() = default;

	[[nodiscard]] std::string someOperation() const {
		return "Abstraction: Base operation with:\n"
			+ m_upImpl->operationImplement();
	}

protected:
	std::unique_ptr<IImplementation> m_upImpl;
};


class ExtendedAbstr final : public Abstraction
{
public:
	ExtendedAbstr(std::unique_ptr<IImplementation> _upImpl)
		: Abstraction(std::move(_upImpl)) {}

	[[nodiscard]] std::string someOperation() const {
		return "ExtendedAbstr: Extended operation with:\n"
			+ m_upImpl->operationImplement();
	}
};

//main()
#if 0

std::unique_ptr<IImplementation> upImpl{ std::make_unique<ConcreatImplementA>() };
auto upAbstr{ make_unique<Abstraction>(move(upImpl)) };
std::cout << upAbstr->someOperation() << "\n";

upImpl = std::make_unique<ConcreatImplementB>();
upAbstr = std::make_unique<ExtendedAbstr>(move(upImpl));
std::cout << upAbstr->someOperation() << "\n";

#endif
