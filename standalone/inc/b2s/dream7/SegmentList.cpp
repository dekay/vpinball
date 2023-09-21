#include "stdafx.h"

#include "SegmentList.h"

void SegmentList::Transform(B2S::Matrix* pMatrix)
{
   for (auto& pSegment : *this)
      pSegment->Transform(pMatrix);
}
