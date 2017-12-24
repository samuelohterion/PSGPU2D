#version 150 core

layout( points ) in;
//layout( points, max_vertices = 2 ) out;
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

in vec4
vCol[ ];

out vec4
gPosVel;

out vec2
gTexPos;

out vec4
gCol;


const float
cos_[ ] = float[ ](	1, .8660254, .5, 0., -.5, -.8660254, -1., -.8660254, -.5, 0., .5, .8660254, 1. ),
sin_[ ] = float[ ]( 0., .5, .8660254, 1., .8660254, .5, 0, -.5, -.8660254, -1., -.8660254, -.5, 0. );

void
main( ) {

	vec2
	v = gl_in[ 0 ].gl_Position.xy * ratio;

	for( int i = 0; i <= 12; ++ i ) {

		gPosVel = vPosVel[ 0 ];
		gTexPos = vTexPos[ 0 ];
		gCol    = vCol[ 0 ];
		gl_Position = gl_in[ 0 ].gl_Position + vec4( rad * vec2( cos_[ i ], sin_[ i ] ) * ratio, 0., 0. );
		EmitVertex( );
	}

//	gl_Position = vec4( .5, .5, 0., 0. );
//	EmitVertex( );
//	EndPrimitive( );
}
