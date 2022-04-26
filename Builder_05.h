#pragma once

#include <iostream>
#include <string>
#include <memory>

struct Base
{
	int price;
};

struct Wheel final : Base
{
	int size;
};

struct Engine final : Base
{
	int power;
};

struct Body final : Base
{
	std::string type;
};

struct Car final
{
	void print_info()
	{
		std::cout << "Model name   : " << mName << std::endl;
		std::cout << "Body type    : " << mBody->type << std::endl;
		std::cout << "Engine power : " << mEngine->power << std::endl;
		std::cout << "Wheel size   : " << mWheel[0]->size << std::endl;

		std::cout << "Common price : " << mWheel[0]->price * 4
			+ mEngine->price
			+ mBody->price
			<< std::endl;

	}
	std::string mName;
	std::unique_ptr<Wheel>  mWheel[4];
	std::unique_ptr<Engine> mEngine;
	std::unique_ptr<Body>   mBody;
};

//interface of the concrete class
struct Builder
{
	virtual ~Builder() = default;
	virtual std::unique_ptr<Wheel>  make_wheel() = 0;
	virtual std::unique_ptr<Engine> make_engine() = 0;
	virtual std::unique_ptr<Body>   make_body() = 0;
	std::string mName;
};


struct AudiQ7Diesel final : Builder
{
	AudiQ7Diesel()
	{
		mName = "Audi Q7 Diesel";
	}

	std::unique_ptr<Wheel> make_wheel() override
	{
		auto wheel = std::make_unique<Wheel>();
		wheel->price = 100;
		wheel->size = 19;
		return wheel;
	}

	std::unique_ptr<Engine> make_engine() override
	{
		auto engine = std::make_unique<Engine>();
		engine->price = 2000;
		engine->power = 500;
		return engine;
	}

	std::unique_ptr<Body> make_body() override
	{
		auto body = std::make_unique<Body>();
		body->price = 3000;
		body->type = "SUV";
		return body;
	}
	~AudiQ7Diesel() override = default;
};

struct AudiTTGasoline final : Builder
{
	AudiTTGasoline()
	{
		mName = "Audi TT Gasoline";
	}

	std::unique_ptr<Wheel> make_wheel() override
	{
		auto wheel = std::make_unique<Wheel>();
		wheel->price = 150;
		wheel->size = 17;
		return wheel;
	}

	std::unique_ptr<Engine> make_engine() override
	{
		auto engine = std::make_unique<Engine>();
		engine->price = 2500;
		engine->power = 310;
		return engine;
	}

	std::unique_ptr<Body> make_body() override
	{
		auto body = std::make_unique<Body>();
		body->price = 2500;
		body->type = "coupe";
		return body;
	}
};

struct Director final
{
	void setBuilder(std::unique_ptr<Builder> aBuilder)
	{
		mBuilder = std::move(aBuilder);
	}

	std::unique_ptr<Car> makeCar()
	{
		auto res = std::make_unique<Car>();

		res->mName = mBuilder->mName;
		res->mWheel[0] = mBuilder->make_wheel();
		res->mWheel[1] = mBuilder->make_wheel();
		res->mWheel[2] = mBuilder->make_wheel();
		res->mWheel[3] = mBuilder->make_wheel();
		res->mBody = mBuilder->make_body();
		res->mEngine = mBuilder->make_engine();

		return res;
	}

	std::unique_ptr<Builder> mBuilder;
};

//main()
#if 0
Director director;
director.setBuilder(std::make_unique<AudiQ7Diesel>());

std::unique_ptr<Car> audiQ7(std::make_unique<Car>());
audiQ7 = director.makeCar();
audiQ7->print_info();

std::cout << std::endl;
std::cout << std::endl;

director.setBuilder(std::make_unique<AudiTTGasoline>());
std::unique_ptr<Car> audiTT(std::make_unique<Car>());
audiTT = director.makeCar();
audiTT->print_info();
#endif
