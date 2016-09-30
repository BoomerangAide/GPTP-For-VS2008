//V241 for VS2008

#include "spells.h"
#include <AI/ai_common.h>

namespace AI {

//Based on AI_BestUnit @ 0x004E8740 and canHitUnit @ 0x00441870
class DarkSwarmTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

	private:

	CUnit* caster;

	//equivalent to weaponBehaviourCanHitTargetCheck @ 0x004765B0
	Bool32 weaponBehaviourCanHitTargetCheck(CUnit* attacker, CUnit* target) {

		Bool32 returnValue;

		const u32* offset_0x005873F0 = (u32*)0x005873F0;

		u8 isUnderDarkSwarmStatus;

		//code equivalent to isUnderDarkSwarm @ 0x00476210, a function different 
		//from scbw::isUnderDarkSwarm(target) that just seek a nearby 
		//Dark Swarm active spell and is used in here.

		if(target->status & UnitStatus::InAir)
			isUnderDarkSwarmStatus = 0;
		else
		if(
			(units_dat::BaseProperty[target->id] & UnitProperty::Building) ||
			(*offset_0x005873F0 == 0) ||
			!scbw::isUnderDarkSwarm(target)
		)
		{

			s32 targetX = target->getX();
			s32 targetY = target->getY();

			if(targetX < 0)
				targetX += 31;
			if(targetY < 0)
				targetY += 31;

			if(scbw::getActiveTileAt(targetX,targetY).hasDoodadCover)
				isUnderDarkSwarmStatus = OrderId::DarkSwarm; /*0x77*/
			else
				isUnderDarkSwarmStatus = 0;

		}
		else
			isUnderDarkSwarmStatus = 0xFF;

		//back to weaponBehaviourCanHitTargetCheck code

		if(attacker->status & UnitStatus::InAir)
			returnValue = isUnderDarkSwarmStatus;
		else
		if(target->status & UnitStatus::InAir)
			returnValue = isUnderDarkSwarmStatus;
		else {

			if(
				scbw::getGroundHeightAtPos(attacker->getX(),attacker->getY()) >=
				scbw::getGroundHeightAtPos(target->getX(),target->getY())
			)
				returnValue = isUnderDarkSwarmStatus;
			else
			if(isUnderDarkSwarmStatus <= OrderId::DarkSwarm)	/*code use 0x77, the order seems to fit,but maybe*/
				returnValue = OrderId::DarkSwarm;				/*that's just an accident and it's unrelated*/
			else
				returnValue = isUnderDarkSwarmStatus;

		}

		return returnValue;

	}

	public:

	DarkSwarmTargetFinderProc(CUnit* caster) : caster(caster) {}

