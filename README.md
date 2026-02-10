# Bbop-2D

![GitHub License](https://img.shields.io/github/license/Alexander7474/Bbop-Library)
![GitHub Release](https://img.shields.io/github/v/release/Alexander7474/Bbop-Library?include_prereleases&color=pink)
![GitHub last commit](https://img.shields.io/github/last-commit/Alexander7474/Bbop-Library?link=https%3A%2F%2Fgithub.com%2FAlexander7474%2FBbop-Library%2Fcommits%2Fmain%2F)

Bbop-2D is a graphics library based on [OpenGL](https://www.opengl.org/), specifically designed for **2D game development**.  
It stands out with its support for **lighting and normal maps**, enabling the creation of visually rich and immersive environments, even in a 2D context.

[Installation](#installation)   
[Features](#features)  
[Documentation](https://github.com/Alexander7474/Bbop-2D-Documentation)  
[Tutorials](https://alexander7474.github.io/bbop-web-docs/md_doc_2doc__markdown__page_2tuto.html)  
[Report Issue](https://github.com/Alexander7474/Bbop-Library/issues)  
[Contribute](#contribute)  

## Installation  

### External Libraries

```
sudo apt-get install libglew-dev libfreetype6-dev 
```

Install [GLM](https://github.com/g-truc/glm), [GLFW](https://github.com/glfw/glfw), and [LDTKLoader](https://github.com/Madour/LDtkLoader).

### Install Bbop

Bbop-2D require at least a C++17 compiler. Older complier will not work due to GLM.

```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
make && sudo make install
```

### Simple loop example

This is a basic loop with the mandatory functions you need to use the library.

```
int main()
{
    GLFWwindow * window;
    bbopInit(1920,1080,"window name",window);
    while (!glfwWindowShouldClose(window))
    {
      bbopCleanWindow(window,Vector3i(0,0,0),1.0f));
    
      ///////////////
      // your code
      ///////////////
    
      bbopErrorCheck();
      glfwSwapBuffer(window);
      glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

## Features

A non-exhaustive list of features:

- Sprite.
- Geometric Shape (Rectangle, Circle, Convex, Triangle...).
- Basic CollisionBox.
- Light and NormalMap for light reflexion.
- Camera.

## Contributing

We welcome contributions! If you want to help improve Bbop-2D, feel free to submit a [pull request](https://github.com/Alexander7474/Bbop-2D/pulls).  

Please make sure to **follow the project’s coding style**. You can easily format your code using:  

- The `format_code.sh` script in the root of the repository.  
- Or directly `clang-format` command with `.clang-format` file in te root of the repository.  

Following the style helps keep the code clean and consistent for everyone.
