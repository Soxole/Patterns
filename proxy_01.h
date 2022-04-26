#pragma once
#include <iostream>
#include <memory>
/*
 �����������
 
����������� � ��� ������, ������� ��������� ���������� ����� �������� � �������� ��������� ��������. 
����������� �������� ������ �� �������, ��������� ���� ������� (�������� �������, �����������, 
��������� ������� � ������), � ����� ������� ����� ���������� �������.
*/


class ISubject
{
public:
	virtual~ISubject() = default;
	virtual void request() const = 0;
};

class RealSubject : public ISubject
{
public:
	void request() const override
	{
		std::cout << "RealSubject: Handling request.\n";
	}
};

class Proxy final : public ISubject
{
public:
	Proxy(std::unique_ptr<RealSubject> realSubject) 
		: m_realSubject{std::make_unique<RealSubject>(*realSubject)}
	{
	}
	void request() const override
	{
		if (checkAccess())
		{
			m_realSubject->request();
			this->logAccess();
		}
	}

private:
	std::unique_ptr<RealSubject> m_realSubject;

	[[nodiscard]] bool checkAccess() const
	{
		std::cout << "Proxy: Checking access prior to firing a real request.\n";
		return true;
	}
	void logAccess() const
	{
		std::cout <<"Proxy: Logging the time of request.\n";
	}
};

/*
void clientCode(const ISubject &sub)
{
	sub.request();
}

int main()
{
	cout << "Client: Executing the client code with a real subject:\n";
	auto ptrRealSubject{make_unique<RealSubject>()};
	clientCode(*ptrRealSubject);
	cout << "\n";
	cout << "Client: Executing the same client code with a proxy:\n";
	//ptrProxy � main() ������� Proxy, � � ������ ��������� RealSubject � ��������� ��� �����, 
	//������� � ���������������� request() �������� ���� ����� RealSubject
	auto ptrProxy{make_unique<Proxy>(move(ptrRealSubject))};
	clientCode(*ptrProxy);
*/