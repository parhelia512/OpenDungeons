#ifndef MODEMANAGER_H
#define MODEMANAGER_H

#include <stack>


using std::stack;

class AbstractApplicationMode;
class ModeContext;
class GameMap;
class MiniMap;
class Console;

class ModeManager
{
friend class Gui;


public:

enum ModeType {
    MENU,
    GAME,
    EDITOR,
    CONSOLE,
    PREV
    };



ModeManager(GameMap* ,MiniMap*, Console* cn );
~ModeManager();

AbstractApplicationMode*  getCurrentMode();


AbstractApplicationMode*  progressMode(ModeType);
AbstractApplicationMode*  regressMode();

int lookForNewMode();

ModeContext *mc;


private:
Console *cn;
AbstractApplicationMode* modesArray[4];
stack<ModeType> modesStack;




};

#endif // MODEMANAGER_H