#include "SolidColorAnimation.hpp"

SolidColorAnimation::SolidColorAnimation(LedStrip *ledStrip, uint8_t red, uint8_t green, uint8_t blue, uint8_t speed)
    : ledStrip(ledStrip), speed(speed)
{
    Color* color = ledStrip->getLedColor(0);
    printf("[SolidColorAnimation] id: %d set color (%d %d %d), current color (%d %d %d)\n", ledStrip->getStripId(), red, green, blue, color->getRed(), color->getGreen(), color->getBlue());

    this->targetColor = Color(red, green, blue);
}

SolidColorAnimation::SolidColorAnimation(LedStrip *ledStrip, Color targetColor, uint8_t speed)
    : SolidColorAnimation(ledStrip, targetColor.getRed(), targetColor.getGreen(), targetColor.getBlue(), speed)
{

}

void SolidColorAnimation::nextFrame()
{
    //printf("[SolidColorAnimation] Play animation for strip: %d, with %d diodes\n", static_cast<int>(this->ledStrip->getStripId()), this->ledStrip->getLedsCount());

    int sameLedColorCounter = 0;

    for(int i = 0; i < this->ledStrip->getLedsCount(); i++) {
        Color* currentColor = this->ledStrip->getLedColor(i);

        if(*currentColor == this->targetColor) {
            sameLedColorCounter++;
            continue;
        }

        Color nextFrameLedColor = this->generateNewFrameColor(*currentColor);
        this->ledStrip->setLedColor(
            i,
            nextFrameLedColor.getRed(),
            nextFrameLedColor.getGreen(),
            nextFrameLedColor.getBlue()
        );

        if(nextFrameLedColor == this->targetColor) sameLedColorCounter++;
    }

    //this->ledStrip->show();

    if(sameLedColorCounter == this->ledStrip->getLedsCount()) {
        //printf("[SolidColorAnimation] Finish animation\n");
        this->finished = true;
    }   
}

bool SolidColorAnimation::isFinished()
{
    return this->finished;
}

Color SolidColorAnimation::generateNewFrameColor(Color currentColor)
{
    uint8_t red, green, blue;
    int parsedTargetColorRed = static_cast<int>(this->targetColor.getRed());
    int parsedTargetColorGreen = static_cast<int>(this->targetColor.getGreen());
    int parsedTargetColorBlue = static_cast<int>(this->targetColor.getBlue());

    int parsedCurrentColorRed = static_cast<int>(currentColor.getRed());
    int parsedCurrentColorGreen = static_cast<int>(currentColor.getGreen());
    int parsedCurrentColorBlue = static_cast<int>(currentColor.getBlue());

    if (parsedCurrentColorRed == parsedTargetColorRed)
        red = parsedTargetColorRed;
    else if (parsedCurrentColorRed < parsedTargetColorRed)
        red = parsedCurrentColorRed + this->speed > parsedTargetColorRed ? parsedTargetColorRed : parsedCurrentColorRed + this->speed;
    else if(parsedCurrentColorRed > parsedTargetColorRed)
        red = parsedCurrentColorRed - this->speed < parsedTargetColorRed ? parsedTargetColorRed : parsedCurrentColorRed - this->speed;

    if (parsedCurrentColorGreen == parsedTargetColorGreen)
        green = parsedTargetColorGreen;
    else if (parsedCurrentColorGreen < parsedTargetColorGreen)
        green = parsedCurrentColorGreen + this->speed > parsedTargetColorGreen ? parsedTargetColorGreen : parsedCurrentColorGreen + this->speed;
    else if(parsedCurrentColorGreen > parsedTargetColorGreen)
        green = parsedCurrentColorGreen - this->speed < parsedTargetColorGreen ? parsedTargetColorGreen : parsedCurrentColorGreen - this->speed;

    if (parsedCurrentColorRed == parsedTargetColorBlue)
        blue = parsedTargetColorBlue;
    else if (parsedCurrentColorBlue < parsedTargetColorBlue)
        blue = parsedCurrentColorBlue + this->speed > parsedTargetColorBlue ? parsedTargetColorBlue : parsedCurrentColorBlue + this->speed;
    else if(parsedCurrentColorBlue > parsedTargetColorBlue)
        blue = parsedCurrentColorBlue - this->speed < parsedTargetColorBlue ? parsedTargetColorBlue : parsedCurrentColorBlue - this->speed;

    //printf("[SolidColorAnimation] newFrame FROM: (%d %d %d) TO (%d %d %d)\n", parsedTargetColorRed, parsedTargetColorGreen, parsedTargetColorBlue, red, green, blue);

    return Color(red, green, blue);
}
