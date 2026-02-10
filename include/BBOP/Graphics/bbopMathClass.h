/*
 * bbopMathClass.h
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

#ifndef MATH_CLASS_H
#define MATH_CLASS_H

#include <cmath>

template <typename T>
/**
* @class Vector2
* @brief Stock deux valeurs
* @details Cette class est parent de tous les Vector2# (Vector2d, Vector2f, Vector2i) et peut être initialisé avec un type choisi
* 
* @todo Gérer les constructeur par copy d'une bonne manière
*/
class Vector2
{
      public:
	Vector2();
	Vector2(T x_, T y_);
	Vector2(const Vector2<T> &other);

	T x;
	T y;
};

class Vector2i : public Vector2<int>
{
      public:
	Vector2i();
	Vector2i(int x_, int y_);
	Vector2i(const Vector2i &other);
};

class Vector2f : public Vector2<float>
{
      public:
	Vector2f();
	Vector2f(float x_, float y_);
	Vector2f(const Vector2f &other);
};

class Vector2d : public Vector2<double>
{
      public:
	Vector2d();
	Vector2d(double x_, double y_);
	Vector2d(const Vector2d &other);
};

template <typename T>
/**
* @class Vector3
* @brief Stock trois valeurs
* @details Cette class est parent de tous les Vector3# (Vector3d, Vector3f, Vector3i) et peut être initialisé avec un type choisi
*/
class Vector3
{
      public:
	Vector3();
	Vector3(T x_, T y_, T z_);

	T x;
	T y;
	T z;
};

class Vector3i : public Vector3<int>
{
      public:
	Vector3i();
	Vector3i(int x_, int y_, int z_);
};

class Vector3f : public Vector3<float>
{
      public:
	Vector3f();
	Vector3f(float x_, float y_, float z_);
};

class Vector3d : public Vector3<double>
{
      public:
	Vector3d();
	Vector3d(double x_, double y_, double z_);
};

template <typename T>
/**
* @class Vector4
* @brief Stock quatre valeurs
* @details Cette class est initialisé avec un type choisi
*/
class Vector4
{
      public:
	Vector4();
	Vector4(T x_, T y_, T z_, T w_);

	T x;
	T y;
	T z;
	T w;
};

/**
* @brief Renvoie la distance entre deux point
* 
* @param[in] a point A 
* @param[in] b point B 
* @return float Disctance entre a et b
*/
float bbopGetDistance(Vector2f a, Vector2f b);

#endif // ! MATH_CLASS_H
