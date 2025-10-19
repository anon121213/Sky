workspace "Sky"
	architecture "x64"
	
	configurations {
		"Debug",
		"Relese",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sky"
	location "Sky"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"Sky/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions "/utf-8" 

	defines {
		"SKY_PLATFORM_WINDOWS",
		"SKY_BUILD_DLL"
	}

	postbuildcommands {
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "SKY_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SKY_DIST"
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
		"Sky/src"
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
		optimize "On"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "SKY_DIST"
		optimize "On"
