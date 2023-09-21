#pragma once

#include "../collections/RunningAnimationsCollection.h"

class B2SAnimation
{
public:
   B2SAnimation();
   virtual ~B2SAnimation();

private:
   RunningAnimationsCollection m_runningAnimations;
};