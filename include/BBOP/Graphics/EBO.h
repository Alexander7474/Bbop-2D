/*
 * EBO.h
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

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class EBO
{
      public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint *indices, GLsizeiptr size);
	EBO();

	void init(GLuint *indices, GLsizeiptr size);

	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
	// update the EBO
	void update(GLuint *indices, GLsizeiptr size);
};

#endif
