workspace "Sky"
	architecture "x64"
	
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
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8" 

	defines {
		"SKY_PLATFORM_WINDOWS",
		"SKY_BUILD_DLL",
		"GLFW_INCLUDE_NONE"
	}

	postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "SKY_DEBUG"
		buildoptions "/MDd"
		optimize "On"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SKY_DIST"
		buildoptions "/MD"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Sky/vendor/spdlog/include",
		"Sky/src",
		"%{IncludeDir.glm}",
	}

	links {
		"Sky"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8" 

	defines {
		"SKY_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
		defines "SKY_DEBUG"
		buildoptions "/MDd"
		optimize "On"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "SKY_DIST"
		buildoptions "/MD"
		optimize "On"
