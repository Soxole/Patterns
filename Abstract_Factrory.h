#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

//����������� ������� 1
// ��������� ��� ���������
struct IDrawer
{
	virtual void draw() = 0;
};
//����������
// ������ � ������� OpenGL
struct GLDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};
//����������
// ������ � ������� DirectX
struct DirectXDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

//����������� ������� 2
// ��������� ��� �������� ��������� �� ����
struct INetworkSender
{
	virtual void sendData() = 0;
};
// �������� ��������� �� ��������� ����
struct NetworkWiredSender : INetworkSender
{
	void sendData() override
	{
		std::cout << "sended by Wired" << std::endl;
	}
};
// �������� ��������� � ������� GSM ������
struct NetworkGSMSender : INetworkSender
{
	void sendData() override
	{
		std::cout << "sended by GSM" << std::endl;
	}
};

//����������� ������� 3
// ��������� ��� �������� ������ � ����
struct IDataBase
{
	virtual void save() = 0;
};
// �������� � �������� ����
struct LocalDB : IDataBase
{
	void save() override
	{
		std::cout << "saved on local" << std::endl;
	}
};
// �������� � ��������� ����
struct RemoteDB : IDataBase
{
	void save() override
	{
		std::cout << "saved on remote" << std::endl;
	}
};



//����������� �������
// ��������� ������� ��� ��������� AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() = 0;
	virtual unique_ptr<INetworkSender> createNetwork() = 0;
	virtual unique_ptr<IDataBase> createDataBase() = 0;
};
// ���������� ������� 1 (��� ��������� � OpenGL, Wired Network, Local DB)
struct AppCorePlatformFactory : IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() override
	{
		return make_unique<GLDrawer>();
	}
	virtual unique_ptr<INetworkSender> createNetwork() override
	{
		return make_unique<NetworkWiredSender>();
	}
	virtual unique_ptr<IDataBase> createDataBase() override
	{
		return make_unique<LocalDB>();
	}
};

// ���������� ������� 1 (��� ��������� � DirectX, GSM Network, Remote DB)
struct AppCorePlatformFactory2 : IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() override
	{
		return make_unique<DirectXDrawer>();
	}
	virtual unique_ptr<INetworkSender> createNetwork() override
	{
		return make_unique<NetworkGSMSender>();
	}
	virtual unique_ptr<IDataBase> createDataBase() override
	{
		return make_unique<RemoteDB>();
	}
};

// ����� ���� ����� �������
struct AppCore
{
	AppCore(unique_ptr<IAppCoreFactory> &&apFactory)
		:mDrawer(apFactory->createDrawer()), mNetwork(apFactory->createNetwork()), mDB(apFactory->createDataBase())
	{
	}

	void processing()
	{
		if (mDrawer)
			mDrawer->draw();
		if (mNetwork)
			mNetwork->sendData();
		if (mDB)
			mDB->save();
	}
private:
	unique_ptr<IDrawer> mDrawer;
	unique_ptr<INetworkSender> mNetwork;
	unique_ptr<IDataBase> mDB;
};

/*
unique_ptr<AppCore> globalCore;
int variant = 0;
// ��������� ���-��
// ��� ��������� �� ����������� ��������� ���:
// ���������, ��� ������, ����

// ...
variant = 0;// std::rand() % 2;
// � ����������� �� ������������, �������� ������ �������
// ������� ����������� ���� ���� �� ������������ ����������
// �������� ������� ��������� �����
// ������� ���������� �� ������� ���� � ������
switch (variant)
{
case 0:
{
	auto factory = std::make_unique<AppCorePlatformFactory>();
	globalCore = std::make_unique<AppCore>(std::move(factory));
	break;
}
case 1:
{
	auto factory = std::make_unique<AppCorePlatformFactory2>();
	globalCore = std::make_unique<AppCore>(std::move(factory));
	break;
}
}

// ...
globalCore->processing();
*/