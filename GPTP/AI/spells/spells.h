#include <SCBW/structures/CUnit.h>

namespace AI {

CUnit* findBestLockdownTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestNukeLaunchTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestDefensiveMatrixTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestEmpShockwaveTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestIrradiateTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestYamatoGunTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestOpticalFlareTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestRestorationTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestRestorationTargetSituational(const CUnit *caster, bool isUnderAttack);

CUnit* findBestParasiteTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestEnsnareTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestSpawnBroodlingsTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestDarkSwarmTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestPlagueTarget(const CUnit *caster, bool isUnderAttack);

CUnit* findBestPsiStormTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestHallucinationTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestStasisFieldTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestRecallTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestDisruptionWebTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestFeedbackTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestMaelstromTarget(const CUnit *caster, bool isUnderAttack);
CUnit* findBestMindControlTarget(const CUnit *caster, bool isUnderAttack);

} //AI
