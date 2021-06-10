#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aColor;

out vec3 vertexColor;
out vec3 vertexPosition;

uniform float xOffset;

void main()
{
  vec3 position=vec3(aPos.x+xOffset,aPos.y,aPos.z);
  gl_Position=vec4(position,1.);
  vertexColor=aColor * position;
  vertexPosition=position;
}