#pragma once
#include <iostream>
#include <memory>
#include <mutex>

/*
 http://cpp-reference.ru/patterns/creational-patterns/singleton/
 Для решения этой проблемы паттерн Singleton возлагает контроль над созданием единственного
 объекта на сам класс. Доступ к этому объекту осуществляется через статическую функцию-член
 класса, которая возвращает указатель или ссылку на него. Этот объект будет создан только
 при первом обращении к методу, а все последующие вызовы просто возвращают его адрес.
 Для обеспечения уникальности объекта, конструкторы и оператор присваивания объявляются закрытыми.
 */

class Singletone
{
public:
	Singletone(const Singletone &) = delete;
	void operator=(const Singletone &) = delete;
	explicit Singletone(std::string &&line) : m_line(std::move(line)) { }
	~Singletone() noexcept = default;

	[[nodiscard]] std::string getLine() const {
		return m_line;
	}
	[[nodiscard]] static std::unique_ptr<Singletone> getInstance(std::string &&line) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!m_pInstance)
			m_pInstance = std::make_unique<Singletone>(std::move(line));

		return std::move(m_pInstance);
	}

protected:
	std::string m_line{ "empty" };

private:
	static inline std::unique_ptr<Singletone> m_pInstance;
	static inline std::mutex m_mutex;
};

//main()
#if 0
using namespace std::chrono_literals;

void threadFoo() {
	std::this_thread::sleep_for(1000ms);
	auto singletoneFoo = Singletone::getInstance("Foo");
	std::cout << singletoneFoo->getLine() << "\n";
}

void threadBar() {
	std::this_thread::sleep_for(1000ms);
	auto singletoneFoo = Singletone::getInstance("Bar");
	std::cout << singletoneFoo->getLine() << "\n";
}

int main()
{
	std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
		"If you see different values, then 2 singletons were created (booo!!)\n\n" <<
		"RESULT:\n";
	std::thread t1(threadFoo);
	std::thread t2(threadBar);
	t1.join();
	t2.join();
}
#endif


