#version 300 es
precision mediump float;
in vec4 colorOut;
out vec4 color;

void main()
{    
    color = colorOut * (1.0 / 255.0); // convert color to 0-1 range
}
