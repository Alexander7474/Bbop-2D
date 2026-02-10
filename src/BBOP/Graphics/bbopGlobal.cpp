/*
 * bbopGlobal.cpp
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

#include "../../../include/BBOP/Graphics/bbopGlobal.h"
#include <string>
#include <vector>

using namespace std;

Vector2i BBOP_WINDOW_SIZE(0, 0);
Vector2i BBOP_WINDOW_RESOLUTION(0, 0);
std::vector<std::string> LOGS;

// Lecture du fichier text et sortie en string
string bbopGetFileData(const char *filename)
{
	ifstream in(filename, ios::binary);
	if (in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}
