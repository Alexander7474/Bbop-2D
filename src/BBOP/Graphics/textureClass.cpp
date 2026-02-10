/*
 * textureClass.cpp
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

#include "../../../include/BBOP/Graphics/textureClass.h"
#include "../../../include/BBOP/Graphics/bbopGlobal.h"

#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char *textureFileName)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	// définit les options de la texture actuellement liée
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// charge et génère la texture
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(
		textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, data);

	} else {
		std::string message = "BBOP ERROR -> failed to load texture ";
		message += textureFileName;
		LOGS.push_back(message);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Image &textureImage)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	// définit les options de la texture actuellement liée
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// charge et génère la texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width,
		textureImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		textureImage.data);
	width = textureImage.width;
	height = textureImage.height;
	nrChannels = textureImage.nrChannels;
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Texture &other)
    : ID(other.ID), width(other.width), height(other.height),
      nrChannels(other.nrChannels)
{
}

int Texture::getWidth() const { return width; }

int Texture::getHeight() const { return height; }

void Texture::Bind() const { glBindTexture(GL_TEXTURE_2D, ID); }

void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }

Image bbopLoadImage(const char *filename, int nrChannels)
{
	Image toLoad;
	stbi_set_flip_vertically_on_load(true);
	toLoad.data = stbi_load(filename, &toLoad.width, &toLoad.height,
		&toLoad.nrChannels, nrChannels);
	if (toLoad.data) {
		return toLoad;
	} else {
		std::string message = "BBOP ERROR -> failed to load image ";
		message += filename;
		LOGS.push_back(message);
		return toLoad;
	}
}

Image bbopCCutImage(const Image &toCC, int x, int y, int width, int height)
{
	Image result;
	if (x + width > toCC.width || y + height > toCC.height) {
		std::string message = "BBOP ERROR -> failed to cut image";
		LOGS.push_back(message);
		result.data = nullptr;
		return result;
	}

	result.data = (unsigned char *)malloc(width * height * toCC.nrChannels);
	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < width; ++i) {
			for (int k = 0; k < toCC.nrChannels; ++k) {
				result.data[(j * width + i) * toCC.nrChannels +
					k] =
					toCC.data[((toCC.height - y - height +
							   j) * toCC.width +
							  (x + i)) *
							toCC.nrChannels +
						k];
			}
		}
	}
	result.width = width;
	result.height = height;
	result.nrChannels = toCC.nrChannels;

	return result;
}

Image bbopLoadPartialImage(const char *filename, int nrChannels, int x, int y,
	int width, int height)
{
	Image notCC = bbopLoadImage(filename, nrChannels);
	Image cuted = bbopCCutImage(notCC, x, y, width, height);
	bbopFreeImage(notCC);
	return cuted;
}

std::vector<Texture> bbopLoadSpriteSheet(
	const char *spriteSheetPath, int rows, int columns)
{
	std::vector<Texture> vecSheet;
	Image imgSheet = bbopLoadImage(spriteSheetPath, STBI_rgb_alpha);

	const unsigned int rowSize = imgSheet.height / rows;
	const unsigned int columnsSize = imgSheet.width / columns;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Image spr = bbopCCutImage(imgSheet, j * columnsSize,
				i * rowSize, columnsSize - 1, rowSize - 1);
			Texture sprTexture(spr);
			vecSheet.push_back(sprTexture);
			bbopFreeImage(spr);
		}
	}

	bbopFreeImage(imgSheet);

	return vecSheet;
}

void bbopFreeImage(Image &image) { stbi_image_free(image.data); }
