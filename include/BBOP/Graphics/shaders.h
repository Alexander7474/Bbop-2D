/*
 * shaders.h
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

#ifndef SHADERS_CODE_H
#define SHADERS_CODE_H

/**
* @todo Utiliser des matrices de model, de view et de projection pour le vertex shaders
*
* @todo 1 -> Mettre les shaders dans des fichier .glsl 
* @todo 2 -> Faire des ubershader configurable pour optimiser les transfert de données (quantité) et la vitesse de calcule 
* @todo 3 -> utilisé des matrice de tranformation, view et model pour éviter les calcule côté cpu 
* @todo 4 -> faire un framebuffer pour calculer l'éclairage en une fois
* @todo 5 -> ajout de shadow map 
* @todo 6 -> ajout de normal/light map
*/
extern const char *defaultFragment;
extern const char *defaultVertex;
extern const char *lightFragment;
extern const char *lightVertex;

#endif // ! SHADERS_CODE_H
