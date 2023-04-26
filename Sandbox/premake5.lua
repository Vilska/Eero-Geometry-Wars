project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++latest"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"
   
   files { "src/**.h", "src/**.cpp" }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    filter "configurations:*"
      defines { "SFML_STATIC" }
      includedirs { "../Eero/src", "../vendor/SFML/include" }
      libdirs { "../vendor/SFML/lib" }
      links {
         "Eero",
         "opengl32",
         "freetype",
         "winmm",
         "gdi32",
         "flac",
         "vorbisenc",
         "vorbisfile",
         "vorbis",
         "ogg",
         "ws2_32"
      }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      links {   
         "sfml-graphics-s-d",
         "sfml-window-s-d",
         "sfml-system-s-d",
         "sfml-audio-s-d",
         "sfml-network-s-d"
      }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      links {   
         "sfml-graphics-s",
         "sfml-window-s",
         "sfml-system-s",
         "sfml-audio-s",
         "sfml-network-s"
      }