/*
 * VBO.h
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

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBO
{
      public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat *vertices, GLsizeiptr size, GLenum typeVBO);
	VBO();

	void init(GLfloat *vertices, GLsizeiptr size, GLenum typeVBO);

	// Binds the VBO
	void Bind() const;
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
	// change data of VBO
	void update(GLfloat *vertices, GLsizeiptr size);
};

#endif
