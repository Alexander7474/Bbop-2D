#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "animatedSpriteClass.h"
#include "sceneClass.h"
#include "spriteClass.h"
#include "collisionBoxClass.h"
#include "bbopMathClass.h"
#include "lightClass.h"
#include "cameraClass.h"

/**
* @class Map "map.h" "map.cpp"
* @brief La class Map initialise une map LDTK  
* @author Alexandre
* @version 0.1
*/
class Map
{
private:
  std::vector<Sprite> tiles; //!< Vecteur de Sprite pour stocké les tuiles de la map
  std::vector<CollisionBox> collision_layer; //!< stock les collision de la box
  std::vector<Vector2f> spawn_points; //<! different point de spawn de la map
  std::vector<AnimatedSprite> animated_sprites; //<! stock les particule animé de la map
  std::vector<Light> lights; //<! stock les lumières
  Sprite background; //!< Background du jeu

  float y_size;
  float x_size; 

  float global_illumination;
  
public:

  friend class Game;

  /**
  * @brief Constructeur par défault de Map.
  *
  * @see Map::Map();
  */
  Map();

  /**
  * @brief Constructeur de Map.
  * @overload
  * @param tiles_folder Chemin d'accès vers le dossier contenant les tuiles de la map de la forme img/map/glace/
  * @note Le dossier doit contenir un fichier background.png, definition.bmc et un set de tuiles en fonctions de defintion.bmc
  */
  Map(const char* map_folder);

  /**
  * @brief Conctructeur par copie de Map
  * @param other Autre Map
  */
  Map(const Map& other);

  /**
  * @brief Dessine la map sur l'écran, à utiliser avec une scene ou une autre méthode draw
  *
  */
  void Draw(Scene &scene, Camera &ground_camera);


  /**
   * @brief Prend un dossier fais avec ldtk
   */
  void remplissage(const char* tiles_folder);

   /**
  * @brief update de la map
  */
  void update();

  std::vector<Sprite>& getTiles();
  std::vector<CollisionBox>& getCollision();
  std::vector<Vector2f>& getSpawnPoints();
};
