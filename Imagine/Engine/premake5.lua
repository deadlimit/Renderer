project "Engine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/")
    objdir ("bin-int/")

    defines { "OPENGL" }

    files {
        "src/EngineCore/**.h",
        "src/EngineCore/**.cpp",
        "src/Subsystems/Renderer/**.h",
        "src/Subsystems/Renderer/**.cpp",
        "src/Subsystems/Renderer/OpenGL/**.h",
        "src/Subsystems/Renderer/OpenGL/**.cpp",
        "src/Subsystems/GUI/**.h",
        "src/Subsystems/GUI/**.cpp",
        "src/Subsystems/GUI/Windows/**.h",
        "src/Subsystems/GUI/Windows/**.cpp",
        "../vendor/GLAD/src/glad.c",
    }

    includedirs {
        "../vendor/GLFW/include/GLFW",
        "../vendor/GLM/glm/glm",
        "../vendor/GLAD/include/glad",
        "../vendor/GLAD/include/KHR",
        "../Renderer",
        "../Renderer/OpenGL",
        --"../InternalCore/Vulkan/VulkanAPI/src",
        --"../InternalCore/OpenGL/OpenGLAPI/src",
        "../vendor/IMGUI"
    }

    libdirs{
        --"C:/VulkanSDK/1.3.204.1/Lib",
        --"../InternalCore/Vulkan/VulkanAPI/bin",
        --"../InternalCore/OpenGL/OpenGLAPI/bin",
    }

    links {
        "GLFW",
        "IMGUI",
        --"vulkan-1.lib",
        --"VulkanAPI.lib",
        --"OpenGLAPI.lib",
    }