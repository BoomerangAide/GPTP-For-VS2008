#include "stim_packs.h"
#include "../SCBW/api.h"

namespace hooks {

void useStimPacksHook(CUnit *unit) {
  //Default StarCraft behavior
  if (unit->hitPoints > 2560) {
    scbw::playSound(scbw::randBetween(278, 279), unit);
    unit->damageHp(2560);
    if (unit->stimTimer < 37) {
      unit->stimTimer = 37;
      unit->updateSpeed();
    }
  }
}

bool canUseStimPacksHook(const CUnit *unit) {
  //Default StarCraft behavior
  return unit->hitPoints > 2560;
}

} //hooks
