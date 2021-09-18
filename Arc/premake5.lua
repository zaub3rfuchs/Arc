project "Arc"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "apch.h"
	pchsource "src/apch.cpp"

	LibraryDir = {}
	LibraryDir["mono"] = "vendor/mono/lib/Debug/mono-2.0-sgen.lib"

	
	files
	{
		"src/**.h",
		"src/**.cpp",

		"vendor/stb_image/**.cpp",
		"vendor/stb_image/**.h",

		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.mono}"
	}

	links
	{
		"GLFW",
		"Box2D",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib",
		"%{LibraryDir.mono}"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags {"NoPCH"}


	filter "system:windows"
		systemversion "latest"
		
		filter "configurations:Debug"
			defines "ARC_DEBUG"
			runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "ARC_RELEASE"
			runtime "Release"
			optimize "on"

		filter "configurations:Dist"
			defines "ARC_DIST"
			runtime "Release"
			optimize "on"