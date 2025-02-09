/*
 * spriteClass.h
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

#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "textureClass.h"
#include "collisionBoxClass.h"
#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "shapeClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

/**
  * @brief Gère un Sprite (Rectangle avec une Texture)
  *
  * @note Hérite de la class Shape pour gérer les infos du rectangle 
  * @attention L'attribut RGB du Sprite sert comme filtre sur la texture quand isRGBFilter est true
  *
  * @see Shape NoTextureSprite
  */
class Sprite : public Shape
{
public:
  Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);
  Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  Sprite(Texture nTexture, Vector2f nPos);

  /**
   * @brief Constructeur du Sprite 
   *
   * @param[in] nTexture texture du Sprite
   */
  Sprite(Texture nTexture);

  /**
   * @brief Constructeur par défault de Sprite 
   *
   * @note Utilsier setTexture avant d'utiliser le Sprite 
   */ 
  Sprite();

  /**
   * @brief Constructeur de srpite
   */
  Sprite(const Sprite& other);

  /**
   * @brief Destructeur de sprite
   */
  ~Sprite();

  /**
   * @brief Operateur = de sprite
   */
  Sprite& operator=(const Sprite& other);

  void Draw(GLint* renderUniforms) const override;

  /**
  * @brief Change la texture du sprite
  *
  * @param[in] nTexture texture 
  */
  void setTexture(const Texture &nTexture);

  /**
   * @brief renvoie un pointeur vers la texture du sprite 
   *
   * @return spriteTexture pointeur vers la Texture du sprite
   */
  Texture* getTexture();

  /**
   * @brief Change la texture de la normal map du sprite 
   *
   * @details le Sprite utilise automatiquement sa normal map lors du rendue dès que le pointer vers celle ci est non null
   *
   * @param[in] nNormalMap Texture de normal map
   */
  void setNormalMap(const Texture &nNormalMap);

  /**
   * @brief renvoie la normal map du sprite 
   *
   * @return spriteNormalMap pointeur vers la Texture de la normal map
   */
  Texture* getNormalMap();

  /**
  * @brief Renvoie si oui ou non le filtre de couleur est activé 
  *
  * @return isRGBFilter
  */
  bool getRGBFilterState() const;

  /**
  * @brief Change l'etat du filtre de couleur 
  *
  * @param[in] etat Etat du filtre de couleur
  */
  void setRGBFilterState(bool etat);

  /**
  * @brief Retourne la Texture horizontallement 
  */
  void flipHorizontally();

  /**
  * @brief Retourne la Texture Verticallement
  */
  void flipVertically();

private:
  Texture* spriteTexture; // pointeur ves la Texture a bing avec opengl lors du dessin
  Texture* spriteNormalMap; // normal map de la texture du sprite
protected:
  GLfloat vertices[32];
  GLuint indices[6];
  bool isRGBFilter;
  void buildVAO() override; //<! Calcule de la geométrie 
  void updateVBO() override; //<! Recalcule de la géométrie
  void updateVBORGB() override; 
  void updateVBOAlpha() override;
 };

/**
  * @class NoTextureSprite 
  * @warning Ce sprite ne bind pas de Texture avec opengl, c'est donc a l'utilisateur de le faire.
  * @details class un peu four tous pour faire des trucs pas très légal
  */
class NoTextureSprite : public Sprite
{
public:
  void Draw(GLint* renderUniforms) const override;
  void DrawAsFrameBuffer() const;
};

#endif // !SPRITE_CLASS_H
