#pragma once

#include "../b2s_i.h"

#include <map>

#include "Segment.h"
#include "../graphics/Matrix.h"

class SegmentList : public vector<Segment*>
{
public:
   void Transform(B2S::Matrix* pMatrix);
};