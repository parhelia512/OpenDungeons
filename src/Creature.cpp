#include "Creature.h"
#include "Defines.h"
#include "Globals.h"

Creature::Creature()
{
	position = Ogre::Vector3(0,0,0);
	scale = Ogre::Vector3(1,1,1);
}

Creature::Creature(string nClassName, string nMeshName, Ogre::Vector3 nScale)
{
	className = nClassName;
	meshName = nMeshName;
	scale = nScale;
}

ostream& operator<<(ostream& os, Creature *c)
{
	os << c->className << "\t" << c->name << "\t";
	os << c->position.x << "\t" << c->position.y << "\t" << c->position.z << "\n";

	return os;
}

istream& operator>>(istream& is, Creature *c)
{
	static int uniqueNumber = 1;
	double xLocation = 0.0, yLocation = 0.0, zLocation = 0.0;
	string tempString;
	is >> c->className;

	is >> tempString;

	if(tempString.compare("autoname") == 0)
	{
		char tempArray[255];
		sprintf(tempArray, "%s_%04i", c->className.c_str(), uniqueNumber);
		tempString = string(tempArray);
	}

	c->name = tempString;

	is >> xLocation >> yLocation >> zLocation;
	c->position = Ogre::Vector3(xLocation, yLocation, zLocation);

	uniqueNumber++;
	return is;
}

void Creature::createMesh()
{
	Entity *ent;
	SceneNode *node;

	ent = mSceneMgr->createEntity( ("Creature_" + name).c_str(), meshName.c_str());
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode( (name + "_node").c_str() );
	node->setPosition(position/BLENDER_UNITS_PER_OGRE_UNIT);
	//FIXME: Something needs to be done about the caling issue here.
	//node->setScale(1.0/BLENDER_UNITS_PER_OGRE_UNIT, 1.0/BLENDER_UNITS_PER_OGRE_UNIT, 1.0/BLENDER_UNITS_PER_OGRE_UNIT);
	node->setScale(scale);
	node->attachObject(ent);
}

void Creature::destroyMesh()
{
	Entity *ent;
	SceneNode *node;

	ent = mSceneMgr->getEntity( ("Creature_" + name).c_str() );
	node = mSceneMgr->getSceneNode( (name + "_node").c_str() );
	mSceneMgr->getRootSceneNode()->removeChild( node );
	node->detachObject( ent );
	mSceneMgr->destroyEntity( ent );
	mSceneMgr->destroySceneNode( (name + "_node") );
}

void Creature::setPosition(double x, double y, double z)
{
	SceneNode *creatureSceneNode = mSceneMgr->getSceneNode(name + "_node");

	//FIXME: X-Y reversal issue.
	creatureSceneNode->setPosition(y/BLENDER_UNITS_PER_OGRE_UNIT, x/BLENDER_UNITS_PER_OGRE_UNIT, z/BLENDER_UNITS_PER_OGRE_UNIT);
	gameMap.getCreature(name)->position = Ogre::Vector3(y, x, z);
}

Ogre::Vector3 Creature::getPosition()
{
	return position;
}

void Creature::doTurn()
{
}

