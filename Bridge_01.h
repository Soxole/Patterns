#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;
/*
Применимость: Паттерн Мост особенно полезен когда вам приходится делать кросс-платформенные приложения, поддерживать несколько типов
баз данных или работать с разными поставщиками похожего API (например, cloud-сервисы, социальные сети и т. д.)
Признаки применения паттерна: Если в программе чётко выделены классы «управления» и несколько видов классов «платформ», 
причём управляющие объекты делегируют выполнение платформам, то можно сказать, что у вас используется Мост.

 * Реализация устанавливает интерфейс для всех классов реализации. Он не должен
 * соответствовать интерфейсу Абстракции. На практике оба интерфейса могут быть
 * совершенно разными. Как правило, интерфейс Реализации предоставляет только
 * примитивные операции, в то время как Абстракция определяет операции более
 * высокого уровня, основанные на этих примитивах.
 */

class IImplementation
{
public:
	virtual~IImplementation() = default;
	[[nodiscard]] virtual string operationImplement() const = 0;
};

/*
 * Каждая Конкретная Реализация соответствует определённой платформе и реализует
 * интерфейс Реализации с использованием API этой платформы.
 */
class ConcreatImplementA : public IImplementation
{
public:
	[[nodiscard]] string operationImplement() const override {
		return "ConcreteImpA: Here's the result on the platform A.\n";
	}
};

class ConcreatImplementB final : public IImplementation
{
public:
	[[nodiscard]] string operationImplement() const override {
		return "ConcreteImpB: Here's the result on the platform B.\n";
	}
};

/*
 * Абстракция устанавливает интерфейс для «управляющей» части двух иерархий
 * классов. Она содержит ссылку на объект из иерархии Реализации и делегирует
 * ему всю настоящую работу.
 */
class Abstraction
{
public:
	Abstraction(unique_ptr<IImplementation> _upImpl) : upImpl(std::move(_upImpl))
	{}
	~Abstraction() = default;
	[[nodiscard]] string someOperation() const {
		return "Abstraction: Base operation with:\n" + upImpl->operationImplement();
	}

protected:
	unique_ptr<IImplementation> upImpl;
};

/*
 * Можно расширить Абстракцию без изменения классов Реализации.
 */
class ExtendedAbstr : public Abstraction
{
public:
	ExtendedAbstr(unique_ptr<IImplementation> _upImpl) : Abstraction(std::move(_upImpl))
	{}

	[[nodiscard]] string someOperation() const {
		return "ExtendedAbstr: Extended operation with:\n" + upImpl->operationImplement();
	}
};

/*
	unique_ptr<IImplementation> upImpl{ make_unique<ConcreatImplementA>() };
	auto upAbstr{ make_unique<Abstraction>(move(upImpl)) };
	cout << upAbstr->someOperation() << "\n";

	upImpl = make_unique<ConcreatImplementB>();
	upAbstr = make_unique<ExtendedAbstr>(move(upImpl));
	cout << upAbstr->someOperation() << "\n";
*/