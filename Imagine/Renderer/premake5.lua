project "Renderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/")
    objdir ("bin-int/")

    files {
        "src/**.h",
        "src/**.cpp",
        "../vendor/GLAD/src/glad.c",
    }

    includedirs {
        "../vendor/GLFW/include/GLFW",
        "C:/VulkanSDK/1.3.204.1/Include",
        "../vendor/GLM/glm/glm",
        "../vendor/GLAD/include/glad",
        "../vendor/GLAD/include/KHR",
        "../InternalCore/VulkanAPI/VulkanAPI/src",
        --"../vendor/IMGUI",
        --"../vendor/IMGUI/backends",

        --"../vendor/YAML/include/yaml-cpp"
    }

    libdirs{
        "C:/VulkanSDK/1.3.204.1/Lib",
        "../InternalCore/VulkanAPI/VulkanAPI/bin",
        --"../vendor/YAML/lib"
    }

    links {
        "GLFW",
        "vulkan-1.lib",
        "VulkanAPI.lib",
        --"IMGUI",
        
        --"yaml-cpp.lib"
    }