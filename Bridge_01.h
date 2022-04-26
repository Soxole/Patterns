#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;
/*
������������: ������� ���� �������� ������� ����� ��� ���������� ������ �����-������������� ����������, ������������ ��������� �����
��� ������ ��� �������� � ������� ������������ �������� API (��������, cloud-�������, ���������� ���� � �. �.)
�������� ���������� ��������: ���� � ��������� ����� �������� ������ ������������ � ��������� ����� ������� ���������, 
������ ����������� ������� ���������� ���������� ����������, �� ����� �������, ��� � ��� ������������ ����.

 * ���������� ������������� ��������� ��� ���� ������� ����������. �� �� ������
 * ��������������� ���������� ����������. �� �������� ��� ���������� ����� ����
 * ���������� �������. ��� �������, ��������� ���������� ������������� ������
 * ����������� ��������, � �� ����� ��� ���������� ���������� �������� �����
 * �������� ������, ���������� �� ���� ����������.
 */

class IImplementation
{
public:
	virtual~IImplementation() = default;
	[[nodiscard]] virtual string operationImplement() const = 0;
};

/*
 * ������ ���������� ���������� ������������� ����������� ��������� � ���������
 * ��������� ���������� � �������������� API ���� ���������.
 */
class ConcreatImplementA : public IImplementation
{
public:
	[[nodiscard]] string operationImplement() const override {
		return "ConcreteImpA: Here's the result on the platform A.\n";
	}
};

class ConcreatImplementB final : public IImplementation
{
public:
	[[nodiscard]] string operationImplement() const override {
		return "ConcreteImpB: Here's the result on the platform B.\n";
	}
};

/*
 * ���������� ������������� ��������� ��� ������������ ����� ���� ��������
 * �������. ��� �������� ������ �� ������ �� �������� ���������� � ����������
 * ��� ��� ��������� ������.
 */
class Abstraction
{
public:
	Abstraction(unique_ptr<IImplementation> _upImpl) : upImpl(std::move(_upImpl))
	{}
	~Abstraction() = default;
	[[nodiscard]] string someOperation() const {
		return "Abstraction: Base operation with:\n" + upImpl->operationImplement();
	}

protected:
	unique_ptr<IImplementation> upImpl;
};

/*
 * ����� ��������� ���������� ��� ��������� ������� ����������.
 */
class ExtendedAbstr : public Abstraction
{
public:
	ExtendedAbstr(unique_ptr<IImplementation> _upImpl) : Abstraction(std::move(_upImpl))
	{}

	[[nodiscard]] string someOperation() const {
		return "ExtendedAbstr: Extended operation with:\n" + upImpl->operationImplement();
	}
};

/*
	unique_ptr<IImplementation> upImpl{ make_unique<ConcreatImplementA>() };
	auto upAbstr{ make_unique<Abstraction>(move(upImpl)) };
	cout << upAbstr->someOperation() << "\n";

	upImpl = make_unique<ConcreatImplementB>();
	upAbstr = make_unique<ExtendedAbstr>(move(upImpl));
	cout << upAbstr->someOperation() << "\n";
*/