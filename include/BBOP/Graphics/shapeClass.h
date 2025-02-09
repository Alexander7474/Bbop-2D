/*
 * shapeClass.h
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

#ifndef SHAPE_CLASS_H
#define SHAPE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <initializer_list>

#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "collisionBoxClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

/**
 * @class Shape
 * @brief Class parente de toutes les formes géométriques(RectangleShape, ConvexShape, CircleShape, Sprite) 
 * @details Elle stock et gère tous les attribut de base d'une forme géométrique comme sa position ou encore sa couleur
 *
 * @attention Certaine Shape utilise des attributs de cette class parent de manière différente donc renseignez vous sur les shapes que vous utilisez
 * @todo Optimiser les constructeurs des Shape
 * @todo Gérer l'héritage de Geometric sur Shape 
 */
class Shape : public BbopDrawable
{
public:

  /**
   * @brief Constructeur de Shape 
   */
  Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize);
  
  /**
   * @brief Constructeur par défault de Shape
   */
  Shape();

  /**
   * @brief Constructeur par copie de shape
   */ 
  Shape(const Shape &other);

  /**
   * @brief Destructeur de shape
   */
  ~Shape();

  /**
   * @brief Initialise la Shape comme sont constructeur
   */
  void initShape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize);
  
  /**
   * @brief Renvoie la Taille du Shape
   *
   * @return size taille
   */
  const Vector2f &getSize() const;

  /**
   * @brief Change la taille du Shape 
   *
   * @param[in] nSize taille
   */
  void setSize(const Vector2f &nSize);

  /**
   * @brief Change la taille du Shape 
   *
   * @param[in] x_ taille x
   * @param[in] y_ taille y
   */
  void setSize(float x_, float y_);

  /**
   * @brief Renvoie la position du Shape
   *
   * @return pos position
   */
  const Vector2f &getPosition() const;

  /**
   * @brief Change la position du Shape 
   *
   * @param[in] nPos position
   */
  void setPosition(const Vector2f &nPos);

  /**
   * @brief Change la position de la Shape
   *
   * @param[in] x_ position x
   * @param[in] y_ position y
   */
  void setPosition(float x_, float y_);

  /**
   * @brief Renvoie l'origine de la Shape 
   *
   * @return origin
   */
  const Vector2f &getOrigin() const;

  /**
   * @brief Change l'origine de la Shape 
   *
   * @param[in] nOrigin origin 
   */
  void setOrigin(const Vector2f &nOrigin);

  /**
   * @brief Change l'origine de la Shape 
   *
   * @param[in] x_ origine x
   * @param[in] y_ origine y
   */
  void setOrigin(float x_, float y_);
  
  /**
   * @brief Renvoie la couleur de Shape
   *
   * @return RGB couleur
   */
  const Vector3i &getColor() const;

  /**
   * @brief Change la couleur de Shape 
   *
   * @param[in] nRGB couleur en rgb 
   */
  void setColor(const Vector3i &nRGB);
  
  /**
   * @brief Change la couleur de Shape 
   *
   * @param[in] x_ rouge
   * @param[in] y_ vert
   * @param[in] z_ bleu
   */
  void setColor(int x_, int y_, int z_);

  /**
   * @brief Renvoie la transaprence du la Shape
   *
   * @return alpha
   */
  float getAlpha() const;

  /**
   * @brief Change la transaprence de la Shape 
   *
   * @param[in] nAlpha transparence
   */
  void setAlpha(float nAlpha);

  /**
   * @brief Renvoie la rotation de la Shape 
   *
   * @return rotation
   */
  float getRotation() const;

  /**
   * @brief Change la rotation de la Shape
   *
   * @param[in] nRotation rotation
   */
  void setRotation(float nRotation);

  /**
   * @brief Renvoie la boîte de collision de Shape
   *
   * @return shapeCollisionBox
   */
  CollisionBox &getCollisionBox();

  /**
   * @brief Change l'état de l'automatisation de la mise a jour de la boîte de collision 
   *
   * @param[in] etat activation
   */
  void setAutoUpdateCollision(bool etat); 

  /**
   * @brief Déplace la Shape
   *
   * @param[in] vecM vecteur de mouvement
   */
  void move(const Vector2f &vecM);

  /**
   * @brief Déplace la Shape
   *
   * @param[in] x_ distance en x
   * @param[in] y_ distance en y
   */
  void move(float x_, float y_);

