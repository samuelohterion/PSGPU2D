#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <GLES3/gl32.h>
//#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "shaderprogram.hpp"
#include "clock.hpp"

typedef std::vector< GLfloat > VFlt;

class Simulation {

	public:

		enum DIM {

			X, XY, XYZ
		};

	public:

		GLfloat const
		simMem[ 2 * 2 * 4 ] = {
			-1., -1.,	0., 0.,
			+1., -1.,	1., 0.,
			-1., +1.,	0., 1.,
			+1., +1.,	1., 1.
		}; // pos and tex

		GLuint
		state;

		GLuint
		simuWdth,
		simuHght,
		simuSize,
		viewWdth,
		viewHght,
		simuVAO,
		simuVBO,
		simuFBO,
		viewVAO,
		viewVBO,
		texPos[ 2 ];

		VFlt
		simuTexData, // positions
		viewMem; // computed positions

		bool
		started;

		ShaderProgram
		*simuShader,
		*geomShader,
		*viewShader;

		Clock
		clockTot,
		clockRel;

		GLint
		frame;

		GLfloat
		time,
		dtime,
		seed;

	public:

		Simulation( GLfloat const &p_seed = .1 );

		~Simulation( );

	public:

		bool
		checkFBOState( );

		void
		compute( );

		void
		createFrameBufferObjects( );

		void
		createShaders( CStr &shaderDir = "../../shaders/fallingMasses/" );

		void
		createTextures( );

		void
		createVertexBufferObjects();

		void
		prepare( );

		void
		renderView( );

		void
		resizeView( GLuint const &p_width, GLuint const &p_height );
};

#endif // SIMULATION_HPP
