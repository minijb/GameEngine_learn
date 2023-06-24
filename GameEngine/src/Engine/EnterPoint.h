#pragma once


#ifdef E_PLATFROM_WINDOWS

extern Engine::Application* Engine::createApplication();


int main(int argc, char** args)
{
	auto app = Engine::createApplication();
	app->run();
	delete app;
	return 0;

}


#endif
