/*
 * VAO.cpp
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

#include "../../../include/BBOP/Graphics/VAO.h"

// Constructor that generates a VAO ID
VAO::VAO() { glGenVertexArrays(1, &ID); }

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(
	VBO &VBO, GLuint layout, GLuint vecN, GLuint strideN, GLuint jump)
{
	VBO.Bind();
	glVertexAttribPointer(layout, vecN, GL_FLOAT, GL_FALSE,
		strideN * sizeof(float), (void *)(jump * sizeof(float)));
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind() const { glBindVertexArray(ID); }

// Unbinds the VAO
void VAO::Unbind() const { glBindVertexArray(0); }

// Deletes the VAO
void VAO::Delete() { glDeleteVertexArrays(1, &ID); }
