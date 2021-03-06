#include "QuadTree.h"


QuadTree1::QuadTree1(void)
{
	MAX_OBJECTS = 1;
	MAX_LEVELS = 10;
}

QuadTree1::QuadTree1(int pLevel, rect pBounds)
{
	level = pLevel;
	bounds = pBounds;
	for (int i = 0; i < 4; i++)
		nodes[i] = NULL;
	MAX_OBJECTS = 5;
	MAX_LEVELS = 10;
}

QuadTree1::~QuadTree1(void)
{
	if (level == MAX_LEVELS)
		return;
	for (int i = 0; i < 4; i++)
		if (nodes[i] != NULL)
			nodes[i] = NULL;
}

void QuadTree1::clear()
{
	if (level == MAX_LEVELS)
	{
		objects.clear();
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		if (nodes[i] != NULL)
		{
			nodes[i]->clear();
			nodes[i] = NULL;
		}
	}
	if (!objects.empty())
	{
		objects.clear();
	}
}

void QuadTree1::Split()
{
	float subWidth = (float)(bounds.width * 0.5);
	float subHeight = (float)(bounds.height * 0.5);
	float x = (float)bounds.x;
	float y = (float)bounds.y;

	nodes[0] =  new QuadTree1(level+1, rect(x + subWidth, y, subWidth, subHeight));
	nodes[1] =  new QuadTree1(level+1,  rect(x, y, subWidth, subHeight));
	nodes[2] =  new QuadTree1(level+1, rect(x, y + subHeight, subWidth, subHeight));
	nodes[3] =  new QuadTree1(level+1,  rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

Quadrant QuadTree1::GetIndex(rect pRect)
{
	Quadrant index;
	double verticalMidpoint = bounds.x + (bounds.width / 2);
	double horizontalMidpoint = bounds.y + (bounds.height / 2);

	float BottomLeftQuad = GetPtQuadrant(pRect.x, pRect.y);
	float TopRightQuad = GetPtQuadrant(pRect.x + pRect.width, pRect.y + pRect.height);


	for (int i = 0; i < 4; i++)
	{
		if (BottomLeftQuad == i)
		{
			index.quad[i] = true;
		}
		if (TopRightQuad == i)
		{
			index.quad[i] = true;
		}
	}

	//Check if the poitns are in opposite quads. IF they are, all four of them should have points.
	if ((int)(BottomLeftQuad + TopRightQuad) % 2 == 0 && (BottomLeftQuad != TopRightQuad))
	{
		for (int i = 0; i < 4; i ++)
			index.quad[i] = true;
	}

	return index;
	//// Object can completely fit within the top quadrants
	//bool topQuadrant = (pRect.y < horizontalMidpoint && pRect.y + pRect.height < horizontalMidpoint);
	//// Object can completely fit within the bottom quadrants
	//bool bottomQuadrant = (pRect.y > horizontalMidpoint);

	//// Object can completely fit within the left quadrants
	//if (pRect.x < verticalMidpoint && pRect.x + pRect.width < verticalMidpoint) {
	//	if (topQuadrant) {
	//		index = 1;
	//	}
	//	else if (bottomQuadrant) {
	//		index = 2;
	//	}
	//}
	//// Object can completely fit within the right quadrants
	//else if (pRect.x > verticalMidpoint) {
	//	if (topQuadrant) {
	//		index = 0;
	//	}
	//	else if (bottomQuadrant) {
	//		index = 3;
	//	}
	//}
	////Basically cut two lines in a cross and get the index value of which rect it is act.
	//return index;
}

int QuadTree1::GetPtQuadrant(float x, float y)
{
	int index = -1;
	double verticalMidpoint = bounds.x + (bounds.width / 2);
	double horizontalMidpoint = bounds.y + (bounds.height / 2);

	// Object can completely fit within the top quadrants
	bool topQuadrant = (y < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (y > horizontalMidpoint);

	// Object can completely fit within the left quadrants
	if (x < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (x > verticalMidpoint) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}
	//Basically cut two lines in a cross and get the index value of which rect it is act.
	return index;
}

void QuadTree1::insert(BaseEntity * theEntity)
{
	float x = theEntity->GetTopLeft().x;
	float z = theEntity->GetBottomRight().z;
	float width = theEntity->GetBottomRight().x - theEntity->GetTopLeft().x;
	float height = theEntity->GetTopLeft().z - theEntity->GetBottomRight().z;

	rect InsertRect(x,z,width,height,theEntity);

	insert(InsertRect);
}

void QuadTree1::insert(rect pRect)
{
	if (nodes[0] != NULL)
	{
		Quadrant index = GetIndex(pRect);

		for (int i = 0; i < 4; i++)
		{
			if (index.quad[i])
			{
				nodes[i]->insert(pRect);
			}
		}
		return;
	}
	//The method first determines whether the node has any child nodes and tries to add the object there.


	objects.push_back(pRect);
	//If there are no child nodes or the object doesn�t fit in a child node, it adds the object to the current node.

	if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
	{
		if (nodes[0] == NULL)
		{
			Split();
		}

		vector<rect>::iterator i = objects.begin();
		int counter = 0;
		for(i = objects.begin(), counter = 0; i != objects.end();counter++)
		{
			Quadrant index = GetIndex(objects.at(counter));
			for (int a = 0; a < 4; a++)
			{
				if (index.quad[a])
				{
					nodes[a]->insert(objects.at(counter));
				}
			}
			i = objects.erase(i);
			counter--;
		}
	}
	//Once the object is added, it determines whether the node needs to split by checking if the current number of objects exceeds the max allowed objects.
	//Splitting will cause the node to insert any object that can fit in a child node to be added to the child node; otherwise the object will stay in the parent node.
}

vector<rect> QuadTree1::retrive(vector<rect> &returnObjects, rect pRect)
{
	//int index = GetIndex(pRect);
	//if (index != -1 && nodes[0] != NULL)
	//{
	//	nodes[index]->retrive(returnObjects, pRect);
	//}

	//returnObjects.insert(returnObjects.end(),objects.begin(),objects.end());

	return returnObjects;
}

void QuadTree1::DrawQuad(int res, CCamera *theCamera)
{

	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(this->bounds.x, 5, this->bounds.y);
	glVertex3f(this->bounds.x, 5, this->bounds.y + this->bounds.height);
	glVertex3f(this->bounds.x + this->bounds.width, 5, this->bounds.y + this->bounds.height);
	glVertex3f(this->bounds.x + this->bounds.width, 5, this->bounds.y);
	glVertex3f(this->bounds.x, 5, this->bounds.y);
	glEnd();

	if(res == 0)
	{
		glColor3f(1, 0, 0);
	}
	else if(res == 1)
	{
		glColor3f(0,1,0);
	}
	else if(res == 2)
	{
		glColor3f(0,0,1);
	}
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(this->bounds.x, 0, this->bounds.y);
	glVertex3f(this->bounds.x, 0, this->bounds.y + this->bounds.height);
	glVertex3f(this->bounds.x + this->bounds.width, 0, this->bounds.y + this->bounds.height);
	glVertex3f(this->bounds.x + this->bounds.width, 0, this->bounds.y);
	glEnd();
	glPopMatrix();
	glColor3f(1,1,1);


	for (auto iter = this->objects.begin(); iter != this->objects.end(); iter++)
	{
		if (iter->Pointer != NULL)
		{
			if (theCamera != NULL)
			{
				if (theCamera->theFrustum.ContainmentCheck(iter->Pointer->GetTopLeft(),iter->Pointer->GetBottomRight())
					/*|| ((theCamera->Position() - iter->Pointer->getPosition()).GetMagnitude() < 10)*/)
				{
					//iter->Pointer->glRenderObject(res);
				}
			}
			else
			{
				//iter->Pointer->glRenderObject(3);
			}
		}
	}
}

void QuadTree1::DrawQuadTree(rect * pRect)
{
	//int index = GetIndex(pRect);
	if (pRect == NULL)
	{
		pRect = &bounds;
		DrawQuad(3);
	}
	for (int i = 0; i < 4; i++)
	{
		if (this->nodes[i] != NULL)
		{
			nodes[i]->DrawQuadTree();
		}
	}
}

void QuadTree1::DrawQuadTree(CCamera *theCamera, int res, rect * pRect)
{
	if (pRect == NULL)
	{
		FirstPass = false;
		pRect = &bounds;
		DrawQuad(res, theCamera);
	}
	for (int i = 0; i < 4; i++)
	{
		if (this->nodes[i] != NULL)
		{
			nodes[i]->DrawQuadTree(theCamera, res);
		}
	}
}

void QuadTree1::Draw(CCamera * theCamera)
{
	//DrawQuadTree(theCamera);
	for (int i = 0; i < 4; i ++)
	{
		double verticalMidpoint = nodes[i]->bounds.x + (nodes[i]->bounds.width / 2);
		double horizontalMidpoint = nodes[i]->bounds.y + (nodes[i]->bounds.height / 2);
		CVector3 camPos(theCamera->Position().x, 0, theCamera->Position().z);
		CVector3 rectPos(verticalMidpoint, 0, horizontalMidpoint);

		//Four cornors of quad.
		//	glVertex3f(this->bounds.x, 0, this->bounds.y);
	//glVertex3f(this->bounds.x, 0, this->bounds.y + this->bounds.height);
	//glVertex3f(this->bounds.x + this->bounds.width, 0, this->bounds.y + this->bounds.height);
	//glVertex3f(this->bounds.x + this->bounds.width, 0, this->bounds.y);
		CVector3 topright (nodes[i]->bounds.x + nodes[i]->bounds.width, 0 , nodes[i]->bounds.y + nodes[i]->bounds.height);
		CVector3 bottomleft(nodes[i]->bounds.x , 0 , nodes[i]->bounds.y);

		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(1,0,1);
		glLineWidth(10);
		glVertex3f(verticalMidpoint, 0, horizontalMidpoint);
		glVertex3f(verticalMidpoint, 100, horizontalMidpoint);
		glLineWidth(1);
		glColor3f(1,1,1);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINES);
		glColor3f(1,0,1);
		glLineWidth(10);
		glVertex3f(nodes[i]->bounds.x + nodes[i]->bounds.width, 0, nodes[i]->bounds.y + nodes[i]->bounds.height);
		glVertex3f(nodes[i]->bounds.x + nodes[i]->bounds.width, 100, nodes[i]->bounds.y + nodes[i]->bounds.height);
		glLineWidth(1);
		glColor3f(1,1,1);
		glEnd();
		glPopMatrix();

		float distance = (camPos - rectPos).GetMagnitude();
		if (distance < 30)
		{
			nodes[i]->DrawQuadTree(theCamera,0);
		}
		else if (distance < 60)
		{
			nodes[i]->DrawQuadTree(theCamera,1);
		}
		else
		{
			nodes[i]->DrawQuadTree(theCamera,2);
		}

	}
}

bool QuadTree1::DetermineLOD = false;
bool QuadTree1::FirstPass = true;