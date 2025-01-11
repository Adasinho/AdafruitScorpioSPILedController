#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation {
public:
  virtual void nextFrame() = 0;
  virtual bool isFinished() = 0;
};

#endif // ANIMATION_HPP