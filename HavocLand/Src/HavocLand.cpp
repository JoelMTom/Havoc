#include <Havoc.h>


class ExampleLayer : public Havoc::Layer
{
public:
	ExampleLayer()
		:Layer("Example Layer")
	{

	}

	void OnUpdate() override
	{
		//H_CLIENT_INFO("Example Layer::Update");
	}

	void OnEvent(Havoc::Event& e)
	{
		H_CLIENT_DEBUG("{0}", e.ToString());
	}
};

class HavocLand : public Havoc::Application
{

public:

	HavocLand(const char* name)
		:Havoc::Application(name)
	{
		PushLayer(new ExampleLayer());
	}
	
	~HavocLand()
	{

	}
};

Havoc::Application* Havoc::CreateApplication()
{
	return new HavocLand("HavocLand");
}