protected:
  VAO shapeVAO; //<! VAO de opengl de la Shape
  VBO shapeVBO; //<! VBO opengl de la Shape
  EBO shapeEBO; //<! EBO opengl de la Shape
  Vector2f pos; //<! position de la shape
  Vector2f size; //<! taille de la shape
  Vector2f origin; //<! origin de la shape
  Vector3i RGB; //<! couleur de la shape
  bool autoUpdateCollision; //<! activation automatique des collisions
  float rotation; //<! rotation
  CollisionBox shapeCollisionBox; //<! boîte de collision
  float alpha; //<! transparence de la shape
  virtual void buildVAO() = 0;
  virtual void updateVBO() = 0;
  virtual void updateVBORGB() = 0;
  virtual void updateVBOAlpha() = 0;
};

/**
 * @brief Gère un rectangle/carré
 */
class RectangleShape : public Shape
{
public:

  /**
   * @brief Constructeur par défault du rectangle 
   */
  RectangleShape();

  /**
   * @brief Constructeur du rectangle 
   *
   * @param[in] nSize Taille du rectangle 
   * @param[in] nPos Position du rectangle
   */
  RectangleShape(Vector2f nSize, Vector2f nPos);
  RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);
  
  void Draw(GLint* renderUniforms) const override;
private:
  GLfloat vertices[24];
  GLuint indices[6];
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
};

/**
 * @brief Gère une convex
 */
class ConvexShape : public Shape
{
public:

  /**
   * @brief Constructeur par défault de la convex 
   *
   * @note Utiliser initConvex avant d'utiliser la convex
   */
  ConvexShape();

  /**
   * @brief Constructeur de la convex 
   *
   * @param[in] nnPoint Lombre de point de la convex 
   * @param[in] nlistPoint Liste de poitn de la convex 
   */
  ConvexShape(int nnPoint, Vector2f* nlistPoint);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);

  ConvexShape(const ConvexShape& other);
  ~ConvexShape();

  ConvexShape& operator=(const ConvexShape& other);
  
  /**
   * @brief Initialise la convex comme le constructeur
   *
   * @param[in] nnPoint nombre de points de la convex
   * @param[in] nlistPoint list de point de la convex
   */
  void initConvex(int nnPoint, Vector2f* nlistPoint);

  void Draw(GLint* renderUniforms) const override;
private:
  GLfloat* vertices;
  GLuint* indices;
  int nPoint;
  Vector2f* listPoint;
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
};

/**
 * @brief Gère un cercle
 *
 * @see ConvexShape
 * @note Le cercle est un enfant de convex, il gère juste la convex comme un cercle
 */
class CircleShape : public ConvexShape
{
public:

  /**
   * @brief constructeur du cercle 
   *
   * @param[in] nnPoint nombre de point du cercle
   * @param[in] nRadius rayon du cercle 
   *
   * @note Avec 3 point le cercle est un triangle !!
   */
  CircleShape(int nnPoint, float nRadius);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);

  /**
  * @brief Renvoie le rayon du cercle
  *
  * @return radius
  */
  float getRadius() const;

  /**
  * @brief Change le rayon du cercle
  *
  * @param[in] nRadius rayon du cercle
  */
  void setRadius(float nRadius);

  /**
  * @brief Renvoie le nombre de point du cercle
  *
  * @return nPointCircle
  */
  int getNPointCircle() const;

  /**
  * @brief Change le nombre de point du cercle
  *
  * @param[in] nnPoint nombre de point du cercle
  */ 
  void setNPointCircle(int nnPoint);

private:
  float radius;
  int nPointCircle;
protected:

  /**
  * @brief Recalcule la géometrie du cercle
  */
  void buildConvex();
};

#endif // ! SHAPE_CLASS_H
