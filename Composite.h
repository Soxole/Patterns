#pragma once
#include <memory>
#include <list>
#include <string>

using namespace std;
/*
Применимость: Паттерн Компоновщик встречается в любых задачах, которые связаны с построением дерева.
Самый простой пример — составные элементы GUI, которые тоже можно рассматривать как дерево.
Признаки применения паттерна: Если из объектов строится древовидная структура, и со всеми объектами дерева,
как и с самим деревом работают через общий интерфейс.
*/

class IComponent
{
public:
	//IComponent() = default;
	virtual ~IComponent() = default;

	//setter
	void setParent(unique_ptr<IComponent> parent)
	{
		parent_ = move(parent);
	}
	//getter
	[[nodiscard]] unique_ptr<IComponent> getParent() const {
		return make_unique<IComponent>();
	}
	//empty methods 
	[[maybe_unused]] virtual void addComp(unique_ptr<IComponent> component)
	{}
	[[maybe_unused]] virtual void removeComp(unique_ptr<IComponent> component)
	{}

	[[nodiscard]] virtual bool isComposite() const {
		return false;
	}
	//any operation return string
	[[nodiscard]] virtual string operation() const {
		return "";
	}

protected:
	unique_ptr<IComponent> parent_;
};
/*
 * Класс Лист представляет собой конечные объекты структуры. Лист не может иметь
 * вложенных компонентов.
 *
 * Обычно объекты Листьев выполняют фактическую работу, тогда как объекты
 * Контейнера лишь делегируют работу своим подкомпонентам.
 */

class Leaf : public IComponent
{
public:
	[[nodiscard]] string operation() const override {
		return "leaf";
	}
};

/**
 * Класс Контейнер содержит сложные компоненты, которые могут иметь вложенные
 * компоненты. Обычно объекты Контейнеры делегируют фактическую работу своим
 * детям, а затем «суммируют» результат.
 */

class Composite final : public IComponent
{
public:
	void addComp(unique_ptr<IComponent> component) override {
		component->setParent(make_unique<Leaf>());
		children_.push_back(move(component));
	}

	void removeComp(unique_ptr<IComponent> component) override {
		children_.remove(component);
		component->setParent(nullptr);
	}

	[[nodiscard]] string operation() const override {

		string result;

		for (auto &&component : children_) {
			if (component == children_.back())
			{
				result += component->operation();
			}
			else
			{
				result += component->operation() + " + ";
			}
		}
		return "Branch(" + result + ")";
	}

protected:
	list <unique_ptr<IComponent>> children_;
};

/*
void client_code(const unique_ptr<IComponent> component) {

	std::cout << "RESULT: " << component->operation();
}


 * Благодаря тому, что операции управления потомками объявлены в базовом классе
 * Компонента, клиентский код может работать как с простыми, так и со сложными
 * компонентами, вне зависимости от их конкретных классов.
void client_code2(unique_ptr<IComponent> component1, unique_ptr<IComponent> component2) {

	if (component1->isComposite()) {
		component1->addComp(move(component2));
	}
	std::cout << "RESULT: " << component1->operation();
}


int main()
{
	unique_ptr<IComponent> simple{ make_unique<Leaf>() };
	std::cout << "Client: I've got a simple component:\n";
	ClientCode(move(simple));
	cout << endl;

	unique_ptr<IComponent> tree{ make_unique<Composite>() };
	unique_ptr<IComponent> branch{ make_unique<Composite>() };

	unique_ptr<IComponent> leaf_1{ make_unique<Leaf>() };
	unique_ptr<IComponent> leaf_2{ make_unique<Leaf>() };
	unique_ptr<IComponent> leaf_3{ make_unique<Leaf>() };
	branch->addComp(move(leaf_1));
	branch->addComp(move(leaf_2));
	unique_ptr<IComponent> branch2{ make_unique<Composite>() };
	branch->addComp(move(leaf_3));
	tree->addComp(move(branch));
	tree->addComp(move(branch2));
	std::cout << "Client: Now I've got a composite tree:\n";
	ClientCode(move(tree));
	std::cout << "\n\n";

	std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	ClientCode2(move(tree), move(simple));
	std::cout << "\n";

	return 0;
}

*/