#include "Texture2D.h"
#include <iostream>
#include <fstream>

using namespace std;

Texture2D::Texture2D()
{	
	_ID = NULL;
	_height = NULL;
	_width = NULL;

}

bool Texture2D::LoadRAW(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;

	_width = width;
	_height = height;

	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file! " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //find end of file
	fileSize = (int)inFile.tellg();// end of file position gives file size
	tempTextureData = new char[fileSize]; //char array to store texture data
	inFile.seekg(0, ios::beg); // find beginning of file
	inFile.read(tempTextureData, fileSize); // read all lines of file and store in tempTextureData

	inFile.close(); //close file

	cout << path << " loaded." << endl;

	glGenTextures(1, &_ID); //Get texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); // bind texture to ID

	//Build Textures
	/*glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData;

	return true;
}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}