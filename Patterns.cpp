#include <iostream>
#include "FMethod.h"
#include <vector>
#include <memory>

using namespace std;

int main()
{
	using uptr = std::unique_ptr<BaseTank>();
	vector<uptr> tanks;
	tanks.emplace_back(BaseTank::make_tank(eTankType::T34_USA));

	cout << endl;
	return 0;
}

