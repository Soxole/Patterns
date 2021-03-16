#pragma once
#include <memory>
#include <list>
#include <string>

using namespace std;
//TODO: pattern composite; incorrect working 

/*
������������: ������� ����������� ����������� � ����� �������, ������� ������� � ����������� ������.
����� ������� ������ � ��������� �������� GUI, ������� ���� ����� ������������� ��� ������.
�������� ���������� ��������: ���� �� �������� �������� ����������� ���������, � �� ����� ��������� ������,
��� � � ����� ������� �������� ����� ����� ���������.
*/

class IComponent
{
public:
	//IComponent() = default;
	virtual ~IComponent() = default;

	//setter
	void setParent(shared_ptr<IComponent> parent)
	{
		m_parent_ = parent;
	}
	//getter; unused
	[[nodiscard]] shared_ptr<IComponent> getParent() const
	{
		return make_shared<IComponent>();
	}
	
	//empty methods 
	[[maybe_unused]] virtual void addComp(shared_ptr<IComponent> component)
	{}
	[[maybe_unused]] virtual void removeComp(shared_ptr<IComponent> component)
	{}

	[[nodiscard]] virtual bool isComposite() const {
		return false;
	}
	//any operation return string
	[[nodiscard]] virtual string operation() const {
		return "";
	}

protected:
	weak_ptr<IComponent> m_parent_; //weak_ptr
};
/*
 * ����� ���� ������������ ����� �������� ������� ���������. ���� �� ����� �����
 * ��������� �����������.
 *
 * ������ ������� ������� ��������� ����������� ������, ����� ��� �������
 * ���������� ���� ���������� ������ ����� ��������������.
 */

class Leaf : public IComponent
{
public:
	[[nodiscard]] string operation() const override
	{
		return "leaf";
	}
};

/**
 * ����� ��������� �������� ������� ����������, ������� ����� ����� ���������
 * ����������. ������ ������� ���������� ���������� ����������� ������ �����
 * �����, � ����� ���������� ���������.
 */

class Composite final : public IComponent, public std::enable_shared_from_this<Composite>
{
public:
	void addComp(shared_ptr<IComponent> component) override
	{
		m_children_.emplace_back(component);
		component->setParent(shared_from_this());	//this
	}

	void removeComp(shared_ptr<IComponent> component) override
	{
		m_children_.remove(component);
		component->setParent(nullptr);
	}

	[[nodiscard]] string operation() const override
	{
		string result;

		for (const auto &component : m_children_) {
			if (component == m_children_.back())
			{
				result += component->operation();
			}else{
				result += component->operation() + " + ";
			}
		}
		return "Branch(" + result + ")";
	}

protected:
	list<shared_ptr<IComponent>> m_children_;
};

/*

 * ��������� ����, ��� �������� ���������� ��������� ��������� � ������� ������
 * ����������, ���������� ��� ����� �������� ��� � ��������, ��� � �� ��������
 * ������������, ��� ����������� �� �� ���������� �������.


void client_code(const unique_ptr<IComponent> &component) {

	std::cout << "RESULT: " << component->operation();
}


void client_code2(unique_ptr<IComponent> &component1,unique_ptr<IComponent> &component2) {

	if (component1->isComposite()) {
		component1->addComp(move(component2));
	}
	std::cout << "RESULT: " << component1->operation();
}

int main()
{
	unique_ptr<IComponent> simple{ make_unique<Leaf>() };
	std::cout << "Client: I've got a simple component:\n";
	client_code(simple);
	cout << "\n";

	unique_ptr<IComponent> tree{ make_unique<Composite>() };
	unique_ptr<IComponent> branch{ make_unique<Composite>() };

	unique_ptr<IComponent> leaf_1{ make_unique<Leaf>() };
	unique_ptr<IComponent> leaf_2{ make_unique<Leaf>() };
	unique_ptr<IComponent> leaf_3{ make_unique<Leaf>() };

	branch->addComp(move(leaf_1));
	branch->addComp(move(leaf_2));
	unique_ptr<IComponent> branch2{ make_unique<Composite>() };
	branch2->addComp(move(leaf_3));
	tree->addComp(move(branch));
	tree->addComp(move(branch2));

	std::cout << "Client: Now I've got a composite tree:\n";
	client_code(tree);
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	client_code2(tree, simple);
	std::cout << "\n";
}

*/