#pragma once
#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <iterator>

/**
 * TITLE: Паттерн Наблюдатель
 *
 * Назначение: Создаёт механизм подписки, позволяющий одним объектам следить и
 * реагировать на события, происходящие в других объектах.
 *
 * Обратите внимание, что существует множество различных терминов с похожими
 * значениями, связанных с этим паттерном. Просто помните, что Субъекта также
 * называют Издателем, а Наблюдателя часто называют Подписчиком и наоборот.
 * Также глаголы «наблюдать», «слушать» или «отслеживать» обычно означают одно и
 * то же.
 */

//abstract class
class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void update(const std::string &msg_from_subject) = 0;
};
//abstract class
class ISubject
{
public:
	virtual ~ISubject() = default;
	virtual void attach(std::shared_ptr<IObserver> observer) = 0;
	virtual void detach(std::shared_ptr<IObserver> observer) = 0;
	virtual void notify() = 0;
};
/**
 * Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его изменениях.
 * 
 */
//it's saved the lis of pointers at IObserver
class Subject : public ISubject
{
public:

	//Subject(const Subject &) = delete;
	//Subject &operator=(const Subject &) = delete;

	virtual ~Subject() {
		std::cout << "Goodbye, I was the Subject.\n";
	}

	//replace IObserver to Subject
	void attach(std::shared_ptr<IObserver> observer)  override
	{
		m_list_observer_.emplace_back(observer);
	}

	void detach(std::shared_ptr<IObserver> observer) override
	{
		m_list_observer_.remove(observer);
	}

	void notify() override
	{
		auto tmp_iterator = m_list_observer_.begin();
		how_many_observers();

		while (tmp_iterator != m_list_observer_.end())
		{
			(*tmp_iterator)->update(m_msg_);
			++tmp_iterator;
		}
	}

	void create_message(std::string msg = "Empty")
	{
		this->m_msg_ = std::move(msg);
		notify();
	}

	void how_many_observers() const
	{
		std::cout << "There are " << m_list_observer_.size() << " observers in the list.\n";
	}
	/**
	 * Обычно логика подписки – только часть того, что делает Издатель. Издатели
	 * часто содержат некоторую важную бизнес-логику, которая запускает метод
	 * уведомления всякий раз, когда должно произойти что-то важное (или после
	 * этого).
	 */
	void some_biseness_logic()
	{
		this->m_msg_ = "change m_msg_ msg";
		notify();
		std::cout << "I'm about to do some thing important\n";
	}


private:
	std::list<std::shared_ptr<IObserver>> m_list_observer_;
	std::string m_msg_;
};

//observer
//it's saved a pointer at Subject; there is a static counter - m_st_number_
class Observer : public IObserver, public std::enable_shared_from_this<Observer>
{
public:
	//Любая попытка вызова shared_from_this из конструктора приведет к bad_weak_ptr исключению.
	//Observer(std::shared_ptr<Subject> subject) : subject_(std::move(subject))
	//{
	//	this->subject_->attach(get_this());
	//	std::cout << "Hi, I'm the Observer \"" << ++st_number_ << "\".\n";
	//	this->number_ = st_number_;
	//}
	Observer() = default;
	virtual ~Observer() {
		std::cout << "Goodbye, I was the Observer \"" << this->m_number_ << "\".\n";
	}

	//set subject 
	void set_subject(std::shared_ptr<Subject> subject)
	{
		this->m_subject_ = std::move(subject);
		std::cout << "Hi, I'm the Observer \"" << ++m_st_number_ << "\".\n";
		this->m_subject_->attach(shared_from_this());
		this->m_number_ = m_st_number_;
	}

	void update(const std::string &msg_from_subject) override
	{
		this->m_msg_from_subject_ = msg_from_subject;
		print_info();
	}

	void remove_me_from_the_list()
	{
		this->m_subject_->detach(shared_from_this());
		std::cout << "Observer \"" << m_number_ << "\" removed from the list.\n";
	}

	void print_info() const
	{
		std::cout << "Observer \"" << this->m_number_ << "\": a new message is available --> " << this->m_msg_from_subject_ << "\n";
	}

private:
	std::shared_ptr<Subject> m_subject_;
	std::string m_msg_from_subject_;
	inline static size_t m_st_number_{0};
	size_t m_number_{};
};


/*
void client_code()
{
	auto main_subject = make_shared<Subject>();
	auto main_observer1 = make_shared<Observer>();
	main_observer1->set_subject(main_subject);		//т.к. невозможно использовать shared_from_this() из конструктора - используем этот метод
	auto main_observer2 = make_shared<Observer>();
	main_observer2->set_subject(main_subject);
	auto main_observer3 = make_shared<Observer>();
	main_observer3->set_subject(main_subject);
	auto main_observer4 = make_shared<Observer>();
	auto main_observer5 = make_shared<Observer>();

	main_subject->create_message("Hello World! :D"s);
	main_observer3->remove_me_from_the_list();

	main_subject->create_message("The weather is hot today! :p"s);
	main_observer4->set_subject(main_subject);

	main_observer2->remove_me_from_the_list();
	main_observer5->set_subject(main_subject);

	main_subject->create_message("My new car is great! ;)"s);
	main_observer5->remove_me_from_the_list();

	main_observer4->remove_me_from_the_list();
	main_observer1->remove_me_from_the_list();
}

int main() noexcept
{
	client_code();
}
	//-----output
	
Hi, I'm the Observer "1".
Hi, I'm the Observer "2".
Hi, I'm the Observer "3".
There are 3 observers in the list.
Observer "1": a new message is available --> Hello World! :D
Observer "2": a new message is available --> Hello World! :D
Observer "3": a new message is available --> Hello World! :D
Observer "3" removed from the list.
There are 2 observers in the list.
Observer "1": a new message is available --> The weather is hot today! :p
Observer "2": a new message is available --> The weather is hot today! :p
Hi, I'm the Observer "4".
Observer "2" removed from the list.
Hi, I'm the Observer "5".
There are 3 observers in the list.
Observer "1": a new message is available --> My new car is great! ;)
Observer "4": a new message is available --> My new car is great! ;)
Observer "5": a new message is available --> My new car is great! ;)
Observer "5" removed from the list.
Observer "4" removed from the list.
Observer "1" removed from the list.
Goodbye, I was the Observer "5".
Goodbye, I was the Observer "4".
Goodbye, I was the Observer "3".
Goodbye, I was the Observer "2".
Goodbye, I was the Observer "1".
Goodbye, I was the Subject.
 
 */