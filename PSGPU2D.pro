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

#SHADERDIR = ../PSGPU2D/shaders/gravity
SHADERDIR = ../PSGPU2D/shaders/fallingMasses
#SHADERDIR = ../PSGPU2D/shaders/fabrique

DISTFILES += \
	$$SHADERDIR/view.vert \
	$$SHADERDIR/view.geom \
	$$SHADERDIR/view.frag \
	$$SHADERDIR/simu.frag \
	$$SHADERDIR/simu.geom \
	$$SHADERDIR/simu.vert
