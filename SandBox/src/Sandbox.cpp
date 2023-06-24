#include "Engine.h"

class SandBox: public Engine :: Application
{
public:
	~SandBox() override
	{
		
	}
	SandBox()
	{
		
	}
};


Engine::Application* Engine::createApplication()
{
	return new SandBox;
}