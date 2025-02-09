/*
 * bbopGlobal.h
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

#ifndef GLOBALS_H
#define GLOBALS_H

/**
 * @brief Version de bbop
 */
#define BBOP_VERSION "0.4.1-alpha"

/**
 * Local headers
 */
#include "bbopMathClass.h"

/**
 * External headers
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief RenderMode avec uniquement les textures
 */
enum BBOP_SHADER_MODE_ENUM:int {
  BBOP_SHADER_MODE_TEXTURE=0,
  BBOP_SHADER_MODE_COLOR=1,
  BBOP_SHADER_MODE_MIX=2,
  BBOP_SHADER_MODE_TEXTURE_NMAP=3,
  BBOP_SHADER_MODE_MIX_NMAP=4
};

/**
 * @brief Détermine la place de l'adresse d'une valeur uniform dans le tableau d'adresse d'uniform du shader par default
 */
#define BBOP_UNIFORM_ADDR_RENDER_MODE 0
#define BBOP_UNIFORM_ADDR_TEXTURE 1
#define BBOP_UNIFORM_ADDR_NORMAL_MAP 2
#define BBOP_UNIFORM_ADDR_PROJECTION 3 
#define BBOP_UNIFORM_ADDR_PROJECTION_CAM 4 
#define BBOP_UNIFORM_ADDR_WINDOW_SIZE 5
#define BBOP_UNIFORM_ADDR_WINDOW_RESOLUTION 6 
#define BBOP_UNIFORM_ADDR_CAM_SCALE 7
#define BBOP_UNIFORM_ADDR_AMBIANT_LIGHT 8
#define BBOP_UNIFORM_ADDR_LIGHTS_N 9

/**
 * @brief Nombre d'uniform a envoyer au shader
 */
#define BBOP_UNIFORM_N 10

/**
 * @brief Variable global qui stoke la taille de la fenêtre.
 */
extern Vector2i BBOP_WINDOW_SIZE;

/**
 * @brief Variable global qui stoke la résolution de la fenêtre.
 */
extern Vector2i BBOP_WINDOW_RESOLUTION;

/**
 * @brief Récupère les données d'un fichier et les renvoie sous forme de string.
 * @details Cette fonction est seulement utilisé par la class Shader.
 * 
 * @param[in] filename Chemin d'accès vers le fichier à lire.
 * @return std::string Contenu du fichier.
 */
std::string bbopGetFileData(const char* filename);

/**
 * @class BbopDrawable
 * @brief Class Parent de tous ce qui peut être dessiné par une Scene.
 * @details La class Scene utilise cette comme paramètre dans Draw(BbopDrawable).
 *
 * @see Scene
 */
class BbopDrawable
{
public:

  /**
   * @brief Déssine l'objet héritant de la class.
   * @details Cette méthode est utilisé dans Scene.Draw(BbopDrawable) qui lui transmet le renderModeLoc.
   *
   * @see Scene.Draw(BbopDrawable)
   */
  virtual void Draw(GLint* renderUniforms) const = 0;

};

/**
  * @stock les logs de la libs
  */
extern std::vector<std::string> LOGS;

#endif // ! GLOBALS_H
