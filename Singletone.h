#pragma once

/*
 http://cpp-reference.ru/patterns/creational-patterns/singleton/
 Внутри getInstance() используется статический экземпляр нужного класса. Стандарт языка
 программирования C++ гарантирует автоматическое уничтожение статических объектов при
 завершении программы.

 К сожалению, у реализации Мэйерса есть недостатки: сложности создания объектов производных
 классов и невозможность безопасного доступа нескольких клиентов к единственному объекту в
 многопоточной среде.
 */


class SingletonMaers
{
	SingletonMaers() = default;
	SingletonMaers(const SingletonMaers &) = default;
	SingletonMaers &operator=(SingletonMaers &) = default;
public:
	static SingletonMaers &getInstance() {
		static SingletonMaers instance;
		return instance;
	}
};

