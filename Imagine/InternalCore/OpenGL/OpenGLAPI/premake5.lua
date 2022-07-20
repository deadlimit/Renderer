project "OpenGLAPI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/")
    objdir ("bin-int/")

    files {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs {
        "../vendor/GLFW/include/GLFW",
        "../vendor/GLM/glm/glm",
        "../../../Renderer/src"
    }

    links {
        "GLFW"
    }