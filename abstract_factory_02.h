#pragma once
#include<memory>
#include<string>	

/*
 Абстрактная фабрика — это порождающий паттерн проектирования, который позволяет создавать
 семейства связанных объектов, не привязываясь к конкретным классам создаваемых объектов
 */


//product A
class AbstractProduct_A
{
public:
	virtual~AbstractProduct_A() = default;
	virtual std::string useFullFunction_A() const = 0;
};

class ConcreateProduct_A1 : public AbstractProduct_A
{
public:
	[[nodiscard]] std::string useFullFunction_A() const override {
		return "The result of the product A1.";
	}
};

class ConcreateProduct_A2 : public AbstractProduct_A
{
public:
	[[nodiscard]] std::string useFullFunction_A() const override {
		return "The result of the product A2.";
	}
};

//product B
class AbstractProduct_B
{
public:
	virtual~AbstractProduct_B() = default;
	virtual std::string useFullFunction_B() const = 0;
	virtual std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const = 0;
};

class ConcreteProduct_B1 : public AbstractProduct_B
{
public:
	[[nodiscard]] std::string useFullFunction_B() const override {
		return "The result of the product B1.";
	}
	[[nodiscard]] std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const override{
		const std::string result = collaborator.useFullFunction_A();
		return "The result of the B1 collaborating with ( " + result + " )";
	}
};

class ConcreteProduct_B2 : public AbstractProduct_B
{
public:
	[[nodiscard]] std::string useFullFunction_B() const override {
		return "The result of the product B2.";
	}
	[[nodiscard]] std::string anotherFulFunction_B(const AbstractProduct_A &collaborator) const override{
		const std::string result = collaborator.useFullFunction_A();
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
		//Когда временный объект уничтожается, он больше не владеет указателем и, следовательно, не удаляет его.
		return std::make_unique<ConcreateProduct_A1>(ConcreateProduct_A1{});
	}
	[[nodiscard]] std::unique_ptr<AbstractProduct_B> createProduct_B() const override {
		return std::make_unique<ConcreteProduct_B1>(ConcreteProduct_B1{});
	}
};

class ConcreteFactory2 : public AbstractFactory
{
public:
	[[nodiscard]] std::unique_ptr<AbstractProduct_A> createProduct_A() const override {
		return std::make_unique<ConcreateProduct_A2>(ConcreateProduct_A2{});
	}
	[[nodiscard]] std::unique_ptr<AbstractProduct_B> createProduct_B() const override {
		return std::make_unique<ConcreteProduct_B2>(ConcreteProduct_B2{});
	}
};


/*
	
void clientCode(std::unique_ptr<AbstractFactory> const factory)
{
	std::unique_ptr<AbstractProduct_A> product_a = factory->createProduct_A();
	std::unique_ptr<AbstractProduct_B> product_b = factory->createProduct_B();
	std::cout << product_b->useFullFunction_B() << "\n";
	std::cout << product_b->anotherFulFunction_B(*product_a) << "\n";
}


main()
{
	std::cout << "Client: Testing client code with the first factory type:\n";
	std::unique_ptr<AbstractFactory> firstFactory = std::make_unique<ConcreteFactory1>(ConcreteFactory1{});
	clientCode(std::move(firstFactory));
	std::cout << std::endl;
	std::cout << "Client: Testing the same client code with the second factory type:\n";
	std::unique_ptr<AbstractFactory> secondFactory = std::make_unique<ConcreteFactory2>(ConcreteFactory2{});
	clientCode(std::move(secondFactory));
}

*/