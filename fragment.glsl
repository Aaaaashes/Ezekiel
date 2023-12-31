#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform mat4 transform;

void main()
{
    FragColor = texture(texture1, TexCoord);
}