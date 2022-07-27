workspace "Imagine"
    configurations {"Debug", "Release" }
    architecture "x64"

    include "Renderer"
    include "vendor/IMGUI"
    include "vendor/GLFW"
    --include "InternalCore/OpenGL/OpenGLAPI"
    --include "InternalCore/Vulkan/VulkanAPI"




