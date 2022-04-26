#pragma once
#include <iostream>
#include <memory>
#include <string>


class House final
{
public:
	void setWall(const std::string_view wall) { m_wall_ = wall; }
	void setWindow(const std::string_view window) { m_window_ = window; }
	void setGarage(const std::string_view garage) { m_garage_ = garage; }
	void setSwimmingPool(const std::string_view swimmingPool) { m_swimming_pool_ = swimmingPool; }

	void info() const {
		std::cout << "House: " << m_wall_ << " " << m_window_ << " " << m_garage_ << " " << m_swimming_pool_ << "\n";
	}
private:
	std::string m_wall_;
	std::string m_window_;
	std::string m_garage_;
	std::string m_swimming_pool_;
};

//builder
class House_builder
{
public:
	virtual~House_builder() = default;

	void createNewHouse() { m_house = std::make_unique<House>(); }
	[[nodiscard]] std::unique_ptr<House> getHouse() { return std::move(m_house); }

	virtual void build_wall() = 0;
	virtual void build_window() = 0;
	virtual void build_garage() = 0;
	virtual void build_w_swimming_pool() = 0;

protected:
	std::unique_ptr<House> m_house;
};

//concrete builder
class HouseWithGarage final : public House_builder
{
public:
	void build_wall() override { m_house->setWall("wall"); }
	void build_window() override { m_house->setWindow("window"); }
	void build_garage() override { m_house->setGarage("garage"); }
	void build_w_swimming_pool() override {}
};

//concrete builder
class HouseWithSwimmingPool final : public House_builder
{
public:
	void build_wall() override { m_house->setWall("wall"); }
	void build_window() override { m_house->setWindow("window"); }
	void build_garage() override { m_house->setSwimmingPool("swimming pool"); }
	void build_w_swimming_pool() override {}
};

//Director
class Director final
{
public:
	void showHouse() const { m_house_builder->getHouse()->info(); }

	void createHouse(std::unique_ptr<House_builder> hBuilder) {
		m_house_builder = std::move(hBuilder);
		m_house_builder->createNewHouse();
		m_house_builder->build_wall();
		m_house_builder->build_window();
		m_house_builder->build_garage();
		m_house_builder->build_w_swimming_pool();
	}
private:
	std::unique_ptr<House_builder> m_house_builder;
};

//main()
#if 0

auto dir = std::make_unique<Director>();
auto house_garage = std::make_unique<HouseWithGarage>();
auto house_swpool = std::make_unique<HouseWithSwimmingPool>();

dir->createHouse(std::move(house_garage));
dir->showHouse();
std::cout << std::endl;
dir->createHouse(std::move(house_swpool));
dir->showHouse();

#endif
