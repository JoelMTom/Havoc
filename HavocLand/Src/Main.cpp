#include <Havoc.h>


class HavocLand : public Havoc::Application
{

public:

	HavocLand(const char* name)
		:Havoc::Application(name)
	{

	}
	
	~HavocLand()
	{

	}
};

Havoc::Application* Havoc::CreateApplication()
{
	return new HavocLand("HavocLand");
}