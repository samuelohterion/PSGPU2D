#version 150 core

precision highp float;
precision highp int;

//in  vec2 tPos;
//in  vec2 tCol;

in vec4
gPosVel;

in vec2
gTexPos;

in vec4
gCol;

out vec4
fCol;

float
rand( vec2 last ) {

	return fract( sin( dot( last, vec2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

void
main( void ) {

	fCol = vec4( .25 * floor( ( .5 * ( 5. + gCol.xy ) ) ), 0., 1 );
}
