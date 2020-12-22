#pragma once
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>

//этот пример не работает, если конструктор находится в протектед методе
class Singletone
{
public:
	Singletone(const Singletone &) = delete;
	void operator=(const Singletone &) = delete;
	explicit Singletone(const std::string &line) : m_line(line)
	{
	}

	std::string getLine() const
	{
		return m_line;
	}
	[[nodiscard]] static inline std::unique_ptr<Singletone> getInstance(const std::string &line)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (m_pInstance == nullptr)
		{
			m_pInstance = std::make_unique<Singletone>(line);
		}
		return std::move(m_pInstance);
	}

	~Singletone() = default;

protected:
	std::string m_line{ "empty" };

private:
	static inline std::unique_ptr<Singletone> m_pInstance{ nullptr };
	static inline std::mutex m_mutex{};
};

/*

void threadFoo()
{
	this_thread::sleep_for(1000ms);
	auto singletoneFoo = Singletone::getInstance("Foo");
	cout << singletoneFoo->getLine() << "\n";
}

void threadBar()
{
	this_thread::sleep_for(1000ms);
	auto singletoneFoo = Singletone::getInstance("Bar");
	cout << singletoneFoo->getLine() << "\n";
}	

int main()
{
	std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
				"If you see different values, then 2 singletons were created (booo!!)\n\n" <<
				"RESULT:\n";
	thread t1(threadFoo);
	thread t2(threadBar);
	t1.join();
	t2.join();

}


*/



/*
class Singleton
{


private:
    static Singleton * pinstance_;
    static std::mutex mutex_;

protected:
    Singleton(const std::string value): value_(value)
    {
    }
    ~Singleton() {}
    std::string value_;

public:

    Singleton(Singleton &other) = delete;

    void operator=(const Singleton &) = delete;


    static Singleton *GetInstance(const std::string& value);

    void SomeBusinessLogic()
    {
        // ...
    }
    
    std::string value() const{
        return value_;
    } 
};



Singleton* Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;


Singleton *Singleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Singleton(value);
    }
    return pinstance_;
}
*/

