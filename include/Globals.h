#ifndef GLOBALS_H
#define GLOBALS_H

#include "Tile.h"
#include "GameMap.h"
#include "Player.h"

extern GameMap gameMap;
extern SceneManager* mSceneMgr;
extern string MOTD;
extern int MAX_FRAMES_PER_SECOND;
extern vector<Player*> players;
extern Player *me;
extern double turnsPerSecond;
extern long int turnNumber;

#endif

