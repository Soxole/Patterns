#pragma once

#include <iostream>
#include <string>
#include <memory>

/*
//������������ ���������� �������� Adapter



//������ ����� � ������������
class FahrenheitSensor
{
public:
	FahrenheitSensor() = default;
	~FahrenheitSensor() = default;
	float getFahrenheitTemp() {
		float t = 104.0f;
		return t;
	}
};

//������������ �����
class ISensor
{
public:
	virtual~ISensor() = default;
	virtual float getTemperature() = 0;
};

//�������, ������� ��������� � �������
class Adapter : public ISensor
{
public:
	Adapter(std::unique_ptr<FahrenheitSensor> p) : p_fsensor(std::move(p))
	{}
	virtual float getTemperature() override {
		return (p_fsensor->getFahrenheitTemp() - 32.0f) * 5.0f / 9.0f;
	}

private:
	std::unique_ptr<FahrenheitSensor> p_fsensor;
};


������� ��������� �� ��������� ISensor, ������� ������� Adapter, ������� �������� � ������������ FahrenheitSensor
unique_ptr<ISensor> p_Isensor = make_unique<Adapter>(make_unique<FahrenheitSensor>());
cout << fixed << showpoint << setprecision(1);
cout << p_Isensor->getTemperature() << endl;
*/


//���������� �������� Adapter �� ������ ��������� ������������


class FahrenheitSensor
{
public:
	FahrenheitSensor() = default;
	~FahrenheitSensor() = default;
	float getFahrenheitTemp() {
		float t = 103.0f;
		return t;
	}
protected:
	void oldAdjust() {			// ��������� ������� (���������� �����)
	}	
};

//������������ �����
class ISensor
{
public:
	virtual~ISensor() = default;
	virtual float getTemperature() = 0;
	virtual void adjust() = 0;
};

//�������, ������� ��������� � �������
class Adapter : public ISensor, private FahrenheitSensor
{
public:
	Adapter() = default;
	virtual float getTemperature() override {
		return (p_fsensor->getFahrenheitTemp() - 32.0f) * 5.0f / 9.0f;
	}
	virtual void adjust() override {
		oldAdjust();
	}

private:
	std::unique_ptr<FahrenheitSensor> p_fsensor;
};

/*
	unique_ptr<ISensor> pSensor = make_unique<Adapter>();
	pSensor->adjust();
	cout << fixed << showpoint << setprecision(1);
	cout << pSensor->getTemperature() << endl;


*/