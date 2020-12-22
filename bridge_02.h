#pragma once
#include <iomanip>
#include <iostream>
#include <memory>

/*
 *Паттерн Bridge разделяет абстракцию и реализацию на две отдельные иерархии классов так,
 *что их можно изменять независимо друг от друга.
*/

//realization 
class I_Drawer
{
public:
	virtual ~I_Drawer() = default;
	virtual void drawCircle(const double &x, const double &y, const double &radius) = 0;
};

class SmallCircleDrawer : public I_Drawer
{
public:
	const double radiusMultiplier = 0.25;

	void drawCircle(const double &x, const double &y, const double &radius) override
	{
		std::cout << "Small circle center " << x << ", " << y << " radius = " <<
			radius * radiusMultiplier << "\n";
	}
};

class LargeCircleDrawer final : public I_Drawer
{
public:
	const double radiusMultiplier = 10;
	
	void drawCircle(const double &x, const double &y, const double &radius) override
	{
		std::cout << "Large circle center " << x << ", " << y << " radius = " <<
			radius * radiusMultiplier;
	}
};

//abstraction
//Shape
class Shape
{
public:
	Shape() = default;
	Shape(std::unique_ptr<I_Drawer> drw) : m_drawer(std::move(drw)) { }
	virtual ~Shape() = default;

	virtual void draw() = 0;
	virtual void enlargeRadius(double multiplier) = 0;
protected:
	std::unique_ptr<I_Drawer> m_drawer;

};

class Circle : public Shape
{
public:
	Circle(const double &x, const double &y, const double &radius, std::unique_ptr<I_Drawer> drw)
		:m_x(x), m_y(y), m_radius(radius)
	{
		m_drawer = std::move(drw);
	}

	void draw() override
	{
		m_drawer->drawCircle(m_x, m_y, m_radius);
	}

	virtual void enlargeRadius(double multiplier) override
	{
	}
protected:
	double m_x = 0;
	double m_y = 0;
	double m_radius = 0;

};

/*
	unique_ptr<I_Drawer> ptrRealization{make_unique<SmallCircleDrawer>()};
	auto ptrAbstraction = make_unique<Circle>(12.0, 12.0, 4.9, move(ptrRealization));
	ptrAbstraction->draw();

	ptrRealization = make_unique<LargeCircleDrawer>();
	ptrAbstraction = make_unique<Circle>(55.0, 55.0, 17.22, move(ptrRealization));
	ptrAbstraction->draw();

*/