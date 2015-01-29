#pragma once
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <vector>
#include "BaseEntity.h"
#include "tgaLoader.h"
#include "Frustum.h"

using namespace std;

struct Quadrant
{
	bool quad[4];
	Quadrant()
	{
		for (int i = 0; i < 4; i++)
		{
			quad[i] = false;
		}
	}
};

struct rect
{
	int x;
	int y;
	int height;
	int width;
	BaseEntity * Pointer;

	rect(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	rect(int x, int y, int width, int height, BaseEntity * theEntity)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->Pointer = theEntity;
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
	int GetPtQuadrant(float x, float y);
	QuadTree1(void);
	QuadTree1(int pLevel, rect pBounds);
	~QuadTree1(void);

	void clear();	//clear the quadtree
	void Split();	//split the quadtree
	Quadrant GetIndex(rect pRect);	//Determine Location in quadtree -1 means object cannot completely fit within a child node and is part of the parent node

	void insert(BaseEntity * theEntity);
	void insert(rect pRect);
	vector<rect> retrive(vector<rect> &returnObjects, rect pRect);

	void DrawQuad(CFrustum *theFrustum = NULL);
	void DrawQuadTree(CFrustum *theFrustum, rect * pRect = NULL);
	void DrawQuadTree( rect * pRect = NULL);

};

