#ifndef GL2DWDGT_HPP
#define GL2DWDGT_HPP

#include <QGLWidget>
#include <QTimer>
#include <iostream>
#include "clock.hpp"
#include "simulation.hpp"

namespace Ui {

	class GL2DWdgt;
}

class GL2DWdgt :
public QGLWidget {

		Q_OBJECT

	public:

		explicit
		GL2DWdgt( QWidget *parent = 0 );

		~GL2DWdgt( );

	private:

		Ui::GL2DWdgt
		*ui;

	public:

		Clock
		clock;

		QTimer
		timer;

		bool
		started;

		Simulation
		*simulation;

	public:

		void
		initializeGL( );

		void
		resizeGL( int p_width, int p_height );

		void
		paintGL( );

	public slots:

		void
		slotPaint( );
};

#endif // GL2DWDGT_HPP
