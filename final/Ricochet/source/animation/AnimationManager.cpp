#include "AnimationManager.h"

using namespace tinyxml2;

AnimationManager::AnimationManager(GameData& gameData) : gdata(gameData)
{
    //ctor
}

AnimationManager::~AnimationManager()
{
    //dtor
}

void AnimationManager::updateAnimations()
{
    for (Animation* a: m_activeAnimations)
    {
        if (a)
        {
            a->update();
        }
    }
}

Animation* AnimationManager::getPresetAnimation(std::string name, Object* obj)
{
    Animation* preset = nullptr;
    for (Animation* anim: m_presetAnimations)
    {
        if (anim->m_name == name)
        {
            preset = anim;
        }
    }

    Animation* newAnimation = nullptr;
    if (preset)
    {
        newAnimation = new Animation();
        newAnimation->gdata             = &gdata;
        newAnimation->m_name            = preset->m_name;
        newAnimation->m_duration        = preset->m_duration;
        newAnimation->m_loops           = preset->m_loops;
        newAnimation->m_reset           = preset->m_reset;
        newAnimation->m_resetRotation   = preset->m_resetRotation;
        newAnimation->m_resetPosition   = preset->m_resetPosition;
        newAnimation->setInstructions(preset->getInstructions());
        newAnimation->setObject(obj);
        m_activeAnimations.push_back(newAnimation);
    }

    return newAnimation;
}


bool AnimationManager::loadAnimationsFile(std::string path)
{
    XMLDocument doc;
    XMLError xmlError = doc.LoadFile(path.c_str());


    if (xmlError != XML_NO_ERROR)
    {
        gz::print_w("Error loading animations.xml error:" + gz::toString(xmlError));    // failed to open document
        return false;
    }

    XMLElement* root = doc.RootElement();
    if (!root)
    {
        gz::print_w("Error getting root element");        // no root element
        return false;
    }

    //create the animations from the xml
    createAnimations(root);

    return true;
}

bool AnimationManager::createAnimations(XMLElement* root)
{
    //TODO check if attributes are null or dont exist
    XMLElement* element = root->FirstChildElement("animation");
    while (element)
    {
        // create the animation
        Animation* animation = new Animation();
        animation->m_name = element->Attribute("name");
        animation->m_duration = atof(element->Attribute("duration"));
        animation->m_loops = gz::toInt(element->Attribute("loops"),0);

        XMLElement* element_reset = element->FirstChildElement("reset");
        if (element_reset)
        {
            animation->m_reset = gz::toBool(element_reset->Attribute("value"));
            animation->m_resetPosition = Vector2(element_reset->Attribute("position"));
            animation->m_resetRotation = gz::toInt(element_reset->Attribute("rotation"),0);
        }


        XMLElement* element_instruction = element->FirstChildElement("instruction");
        while (element_instruction)
        {
            //create the instructions and add them to the animation
            AnimationInstruction* ai = new AnimationInstruction();
            ai->m_startTime = atof(element_instruction->Attribute("starttime"));
            ai->m_duration = atof(element_instruction->Attribute("duration"));

            XMLElement* ele_start = element_instruction->FirstChildElement("start");
            if (ele_start)
            {
                ai->m_relativeStartPosition = gz::toBool(ele_start->Attribute("relative"));
                ai->m_relativeStartRotation = gz::toBool(ele_start->Attribute("relative"));
                ai->m_startPosition = Vector2(ele_start->Attribute("position"));
                ai->m_startRotation = gz::toInt(ele_start->Attribute("rotation"),0);
            }

            XMLElement* ele_end = element_instruction->FirstChildElement("end");
            if (ele_end)
            {
                ai->m_relativeEndPosition = gz::toBool(ele_end->Attribute("relative"));
                ai->m_relativeEndRotation = gz::toBool(ele_end->Attribute("relative"));
                ai->m_endPosition = Vector2(ele_end->Attribute("position"));
                ai->m_endRotation = gz::toInt(ele_end->Attribute("rotation"),0);
            }

            animation->addAction(ai);
            element_instruction = element_instruction->NextSiblingElement("instruction");
        }

        m_presetAnimations.push_back(animation);
        element = element->NextSiblingElement("animation");
    }

    return true;
}


//bool AnimationManager::createAnimations(TiXmlElement* root)
//{
//    TiXmlElement* e_animation = root->FirstChildElement();
//    while (e_animation)
//    {
//        std::string tagName = e_animation->Attribute("type");
//        if (gz::toLowerCase(tagName) == "animation")
//        {
//            Animation* animation = new Animation();
//            animation->m_name = e_animation->Attribute("name");
//
//            animation->m_duration = atof(e_animation->Attribute("duration"));
//            animation->m_loops = gz::toInt(e_animation->Attribute("loops"),0);
//            animation->m_reset = gz::toBool(e_animation->Attribute("reset"));
//            animation->m_resetRotation = gz::toInt(e_animation->Attribute("resetrotation"),0);
//            animation->m_resetPosition = Vector2(e_animation->Attribute("resetposition"));
//
//            gz::print_d("name=" + animation->m_name);
//            gz::print_value("duration",animation->m_duration);
//            gz::print_value("loops",animation->m_loops);
//            gz::print_value("reset",animation->m_reset);
//            gz::print_value("rotation",animation->m_resetRotation);
//            animation->m_resetPosition.print("position");
//
//            // TODO:
//            std::vector<AnimationInstruction*> instruction = createInstructions(e_animation);
//            // read and create instructions
//            // add them to the animation
//            // add animation to the collection
//        }
//        e_animation = e_animation->NextSiblingElement();
//    }
//
//    // TODO: return the success of the function
//    return true;
//}
//
//std::vector<AnimationInstruction*> AnimationManager::createInstructions(TiXmlElement* element)
//{
//
//}


