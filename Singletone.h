#pragma once

//����������� �������� Singleton �������� �� ���� ������������� ���������� ����������, ������� ��������� ������ ��������:
//1. ����� ���������� �������� ������.����� ����� ���������� ���������� - �� ������� ��������� �� �� ����������.
//2. ������������� ���������� ������, �� ����, ����� ���������� ����� ���� �������� �� ����� ����� ���������.


//class SingleTone;
//
//class SingleToneDestroyer
//{
//private:
//	SingleTone *p_inst;
//public:
//	SingleToneDestroyer() = default;
//	~SingleToneDestroyer() { delete p_inst; }
//	void initialize(SingleTone *ptr) { p_inst = ptr; }
//
//};
//
//
//class SingleTone
//{
//private:
//	static SingleTone *p_inst;
//	static SingleToneDestroyer destroyer;
//protected:
//	SingleTone() = default;
//	~SingleTone() = default;
//	friend class SingleToneDestroyer;
//public:
//	static SingleTone &getInst(); //�������� ���������� ����������� ����� getInstance, ������� ���������� ������������ ��������� ������	������
//};


