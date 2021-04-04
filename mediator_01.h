#pragma once

#include <iostream>
#include <memory>
#include <string>

//TITLE: Mediator


class BaseComponent;

class Mediator
{
public:
    virtual ~Mediator() = default;
    virtual void notify(std::shared_ptr<BaseComponent> sender, std::string event) = 0;
};

//It's stored a weak pointer to Mediator
class BaseComponent
{
public:
    ~BaseComponent() = default;
    explicit BaseComponent(const std::shared_ptr<Mediator> &mediator = nullptr)
        : m_mediator_(mediator)
    {
    }

    void set_mediator(const std::shared_ptr<Mediator> &mediator)
    {
        this->m_mediator_ = mediator;
    }

protected:
    std::weak_ptr<Mediator> m_mediator_;
};

//component 1
class Component_1 : public BaseComponent, public std::enable_shared_from_this<Component_1>
{
public:

    void make_up_A()
    {
        std::cout << "Component_1 make up A.\n";
        auto tmp = m_mediator_.lock();
        if (tmp)
            tmp->notify(shared_from_this(), "A"); //this
    }
    void make_up_B()
    {
        std::cout << "Component_1 make up B.\n";
        auto tmp = m_mediator_.lock();
        if (tmp)
            tmp->notify(shared_from_this(), "B"); //this
    }
};

//component 2
class Component_2 final : public BaseComponent, public std::enable_shared_from_this<Component_2>
{
public:
    void make_up_C()
    {
        std::cout << "Component_2 make up C.\n";
        auto tmp = m_mediator_.lock();
        if (tmp)
            tmp->notify(shared_from_this(), "C"); //this
    }

    void make_up_D()
    {
        std::cout << "Component_2 make up D.\n";
        auto tmp = m_mediator_.lock();
        if (tmp)
            tmp->notify(shared_from_this(), "D"); //this
    }
};

//It's stored 2 shared pointers to Component_1 and Component_2
class ConcreteMediator : public Mediator, public std::enable_shared_from_this<ConcreteMediator>
{
public:
    ConcreteMediator() = default;

    void set_component_1(std::shared_ptr<Component_1> component_1)
    {
        m_component_1_ = std::move(component_1);
        m_component_1_->set_mediator(shared_from_this()); //this
    }

    void set_component_2(std::shared_ptr<Component_2> component_2)
    {
        m_component_2_ = std::move(component_2);
        m_component_2_->set_mediator(shared_from_this()); //this
    }

    void notify(std::shared_ptr<BaseComponent> sender, const std::string event) override
    {
        if (event == "A")
        {
            std::cout << "Mediator reacts on A and triggers following operations:\n";
            m_component_2_->make_up_C();
        }
        else if (event == "D")
        {
            std::cout << "Mediator reacts on D and triggers following operations:\n";
            m_component_1_->make_up_B();
            m_component_2_->make_up_C();
        }
    }
protected:
    std::shared_ptr<Component_1> m_component_1_;
    std::shared_ptr<Component_2> m_component_2_;
};


/*
void clientCode()
{
   auto component_1 = make_shared<Component_1>();
   auto component_2 = make_shared<Component_2>();
   auto concreteMediator = make_shared<ConcreteMediator>();
   concreteMediator->set_component_1(component_1);
   concreteMediator->set_component_2(component_2);

   std::cout << "Client triggers operation A.\n";
   component_1->make_up_A();
   std::cout << "\n";
   std::cout << "Client triggers operation D.\n";
   component_2->make_up_D();
}

int main()
{
    clientCode();
}
 */
