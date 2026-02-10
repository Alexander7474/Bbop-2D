/*
 * collisionBoxClass.h
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

#ifndef COLLISION_BOX_CLASS_H
#define COLLISION_BOX_CLASS_H

#include "bbopMathClass.h"
#include "geometricClass.h"
#include <iostream>

/**
* @class CollisionBox
* @brief gère une boîte de collision
*
* @note Cette class est utilisé par défault pour gèrer les collision des Shape
*/
class CollisionBox : public Geometric
{
      public:
	/**
	* @brief Constructeur de la boîte de collision 
	*
	* @param[in] nPos position de la boîte
	* @param[in] nOrigin origin de la boîte 
	* @param[in] nSize Dimension de la boîte 
	* @param[in] nRotation angle de rotation de la boîte 
	*/
	CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize,
		float nRotation);

	/**
	* @brief Constructeur de la boîte de collision à partir d'une Geometric 
	*
	* @param[in] to_follow Geometric à copier 
	*/
	CollisionBox(const Geometric &to_follow);

	/**
	* @brief constructeur par défault de la boîte de collision 
	*/
	CollisionBox();

	/**
	* @brief Detecte si la boîte est en collision avec une autre
	*
	* @param[in] otherBox Boîte à comparer avec la boîte qui appele la méthode
	* @return bool true si la boîte est en collision avec otherBox et false si non
	*
	* @attenion Cette méthode ne prend pas en compte la roation des deux boîte pour des raisons de performances
	*/
	bool check(const CollisionBox &otherBox) const;

	/**
	* @brief Detecte si la boîte est en collision en prenant en compte la rotaion des deux boîtes
	*
	* @param[in] otherBox Boîte à comparer avec la boîte qui appele la méthode 
	* @return bool true si la boîte est en collision avec otherBox et false si non
	*
	* @attenion Cette méthode prend en compte la rotation et est donc plus gourmand en ressource, à utiliser seulement si nécessaire
	*/
	bool checkWithRotation(const CollisionBox &otherBox) const;

	/**
	* @brief Renvoie l'offset X de la boîte 
	* @details l'offset X représente le rétrécicement horizontale de la boîte de collision par rapport à sa Geomtric/Shape 
	* @details X.x->gauche X.y->droite
	*/
	Vector2f getOffsetX() const;

	/**
	* @brief Renvoie l'offset Y de la boîte 
	* @details L'offset Y représente le rétrécicement vertical de la boîte de collision par rapport à sa Geomtric/Shape
	* @details Y.x->haut X.y->bas
	*/
	Vector2f getOffsetY() const;

	/**
	* @brief Change l'offsetX
	*
	* @param[in] off_ offsetX
	*
	* @see getOffsetX()
	*/
	void setOffsetX(const Vector2f &off_);

	/**
	* @brief Change l'offsetX
	*
	* @param[in] x_ offsetX.x
	* @param[in] y_ offsetX.y
	*
	* @see getOffsetX()
	*/
	void setOffsetX(float x_, float y_);

	/**
	* @brief Change l'offsetY
	*
	* @param[in] off_ offsetX
	*
	* @see getOffsetY()
	*/
	void setOffsetY(const Vector2f &off_);

	/**
	* @brief Change l'offsetY
	*
	* @param[in] x_ offsetY.x 
	* @param[in] y_ offsetY.y
	*
	* @see getOffsetY()
	*/
	void setOffsetY(float x_, float y_);

	/**
	* @brief Copy les caractèristique d'un objet Geometric pour utiliser la boîte de collision comme la sienne
	*
	* @param[in] to_follow Geometric à copier/suivre
	*/
	void follow(const Geometric &to_follow);

	/**
	* @brief Renvoie la position y de la limite haute de la boite 
	*
	* @return top 
	*/
	float getTop();

	/**
	* @brief Renvoie la position y de la limite basse de la boite 
	*
	* @return bottom
	*/
	float getBottom();

	/**
	* @brief Renvoie la position x de la limite gauche de la boite 
	*
	* @return left 
	*/
	float getLeft();

	/**
	* @brief Renvoie la position x de la limite droite de la boite 
	*
	* @return right
	*/
	float getRight();

	/**
	* @brief renverse la boîte de collision horizontallement
	*/
	void flipHorizontally();

	/**
	* @brief renverse la boîte de collision verticallement  
	*/
	void flipVertically();

      private:
	Vector2f offsetX; //<! rétrécicement X
	Vector2f offsetY; //<! rétrécicement Y
};

#endif // !COLLISION_BOX_CLASS_H
