/*
 * cameraClass.cpp
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

#include "../../../include/BBOP/Graphics/cameraClass.h"

Camera::Camera()
    : camX(0.0f, 0.0f), camY(0.0f, 0.0f),
      pos(BBOP_WINDOW_RESOLUTION.x / 2.0f, BBOP_WINDOW_RESOLUTION.y / 2.0f),
      scale(1.0f)
{
	buildCamera();
}

Camera::Camera(Vector2f nPos, float nScale)
    : camX(0.0f, 0.0f), camY(0.0f, 0.0f), pos(nPos), scale(nScale)
{
	buildCamera();
}

void Camera::buildCamera()
{
	camX.x = pos.x - scale * (BBOP_WINDOW_RESOLUTION.x / 2.0f);
	camX.y = pos.x + scale * (BBOP_WINDOW_RESOLUTION.x / 2.0f);
	camY.x = pos.y - scale * (BBOP_WINDOW_RESOLUTION.y / 2.0f);
	camY.y = pos.y + scale * (BBOP_WINDOW_RESOLUTION.y / 2.0f);
}

void Camera::setPosition(Vector2f nPos)
{
	pos = nPos;
	buildCamera();
}

Vector2f Camera::getPosition() { return pos; }

void Camera::move(Vector2f m)
{
	pos.x += m.x;
	pos.y += m.y;
}

void Camera::setScale(float nScale)
{
	scale = nScale;
	buildCamera();
}

float Camera::getScale() { return scale; }

Vector2f Camera::screenPosToCamPos(Vector2f screenPos)
{

	float xRapport =
		(BBOP_WINDOW_RESOLUTION.x * scale) / BBOP_WINDOW_SIZE.x;
	float yRapport =
		(BBOP_WINDOW_RESOLUTION.y * scale) / BBOP_WINDOW_SIZE.y;

	Vector2f finalPos(xRapport * screenPos.x, yRapport * screenPos.y);

	return finalPos;
}

Vector2f Camera::camPosToWorldPos(Vector2f camPos)
{
	float xStart = pos.x - (BBOP_WINDOW_RESOLUTION.x * scale) / 2.f;
	float yStart = pos.y - (BBOP_WINDOW_RESOLUTION.y * scale) / 2.f;

	Vector2f finalPos(xStart + camPos.x, yStart + camPos.y);

	return finalPos;
}

//ne marche que avec les formes rectangulaires
bool Camera::isInCamView(Shape &obj)
{
	float left = obj.getPosition().x - obj.getOrigin().x;
	float right = left + obj.getSize().x;
	float top = obj.getPosition().y - obj.getOrigin().y;
	float bottom = top + obj.getSize().y;
	if (right < camX.x || left > camX.y || top > camY.y ||
		bottom < camY.x) {
		return false;
	}
	return true;
}

bool Camera::isInCamView(CollisionBox &obj)
{
	float left = obj.getLeft();
	float right = obj.getRight();
	float top = obj.getTop();
	float bottom = obj.getBottom();
	if (right < camX.x || left > camX.y || top > camY.y ||
		bottom < camY.x) {
		return false;
	}
	return true;
}
