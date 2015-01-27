#pragma once
#include "BaseEntity.h"
#include <set>
#include <vector>
#include "ObjLoader.h"




struct BaseEntityPair
{
	BaseEntity* BaseEntity1;
	BaseEntity* BaseEntity2;
};
class Quadtree2 {
private:
	float minX;
	float minZ;
	float maxX;
	float maxZ;
	float centerX; //(minX + maxX) / 2
	float centerZ; //(minZ + maxZ) / 2

	/* The children of this, if this has any.  children[0][*] are the
	* children with x coordinates ranging from minX to centerX.
	* children[1][*] are the children with x coordinates ranging from
	* centerX to maxX.  Similarly for the other dimension of the children
	* array.
	*/
	Quadtree2 *children[2][2];
	//Whether this has children
	bool hasChildren;
	//The BaseEntitys in this, if this doesn't have any children
	std::set<BaseEntity*> BaseEntitys;
	//The depth of this in the tree
	int depth;
	//The number of BaseEntitys in this, including those stored in its children
	int numBaseEntitys;

	//Adds a BaseEntity to or removes one from the children of this
	void fileBaseEntity(BaseEntity* theBaseEntity, float x, float z, bool addBaseEntity)
	{
		//Figure out in which child(ren) thetheBaseEntity belongs
		for (int xi = 0; xi < 2; xi++)
		{
			if (xi == 0)
			{
				if (GetMinMax(*theBaseEntity->GetObjectModel().theCurrent).MaxX > centerX)
				{
					continue;
				}
			}
			else if (GetMinMax(*theBaseEntity->GetObjectModel().theCurrent).MinX < centerX) 
			{
				continue;
			}

			for (int zi = 0; zi < 2; zi++)
			{
				if (zi == 0)
				{
					if (GetMinMax(*theBaseEntity->GetObjectModel().theCurrent).MaxZ > centerZ)
					{
						continue;
					}
				}
				else if (GetMinMax(*theBaseEntity->GetObjectModel().theCurrent).MinZ < centerZ)
				{
					continue;
				}

				//Add or remove thetheBaseEntity
				if (addBaseEntity)
				{
					children[xi][zi]->add(theBaseEntity);
				}
				else {
					children[xi][zi]->remove(theBaseEntity, x, z);
				}
			}
		}
	}

	//Creates children of this, and moves the BaseEntitys in this to the children
	void haveChildren() {
		for (int x = 0; x < 2; x++) {
			float minX2;
			float maxX2;
			if (x == 0) {
				minX2 = minX;
				maxX2 = centerX;
			}
			else {
				minX2 = centerX;
				maxX2 = maxX;
			}

			for (int z = 0; z < 2; z++) {
				float minZ2;
				float maxZ2;
				if (z == 0) {
					minZ2 = minZ;
					maxZ2 = centerZ;
				}
				else {
					minZ2 = centerZ;
					maxZ2 = maxZ;
				}

				children[x][z] =
					new Quadtree2(minX2, maxX2, minZ2, maxZ2, depth + 1);
			}
		}

		//Remove all BaseEntitys from "BaseEntitys" and add them to the new children
		for (std::set<BaseEntity*>::iterator it = BaseEntitys.begin(); it != BaseEntitys.end();
			it++) {
			BaseEntity* BaseEntity = *it;
			fileBaseEntity(BaseEntity, BaseEntity->getPosition().x, BaseEntity->getPosition().z, true);
		}
		BaseEntitys.clear();

		hasChildren = true;
	}

	//Adds all BaseEntitys in this or one of its descendants to the specified set
	void collectBaseEntitys(std::set<BaseEntity*> &gs) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int z = 0; z < 2; z++) {
					children[x][z]->collectBaseEntitys(gs);
				}
			}
		}
		else {
			for (std::set<BaseEntity*>::iterator it = BaseEntitys.begin(); it != BaseEntitys.end();
				it++) {
				BaseEntity* BaseEntity = *it;
				gs.insert(BaseEntity);
			}
		}
	}

	//Destroys the children of this, and moves all BaseEntitys in its descendants
	//to the "BaseEntitys" set
	void destroyChildren() {
		//Move all BaseEntitys in descendants of this to the "BaseEntitys" set
		collectBaseEntitys(BaseEntitys);

		for (int x = 0; x < 2; x++) {
			for (int z = 0; z < 2; z++) {
				delete children[x][z];
			}
		}

		hasChildren = false;
	}

	//Removes the specified BaseEntity at the indicated position
	void remove(BaseEntity* BaseEntity, float x, float z) {
		numBaseEntitys--;

		if (hasChildren && numBaseEntitys < 1) {
			destroyChildren();
		}

		if (hasChildren) {
			fileBaseEntity(BaseEntity, x, z, false);
		}
		else {
			BaseEntitys.erase(BaseEntity);
		}
	}
public:
	//Constructs a new Quadtree.  d is the depth, which starts at 1.
	Quadtree2(float minX1, float minZ1, float maxX1, float maxZ1, int d) {
		minX = minX1;
		minZ = minZ1;
		maxX = maxX1;
		maxZ = maxZ1;
		centerX = (minX + maxX) / 2;
		centerZ = (minZ + maxZ) / 2;

		depth = d;
		numBaseEntitys = 0;
		hasChildren = false;
	}

	~Quadtree2() {
		if (hasChildren) {
			destroyChildren();
		}
	}

	//Adds a BaseEntity to this
	void add(BaseEntity* BaseEntity)
	{
		numBaseEntitys++;
		if (!hasChildren && depth < 10 &&
			numBaseEntitys > 1) {
			haveChildren();
		}

		if (hasChildren) {
			fileBaseEntity(BaseEntity, BaseEntity->getPosition().x, BaseEntity->getPosition().z, true);
		}
		else {
			BaseEntitys.insert(BaseEntity);
		}
	}

	//Removes a BaseEntity from this
	void remove(BaseEntity* BaseEntity) {
		remove(BaseEntity, BaseEntity->getPosition().x, BaseEntity->getPosition().z);
	}

	//Changes the position of a BaseEntity in this from the specified position to
	//its current position
	void BaseEntityMoved(BaseEntity* BaseEntity, float x, float z) {
		remove(BaseEntity, x, z);
		add(BaseEntity);
	}

	//Adds potential collisions to the specified set
	void potentialCollisions(std::vector<BaseEntityPair> &collisions) {
		if (hasChildren) {
			for (int x = 0; x < 2; x++) {
				for (int z = 0; z < 2; z++) {
					children[x][z]->potentialCollisions(collisions);
				}
			}
		}
		else {
			//Add all pairs (BaseEntity1, BaseEntity2) from BaseEntitys
			for (std::set<BaseEntity*>::iterator it = BaseEntitys.begin(); it != BaseEntitys.end();
				it++) {
				BaseEntity* BaseEntity1 = *it;
				for (std::set<BaseEntity*>::iterator it2 = BaseEntitys.begin();
					it2 != BaseEntitys.end(); it2++) {
					BaseEntity* BaseEntity2 = *it2;
					//This test makes sure that we only add each pair once
					if (BaseEntity1 < BaseEntity2) {
						BaseEntityPair gp;
						gp.BaseEntity1 = BaseEntity1;
						gp.BaseEntity2 = BaseEntity2;
						collisions.push_back(gp);
					}
				}
			}
		}
	}
};
