#pragma once

//Архитектура паттерна Singleton основана на идее использования глобальной переменной, имеющей следующие важные свойства:
//1. Такая переменная доступна всегда.Время жизни глобальной переменной - от запуска программы до ее завершения.
//2. Предоставляет глобальный доступ, то есть, такая переменная может быть доступна из любой части программы.


class SingleTone;

class SingleToneDestroyer
{
private:
	SingleTone *p_inst;
public:
	SingleToneDestroyer() = default;
	~SingleToneDestroyer() { delete p_inst; }
	void initialize(SingleTone *ptr) { p_inst = ptr; }

};


class SingleTone
{
private:
	static SingleTone *p_inst;
	static SingleToneDestroyer destroyer;
protected:
	SingleTone() = default;
	~SingleTone() = default;
	friend class SingleToneDestroyer;
public:
	static SingleTone &getInst(); //Одиночка определяет статический метод getInstance, который возвращает единственный экземпляр своего	класса

};


