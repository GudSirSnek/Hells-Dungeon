#version 330 core
out vec4 frag_color;

in vec2 uvs;

uniform vec4 color;

void main() {
	frag_color =  color;
}
