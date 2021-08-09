workspace "Arc"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-{cfg.architecture}"


--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Arc/vendor/GLFW/include"

include "Arc/vendor/GLFW"

project "Arc"
	location "Arc"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "apch.h"
	pchsource "Arc/src/apch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		
		filter "configurations:Debug"
			defines "ARC_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ARC_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "ARC_DIST"
			optimize "On"

		--filter {"system:windows", "configurations:Release"}
			--buildoptiopns "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Arc/vendor/spdlog/include",
		"Arc/src"
	}

	links
	{
		"Arc"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS"
		}
		
		filter "configurations:Debug"
			defines "ARC_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "ARC_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "ARC_DIST"
			optimize "On"