workspace "SClick-DrawingProgram"
   configurations { "Debug", "Release" }


   filter "configurations:Debug"
	      defines { "DEBUG" }
	      symbols "On"
	
	   filter "configurations:Release"
	      defines { "NDEBUG" }
	      optimize "On"
	
		filter "system:windows"
			defines {"WINDOWS"}
	
		filter "system:linux"
			defines {"LINUX"}

	project "SClick"
	location "SClick"
	   kind "ConsoleApp"
	   language "C++"
	   cppdialect "c++17"
	   links {"SClick-lib"}
	   targetdir "bin/%{cfg.buildcfg}"
	   files { "SClick/src/**.h", "SClick/src/**.cpp" }
	   architecture "x86_64"
	   defines { "UNICODE" }

	   --pchheader "pch.h"
	   --pchsource "SClick/src/z_pch/pch.cpp"

	   includedirs {
		   "SClick-lib/include",
		   --"SClick/src/z_pch",
	   }

	 project "SClick-lib"
	    location "SClick-lib"
		kind "StaticLib"
		language "C++"
		cppdialect "c++17"
		links {"d2d1"}
		targetdir "bin/%{cfg.buildcfg}"
		files { "SClick-lib/src/**.h", "SClick-lib/src/**.cpp" }
	    architecture "x86_64"
	    defines { "UNICODE" }

			pchheader "pch.h"
			pchsource "SClick-lib/src/z_pch/pch.cpp"

	    includedirs {
		   "SClick-lib/src/z_pch",
	   }
	
	
	   
	
	