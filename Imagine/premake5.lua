workspace "Imagine"
    configurations {"Debug", "Release" }
    architecture "x64"

    include "Engine"
    include "vendor/IMGUI"
    include "vendor/GLFW"
    include "vendor/YAML"
    --include "InternalCore/OpenGL/OpenGLAPI"
    --include "InternalCore/Vulkan/VulkanAPI"




