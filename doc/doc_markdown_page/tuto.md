
# Tuto 

Voici une série de tuto sur la plus part des class de la librairie, il décrive le rôle de chaque class mais ne donne pas tous les détails. \n 
La documentation elle pourra répondre à toutes vos questions. \n 

## Info 

Tous les getters de la librairie sont marqués comme const.

## Mise en place 

Premier programme hello world avec Bbop, affichage d'un rectangle blanc. \n

Initialisation de la librairie avec une fenêtre glfw. \n 
```
GLFWwindow *window;
bbopInit(1920,1080,"name",window);
```

Mise en place d'une Scene pour afficher notre premier rectangle. \n
```
Scene scene;
```

Creation d'un rectangle. \n
```
RectangleShape rectangle;
rectangle.setPosition(100.f,100.f); //changement de position 
rectangle.setSize(500.f,500.f); //changement de la taille du rectangle
```

Exemple dans une boucle d'affichage avec une fenêtre glfw. \n
```
int main() {
  
  GLFWwindow * window;
  bbopInit(1920,1080,"name",window);
  
  Scene scene;

  RectangleShape rectangle;
  rectangle.setPosition(100.f, 100.f);
  rectangle.setSize(500.f,500.f);

  while (!glfwWindowShouldClose(window))
  {
    // Nettoyage de la fenêtre
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

    // On 'active' la scene pour donner au shader opengl les variables uniforms
    scene.Use();

    // Affichage du rectangle
    scene.Draw(rectangle);

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
```

## Forme géométrique / Shape

Toutes les formes géométriques hérites de la class mère Shape, elles ont donc en commun la plus part de leurs attributs mais les utilisent de différente manières. \n
Ces attributs sont tous accessible avec des getters et setters. \n

Attributs communs. \n
```
Vector2f position; //position
Vector2f size; //taille
Vector2f origin; //origine
float rotation; //angle de rotation en radians
float alpha; //transparence
Vector3i Color; // Couleur au format rgb
CollisionBox shapeCollisionBox: // boîte de collision
bool autoUpdateCollision; // Si true, la boîte de collision se met à jour automatiquement (true par défault)
```

Toutes les Shape hérites de BbopDrawable, qui est la class mère de tous les objets dessinables de la librairie. \n

### Rectangle / RectangleShape

Le rectangle est la forme la plus simple de la librairie et possède les attributs suivant. \n 
Tous les attributs de la Shape sont utilisés de manière trivial ! \n

Exemple simple de pour créer un rectangle bleu de 100px par 100px \n
```
//création du rectangle 
RectangleShape rect;
rect.setSize(100.f,100.f);
rect.setColor(0,0,255);

//affichage dans la boucle principale avec la scene 
scene.Draw(rect);
```

!!! AVANT TOUS AFFICHAGE IL FAUT SAVOIR UTILISER LA CLASS Scene !!! \n

### Forme Convex / ConvexShape

todo

#### Cercle / CircleShape

todo

#### Et les triangles ?

todo \n

### Sprite

Le Sprite est basiquement un rectangle avec une Texture. \n 

Elle stock cette texture avec un pointeur et le setter associé. \n 
```
Texture *spriteTexture;
sprite.setTexture(Texture nTexture); // !!! l'objet passé en paramètre n'est pas un pointeur !!!
```

Une des grosse différence avec le RectangleShape est que le Sprite gère ```Vector3i Color``` comme un filtre de couleur sur la texture. \n 
Ce filtre peut-être activé avec getter et setter. 
```
sprite.setRGBFilterState(bool etat);
sprite.getRGBFilterState() const;
```

#### Sprite animé

todo

## Scene 

La Scene est l'une des class principale de la librairie, elle sert à afficher les BbopDrawable et configurer le rendue de la lumière. \n

La Scene possède des attributs pour paramètrer la lumière ambiant. \n 
```
floar ambiantLightIntensity; // intensité de la lumière ambiante, avec 1.f la scene affiche les objets telle qu'ils sont.
Vector3i ambiantLightColor; // couleur de la lumière ambiant RGB
```

La Scene possède aussi un pointeur vers une camera pour déterminer le point de vue avec le quel afficher les BbopDrawable. \n
```
Camera *sceneCamera; // par défault nullptr 
```

On peut donc utiliser une camera personnalisé pour afficher des éléments dans notre Scene. \n
```
scene.useCamera(Camera* _cam);
```

Pour déssiner sur une Scene lors d'une frame il faut d'abord "l'utiliser" pour transmettre les infos de la Scene au GPU. \n 
```
scene.Use(); 
```

Après cela on peut dessiner des BbopDrawable. \n 
```
scene.Draw(const BbopDrawable b);
```

Voici un exemple du pipeline complet de rendue avec une Scene. \n 
```
scene.Use();

scene.Draw(const BbopDrawable b);

scene.addLight(Light l); // ajoute une lumière à l'environement de la Scene 

scene.render(); // rend le frame buffer de la scene avec la lumière 
```

La methode  ```render()``` supprime le vecteur de lumière de la scene, il ne faut donc pas oublier d'ajouter les lumières à chaque frames. \n 

## Camera

La camera permet de regarder a des endroit précis dans la Scene.

Elle utilise une position et une scale qui détermine là ou elle regarde et le zoom de celle ci.

Exemple 
```
Camera cam;
cam.setPosition(100.f,100.f); // centre de la camera placé en x:100 y:100 
cam.setScale(0.8);
```

## Collision

todo

## Light

todo

## Map

todo

## Math 

todo 

## Texture

todo
