#pragma once

#include <cmath>
#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

//абстрактный продукт 1; интерфейс для рисования
struct IDrawer
{
	virtual void draw() const = 0;
};
//подпродукт; рисуем с помощью OpenGL
struct GLDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};
//подпродукт; рисуем с помощью DirectX
struct DirectXDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};

//абстрактный продукт 2; интерфейс для отправки сообщений по сети
struct INetworkSender
{
	virtual void sendData() const = 0;
};
// отправка сообщения по проводной сети
struct NetworkWiredSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by Wired" << std::endl;
	}
};
// отправка сообщения с помощью GSM модуля
struct NetworkGSMSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by GSM" << std::endl;
	}
};

//абстрактный продукт 3; интерфейс для хранения данных в базе
struct IDataBase
{
	virtual void save() const = 0;
};
// хранение в локально базе
struct LocalDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on local" << std::endl;
	}
};
// хранение в удаленной базе
struct RemoteDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on remote" << std::endl;
	}
};



//АБСТРАКТНАЯ ФАБРИКА
// интерфейс фабрики для семейства AppCore
struct IAppCoreFactory
{
	virtual unique_ptr<IDrawer> createDrawer() const = 0;
	virtual unique_ptr<INetworkSender> createNetwork() const = 0;
	virtual unique_ptr<IDataBase> createDataBase() const = 0;
};
// конкретная фабрика 1 (для платформы с OpenGL, Wired Network, Local DB)
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

// конкретная фабрика 2 (для платформы с DirectX, GSM Network, Remote DB)
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