	bool match(CUnit* target) {

		bool bReturnValue;

		if(isTargetWorthHitting(target, caster)) {

			CUnit* targetOfTarget = target->orderTarget.unit;

			if(targetOfTarget != NULL) {

				if (
					targetOfTarget->playerId < PLAYABLE_PLAYER_COUNT &&
					!caster->isTargetEnemy(targetOfTarget) &&
					targetOfTarget->subunit == NULL &&
					!(targetOfTarget->status & UnitStatus::InAir)
				)
				{
					
					u8 totGroundWeapon = targetOfTarget->getGroundWeapon();

					if(
						totGroundWeapon != WeaponId::None &&
						weapons_dat::Behavior[totGroundWeapon] == WeaponBehavior::AppearOnAttacker
					)
					{

						u8 targetGroundWeapon;

						if (target->subunit->isSubunit())
						  target = target->subunit;

						targetGroundWeapon = target->getGroundWeapon();

						if (targetGroundWeapon != WeaponId::None) {

							u8 weapon_behavior = weapons_dat::Behavior[targetGroundWeapon];

							if(
								weapons_dat::Behavior[targetGroundWeapon] == WeaponBehavior::Fly_DoNotFollowTarget ||
								weapons_dat::Behavior[targetGroundWeapon] == WeaponBehavior::Fly_FollowTarget ||
								weapons_dat::Behavior[targetGroundWeapon] == WeaponBehavior::AppearOnTargetUnit ||
								weapons_dat::Behavior[targetGroundWeapon] == WeaponBehavior::AppearOnTargetSite ||
								weapons_dat::Behavior[targetGroundWeapon] == WeaponBehavior::Bounce
							)
								bReturnValue = weaponBehaviourCanHitTargetCheck(target,targetOfTarget) == 0;
							else
								bReturnValue = false;

						}
						else
							bReturnValue = false;
						
					}
					else
						bReturnValue = false;

				}
				else
					bReturnValue = false;

			}
			else
				bReturnValue = false;

		}
		else
			bReturnValue = false;

		return bReturnValue;

		//CUnit* targetOfTarget;

		//if (!isTargetWorthHitting(target, caster))
		//  return false;

		//targetOfTarget = target->orderTarget.unit;

		//if (!targetOfTarget || targetOfTarget->playerId >= 8)
		//  return false;

		//if (caster->isTargetEnemy(targetOfTarget))
		//  return false;

		//if (targetOfTarget->subunit)
		//  return false;
	 //     
		//if (targetOfTarget->status & UnitStatus::InAir)
		//  return false;

		//u8 totGroundWeapon = targetOfTarget->getGroundWeapon();

		//if (totGroundWeapon == WeaponId::None)
		//  return false;

		//if (weapons_dat::Behavior[totGroundWeapon] != WeaponBehavior::AppearOnAttacker)
		//  return false;

		//if (target->subunit->isSubunit())
		//  target = target->subunit;

		//u8 targetGroundWeapon = target->getGroundWeapon();

		//if (targetGroundWeapon == WeaponId::None)
		//  return false;

		//switch (weapons_dat::Behavior[targetGroundWeapon]) {

		//  case WeaponBehavior::Fly_DoNotFollowTarget:
		//  case WeaponBehavior::Fly_FollowTarget:
		//  case WeaponBehavior::AppearOnTargetUnit:
		//  case WeaponBehavior::AppearOnTargetSite:
		//  case WeaponBehavior::Bounce:

		//	//Based on	weaponBehaviourCanHitTargetCheck	@ 0x004765B0 and
		//	//			isUnderDarkSwarm					@ 0x00476210

		//	if (!(targetOfTarget->status & UnitStatus::InAir)
		//		&& !(units_dat::BaseProperty[targetOfTarget->id] & UnitProperty::Building)
		//		&& scbw::isUnderDarkSwarm(targetOfTarget))
		//	  return true;

		//	//isUnderDarkSwarm @ 0x00476210 would return a positive value (0x77)
		//	if (scbw::getActiveTileAt(targetOfTarget->getX(), targetOfTarget->getY()).hasDoodadCover)
		//	  return true;

		//	if (!(targetOfTarget->status & UnitStatus::InAir || target->status & UnitStatus::InAir))
		//	{
		//	  u32 targGndHeight = scbw::getGroundHeightAtPos(target->getX(), target->getY());
		//	  u32 totGndHeight = scbw::getGroundHeightAtPos(targetOfTarget->getX(), targetOfTarget->getY());
		//	  if (targGndHeight < totGndHeight)
		//		return true;
		//	}

		//  default:
		//	return false;

		//}

	}
};

//Based on AI_AssignBestDarkSwarmTarget @ 0x00442840
CUnit* findBestDarkSwarmTarget(CUnit* caster, bool isUnderAttack) {

  int bounds;
  if (isUnderAttack)
    bounds = 32 * 9;	/*0x120*/
  else if (isUmsMode(caster->playerId))
    bounds = 32 * 64;	/*0x800*/
  else
    bounds = 32 * 32;	/*0x400*/

  //Based on AI_BestUnit @ 0x004E8740 and canHitUnit @ 0x00441870
  CUnit* result = scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
	caster, DarkSwarmTargetFinderProc(caster));

  //Specific to 0x00442840
  if ( (result != NULL) && (result->status & UnitStatus::InAir) )
    result = result->orderTarget.unit;

  return result;

}

} //AI