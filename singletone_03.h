#pragma once

/*
 TITLE: Singleton Mayer;
 the default constructor places into a private section;
 the get_singleton_mayer method is static method and returns object of a static class;
 */


class SingletonMayer
{
public:
	SingletonMayer(const SingletonMayer &) = delete;
	SingletonMayer(SingletonMayer &&) = delete;
	SingletonMayer &operator=(const SingletonMayer &) = delete;
	SingletonMayer &operator=(SingletonMayer &&) = delete;
	static SingletonMayer &get_singleton_mayer()
	{
		static SingletonMayer tmp;
		return tmp;
	}
private:
	SingletonMayer() = default;
};

//int main(int argc, const char *argv[])  // NOLINT(bugprone-exception-escape)
//{
//	SingltonMayersa &sm{SingltonMayersa::get_singlton_mayersa()};
//
//	std::cout << endl;
//	return 0;
//}