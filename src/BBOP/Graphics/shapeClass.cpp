/*
 * shapeClass.cpp
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

#include "../../../include/BBOP/Graphics/shapeClass.h"
#include <GLFW/glfw3.h>

using namespace std;

Shape::Shape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize)
  : shapeVBO(vertices, verticesSize, GL_DYNAMIC_DRAW),
    shapeEBO(indices, indicesSize),
    pos(0.0f, 0.0f),
    size(0.0f, 0.0f),
    origin(0.0f, 0.0f),
    RGB(255,255,255),
    autoUpdateCollision(true),
    rotation(0.0f),
    shapeCollisionBox(pos, origin, size, rotation),
    alpha(1.0f)
{}

Shape::Shape()
  : shapeVBO(),
    shapeEBO(),
    pos(0.0f, 0.0f),
    size(0.0f, 0.0f),
    origin(0.0f, 0.0f),
    RGB(255,255,255),
    autoUpdateCollision(true),
    rotation(0.0f),
    shapeCollisionBox(pos, origin, size, rotation),
    alpha(1.0f)
{}

Shape::~Shape()
{
  shapeVAO.Delete();
  shapeVBO.Delete();
  shapeEBO.Delete();
  //std::cerr << "Shape détruite, EBO:" << shapeEBO.ID << " VBO:" << shapeVBO.ID << " VAO:"  << shapeVAO.ID  << " time:" << glfwGetTime() << std::endl;
}

Shape::Shape(const Shape &other)
  : shapeVAO(),
    shapeVBO(),
    shapeEBO(),
    pos(other.pos),
    size(other.size),
    origin(other.origin),
    RGB(other.RGB),
    autoUpdateCollision(other.autoUpdateCollision),
    rotation(other.rotation),
    shapeCollisionBox(other.shapeCollisionBox),
    alpha(other.alpha)
{
  
}

void Shape::initShape(GLfloat* vertices, GLsizeiptr verticesSize, GLuint* indices, GLsizeiptr indicesSize)
{
  shapeVBO.init(vertices, verticesSize, GL_DYNAMIC_DRAW);
  shapeEBO.init(indices, indicesSize);
}

void Shape::setSize(const Vector2f &nSize)
{
  size = nSize;
  if (autoUpdateCollision){
    shapeCollisionBox.setSize(size);
  }
  updateVBO();
}

void Shape::setSize(float x_, float y_)
{
  size.x = x_; size.y = y_;
  if (autoUpdateCollision){
    shapeCollisionBox.setSize(size);
  }
  updateVBO();
}

void Shape::setPosition(const Vector2f &nPos)
{
  pos = nPos;
  if (autoUpdateCollision){
    shapeCollisionBox.setPosition(pos);
  }
  updateVBO();
}

void Shape::setPosition(float x_, float y_)
{
  pos.x = x_;pos.y = y_;
  if (autoUpdateCollision){
    shapeCollisionBox.setPosition(pos);
  }
  updateVBO();
}

void Shape::setOrigin(const Vector2f &nOrigin)
{
  origin = nOrigin;
  if (autoUpdateCollision){
    shapeCollisionBox.setOrigin(origin);
  }
  updateVBO();
}

void Shape::setOrigin(float x_, float y_)
{
  origin.x = x_; origin.y = y_;
  if (autoUpdateCollision){
    shapeCollisionBox.setOrigin(origin);
  }
  updateVBO();
}

void Shape::setColor(const Vector3i &nRGB)
{
  RGB = nRGB;
  updateVBORGB();
}

void Shape::setColor(int x_, int y_, int z_)
{
  RGB.x = x_;RGB.y = y_;RGB.z = z_;
  updateVBORGB();
}

void Shape::setRotation(float nRotation)
{
  rotation = nRotation;
  if(autoUpdateCollision)
    shapeCollisionBox.setRotation(rotation);
  updateVBO();
}

void Shape::setAlpha(float nAlpha)
{
  alpha = nAlpha;
  updateVBOAlpha();
}

void Shape::move(const Vector2f &vecM)
{
  pos.x += vecM.x; pos.y += vecM.y;
  if(autoUpdateCollision)
    shapeCollisionBox.setPosition(pos);
  updateVBO();
}

void Shape::move(float x_, float y_)
{
  pos.x += x_; pos.y += y_;
  if(autoUpdateCollision)
    shapeCollisionBox.setPosition(pos);
  updateVBO();
}

const Vector2f &Shape::getSize() const
{
  return size;
}

const Vector2f &Shape::getOrigin() const
{
  return origin;
}

const Vector2f &Shape::getPosition() const
{
  return pos;
}

const Vector3i &Shape::getColor() const
{
  return RGB;
}

float Shape::getRotation() const
{
  return rotation;
}

float Shape::getAlpha() const 
{
  return alpha;
}

CollisionBox &Shape::getCollisionBox()
{
  return shapeCollisionBox;
}

void Shape::setAutoUpdateCollision(bool etat)
{
  autoUpdateCollision = etat;
}

RectangleShape::RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha)
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices))
{
  size = nSize;
  pos = nPos;
  RGB = nRGB;
  origin = nOrigin;
  rotation = nRotation;
  alpha = nAlpha;
  shapeCollisionBox.setRotation(rotation);
  shapeCollisionBox.setOrigin(origin);
  shapeCollisionBox.setSize(size);
  shapeCollisionBox.setPosition(pos);
  buildVAO();
}

RectangleShape::RectangleShape(Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin)
  : RectangleShape(nSize, nPos, nRGB, nOrigin, 0.0f, 1.0f)
{}

RectangleShape::RectangleShape(Vector2f nSize, Vector2f nPos)
  : RectangleShape(nSize, nPos, Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

RectangleShape::RectangleShape()
  : RectangleShape(Vector2f(50.0f,50.0f), Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

void RectangleShape::buildVAO()
{
  for(int i = 0; i < 24; i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < 6; i++)
    indices[i] = 0;
  //construtiopn du VAO fontion de la position du rectangle de sa taille et de la taille de la fenetre
  // init coordinate ########################################
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
  vertices[6] = pBR.x+pos.x; vertices[7] = pBR.y+pos.y;
  //bottom left
  vertices[12] = pBL.x+pos.x; vertices[13] = pBL.y+pos.y;
  //top left
  vertices[18] = pTL.x+pos.x; vertices[19] = pTL.y+pos.y;
 
  // color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 24;i+=6){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;vertices[i+5] = alpha;
  }
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind(); 
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 6, 2);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void RectangleShape::Draw(GLint* renderUniforms) const
{
  glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RectangleShape::updateVBO()
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
//top right
  vertices[0] = pTR.x+pos.x; vertices[1] = pTR.y+pos.y;
  //botton right
  vertices[6] = pBR.x+pos.x; vertices[7] = pBR.y+pos.y;
  //bottom left
  vertices[12] = pBL.x+pos.x; vertices[13] = pBL.y+pos.y;
  //top left
  vertices[18] = pTL.x+pos.x; vertices[19] = pTL.y+pos.y;
  shapeVBO.update(vertices, sizeof(vertices));
}

void RectangleShape::updateVBORGB()
{
  // color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 24;i+=6){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void RectangleShape::updateVBOAlpha()
{
  // alpha change ########################################
  for(int i = 0; i < 24;i+=6){
    vertices[i+5] = alpha;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

ConvexShape::ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha)
  : Shape(),
    vertices(new GLfloat[nnPoint*6]),
    indices(new GLuint[(nnPoint-1)*3]),
    nPoint(nnPoint),
    listPoint(new Vector2f[nnPoint])
{
  initShape(vertices, sizeof(GLfloat)*6*nnPoint, indices, sizeof(GLuint)*3*(nnPoint-1));
  for(int i = 0; i < nnPoint; i++)
    listPoint[i] = nlistPoint[i];
  size = nSize;
  pos = nPos;
  RGB = nRGB;
  origin = nOrigin;
  rotation = nRotation;
  alpha = nAlpha;
  buildVAO();
}

ConvexShape::ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin)
  : ConvexShape(nnPoint, nlistPoint, nSize, nPos, nRGB, nOrigin, 0.0f, 1.0f)
{}

ConvexShape::ConvexShape(int nnPoint, Vector2f* nlistPoint, Vector2f nSize, Vector2f nPos)
  : ConvexShape(nnPoint, nlistPoint, nSize, nPos, Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

ConvexShape::ConvexShape(int nnPoint, Vector2f* nlistPoint)
  : ConvexShape(nnPoint, nlistPoint, Vector2f(1.0f,1.0f), Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

ConvexShape::ConvexShape()
  : Shape(),
    vertices(new GLfloat[0]),
    indices(new GLuint[0]),
    nPoint(0),
    listPoint(new Vector2f[0])
{}

ConvexShape::ConvexShape(const ConvexShape& other)
  : Shape(other),
    vertices(new GLfloat[other.nPoint*6]),
    indices(new GLuint[(other.nPoint-1)*3]),
    nPoint(other.nPoint),
    listPoint(new Vector2f[other.nPoint])
{
  for(int i = 0; i < nPoint; i++)
    listPoint[i] = other.listPoint[i];
  buildVAO();
}

ConvexShape& ConvexShape::operator=(const ConvexShape& other)
{
 if (this != &other){
    Shape::operator=(other);

    delete [] vertices;
    delete [] indices;
    delete [] listPoint;
    vertices = new GLfloat[other.nPoint*6];
    indices = new GLuint[(other.nPoint-1)*3];
    nPoint = other.nPoint;
    listPoint = new Vector2f[other.nPoint];
    for(int i = 0; i < nPoint; i++)
      listPoint[i] = other.listPoint[i];
    buildVAO();
  }
  return *this;
}

void ConvexShape::initConvex(int nnPoint, Vector2f* nlistPoint)
{
  delete [] vertices;
  delete [] indices;
  delete [] listPoint;
  vertices = new GLfloat[nnPoint*6];
  indices = new GLuint[(nnPoint-1)*3];
  nPoint = nnPoint;
  listPoint = new Vector2f[nnPoint];
  initShape(vertices, sizeof(GLfloat)*6*nnPoint, indices, sizeof(GLuint)*3*(nnPoint-1));
  for(int i = 0; i < nnPoint; i++)
    listPoint[i] = nlistPoint[i];
  size.x = 1.0f; size.y=1.0f;
  buildVAO();
}

ConvexShape::~ConvexShape()
{
  delete [] vertices;
  delete [] indices;
  delete [] listPoint;
}

void ConvexShape::buildVAO()
{
  for(int i = 0; i < nPoint*6; i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < (nPoint-1)*3; i++)
    indices[i] = 0;
  //construtiopn du VAO fontion de la position du rectangle de sa taille et de la taille de la fenetre
  // init coordinate ########################################
  //valeur des couleurs normalisé
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  //calcule cos et sin pour la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  
  for (int i = 0; i < nPoint; i++){
    Vector2f finalPos(listPoint[i].x*size.x-origin.x, listPoint[i].y*size.y-origin.y);
    finalPos = Vector2f(finalPos.x * cosAngle - finalPos.y*sinAngle,finalPos.x*sinAngle+finalPos.y*cosAngle);
    vertices[i*6] = finalPos.x+pos.x; vertices[i*6+1] = finalPos.y+pos.y;
    vertices[i*6+2] = r;vertices[i*6+3] = g; vertices[i*6+4] = b;vertices[i*6+5] = alpha;
  }

  for (int i = 0; i < nPoint-1; i++){
    if (i != nPoint-2){
      indices[i*3] = 0;indices[i*3+1] = 1+i; indices[i*3+2] = 2+i;
    }else {
      indices[i*3] = 0;indices[i*3+1] = 1+i; indices[i*3+2] = 1;
    }
  }
  shapeVAO.Bind();
  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
  shapeEBO.update(indices, sizeof(GLuint)*3*(nPoint-1));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 6, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 6, 2);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void ConvexShape::updateVBO()
{
  //calcule cos et sin pour la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);

  for (int i = 0; i < nPoint; i++){
    Vector2f finalPos(listPoint[i].x*size.x-origin.x, listPoint[i].y*size.y-origin.y);
    finalPos = Vector2f(finalPos.x * cosAngle - finalPos.y*sinAngle,finalPos.x*sinAngle+finalPos.y*cosAngle);
    vertices[i*6] = finalPos.x+pos.x; vertices[i*6+1] = finalPos.y+pos.y;
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}

void ConvexShape::updateVBORGB()
{
  //valeur des couleurs normalisé
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;

  for (int i = 0; i < nPoint; i++){
    vertices[i*6+2] = r;vertices[i*6+3] = g; vertices[i*6+4] = b;
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}

void ConvexShape::updateVBOAlpha()
{
  for (int i = 0; i < nPoint; i++){
    vertices[i*6+5] = alpha;
  }

  shapeVBO.update(vertices, sizeof(GLfloat)*6*nPoint);
}

void ConvexShape::Draw(GLint* renderUniforms) const
{
  glUniform1i(renderUniforms[BBOP_UNIFORM_ADDR_RENDER_MODE], BBOP_SHADER_MODE_COLOR);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 3*(nPoint-1), GL_UNSIGNED_INT, 0);
}

CircleShape::CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha)
  : ConvexShape(),
    radius(nRadius),
    nPointCircle(nnPoint)
{
  size = nSize;
  pos = nPos;
  RGB = nRGB;
  origin = nOrigin;
  rotation = nRotation;
  alpha = nAlpha;
  buildConvex();
}

CircleShape::CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin)
  : CircleShape(nnPoint, nRadius, nSize, nPos, nRGB, nOrigin, 0.0f, 1.0f)
{}

CircleShape::CircleShape(int nnPoint, float nRadius, Vector2f nSize, Vector2f nPos)
  : CircleShape(nnPoint, nRadius, nSize, nPos, Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

CircleShape::CircleShape(int nnPoint, float nRadius)
  : CircleShape(nnPoint, nRadius, Vector2f(1.0f,1.0f), Vector2f(0.0f,0.0f), Vector3i(255,255,255), Vector2f(0.0f,0.0f), 0.0f, 1.0f)
{}

void CircleShape::buildConvex()
{
  Vector2f lstP[nPointCircle+1];
  lstP[0] = Vector2f(radius,radius);
  float angle_increment = 2 * M_PI / nPointCircle; // Angle entre chaque point
  for (int i = 0; i < nPointCircle; i++) {
    float angle = i * angle_increment;
    float x = radius + radius * cos(angle);
    float y = radius + radius * sin(angle);
    lstP[i+1] = Vector2f(x,y);
  }
  initConvex(nPointCircle+1, lstP);
}

void CircleShape::setRadius(float nRadius)
{
  radius = nRadius;
  buildConvex();
}

float CircleShape::getRadius() const
{
  return radius;
}

void CircleShape::setNPointCircle(int nnPoint)
{
  nPointCircle = nnPoint;
  buildConvex();
}

int CircleShape::getNPointCircle() const
{
  return nPointCircle;
}
