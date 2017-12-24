#version 150 core

precision highp float;
precision highp int;

//in  vec2 tPos;
//in  vec2 tCol;

in vec4
gPosVel;

in vec2
gTexPos;

out vec4
fCol;

float
rand( vec2 last ) {

	return fract( sin( dot( last, vec2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

void
main( void ) {

//	float
//	s = 4. * dot( tPos, tPos );

/*	vec3
	col =
		tCol < .5
			? tCol < .25
				? vec3( 1, 0, 0 )
				: vec3( 0, 1., 0 )
			: tCol < .75
				? vec3( 0, 0, 1 )
				: vec3( .7, .7, 0 );
*/
//	oCol = vec4( 4. * dot( tPos, tPos ), 1. - 4. * dot( tPos, tPos ), 0., 1. );
	fCol = vec4( gTexPos, rand( gTexPos.xx ), 1 );
}
