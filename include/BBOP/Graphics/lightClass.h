/*
 * lightClass.h
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

#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "bbopMathClass.h"
#include "bbopGlobal.h"

/**
 * @class Light
 * @brief Gère un point de lumière en fonction de son Intensité, sa couleur et son attenuation
 *
 * @todo Créer une class DirectionnalLight pour différentier certaine lumière 
 * @todo Ajouter la gestion d'une shadowMap pour empêcher le passage de la lumière 
 * @todo utiliser un point à éclairé pour déterminer la rotation d'une lumière directionnelle
 */
class Light
{
public:

  /**
  * @brief Constructeur de light 
  *
  * @param[in] nPos Position
  * @param[in] nIntensity Intensité
  * @param[in] nRGB couleur
  * @param[in] nConstantAttenuation attenuation constante 
  * @param[in] nLinearAttenuation attenuation linéaire 
  * @param[in] nQuadraticAttenuation attenuation quadratique
  */
  Light(Vector2f nPos, float nIntensity, Vector3i nRGB, float nConstantAttenuation,float nLinearAttenuation, float nQuadraticAttenuation);

  /**
   * @brief Constructeur par défault de Light 
   *
   * @details Lumière blanche avec 0.2 d'intensité et 0.2 pour toute les attenuation
   */
  Light();

  /**
  * @brief Renvoie la couleur de Light
  *
  * @return RGB
  */
  Vector3i getColor();

  /**
   * @brief Change la couleur de Light
   *
   * @param[in] nRGB Couleur
   */
  void setColor(Vector3i nRGB);
  
  /**
  * @brief Renvoie la position de Light
  *
  * @return pos
  */
  Vector2f getPosistion();

  /**
   * @brief Change la position de Light
   *
   * @param[in] nPos Position
   */
  void setPosition(Vector2f nPos);
  
  /**
  * @brief Renvoie l'Intensité de Light
  *
  * @return intensity
  */
  float getIntensity();

  /**
   * @brief Change l'Intensité de Light
   *
   * @param[in] nIntensity Intensité
   */
  void setIntensity(float nIntensity);
  
  /**
  * @brief Renvoie l'attenuation constante de Light
  *
  * @return constantAttenuation
  */
  float getConstant();

  /**
   * @brief Change l'attenuation constante de Light
   *
   * @param[in] nConstant attenuation constante
   */
  void setConstant(float nConstant);
  
  /**
  * @brief Renvoie l'attenuation linéaire de Light
  *
  * @return linearAttenuation
  */
  float getLinear();

  /**
   * @brief Change l'attenuation linéaire de Light
   *
   * @param[in] nLinear attenuation linéaire
   */
  void setLinear(float nLinear);
  
  /**
  * @brief Renvoie l'attenuation quadratique de Light
  *
  * @return quadraticAttenuation
  */
  float getQuadratic();

  /**
   * @brief Change l'attenuation quadratique de Light
   *
   * @param[in] nQuadratic attenuation quadratique
   */
  void setQuadratic(float nQuadratic);

  /**
  * @brief change l'angle d'ouverture de la light 
  *
  * @parm[in] nOpenAngle Nouvelle angle d'ouverture
  */
  void setOpenAngle(float nOpenAngle);

  /**
  * @brief Renvoie l'angle d'ouverture
  *
  * @return openAngle
  */
  float getOpenAngle();

  /**
  * @brief change l'angle de rotation de la light 
  *
  * @parm[in] nRotationAngle Nouvelle angle de rotation
  */
  void setRotationAngle(float nRotationAngle);

  /**
  * @brief Renvoie l'angle de rotation
  *
  * @return rotationAngle
  */
  float getRotationAngle();

private:
  Vector2f pos; //<! postion de Light
  Vector3i RGB; //<! Couleur de la lumière
  float intensity; //<! Intensité de la lumière
  float constantAttenuation; //<! Attnuation constante
  float linearAttenuation; //<! Attnuation linéaire
  float quadraticAttenuation; //<! Attnuation quadratique
  float openAngle; //<! Angle d'ouverture de la light 
  float rotationAngle; //<! Angle de roation de la light
};

#endif // ! LIGHT_CLASS_H
