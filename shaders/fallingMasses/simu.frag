#version 150 core

precision highp float;
precision highp int;

in  vec2 txPos;
out vec4 oPV;

uniform highp sampler2D texPV;

uniform int width;
uniform int height;
uniform int frame;

uniform float seed;
uniform float time;
uniform float dtime;

const vec2
acc = vec2( 0., -1e5 );

float
rand( vec2 last ) {

	return fract( sin( dot( last, vec2( 12.9898, 78.233 ) ) ) * 43758.5453 );
}

vec4
init( float interval ) {

	return
		clamp( ( time - interval / 2 ) / ( interval / 2 ), 0, 1 ) *
			( 2. * vec4(
			rand( seed + txPos.xy ), rand( -seed + txPos.yx ),
			rand( 5.5 * seed + txPos.xy ), rand( -5.5 + seed + txPos.yx ) ) - 1. );
}

vec4
run( ) {

	vec4
	p = texture2D( texPV, txPos );

	vec2
	r = p.xy,
	v = p.zw;

	v += dtime * acc - 0.000 * v;
	r += dtime * v;

	if( r.y <= -1. && v.y < 0. ) {

		r.y = -2. - r.y;
		v.y = -v.y;
	}

	if( r.x < -1. ) {

		r.x = -2. - r.x;
		v.x = -1. * v.x;
	}

	if( +1. <= r.x ) {

		r.x = +2. - r.x;
		v.x = -1. * v.x;
	}

	return vec4( r, v );
}

void
main( void ) {

	oPV = time < 5 ? init( 5. ) : run( );
}
