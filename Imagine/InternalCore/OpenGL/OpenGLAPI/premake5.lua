project "OpenGLAPI"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/")
    objdir ("bin-int/")

    files {
        "src/**.h",
        "src/**.cpp",
        "../vendor/GLAD/src/**.c",
    }

    includedirs {
        "../vendor/GLFW/include/GLFW",
        "../vendor/GLM/glm/glm",
        "../../../Renderer/src",
        "../vendor/GLAD/include/glad",
        "../vendor/GLAD/include/KHR",
    }

    links {
        "GLFW",
    }