project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"%{wks.location}/Sky/vendor/spdlog/include",
		"%{wks.location}/Sky/src",
		"%{wks.location}/Sky/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
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
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		defines "SKY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SKY_DIST"
		runtime "Release"
		optimize "on"