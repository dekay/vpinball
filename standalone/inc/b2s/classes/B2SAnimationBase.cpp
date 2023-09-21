#include "stdafx.h"

#include "B2SAnimationBase.h"

B2SAnimationBase::B2SAnimationBase(eDualMode dual, int interval, eType type, int loops, bool playReverse, bool startMeAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd, 
      eAnimationStopBehaviour animationStopBehaviour, bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront,
      bool randomStart, int randomQuality) : B2S::Timer()
{
   m_dual = dual;
   m_interval = interval;
   m_type = type;
   m_loops = loops;
   m_playReverse = playReverse;
   m_startMeAtVPActivate = startMeAtVPActivate;
   m_lightsStateAtAnimationStart = lightsStateAtAnimationStart;
   m_lightsStateAtAnimationEnd = lightsStateAtAnimationEnd;
   m_animationStopBehaviour = animationStopBehaviour;
   m_lockInvolvedLamps = lockInvolvedLamps;
   m_hideScoreDisplays = hideScoreDisplays;
   m_bringToFront = bringToFront;
   m_randomStart = randomStart;
   m_randomQuality = randomQuality;

   m_baseInterval = 0;
   m_slowDown = 1;
   m_wouldBeStarted = false;
   m_stopMeLater = false;
}
