/*
 * geometricClass.cpp
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

#include "../../../include/BBOP/Graphics/geometricClass.h"

Geometric::Geometric(
	Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation)
    : pos(nPos.x, nPos.y), origin(nOrigin.x, nOrigin.y), size(nSize.x, nSize.y),
      rotation(nRotation)
{
}

Geometric::Geometric()
    : pos(0.f, 0.f), origin(0.f, 0.f), size(0.f, 0.f), rotation(0.f)
{
}

Geometric::Geometric(const Geometric &other)
    : pos(other.pos), origin(other.origin), size(other.size),
      rotation(other.rotation)
{
}

void Geometric::setPosition(const Vector2f &nPos)
{
	setPosition(nPos.x, nPos.y);
}

void Geometric::setPosition(float x_, float y_)
{
	pos.x = x_;
	pos.y = y_;
}

const Vector2f &Geometric::getPosition() const { return pos; }

void Geometric::setSize(const Vector2f &nSize) { setSize(nSize.x, nSize.y); }

void Geometric::setSize(float x_, float y_)
{
	size.x = x_;
	size.y = y_;
}

const Vector2f &Geometric::getSize() const { return size; }

void Geometric::setOrigin(const Vector2f &nOrigin)
{
	setOrigin(nOrigin.x, nOrigin.y);
}

void Geometric::setOrigin(float x_, float y_)
{
	origin.x = x_;
	origin.y = y_;
}

const Vector2f &Geometric::getOrigin() const { return origin; }

void Geometric::setRotation(float nRotation) { rotation = nRotation; }

const float Geometric::getRotation() const { return rotation; }
