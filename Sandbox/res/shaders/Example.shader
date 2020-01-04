#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

out vec3 vPosition;
out vec4 vColor;
uniform mat4 uViewProjection;
uniform mat4 uTransform;

void main()  {
	vPosition = aPosition;
	vColor = aColor;
	gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type frag
#version 330 core

layout(location = 0) out vec4 oColor;

in vec4 vColor;
uniform float uRed;
uniform vec4 uColor;

void main()  {
	oColor = vColor * uColor * (uRed + 0.5);
}