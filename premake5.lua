workspace "Sky"
	architecture "x64"
	startproject "Sandbox"
	
	configurations {
		"Debug",
		"Relese",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sky/vendor/GLFW/include"
IncludeDir["Glad"] = "Sky/vendor/Glad/include"
IncludeDir["ImGui"] = "Sky/vendor/imgui"
IncludeDir["glm"] = "Sky/vendor/glm"

include "Sky/vendor/GLFW"
include "Sky/vendor/Glad"
include "Sky/vendor/imgui"

project "Sky"
	location "Sky"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "skypch.h"
	pchsource "Sky/src/skypch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"Sky/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions "/utf-8" 

		defines {
			"SKY_PLATFORM_WINDOWS",
			"SKY_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "SKY_DEBUG"
		runtime "Debug"
		optimize "on"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SKY_DIST"
		runtime "Release"
		optimize "on"

	-- this need to remove the same macros name of version in imgui.h
	filter "files:**/imgui/*.cpp"
    	disablewarnings { "4005" }

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Sky/vendor/spdlog/include",
		"Sky/src",
		"Sky/vendor",
		"%{IncludeDir.glm}",
	}

	links {
		"Sky"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions "/utf-8" 

	defines {
		"SKY_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "SKY_DEBUG"
		runtime "Debug"
		optimize "on"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "SKY_DIST"
		runtime "Release"
		optimize "on"
