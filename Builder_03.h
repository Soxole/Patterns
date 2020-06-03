#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>



using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::make_unique;


class House
{
public:
	void setWall(const string& wall) { this->wall = wall; }
	void setWindow(const string& window) { this->window = window; }
	void setGarage(const string& garage) { this->garage = garage; }
	void setSwimmingPool(const string& swimmingPool) { this->swimmingPool = swimmingPool; }

	void info() const { cout << "House: " << wall << " " << window << " " << garage << " " << swimmingPool << endl; }
private:
	string wall;
	string window;
	string garage;
	string swimmingPool;

};

//builder
class HouseBiulder
{
public:
	virtual~HouseBiulder() = default;

	House *getHouse() { return uPtrHouse.release(); }
	void createNewHouse() { uPtrHouse = make_unique<House>(); }

	virtual void buildWall() = 0;
	virtual void builWindow() = 0;
	virtual void buildGarage() = 0;
	virtual void buildWSwimmingPool() = 0;

protected:
	unique_ptr<House> uPtrHouse;
};



class HouseWithGarage : public HouseBiulder
{
public:
	virtual ~HouseWithGarage() override = default;
	virtual void buildWall() override { uPtrHouse->setWall("wall"); };
	virtual void builWindow() override { uPtrHouse->setWindow("window"); };
	virtual void buildGarage() override { uPtrHouse->setGarage("garage"); };
	virtual void buildWSwimmingPool() override { uPtrHouse->setSwimmingPool(""); }
};

class HouseWithSwimmingPool : public HouseBiulder
{
public:
	virtual ~HouseWithSwimmingPool() override = default;
	virtual void buildWall() override { uPtrHouse->setWall("wall"); };
	virtual void builWindow() override { uPtrHouse->setWindow("window"); };
	virtual void buildGarage() override { uPtrHouse->setGarage(""); };
	virtual void buildWSwimmingPool() override { uPtrHouse->setSwimmingPool("swimming pool"); };
};


//Director
class Director
{
public:
	void showHouse() { m_houseCreator->getHouse()->info(); };

	void createHouse(HouseBiulder *hBuilder)
	{
		m_houseCreator = hBuilder;
		hBuilder->createNewHouse();

		hBuilder->buildWall();
		hBuilder->builWindow();
		hBuilder->buildGarage();
		hBuilder->buildWSwimmingPool();
	}

private:
	HouseBiulder *m_houseCreator;
};

