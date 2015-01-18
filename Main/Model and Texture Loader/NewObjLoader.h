#pragma once

typedef struct {
	float x, y, z, u, v;
	unsigned int color;
} Vertex;

typedef struct {
	int * vIndices, *nIndices, *tcIndices; int vCount;
} Face;

typedef struct _Mesh
{
	Vertex * vertices;
	Vertex * normals;
	Vertex * texCoords;
	Face * faces;
	int noVertices, noNormals, noTexCoords, noFaces;
} Mesh;

class NewObjLoader
{
public:
	NewObjLoader();
	~NewObjLoader();
};

