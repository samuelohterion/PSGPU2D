#version 150 core

layout( triangles ) in;
layout( triangle_strip, max_vertices = 4 ) out;

in  vec2 tPos[ ];
out vec2 txPos;

void
main( ) {

	txPos = tPos[ 0 ];

	gl_Position = gl_in[ 0 ].gl_Position;
	EmitVertex( );

	txPos = tPos[ 1 ];

	gl_Position = gl_in[ 1 ].gl_Position;
	EmitVertex( );

	txPos = tPos[ 2 ];

	gl_Position = gl_in[ 2 ].gl_Position;
	EmitVertex( );

	EndPrimitive( );
}
