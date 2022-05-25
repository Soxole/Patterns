#pragma once

class FahrenheitSensor
{
public:
	FahrenheitSensor() = default;
	~FahrenheitSensor() = default;

	[[nodiscard]] float getFahrenheitTemp() const {
		float t = 125.5f;
		return t;
	}
protected:
	void f_adjust() { }
};

class ISensor
{
public:
	virtual~ISensor() = default;
	[[nodiscard]] virtual float getTemperature() const = 0;
	virtual void adjust() = 0;
};

class Adapter final : public ISensor, private FahrenheitSensor
{
public:
	Adapter() = default;

	[[nodiscard]] float getTemperature() const override {
		const auto tCelsius = (getFahrenheitTemp() - 32.0f) * 5.0f / 9.0f;
		return tCelsius;
	}
	void adjust() override {
		FahrenheitSensor::f_adjust();
	}

};


//main()
#if 0
	std::unique_ptr<ISensor> pSensor = std::make_unique<Adapter>();
	pSensor->adjust();
	std::cout << std::fixed << std::showpoint << std::setprecision(1);
	std::cout << pSensor->getTemperature() << '\n';
#endif
