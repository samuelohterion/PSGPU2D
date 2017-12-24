#-------------------------------------------------
#
# Project created by QtCreator 2017-12-03T19:50:08
#
#-------------------------------------------------

QT += core gui opengl

greaterThan( QT_MAJOR_VERSION, 4 ) : QT += widgets

TARGET = \
	PSGPU2D

TEMPLATE = \
	app

CONFIG += \
	c++11

SOURCEDIR = source

SOURCES += \
	$$SOURCEDIR/main.cpp \
	$$SOURCEDIR/gl2dwdgt.cpp \
	$$SOURCEDIR/shaderprogram.cpp \
	$$SOURCEDIR/simulation.cpp

HEADERS += \
	$$SOURCEDIR/gl2dwdgt.hpp \
	$$SOURCEDIR/shaderprogram.hpp \
	$$SOURCEDIR/clock.hpp \
	$$SOURCEDIR/simulation.hpp

FORMS += \
	$$SOURCEDIR/gl2dwdgt.ui

SHADERDIR = ../PSGPU2D/shaders

DISTFILES += \
	$$SHADERDIR/gravity/view.vert \
	$$SHADERDIR/gravity/view.geom \
	$$SHADERDIR/gravity/view.frag \
	$$SHADERDIR/gravity/simu.frag \
	$$SHADERDIR/gravity/simu.geom \
	$$SHADERDIR/gravity/simu.vert \
	$$SHADERDIR/fallingMasses/view.vert \
	$$SHADERDIR/fallingMasses/view.geom \
	$$SHADERDIR/fallingMasses/view.frag \
	$$SHADERDIR/fallingMasses/simu.frag \
	$$SHADERDIR/fallingMasses/simu.geom \
	$$SHADERDIR/fallingMasses/simu.vert \
	$$SHADERDIR/fabrique/view.vert \
	$$SHADERDIR/fabrique/view.geom \
	$$SHADERDIR/fabrique/view.frag \
	$$SHADERDIR/fabrique/simu.frag \
	$$SHADERDIR/fabrique/simu.geom \
	$$SHADERDIR/fabrique/simu.vert
