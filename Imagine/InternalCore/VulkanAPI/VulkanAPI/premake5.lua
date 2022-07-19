project "VulkanAPI"
    kind "SharedLib"
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
        "C:/VulkanSDK/1.3.204.1/Include",
        "../vendor/GLM/glm/glm",
        "../../../Renderer/src"
    }

    libdirs{
        "C:/VulkanSDK/1.3.204.1/Lib",
    }

    links {
        "GLFW",
        "vulkan-1.lib",
    }