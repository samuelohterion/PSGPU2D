#include "simulation.hpp"

Simulation::Simulation( GLfloat const &p_seed ) :
state( 0 ),
simuWdth( 1 << 6 ),
simuHght( 1 << 5 ),
// x0 x1 v0 v1 |             |
// v0 v1 a0 a1 | v0 v1 a0 a1 |
//
simuSize( simuWdth * simuHght ),
viewWdth( 1 ),
viewHght( 1 ),
simuTexData( 4. * simuSize, 0. ),
viewMem( 4. * simuSize ),
started( false ) {

}

Simulation::~Simulation( ) {

	glDeleteBuffers( 1, &simuVBO );

	glDeleteVertexArrays( 1, &simuVAO );

	glDeleteTextures( 2, texPos );

	glDeleteFramebuffers( 1, &simuFBO );

	delete viewShader;
	delete simuShader;
}

bool
Simulation::checkFBOState( ) {

	GLenum
	fboStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );

	if( fboStatus != GL_FRAMEBUFFER_COMPLETE ) {

		switch( fboStatus ) {

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT : {

				std::cout << "framebuffer incomplete attachment" << std::endl;

				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS : {

				std::cout << "framebuffer incomplete dimensions" << std::endl;

				break;
			}
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : {

				std::cout << "framebuffer incomplete missing attachment" << std::endl;

				break;
			}
			case GL_FRAMEBUFFER_UNSUPPORTED : {

				std::cout << "framebuffer unsupported" << std::endl;

				break;
			}
			default : {

				std::cout << "framebuffer incomplete" << std::endl;

				break;
			}
		}

		return false;
	}

	return true;
}

void
Simulation::compute( ) {

	if( !started ) {

		clockTot.start( );
		clockRel.start( );
		frame = 0;
		started = true;
	}

	GLenum const
	drawBuffers[ 1 ] = {

		GL_COLOR_ATTACHMENT0
	};

	glViewport( 0, 0, simuWdth, simuHght );

	glEnable( GL_TEXTURE_2D );

	glBindFramebuffer( GL_FRAMEBUFFER, simuFBO );

	simuShader->bind( );

	glActiveTexture( GL_TEXTURE0 );

	glBindTexture( GL_TEXTURE_2D, texPos[ state ] );

	dtime = 1.e-6 * clockRel.elapsedMicros( );
	clockRel.start( );


	dtime = 1e-2 / 60. / 5.;
	time = 1.e-6 * clockTot.elapsedMicros( );

//	if( 1000. / 60. < dtime && dtime < 1.e-3 )

//		return;

	simuShader->setUniformInt( "texPV", 0 );
	simuShader->setUniformInt( "width", simuWdth );
	simuShader->setUniformInt( "height", simuHght );
	simuShader->setUniformInt( "frame", frame++ );
	simuShader->setUniformFloat( "time", time );
	simuShader->setUniformFloat( "dtime", dtime );
	simuShader->setUniformFloat( "seed", seed );
//	std::cout << dtime << ", ";

	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texPos[ 1 - state ], 0 );

	if( !checkFBOState( ) )

		return;

	glBindVertexArray( simuVAO );

	glDrawBuffers( 1, drawBuffers );

	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

//	glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, h_hdot.data( ) );

	glBindVertexArray( 0 );

	glBindTexture( GL_TEXTURE_2D, 0 );

	simuShader->release( );

	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	glDisable( GL_TEXTURE_2D );

	state = 1 - state;
}

void
Simulation::createFrameBufferObjects( ) {

	// we only need one framebuffer for the simulation
	glGenFramebuffers( 1, &simuFBO );

//	glFramebufferTexture2D( GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texPos[ 0 ], 0 );

//	bool
//	cfbo = checkFBOState( );
}

