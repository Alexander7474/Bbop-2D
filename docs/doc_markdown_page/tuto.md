---

# Tuto

Ce tuto n'en est qu'une vue d'ensemble pratique.

Convention utilisée dans toute la lib : **tous les getters sont `const`**, les setters ont
souvent deux surcharges (`set(const Vector2f&)` et `set(float, float)`).

[TOC]

## 1. Mise en place du projet

### 1.1 Dépendances

Bbop-2D s'appuie sur OpenGL via GLFW/GLEW, GLM pour les maths matricielles, FreeType pour les
polices et LDtkLoader pour le format de map. Le C++17 est le minimum requis (GLM en a besoin).

```bash
sudo apt-get install libglew-dev libfreetype6-dev
# + GLM, GLFW, LDTKLoader installés séparément
git clone https://github.com/Alexander7474/Bbop-2D.git
cd Bbop-2D
make && sudo make install
```

### 1.2 Le header unique

Pas besoin d'inclure chaque header un par un : `Graphics.h` ré-exporte tout (Scene, Shape,
Sprite, AnimatedSprite, Camera, Light, Texture, Map, CollisionBox, Font/TexteBox, les vecteurs...).

```cpp
#include "BBOP/Graphics.h"
```

### 1.3 Boucle minimale

Trois fonctions globales structurent obligatoirement le cycle de vie : `bbopInit`,
`bbopCleanWindow`, `bbopErrorCheck`. Le reste (swap buffer, poll events) reste du GLFW pur,
Bbop-2D ne le masque pas.

```cpp
int main()
{
    GLFWwindow *window;
    bbopInit(1920, 1080, "demo", window);

    Scene scene; // scene par défaut : lumière ambiante blanche, intensité 1.0

    while (!glfwWindowShouldClose(window))
    {
        bbopCleanWindow(window, Vector3i(0, 0, 0), 1.0f);

        scene.Use();      // envoie les uniforms (camera, lumière ambiante...) au shader
        // ... vos Draw() ici ...
        scene.render();   // calcule l'éclairage final et blit le framebuffer

        bbopErrorCheck();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```

Le pipeline de rendu d'une frame est toujours le même : `Use()` → N×`Draw()` →
(optionnel) `addLight()` → `render()`. `render()` vide la liste de lumières de la `Scene`, il
faut donc la réalimenter à chaque frame si vous voulez un éclairage persistant.

D'autres utilitaires globaux existent dans `bbopFunc.h` :

```cpp
bbopChangeWindowSize(1280, 720);         // redimensionne la fenêtre GLFW
bbopChangeWindowResolution(1280, 720);   // change la résolution logique (BBOP_WINDOW_RESOLUTION)
bbopDebugCollisionBox(box, scene);       // dessine une CollisionBox pour debug (lent, debug only)
```

## 2. Maths : `Vector2`/`Vector3`/`Vector4`

Templates simples sans surcharge d'opérateurs arithmétiques (pas de `+`/`-`/`*` builtin),
juste des structures de données typées avec des alias concrets :

```cpp
Vector2f posF(10.f, 20.f);
Vector2i posI(10, 20);
Vector3i rgb(255, 128, 0);   // utilisé partout pour les couleurs (0-255)
Vector4<double> v4(1.0, 2.0, 3.0, 4.0);

float d = bbopGetDistance(Vector2f(0,0), Vector2f(3,4)); // == 5.f
```

`Vector3i` est la convention couleur de toute la lib (RGB 8 bits), pas de `Vector3f` normalisé
0-1 pour les couleurs.

## 3. `BbopDrawable` et la hiérarchie `Shape`

Tout ce qui peut être passé à `Scene::Draw()` hérite de `BbopDrawable` (interface : une seule
méthode virtuelle pure `Draw(GLint *renderUniforms)`). `Shape` est la classe mère concrète de
toutes les formes géométriques (`RectangleShape`, `ConvexShape`, `CircleShape`, `Sprite`).

Attributs communs exposés par get/set (`position`, `size`, `origin`, `rotation` en radians,
`alpha`, `color` en `Vector3i`, et une `CollisionBox` auto-suivie) :

