#TYPE VERTEX

#version 460 core

layout(location = 0) in vec3 inPos;

out vec4 outVertexColor;

void main() {

    gl_Position = vec4(inPos, 1.0);
    outVertexColor = vec4(0.5, 0.5, 0.5, 1.0);
}

#TYPE FRAGMENT

#version 460 core

in vec4 outVertexColor;
out vec4 outColor;

void main() {

    outColor = outVertexColor;

}
