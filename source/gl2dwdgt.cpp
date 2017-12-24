#include "gl2dwdgt.hpp"
#include "ui_gl2dwdgt.h"

GL2DWdgt::GL2DWdgt( QWidget *parent ) :
QGLWidget( parent ),
ui( new Ui::GL2DWdgt ) {

	ui->setupUi( this );

	QGLFormat
	glFormat;
	glFormat.setVersion( 3, 3 );
	glFormat.setProfile( QGLFormat::CoreProfile ); // Requires >=Qt-4.8.0
	glFormat.setSampleBuffers( true );
//	glFormat.setDoubleBuffer( true );

	this->setFormat( glFormat );

	started = false;

	simulation = new Simulation( 1e-6 * Clock::time( ).tv_usec );

	connect( &timer, SIGNAL( timeout( ) ), this, SLOT( slotPaint( ) ) );

	timer.setInterval( 1000. / 60. );

	timer.start( );

}

GL2DWdgt::~GL2DWdgt( ) {

	delete simulation;

	delete ui;
}

void
GL2DWdgt::initializeGL( ) {

	simulation->prepare( );
}

void
GL2DWdgt::resizeGL( int p_width, int p_height ) {

	simulation->resizeView( p_width, p_height );
}

void
GL2DWdgt::paintGL( ) {

	simulation->renderView( );
}

void
GL2DWdgt::slotPaint( ) {

	if( !started ) {

		timer.setInterval( 1000. / 60. );

		clock.start( );

		started = true;
	}

	for( int i = 0; i < 5; ++ i )

		simulation->compute( );

	updateGL( );
}
