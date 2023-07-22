workspace "GameEngine"
  architecture "x64"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["GLAD"] = "Hazel/vendor/GLAD/include"

include "Hazel/vendor/GLFW"
include "Hazel/vendor/GLAD"


project "Hazel"
  location "Hazel"
  kind "SharedLib"
  language "C++"

  targetdir ("bin/".. outputdir .. "/%{prj.name}")
  objdir ("bin-int/".. outputdir .. "/%{prj.name}")
  
  pchheader "hzpch.h"
  pchsource "%{prj.name}/src/hzpch.cpp"

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs
  {
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/src",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.GLAD}"
  }

  links
  {
    "GLFW",
    "GLAD",
    "opengl32.lib"
  }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    defines
    {
      "HZ_BUILD_DLL",
      "HZ_PLATFORM_WINDOWS",
      "_DEBUG",
      "_CONSOLE",
      "GLFW_INCLUDE_NONE"
    }

    postbuildcommands
    {
      ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/SandBox")
    }

  filter "configurations:Debug"
    defines "HZ_DEBUG"
    buildoptions "/MDd"
    symbols "On"
  filter "configurations:Release"
    defines "HZ_RELEASE"
    buildoptions "/MD"
    symbols "On"
  filter "configurations:Dist"
    defines "HZ_DIST"
    buildoptions "/MD"
    symbols "On"

project "SandBox"
  location "SandBox"
  kind "ConsoleApp"
  language "C++"

  targetdir ("bin/".. outputdir .. "/%{prj.name}")
  objdir ("bin-int/".. outputdir .. "/%{prj.name}")

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs
  {
    "Hazel/vendor/spdlog/include",
    "Hazel/src"
  }

  links
  {
    "Hazel"
  }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    defines
    {
      "HZ_PLATFORM_WINDOWS",
      "_DEBUG",
      "_CONSOLE"
    }

  filter "configurations:Debug"
    defines "HZ_DEBUG"
    buildoptions "/MDd"
    symbols "On"
  filter "configurations:Release"
    defines "HZ_RELEASE"
    buildoptions "/MD"
    symbols "On"
  filter "configurations:Dist"
    defines "HZ_DIST"
    buildoptions "/MD"
    symbols "On"