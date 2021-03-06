//
//      unit_updater.h: game setup menu as it appears to
//      to the host
//
//      This file is part of ZetaGlest <https://github.com/ZetaGlest>
//
//      Copyright (C) 2018  The ZetaGlest team
//
//      ZetaGlest is a fork of MegaGlest <https://megaglest.org>
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>

#ifndef _GLEST_GAME_UNITUPDATER_H_
#define _GLEST_GAME_UNITUPDATER_H_

#ifdef WIN32
    #include <winsock2.h>
    #include <winsock.h>
#endif

#include "gui.h"
#include "particle.h"
#include "randomgen.h"
#include "command.h"
#include "leak_dumper.h"

using Shared::Graphics::ParticleObserver;
using Shared::Util::RandomGen;

namespace Glest{ namespace Game{

class Unit;
class Map;
class ScriptManager;
class PathFinder;

// =====================================================
//	class UnitUpdater
//
///	Updates all units in the game, even the player
///	controlled units, performs basic actions only
///	such as responding to an attack
// =====================================================

class ParticleDamager;
class Cell;

class UnitRangeCellsLookupItem {
public:

	//int UnitRangeCellsLookupItemCacheTimerCountIndex;
	std::vector<Cell *> rangeCellList;

	static time_t lastDebug;
};

class AttackWarningData {
public:
	Vec2f attackPosition;
	int lastFrameCount;
};

class UnitUpdater {
private:
	friend class ParticleDamager;
	typedef vector<AttackWarningData*> AttackWarnings;

private:
	static const int maxResSearchRadius= 10;
	static const int harvestDistance= 5;
	static const int ultraResourceFactor= 3;
	static const int megaResourceFactor= 4;

private:
	const GameCamera *gameCamera;
	Gui *gui;
	Map *map;
	World *world;
	Console *console;
	ScriptManager *scriptManager;
	PathFinder *pathFinder;
	Game *game;
	//RandomGen random;
	Mutex *mutexAttackWarnings;
	float attackWarnRange;
	AttackWarnings attackWarnings;

	Mutex *mutexUnitRangeCellsLookupItemCache;
	std::map<Vec2i, std::map<int, std::map<int, UnitRangeCellsLookupItem > > > UnitRangeCellsLookupItemCache;
	//std::map<int,ExploredCellsLookupKey> ExploredCellsLookupItemCacheTimer;
	//int UnitRangeCellsLookupItemCacheTimerCount;

	bool findCachedCellsEnemies(Vec2i center, int range,
								int size, vector<Unit*> &enemies,
								const AttackSkillType *ast, const Unit *unit,
								const Unit *commandTarget);
	void findEnemiesForCell(const AttackSkillType *ast, Cell *cell, const Unit *unit,
							const Unit *commandTarget,vector<Unit*> &enemies);

public:
	UnitUpdater();
    void init(Game *game);
    ~UnitUpdater();

	//update skills
    bool updateUnit(Unit *unit);

    //update commands
    void updateUnitCommand(Unit *unit, int frameIndex);
    void updateStop(Unit *unit, int frameIndex);
    void updateMove(Unit *unit, int frameIndex);
    void updateAttack(Unit *unit, int frameIndex);
    void updateAttackStopped(Unit *unit, int frameIndex);
    void updateBuild(Unit *unit, int frameIndex);
    void updateHarvest(Unit *unit, int frameIndex);
    void updateHarvestEmergencyReturn(Unit *unit, int frameIndex);
    void updateRepair(Unit *unit, int frameIndex);
    void updateProduce(Unit *unit, int frameIndex);
    void updateUpgrade(Unit *unit, int frameIndex);
	void updateMorph(Unit *unit, int frameIndex);
	void updateSwitchTeam(Unit *unit, int frameIndex);

	void clearUnitPrecache(Unit *unit);
	void removeUnitPrecache(Unit *unit);

	inline unsigned int getAttackWarningCount() const { return (unsigned int)attackWarnings.size(); }
	std::pair<bool,Unit *> unitBeingAttacked(const Unit *unit);
	void unitBeingAttacked(std::pair<bool,Unit *> &result, const Unit *unit, const AttackSkillType *ast,float *currentDistToUnit=NULL);
	vector<Unit*> enemyUnitsOnRange(const Unit *unit,const AttackSkillType *ast);
	void findEnemiesForCell(const Vec2i pos, int size, int sightRange, const Faction *faction, vector<Unit*> &enemies, bool attackersOnly) const;

	vector<Unit*> findUnitsInRange(const Unit *unit, int radius);

	string getUnitRangeCellsLookupItemCacheStats();

	void saveGame(XmlNode *rootNode);
	void loadGame(const XmlNode *rootNode);

	void clearCaches();

private:
    //attack
    void hit(Unit *attacker);
	void hit(Unit *attacker, const AttackSkillType* ast, const Vec2i &targetPos, Field targetField, int damagePercent);
	void damage(Unit *attacker, const AttackSkillType* ast, Unit *attacked, float distance, int damagePercent);
	void startAttackParticleSystem(Unit *unit, float lastAnimProgress, float animProgress);

	//misc
    bool searchForResource(Unit *unit, const HarvestCommandType *hct);
    bool attackerOnSight(Unit *unit, Unit **enemyPtr, bool evalMode=false);
    bool attackableOnSight(Unit *unit, Unit **enemyPtr, const AttackSkillType *ast, bool evalMode=false);
    bool attackableOnRange(Unit *unit, Unit **enemyPtr, const AttackSkillType *ast, bool evalMode=false);
	bool unitOnRange(Unit *unit, int range, Unit **enemyPtr, const AttackSkillType *ast,bool evalMode=false);
	void enemiesAtDistance(const Unit *unit, const Unit *priorityUnit, int distance, vector<Unit*> &enemies);

	void spawn(Unit *unit,string spawnUnit,int spawnUnitcount,int healthMin,int healthMax,int probability);
	void spawnAttack(Unit *unit,string spawnUnit,int spawnUnitcount,int healthMin,int healthMax,int probability,bool spawnUnitAtTarget,Vec2i targetPos=Vec2i(-10,-10));
	Unit* spawnUnit(Unit *unit,string spawnUnit,Vec2i targetPos=Vec2i(-10,-10));

	Unit * findPeerUnitBuilder(Unit *unit);
	void SwapActiveCommand(Unit *unitSrc, Unit *unitDest);
	void SwapActiveCommandState(Unit *unit, CommandStateType commandStateType,
								const CommandType *commandType,
								int originalValue,int newValue);
	void findUnitsForCell(Cell *cell, vector<Unit*> &units);

};

// =====================================================
//	class ParticleDamager
// =====================================================

class ParticleDamager: public ParticleObserver {

public:
	UnitReference attackerRef;
	const AttackSkillType* ast;
	const ProjectileType* projectileType;
	UnitUpdater *unitUpdater;
	const GameCamera *gameCamera;
	Vec2i targetPos;
	Field targetField;

public:
	ParticleDamager(Unit *attacker, const ProjectileType *projectileType, UnitUpdater *unitUpdater, const GameCamera *gameCamera);
	virtual void update(ParticleSystem *particleSystem);

	virtual void saveGame(XmlNode *rootNode);
	virtual void loadGame(const XmlNode *rootNode,void *genericData);
};

}}//end namespace

#endif
