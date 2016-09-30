#include <SCBW/structures/CUnit.h>

namespace AI {

CUnit* findBestLockdownTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestNukeLaunchTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestDefensiveMatrixTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestEmpShockwaveTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestIrradiateTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestYamatoGunTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestOpticalFlareTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestRestorationTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestRestorationTargetSituational(CUnit* caster, bool isUnderAttack);

CUnit* findBestParasiteTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestEnsnareTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestSpawnBroodlingsTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestDarkSwarmTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestPlagueTarget(CUnit* caster, bool isUnderAttack);

CUnit* findBestPsiStormTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestHallucinationTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestStasisFieldTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestRecallTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestDisruptionWebTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestFeedbackTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestMaelstromTarget(CUnit* caster, bool isUnderAttack);
CUnit* findBestMindControlTarget(CUnit* caster, bool isUnderAttack);

} //AI
