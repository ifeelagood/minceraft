#version 330

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, texCoord);
}
