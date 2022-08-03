#pragma once
#include <iostream>



class Widget
{
public:
	virtual ~Widget() = default;
	virtual void draw() const = 0;
};

class TextField final : public Widget
{
public:
	~TextField() override = default;
	TextField(int w, int h) : width_(w), height_(h) { }
	void draw() const override
	{
		std::cout << "TextField: " << width_ << ", " << height_ << "\n";
	}
protected:
	int width_ = 0;
	int height_ = 0;
};

class Decorator : public Widget 
{
public:
	~Decorator() override = default;
	Decorator(std::unique_ptr<Widget> w)
		:ptrOnWidget_(std::move(w)) { }

	void draw() const override
	{
		ptrOnWidget_->draw(); 
	}
protected:
	std::unique_ptr<Widget> ptrOnWidget_; 
};

class BorderDecorator final : public Decorator
{
public:
	~BorderDecorator() override = default;
	BorderDecorator(std::unique_ptr<Widget> w)
		:Decorator(std::move(w)) { }

	void draw() const override
	{
		Decorator::draw(); 
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

//main()
#if 0

std::unique_ptr<Widget> a_widget{ std::make_unique<BorderDecorator>(
											std::make_unique<BorderDecorator>(
												std::make_unique<ScrollDecorator>(
													std::make_unique<TextField>(80, 24)))) };
a_widget->draw();


#endif
