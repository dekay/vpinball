#include "stdafx.h"

#include "TimerAnimation.h"
#include "../collections/RunningAnimationsCollection.h"

TimerAnimation::TimerAnimation(Control* pForm, Control* pFormDMD, const string& szName, eDualMode dual, int interval, int loops, bool startTimerAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd, eAnimationStopBehaviour animationStopBehaviour, 
      bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront, bool randomStart, int randomQuality, vector<SDL_Surface*> images) : B2SAnimationBase(dual,
      interval, eType_ImageCollectionAtForm, loops, false, startTimerAtVPActivate, lightsStateAtAnimationStart, lightsStateAtAnimationEnd, animationStopBehaviour, 
      lockInvolvedLamps, hideScoreDisplays, bringToFront, randomStart, randomQuality)
{
   //Me.SynchronizingObject = _Form
   //Me.Form = _Form
   //Me.FormDMD = _FormDMD
   SetName(szName);
   //Me.ImageCollection = _ImageCollection
}

TimerAnimation::TimerAnimation(Control* pForm, B2SPictureBox* pPictureBox, const string& szName, eDualMode dual, int interval, int loops, bool startTimerAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd, eAnimationStopBehaviour animationStopBehaviour, 
      bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront, bool randomStart, int randomQuality, vector<SDL_Surface*> images) : B2SAnimationBase(dual,
      interval, eType_ImageCollectionAtForm, loops, false, startTimerAtVPActivate, lightsStateAtAnimationStart, lightsStateAtAnimationEnd, animationStopBehaviour, 
      lockInvolvedLamps, hideScoreDisplays, bringToFront, randomStart, randomQuality)
{
   //Me.SynchronizingObject = _Form
   //Me.Form = _Form
   //Me.PictureBox = _Picturebox
   SetName(szName);
   //Me.ImageCollection = _ImageCollection
}

void TimerAnimation::Start()
{
   // start the base timer
   B2S::Timer::Start();
   
   RunningAnimationsCollection::GetInstance()->Add(GetName());
}