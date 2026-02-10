/*
 * VAO.h
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

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "VBO.h"

class VAO
{
      public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO &VBO, GLuint layout, GLuint vecN, GLuint strideN,
		GLuint jump);
	// Binds the VAO
	void Bind() const;
	// Unbinds the VAO
	void Unbind() const;
	// Deletes the VAO
	void Delete();
};
#endif
