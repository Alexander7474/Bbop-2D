
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

La class AnimatedSprite permet de créer un sprite avec une sprite sheet. \n 
Elle va animé ce Sprite automatiquement en fonction de la durée entre chaque frame. \n

Exemple: \n 
```
AnimatedSprite anim("chemin/vers/spritesheet", Vector2i(ligne,colonne), tps_entre_chaque_frame, frame_morte);

anim.update(); //mise a jour de l'anim dans la boucle principale

scene.Draw(anim); //affichage du sprite
```

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

La camera permet de regarder a des endroit précis dans la Scene. \n

Elle utilise une position et une scale qui détermine là ou elle regarde et le zoom de celle ci. \n

Exemple \n
```
Camera cam;
cam.setPosition(100.f,100.f); // centre de la camera placé en x:100 y:100 
cam.setScale(0.8); //scale de cam réduit donc elle zoom
```

## Collision

Toute les shapes possède une instance de CollisionBox qui suit automatiquement les dimensions de la shape.\n
!!! Attenetion, la boîte de collision est rectangulaire, elle n'est donc pas représentative des Shape autre que RectangleShape et Sprite. \n 
Il, n'y à pas encore de gestion des collision circulaire,triangulaire et convex, il faut donc l'implémenter vous même (faite un fork svppp) !!! \n

On peut annuler ce suivi avec ce setter: \n 
```
shape.setAutoUpdateCollisionBox(bool etat);
```

On peut récupérer la CollisionBox d'une Shape pour s'en servir dans la gestion des collision: \n 
```
shape.getCollisionBox(); // recup de la collision box

// test de la collision en deux sprite 
if(sprite1.getCollisionBox().check(sprite2.getCollisionBox()))
{
  //do something
}
```

## Lumop

Bbop2D intègre une gestion de la lumière (Lumop) \n

Les reflets de la lumière dans la scène sont calculer lors d'une deuxième passe de rendue sur le frame buffer de la scene avec un shader personnalié. \n

### Light 

La class Light est un simple lumière à 360°. \n
Elle possède les getters et setters pour changer tous ces attributs. \n

Exemple: \n 
```
//créer un light 
Light light(Vector2f(x,y), intensité, Vector3i(R,G,B), atténuation_constante, atténuation_linéaire, atténuation_quadratique);

//dans la boucle d'affichage 
scene.addLight(light);
```

La light va venir émettre de la lumière en plus de l'éclaire ambiant de la scene, cela permet un éclairage dynamique, personnalisé et plus détaillé. \n 

### Light directionnel

La light possède deux attribut pour la diriger. \n 

```
float openAngle; // angle d'ouverture de la lumière 
float rotationAngle; // angle de rotation de la lumière 
```

### Normal Map

Lumop intégre la gestion de normal map sur les Sprite. \n 
Une normal map permet un éclairage dynamique d'une texture pour donner l'impression de relief. \n

Un Sprite peut se voire attribué une Texture pour représenter sa normal Map. \n 
```
sprite.setNormalMap(const Texturea& normalMap); // alloue dynamiquement un nouvelle espace mem vers la texture opengl
```

La scene créé un deuxième frame buffer qui contient les normals maps à utiliser lors du rendue final de la lumière. \n

## Map

todo

## Math 

Bbop contient sa propre gestion des vecteurs.\n

Tous les transfert e point ou de couleur se font à l'origine par le passage d'un vecteur. Toute les méthode n'intégre pas un passage a plusieur paramètre pour faire passer un vecteur.\n

## Texture

La class Texture permet la creation et l'utilisation simplifé de texture openGL. \n
Elle est utilisé par Sprite. \n

Exemple: \n
```
Texture texture("chemin/vers/la/texture");

texture.Bind(); //bind de la texture dans le shader opengl 
// après avoir bind manuellement une texture, on peut par exemple utiliser un NoTextureSprite 
```
