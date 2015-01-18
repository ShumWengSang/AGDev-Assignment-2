#pragma once
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <vector>
#include "BaseEntity.h"
using namespace std;

struct rect
{
	int x;
	int y;
	int height;
	int width;

	rect(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	rect()
	{

	};
};

class QuadTree1
{
private :


	int MAX_OBJECTS;
	int MAX_LEVELS;

	int level;
	vector<rect> objects;
	rect bounds;
	QuadTree1 *nodes[4];


public:

	QuadTree1(void);
	QuadTree1(int pLevel, rect pBounds);
	~QuadTree1(void);

	void clear();	//clear the quadtree
	void Split();	//split the quadtree
	int GetIndex(rect pRect);	//Determine Location in quadtree -1 means object cannot completely fit within a child node and is part of the parent node

	void insert(BaseEntity theEntity);
	void insert(rect pRect);
	vector<rect> retrive(vector<rect> &returnObjects, rect pRect);

	void DrawQuad();
	void DrawQuadTree(rect * pRect = NULL);

};

