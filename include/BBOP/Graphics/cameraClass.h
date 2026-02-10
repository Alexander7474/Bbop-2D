/*
 * cameraClass.h
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

#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "bbopGlobal.h"
#include "bbopMathClass.h"
#include "collisionBoxClass.h"
#include "geometricClass.h"
#include "shapeClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @class Camera
* @brief Permet de modifier les point de vue et la position de l'affichage de la class Scene
*
* @note Les attribut de cette class sont utilisé par Scene pour fabriquer la matrice de projection du vertex shader
* @todo Ajouter des méthode d'effet sur la caméra comme le trenblement ou des filtre de couleur
*/
class Camera
{
      public:
	/**
	* @brief Constructeur de la Camera
	* 
	* @param[in] nPos Position du centre de la Camera
	* @param[in] nScale Scale de la camera, a 1.0 la camera à la même proportion que la résolution BBOP_WINDOW_SIZE
	*/
	Camera(Vector2f nPos, float nScale);

	/**
	* @brief Constructeur par défault de la camera.
	* @details La position de la camera est le milieu de BBOP_WINDOW_SIZE et la scale est de 1.0
	*
	* @note Une Camera par défault peut être utile pour convertir des coordonnées de la souris en coordonnées dans le monde avec les méthodes de Camera
	*/
	Camera();

	/**
	* @brief Determine les limites x et y de la cam avec ces attribut
	*/
	void buildCamera();

	/**
	* @brief Change la scale de la camera
	*
	* @param[in] nScale Scale de la camera
	*/
	void setScale(float nScale);

	/**
	* @brief Renvoie la scale de la camera
	*
	* @return scale
	*/
	float getScale();

	/**
	* @brief Change la position de la camera
	*
	* @param[in] nPos Position de la camera
	*
	* @attention La postion de la camera est les coordonnées du centre de celle ci
	*/
	void setPosition(Vector2f nPos);

	/**
	* @brief Renvoie la position actuelle de la camera 
	*
	* @return pos
	*/
	Vector2f getPosition();

	/**
	* @brief Déplace la caméra avec le vecteur m 
	*
	* @param[in] m Vecteur de déplacement de la caméra
	*/
	void move(Vector2f m);

	/**
	* @brief Convertie des coordonnées en pixel sur l'écran en coordonnées sur la caméra
	*
	* @param[in] screenPos Position sur l'écran à convertir
	* @return finalPos Position sur la caméra calculé à partir de screenPos
	*/
	Vector2f screenPosToCamPos(Vector2f screenPos);

	/**
	* @brief Convertie des coordonnées en pixel sur la caméra en coordonnées dans le monde
	*
	* @param[in] camPos Position sur la caméra
	* @return finalPos dans le monde
	*/
	Vector2f camPosToWorldPos(Vector2f camPos);

	/**
	* @brief Détermine si un objet Shape est visible sur l'écran à travers le prisme de la Camera
	*
	* @param[in] obj Objet à tester
	* @return bool Oui ou Non l'objet est visible
	*
	* @note Cette méthode est très utile pour eviter d'afficher des objet non visible par le joueur ou même les détruirze quand ils sortent de l'écran.
	* @attention La méthode n'a été testé que sur des RectangleShape et des Sprite, Il peut y avaoir certain disfonctionnement avec les ConvexShape et les CircleShape. 
	*/
	bool isInCamView(Shape &obj);

	/**
	* @brief Détermine si un geometrix est dans le champs de la camera
	*
	* @param[in] obj Objet à tester
	* @return bool Oui ou Non l'objet est visible
	*
	* @note Cette méthode est très utile pour eviter d'afficher des objet non visible par le joueur ou même les détruirze quand ils sortent de l'écran.
	* @attention La méthode n'a été testé que sur des RectangleShape et des Sprite, Il peut y avaoir certain disfonctionnement avec les ConvexShape et les CircleShape.
	*/
	bool isInCamView(CollisionBox &obj);

	/**
	* @brief Limites de la camera en X
	*/
	Vector2f camX;

	/**
	* @brief Limites de la camera en Y
	*/
	Vector2f camY;

      private:
	Vector2f pos; //<! Positon de la camera
	float scale;  //<! Scale de la camera
};

#endif // !CAMERA_CLASS_H
