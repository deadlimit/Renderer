#TYPE VERTEX

#version 460 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;

out vec2 TexCoord;

void main() {

    gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
    TexCoord = inUV;
}

#TYPE FRAGMENT

#version 460 core

in vec2 TexCoord;

uniform sampler2D u_Texture;

out vec4 outColor;

void main() {

    outColor = texture(u_Texture, TexCoord);

}
