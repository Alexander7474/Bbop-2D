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

////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <chrono>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/animatedSpriteClass.h"
#include "include/BBOP/Graphics/bbopGlobal.h"
#include "include/BBOP/Graphics/bbopMathClass.h"
#include "include/BBOP/Graphics/collisionBoxClass.h"
#include "include/BBOP/Graphics/fontsClass.h"
#include "include/BBOP/Graphics/shapeClass.h"


using namespace std;

float fast_rand(float min, float max) {
    static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    seed = (214013 * seed + 2531011); // LCG constants
    return min + (seed >> 16) * (1.0f / 65535.0f) * (max - min); // Scale to [min, max]
}

//tentative de simuler une bougie

int main() {
  
  GLFWwindow * window;
  bbopInit(1920,1080,"name",window);
  
  Scene scene(0.1f, Vector3i(255,255,255));
  Camera cam;

  AnimatedSprite bougie("imgTesting/bougie/sprite_sheet_candle1-sheet.png",Vector2i(5,1),0.1f,0);

  Sprite rock("imgTesting/rock.png");
  rock.setNormalMap(Texture("imgTesting/rock_map.png"));
  rock.setPosition(800.f,400.f);
  rock.setSize(500.f,500.f);
  
  Sprite box("imgTesting/box.png");
  box.setNormalMap(Texture("imgTesting/box_normal.png"));
  box.setPosition(100.f,100.f);
  box.setSize(500.f,500.f);

  bougie.setSize(270.f,270.f);
  bougie.setOrigin(bougie.getSize().x/2.f, 55.f);

  Light light(Vector2f(0.f,0.f), 0.9f, Vector3i(255,255,255),1.5f,3.0f,4.5f); // bougie
  Vector2f maxIntensity(0.9f,1.2f); // intensité max de la bougie
  float variation = 0.10f;

   // Masquer le curseur de la souris
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  // fond 
  RectangleShape rectangle;

  while (!glfwWindowShouldClose(window))
  {
    // Nettoyage de la fenêtre
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);
  
    //taille du fond 
    rectangle.setSize(BBOP_WINDOW_RESOLUTION.x , BBOP_WINDOW_RESOLUTION.y);

    //poistion de la souris pour la light 
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // la bougie suit la souris
    Vector2f mouseWorldPos = cam.camPosToWorldPos(cam.screenPosToCamPos(Vector2f(static_cast<float>(xpos), static_cast<float>(ypos))));
    light.setPosition(mouseWorldPos);
    bougie.setPosition(mouseWorldPos);

    // variation de l'intensité de la bougie 
    light.setIntensity(light.getIntensity() + fast_rand(-variation, variation));
    if(light.getIntensity() > maxIntensity.y)
      light.setIntensity(maxIntensity.y - variation);
    if(light.getIntensity() < maxIntensity.x)
      light.setIntensity(maxIntensity.x + variation);

    // On 'active' la scene pour donner au shader opengl les variables uniforms
    scene.Use();

    //
    bougie.update();

    // Affichage du rectangle
   // scene.Draw(rectangle);

    scene.Draw(rock);
    scene.Draw(box);
    scene.Draw(bougie);

    // ajout de la lumière 
    scene.addLight(light);

    // Faire le rendue du frame buffer de la fenêtre
    scene.render();
    
    // Verfication d'erreur opengl
    bbopErrorCheck();

    // Passage du front buffer pour afficher le rendue opengl sur la fenêtre glfw 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // Suppression de la fenêtre
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
