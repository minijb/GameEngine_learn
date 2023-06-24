#pragma once

#include "Core.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:

		Application();
		virtual ~Application();

		void run();
	};

	//to be define in client
	Application* createApplication();


}

