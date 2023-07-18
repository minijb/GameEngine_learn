workspace "GameEngine"
  architecture "x64"

  configurations
  {
    "Debug",
    "Release",
    "Dist"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "GameEngine"
  location "GameEngine"
  kind "SharedLib"
  language "C++"

  targetdir ("bin/".. outputdir .. "/%{prj.name}")
  objdir ("bin-int/".. outputdir .. "/%{prj.name}")
  
  pchheader "pch.h"
  pchsource "%{prj.name}/src/pch.cpp"

  files
  {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
  }

  includedirs
  {
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/src"
  }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    defines
    {
      "E_BUILD_DLL",
      "E_PLATFROM_WINDOWS",
      "_DEBUG",
      "_CONSOLE"
    }

    postbuildcommands
    {
      ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .. "/SandBox")
    }

  filter "configurations:Debug"
    defines "E_DEBUG"
    symbols "On"
  filter "configurations:Release"
    defines "E_RELEASE"
    symbols "On"
  filter "configurations:Dist"
    defines "E_DIST"
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
    "GameEngine/vendor/spdlog/include",
    "GameEngine/src"
  }

  links
  {
    "GameEngine"
  }

  filter "system:windows"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    defines
    {
      "E_PLATFROM_WINDOWS",
      "_DEBUG",
      "_CONSOLE"
    }

  filter "configurations:Debug"
    defines "E_DEBUG"
    symbols "On"
  filter "configurations:Release"
    defines "E_RELEASE"
    symbols "On"
  filter "configurations:Dist"
    defines "E_DIST"
    symbols "On"