/*
 * fontsClass.h
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

#ifndef FONTS_CLASS_H
#define FONTS_CLASS_H

#include "bbopGlobal.h"
#include "bbopMathClass.h"
#include "spriteClass.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * @brief Stock un caractère
 */
struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    Vector2f size;       // Size of glyph
    Vector2f bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

void loadFontTexture(const char* fontPath, int fontSize, Character* charList, int numTextures);

/**
 * @class Font
 * @brief Stock une police de caractère
 *
 * @note Utilisé par la class TexteBox
 *
 * @todo créer un Constructeur par défaukt avec une police system
 */
class Font
{
public:

  /**
   * @brief Constructeur de la class Font 
   *
   * @param[in] glyphSize Taille de la police de caractère
   * @param[in] ttfPath Chemin d'accès vers de fichier de police de caractère 
   *
   * @attention Les polices de caractères de ne fonctionne que avec des .ttf et charge uniquement les 128 premiers caractères de la police 
   * @todo Arranger la class pour utiliser tous les caractères de la police
   */
  Font(int glyphSize, const char *ttfPath);

  /**
   * @brief List dans la quelles les 128 caractères de la police sont stockées 
   */
  Character charL[128];

};

/**
 * @class TexteBox
 * @brief Stock du texte pour le draw dans la fenêtre 
 *
 * @attention Cette class peut produire des erreurs de segementation dans un tableau dynamique, utiliser de préférence un std::vector en cas de core dump
 */
class TexteBox : public BbopDrawable
{
public:

  /**
  * @brief Constructeur de la boîter de texte
  * 
  * @param[in] nTexte Chaine de la caractères à afficher avec la boîte 
  * @param[in] nFont Police de caractère à utiliser avec la boîte de texte
  */
  TexteBox(const char * nTexte, Font *nFont);
  TexteBox(const TexteBox& other);
  ~TexteBox();

  TexteBox& operator=(const TexteBox& other);

  Vector2f getPosition();
  void setPosition(Vector2f nPos);
  Vector2f getOrigin();
  void setOrigin(Vector2f nOrigin);
  Vector3i getColor();
  void setColor(Vector3i nRGB);
  float getAlpha();
  void setAlpha(float nAlpha);
  float getRotation();
  void setRotation(float nRotation);

  /**
   * @brief Change la font de la texte box
   *
   * @param[in] font_ nouvelle font
   */
  void setFont(Font *font);
  
  /**
  * @brief Renvoie la chaine de caractères affiché
  *
  * @return texte
  */
  const char* getTexte();
  
  /**
  * @brief Change la chaine de caractères
  *
  * @param[in] nTexte Nouvelle chaine de caractères 
  */
  void setTexte(const char* nTexte);
  
  /**
  * @brief Fabrique la liste de NoTextureSprite glyphList
  * @details Cette liste de NoTextureSprite est utilisé par Draw
  */
  void buildTexteBox();

  /**
  * @brief Dessine la boîte de texte 
  * @overload 
  *
  * @param[in] renderModeLoc GPU MEM addr du mode de rendue
  */
  void Draw(GLint *renderUniforms) const override;

  /**
   * @brief renvoie la taille de la boite de texte 
   *
   * @return size
   */
  const Vector2f &getSize();

private:
  Font *texteFont;
  Vector2f pos;
  Vector2f origin;
  float rotation;
  Vector3i RGB;
  float alpha;
  const char* texte;
  unsigned int sizeTexte;
  NoTextureSprite* glyphList;
  float offset;
  Vector2f size;
};

#endif // !FONTS_CLASS_H
