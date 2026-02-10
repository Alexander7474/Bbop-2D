/*
 * textureClass.h
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

#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "bbopMathClass.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

/**
* @brief Stock une image 
*
* @note Peut être utiliser avec les fonctions de chargements d'image personnalisées pour être passé en paramètre au constructeur de Texture 
* @see Texture bbopLoadImagePartial bbopLoadSpriteSheet
*
* @todo Faire de cette struct une class pour ajouter ddes méthode de moification des Images
*/
struct Image {
	int width;	     //<! Largeur de l'image
	int height;	     //<! Hauteur de l'image
	int nrChannels;	     //<! Nombre de channels de couleur de l'image
	unsigned char *data; //<! Données de l'image
};

/**
* @class Texture
* @brief Contient une texture qui peut être utilisé dans un sprite
* 
* @attention La class texture à été testé uniqument sur des images png 
* @see Sprite 
*
* @todo Vérifier la possibilité de gérer plusieur format d'image comme jpg, jpeg, ou gif ext...
*/
class Texture
{
      public:
	/**
	* @brief Constructeur par défault de la class Texture 
	* @details Charge l'image en entier
	*
	* @param[in] textureFileName Chemin d'accès vers la texture
	*
	* @note Utiliser les fontions de chargement d'image et le deuxième constructeur pour une texture plus permissive 
	* @attention Uniquement des fichier png 
	*/
	Texture(const char *textureFileName);

	/**
	* @brief Constructeur de la texure a partir d'une image déjà chargé
	*
	* @param[in] Image image à utiliser dans la texture
	*
	* @attention Utiliser les fonctions de chargement d'image comme bbopLoadImagePartial
	*/
	Texture(const Image &textureImage);

	/**
	* @brief constructeur par copie de texture 
	*
	* @param other autre texture 
	*/
	Texture(const Texture &other);

	/**
	* @brief Permet de bin la texture a opengl avant de Draw
	*
	* @note A utiliser en général avec NoTextureSprite
	*
	* @see NoTextureSprite
	*/
	void Bind() const;

	/**
	* @brief Détache la texture d'opengl
	*/
	void Unbind() const;

	/**
	* @brief Supprime la texture d'opengl
	*/
	void Delete();

	/**
	* @brief Renvoie la larguer de la Texture 
	*
	* @return width largeur
	*/
	int getWidth() const;

	/**
	* @brief Renvoie la hauteur de la Texture 
	*
	* @return height hauteur
	*/
	int getHeight() const;

      private:
	GLuint ID;		       //<! ID de la texture avec opengl
	int width, height, nrChannels; //<! info sur la texture
};

/**
* @brief Load une image
*/
Image bbopLoadImage(const char *filename, int nrChannels);

/**
* @brief Copy et coupe une image
*/
Image bbopCCutImage(const Image &toCC, int x, int y, int width, int height);

/**
* @brief Charge de manière partiel une image 
*
* @param[in] filename Chemin d'acès vers l'image 
* @param[in] nrChannels Nombre de canaux de couleurs de l'image 
* @param[in] x Point x de départ du chargement 
* @param[in] y Poitn y de départ du chargement 
* @param[in] Nombre de pixel(s) de large à chargé 
* @param[in] Nombre de pixel(s) de haut à chargé 
* @return Image image chargé prête à être utilsé 
*
* @see Texture Image
*/
Image bbopLoadPartialImage(const char *filename, int nrChannels, int x, int y,
	int width, int height);

/**
* @brief Charge une sprite sheet dans un vector de Texture
*
* @param[in] rows Nombre de lignes
* @param[in] columns Nombre de colonnes 
* @param[in] spriteSheetPath Chemin d'accès vers la sprite sheet
* @return std::vector<Texture> Vector de texture avec les sprites chargé de droite à gauche
*
* @note À utiliser pour faire des animations plus facilement
*/
std::vector<Texture> bbopLoadSpriteSheet(
	const char *spriteSheetPath, int rows, int columns);

/**
* Vide le tablea ude données d'une Image 
*
* @param[in] image image à vider 
*/
void bbopFreeImage(Image &image);

#endif // !TEXTURE_CLASS_H
