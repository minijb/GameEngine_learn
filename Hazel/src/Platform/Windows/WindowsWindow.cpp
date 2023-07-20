#include "hzpch.h"
#include "WindowsWindow.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel {
	
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallBack(int error, const char* description )
	{
		HZ_CORE_ERROR ( "GLFW Error ({0}): {1}", error, description );
	}


	//基类 -- 返回 一个 window 平台的 窗口类
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	//子类---的初始化函数
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback ( GLFWErrorCallBack );

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//set glfw callbacks

		glfwSetWindowSizeCallback ( m_Window, [ ] ( GLFWwindow* window, int width, int height )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event ( width, height );
				data.EventCallback ( event );
			} );

		glfwSetWindowCloseCallback ( m_Window, [ ] ( GLFWwindow* window )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				WindowCloseEvent event;
				data.EventCallback ( event );
			} );

		glfwSetKeyCallback ( m_Window, [ ] ( GLFWwindow* window, int key, int scancode, int action, int mods )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				switch ( action )
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event ( key, 0 );
						data.EventCallback ( event );
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event ( key );
						data.EventCallback ( event );
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event ( key, 1 );
						data.EventCallback ( event );
						break;
					}
				}
			} );

		glfwSetMouseButtonCallback ( m_Window, [ ] ( GLFWwindow* window, int button, int action, int mods )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				switch ( action ){
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event ( button );
						data.EventCallback ( event );
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event ( button );
						data.EventCallback ( event );
						break;
					}
				}
			} );

		glfwSetScrollCallback ( m_Window, [ ] ( GLFWwindow* window, double xoffset, double yoffset )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				MouseScrolledEvent event ( (float)xoffset, (float)yoffset );
				data.EventCallback ( event );
			} );

		glfwSetCursorPosCallback ( m_Window, [ ] ( GLFWwindow* window, double xpos, double ypos )
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer ( window );
				MouseMovedEvent event ( (float)xpos, (float)ypos );
				data.EventCallback ( event );
			} );
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
