workspace "Havoc"

    startproject "HavocLand"

    configurations 
    {
        "Debug",
        "Release"
    }

    characterset ("ASCII")

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


    platforms { "Win64" }

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"
        defines "HWin64"


    

project "Havoc"
    kind "StaticLib"
    language "C++"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "Havoc/**.h",
        "Havoc/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Havoc/Dependencies/fmt/include",
        "%{wks.location}/Havoc/Src"
    }

    location "%{wks.location}/Havoc"

    links 
    { 
        "fmt"
    }


    filter { "configurations:Debug" }
        defines { "HDEBGUG" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        defines { "HRELEASE" }
        runtime "Release"
        optimize "On"

  
project "HavocLand"
    kind "ConsoleApp"
    language "C++"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Havoc/src",
        "%{wks.location}/Havoc/Dependencies/fmt/include"
    }

    location "%{wks.location}/HavocLand"

    links 
    { 
        "Havoc"
    }

    filter { "configurations:Debug" }  
        defines { "HDEBGUG" }
        runtime "Debug"
        symbols "On"

    filter { "configurations:Release" }
        defines { "HRELEASE" }
        runtime "Release"
        optimize "On"


include "Havoc/Dependencies/fmt"
    

    

