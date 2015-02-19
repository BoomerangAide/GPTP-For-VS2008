#pragma once
#include "Target.h"

#pragma pack(1)

//V241 for VS2008

struct COrder {
  COrder*   prev;
  COrder*   next;
  u16       orderId;
  u16       unitId;
  Target    target;
};

C_ASSERT(sizeof(COrder) == 20);
//static_assert(sizeof(COrder) == 20, "The size of the COrder structure is invalid");

#pragma pack()
