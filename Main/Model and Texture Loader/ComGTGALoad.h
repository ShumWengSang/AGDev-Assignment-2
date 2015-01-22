
#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name




bool LoadTGA(TextureImage *texture, char *filename);			// Loads A TGA File Into Memory