project "YAML"
    kind "StaticLib"
    language "C++"

    defines{
        "YAML_CPP_STATIC_DEFINE"
    }

    files
    {
        "src/**.h",
        "src/**.cpp",
        "include/**h",
    }

    includedirs{
        "include",
    }       

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"