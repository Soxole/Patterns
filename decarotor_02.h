#pragma once
#include <iostream>

/*
 *     Создайте "наименьший общий знаменатель", делающий классы взаимозаменяемыми.
    Создайте базовый класс второго уровня для реализации дополнительной функциональности.
    Основной класс и класс-декоратор используют отношение "является".
    Класс-декоратор "имеет" экземпляр "наименьшего общего знаменателя".
    Класс Decorator делегирует выполнение операции объекту "имеет".
    Для реализации каждой дополнительной функциональности создайте подклассы Decorator.
    Подклассы Decorator делегируют выполнение операции базовому классу и реализуют дополнительную функциональность.
    Клиент несет ответственность за конфигурирование нужной функциональности.

 */

// 1. " Наименьший общий знаменатель"
class Widget
{
public:
	virtual ~Widget() = default;
	virtual void draw() const = 0;
};

// 3. Основной класс, использующий отношение "является"
class TextField : public Widget
{
public:
	~TextField() override = default;
	TextField(int w, int h) : width(w), height(h) { }
	void draw() const override
	{
		std::cout << "TextField: " << width << ", " << height << "\n";
	}
protected:
	int width = 0;
	int height = 0;
};

// 2. Базовый класс второго уровня
class Decorator : public Widget // 3. использует отношение "является"
{
public:
	~Decorator() override = default;
	Decorator(std::unique_ptr<Widget> w)
		:ptrOnWidget(std::move(w)) { }

	void draw() const override
	{
		ptrOnWidget->draw(); // 5. делегирование
	}
protected:
	std::unique_ptr<Widget> ptrOnWidget; // 4. отношение "имеет"
};


// 6. Дополнительное декорирование
class BorderDecorator : public Decorator
{
public:
	~BorderDecorator() override = default;
	BorderDecorator(std::unique_ptr<Widget> w)
		:Decorator(std::move(w)) { }

	void draw() const override
	{
		Decorator::draw(); // 7. Делегирование базовому классу
		std::cout << " BorderDecorator" << "\n";
	}
};

class ScrollDecorator final : public Decorator
{
public:
	~ScrollDecorator() override = default;
	ScrollDecorator(std::unique_ptr<Widget> w)
		: Decorator(std::move(w)) { }

	void draw() const override
	{
		Decorator::draw();
		std::cout << " ScrollDecorator" << "\n";
	}
};
/*
 * 8. Клиент ответственен за конфигурирование нужной функциональности
 * 	unique_ptr<Widget> a_widget{make_unique<BorderDecorator>(
		make_unique<BorderDecorator>(
			make_unique<ScrollDecorator>(
				make_unique<TextField>(80, 24))))};
	
	a_widget->draw();
 */