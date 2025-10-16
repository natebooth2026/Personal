// UNO: Nate's Version (PRE-ALPHA)
// A Nate Booth Production
// May 24th, 2025-July 30th, 2025
// BUG PATCH: August 1st, 2025

#ifndef MEDIA_HPP
#define MEDIA_HPP

#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <IrrKlang/irrKlang.h>
#include <stdio.h>
using namespace irrklang;

/*
CREDITS:
UNO Cards: https://www.textures-resource.com/fullview/8671/?source=genre
Reverse Arrow (modified with Gimp, coverted to PNG @ https://svgtopng.com/): https://www.svgrepo.com/svg/4502/rotating-arrow-to-the-left
*/

/// TEXTURES
const int MAX_TEX = 64;
const int CARD_BACK = 0;
const int START_OF_WILD = 1;
const int START_OF_P4 = 6;
const int START_OF_RED = 11;
const int START_OF_YELLOW = 24;
const int START_OF_GREEN = 37;
const int START_OF_BLUE = 50;
const int TURN_ARROW = 63;
GLuint texID[MAX_TEX];
char* texName[MAX_TEX] = {
	///CARDS
	(char*)"sprite/cards/!.png", //deck & back of cards

	//WILD
	(char*)"sprite/cards/wild.png",
	(char*)"sprite/cards/rWild.png",
	(char*)"sprite/cards/yWild.png",
	(char*)"sprite/cards/gWild.png",
	(char*)"sprite/cards/bWild.png",

	//+4
	(char*)"sprite/cards/+4.png",
	(char*)"sprite/cards/r+4.png",
	(char*)"sprite/cards/y+4.png",
	(char*)"sprite/cards/g+4.png",
	(char*)"sprite/cards/b+4.png",

	//RED BASIC
	(char*)"sprite/cards/r0.png",
	(char*)"sprite/cards/r1.png",
	(char*)"sprite/cards/r2.png",
	(char*)"sprite/cards/r3.png",
	(char*)"sprite/cards/r4.png",
	(char*)"sprite/cards/r5.png",
	(char*)"sprite/cards/r6.png",
	(char*)"sprite/cards/r7.png",
	(char*)"sprite/cards/r8.png",
	(char*)"sprite/cards/r9.png",
	(char*)"sprite/cards/r+2.png",
	(char*)"sprite/cards/rRev.png",
	(char*)"sprite/cards/rSkip.png",

	//YELLOW BASIC
	(char*)"sprite/cards/y0.png",
	(char*)"sprite/cards/y1.png",
	(char*)"sprite/cards/y2.png",
	(char*)"sprite/cards/y3.png",
	(char*)"sprite/cards/y4.png",
	(char*)"sprite/cards/y5.png",
	(char*)"sprite/cards/y6.png",
	(char*)"sprite/cards/y7.png",
	(char*)"sprite/cards/y8.png",
	(char*)"sprite/cards/y9.png",
	(char*)"sprite/cards/y+2.png",
	(char*)"sprite/cards/yRev.png",
	(char*)"sprite/cards/ySkip.png",

	//GREEN BASIC
	(char*)"sprite/cards/g0.png",
	(char*)"sprite/cards/g1.png",
	(char*)"sprite/cards/g2.png",
	(char*)"sprite/cards/g3.png",
	(char*)"sprite/cards/g4.png",
	(char*)"sprite/cards/g5.png",
	(char*)"sprite/cards/g6.png",
	(char*)"sprite/cards/g7.png",
	(char*)"sprite/cards/g8.png",
	(char*)"sprite/cards/g9.png",
	(char*)"sprite/cards/g+2.png",
	(char*)"sprite/cards/gRev.png",
	(char*)"sprite/cards/gSkip.png",

	//BLUE BASIC
	(char*)"sprite/cards/b0.png",
	(char*)"sprite/cards/b1.png",
	(char*)"sprite/cards/b2.png",
	(char*)"sprite/cards/b3.png",
	(char*)"sprite/cards/b4.png",
	(char*)"sprite/cards/b5.png",
	(char*)"sprite/cards/b6.png",
	(char*)"sprite/cards/b7.png",
	(char*)"sprite/cards/b8.png",
	(char*)"sprite/cards/b9.png",
	(char*)"sprite/cards/b+2.png",
	(char*)"sprite/cards/bRev.png",
	(char*)"sprite/cards/bSkip.png",

	//OTHER
	(char*)"sprite/other/arrow.png"
};
///

/// MEDIA HANDLERS
//sound
ISoundEngine* soundEngine = createIrrKlangDevice();

//loads in textures
void loadTex() {
	glGenTextures(MAX_TEX, texID);
	for (int i = 0; i < MAX_TEX; ++i) {
		BYTE* data; //holds color data read
		int w; //width
		int h; //height

		//grab format
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(texName[i]);
		if (format == FIF_UNKNOWN) {
			printf("File type error for texture at path: %s\n", texName[i]);
			continue;
		}

		//grab raw bitmap
		FIBITMAP* bitmap = FreeImage_Load(format, texName[i], PNG_DEFAULT);
		if (!bitmap) {
			printf("Image load error for image at pat: %s\n", texName[i]);
			continue;
		}

		//colorize bitmap
		FIBITMAP* bitmap2 = FreeImage_ConvertTo32Bits(bitmap);
		FreeImage_Unload(bitmap);

		//finalize
		if (bitmap2) {
			data = FreeImage_GetBits(bitmap2);
			w = FreeImage_GetWidth(bitmap2);
			h = FreeImage_GetHeight(bitmap2);

			for (int j = 0; j < w * h; ++j) {
				BYTE temp = data[j * 4];
				data[j * 4] = data[j * 4 + 2];
				data[j * 4 + 2] = temp;
			}

			printf("Texture loaded from file %s, size %dx%d\n", texName[i], w, h);
			glBindTexture(GL_TEXTURE_2D, texID[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			FreeImage_Unload(bitmap2);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			printf("Texture data grab error from file at path: %s\n", texName[i]);
			continue;
		}
	}
}
///

#endif