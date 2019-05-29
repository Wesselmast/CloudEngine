workspace "CloudEngine"
	architecture "x64";

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"CLD_PLATFORM_WINDOWS",
			"CLD_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "CLD_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CLD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CLD_DIST"
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
		symbols "On"

	filter "configurations:Release"
		defines "CLD_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CLD_DIST"
		optimize "On"
	