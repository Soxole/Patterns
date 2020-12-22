#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>



class Product1
{
public:
	std::vector<std::shared_ptr<std::string>> parts_;

	void ListParts()const {
		std::cout << "Product parts: ";

		for (size_t i = 0; i < parts_.size(); i++) {
			if (parts_[i] == parts_.back()) {
				std::cout << *parts_[i];
			}
			else {
				std::cout << *parts_[i] << ", ";
			}
		}
		std::cout << "\n\n";
	}
};


/**
 * Интерфейс Строителя объявляет создающие методы для различных частей объектов
 * Продуктов.
 */
class Builder
{
public:
	virtual ~Builder() = default;
	virtual void ProducePartA() const = 0;
	virtual void ProducePartB() const = 0;
	virtual void ProducePartC() const = 0;
};

//******************************************************************************
class ConcreteBuilder1 : public Builder
{
public:

	ConcreteBuilder1() { Reset(); }

	void Reset() { m_concrete_product = std::make_shared<Product1>(); }

	//Все этапы производства работают с одним и тем же экземпляром продукта.
	void ProducePartA() const override {
		m_concrete_product->parts_.push_back(std::make_shared<std::string>("PartA1"));
	}
	void ProducePartB() const override {
		m_concrete_product->parts_.push_back(std::make_shared<std::string>("PartB1"));
	}
	void ProducePartC() const override {
		m_concrete_product->parts_.push_back(std::make_shared<std::string>("PartC1"));
	}

	/**
	 * Конкретные Строители должны предоставить свои собственные методы
	 * получения результатов. Это связано с тем, что различные типы строителей
	 * могут создавать совершенно разные продукты с разными интерфейсами.
	 * Поэтому такие методы не могут быть объявлены в базовом интерфейсе
	 * Строителя (по крайней мере, в статически типизированном языке
	 * программирования).
	 *
	 * Как правило, после возвращения конечного результата клиенту, экземпляр
	 * строителя должен быть готов к началу производства следующего продукта.
	 * Поэтому обычной практикой является вызов метода сброса в конце тела
	 * метода getProduct. Однако такое поведение не является обязательным, вы
	 * можете заставить своих строителей ждать явного запроса на сброс из кода
	 * клиента, прежде чем избавиться от предыдущего результата.
	 */


	std::shared_ptr<Product1> GetProduct()
	{
		std::shared_ptr<Product1> result = std::move(m_concrete_product);
		Reset();
		return result;
	}

private:
	/**
	 * Новый экземпляр строителя должен содержать пустой объект продукта,
	 * который используется в дальнейшей сборке.
	 */
	std::shared_ptr<Product1> m_concrete_product;
};

/**
 * Директор отвечает только за выполнение шагов построения в определённой
 * последовательности. Это полезно при производстве продуктов в определённом
 * порядке или особой конфигурации. Строго говоря, класс Директор необязателен,
 * так как клиент может напрямую управлять строителями.
 */
class Director
{
public:
	//recieve pointer builder
	void set_builder(std::shared_ptr<Builder> builder)
	{
		m_builder = builder;
	}

	//to build a one solution of the product
	void BuildMinimalViableProduct()
	{
		m_builder->ProducePartA();
	}
	//all solutions ...
	void BuildFullFeaturedProduct()
	{
		m_builder->ProducePartA();
		m_builder->ProducePartB();
		m_builder->ProducePartC();
	}
private:
	std::shared_ptr<Builder> m_builder;
	/**
	 * Директор работает с любым экземпляром строителя, который передаётся ему
	 * клиентским кодом. Таким образом, клиентский код может изменить конечный
	 * тип вновь собираемого продукта.
	 */

};
/**
* Клиентский код создаёт объект-строитель, передаёт его директору, а затем
* инициирует процесс построения. Конечный результат извлекается из объекта-
* строителя.
*/
/**
 * I used raw pointers for simplicity however you may prefer to use smart
 * pointers here
 */

 /*
void ClientCode(Director &director)
{
	auto builder = make_shared<ConcreteBuilder1>();
	director.set_builder(builder);
	std::cout << "Standard basic product:\n";
	director.BuildMinimalViableProduct();

	auto p = builder->GetProduct();
	p->ListParts();

	std::cout << "Standard full featured product:\n";
	director.BuildFullFeaturedProduct();

	p = builder->GetProduct();
	p->ListParts();

	// Помните, что паттерн Строитель можно использовать без класса Директор.
	std::cout << "Custom product:\n";
	builder->ProducePartA();
	builder->ProducePartC();
	p = builder->GetProduct();
	p->ListParts();
}

int main()
{
	auto ptrDirector = make_shared<Director>();
	ClientCode(*ptrDirector);


}

*/