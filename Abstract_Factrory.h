#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

// ��������� ��� ���������
struct IDrawer
{
	virtual void draw() = 0;
};

// ������ � ������� OpenGL
struct GLDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};

// ������ � ������� DirectX
struct DirectXDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

/***********************************************/
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

/***********************************************/
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


// ��������� ������� ��� ��������� AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() = 0;
	virtual unique_ptr<INetworkSender> createNetwork() = 0;
	virtual unique_ptr<IDataBase> createDataBase() = 0;
};

// ������� 1 (��� ��������� � OpenGL, Wired Network, Local DB)
struct AppCorePlatformFactory : IAppCoreFactory
{
	unique_ptr<IDrawer> createDrawer() override
	{
		return make_unique<GLDrawer>();
	}
	unique_ptr<INetworkSender> createNetwork() override
	{
		return make_unique<NetworkWiredSender>();
	}
	unique_ptr<IDataBase> createDataBase() override
	{
		return make_unique<LocalDB>();
	}
};

// ������� 1 (��� ��������� � DirectX, GSM Network, Remote DB)
struct AppCorePlatformFactory2 : IAppCoreFactory
{
	unique_ptr<IDrawer> createDrawer() override
	{
		return make_unique<DirectXDrawer>();
	}
	unique_ptr<INetworkSender> createNetwork() override
	{
		return make_unique<NetworkGSMSender>();
	}
	unique_ptr<IDataBase> createDataBase() override
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