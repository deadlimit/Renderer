#TYPE VERTEX

#version 330 core

layout(location = 0) in vec3 inPos;

void main() {

    gl_Position = vec4(inPos, 1.0);

}

#TYPE FRAGMENT

#version 330 core

out vec4 outColor;

void main() {

    outColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

}
