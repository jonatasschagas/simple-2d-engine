#version 330 core
out vec4 FragColor;

uniform vec2 shapeSize;
uniform vec2 shapePosition;
uniform vec2 screenSize;
uniform vec4 color;

void main()
{
    vec2 redefinedCoord =  vec2(gl_FragCoord.x, (screenSize - gl_FragCoord.y)); // bottom-left origin to top-left origin
    vec2 normalizedCoord = (redefinedCoord - shapePosition) / shapeSize;
    vec4 normalizedColor = color.xyzw / 255.0;

    vec2 center = vec2(0.5, 0.5); // center of the circle in NDC

    float radius = 0.3; // radius of the circle in NDC

    // Calculate the distance from the fragment to the center of the circle
    float dist = distance(normalizedCoord, center);

    // Check if the fragment is inside the circle
    if (dist < radius)
    {
        FragColor = normalizedColor;
    }
    else
    {
        discard; // discard the fragment if it's outside the circle
    }
}
