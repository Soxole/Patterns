#pragma once
#include <string>
#include <iostream>
#include <list>
#include <memory>

/*
Наблюдатель — это поведенческий паттерн проектирования, который создаёт
механизм подписки, позволяющий одним объектам следить и реагировать на
sсобытия, происходящие в других объектах.
 */


class IObserver
{
public:
	IObserver() = default;
	IObserver(IObserver const &) = default;
	IObserver &operator=(IObserver const &) = default;
	IObserver(IObserver &&) = default;
	IObserver &operator=(IObserver &&) = default;
	virtual ~IObserver() = default;
	virtual void update(const std::string &msg_from_subject) = 0;
};

class ISubject
{
public:
	ISubject() = default;
	ISubject(ISubject const &) = default;
	ISubject &operator=(ISubject const &) = default;
	ISubject(ISubject &&) noexcept = default;
	ISubject &operator=(ISubject &&) noexcept = default;
	virtual ~ISubject() = default;
	virtual void attach(std::shared_ptr<IObserver> observer) = 0;
	virtual void detach(std::shared_ptr<IObserver> observer) = 0;
	virtual void notify() = 0;
};

//it's saved the list of pointers to IObserver
class Subject final : public ISubject
{
public:
	Subject() = default;
	Subject(Subject const &) = default;
	Subject &operator=(Subject const &) = default;
	Subject(Subject &&) noexcept = default;
	Subject &operator=(Subject &&) noexcept = default;
	~Subject() override {
		std::cout << "Goodbye, I was the Subject.\n";
	}

	//replace IObserver to Subject
	void attach(std::shared_ptr<IObserver> observer)  override {
		m_list_observer_.emplace_back(observer);
	}

	void detach(std::shared_ptr<IObserver> observer) override {
		m_list_observer_.remove(observer);
	}

	void notify() override {
		auto tmp_iterator = m_list_observer_.begin();
		how_many_observers();

		while (tmp_iterator != m_list_observer_.end()) {
			(*tmp_iterator)->update(m_msg_);
			++tmp_iterator;
		}
	}

	void create_message(std::string &&msg = "Empty") {
		m_msg_ = std::move(msg);
		notify();
	}

	void how_many_observers() const {
		std::cout << "There are " << m_list_observer_.size()
			<< " observers in the list.\n";
	}
	void some_business_logic() {
		m_msg_ = "change m_msg_ msg";
		notify();
		std::cout << "I'm about to do some thing important\n";
	}
private:
	std::list<std::shared_ptr<IObserver>> m_list_observer_;
	std::string m_msg_;
};

class Observer final : public IObserver,
	public std::enable_shared_from_this<Observer>
{
public:
	Observer() = default;
	Observer(Observer const &) = default;
	Observer &operator=(Observer const &) = default;
	Observer(Observer &&) noexcept = default;
	Observer &operator=(Observer &&) noexcept = default;
	~Observer() override {
		std::cout << "Goodbye, I was the Observer \"" << m_number_ << "\".\n";
	}

	void set_subject(std::shared_ptr<Subject> subject) {
		m_subject_ = std::move(subject);
		std::cout << "Hi, I'm the Observer \"" << ++m_st_number_ << "\".\n";
		m_subject_->attach(shared_from_this());
		m_number_ = m_st_number_;
	}

	void update(const std::string &msg_from_subject) override {
		m_msg_from_subject_ = msg_from_subject;
		print_info();
	}

	void remove_me_from_the_list() {
		m_subject_->detach(shared_from_this());
		std::cout << "Observer \"" << m_number_ << "\" removed from the list.\n";
	}

	void print_info() const {
		std::cout << "Observer \"" << m_number_ << "\": a new message is available --> "
			<< m_msg_from_subject_ << "\n";
	}
private:
	std::shared_ptr<Subject> m_subject_;
	std::string m_msg_from_subject_;
	inline static size_t m_st_number_{};
	size_t m_number_{};
};


//main()
#if 0
void client_code() {
	auto main_subject = std::make_shared<Subject>();
	auto main_observer1 = std::make_shared<Observer>();
	main_observer1->set_subject(main_subject);
	auto main_observer2 = std::make_shared<Observer>();
	main_observer2->set_subject(main_subject);
	auto main_observer3 = std::make_shared<Observer>();
	main_observer3->set_subject(main_subject);
	auto main_observer4 = std::make_shared<Observer>();
	auto main_observer5 = std::make_shared<Observer>();

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

int main() {
	client_code();
}


//-----output
/*
Hi, I'm the Observer "1".
Hi, I'm the Observer "2".
Hi, I'm the Observer "3".
There are 3 observers in the list.
Observer "1": a new message is available-- > Hello World!:D
Observer "2" : a new message is available-- > Hello World!:D
Observer "3" : a new message is available-- > Hello World!:D
Observer "3" removed from the list.
There are 2 observers in the list.
Observer "1" : a new message is available-- > The weather is hot today!:p
Observer "2" : a new message is available-- > The weather is hot today!:p
Hi, I'm the Observer "4".
Observer "2" removed from the list.
Hi, I'm the Observer "5".
There are 3 observers in the list.
Observer "1" : a new message is available-- > My new car is great!;)
Observer "4": a new message is available-- > My new car is great!;)
Observer "5": a new message is available-- > My new car is great!;)
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
#endif
