/*
 * spriteClass.cpp
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

#include "../../../include/BBOP/Graphics/spriteClass.h"

Sprite::Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha)
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(new Texture(nTexture)),
    isRGBFilter(false)
{
  size.x = spriteTexture->getWidth(); size.y = spriteTexture->getHeight();
  pos = nPos;
  RGB = nRGB;
  origin = nOrigin;
  rotation = nRotation;
  alpha = nAlpha;
  spriteNormalMap = nullptr;
  // Build du vao
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  buildVAO();
}

Sprite::Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin)
  : Sprite(nTexture, nPos, nRGB, nOrigin, 0.0f, 1.0f)
{}

Sprite::Sprite(Texture nTexture, Vector2f nPos)
  : Sprite(nTexture, nPos, Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

Sprite::Sprite(Texture nTexture)
  : Sprite(nTexture, Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

Sprite::Sprite()
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(nullptr),
    isRGBFilter(false)
{
  size.x = 50.0f; size.y = 50.0f;
  buildVAO();
}

Sprite::Sprite(const Sprite& other)
  : Shape(other),
    spriteTexture(new Texture(*other.spriteTexture)),
    isRGBFilter(other.isRGBFilter)
{
  //init une forme vierge
  shapeVBO.init(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
  shapeEBO.init(indices, sizeof(indices));
  buildVAO();
  // copy de la forme
  for(int i = 0; i < 32; i++)
    vertices[i] = other.vertices[i];
  for(int i = 0; i < 6; i++)
    indices[i] = other.indices[i];

  updateVBO();
}

Sprite& Sprite::operator=(const Sprite& other)
{
  if (this != &other){
    Shape::operator=(other);
    
    if (spriteTexture != nullptr){
      delete spriteTexture;
      spriteTexture = new Texture(*other.spriteTexture);
    }
  }
  return *this;
}

Sprite::~Sprite()
{
  delete spriteTexture;
}

void Sprite::buildVAO()
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(vertices)/sizeof(GLfloat)); i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(indices)/sizeof(GLuint)); i++)
    indices[i] = 0;
  // init sprite and texture coordinate ########################################
  // vecteur position normalizé
  Vector2f pTL(-origin.x, -origin.y);
  Vector2f pTR(pTL.x+size.x,pTL.y);
  Vector2f pBR(pTR.x,pTL.y+size.y);
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+pos.x; vertices[1] = pTR.y+pos.y;
  //botton right
  vertices[8] = pBR.x+pos.x; vertices[9] = pBR.y+pos.y;
  //bottom left
  vertices[16] = pBL.x+pos.x; vertices[17] = pBL.y+pos.y;
  //top left
  vertices[24] = pTL.x+pos.x; vertices[25] = pTL.y+pos.y;
 /// color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 32;i+=8){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;vertices[i+5] = alpha;
  }
  //texture coo
  vertices[6] = 1.0f;vertices[7] = 1.0f;vertices[14] = 1.0f;vertices[15] = 0.0f;vertices[22] = 0.0f;vertices[23] = 0.0f;vertices[30] = 0.0f;vertices[31] = 1.0f;
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind();
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 8, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 8, 2);
  shapeVAO.LinkVBO(shapeVBO, 2, 2, 8, 6);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void Sprite::updateVBO()
{
  //  coordinate change ######################################## 
  // vecteur position normalizé
  Vector2f pTL(-origin.x, -origin.y);
  Vector2f pTR(pTL.x+size.x,pTL.y);
  Vector2f pBR(pTR.x,pTL.y+size.y);
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+pos.x; vertices[1] = pTR.y+pos.y;
  //botton right
  vertices[8] = pBR.x+pos.x; vertices[9] = pBR.y+pos.y;
  //bottom left
  vertices[16] = pBL.x+pos.x; vertices[17] = pBL.y+pos.y;
  //top left
  vertices[24] = pTL.x+pos.x; vertices[25] = pTL.y+pos.y;
  
  shapeVBO.update(vertices, sizeof(vertices));
  if (autoUpdateCollision){
    shapeCollisionBox.setPosition(pos);
    shapeCollisionBox.setSize(size);
    shapeCollisionBox.setOrigin(origin);
  }
}

void Sprite::updateVBORGB()
{
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 32;i+=8){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void Sprite::updateVBOAlpha()
{
  for(int i = 0; i < 32;i+=8){
    vertices[i+5] = alpha;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void Sprite::Draw(GLint* renderUniforms) const 
{
  if (!isRGBFilter){
    if(spriteNormalMap != nullptr){
      glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_TEXTURE_NMAP);

      glActiveTexture(GL_TEXTURE1);
      spriteNormalMap->Bind();
    }else{
      glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_TEXTURE);
    }
  }else{
    if(spriteNormalMap != nullptr){
      glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_MIX_NMAP);

      glActiveTexture(GL_TEXTURE1);
      spriteNormalMap->Bind();
    }else{
      glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_MIX);
    }
  }

  //bind texture and vao
  glActiveTexture(GL_TEXTURE0);
  spriteTexture->Bind();
  shapeVAO.Bind();  

  //après avoir bind on dit au shader quelle sampler prend quelle texture 
  glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_TEXTURE], 0);
  glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_NORMAL_MAP], 1);
  
  //draw
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  //unbind all data
  shapeVAO.Unbind();
  spriteTexture->Unbind();
  if(spriteNormalMap != nullptr)
    spriteNormalMap->Unbind();
}

void Sprite::setTexture(const Texture &nTexture)
{
  delete spriteTexture;
  spriteTexture = new Texture(nTexture);
}

Texture* Sprite::getTexture()
{
  return spriteTexture;
}


void Sprite::setNormalMap(const Texture &nNormalMap)
{
  delete spriteNormalMap;
  spriteNormalMap = new Texture(nNormalMap);
}

Texture* Sprite::getNormalMap()
{
  return spriteNormalMap;
}

void Sprite::setRGBFilterState(bool etat)
{
  isRGBFilter = etat;
}

bool Sprite::getRGBFilterState() const
{
  return isRGBFilter;
}

void Sprite::flipVertically()
{
  Vector2f tempCoord(vertices[6], vertices[7]);
  vertices[6] = vertices[30];vertices[7] = vertices[31];
  vertices[30] = tempCoord.x;vertices[31] = tempCoord.y;
  
  tempCoord.x = vertices[14]; tempCoord.y = vertices[15];
  vertices[14] = vertices[22];vertices[15] = vertices[23];
  vertices[22] = tempCoord.x;vertices[23] = tempCoord.y;

  if(autoUpdateCollision)
    shapeCollisionBox.flipVertically();

  updateVBO();
}


void Sprite::flipHorizontally()
{
  Vector2f tempCoord(vertices[6], vertices[7]);
  vertices[6] = vertices[14];vertices[7] = vertices[15];
  vertices[14] = tempCoord.x;vertices[15] = tempCoord.y;
  
  tempCoord.x = vertices[22]; tempCoord.y = vertices[23];
  vertices[22] = vertices[30];vertices[23] = vertices[31];
  vertices[30] = tempCoord.x;vertices[31] = tempCoord.y;
  
  if(autoUpdateCollision)
    shapeCollisionBox.flipHorizontally();
 
  updateVBO();
}

void NoTextureSprite::Draw(GLint* renderUniforms) const 
{
  if (!isRGBFilter)
    glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_TEXTURE);
  else
    glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_MIX);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void NoTextureSprite::DrawAsFrameBuffer() const
{
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
