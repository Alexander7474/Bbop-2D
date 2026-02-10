/*
 * geometricClass.h
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

#ifndef GEOMETRIC_CLASS_H
#define GEOMETRIC_CLASS_H

#include "bbopMathClass.h"
#include <iostream>

/**
* @class Geometric
* @brief gère un objet avec de propriété géométrique
*
* @note Class utile pour décrire toute forme géometrique
* @todo ajouter a shape
*/
class Geometric
{
      public:
	Geometric(Vector2f nPos, Vector2f nOrigin, Vector2f nSize,
		float nRotation);
	Geometric(const Geometric &other);
	Geometric();

	void setPosition(const Vector2f &nPos);
	virtual void setPosition(float x_, float y_);
	const Vector2f &getPosition() const;
	void setSize(const Vector2f &nSize);
	virtual void setSize(float x_, float y_);
	const Vector2f &getSize() const;
	void setOrigin(const Vector2f &nOrigin);
	virtual void setOrigin(float x_, float y_);
	const Vector2f &getOrigin() const;
	virtual void setRotation(float nRotation);
	const float getRotation() const;

      protected:
	Vector2f pos;
	Vector2f origin;
	Vector2f size;
	float rotation;
};

#endif // !GEOMETRIC_CLASS_H
