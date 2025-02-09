#include "../../../include/BBOP/Graphics/animatedSpriteClass.h"
#include "../../../include/BBOP/Graphics.h"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <vector>

AnimatedSprite::AnimatedSprite()
  : AnimatedSprite("assets/animated_sprites/Smoke-Sheet.png", Vector2i(4,5), 0.1f, 1)
{}

AnimatedSprite::AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t)
  : AnimatedSprite(_animated_sprite_sheet, _size, _frame_t, 0)
{}

AnimatedSprite::AnimatedSprite(std::string _animated_sprite_sheet, Vector2i _size, float _frame_t, int _dead_frame)
  : Sprite()
{
  animated_sprite_texture = bbopLoadSpriteSheet(_animated_sprite_sheet.c_str(), _size.y, _size.x);
  frame_t = _frame_t;
  n_frame = _size.x * _size.y - _dead_frame;
  frame_cpt = rand() % n_frame;
  total_t = n_frame * frame_t;
  anim_start = glfwGetTime();
  last_frame_t = glfwGetTime();

  setTexture(animated_sprite_texture[0]);
}

bool AnimatedSprite::update()
{
  float actual_time = glfwGetTime();

  if(actual_time - last_frame_t >= frame_t){
    frame_cpt++;
    last_frame_t = glfwGetTime();
    if(frame_cpt >= n_frame){
      frame_cpt = 0;
    }
    setTexture(animated_sprite_texture[frame_cpt]);
  }

  if(actual_time - anim_start >= total_t)
    return true;

  return false;
}

std::vector<Texture>& AnimatedSprite::getSpriteSheet()
{
  return animated_sprite_texture;
}
