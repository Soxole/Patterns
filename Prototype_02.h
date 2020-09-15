#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <array>


using std::string;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;



class Stooge
{
public:
	virtual void slap_stick() = 0;
	virtual unique_ptr<Stooge> clone() = 0;
};


class Larry : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Larry " << endl;
	}
	virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Larry>();
	}
	virtual~Larry() = default;
};


class Moe : public Stooge
{
public:
	virtual void slap_stick() override
	{
		cout << "class Moe " << endl;
	}
	virtual unique_ptr<Stooge> clone() override
	{
		return make_unique<Moe>();
	}
	virtual~Moe() = default;
};

//������� 
class Factory
{
public:
	static inline unique_ptr<Stooge> make_stooge(int choice)
	{
		return s_prototypes[choice]->clone();
	}
protected:
	static inline std::array<unique_ptr<Stooge>, 3> s_prototypes = {		//using std::array<> � �������� ��� ���������� ��������� ������
		nullptr, make_unique<Larry>(), make_unique<Moe>()
	};

};


/*
	int main()
	{

		vector<unique_ptr<Stooge>> vecProt;

		auto objLarry = Factory::make_stooge(1);
		auto objMoe = Factory::make_stooge(2);
		vecProt.emplace_back(move(objMoe));						<--������������ std::move(), ��� ���������� ��������� � ������ ����������
		vecProt.emplace_back(move(Factory::make_stooge(2)));	// ��� ���������� �������� ������� ����� ������� ����� ��������
		vecProt.emplace_back(move(objLarry));

		for (const auto &it : vecProt)
			it->slap_stick();

		return 0;
	}

*/
