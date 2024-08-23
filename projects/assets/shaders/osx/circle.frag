#version 330 core
out vec4 FragColor;

uniform vec2 shapeSize;
uniform vec2 shapePosition;
uniform vec2 screenSize;
uniform vec4 color;
uniform float time;

void main()
{
    vec2 redefinedCoord = vec2(gl_FragCoord.x, (screenSize.y - gl_FragCoord.y)); // bottom-left origin to top-left origin
    vec2 normalizedCoord = (redefinedCoord - shapePosition) / shapeSize;

    vec2 center = vec2(0.5, 0.5); // center of the star in NDC
    float baseRadius = 0.3; // base radius of the star in NDC

    // Calculate the angle and distance from the center
    vec2 fromCenter = normalizedCoord - center;
    float angle = atan(fromCenter.y, fromCenter.x);
    float dist = length(fromCenter);

    // Define star points (5 points in this case)
    float starAngle = 2.0 * 3.14159265359 / 5.0; // 5-pointed star
    float starRadius = baseRadius * (sin(5.0 * angle) > 0.0 ? 0.5 : 1.0);

    // Apply pulsing effect: interpolate between star shape and full circle
    float pulseFactor = (sin(time * 2.0) + 1.0) / 2.0; // Pulsate between 0 and 1
    float dynamicRadius = mix(starRadius, baseRadius, pulseFactor); // Interpolate between star and circle

    // Check if the fragment is inside the dynamic shape
    if (dist < dynamicRadius)
    {
        vec4 pulsingColor = color.xyzw / 255.0;
        pulsingColor.rgb *= mix(0.8, 1.0, pulseFactor); // Pulsate the color brightness
        FragColor = pulsingColor;
    }
    else
    {
        discard; // discard the fragment if it's outside the dynamic shape
    }
}
