#version 330 core
out vec4 fragColor;
uniform vec4 uColor;

in vec2 texCoord;
uniform sampler2D outTexture;
void main()
{
    fragColor = texture(outTexture,texCoord);

}