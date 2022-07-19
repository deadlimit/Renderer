project "Renderer"
    kind "ConsoleApp"
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
        --"../vendor/IMGUI",
        --"../vendor/IMGUI/backends",

        --"../vendor/YAML/include/yaml-cpp"
    }

    libdirs{
        "C:/VulkanSDK/1.3.204.1/Lib",

        --"../vendor/YAML/lib"
    }

    links {
        "GLFW",
        "vulkan-1.lib",
        --"IMGUI",
        
        --"yaml-cpp.lib"
    }