```cpp
RectangleShape rect;
rect.setSize(100.f, 100.f);
rect.setPosition(50.f, 50.f);
rect.setOrigin(50.f, 50.f);     // pivot de rotation/scale, en coordonnées locales
rect.setColor(0, 128, 255);
rect.setAlpha(0.8f);
rect.setRotation(0.78f);        // radians
rect.move(Vector2f(1.f, 0.f));  // déplacement relatif

scene.Draw(rect);
```

### 3.1 `ConvexShape` / `CircleShape`

`ConvexShape` prend un nombre de points et un tableau de `Vector2f` (polygone arbitraire,
triangulé en éventail).

```cpp
Vector2f pts[3] = { {0,0}, {100,0}, {50,100}}; // triangle
ConvexShape triangle(3, pts);
triangle.setPosition(200.f, 200.f);
```

`CircleShape` hérite de `ConvexShape` et génère un polygone régulier :

```cpp
CircleShape circle(32, 50.f);     // 32 points, rayon 50px (3 points == triangle !)
circle.setColor(255, 0, 0);
circle.setRadius(60.f);           // recalcule la géométrie
```

### 3.2 Collisions : `CollisionBox`

Chaque `Shape` embarque une `CollisionBox` (AABB) qui suit automatiquement sa géométrie tant
que `autoUpdateCollision` est `true` (valeur par défaut). Désactivez ce suivi si vous voulez
gérer une box manuellement (hitbox réduite par rapport au sprite, par ex.).

```cpp
sprite.setAutoUpdateCollision(false);
sprite.getCollisionBox().setOffsetX(Vector2f(10.f, 10.f)); // rétrécit la box de 10px de chaque côté en x
sprite.getCollisionBox().setOffsetY(Vector2f(5.f, 0.f));

if (sprite1.getCollisionBox().check(sprite2.getCollisionBox()))
{
    // AABB simple, ignore la rotation : rapide
}
if (sprite1.getCollisionBox().checkWithRotation(sprite2.getCollisionBox()))
{
    // SAT avec rotation : plus coûteux, à réserver aux cas qui en ont besoin
}
```

`CollisionBox` hérite de `Geometric` (position/origin/size/rotation génériques) et peut être
construite indépendamment d'une `Shape`, ou faire `.follow(const Geometric&)` pour se
recaler sur un objet géométrique quelconque.

⚠️ Seules `RectangleShape` et `Sprite` ont une `CollisionBox` réellement fidèle à leur forme ;
pour `ConvexShape`/`CircleShape` la box reste un simple rectangle englobant.

## 4. Textures et `Sprite`

### 4.1 `Texture`

```cpp
Texture tex("assets/rock.png");          // charge l'image entière (PNG uniquement, testé)
int w = tex.getWidth(), h = tex.getHeight();
```

Chargement avancé via les fonctions libres de `textureClass.h`, utile pour découper une
spritesheet sans passer par `AnimatedSprite` :

```cpp
Image img = bbopLoadImage("assets/sheet.png", 4);                 // RGBA
Image sub = bbopCCutImage(img, 0, 0, 64, 64);                     // crop CPU
Texture frame(sub);
bbopFreeImage(img);                                                // libère le buffer CPU

// ou en un seul appel :
Image partial = bbopLoadPartialImage("assets/sheet.png", 4, 64, 0, 64, 64);

// découpage automatique d'une grille en N textures (gauche -> droite, ligne par ligne)
std::vector<Texture> frames = bbopLoadSpriteSheet("assets/sheet.png", 1 /*rows*/, 5 /*cols*/);
```

### 4.2 `Sprite`

`Sprite` hérite de `Shape` : un rectangle texturé. La couleur (`Vector3i`) devient un **filtre
multiplicatif** sur la texture, activable indépendamment :

```cpp
Sprite player(Texture("assets/player.png"));
player.setPosition(400.f, 300.f);
player.setSize(128.f, 128.f);

player.setColor(255, 0, 0);
player.setRGBFilterState(true);   // teinte rouge appliquée sur la texture
player.setRGBFilterState(false);  // texture affichée sans teinte (défaut)

player.flipHorizontally();
player.flipVertically();
```

Texture remplaçable à chaud, et normal map optionnelle pour l'éclairage dynamique (voir §6) :

```cpp
player.setTexture(Texture("assets/player2.png"));
player.setNormalMap(Texture("assets/player_normal.png"));
Texture *tex = player.getTexture();
```

