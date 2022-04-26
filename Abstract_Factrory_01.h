#pragma once
#include <iostream>
#include <memory>

/*
 Абстрактная фабрика — это порождающий паттерн проектирования, который позволяет создавать
 семейства связанных объектов, не привязываясь к конкретным классам создаваемых объектов
 */

using std::unique_ptr;
using std::make_unique;


struct IDrawer
{
	virtual ~IDrawer() = default;
	virtual void draw() const = 0;
};

struct GLDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "OpenGL draw" << std::endl;
	}
};

struct DirectXDrawer : public IDrawer
{
	void draw() const override
	{
		std::cout << "DirectX draw" << std::endl;
	}
};


struct INetworkSender
{
	virtual ~INetworkSender() = default;
	virtual void sendData() const = 0;
};

struct NetworkWiredSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by Wired" << std::endl;
	}
};

struct NetworkGSMSender : public INetworkSender
{
	void sendData() const override
	{
		std::cout << "sended by GSM" << std::endl;
	}
};


struct IDataBase
{
	virtual ~IDataBase() = default;
	virtual void save() const = 0;
};

struct LocalDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on local" << std::endl;
	}
};

struct RemoteDB : public IDataBase
{
	void save() const override
	{
		std::cout << "saved on remote" << std::endl;
	}
};

//Abstract fabric
struct IAppCoreFactory
{
	virtual ~IAppCoreFactory() = default;
	virtual unique_ptr<IDrawer> createDrawer() const = 0;
	virtual unique_ptr<INetworkSender> createNetwork() const = 0;
	virtual unique_ptr<IDataBase> createDataBase() const = 0;
};

struct AppCorePlatformFactory : public IAppCoreFactory
{
	[[nodiscard]] unique_ptr<IDrawer> createDrawer() const override
	{
		return make_unique<GLDrawer>(GLDrawer{});
	}
	[[nodiscard]] unique_ptr<INetworkSender> createNetwork() const override
	{
		return make_unique<NetworkWiredSender>(NetworkWiredSender{});
	}
	[[nodiscard]] unique_ptr<IDataBase> createDataBase() const override
	{
		return make_unique<LocalDB>(LocalDB{});
	}
};


struct AppCorePlatformFactory2 : public IAppCoreFactory
{
	[[nodiscard]] unique_ptr<IDrawer> createDrawer() const override
	{
		return make_unique<DirectXDrawer>(DirectXDrawer{});
	}
	[[nodiscard]] unique_ptr<INetworkSender> createNetwork() const override
	{
		return make_unique<NetworkGSMSender>(NetworkGSMSender{});
	}
	[[nodiscard]] unique_ptr<IDataBase> createDataBase() const override
	{
		return make_unique<RemoteDB>(RemoteDB{});
	}
};


struct AppCore
{
	AppCore(unique_ptr<IAppCoreFactory> const apFactory)
		:mDrawer(apFactory->createDrawer()),
		mNetwork(apFactory->createNetwork()),
		mDB(apFactory->createDataBase())
	{}

	~AppCore() = default;

	void processing() const
	{
		if (mDrawer)
			mDrawer->draw();
		else if (mNetwork)
			mNetwork->sendData();
		else if (mDB)
			mDB->save();
	}
private:
	unique_ptr<IDrawer> mDrawer{nullptr};
	unique_ptr<INetworkSender> mNetwork{nullptr};
	unique_ptr<IDataBase> mDB{nullptr};
};

/*
	//main()

	std::unique_ptr<AppCore> global_core;
	const size_t var = 1;
	switch (var)
	{
	case 0:
	{
		auto factory = std::make_unique<AppCorePlatformFactory>(AppCorePlatformFactory{});
		global_core = std::make_unique<AppCore>(std::move(factory));
		break;
	}
	case 1:
	{
		auto factory = std::make_unique<AppCorePlatformFactory2>(AppCorePlatformFactory2{});
		global_core = std::make_unique<AppCore>(std::move(factory));
		break;
	}
	default:
		std::cout << "Default call's!" << '\n';
	}

	global_core->processing();

*/