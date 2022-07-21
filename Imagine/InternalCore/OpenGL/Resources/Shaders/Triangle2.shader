#TYPE VERTEX
#version 460 core

layout(location = 0) in vec3 inPos;

void main() {

    gl_Position = vec4(inPos, 1.0);

}

#TYPE FRAGMENT
#version 460 core

out vec4 outColor;

void main() {

    outColor = vec4(0.0f, 0.2f, 0.2f, 1.0f);

}
