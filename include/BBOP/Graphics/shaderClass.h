/*
 * shaderClass.h
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "bbopGlobal.h"

class Shader
{
      public:
	// ID de reference shader program
	GLuint ID;
	// BUILDER creation du shader program
	Shader(const char *vertexFile, const char *fragmentFile);

	GLint getUniformLoc(const GLchar *varName) const;
	GLuint getID() const;
	void Activate() const;
	void Delete();
};
#endif