void
Simulation::createVertexBufferObjects( ) {

	// we need a vertex array object for the simulation
	glGenVertexArrays( 1, &simuVAO );

	// bind this vertex array object to ogl
	glBindVertexArray( simuVAO );

	// now we need a vertex buffer object for the simulation
	glGenBuffers( 1, &simuVBO );

	// bind this to the vertex array buffer simuVBO
	glBindBuffer( GL_ARRAY_BUFFER, simuVBO );

	// create and initialize a buffer object's data storage
	glBufferData( GL_ARRAY_BUFFER, sizeof( simMem ), simMem, GL_STATIC_DRAW );

	// bind the simulation shader
	simuShader->bind( );

	// specify location and data format of vertex positions
	simuShader->setVertexAttrib( "inVPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 0 * sizeof( GLfloat ) ) );
	simuShader->setVertexAttrib( "inTPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );

	// release simulation shader
	simuShader->release( );


	for( unsigned int y = 0; y < simuHght; ++y ) {

		for( unsigned int x = 0; x < simuWdth; ++x ) {

			viewMem[ 4. * ( y * simuWdth + x ) + 0 ] = 2. * x / ( simuWdth - 1. ) - 1.;
			viewMem[ 4. * ( y * simuWdth + x ) + 1 ] = 2. * y / ( simuHght - 1. ) - 1.;
			viewMem[ 4. * ( y * simuWdth + x ) + 2 ] = 1. * x / ( simuWdth - 1. );
			viewMem[ 4. * ( y * simuWdth + x ) + 3 ] = 1. * y / ( simuHght - 1. );
		}
	}

	// we need a vertex array object for the view
	glGenVertexArrays( 1, &viewVAO );

	// bind this vertex array object to ogl
	glBindVertexArray( viewVAO );

	// now we need a vertex buffer object for the view
	glGenBuffers( 1, &viewVBO );

	// bind this to the vertex array buffer viewVBO
	glBindBuffer( GL_ARRAY_BUFFER, viewVBO );

	// create and initialize a buffer object's data storage
	glBufferData( GL_ARRAY_BUFFER, sizeof( GL_FLOAT ) * viewMem.size( ), viewMem.data( ), GL_STATIC_DRAW );

	// bind the simulation shader
	viewShader->bind( );

	// specify location and data format of vertex positions
	viewShader->setVertexAttrib( "inVPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 0 * sizeof( GLfloat ) ) );
	viewShader->setVertexAttrib( "inTPos", 2, GL_FLOAT, GL_FALSE, 4 * sizeof( GLfloat ), ( void* ) ( 2 * sizeof( GLfloat ) ) );

	// release simulation shader
	viewShader->release( );
}

void
Simulation::createShaders( CStr &shaderDir ) {

	simuShader = new ShaderProgram( shaderDir + "simu.vert", shaderDir + "simu.geom", shaderDir + "simu.frag", Shader::FROM_FILE );
	viewShader = new ShaderProgram( shaderDir + "view.vert", shaderDir + "view.geom", shaderDir + "view.frag", Shader::FROM_FILE );
}

void
Simulation::createTextures( ) {

	// Erstelle 2. Texturen fuer Simulation
	glGenTextures( 2, texPos );

	// Konfiguriere Simulation Textur
	glBindTexture( GL_TEXTURE_2D, texPos[ 0 ] );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simuWdth, simuHght );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simuWdth, simuHght, 0, GL_RGBA, GL_FLOAT, simuTexData.data( ) );

	// Konfiguriere Simulation Textur
	glBindTexture( GL_TEXTURE_2D, texPos[ 1 ] );
	glTexStorage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simuWdth, simuHght );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, simuWdth, simuHght, 0, GL_RGBA, GL_FLOAT, simuTexData.data( ) );
}

void
Simulation::prepare( ) {

//	glFrustum( 0., 1., 0., 1., 0., 0. );

//	createShaders( "../../shaders/gravity/" );
	createShaders( "../../shaders/fabrique/" );
//	createShaders( "../../shaders/fallingMasses/" );

	createTextures( );

	createVertexBufferObjects( );

	createFrameBufferObjects( );

//	glClearColor( .265, .265, .265, 1. );
	glClearColor( 0,0,0, 1 );
//	glClearColor( 1,1,1,1 );
}

void
Simulation::renderView( ) {

	glClear( GL_COLOR_BUFFER_BIT );

	glViewport( 0, 0, viewWdth, viewHght );

	glEnable( GL_TEXTURE_2D );

	viewShader->bind( );

	glActiveTexture( GL_TEXTURE0 );

	glBindTexture( GL_TEXTURE_2D, texPos[ state ] );

	viewShader->setUniformInt( "width", viewWdth );
	viewShader->setUniformInt( "height", viewHght );
	viewShader->setUniformInt( "texPV", 0 );

	glBindVertexArray( viewVAO );

	glDrawArrays( GL_POINTS, 0, simuSize );

	glBindVertexArray( 0 );

	viewShader->release( );

	glBindTexture( GL_TEXTURE_2D, 0 );

	glDisable( GL_TEXTURE_2D );
}

void
Simulation::resizeView( GLuint const &p_width, GLuint const &p_height ) {

	viewWdth = p_width;
	viewHght = p_height;
}
