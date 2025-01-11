#include "AnimationManager.hpp"

AnimationManager::AnimationManager()
{
    
}

AnimationManager::AnimationManager(Adafruit_NeoPXL8 *pixels)
{
    printf("[AnimationManager] constructor\n");
    this->pixels = pixels;
}

void AnimationManager::update()
{
    //printf("[AnimationManager] update\n");
    std::vector<StripId> stripsToStopAnimate;

    uint32_t owner_id; 
    if (!this->blocking) {
        for(const auto& pair : this->animations)
        {
            if (pair.second) {
                const StripId& id = pair.first;
                Animation* animation = pair.second.get();

                printf("[AnimationManager] next frame for strip: %d\n", id);

                if(animation->isFinished()) stripsToStopAnimate.push_back(id);
                else animation->nextFrame();
            } else {
                const StripId& id = pair.first;
                printf("Animation for strip %d, not exist", static_cast<int>(id));
            }
        }

        for(StripId& stripToStopAnimation : stripsToStopAnimate) {
            this->stopAnimation(stripToStopAnimation);
        }
    }

    this->pixels->show();
}

void AnimationManager::playAnimation(StripId id, std::unique_ptr<Animation> animation)
{
    this->blocking = true;
    printf("[AnimationManager] playAnimation for strip %d \n", id);
    //this->animations[id] = std::move(animation);

    if(this->animations[id]) {
        if(!this->animations[id]->isFinished()) this->stopAnimation(id);
    }
    
    this->animations[id] = std::move(animation);
    //printf("[AnimationManager] After playAnimation for strip %d \n", id);
    this->blocking = false;
}

void AnimationManager::stopAnimation(StripId id)
{
    printf("[AnimationManager] stopAnimation for strip %d \n", id);
    printf("[AnimationManager] Size of: %d\n", this->animations.size());
    this->animations.erase(id);
    
}
