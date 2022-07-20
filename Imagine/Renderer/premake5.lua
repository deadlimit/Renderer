project "Renderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/")
    objdir ("bin-int/")

    defines { "OPENGL" }

    files {
        "src/**.h",
        "src/**.cpp",
        "../vendor/GLAD/src/glad.c",
    }

    includedirs {
        "../vendor/GLFW/include/GLFW",
        "../vendor/GLM/glm/glm",
        "../vendor/GLAD/include/glad",
        "../vendor/GLAD/include/KHR",
        "../InternalCore/Vulkan/VulkanAPI/src",
        "../InternalCore/OpenGL/OpenGLAPI/src",
    }

    libdirs{
        "C:/VulkanSDK/1.3.204.1/Lib",
        "../InternalCore/Vulkan/VulkanAPI/bin",
        "../InternalCore/OpenGL/OpenGLAPI/bin",
    }

    links {
        "GLFW",
        "vulkan-1.lib",
        "VulkanAPI.lib",
        "OpenGLAPI.lib",
    }