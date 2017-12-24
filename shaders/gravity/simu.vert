#version 150 core

precision highp float;
precision highp int;

//layout( location = 0 ) in vec2 inVPos;
//layout( location = 1 ) in vec2 inTPos;

in vec2
inVPos;

in vec2
inTPos;

out vec2
vTexPos;

void
main( ) {

	vTexPos = inTPos;

	gl_Position = vec4( inVPos, 0., 1. );
}
