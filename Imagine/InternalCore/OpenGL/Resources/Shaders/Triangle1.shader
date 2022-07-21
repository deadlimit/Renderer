#TYPE VERTEX

#version 460 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;

out vec4 vColor;

void main() {

    gl_Position = vec4(inPos, 1.0);
    vColor = vec4(inColor, 1.0);
}

#TYPE FRAGMENT

#version 460 core

in vec4 vColor;

out vec4 outColor;

void main() {

    outColor = vColor;

}
