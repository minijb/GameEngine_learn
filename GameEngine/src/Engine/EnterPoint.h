#pragma once
#include "Log.h"


#ifdef E_PLATFROM_WINDOWS

extern Engine::Application* Engine::createApplication();


int main(int argc, char** args)
{
	Engine::Log::init();
	E_CORE_WARN("Initialized log");
	int a = 5;
	E_INFO("Hello! Var={0}", a);

	auto app = Engine::createApplication();
	app->run();
	delete app;


	return 0;

}


#endif
