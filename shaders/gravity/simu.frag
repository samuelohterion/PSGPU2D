#version 150 core

precision highp float;
precision highp int;

in vec2
gTexPos;

out vec4
fPV;

uniform highp sampler2D texPV;

uniform int width;
uniform int height;
uniform int frame;

uniform float seed;
uniform float time;
uniform float dtime;

vec2
wh = vec2( width, height ),
rwh = 1. / wh;

const vec2
cacc = vec2( 0., 0. );

const float
rad  = .01,
rad2 = rad * rad;

float
rand( vec2 last ) {

	return fract( sin( dot( last, vec2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

vec4
init( float interval ) {

	float
	angle = 6.283 * rand( seed + gTexPos ),
	radius = rand( -seed + gTexPos.yx );
	radius = sqrt( radius );

	return vec4( radius * cos( angle ), radius * sin( angle ), -64 * radius * sin( angle ), 36. * radius * cos( angle ) );

	//return vec4( gTexPos, 0., 0. );
}

vec4
run( ) {

	vec4
	p = texture2D( texPV, gTexPos );

	vec2
	acc = vec2( 0 ),
	r = p.xy,
	v = p.zw,
	i = wh * gTexPos;

	for( int y = 0; y < height; ++ y ) {

		for( int x = 0; x < width; ++ x ) {

			vec2
			d = vec2( x, y ) - i;

			if( .6 < dot( d, d ) ) {

				vec2
				texPos = rwh * vec2( ( x + .5 ), ( y + .5 ) );

				vec4
				rv = texture2D( texPV, texPos );

				vec2
				d = rv.xy - r;

				float
				dd = dot( d, d );

				if( 1e-5 < dd ) {

					dd = pow( dd, -3. / 2. );
					acc += .1 * dd * d;
				}
			}
		}
	}

	r += dtime * v;
//	v += dtime * acc - .0001 * sqrt( dot( v, v ) ) * v;
	v += dtime * acc - .0003 * v;

//	while( r.x < -1 ) r.x += 2;
//	while( 1. < r.x ) r.x -= 2;
//	while( r.y < -1 ) r.y += 2;
//	while( 1. < r.y ) r.y -= 2;

	return vec4( r, v );
}

void
main( void ) {

	fPV = time < 5 ? init( 5. ) : run( );
}
