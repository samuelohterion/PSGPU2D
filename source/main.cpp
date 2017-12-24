#include "gl2dwdgt.hpp"
#include <QApplication>

int
main( int argc, char *argv[ ] ) {

	QApplication
	a( argc, argv );

	GL2DWdgt
	w;

	w.show( );

	return a.exec( );
}
