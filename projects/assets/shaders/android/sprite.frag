#version 300 es
in vec2 texCoords;
out vec4 color;

uniform sampler2D image;

void main()
{    
    color = texture(image, texCoords);
}
