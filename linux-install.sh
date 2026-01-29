#!/bin/bash

# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

echo -e "${Purple}Welcome to"
cat << "EOF"
   ___    _                _ __              _                      _                _       _                    
  | _ )  | |__     ___    | '_ \    o O O   (_)    _ _      ___    | |_    __ _     | |     | |     ___      _ _  
  | _ \  | '_ \   / _ \   | .__/   o        | |   | ' \    (_-<    |  _|  / _` |    | |     | |    / -_)    | '_| 
  |___/  |_.__/   \___/   |_|__   TS__[O]  _|_|_  |_||_|   /__/_   _\__|  \__,_|   _|_|_   _|_|_   \___|   _|_|_  
_|"""""|_|"""""|_|"""""|_|"""""| {======|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'                                          
EOF

echo_error() {
  echo -e "${Red}ERROR: $1" >&2
  exit -1
}

animate_loading() {
    local text="$1"
    local delay=0.1
    while true; do
        printf "\r$text /"
        sleep $delay
        printf "\r$text -"
        sleep $delay
        printf "\r$text \\"
        sleep $delay
        printf "\r$text |"
        sleep $delay
    done
}

install_package() {
  #creation du process pour animer le texte
  animate_loading "Installing $package " &
  local animation_pid=$!

  #on install le package avec le package manager
  if [[ $package_manager == "dpkg" ]]
  then
    apt install -y $1 &> /dev/null
  elif [[ $package_manager == "rpm" ]]
  then
    dnf install -y $1
  elif [[ $package_manager == "pacman" ]]
  then
    pacman -S --noconfirm $1
  fi

  #on kill l'animation
  kill $animation_pid &> /dev/null
  echo ""

  #Check si le package c'st bien installé
  if [[ $? -ne 0 ]]
  then
    echo_error "Installation failed $1"
  else
    echo -e "${Green}$1 install with succes !"
  fi
}

detect_package() {
  if [[ $package_manager == "dpkg" ]]
  then
    result=$(dpkg -l |grep $1)
  elif [[ $package_manager == "pacman" ]]
  then
    result=$(pacman -Q $1)
  elif [[ $package_manager == "rpm" ]]
  then
    result=$(rpm -q $1)
  fi
  if [[ ! -z "$result" ]] 
  then
    return 0
  else
    return 1
  fi
}

#Vérification des paramètres
if [[ "$#" -ne 0 ]]
then
  echo_error "This script oes not take parameters"
fi
#check si root
if [ `id -u` -ne 0 ]
then
  echo_error "This script need to be root !"
fi

#installation des libs nécessaires
package_manager="not_found"

#list des package a installer
package_list=("libglew-dev" "xorg-dev" "libfreetype6-dev" "libwayland-dev" "libxkbcommon-dev" "wayland-protocols" "libstb-dev" "cmake" "extra-cmake-modules")

#on determine le package manager
if command -v dpkg &> /dev/null
then 
  package_manager="dpkg"
elif command -v rpm &> /dev/null
then 
  package_manager="rpm"
elif command -v pacman &> /dev/null
then 
  package_manager="pacman"
  package_list=("glew" "freetype2")
fi

if [[ $package_manager == "not_found" ]]
then
  echo_error "package manager not found !"
else
  echo -e "${Yellow}package manager found:${Color_Off} $package_manager"
fi

echo -e "${Yellow}Installing necessary packages"
for package in "${package_list[@]}"
do 
  #on cherche le package avec le package manager detecte
  echo -e "${Yellow}Installing: ${Color_Off}$package"
  
  #on install le package si il ne l'est pas
  if detect_package $package
  then
    echo -e "${Green}$package is already installed !"
  else
    install_package $package
  fi
done

echo -e "${Green}Package install done !"

#installation de glfw
echo -e "${Yellow}Installing GLFW${Color_Off}"

#verification de l'install de glfw
install_glfw=0
if [[ -d "/usr/local/include/GLFW" ]] || [[ -f "/usr/local/lib/libglfw3.a" ]]
then
  read -p "GLFW is already installed, do you want to update ?[y,N]: " response
  if [ "$response" != "y" ]
  then
    install_glfw=1
  fi
fi

if [[ $install_glfw -eq 0 ]]
then
  git clone https://github.com/glfw/glfw.git

  #creation du dossier de build
  cd glfw
  mkdir build
  cd build
  cmake ..
  make && sudo make install
  cd ../../ 
  rm -r glfw
  echo -e "${Green}GLFW install done !"
fi

#installation de glm
echo -e "${Yellow}Installing GLM${Color_Off}"

#verification de l'installation de glm
install_glm=0
if [[ -d "/usr/local/include/glm" ]] || [[ -f "/usr/local/lib/libglm.a" ]]
then
  read -p "GLM is already installed, do you want to update ?[y,N]: " response
  if [ "$response" != "y" ]
  then
    install_glm=1
  fi
fi

if [[ $install_glm -eq 0 ]]
then
  git clone https://github.com/g-truc/glm.git

  #creation du dossier de build
  cd glm
  cmake \
      -DGLM_BUILD_TESTS=OFF \
      -DBUILD_SHARED_LIBS=OFF \
      -B build .
  cmake --build build -- all
  cmake --build build -- install

  cd ../ 
  rm -r glm
  echo -e "${Green}GLM install done !"
fi

#installation de ldtk
echo -e "${Yellow}Installing LDtkLoader${Color_Off}"

#installation de ldtkloader
install_ldtk_loader=0
if [[ -d "/usr/local/include/LDtkLoader" ]] || [[ -f "/usr/local/lib/libLDtkLoader.a" ]]
then
  read -p "LDtkLoader is already installed, do you want to update ?[y,N]: " response
  if [ "$response" != "y" ]
  then
    install_ldtk_loader=1
  fi
fi  

if [[ $install_ldtk_loader -eq 0 ]]
then 
  git clone https://github.com/Madour/LDtkLoader.git
  cd LDtkLoader
  mkdir build && cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
  cmake --build . --config Release
  sudo mv lib/libLDtkLoader.a /usr/local/lib/
  sudo mv ../include/LDtkLoader /usr/include/
  cd ../../ 
  rm -rf LDtkLoader 
  echo -e "${Green}LDtkLoader install done !"
fi

#déplacmeent des header de freetype si non fait
if [[ -d "/usr/include/freetype2" ]]
then 
  sudo mv /usr/include/freetype2/freetype /usr/include/  
  sudo mv /usr/include/freetype2/ft2build.h /usr/include/ 
  sudo rmdir /usr/include/freetype2/
fi

#installation de BBOP
echo -e "${Yellow}Installing BBOP${Color_Off}"

#verification de l'installation de BBOP
install_bbop=0
if [[ -d "/usr/local/include/BBOP" ]] || [[ -f "/usr/local/lib/libbbop.a" ]]
then
  read -p "BBOP is already installed, do you want to update ?[y,N]: " response
  if [ "$response" != "y" ]
  then
    install_bbop=1
  fi
fi  

if [[ $install_bbop -eq 0 ]]
then 
  make
  sudo make install 
  echo -e "${Green}BBOP install done !"
fi

echo -e "${Purple}Install finished"
cat << "EOF"
   ___       _      _                    
  /   \   __| |    (_)     ___     ___   
  | - |  / _` |    | |    / _ \   (_-<   
  |_|_|  \__,_|   _|_|_   \___/   /__/_  
_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| 
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-' 
EOF
