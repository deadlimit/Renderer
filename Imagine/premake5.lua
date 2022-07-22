workspace "Imagine"
    configurations {"Debug", "Release" }
    architecture "x64"

    include "Renderer"
    include "vendor/IMGUI"
    include "vendor/GLFW"
    include "InternalCore/Vulkan/VulkanAPI"
    include "InternalCore/OpenGL/OpenGLAPI"




