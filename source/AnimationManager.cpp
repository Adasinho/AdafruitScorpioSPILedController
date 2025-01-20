#include "AnimationManager.hpp"
#include "Logger.hpp"

AnimationManager::AnimationManager()
{
    
}

AnimationManager::AnimationManager(Adafruit_NeoPXL8 *pixels)
{
    Logger::log(LogLevel::DEBUG, "[AnimationManager] constructor");
    this->pixels = pixels;
}

void AnimationManager::update()
{
    //Logger::log(LogLevel::INFO, "[AnimationManager] update");
    std::vector<StripId> stripsToStopAnimate;

    uint32_t owner_id; 
    if (!this->blocking) {
        for(const auto& pair : this->animations)
        {
            if (pair.second) {
                const StripId& id = pair.first;
                Animation* animation = pair.second.get();

                Logger::log(LogLevel::DEBUG, "[AnimationManager] next frame for strip: %d", id);

                if(animation->isFinished()) stripsToStopAnimate.push_back(id);
                else animation->nextFrame();
            } else {
                const StripId& id = pair.first;
                Logger::log(LogLevel::WARNING, "Animation for strip %d, not exist", static_cast<int>(id));
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
    Logger::log(LogLevel::DEBUG, "[AnimationManager] playAnimation for strip %d", id);
    //this->animations[id] = std::move(animation);

    if(this->animations[id]) {
        if(!this->animations[id]->isFinished()) this->stopAnimation(id);
    }
    
    this->animations[id] = std::move(animation);
    //Logger::log(LogLevel::DEBUG, "[AnimationManager] After playAnimation for strip %d", id);
    this->blocking = false;
}

void AnimationManager::stopAnimation(StripId id)
{
    Logger::log(LogLevel::DEBUG, "[AnimationManager] stopAnimation for strip %d", id);
    Logger::log(LogLevel::DEBUG, "[AnimationManager] Size of: %d", this->animations.size());
    this->animations.erase(id);
    
}
