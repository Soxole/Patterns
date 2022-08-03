#pragma once
#include <memory>
#include <list>
#include <string>


//TODO: pattern composite; incorrect working 

/*
 Компоновщик — это структурный паттерн проектирования, который позволяет сгруппировать множество объектов
 в древовидную структуру, а затем работать с ней так, как будто это единичный объект.
 Применимость: Паттерн Компоновщик встречается в любых задачах, которые связаны с построением дерева.
Самый простой пример — составные элементы GUI, которые тоже можно рассматривать как дерево.
 Признаки применения паттерна: Если из объектов строится древовидная структура, и со всеми объектами дерева,
как и с самим деревом работают через общий интерфейс.
*/


//Abstract Component; stores a pointer yourself
class IComponent
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	//setter
	void setParent(const std::shared_ptr<IComponent> &parent)
	{
		m_parent_ = parent;
	}
	//getter; unused
	[[nodiscard]] std::shared_ptr<IComponent> getParent() const
	{
		auto tmp = m_parent_.lock();
		if (tmp)
			return tmp;

		return nullptr;
	}

	//empty methods 
	[[maybe_unused]] virtual void addComp(std::shared_ptr<IComponent> &&component)
	{}
	[[maybe_unused]] virtual void removeComp(const std::shared_ptr<IComponent> &component)
	{}

	[[nodiscard]] virtual bool isComposite() const {
		return false;
	}
	//some operation return string
	[[nodiscard]] virtual std::string operation() const {
		return "";
	}

protected:
	std::weak_ptr<IComponent> m_parent_; //weak_ptr
};

//Leaf
class Leaf : public IComponent
{
public:
	[[nodiscard]] std::string operation() const override
	{
		return "leaf";
	}
};

//Composite derived from IComponent; stores pointer to IComponent
class Composite final : public IComponent, public std::enable_shared_from_this<Composite>
{
public:
	void addComp(std::shared_ptr<IComponent> &&component) override
	{
		std::weak_ptr tmp_this_composite(shared_from_this());
		m_children_.emplace_back(component);
		if (!tmp_this_composite.expired())
		{
			component->setParent(tmp_this_composite.lock());	//ptr to this
		}
	}

	void removeComp(const std::shared_ptr<IComponent> &component) override
	{
		m_children_.remove(component);
		component->setParent(nullptr);
	}

	[[nodiscard]] std::string operation() const override
	{
		std::string result;

		for (const auto &component : m_children_)
		{
			if (component == m_children_.back())
			{
				result += component->operation();
			}
			else {
				result += component->operation() + " + ";
			}
		}
		return "Branch(" + result + ")";
	}

protected:
	std::list<std::shared_ptr<IComponent>> m_children_;
};

/*


void client_code(const shared_ptr<IComponent> &component) {

	std::cout << "RESULT: " << component->operation();
}


void client_code2(shared_ptr<IComponent> &&component1, shared_ptr<IComponent> &&component2) {

	if (component1->isComposite()) {
		component1->addComp(move(component2));
	}
	std::cout << "RESULT: " << component1->operation();
}


int main()
{
		shared_ptr<IComponent> simple{ make_shared<Leaf>() };
		std::cout << "Client: I've got a simple component:\n";
		client_code(simple); //cl_1
		cout << "\n";

		shared_ptr<IComponent> tree{ make_shared<Composite>() };
		shared_ptr<IComponent> branch{ make_shared<Composite>() };
		unique_ptr<IComponent> leaf_1{ make_unique<Leaf>() }; //once using
		unique_ptr<IComponent> leaf_2{ make_unique<Leaf>() };	//once using
		unique_ptr<IComponent> leaf_3{ make_unique<Leaf>() };	//once using

		branch->addComp(move(leaf_1));
		branch->addComp(move(leaf_2));

		shared_ptr<IComponent> branch2{ make_shared<Composite>() };

		branch2->addComp(move(leaf_3));
		tree->addComp(move(branch));
		tree->addComp(move(branch2));

		std::cout << "Client: Now I've got a composite tree:\n";
		client_code(tree);	//cl_1
		std::cout << "\n\n";

		std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";

		client_code2(move(tree), move(simple));	//cl_1
		std::cout << "\n";
}

*/