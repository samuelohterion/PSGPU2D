#version 150 core

precision highp float;
precision highp int;

in vec2 inVPos;
in vec2 inTPos;

uniform highp sampler2D texPV;
uniform int width;
uniform int height;

out vec4 vPosVel;
out vec2 vTexPos;

void
main( ) {

	vec4
	p = texture2D( texPV, inTPos );

	p.xy *= width < height ? vec2( 1., 1. * width / height ) : vec2( 1. * height / width, 1. );

	while( p.x < -1 ) p.x += 2;
	while( +1 < p.x ) p.x -= 2;
	while( p.y < -1 ) p.y += 2;
	while( +1 < p.y ) p.y -= 2;

	vPosVel = p;
	vTexPos = inTPos.xy;

	gl_Position = vec4( p.xy, 0., 1. );
}
