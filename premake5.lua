workspace "CloudEngine"
	architecture "x64";

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "CloudEngine/vendor/glfw/include"
IncludeDir["glad"] = "CloudEngine/vendor/glad/include"
IncludeDir["imgui"] = "CloudEngine/vendor/imgui"

include "CloudEngine/vendor/glfw"
include "CloudEngine/vendor/glad"
include "CloudEngine/vendor/imgui"

project "CloudEngine"
	location "CloudEngine"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	pchheader "cldpch.h"
	pchsource "%{prj.name}/src/cldpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}"
	}

	links {
		"glfw",
		"glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CLD_PLATFORM_WINDOWS",
			"CLD_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "CLD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CLD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CLD_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("obj/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"CloudEngine/vendor/spdlog/include",
		"CloudEngine/src"
	}

	links {
		"CloudEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CLD_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CLD_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CLD_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "CLD_DIST"
		buildoptions "/MD"
		optimize "On"
	