`NoTextureSprite` est une variante qui ne bind pas de texture automatiquement à `Draw()` :
utile pour des effets manuels ou pour afficher un framebuffer (`scene.DrawFrameBuffer(...)`
l'utilise en interne).

### 4.3 `AnimatedSprite`

Hérite de `Sprite`, gère une spritesheet et l'avancement des frames en fonction du temps.

```cpp
// spritesheet de 1 ligne, 5 colonnes, 0.1s entre chaque frame, pas de frame morte
AnimatedSprite candle("assets/candle_sheet.png", Vector2i(5, 1), 0.1f, 0);
candle.setSize(270.f, 270.f);
candle.setOrigin(candle.getSize().x / 2.f, 55.f);

// dans la boucle :
candle.update();      // avance l'animation, renvoie true quand un cycle est terminé
scene.Draw(candle);
```

`getSpriteSheet()` expose directement le `std::vector<Texture>` si vous voulez piloter
manuellement l'affichage d'une frame précise plutôt que de laisser `update()` faire défiler.

## 5. `Scene` et `Camera`

### 5.1 `Scene`

`Scene` est le point de passage obligé pour tout rendu : elle porte le shader, la lumière
ambiante, la caméra active et le framebuffer (texture couleur + texture normal map) sur lequel
elle dessine avant de calculer l'éclairage final.

```cpp
Scene scene(0.3f, Vector3i(255, 255, 255)); // intensité ambiante 0.3, lumière blanche

scene.setAmbiantLightValue(0.5f);
scene.setAmbiantLightColor(Vector3i(200, 200, 255));
```

### 5.2 `Camera`

```cpp
Camera cam(Vector2f(960.f, 540.f), 1.0f); // centre + scale (1.0 == résolution native)
cam.setPosition(Vector2f(0.f, 0.f));
cam.setScale(0.8f);                       // < 1.0 : dézoom (on voit plus large)
cam.move(Vector2f(5.f, 0.f));

scene.useCamera(&cam);   // toutes les Scene::Draw() suivantes utilisent ce point de vue
// ...
scene.useCamera(nullptr); // retour à la caméra par défaut
```

Conversions souris → monde, utiles pour de l'interaction :

```cpp
double mx, my;
glfwGetCursorPos(window, &mx, &my);
Vector2f worldPos = cam.camPosToWorldPos(
    cam.screenPosToCamPos(Vector2f((float)mx, (float)my)));
```

Culling manuel (à appeler vous-même avant `Draw()` si vous gérez beaucoup d'objets) :

```cpp
if (cam.isInCamView(sprite)) scene.Draw(sprite);
// variante avec une CollisionBox directement :
if (cam.isInCamView(sprite.getCollisionBox())) scene.Draw(sprite);
```

## 6. Lumière dynamique (« Lumop ») et normal maps

L'éclairage est calculé en deux passes : la `Scene` dessine d'abord sur un framebuffer
(couleur + normal map), puis `render()` recompose l'image finale en appliquant la lumière
ambiante et chaque `Light` ajoutée via `addLight()`.

```cpp
Light torch(
    Vector2f(400.f, 300.f), // position
    0.9f,                   // intensité
    Vector3i(255, 180, 80), // couleur
    1.5f, 3.0f, 4.5f);      // atténuation constante / linéaire / quadratique

// dans la boucle, après les Draw() :
scene.addLight(torch);
scene.render();
```

Une `Light` peut être restreinte en cône (spot light) :

```cpp
torch.setOpenAngle(0.6f);      // angle d'ouverture (radians)
torch.setRotationAngle(1.57f); // direction du cône
```

### Normal maps

Toute `Sprite` qui possède une normal map (texture en espace tangent classique, canaux RGB =
XYZ de la normale) en bénéficie automatiquement dès que le pointeur est non-null :

```cpp
Sprite wall("assets/wall.png");
wall.setNormalMap(Texture("assets/wall_normal.png"));
// scene.Draw(wall) suffit, le second framebuffer (normal map) est rempli automatiquement
```

Sans normal map, une `Sprite` est éclairée comme une surface plane orientée vers la caméra.

## 7. Texte : `Font` / `TexteBox`

```cpp
Font arial(32, "fonts/arial.ttf");   // ne charge que les 128 premiers caractères du .ttf

TexteBox label("Score: 0", &arial);
label.setPosition(20.f, 20.f);
label.setColor(Vector3i(255, 255, 255));

// mise à jour dynamique
label.setTexte("Score: 42");
label.buildTexteBox();   // recalcule la géométrie des glyphes après setTexte/setFont

scene.Draw(label);
```

`TexteBox` hérite directement de `BbopDrawable` (pas de `Shape`) : pas de `CollisionBox`,
pas de `setSize` direct, la taille (`getSize()`) est dérivée du texte rendu.

⚠️ Des plantages mémoire sont possibles avec des tableaux statiques de `TexteBox` :
préférez `std::vector<TexteBox>` si vous en gérez plusieurs dynamiquement.

## 8. Cartes LDtk : `Map`

`Map` charge un projet exporté au format [LDtk](https://ldtk.io/) (tuiles, calques de
collision, points de spawn, sprites animés et lumières placées dans l'éditeur).

```cpp
Map level("mapModel/map"); // dossier contenant l'export LDtk

// dans la boucle :
level.update();
level.Draw(scene, cam);

// exploitation des données chargées :
for (auto &box : level.getCollision())
    if (player.getCollisionBox().check(box)) { /* résolution de collision */ }

auto &spawns = level.getSpawnPoints();
if (!spawns.empty()) player.setPosition(spawns[0]);
```

`Map` reste volontairement minimal côté API publique (pas de gestion de calques multiples
configurable depuis le code) : pour un usage avancé, mieux vaut s'inspirer de son
implémentation et composer ses propres `Sprite`/`CollisionBox` à partir du LDtk si vous avez
besoin de plus de contrôle.

## 9. Benchmark intégré

Le module `Performance/benchmark.h` fournit un stress-test rapide de la pipeline de rendu,
pratique pour profiler une `Scene` donnée :

```cpp
#include "BBOP/Performance/benchmark.h"

bbopBenchMark(window, scene); // boucle de stress-test, retourne false en cas d'erreur
```

## 10. Exemple récapitulatif

Assemble la majorité des notions ci-dessus : sprite avec normal map, lumière qui suit la
souris, sprite animé, caméra par défaut pour la conversion de coordonnées.

```cpp
#include "BBOP/Graphics.h"

int main()
{
    GLFWwindow *window;
    bbopInit(1920, 1080, "demo", window);

    Scene scene(0.1f, Vector3i(255, 255, 255));
    Camera cam;

    Sprite rock("assets/rock.png");
    rock.setNormalMap(Texture("assets/rock_normal.png"));
    rock.setPosition(800.f, 400.f);
    rock.setSize(500.f, 500.f);

    AnimatedSprite candle("assets/candle_sheet.png", Vector2i(5, 1), 0.1f, 0);
    candle.setSize(270.f, 270.f);
    candle.setOrigin(candle.getSize().x / 2.f, 55.f);

    Light light(Vector2f(0.f, 0.f), 0.9f, Vector3i(255, 255, 255), 1.5f, 3.0f, 4.5f);

    while (!glfwWindowShouldClose(window))
    {
        bbopCleanWindow(window, Vector3i(0, 0, 0), 1.0f);

        double mx, my;
        glfwGetCursorPos(window, &mx, &my);
        Vector2f worldPos = cam.camPosToWorldPos(
            cam.screenPosToCamPos(Vector2f((float)mx, (float)my)));
        light.setPosition(worldPos);
        candle.setPosition(worldPos);

        scene.Use();
        candle.update();

        scene.Draw(rock);
        scene.Draw(candle);
        scene.addLight(light);
        scene.render();

        bbopErrorCheck();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```

## Pour aller plus loin

- `VAO`/`VBO`/`EBO` (`Graphics/VAO.h`, `VBO.h`, `EBO.h`) et `Shader`/`shaders.h` sont accessibles
  si vous voulez écrire votre propre `BbopDrawable` personnalisé en dessous du niveau `Shape`.
- `Geometric` (`geometricClass.h`) est la classe de base légère à hériter pour décrire un objet
  purement géométrique sans rendu (utilisée par `CollisionBox`).
- Le code source reste la référence ultime : chaque header est court et commenté, n'hésitez pas
  à l'ouvrir directement pour les détails d'implémentation non couverts ici.
