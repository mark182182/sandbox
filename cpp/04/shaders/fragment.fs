#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
  FragColor=mix(texture(texture1,TexCoord)*vec4(vertexColor,1.f),texture(texture2,vec2(TexCoord.x*2,TexCoord.y*2)),.4);
}