#pragma once
#include <iostream>
#include <memory>
/*
Заместитель — это структурный паттерн проектирования, который позволяет
подставлять вместо реальных объектов специальные объекты-заменители.
Эти объекты перехватывают вызовы к оригинальному объекту, позволяя
сделать что-то до или после передачи вызова оригиналу.

Применимость: Паттерн Заместитель применяется в C++ коде тогда, когда надо
заменить настоящий объект его суррогатом, причём незаметно для клиентов
настоящего объекта. Это позволит выполнить какие-то добавочные поведения
до или после основного поведения настоящего объекта.

Признаки применения паттерна: Класс заместителя чаще всего делегирует всю
настоящую работу своему реальному объекту. Заместители часто сами следят
за жизненным циклом своего реального объекта.
*/


class ISubject
{
public:
	ISubject() = default;
	ISubject(ISubject const &) = default;
	ISubject &operator=(ISubject const &) = default;
	ISubject(ISubject && ) noexcept = default;
	ISubject &operator=(ISubject &&) noexcept = default;
	virtual~ISubject() = default;

	virtual void request() const = 0;
};

class RealSubject final : public ISubject
{
public:
	void request() const override {
		std::cout << "RealSubject: Handling request.\n";
	}
};

//proxy object
class Proxy final : public ISubject
{
public:
	explicit Proxy(std::unique_ptr<RealSubject> realSubject)
		: m_realSubject{ std::make_unique<RealSubject>(*realSubject) } {}

	void request() const override {
		if (checkAccess()) {
			m_realSubject->request();
			logAccess();
		}
	}
private:
	[[nodiscard]] bool checkAccess() const {
		std::cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void logAccess() const {
		std::cout << "Proxy: Logging the time of request.\n";
	}
private:
	std::unique_ptr<RealSubject> m_realSubject;
};


//main()
#if 0
void clientCode(const ISubject &sub) {
	sub.request();
}

std::cout << "Client: Executing the client code with a real subject:\n";
auto ptrRealSubject = std::make_unique<RealSubject>();
clientCode(*ptrRealSubject);
std::cout << "\n";
std::cout << "Client: Executing the same client code with a proxy:\n";
auto ptrProxy = std::make_unique<Proxy>(std::move(ptrRealSubject));
clientCode(*ptrProxy);

#endif
