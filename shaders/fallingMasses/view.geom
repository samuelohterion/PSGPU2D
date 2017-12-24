#version 150 core

layout( points ) in;
//layout( points, max_vertices = 13 ) out;
layout( line_strip, max_vertices = 13 ) out;

uniform int width;
uniform int height;

vec2 ratio = width < height ? vec2( 1., 1. * width / height ) : vec2( 1. * height / width, 1. );
const float rad = .01;

in vec4
vPosVel[ ];

in vec2
vTexPos[ ];

out vec4
gPosVel;

out vec2
gTexPos;


const float
cos_[ ] = float[ ](	1, .8660254, .5, 0., -.5, -.8660254, -1., -.8660254, -.5, 0., .5, .8660254, 1. ),
sin_[ ] = float[ ]( 0., .5, .8660254, 1., .8660254, .5, 0, -.5, -.8660254, -1., -.8660254, -.5, 0. );

void
main( ) {

	vec2
	v = gl_in[ 0 ].gl_Position.xy * ratio;

	int
	steps =
		v.y < 0
			? v.y < -.5
				? 4
				: 3
			: v.y < +.5
				? 2
				: 1;

	int
	start = int( 6. * ( v.x + 1. ) );

	for( int i = 0; i <= 12; i += steps ) {

		int
		j = start + i;

		if( 12 < j ) j -= 12;

		gPosVel = vPosVel[ 0 ];
		gTexPos = vTexPos[ 0 ];
		gl_Position = gl_in[ 0 ].gl_Position + vec4( rad * vec2( cos_[ j ], sin_[ j ] ) * ratio, 0., 0. );
		EmitVertex( );
	}

//	gPosVel = vPosVel[ 0 ];
//	gTexPos = vTexPos[ 0 ];
//	gl_Position = gl_in[ 0 ].gl_Position ;
//	EmitVertex( );
	EndPrimitive( );
}
