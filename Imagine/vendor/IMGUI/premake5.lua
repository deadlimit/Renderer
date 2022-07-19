project "IMGUI"
    kind "StaticLib"
    language "C++"
    files
    {
        "imconfig.h",
        "imgui.h",
        "imgui.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "imgui_widgets.cpp",
        "imstb_rectpack.h",
        "imstb_textedit.h",
        "imstb_truetype.h",
        "imgui_demo.cpp",
        "backends/imgui_impl_vulkan.h",
        "backends/imgui_impl_vulkan.cpp",
        "backends/imgui_impl_glfw.h",
        "backends/imgui_impl_glfw.cpp"
    }

    includedirs{
        "../GLFW/include",
        "C:/VulkanSDK/1.3.204.1/Include",
        "../../vendor/IMGUI",
        "../../vendor/IMGUI/backends"
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