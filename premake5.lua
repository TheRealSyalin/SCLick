workspace "sclick-DrawingProgram"
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

	project "sclick"
	location "sclick"
	   kind "ConsoleApp"
	   language "C++"
	   cppdialect "c++17"
	   links {"sclick-lib"}
	   targetdir "bin/%{cfg.buildcfg}"
	   objdir "sclick/obj/%{cfg.buildcfg}"
	   files { "sclick/src/**.h", "sclick/src/**.cpp" }
	   architecture "x86_64"
	   defines { "UNICODE" }

	   --pchheader "pch.h"
	   --pchsource "sclick/src/z_pch/pch.cpp"

	   includedirs {
		   "sclick-lib/include",
		   "sclick-lib/src"
		   --"sclick/src/z_pch",
	   }

	 project "sclick-lib"
	    location "sclick-lib"
		kind "StaticLib"
		language "C++"
		cppdialect "c++17"
		links {"d2d1", "d3d11"}
		targetdir "bin/%{cfg.buildcfg}"
		objdir "sclick-lib/obj/%{cfg.buildcfg}"
		files { "sclick-lib/src/**.h", "sclick-lib/src/**.cpp" }
	    architecture "x86_64"
	    defines { "UNICODE" }

			pchheader "pch.h"
			pchsource "sclick-lib/src/z_pch/pch.cpp"

	    includedirs {
		    "sclick-lib/src/z_pch",
			"sclick-lib/src",
	   }

	   externalincludedirs {
		"sclick-lib/src"
	   }
	
	
	   
	
	