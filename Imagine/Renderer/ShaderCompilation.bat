@echo off
FOR %%y IN (..\Resources\Shaders\*) DO (C:\VulkanSDK\1.3.204.1\Bin\glslc.exe %%~nfy -c -o ..\Resources\Shaders\Compiled\%%~nxy.spv)