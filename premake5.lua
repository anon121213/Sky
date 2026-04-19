workspace "Sky"
	architecture "x64"
	startproject "Sandbox"
	
	configurations {
		"Debug",
		"Release",
		"Dist"
	}

	flags {
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "%{wks.location}/Sky/vendor/GLFW/include"
	IncludeDir["Glad"] = "%{wks.location}/Sky/vendor/Glad/include"
	IncludeDir["ImGui"] = "%{wks.location}/Sky/vendor/imgui"
	IncludeDir["glm"] = "%{wks.location}/Sky/vendor/glm"
	IncludeDir["stb_image"] = "%{wks.location}/Sky/vendor/stb_image"
	IncludeDir["entt"] = "%{wks.location}/Sky/vendor/entt/include"
	IncludeDir["yaml_cpp"] = "%{wks.location}/Sky/vendor/yaml-cpp/include"

	group "Dependencies"
		include "Sky/vendor/GLFW"
		include "Sky/vendor/Glad"
		include "Sky/vendor/imgui"
		include "Sky/vendor/yaml-cpp"
	group ""

	include "Sky"
	include "Sandbox"
	include "Sky-Editor"