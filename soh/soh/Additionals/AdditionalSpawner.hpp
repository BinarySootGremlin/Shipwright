#pragma once
#include "Scene.h"
#include <map>
#include "global.h"

class AdditionalSpawner
{
public:
	AdditionalSpawner(const AdditionalSpawner&) = delete;
	static AdditionalSpawner& Get() 
	{
		return instance;
	}
	void addActors(PlayState* play, Ship::SceneCommand* cmd, bool cached);
private:
	AdditionalSpawner(){};
	static AdditionalSpawner instance;
	struct AdditionalSceneActor
	{
		s32 sceneSetupIndex;
		s32 index;
		Ship::ActorSpawnEntry actor;
	};

	typedef std::vector<AdditionalSceneActor> sceneActorVector;
	typedef std::map<u16, sceneActorVector> roomActorMap;
	typedef std::map<u16, roomActorMap> sceneRoomMap;

	sceneRoomMap AdditionalSceneMap = { 
		{ SCENE_LINK_HOME, { { 0x00, { { 0, -1, { ACTOR_EN_SA, -79, 0, 93, 0, 25482, 0, 0x0 } } } } } }
	};
};