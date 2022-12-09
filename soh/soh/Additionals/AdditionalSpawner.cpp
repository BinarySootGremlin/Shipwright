#include "AdditionalSpawner.hpp"
#include "vt.h"
AdditionalSpawner AdditionalSpawner::instance;

void AdditionalSpawner::addActors(PlayState* play, Ship::SceneCommand* cmd)
{
    Ship::SetActorList* cmdActor = (Ship::SetActorList*)cmd;
    osSyncPrintf(VT_FGCOL(RED) "ADD ACTORS\n");

    if (this->AdditionalSceneMap.find(play->sceneNum) != this->AdditionalSceneMap.end() &&
        this->AdditionalSceneMap.at(play->sceneNum).find(play->roomCtx.curRoom.num) != this->AdditionalSceneMap.at(play->sceneNum).end()) {
        auto& roomOverrides = this->AdditionalSceneMap.at(play->sceneNum).at(play->roomCtx.curRoom.num);
        for (AdditionalSceneActor& sceneActor : roomOverrides) {
            if (sceneActor.sceneSetupIndex == -1 || sceneActor.sceneSetupIndex == gSaveContext.sceneSetupIndex) {
                if (sceneActor.index == -1) {
                    cmdActor->entries.push_back(sceneActor.actor);
                    osSyncPrintf(VT_FGCOL(RED) "PUSH ACTOR: %i\n", sceneActor.actor.actorNum);
                }
                else {
                    cmdActor->entries[sceneActor.index] = sceneActor.actor;
                    osSyncPrintf(VT_FGCOL(RED) "SET ACTORS: %i\n", sceneActor.actor.actorNum);
                }
                ActorOverlay* overlayEntry = &gActorOverlayTable[sceneActor.actor.actorNum];

                ActorInit* actorInit =
                    (ActorInit*)((uintptr_t)overlayEntry->initInfo -
                            ((intptr_t)overlayEntry->vramStart - (intptr_t)overlayEntry->loadedRamAddr));

                play->objectCtx.status[play->objectCtx.num].id = actorInit->objectId;
                play->objectCtx.num++;
            }
        }
        play->numSetupActors = cmdActor->entries.size();
    }
}
