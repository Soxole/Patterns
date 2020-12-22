#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

//����������� ������� 1; ��������� ��� ���������
struct IDrawer
{
	virtual void draw() const = 0;
};
//����������; ������ � ������� OpenGL
struct GLDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};
//����������; ������ � ������� DirectX
struct DirectXDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

//����������� ������� 2; ��������� ��� �������� ��������� �� ����
struct INetworkSender
{
	virtual void sendData() const = 0;
};
// �������� ��������� �� ��������� ����
struct NetworkWiredSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by Wired" << std::endl;
	}
};
// �������� ��������� � ������� GSM ������
struct NetworkGSMSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by GSM" << std::endl;
	}
};

//����������� ������� 3; ��������� ��� �������� ������ � ����
struct IDataBase
{
	virtual void save() const = 0;
};
// �������� � �������� ����
struct LocalDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on local" << std::endl;
	}
};
// �������� � ��������� ����
struct RemoteDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on remote" << std::endl;
	}
};



//����������� �������
// ��������� ������� ��� ��������� AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() const = 0;
	virtual unique_ptr<INetworkSender> createNetwork() const = 0;
	virtual unique_ptr<IDataBase> createDataBase() const = 0;
};
// ���������� ������� 1 (��� ��������� � OpenGL, Wired Network, Local DB)
struct AppCorePlatformFactory : public IAppCoreFactory
{
	[[nodiscard]] virtual unique_ptr<IDrawer> createDrawer() const override
	{
		return make_unique<GLDrawer>();
	}
	[[nodiscard]] virtual unique_ptr<INetworkSender> createNetwork() const override
	{
		return make_unique<NetworkWiredSender>();
	}
	[[nodiscard]] virtual unique_ptr<IDataBase> createDataBase() const override
	{
		return make_unique<LocalDB>();
	}
};

// ���������� ������� 2 (��� ��������� � DirectX, GSM Network, Remote DB)
struct AppCorePlatformFactory2 : public IAppCoreFactory
{
	[[nodiscard]] virtual unique_ptr<IDrawer> createDrawer() const override
	{
		return make_unique<DirectXDrawer>();
	}
	[[nodiscard]] virtual unique_ptr<INetworkSender> createNetwork() const override
	{
		return make_unique<NetworkGSMSender>();
	}
	[[nodiscard]] virtual unique_ptr<IDataBase> createDataBase() const override
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
		else if (mNetwork)
			mNetwork->sendData();
		else if (mDB)
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
	globalCore = std::make_unique<AppCore>(std::move(factory)); - constr appCore
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