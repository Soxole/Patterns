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

class IObserver
{
public:
	virtual ~IObserver() = default;
	virtual void update(const std::string &msg_from_subject) = 0;
};


class ISubject
{
public:
	virtual ~ISubject() = default;
	virtual void attach(std::shared_ptr<IObserver> observer) = 0;
	virtual void detach(std::shared_ptr<IObserver> observer) = 0;
	virtual void notify() = 0;
};
/**
 * Издатель владеет некоторым важным состоянием и оповещает наблюдателей о его
 * изменениях.
 */
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
		list_observer_.emplace_back(observer);
	}

	void detach(std::shared_ptr<IObserver> observer) override
	{
		list_observer_.remove(observer);
	}

	void notify() override
	{
		auto tmp_iterator = list_observer_.begin();
		how_many_observers();
		
		while (tmp_iterator != list_observer_.end())
		{
			(*tmp_iterator)->update(msg_);
			++tmp_iterator;
		}
	}

	void create_message(std::string &&msg = "Empty")
	{
		this->msg_ = std::move(msg);
		notify();
	}

	void how_many_observers() const
	{
		std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
	}
	/**
	 * Обычно логика подписки – только часть того, что делает Издатель. Издатели
	 * часто содержат некоторую важную бизнес-логику, которая запускает метод
	 * уведомления всякий раз, когда должно произойти что-то важное (или после
	 * этого).
	 */
	void some_biseness_logic()
	{
		this->msg_ = "change msg_ msg";
		notify();
		std::cout << "I'm about to do some thing important\n";
	}


private:
	std::list<std::shared_ptr<IObserver>> list_observer_;
	std::string msg_;
};

//observer
//TODO here I'm used std::dynamic_pointer_cast
class Observer : public IObserver
{
public:
	Observer(std::shared_ptr<Subject> subject) : subject_(std::move(subject))
	{
		this->subject_->attach(std::dynamic_pointer_cast<IObserver>(std::make_shared<IObserver>()));
		std::cout << "Hi, I'm the Observer \"" << ++st_number_ << "\".\n";
		this->number_ = st_number_;
	}
	
	virtual ~Observer() {
		std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
	}

	void update(const std::string &msg_from_subject) override
	{
		this->msg_from_subject_ = msg_from_subject;
		print_info();
	}

	void remove_me_from_the_list()
	{
		this->subject_->detach(std::dynamic_pointer_cast<IObserver>(subject_));
		std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
	}

	void print_info() const
	{
		std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->msg_from_subject_ << "\n";
	}

private:
	std::shared_ptr<Subject> subject_;
	std::string msg_from_subject_;
	inline static size_t st_number_ = 0;
	size_t number_;
};


//void client_code()
//{
//	auto main_subject = make_shared<Subject>();
//	auto main_observer1 = make_shared<Observer>(main_subject);
//	auto main_observer2 = make_shared<Observer>(main_subject);
//	auto main_observer3 = make_shared<Observer>(main_subject);
//	/*shared_ptr<Observer> main_observer4;
//	shared_ptr<Observer> main_observer5;*/
//
//	main_subject->create_message("Hello World! :D");
//	main_observer3->remove_me_from_the_list();
//}
//
//
//int main() noexcept
//{
//	client_code();
//}