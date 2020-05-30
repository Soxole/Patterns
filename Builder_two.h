#pragma once
#include <iostream>
#include <vector>
#include <memory>

//������� Builder ���������� ������� ���������� ��������������� �������� �������, � ���������� �������� ����� ���������� ������ ������������� ����� �������.


using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::cout;
using std::endl;

// ������ ���� ��������� ����� �����
class Infantryman
{
public:
	void info() {
		cout << "Infantryman" << endl;
	}
};

class Archer
{
public:
	void info() {
		cout << "Archer" << endl;
	}
};

class Horseman
{
public:
	void info() {
		cout << "Horseman" << endl;
	}
};

class Catapult
{
public:
	void info() {
		cout << "Catapult" << endl;
	}
};

class Elephant
{
public:
	void info() {
		cout << "Elephant" << endl;
	}
};


// ����� "�����", ���������� ��� ���� ������ ������
class Army
{
public:
	vector<Infantryman> vi;
	vector<Archer>      va;
	vector<Horseman>    vh;
	vector<Catapult>    vc;
	vector<Elephant>    ve;

	void info() {
		size_t i;
		for (i = 0; i < vi.size(); ++i)  vi[i].info();
		for (i = 0; i < va.size(); ++i)  va[i].info();
		for (i = 0; i < vh.size(); ++i)  vh[i].info();
		for (i = 0; i < vc.size(); ++i)  vc[i].info();
		for (i = 0; i < ve.size(); ++i)  ve[i].info();
	}
	void infoSizeArmy()
	{
		cout << vi.size() << endl;
		cout << va.size() << endl;
		cout << vh.size() << endl;
		cout << vc.size() << endl;
		cout << ve.size() << endl;
	}
};


// ������� ����� ArmyBuilder ��������� ��������� ��� ���������� 
// ���������� ����� � ��������������� ��� ���������� �� ���������

class ArmyBuilder
{
protected:
	//Army *p;
	unique_ptr<Army> p = nullptr;
public:
	//ArmyBuilder() : p(nullptr) {}
	virtual ~ArmyBuilder() {}
	virtual void createArmy() {}
	virtual void buildInfantryman() {}
	virtual void buildArcher() {}
	virtual void buildHorseman() {}
	virtual void buildCatapult() {}
	virtual void buildElephant() {}

	virtual unique_ptr<Army> getArmy() { return std::move(p); }
};


// ������� ����� ����� ��� ���� ������ ������ ����� ������ ������
class RomanArmyBuilder : public ArmyBuilder
{	
public:
	void createArmy() {p = make_unique<Army>(); }
	void buildInfantryman() override { p->vi.push_back(Infantryman()); }
	void buildArcher() override { p->va.push_back(Archer()); }
	void buildHorseman() override { p->vh.push_back(Horseman()); }
	void buildCatapult() override { p->vc.push_back(Catapult()); }
	
};


// ����� ��������� ����� ��� ���� ������ ������ ����� ���������
class CarthaginianArmyBuilder : public ArmyBuilder
{
public:
	void createArmy() override { p = make_unique<Army>(); }
	void buildInfantryman() override { p->vi.push_back(Infantryman()); }
	void buildArcher() override { p->va.push_back(Archer()); }
	void buildHorseman() override { p->vh.push_back(Horseman()); }
	void buildElephant() override { p->ve.push_back(Elephant()); }
};


// �����-�������������, �������� ��������� ����� ��� ��� ���� �������.
// ������ ����� ��������� �������� ���������� �����.
class Director
{
public:
	unique_ptr<Army> createArmy(ArmyBuilder &builder)
	{
		builder.createArmy();
		builder.buildInfantryman();
		builder.buildArcher();
		builder.buildHorseman();
		builder.buildCatapult();
		builder.buildElephant();

		return builder.getArmy();
	}
};

//Director dir;
//RomanArmyBuilder ra_builder;
//CarthaginianArmyBuilder ca_builder;
//
//unique_ptr<Army> ra = dir.createArmy(ra_builder);
//unique_ptr<Army> ca = dir.createArmy(ca_builder);
//cout << "Roman army:" << endl;
//ra->info();
//cout << "\nCarthaginian army:" << endl;
//ca->info();