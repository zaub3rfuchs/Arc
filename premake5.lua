workspace "Arc"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Arc/vendor/GLFW/include"
IncludeDir["Glad"] = "Arc/vendor/Glad/include"
IncludeDir["imGui"] = "Arc/vendor/imgui"

group "Dependencies"
	include "Arc/vendor/GLFW"
	include "Arc/vendor/Glad"
	include "Arc/vendor/imgui"

group ""

project "Arc"
	location "Arc"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS",
			"ARC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

		
		filter "configurations:Debug"
			defines "ARC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "ARC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "ARC_DIST"
			runtime "Release"
			optimize "On"

		--filter {"system:windows", "configurations:Release"}
			--buildoptiopns "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"


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
		systemversion "latest"

		defines
		{
			"ARC_PLATFORM_WINDOWS"
		}
		
		filter "configurations:Debug"
			defines "ARC_DEBUG"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			defines "ARC_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "ARC_DIST"
			runtime "Release"
			optimize "On"