#include "Application.h"
#include "iostream"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Log.h"
namespace Engine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e ( 1800, 720 );
		E_TRACE ( e );
		while ( true );
	}
}


