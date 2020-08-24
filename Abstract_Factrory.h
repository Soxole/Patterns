#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

//абстрактный продукт 1
// интерфейс для рисования
struct IDrawer
{
	virtual void draw() = 0;
};
//подпродукт
// рисуем с помощью OpenGL
struct GLDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};
//подпродукт
// рисуем с помощью DirectX
struct DirectXDrawer : IDrawer
{
	void draw() override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

//абстрактный продукт 2
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

//абстрактный продукт 3
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



//АБСТРАКТНАЯ ФАБРИКА
// интерфейс фабрики для семейства AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() = 0;
	virtual unique_ptr<INetworkSender> createNetwork() = 0;
	virtual unique_ptr<IDataBase> createDataBase() = 0;
};
// конкретная фабрика 1 (для платформы с OpenGL, Wired Network, Local DB)
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

// конкретная фабрика 1 (для платформы с DirectX, GSM Network, Remote DB)
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

/*
unique_ptr<AppCore> globalCore;
int variant = 0;
// загружаем что-то
// или проверяем на доступность библиотек для:
// рисования, баз данных, сети

// ...
variant = 0;// std::rand() % 2;
// в зависимости от возможностей, выбираем нужную фабрику
// которая настраивает наше ядро на определенные библиотеки
// создавая объекты различных типов
// которые совершенно не связаны друг с другом
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