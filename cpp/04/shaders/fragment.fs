#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D woodTexture;

void main(){
  FragColor=texture(woodTexture,TexCoord)*vec4(vertexColor,1.f);
}