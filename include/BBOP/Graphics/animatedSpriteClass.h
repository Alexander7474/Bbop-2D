#pragma once 

#include <string>
#include <vector>

#include "spriteClass.h"

/**
 * @class AnimatedSprite
 * @brief Gère un Sprite qui joue une aniomation en boucle 
 *
 * @todo Ajouter une class StateSprite qui gère un sprite et qui l'anime en fonction d'une énumération d'état de ce Sprite
 */
class AnimatedSprite : public Sprite
{
public: 
  /**
   * @brief COntructeur du sprite animé
   *
   * @param[in] _animated_sprite_sheet Chemin d'accés vers le spritesheet 
   * @param[in] _size Vecteur de la taille de la sprite sheet, x: nombre de ligne, y: nombre de colonne
   * @param[in] _frame_t temps entre chaque frame
   * @param[in] _dead_frame frame morte, si le sprite sheet n'est pas complet
   * @param[in] _random_start frame de debut aleatoire
   */
  AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t, int _dead_frame, bool _random_start);
  AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t, int _dead_frame);
  AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t);
  AnimatedSprite();

  /**
  * @brief Met a jour les particules 
  *
  * @return bool renvoie true si l'animation est fini
  */
  bool update();

  /**
  * @brief renvoie la liste de texture 
  */
  std::vector<Texture>& getSpriteSheet();
  std::vector<Texture> animated_sprite_texture; 
  long unsigned int frame_cpt; //<! compteur de frame
  long unsigned int n_frame; //<! nombre de frame 
  float frame_t; //<! timing entre les frames
  float total_t; //<! temps total de l'anim
  float anim_start; //<! depart de l'anim 
  float last_frame_t; //<! timing de la dernière frame
};
