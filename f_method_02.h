#pragma once
#include <string>
#include <memory>
/*
Создает объекты разных типов, позволяя системе оставаться независимой как от самого процесса создания, 
так и от типов создаваемых объектов.

Фабричный метод — это порождающий паттерн проектирования, который определяет
общий интерфейс для создания объектов в суперклассе, позволяя подклассам изменять тип создаваемых объектов.
В системе часто требуется создавать объекты самых разных типов.Паттерн Factory Method(фабричный метод)
может быть полезным в решении следующих задач :

Система должна оставаться расширяемой путем добавления объектов новых типов.Непосредственное использование
выражения new является нежелательным, так как в этом случае код создания объектов с указанием конкретных типов 
может получиться разбросанным по всему приложению.Тогда такие операции как добавление в систему объектов новых 
типов или замена объектов одного типа на другой будут затруднительными(подробнее в разделе Порождающие паттерны).
Паттерн Factory Method позволяет системе оставаться независимой как от самого процесса порождения объектов, так и от их типов.
Заранее известно, когда нужно создавать объект, но неизвестен его тип.
*/

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

//A fabric method
class Creator
{
public:
	virtual ~Creator() = default;
	virtual std::unique_ptr<I_Product> factoryMethod() const = 0;

	[[nodiscard]] std::string someOperation() const
	{
		const auto product = factoryMethod();
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