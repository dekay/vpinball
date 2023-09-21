#pragma once

#include "../b2s_i.h"
#include "B2SAnimationBase.h"

class Control;
class B2SPictureBox;

class TimerAnimation : public B2SAnimationBase
{
public:
   TimerAnimation(Control* pForm, Control* pFormDMD, const string& szName, eDualMode dual, int interval, int loops, bool startTimerAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd,  eAnimationStopBehaviour animationStopBehaviour, 
      bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront, bool randomStart, int randomQuality, vector<SDL_Surface*> images);

   TimerAnimation(Control* pForm, B2SPictureBox* pPictureBox, const string& szName, eDualMode dual, int interval, int loops, bool startTimerAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd, eAnimationStopBehaviour animationStopBehaviour, 
      bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront, bool randomStart, int randomQuality, vector<SDL_Surface*> images);

   void Start() override;

private:
};