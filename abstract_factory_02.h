#pragma once

#include<iostream>
#include<memory>
#include<string>	


class AbstractProduct_A
{
public:
	virtual~AbstractProduct_A() = default;
	virtual std::string useFulFunction_A() const = 0;
};

class ConcreateProduct_A1 : public AbstractProduct_A
{
public:
	[[nodiscard]] std::string useFulFunction_A() const override {
		return "The result of the product A1.";
	}
};

class ConcreateProduct_A2 : public AbstractProduct_A
{
public:
	[[nodiscard]] std::string useFulFunction_A() const override {
		return "The result of the product A2.";
	}
};

class AbstractProduct_B
{
public:
	virtual~AbstractProduct_B() = default;
	virtual std::string useFulFunction_B() const = 0;
	virtual std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const = 0;
};

class ConcreateProduct_B1 : public AbstractProduct_B
{
public:
	[[nodiscard]] std::string useFulFunction_B() const override {
		return "The result of the product B1.";
	}
	[[nodiscard]] std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const {
		std::string result = collaborator.useFulFunction_A();
		return "The result of the B1 collaborating with ( " + result + " )";
	}
};

class ConcreateProduct_B2 : public AbstractProduct_B
{
public:
	[[nodiscard]] std::string useFulFunction_B() const override {
		return "The result of the product B2.";
	}
	[[nodiscard]] std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const {
		std::string result = collaborator.useFulFunction_A();
		return "The result of the B2 collaborating with ( " + result + " )";
	}
};

//Factories
class AbstractFactory
{
public:
	virtual~AbstractFactory() = default;
	virtual std::unique_ptr<AbstractProduct_A> createProduct_A() const = 0;
	virtual std::unique_ptr<AbstractProduct_B> createProduct_B() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
	[[nodiscard]] std::unique_ptr<AbstractProduct_A> createProduct_A() const override {
		return std::make_unique<ConcreateProduct_A1>();
	}
	[[nodiscard]] std::unique_ptr<AbstractProduct_B> createProduct_B() const override {
		return std::make_unique<ConcreateProduct_B1>();
	}
};

class ConcreteFactory2 : public AbstractFactory
{
public:
	[[nodiscard]] std::unique_ptr<AbstractProduct_A> createProduct_A() const override {
		return std::make_unique<ConcreateProduct_A2>();
	}
	[[nodiscard]] std::unique_ptr<AbstractProduct_B> createProduct_B() const override {
		return std::make_unique<ConcreateProduct_B2>();
	}
};


/*
void clientCode(const AbstractFactory &factory)
{
	unique_ptr<AbstractProduct_A> product_a = factory.createProduct_A();
	unique_ptr<AbstractProduct_B> product_b = factory.createProduct_B();
	cout << product_b->useFulFunction_B() << "\n";
	cout << product_b->anotherFulFunction_B(*product_a) << "\n";
}

{
	std::cout << "Client: Testing client code with the first factory type:\n";
	const unique_ptr<AbstractFactory> firstFactory = make_unique<ConcreteFactory1>();
	clientCode(*firstFactory);
	std::cout << std::endl;
	std::cout << "Client: Testing the same client code with the second factory type:\n";
	const unique_ptr<AbstractFactory> secondFactory = make_unique<ConcreteFactory2>();
	clientCode(*secondFactory);



*/