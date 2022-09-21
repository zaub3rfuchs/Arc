include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "Arc"
	architecture "x86_64"
	startproject "Arcanist"

	configurations
	{
		"Debug",
		"Release",
		"Dist"	
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "vendor/premake"
	include "Arc/vendor/GLFW"
	include "Arc/vendor/Glad"
	include "Arc/vendor/imgui"
	include "Arc/vendor/Box2D"
	include "Arc/vendor/yaml-cpp"
group ""

include "Arc"
include "Arcanist"
include "Sandbox"