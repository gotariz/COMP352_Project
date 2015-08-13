#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "general.h"

#include "animation/AnimationInstruction.h"
#include "animation/Animation.h"

#include "entities/Object.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class AnimationManager
{
    public:
        AnimationManager(GameData& gameData);
        virtual ~AnimationManager();

        bool loadAnimationsFile(std::string path);
        Animation* getPresetAnimation(std::string name, Object* obj);

        void updateAnimations();
    protected:

        GameData& gdata;
        // some kind of collection/map
        std::vector<Animation*> m_activeAnimations;

        std::vector<Animation*> m_presetAnimations;
    private:
        bool createAnimations(XMLElement* root);
};

#endif // ANIMATIONMANAGER_H
