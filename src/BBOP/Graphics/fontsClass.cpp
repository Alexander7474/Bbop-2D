/*
 * fontsClass.cpp
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

#include "../../../include/BBOP/Graphics/fontsClass.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ostream>
#include <vector>

// Charge une police TrueType en tant que texture OpenGL
void loadFontTexture(const char* fontPath, int fontSize, Character* charList, int numTextures) {
   
  FT_Library ft;
    if (FT_Init_FreeType(&ft) != 0) {
        std::cerr << "Erreur lors de l'initialisation de FreeType" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face) != 0) {
        std::cerr << "Erreur lors du chargement de la police de caractères" << std::endl;
        FT_Done_FreeType(ft);
        return;
    }

    if (FT_Set_Pixel_Sizes(face, 0, fontSize) != 0) {
        std::cerr << "Erreur lors du redimensionnement de la police de caractères" << std::endl;
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return;
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Désactive le padding pour la texture
    
    // Générer les textures OpenGL pour chaque glyphe
    for (int i = 0; i < numTextures; ++i) {
        char character = static_cast<char>(i);
        if (FT_Load_Char(face, character, FT_LOAD_RENDER) != 0) {
            std::cerr << "Erreur lors du chargement du glyphe " << character << std::endl;
            continue;
        }

        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        // Inverser le glyph
        for (unsigned int row = 0; row < face->glyph->bitmap.rows / 2; ++row) {
          for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
            std::swap(face->glyph->bitmap.buffer[row * face->glyph->bitmap.width + col],
                      face->glyph->bitmap.buffer[(face->glyph->bitmap.rows - row - 1) * face->glyph->bitmap.width + col]);
          }
        }
        
        // Générer une texture OpenGL pour le glyphe
    
        glGenTextures(1, &charList[i].TextureID);
        glBindTexture(GL_TEXTURE_2D, charList[i].TextureID);
        

        // Create a new image buffer for RGBA format
        std::vector<unsigned char> rgbaBuffer(face->glyph->bitmap.width * face->glyph->bitmap.rows * 4); // 4 channels for RGBA

        // Copy the red channel to all RGBA channels
        for (unsigned int row = 0; row < face->glyph->bitmap.rows; ++row) {
          for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
            unsigned char red = face->glyph->bitmap.buffer[row * face->glyph->bitmap.width + col];
            unsigned char* pixel = &rgbaBuffer[(row * face->glyph->bitmap.width + col) * 4]; // RGBA pixel
            pixel[0] = red; // Red channel
            pixel[1] = red; // Green channel
            pixel[2] = red; // Blue channel
            pixel[3] = (red == 0) ? 0 : 255; // Alpha channel (fully opaque)
          }
        }
 
        charList[i].size.x = face->glyph->bitmap.width;
        charList[i].size.y = face->glyph->bitmap.rows;
        charList[i].bearing.x = face->glyph->bitmap_left; // Conversion de la valeur en pixels
        charList[i].bearing.y = face->glyph->bitmap_top; // Conversion de la valeur en pixels
        // Load the glyph as GL_RGBA format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuffer.data());

        // Configuration des paramètres de texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
  }

    // Libérer les ressources FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Font::Font(int glyphSize, const char *ttfPath)
{
  loadFontTexture(ttfPath, glyphSize, charL, 128);
}

TexteBox::TexteBox(const char * nTexte, Font* nFont)
  : texteFont(nFont),
    pos(0.0f,0.0f),
    origin(0.0f,0.0f),
    rotation(0.0f),
    RGB(255,255,255),
    alpha(1.0f),
    texte(new char[strlen(nTexte) + 1]),
    sizeTexte(static_cast<unsigned int>(strlen(nTexte)+1)),
    glyphList(new NoTextureSprite[strlen(nTexte)+ 1]),
    offset(2.5f)
{
  strcpy(const_cast<char*>(texte), nTexte);
  sizeTexte = static_cast<unsigned int>(strlen(texte));
  buildTexteBox();
}

TexteBox::TexteBox(const TexteBox& other)
  : texteFont(other.texteFont),
    pos(other.pos),
    origin(other.origin),
    rotation(other.rotation),
    RGB(other.RGB),
    alpha(other.alpha),
    texte(new char[other.sizeTexte]),
    sizeTexte(other.sizeTexte),
    glyphList(new NoTextureSprite[other.sizeTexte]),
    offset(other.offset)
{
  strcpy(const_cast<char*>(texte), other.texte);
  for(unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i] = other.glyphList[i];
}

TexteBox& TexteBox::operator=(const TexteBox& other)
{
  if (this != &other){
    texteFont = other.texteFont;
    pos = other.pos;
    origin = other.origin;
    rotation = other.rotation;
    RGB = other.RGB;
    alpha = other.alpha;
    sizeTexte = other.sizeTexte;
    offset = other.offset;
    delete [] texte;
    delete [] glyphList;
    texte = new char[sizeTexte];
    glyphList = new NoTextureSprite[sizeTexte];
    strcpy(const_cast<char*>(texte), other.texte);
    for(unsigned int i = 0; i < sizeTexte; i++){
      glyphList[i] = other.glyphList[i];
    }
  }
  return *this;
}

TexteBox::~TexteBox()
{
  delete [] glyphList;
  delete [] texte;
}

void TexteBox::buildTexteBox()
{
  if(texteFont == nullptr){
    std::cerr << "Error buiding texteBox, font initialized has nullptr" << std::endl;
    return;
  }
  float sizeTotal = 0.f;
  float sizeY = 0.f;
  for (unsigned int i = 0; i < sizeTexte; i++){
    glyphList[i].setSize(Vector2f(texteFont->charL[static_cast<unsigned char>(texte[i])].size.x,texteFont->charL[static_cast<unsigned char>(texte[i])].size.y));
    if(glyphList[i].getSize().y > sizeY)
      sizeY = glyphList[i].getSize().y;
    glyphList[i].setOrigin(Vector2f(-(sizeTotal+texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.x)+origin.x,texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.y+origin.y));
    glyphList[i].setPosition(pos);
    glyphList[i].setRotation(rotation);
    glyphList[i].setColor(RGB);
    glyphList[i].setAlpha(alpha);
    glyphList[i].setRGBFilterState(true);
    if(static_cast<unsigned char>(texte[i]) == ' ')
      sizeTotal+=5.0f;
    sizeTotal+=texteFont->charL[static_cast<unsigned char>(texte[i])].size.x+texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.x;
  }
  size.x = sizeTotal;
  size.y = sizeY;
}

void TexteBox::Draw(GLint *renderUniforms) const
{
  for (unsigned int i = 0; i < sizeTexte; i++){
    glBindTexture(GL_TEXTURE_2D, texteFont->charL[static_cast<unsigned char>(texte[i])].TextureID);
    glyphList[i].Draw(renderUniforms);
  }
}

Vector2f TexteBox::getPosition()
{
  return pos;
}

void TexteBox::setPosition(Vector2f nPos)
{
  pos = nPos;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setPosition(pos);
}

Vector2f TexteBox::getOrigin()
{
  return origin;
}

void TexteBox::setOrigin(Vector2f nOrigin)
{
  pos = nOrigin;
  float sizeTotal = 0.0f;
  for (unsigned int i = 0; i < sizeTexte; i++){
    glyphList[i].setOrigin(Vector2f(-(sizeTotal+texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.x)+origin.x,texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.y+origin.y));
    if(static_cast<unsigned char>(texte[i]) == ' ')
      sizeTotal+=5.0f;
    sizeTotal+=texteFont->charL[static_cast<unsigned char>(texte[i])].size.x+texteFont->charL[static_cast<unsigned char>(texte[i])].bearing.x;
  }
}

Vector3i TexteBox::getColor()
{
  return RGB;
}

void TexteBox::setColor(Vector3i nRGB)
{
  RGB= nRGB;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setColor(RGB);
}

void TexteBox::setAlpha(float nAlpha)
{
  alpha = nAlpha;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setAlpha(alpha);
}

float TexteBox::getAlpha()
{
  return alpha;
}

void TexteBox::setRotation(float nRotation)
{
  rotation = nRotation;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setRotation(rotation);
}

float TexteBox::getRotation()
{
  return rotation;
}

void TexteBox::setTexte(const char * nTexte)
{
  delete [] texte;
  texte = new char[strlen(nTexte)+ 1];
  strcpy(const_cast<char*>(texte), nTexte);
  sizeTexte = static_cast<unsigned int>(strlen(texte));
  delete [] glyphList;
  glyphList = new NoTextureSprite[sizeTexte];
  buildTexteBox();
}

void TexteBox::setFont(Font *font_)
{
  texteFont = font_;
  buildTexteBox();
}

const Vector2f &TexteBox::getSize()
{
  return size;
}
