#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;

out vec3 vPosition;
uniform mat4 uViewProjection;
uniform mat4 uTransform;

void main()  {
	vPosition = aPosition;
	gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type frag
#version 330 core

layout(location = 0) out vec4 oColor;

uniform float uRed;
uniform vec4 uColor;

void main()  {
	oColor = uColor * (uRed + 0.5);
}