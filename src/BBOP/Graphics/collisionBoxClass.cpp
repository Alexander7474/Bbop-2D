/*
 * collisionBoxClass.cpp
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

#include "../../../include/BBOP/Graphics/collisionBoxClass.h"
#include <cmath>

CollisionBox::CollisionBox(
	Vector2f nPos, Vector2f nOrigin, Vector2f nSize, float nRotation)
    : Geometric(nPos, nOrigin, nSize, nRotation)
{
}

CollisionBox::CollisionBox() : Geometric() {}

CollisionBox::CollisionBox(const Geometric &to_follow) : Geometric(to_follow) {}

bool CollisionBox::check(const CollisionBox &otherBox) const
{
	//cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << otherBoxX << ";" << otherBoxY << endl;
	float left = pos.x - origin.x;
	float right = left + size.x;
	left += offsetX.x;
	right -= offsetX.y;
	float top = pos.y - origin.y;
	float bottom = top + size.y;
	top += offsetY.x;
	bottom -= offsetY.y;

	float otherLeft = otherBox.getPosition().x - otherBox.getOrigin().x;
	float otherRight = otherLeft + otherBox.getSize().x;
	otherLeft += otherBox.getOffsetX().x;
	otherRight -= otherBox.getOffsetX().y;
	float otherTop = otherBox.getPosition().y - otherBox.getOrigin().y;
	float otherBottom = otherTop + otherBox.getSize().y;
	otherTop += otherBox.getOffsetY().x;
	otherBottom -= otherBox.getOffsetY().y;

	if (left > otherRight || right < otherLeft || top > otherBottom ||
		bottom < otherTop) {
		return false;
	}
	return true;
}

bool CollisionBox::checkWithRotation(const CollisionBox &otherBox) const
{
	//cout << x << ";" << posY << " " << size.x << ";" << size.y <<  endl << otherBoxX << ";" << otherBoxY << endl;
	Vector2f boxMiddle(pos.x - origin.x + (size.x / 2.0f),
		pos.y - origin.y + (size.y / 2.0f));
	Vector2f otherBoxMiddle(
		otherBox.pos.x - otherBox.origin.x + (otherBox.size.x / 2.0f),
		otherBox.pos.y - otherBox.origin.y + (otherBox.size.y / 2.0f));

	float c = cos(rotation);
	float s = sin(rotation);
	float otherCos = cos(otherBox.rotation);
	float otherSin = sin(otherBox.rotation);

	Vector2f translated(boxMiddle.x - pos.x, boxMiddle.y - pos.y);
	Vector2f otherTranslated(otherBoxMiddle.x - otherBox.getPosition().x,
		otherBoxMiddle.y - otherBox.getPosition().y);

	Vector2f final(translated.x * c - translated.y * s,
		translated.x * s + translated.y * c);
	Vector2f otherFinal(
		otherTranslated.x * otherCos - otherTranslated.y * otherSin,
		otherTranslated.x * otherSin + otherTranslated.y * otherCos);

	final.x += pos.x;
	final.y += pos.y;
	otherFinal.x += otherBox.getPosition().x;
	otherFinal.y += otherBox.getPosition().y;

	float left = final.x - (size.x / 2.0f);
	float right = left + size.x;
	float top = pos.y - (size.y / 2.0f);
	float bottom = top + size.y;

	float otherLeft = otherFinal.x - (otherBox.getSize().x / 2.0f);
	float otherRight = otherLeft + otherBox.getSize().x;
	float otherTop = otherFinal.y - (otherBox.getSize().y / 2.0f);
	float otherBottom = otherTop + otherBox.getSize().y;

	if (left > otherRight || right < otherLeft || top > otherBottom ||
		bottom < otherTop) {
		return false;
	}
	return true;
}

Vector2f CollisionBox::getOffsetX() const { return offsetX; }

Vector2f CollisionBox::getOffsetY() const { return offsetY; }

void CollisionBox::setOffsetX(const Vector2f &off_) { offsetX = off_; }

void CollisionBox::setOffsetX(float x_, float y_)
{
	offsetX.x = x_;
	offsetX.y = y_;
}

void CollisionBox::setOffsetY(const Vector2f &off_) { offsetY = off_; }

void CollisionBox::setOffsetY(float x_, float y_)
{
	offsetY.x = x_;
	offsetY.y = y_;
}

void CollisionBox::follow(const Geometric &to_follow)
{
	pos = to_follow.getPosition();
	size = to_follow.getSize();
	origin = to_follow.getOrigin();
	rotation = to_follow.getRotation();
}

float CollisionBox::getTop()
{
	float top = pos.y - origin.y + offsetY.x;
	return top;
}

float CollisionBox::getBottom()
{
	float bottom = pos.y - origin.y + size.y - offsetY.y;
	return bottom;
}

float CollisionBox::getLeft()
{
	float left = pos.x - origin.x + offsetX.x;
	return left;
}

float CollisionBox::getRight()
{
	float right = pos.x - origin.x + size.x - offsetX.y;
	return right;
}

void CollisionBox::flipVertically()
{
	float save = offsetX.x;
	offsetX.x = offsetX.y;
	offsetX.y = save;
}

void CollisionBox::flipHorizontally()
{
	float save = offsetY.x;
	offsetY.x = offsetY.y;
	offsetY.y = save;
}
