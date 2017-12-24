#version 150 core

layout( triangles ) in;
layout( triangle_strip, max_vertices = 4 ) out;

in  vec2
vTexPos[ ];

out vec2
gTexPos;

void
main( ) {

	for( int i = 0; i < 3; ++ i ) {

		gTexPos = vTexPos[ i ];

		gl_Position = gl_in[ i ].gl_Position;
		EmitVertex( );
	}

	EndPrimitive( );
}
