#pragma once
#include <string>
#include <memory>

class I_Product
{
public:
	virtual ~I_Product() = default;
	virtual std::string lineOperation() const = 0;
};

class ConcreteProduct_1 : public I_Product
{
public:
	[[nodiscard]] std::string lineOperation() const override
	{
		return "Result of the ConcreteProduct_1";
	}
};

class ConcreteProduct_2 final : public I_Product
{
public:
	[[nodiscard]] std::string lineOperation() const override
	{
		return "Result of the ConcreteProduct_2";
	}
};

class Creator
{
public:
	virtual ~Creator() = default;
	virtual std::unique_ptr<I_Product> factoryMethod() const = 0;

	[[nodiscard]] std::string someOperation() const
	{
		const auto product = this->factoryMethod();
		auto result = "Creator: The same creator's code " + product->lineOperation();

		return result;
	}
};

class ConcreteCreator_1 : public Creator
{
public:
	[[nodiscard]] std::unique_ptr<I_Product> factoryMethod() const override
	{
		return std::make_unique<ConcreteProduct_1>();
	}
};

class ConcreteCreator_2 final : public Creator
{
public:
	[[nodiscard]] std::unique_ptr<I_Product> factoryMethod() const override
	{
		return std::make_unique<ConcreteProduct_2>();
	}
};

/*
 void clientCode(const Creator &creator) {
	std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
		<< creator.someOperation() << std::endl;
}

	const unique_ptr<Creator> creator{ make_unique<ConcreteCreator_1>() };
	clientCode(*creator);
	const unique_ptr<Creator> creatorTwo{ make_unique<ConcreteCreator_1>() };
	clientCode(*creatorTwo);
*/