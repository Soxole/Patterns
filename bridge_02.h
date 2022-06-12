#pragma once
#include <iostream>
#include <memory>


//realization 
class I_Drawer
{
public:
	virtual ~I_Drawer() = default;
	virtual void drawCircle(double x, double y, double radius) const = 0;
};

class SmallCircleDrawer final : public I_Drawer
{
public:
	const double radiusMultiplier = 0.25;

	void drawCircle(const double x, const double y, const double radius)const override {
		std::cout << "Small circle center " << x << ", " << y << " radius = " <<
			radius * radiusMultiplier << "\n";
	}
};

class LargeCircleDrawer final : public I_Drawer
{
public:
	const double radiusMultiplier = 10;

	void drawCircle(const double x, const double y, const double radius)const override {
		std::cout << "Large circle center " << x << ", " << y << " radius = " <<
												radius * radiusMultiplier << '\n';
	}
};

//abstraction
class Shape
{
public:
	Shape() = default;
	Shape(std::shared_ptr<I_Drawer> drw) : m_drawer(std::move(drw)) {}
	virtual ~Shape() = default;

	virtual void draw() = 0;

protected:
	std::shared_ptr<I_Drawer> m_drawer;

};

class Circle final : public Shape
{
public:
	Circle(const double x, const double y, const double radius,
			std::shared_ptr<I_Drawer> drw)
		: Shape(std::move(drw)), m_x(x), m_y(y), m_radius(radius) {}

	void draw() override {
		m_drawer->drawCircle(m_x, m_y, m_radius);
	}

protected:
	double m_x = 0;
	double m_y = 0;
	double m_radius = 0;
};

//main()
/*
	std::shared_ptr<I_Drawer> ptrRealization = std::make_shared<SmallCircleDrawer>();
	auto ptrAbstraction = std::make_shared<Circle>(12.0, 12.0, 4.9, std::move(ptrRealization));
	ptrAbstraction->draw();

	ptrRealization = std::make_shared<LargeCircleDrawer>();
	ptrAbstraction = std::make_shared<Circle>(55.0, 55.0, 17.22, std::move(ptrRealization));
	ptrAbstraction->draw();

*/