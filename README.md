# Bbop 2D Library

![GitHub License](https://img.shields.io/github/license/Alexander7474/Bbop-Library)
![GitHub Release](https://img.shields.io/github/v/release/Alexander7474/Bbop-Library?include_prereleases&color=pink)
![GitHub last commit](https://img.shields.io/github/last-commit/Alexander7474/Bbop-Library?link=https%3A%2F%2Fgithub.com%2FAlexander7474%2FBbop-Library%2Fcommits%2Fmain%2F)

Bbop est un projet de librairie graphique utilisant l'api opengl.   
La librairie permet de créer des jeux vidéos 2D ou des applications de bureau.

# Naviguer

[![Installation](https://img.shields.io/badge/Installation-lightgreen?style=for-the-badge)](#installation)   
[![Static Badge](https://img.shields.io/badge/Documentation-lightblue?style=for-the-badge)](https://alexander7474.github.io/bbop-web-docs/)   
[![Static Badge](https://img.shields.io/badge/Exemple_code-lightyellow?style=for-the-badge)](https://alexander7474.github.io/bbop-web-docs/)   
[![Static Badge](https://img.shields.io/badge/Report_Bug-red?style=for-the-badge&logoColor=red)](#report-bug)   

# Installation  

## Librairies externes nécessaires

### ![Static Badge](https://img.shields.io/badge/Debian-Packages-grey?style=for-the-badge&logo=debian&labelColor=D70A53)

```
sudo apt-get install libglew-dev libglfw3-dev libfreetype6-dev 
```

### ![Static Badge](https://img.shields.io/badge/Arch_Linux-Packages-grey?style=for-the-badge&logo=arch-linux&logoColor=fff&labelColor=1793D1) 

(I use arch btw)

```
sudo pacman -S glew glfw freetype2 glm
```

## Compiler et installer bbop

### ![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
make && sudo make install
```

# Main exemple

```
int main()
{
    //creation de la fenêtre glfw
    GLFWwindow * window;
    //initialisation de la lib
    bbopInit(1920,1080,"window name",window);
    //main while loop
    while (!glfwWindowShouldClose(window))
    {
      // clear de la fenêtre en noire
      bbopCleanWindow(window,Vector3i(0,0,0),1.0f));
    
      ///////////////
      // ton code ici
      ///////////////
    
      // vérification des erreurs
      bbopErrorCheck();
      // swap du back buffer avec le front buffer
      glfwSwapBuffer(window);
      // recupération des events glfw
      glfwPollEvents();
    }
    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

# Report Bug

[![Static Badge](https://img.shields.io/badge/Report_issue-github-black?style=for-the-badge&logo=github)](https://github.com/Alexander7474/Bbop-Library/issues)
