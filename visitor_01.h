#pragma once
#include <memory>
#include <iostream>


//TITLE: Visitor (!memory leak)
/*
Посетитель — это поведенческий паттерн проектирования, который позволяет добавлять в программу новые операции,
не изменяя классы объектов, над которыми эти операции могут выполняться.

*/

class  ConcreteComponent_a;
class  ConcreteComponent_b;

//abstract class with two methods
class Visitor
{
public:
	virtual ~Visitor() = default;
	virtual void visit_concrete_component_a(ConcreteComponent_a const &element) const = 0;
	virtual void visit_concrete_component_b(ConcreteComponent_b element) const = 0;
};

//component 
class Component
{
public:
	virtual ~Component() = default;
	virtual void accept(Visitor &&visitor) = 0;
};

//concrete component a
class ConcreteComponent_a : public Component, public std::enable_shared_from_this<ConcreteComponent_a>
{
public:
	void accept(Visitor &&visitor) override
	{
		std::weak_ptr tmp_concrete_component_a( shared_from_this());	//this ptr
		if (!tmp_concrete_component_a.expired())
		{
			visitor.visit_concrete_component_a(std::move(*tmp_concrete_component_a.lock()));
		}
	}
	// ReSharper disable once CppMemberFunctionMayBeStatic
	std::string exclusive_method_of_concrete_component_a() const
	{
		return "A";
	}
};

//concrete component b
class ConcreteComponent_b : public Component, public std::enable_shared_from_this<ConcreteComponent_b>
{
public:
	void accept(Visitor &&visitor) override
	{
		std::weak_ptr tmp_concrete_component_b(shared_from_this());	//this ptr
		if (!tmp_concrete_component_b.expired())
		{
			visitor.visit_concrete_component_b(std::move(*tmp_concrete_component_b.lock()));
		}
	}
	std::string special_method_of_concrete_component_b() const
	{
		return "B";
	}
};

//concrete visitor 1
class ConcreteVisitor_1 : public Visitor
{
public:
	void visit_concrete_component_a(ConcreteComponent_a const &element) const override
	{
		std::cout << element.exclusive_method_of_concrete_component_a() << " + ConcreteVisitor_1\n";
	}

	void visit_concrete_component_b(ConcreteComponent_b element) const override
	{
		std::cout << element.special_method_of_concrete_component_b() << " + ConcreteVisitor_1\n";
	}
};

//concrete visitor 2
class ConcreteVisitor_2 : public Visitor
{
public:
	void visit_concrete_component_a(ConcreteComponent_a const &element) const override
	{
		std::cout << element.exclusive_method_of_concrete_component_a() << " + ConcreteVisitor_2\n";
	}

	void visit_concrete_component_b(ConcreteComponent_b element) const override
	{
		std::cout << element.special_method_of_concrete_component_b() << " + ConcreteVisitor_2\n";
	}
};


/*
constexpr int number_comp = 2;
void client_code(array<shared_ptr<Component>, number_comp> const &components,
	shared_ptr<Visitor> &&client_code_visitors)
{
	for (auto &&it : components)
		it->accept(move(*client_code_visitors));
}

int main()
{
	array<shared_ptr<Component>, number_comp> components;
	components[0] = make_shared<ConcreteComponent_a>();
	components[1] = make_shared<ConcreteComponent_b>();


	std::cout << "The client code works with all visitors via the base Visitor interface:\n";
	auto main_visitor_1 = make_shared<ConcreteVisitor_1>();
	client_code(components, move(main_visitor_1));


	std::cout << "\nIt allows the same client code to work with different types of visitors:\n";
	auto main_visitor_2 = make_shared<ConcreteVisitor_2>();
	client_code(components, move(main_visitor_2));
}
 */