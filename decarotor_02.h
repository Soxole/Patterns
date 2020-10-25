#pragma once
#include <iostream>

/*
 *     �������� "���������� ����� �����������", �������� ������ �����������������.
    �������� ������� ����� ������� ������ ��� ���������� �������������� ����������������.
    �������� ����� � �����-��������� ���������� ��������� "��������".
    �����-��������� "�����" ��������� "����������� ������ �����������".
    ����� Decorator ���������� ���������� �������� ������� "�����".
    ��� ���������� ������ �������������� ���������������� �������� ��������� Decorator.
    ��������� Decorator ���������� ���������� �������� �������� ������ � ��������� �������������� ����������������.
    ������ ����� ��������������� �� ���������������� ������ ����������������.

 */

// 1. " ���������� ����� �����������"
class Widget
{
public:
	virtual ~Widget() = default;
	virtual void draw() const = 0;
};

// 3. �������� �����, ������������ ��������� "��������"
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

// 2. ������� ����� ������� ������
class Decorator : public Widget // 3. ���������� ��������� "��������"
{
public:
	~Decorator() override = default;
	Decorator(std::unique_ptr<Widget> w)
		:ptrOnWidget(std::move(w)) { }

	void draw() const override
	{
		ptrOnWidget->draw(); // 5. �������������
	}
protected:
	std::unique_ptr<Widget> ptrOnWidget; // 4. ��������� "�����"
};


// 6. �������������� �������������
class BorderDecorator : public Decorator
{
public:
	~BorderDecorator() override = default;
	BorderDecorator(std::unique_ptr<Widget> w)
		:Decorator(std::move(w)) { }

	void draw() const override
	{
		Decorator::draw(); // 7. ������������� �������� ������
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
 * 8. ������ ������������ �� ���������������� ������ ����������������
 * 	unique_ptr<Widget> a_widget{make_unique<BorderDecorator>(
		make_unique<BorderDecorator>(
			make_unique<ScrollDecorator>(
				make_unique<TextField>(80, 24))))};
	
	a_widget->draw();
 */