#pragma once

#include "../b2s_i.h"
#include "Timer.h"

class B2SAnimationBase : public B2S::Timer
{
public:
   B2SAnimationBase(eDualMode dual, int interval, eType type, int loops, bool playReverse, bool startMeAtVPActivate, 
      eLightsStateAtAnimationStart lightsStateAtAnimationStart, eLightsStateAtAnimationEnd lightsStateAtAnimationEnd, 
      eAnimationStopBehaviour animationStopBehaviour, bool lockInvolvedLamps, bool hideScoreDisplays, bool bringToFront,
      bool randomStart, int randomQuality);

   string GetName() const { return m_szName; }
   void SetName(const string& szName) { m_szName = szName; }

private:
   string m_szName;

   eDualMode m_dual;
   int m_interval;
   eType m_type;
   int m_loops;
   bool m_playReverse;
   bool m_startMeAtVPActivate;
   eLightsStateAtAnimationStart m_lightsStateAtAnimationStart;
   eLightsStateAtAnimationEnd m_lightsStateAtAnimationEnd;
   eAnimationStopBehaviour m_animationStopBehaviour;
   bool m_lockInvolvedLamps;
   bool m_hideScoreDisplays;
   bool m_bringToFront;
   bool m_randomStart;
   int m_randomQuality;

   int m_baseInterval;
   int m_slowDown;
   bool m_wouldBeStarted;
   bool m_stopMeLater;
};