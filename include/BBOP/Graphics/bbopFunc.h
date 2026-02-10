/*
 * bbopFunc.h
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

#ifndef BBOP_FUNCTION_H
#define BBOP_FUNCTION_H

#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "collisionBoxClass.h"
#include "sceneClass.h"
#include "shapeClass.h"
#include "textureClass.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

/**
* @brief Fonction d'initialisation de Bbop Library
* 
* @param[in] windowX Taille x de la fenêtre
* @param[in] windowY Taille y de la fenêtre
* @param[in] windowName Nom de la fenêtre
* @param[in,out] window Fenêtre glfw à utiliser
* 
* @note window dois-être un pointeur
* 
* @todo Ajouter le paramétrage du uberShader
*/
int bbopInit(
	int windowX, int windowY, const char *windowName, GLFWwindow *&window);

/**
* @brief Fonction de nettoyage de la fenêtre
* 
* @param[in] window Fenêtre à nettoyer
* @param[in] rgb Couleur de fond de la fenêtre
* @param[in] alpha Transaprence du nettoyage
*/
void bbopCleanWindow(GLFWwindow *&window, Vector3i rgb, float alpha);

/**
* @brief Fonction de verification d'erreur d'opengl
* @details Affiche toutes les erreurs acumulées dans le cache opengl 
*/
void bbopErrorCheck();

/**
* @brief Change la resolution de la fenêtre glfw utilisé dans bbopInit
* 
* @param[in] wWinR Nouvelle resolution de la fenêtre 
* 
* @see bbopInit
*/
void bbopChangeWindowResolution(const Vector2i &nWinR);

/**
* @brief Change la resolution de la fenêtre glfw utilisé dans bbopInit
* 
* @param[in] x_ resolution x 
* @param[in] y_ resolution y
*/
void bbopChangeWindowResolution(int x_, int y_);

/**
* @brief Change la taille de la fenêtre glfw utilisé dans bbopInit
* 
* @param[in] wWinS Nouvelle taille de la fenêtre 
* 
* @see bbopInit
*/
void bbopChangeWindowSize(const Vector2i &nWinS);

/**
* @brief Change la taille de la fenêtre glfw utilisé dans bbopInit
* 
* @param[in] x_ taille x 
* @param[in] y_ taille y
*/
void bbopChangeWindowSize(int x_, int y_);

/**
* @brief Debug de collision en affichant une box
* 
* @param[in] box Boîte de collision à afficher
* @param[in] scene Scene a utiliser pour afficher la box
* 
* @see CollisionBox
* @todo Optimiser cette méthode terriblement lente
*/
void bbopDebugCollisionBox(const CollisionBox &box, Scene &scene);

#endif // !BBOP_FUNCTION_H
