/*!
 *  Copyright (C) 2011-2015  OpenDungeons Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ai/AIManager.h"

#include "ai/KeeperAI.h"
#include "game/Player.h"

#include "utils/LogManager.h"

AIManager::AIManager(GameMap& gameMap)
    : mGameMap(gameMap)
{
}

AIManager::~AIManager()
{
    clearAIList();
}

bool AIManager::assignAI(Player& player, KeeperAIType type, const std::string& params)
{
    BaseAI* ai = BaseAI::getAi(mGameMap, player, type);
    if(ai == nullptr)
        return false;

    mAiList.push_back(ai);
    return true;
}

bool AIManager::doTurn(double timeSinceLastTurn)
{
    for(BaseAI* ai : mAiList)
    {
        ai->doTurn(timeSinceLastTurn);
    }
    return true;
}

void AIManager::clearAIList()
{
    for(BaseAI* ai : mAiList)
    {
        delete ai;
    }
    mAiList.clear();
}
