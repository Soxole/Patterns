#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

// интерфейс для рисования
struct IDrawer
{
	virtual void draw() = 0;
};

// рисуем с помощью OpenGL
struct GLDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};

// рисуем с помощью DirectX
struct DirectXDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

/***********************************************/
// интерфейс для отправки сообщений по сети
struct INetworkSender
{
	virtual void sendData() = 0;
};

// отправка сообщения по проводной сети
struct NetworkWiredSender : INetworkSender
{
	void sendData() override
	{
		std::cout << "sended by Wired" << std::endl;
	}
};

// отправка сообщения с помощью GSM модуля
struct NetworkGSMSender : INetworkSender
{
	void sendData() override
	{
		std::cout << "sended by GSM" << std::endl;
	}
};

/***********************************************/
// интерфейс для хранения данных в базе
struct IDataBase
{
	virtual void save() = 0;
};

// хранение в локально базе
struct LocalDB : IDataBase
{
	void save() override
	{
		std::cout << "saved on local" << std::endl;
	}
};

// хранение в удаленной базе
struct RemoteDB : IDataBase
{
	void save() override
	{
		std::cout << "saved on remote" << std::endl;
	}
};


// интерфейс фабрики для семейства AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() = 0;
	virtual unique_ptr<INetworkSender> createNetwork() = 0;
	virtual unique_ptr<IDataBase> createDataBase() = 0;
};

// фабрика 1 (для платформы с OpenGL, Wired Network, Local DB)
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

// фабрика 1 (для платформы с DirectX, GSM Network, Remote DB)
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

// класс ядра нашей системы
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