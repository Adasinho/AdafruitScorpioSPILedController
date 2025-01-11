#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include "Animation.hpp"
#include "LedStrip.hpp"
#include "StripId.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

#include "Adafruit_NeoPXL8.h"

class AnimationManager {
public:
    AnimationManager();
    AnimationManager(Adafruit_NeoPXL8* pixels);

    void update();
    void playAnimation(StripId id, std::unique_ptr<Animation> animation);
private:
    void stopAnimation(StripId id);

    std::unordered_map<StripId, std::unique_ptr<Animation>> animations;
    Adafruit_NeoPXL8* pixels;
    bool blocking = false;
};

#endif // ANIMATIONMANAGER_HPP