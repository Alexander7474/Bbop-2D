/*
 * benchmark.h
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

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "../Graphics.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

bool bbopBenchMark(GLFWwindow *&, Scene &sceneToUse);

#endif // ! BENCHMARK_H
