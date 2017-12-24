#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

//#include <GLES3/gl3.h>
//#include <GLES3/gl3ext.h>
#include <GLES3/gl32.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <QVector2D>

typedef std::__cxx11::string Str;
typedef Str const CStr;

class Shader {

	public:

		enum CreationMethod {

			FROM_CODE,
			FROM_FILE
		};

	public:

		Shader( GLenum p_shaderType, CStr &p_text, CreationMethod const &p_method = FROM_CODE );

		~Shader( );

	private:

		GLenum
		__type;			// GL_VERTEX_SHADER or GL_FRAGMENT_SHADER

		GLint
		__success;

		std::string
		__fname,
		__code;

		GLuint
		__id;

		GLchar
		*__infoLog;

	private:

		bool
		createFromCode( CStr &p_code );

		bool
		createFromFile( CStr &p_fileName );

	public:

		Str
		code( ) const;

		GLuint
		id( ) const;

		Str
		fileName( ) const;

		bool
		ok( ) const;

		GLenum
		type( ) const;
};

class ShaderProgram {

	public:

		ShaderProgram( CStr &p_vertexText, CStr &p_geometryText, CStr &p_fragmentText, Shader::CreationMethod const &p_method );

		ShaderProgram( CStr &p_vertexText, CStr &p_geometryText, CStr &p_fragmentText, Shader::CreationMethod const &p_method, std::vector< GLuint > const &p_locId, std::vector< Str > const &p_names );

		~ShaderProgram( );

	private:

		Shader
		*__vertexShader,
		*__geometryShader,
		*__fragmentShader;

		GLint
		__success;

		GLuint
		__id;

		GLchar
		*__infoLog;

	public:

		GLuint
		id( ) const;

		bool
		ok( ) const;

		void
		bind( );

		void
		release( );

		void
		setUniformBool( GLchar const *p_name, GLboolean const &p_value );

		void
		setUniformInt( GLchar const *p_name, GLint const &p_value );

		void
		setUniformFloat( GLchar const *p_name, GLfloat const &p_value );

		void
		setUniformMat4x4F( GLchar const *p_name, GLfloat *p_mat4x4 );

		GLint
		setVertexAttrib( std::string const &p_name, GLint p_size, GLenum p_type, GLboolean p_normalized, GLsizei p_stride, void const *p_offset );
};

#endif // SHADERPROGRAM_HPP
