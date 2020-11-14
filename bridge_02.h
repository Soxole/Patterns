#pragma once
#include <iomanip>
#include <iostream>
#include <memory>

/*
 *Паттерн Bridge разделяет абстракцию и реализацию на две отдельные иерархии классов так,
 *что их можно изменять независимо друг от друга.
*/

//abstraction
class I_Drawer
{
public:
	virtual ~I_Drawer() = default;
	virtual void drawCircle(const int x, const int y, const int radius) = 0;
};

class SmallCircleDrawer : public I_Drawer
{
public:
	const double radiusMultiplier = 0.25;

	void drawCircle(const int x, const int y, const int radius) override
	{
		std::cout << "Small circle center " << x << ", " << y << " radius = " <<
			radius * radiusMultiplier << "\n";
	}
};

class LargeCircleDrawer final : public I_Drawer
{
public:
	const double radiusMultiplier = 10;
	
	void drawCircle(const int x, const int y, const int radius) override
	{
		std::cout << "Large circle center " << x << ", " << y << " radius = " <<
			radius * radiusMultiplier;
	}
};

//Shape
class Shape
{
protected:
	std::unique_ptr<I_Drawer> drawer_;

public:
	//Shape(std::unique_ptr<I_Drawer> drw) : drawer_(std::move(drw)) { }
	//Shape() = default;
	virtual ~Shape() = default;

	virtual void draw() = 0;
	virtual void enlargeRadius(int multiplier) = 0;
};

class Circle : public Shape
{
protected:
	int x_ = 0;
	int y_ = 0;
	int radius_ = 0;

public:
	Circle(const int x, const int y, const int radius, std::unique_ptr<I_Drawer> drw)
		:x_(x), y_(y), radius_(radius)
	{
		drawer_ = std::move(drw);
	}

	void draw() override
	{
		drawer_->drawCircle(x_, y_, radius_);
	}

};
