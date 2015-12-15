#include "attack_orders.h"
#include <SCBW/api.h>
#include <logger.h>

#define WRITE_TO_LOG(x) GPTP::logger<<x<<std::endl

//helper functions def

namespace {

bool unitCanSeeCloakedTarget(CUnit* unit, CUnit* target);												//0x00401D60
u32 getUnitMovableState(CUnit* unit);																	//0x00401DC0
bool isInfestableUnit(CUnit* unit);																		//0x00402210
bool unitCanInfest(CUnit* unit);																		//0x00402750
bool isTargetWithinMinRange(CUnit* unit, CUnit* target, u32 range);										//0x00430F10
void AI_AttackUnit(CUnit* unit);																		//0x0043FFD0
CUnit* findBestAttackTarget(CUnit* unit);																//0x00443080
bool function_00462EA0(CUnit* unit, u8 unknownByteValue);												//0x00462EA0
void function_00465780(CUnit* unit);																	//0x00465780
void removeOrderFromUnitQueue(CUnit* unit);																//0x004742D0
void performAnotherOrder(CUnit* unit, u8 orderId, Point16* pos, const CUnit* target, u16 targetUnitId);	//0x004745F0
void function_00474A70(CUnit* unit, CUnit* target, u8 orderId);											//0x00474A70
void orderComputer_cl(CUnit* unit, u8 orderId); 														//0x00475310
bool isTargetWithinMinMovementRange(CUnit* unit, CUnit* target, u32 range);								//0x004763D0
bool function_00476610(CUnit* unit);																	//0x00476610
bool isUnitInWeaponRange(CUnit* unit, CUnit* target);													//0x00476870
void getWeaponBeginIscript(CUnit* unit, IscriptAnimation::Enum anim);									//0x00476ED0
void function_00477510(CUnit* unit);																	//0x00477510
void function_00477820(CUnit* unit, u8 orderId);														//0x00477820
bool function_00478370(CUnit* unit, u8 orderId);														//0x00478370
bool function_00478540(CUnit* unit);																	//0x00478540
bool isUnitCritter(CUnit* unit);																		//0x0047B450
void function_00495400(CUnit* unit, CUnit* target);														//0x00495400
u16 SAI_GetRegionIdFromPxEx(s32 x, s32 y);																//0x0049C9F0
bool isUnitVisible(CUnit* unit);																		//0x004E5DB0
bool isTargetVisible(CUnit* unit, CUnit* target);														//0x004E5E30
u8 getRightClickActionOrder(CUnit* unit);																//0x004E5EA0
void setNextWaypoint_Sub4EB290(CUnit* unit);															//0x004EB290
void makeToHoldPosition(CUnit* unit);																	//0x004EB5B0
bool moveToTarget(CUnit* unit, CUnit* target);															//0x004EB720
bool SetMoveTarget_xy(CUnit* unit, int x, int y);														//0x004EB820
bool function_004EB900(CUnit* unit, CUnit* target);														//0x004EB900
bool function_004EB9C0(CUnit* unit, int x, int y);														//0x004EB9C0

} //unnamed namespace

namespace hooks {

void orders_ReaverAttack1(CUnit* unit) {

	//WRITE_TO_LOG("orders_ReaverAttack1");

	CUnit* target = unit->orderTarget.unit;

	if(target == NULL) {

		if(unit->orderQueueHead != NULL) {
			//656A2:
			unit->userActionFlags |= 1;
			prepareForNextOrder(unit);
		}
		else {
			//656B2:
			if(unit->pAI != NULL)
				orderComputer_cl(unit,OrderId::ComputerAI);
			else
				//656C6:
				orderComputer_cl(unit,units_dat::ReturnToIdleOrder[unit->id]);
		}

	}
	else {

		//656D8:
		if(!unit->canAttackTarget(target,true))
			unit->orderTo(OrderId::Move, unit->orderTarget.pt.x, unit->orderTarget.pt.y);
		else {

			//656F7:
			u32 status_saved = (unit->status & UnitStatus::HoldingPosition) + (unit->status & UnitStatus::Disabled);
			u8 newOrderId;

			if(unit->id == UnitId::ProtossReaver || unit->id == UnitId::Hero_Warbringer) {
				//65720:
				if(unit->mainOrderId == OrderId::ReaverHold)
					newOrderId = OrderId::ReaverHold;
				else
					newOrderId = OrderId::ReaverFight;
			}
			else {
				//65730
				if(unit->mainOrderId == OrderId::HoldPosition1)
					newOrderId = OrderId::HoldPosition1;
				else
					newOrderId = OrderId::CarrierFight;
			}

			//6573E:
			function_00474A70(unit,target,newOrderId);
			prepareForNextOrder(unit);

			//new status keep initial HoldingPosition and Disabled flags, and
			//add flags set after called functions besides IsSelfDestructing
			unit->status = status_saved |= (unit->status &= ~(UnitStatus::Disabled + UnitStatus::IsSelfDestructing));

		}

	}

	//WRITE_TO_LOG("orders_ReaverAttack1 END"<<std::endl);

} //void orders_ReaverAttack1(CUnit* unit)

;

void orders_CarrierAttack1(CUnit* unit) {

	//WRITE_TO_LOG("orders_CarrierAttack1");

	CUnit* target = unit->orderTarget.unit;

	if(target == NULL) {

		if(unit->orderQueueHead != NULL) {
			//65966:
			unit->userActionFlags |= 1;
			prepareForNextOrder(unit);
		}
		else {
			//65981
			if(unit->pAI != NULL)
				orderComputer_cl(unit,OrderId::ComputerAI);
			else //65998
				orderComputer_cl(unit,units_dat::ReturnToIdleOrder[unit->id]);
		}

	}
	else {

		//659AD:
		if(!unit->canAttackTarget(target,true))
			unit->orderTo(OrderId::Move, unit->orderTarget.pt.x, unit->orderTarget.pt.y);
		else {

			//659CF
			u32 status_saved = (unit->status & UnitStatus::Disabled) + (unit->status & UnitStatus::HoldingPosition);
			u8 newOrderId;

			//give orders to the interceptors
			function_00465780(unit);

			if(unit->id == UnitId::ProtossReaver || unit->id == UnitId::Hero_Warbringer) {
				//65A03:
				if(unit->mainOrderId == OrderId::ReaverHold)
					newOrderId = OrderId::ReaverHold;
				else
					newOrderId = OrderId::ReaverFight;
			}
			else {
				//65A13:
				if(unit->mainOrderId == OrderId::HoldPosition1)
					newOrderId = OrderId::HoldPosition1;
				else
					newOrderId = OrderId::CarrierFight;
			}

			//65A21:

			function_00474A70(unit,target,newOrderId);
			prepareForNextOrder(unit);

			//new status keep initial HoldingPosition and Disabled flags, and
			//add flags set after called functions besides IsSelfDestructing
			unit->status = status_saved |= (unit->status &= ~(UnitStatus::Disabled + UnitStatus::IsSelfDestructing));

		}

	}


	//WRITE_TO_LOG("orders_CarrierAttack1 END"<<std::endl);

} //void orders_CarrierAttack1(CUnit* unit)

;


void orders_TurretAttack(CUnit* unit) {

	//WRITE_TO_LOG("orders_TurretAttack");

	CUnit* target;

	Point16 position;	//replace [EBP-0C] as global storage
	
	bool jump_to_77A45 = false;
	bool jump_to_77A70 = false;
	bool jump_to_77A9D = false;
	bool jump_to_77AFE = false;
	bool jump_to_77AB7 = false;
	bool jump_to_77CDA = false;

	//perform lots of checks, possibly in an attempt to
	//auto-select a better target if the turret has choice
	function_00477510(unit);

	target = unit->orderTarget.unit;

	if(target != NULL) {
		unit->orderTarget.pt.x = target->sprite->position.x;
		unit->orderTarget.pt.y = target->sprite->position.y;
	}

	//779AE:
	if(
		unit->status & UnitStatus::DoodadStatesThing ||
		unit->lockdownTimer != 0 ||
		unit->stasisTimer != 0 ||
		unit->maelstromTimer != 0 ||
		target == NULL ||
		target->status & UnitStatus::Invincible ||
		target->sprite->flags & CSprite_Flags::Hidden ||
		unitCanSeeCloakedTarget(unit, target)
	)
		jump_to_77A45 = true;
	else {
	
		//77A04
		CUnit* current_unit;
		bool bJumpToEarlierCode;

		if(unit->subunit->isSubunit()) 
			current_unit = unit->subunit;
		else
			current_unit = unit;

		//identical to check performed by unitIsCarrier @ 0x00401470
		if(unit->id == UnitId::ProtossCarrier || unit->id == UnitId::Hero_Gantrithor)
			jump_to_77AFE = true;
		else
		//identical to check performed by unitIsReaver @ 0x00401490, using if(!unitIsReaver())
		if(!(unit->id == UnitId::ProtossReaver || unit->id == UnitId::Hero_Warbringer))
			jump_to_77A9D = true;
		else
		if(target->status & UnitStatus::InAir)
			jump_to_77A45 = true;
		else
		if(unit->hasPathToUnit(target))
			jump_to_77AFE = true;
		else
			jump_to_77A45 = true;

		do {

			bJumpToEarlierCode = false;

			if(jump_to_77A45) {

				jump_to_77A45 = false;

				unit->userActionFlags |= 1;

				if(unit->mainOrderId == OrderId::Die)
					prepareForNextOrder(unit);	//77CED
				else {
					position.x = 0;
					position.y = 0;
					jump_to_77A70 = true;
				}

			} //if(jump_to_77A45)

			if(jump_to_77A70) {

				u8 orderProperty;
				jump_to_77A70 = false;

				while(!jump_to_77CDA && unit->orderQueueTail != NULL) {

					orderProperty = orders_dat::ordersDat_6[unit->orderQueueTail->orderId];

					if(orderProperty == 0 && unit->orderQueueTail->orderId != OrderId::TurretGuard)
						jump_to_77CDA = true;
					else
						//77A94:
						removeOrderFromUnitQueue(unit);
				}
				
				if(unit->orderQueueTail == NULL)
					jump_to_77CDA = true;

			}

			if(jump_to_77A9D) {

				//77A9D
				jump_to_77A9D = false;

				if(unitCanInfest(unit)) {

					if(isInfestableUnit(target))
						jump_to_77AFE = true;
					else {
						jump_to_77A45 = true;
						bJumpToEarlierCode = true;
					}

				}
				else
					jump_to_77AB7 = true;

			}

			if(jump_to_77AB7) {

				jump_to_77AB7 = false;

				if(unit->id == UnitId::ProtossArbiter && unit->pAI != NULL) {
					jump_to_77A45 = true;
					bJumpToEarlierCode = true;
				}
				else {

					u8 current_unit_weaponId;

					//77ACC
					if(target->status & UnitStatus::InAir)
						current_unit_weaponId = units_dat::AirWeapon[current_unit->id]; //77AD2
					else
						current_unit_weaponId = current_unit->getGroundWeapon();		//77AE6

					//77AF6
					if(current_unit_weaponId == WeaponId::None || !isTargetVisible(unit,target)) {
						jump_to_77A45 = true;
						bJumpToEarlierCode = true;
					}
					else {

						//77B0E
						CUnit* unit_holder_for_siege_tank = unit->subunit;
						bool jump_to_77BD7 = false;

						if(
							unit->id != UnitId::TerranSiegeTankTankModeTurret ||
							unit_holder_for_siege_tank->subunit->pAI == NULL ||
							unit_holder_for_siege_tank->canUseTech(TechId::TankSiegeMode,unit->playerId) ||
							!isUnitVisible(unit)
						)
							jump_to_77BD7 = true;
						else {

							//77B5F:
							u32 result_getMaxWpnRange = unit->getMaxWeaponRange(units_dat::GroundWeapon[UnitId::TerranSiegeTankSiegeModeTurret]);

							if(!isTargetWithinMinMovementRange(unit_holder_for_siege_tank,target,result_getMaxWpnRange))
								jump_to_77BD7 = true;
							else {

								//77B77:
								result_getMaxWpnRange = unit->getMaxWeaponRange(units_dat::GroundWeapon[UnitId::TerranSiegeTankTankModeTurret]);

								if(
									isTargetWithinMinMovementRange(unit_holder_for_siege_tank,target,result_getMaxWpnRange) ||
									isUnitCritter(target)
								)
									jump_to_77BD7 = true;
								else {

									orderComputer_cl(unit,OrderId::Nothing2);

									unit->order( //args based on 00474D60 __order function (which is the one calling this order)
										units_dat::AttackUnitOrder[UnitId::TerranSiegeTankSiegeModeTurret],	//hardcoded unitId param
										0,
										0,
										NULL,
										UnitId::None,
										true);

									orderComputer_cl(unit_holder_for_siege_tank,OrderId::SiegeMode);

									unit->order(	//using issueQueuedOrderTarget @ 74D10 logic
										units_dat::AttackUnitOrder[UnitId::TerranSiegeTankSiegeMode],
										target->sprite->position.x,
										target->sprite->position.y,
										target,
										UnitId::None,
										false
									);

								}

							} //if(isTargetWithinMinMovementRange(unit_holder_for_siege_tank,target,result_getMaxWpnRange))

						}

						if(jump_to_77BD7) {

							bool jump_to_77C78 = false;
							bool jump_to_77CA1 = false;

							jump_to_77BD7 = false;

							if(target != NULL) {

								if(isTargetVisible(unit,target)) {

									if(	unit->subunit != NULL && 
										units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit
									)
										current_unit = unit->subunit;
									else
										current_unit = unit;

									//77C0C:

									if(target->status & UnitStatus::InAir)
										current_unit_weaponId = current_unit->getAirWeapon();
									else
										current_unit_weaponId = current_unit->getGroundWeapon(); //include the lurker special case so it's ok

									//77C40
									if(current_unit_weaponId == WeaponId::None)
										jump_to_77C78 = true;
									else
									if(	weapons_dat::MinRange[current_unit_weaponId] != 0 &&
										isTargetWithinMinRange(current_unit, target, weapons_dat::MinRange[current_unit_weaponId])
									)
										jump_to_77C78 = true;
									else {

										//77C63:
										if(	isTargetWithinMinMovementRange(
												unit,
												target,
												unit->getMaxWeaponRange(current_unit_weaponId)
											)
										)
											jump_to_77CA1 = true;
										else
											jump_to_77C78 = true;

									}

								} //if(isTargetVisible(unit,target))
								else
									jump_to_77C78 = true;

							} //if(target != NULL)
							else
								jump_to_77CA1 = true;

							if(jump_to_77C78) {

								jump_to_77C78 = false;

								if(	unit->subunit->mainOrderId == units_dat::AttackUnitOrder[unit->subunit->id] &&
									getRightClickActionOrder(unit) != RightClickActions::NoMove_NormalAttack
								)
									jump_to_77CA1 = true;
								else
									orderComputer_cl(unit,OrderId::TurretGuard);	//77C93

							}

							if(jump_to_77CA1) {

								jump_to_77CA1 = false;

								if(	unit->orderTarget.pt.x != unit->nextTargetWaypoint.x ||
									unit->orderTarget.pt.y != unit->nextTargetWaypoint.y
								)
								{
									unit->nextTargetWaypoint.x = unit->orderTarget.pt.x;
									unit->nextTargetWaypoint.y = unit->orderTarget.pt.y;
								}

								//77CC1
								if(!(unit->subunit->movementFlags & MovementFlags::Accelerating))
									getWeaponBeginIscript(unit,IscriptAnimation::GndAttkRpt);

							}

						} //if(jump_to_77BD7)

					} //if (current_unit_weaponId != WeaponId::None && isTargetVisible(unit,target))

				} //if(unit->id != UnitId::ProtossArbiter || unit->pAI == NULL)

			}

			if(jump_to_77CDA) {

				Point16 empty_pos = {0,0};

				jump_to_77CDA = false;

				performAnotherOrder(
					unit,
					OrderId::TurretGuard,
					&empty_pos,
					target,
					UnitId::None
				);

				prepareForNextOrder(unit);

			}

		}while (bJumpToEarlierCode);

	} //If Unit Able To Fight (various conditions)


	//WRITE_TO_LOG("orders_TurretAttack END"<<std::endl);

} //void orders_TurretAttack(CUnit* unit)


;

//Could not be tested and thus is disabled in 
//attack_orders_inject.cpp
//If you find out when it's called, tell me
//UndeadStar / BoomerangAide
void orders_AttackFixedRange(CUnit* unit) {

	WRITE_TO_LOG("orders_AttackFixedRange");

	CUnit* target;

	bool jump_to_77E48 = false;
	bool jump_to_77E99 = false;

	if(unit->pAI != NULL)
		unit->orderTarget.unit = findBestAttackTarget(unit); //77D13
	else
		//perform lots of checks, possibly in an attempt to
		//auto-select a better target if the unit has choice
		function_00477510(unit); //77D1F

	//77D25:
	target = unit->orderTarget.unit;

	if(target != NULL) {
		unit->orderTarget.pt.x = target->sprite->position.x;
		unit->orderTarget.pt.y = target->sprite->position.y;
	}

	//77D42:
	if(
		unit->status & UnitStatus::DoodadStatesThing ||
		unit->lockdownTimer != 0 ||
		unit->stasisTimer != 0 ||
		unit->maelstromTimer != 0 ||
		target == NULL ||
		target->status & UnitStatus::Invincible ||
		target->sprite->flags & CSprite_Flags::Hidden ||
		unitCanSeeCloakedTarget(unit,target)
	)
		jump_to_77E48 = true;
	else {

		CUnit* current_unit;
		bool jump_to_77DEF = false;

		//77DB4:
		if(unit->subunit->isSubunit())
			current_unit = unit->subunit;
		else
			current_unit = unit;

		//77DC4:
		//identical to check performed by unitIsCarrier @ 0x00401470
		if(unit->id == UnitId::ProtossCarrier || unit->id == UnitId::Hero_Gantrithor)
			jump_to_77E99 = true;
		else
		//identical to check performed by unitIsReaver @ 0x00401490, using if(!unitIsReaver())
		if(!(unit->id == UnitId::ProtossReaver || unit->id == UnitId::Hero_Warbringer))
			jump_to_77DEF = true;
		else
		if(target->status & UnitStatus::InAir)
			jump_to_77E48 = true;
		else
		if(unit->hasPathToUnit(target))
			jump_to_77E99 = true;
		else
			jump_to_77E48 = true;

		if(jump_to_77DEF) {

			if(unitCanInfest(unit)) {
				if(isInfestableUnit(target))
					jump_to_77E99 = true;
				else
					jump_to_77E48 = true;
			}
			else {

				//77E09:
				if(unit->id == UnitId::ProtossArbiter && unit->pAI != NULL)
					jump_to_77E48;
				else {

					u8 currentWeaponId;

					//77E1A:
					if(target->status & UnitStatus::InAir)
						currentWeaponId = unit->getAirWeapon();
					else
						currentWeaponId = unit->getGroundWeapon();

					//77E44
					if(currentWeaponId != WeaponId::None)
						jump_to_77E99 = true;
					else
						jump_to_77E48 = true;

				}

			}

		}

	} //if unit able to fight (several conditions)

	if(jump_to_77E48) {

		if(unit->orderQueueHead != NULL) {
			unit->userActionFlags |= 1;
			prepareForNextOrder(unit);
		}
		else
		if(unit->pAI != NULL) //77E6B
			orderComputer_cl(unit,OrderId::ComputerAI);
		else //77E83
			orderComputer_cl(unit,units_dat::ReturnToIdleOrder[unit->id]);

	}

	if(jump_to_77E99) {

		bool jump_to_77EC8 = false;
		bool jump_to_77ED6 = false;

		if(isUnitInWeaponRange(unit,target))
			jump_to_77ED6 = true;
		else
		if(unit->pAI == NULL)
			jump_to_77EC8 = true;
		else
			unit->orderTo(OrderId::AttackMove, unit->orderTarget.pt.x, unit->orderTarget.pt.y);

		if(jump_to_77EC8)
			unit->orderToIdle();

		if(jump_to_77ED6) {

			if(	unit->orderTarget.pt.x != unit->nextTargetWaypoint.x ||
				unit->orderTarget.pt.y != unit->nextTargetWaypoint.y
			)
			{
				unit->nextTargetWaypoint.x = unit->orderTarget.pt.x;
				unit->nextTargetWaypoint.y = unit->orderTarget.pt.y;
			}

			getWeaponBeginIscript(unit,IscriptAnimation::GndAttkRpt);

		}

	}


	WRITE_TO_LOG("orders_AttackFixedRange END"<<std::endl);

} //void orders_AttackFixedRange(CUnit* unit)

;

void orders_SapUnit(CUnit* unit) {

	//WRITE_TO_LOG("orders_SapUnit");

	CUnit* target = unit->orderTarget.unit;

	if(target == NULL) { //788EB

		if(unit->orderQueueHead != NULL) {
			unit->userActionFlags |= 1;
			prepareForNextOrder(unit);
		}
		else {

			if(unit->pAI != NULL)
				orderComputer_cl(unit,OrderId::ComputerAI);
			else
				orderComputer_cl(unit,units_dat::ReturnToIdleOrder[unit->id]);
			
		} //if(unit->orderQueueHead == NULL)

	}
	else { //78928

		if(!unit->canAttackTarget(target,true))
			unit->orderTo(OrderId::Move,target->sprite->position.x,target->sprite->position.y);
		else {//7894D

			//to skip mainOrderState == 3 if the function should end,
			//but an unknown change in a subfonction could cause it
			//to try to load mainOrderState == 3 directly instead
			bool bStopThere = false;

			if(unit->mainOrderState == 0) { //78965
				if(moveToTarget(unit,target))
					unit->mainOrderState = 1;
			} //if(unit->mainOrderState == 0)
			
			if(unit->mainOrderState == 1) { //78975

				u32 unitMovableState = getUnitMovableState(unit);
				
				if(
					!isTargetWithinMinRange(unit,target,4) &&
					unitMovableState != 2
				)
				{ //78998

					if(
						isTargetWithinMinRange(unit,target,256) &&
						target->movementFlags & MovementFlags::Accelerating
					)
					{

						//maybe trigger the acceleration of the infested
						//terran, or something else related to distances?
						function_00495400(unit,target);

						bStopThere = true;

					}
					else { //789BF

						//may cause the unit to go to idle, or
						//execute and return the (unused here) 
						//result of moveToTarget @ 0x004EB720,
						//or something else
						function_004EB900(unit,target);

						bStopThere = true;

					}

				}
				else { //789CC

					setNextWaypoint_Sub4EB290(unit);

					if(!isTargetWithinMinRange
						(
							unit,
							target,
							weapons_dat::OuterSplashRadius[WeaponId::Suicide_InfestedTerran]
						)
					)
					{
						unit->orderToIdle();
						bStopThere = true;
					}
					else { //789F4

						unit->orderTarget.unit = unit;
						CImage* current_image = unit->sprite->images.head;

						while(current_image != NULL) {
							current_image->playIscriptAnim(IscriptAnimation::SpecialState1);
							current_image = current_image->link.next;
						}

						//78A11:
						unit->status |= UnitStatus::CanNotReceiveOrders;
						unit->mainOrderState = 2;

					} //if(isTargetWithinMinRange)

				} //if target reachable

			} //if(unit->mainOrderState == 1)
			
			if(!bStopThere && unit->mainOrderState == 2) { //78A1E

				if(unit->orderSignal & 1) {
					unit->status |= UnitStatus::IsSelfDestructing;
					unit->remove(); //orders_SelfDestructing
				}

			}

		} //if(unit->canAttackTarget(target,true))

	} //if(target != NULL)

	//WRITE_TO_LOG("orders_SapUnit END"<<std::endl);

} //void orders_SapUnit(CUnit* unit)

;

void orders_SapLocation(CUnit* unit) {

	//WRITE_TO_LOG("orders_SapLocation");

	bool bStopThere = false;

	if(unit->mainOrderState == 0) { //78A5C

		bStopThere = !SetMoveTarget_xy(unit,unit->orderTarget.pt.x,unit->orderTarget.pt.y);

		if(	unit->orderTarget.pt.x != unit->nextTargetWaypoint.x ||
			unit->orderTarget.pt.y != unit->nextTargetWaypoint.y
		)
		{
			unit->nextTargetWaypoint.x = unit->orderTarget.pt.x;
			unit->nextTargetWaypoint.y = unit->orderTarget.pt.y;
		}

		if(!bStopThere)
			unit->mainOrderState = 1;

	} //if(unit->mainOrderState == 0)

	if(!bStopThere && unit->mainOrderState == 1) { //78A89

		if(	unit->sprite->position.x != unit->moveTarget.pt.x ||
			unit->sprite->position.y != unit->moveTarget.pt.y
		)
			bStopThere = true;
		else { //78AA0

			if(unit->status & UnitStatus::Unmovable) { //78AB8

				u32 distance = 
					scbw::getDistanceFast(
						unit->orderTarget.pt.x * 256,
						unit->orderTarget.pt.y * 256,
						unit->halt.x,
						unit->halt.y
					);

				if((distance / 256) > weapons_dat::OuterSplashRadius[WeaponId::Suicide_InfestedTerran]) {
					unit->orderToIdle();
					bStopThere = true;
				}


			}

			if(!bStopThere) { //78AF3

				CImage* current_image = unit->sprite->images.head;

				unit->orderTarget.unit = unit;

				while(current_image != NULL) {
					current_image->playIscriptAnim(IscriptAnimation::SpecialState1);
					current_image  = current_image->link.next;
				}

				//78B10
				unit->status |= UnitStatus::CanNotReceiveOrders;
				unit->mainOrderState = 2;

			}

		}	//if unit reached target

	} //if(unit->mainOrderState == 1)

	if(!bStopThere && unit->mainOrderState == 2) { //78B1E

		if(unit->orderSignal & 1) {
			unit->status |= UnitStatus::IsSelfDestructing;
			unit->remove(); //orders_SelfDestructing
		}

	} //if(unit->mainOrderState == 2)

	//WRITE_TO_LOG("orders_SapLocation END"<<std::endl);

} //void orders_SapLocation(CUnit* unit)

;

//Could not be tested and thus is disabled in 
//attack_orders_inject.cpp
//If you find out when it's called, tell me
//UndeadStar / BoomerangAide
void orders_AttackMoveEP(CUnit* unit) {

	WRITE_TO_LOG("orders_AttackMoveEP");
	WRITE_TO_LOG("used by "<<unit->getName());

	u8 saved_mainOrderId = unit->mainOrderId; //[EBP-0x14]

	//function_00478370:
	//probably perform checks to see if the order
	//can be done, but which exactly I don't know

	if(	function_00478370(unit, unit->mainOrderId) &&
		unit->mainOrderTimer == 0
	)
	{ //78E0B

		unit->mainOrderTimer = 15;

		if(
			SAI_GetRegionIdFromPxEx(unit->getX(),unit->getY())
			==
			SAI_GetRegionIdFromPxEx(unit->orderTarget.pt.x,unit->orderTarget.pt.y)
		)
		{
			makeToHoldPosition(unit);
			unit->orderToIdle();
		}
		else { //78E65

			bool jump_to_78EAE = false;

			if(
				getUnitMovableState(unit) != 0 &&
				(unit->orderTarget.pt.x != unit->sprite->position.x ||
				 unit->orderTarget.pt.y != unit->sprite->position.y)
			)
			{ //78E80

				if(
					function_004EB9C0(				//return value is actually from 
						unit,						//SetMoveTarget_xy @ 0x004EB820
						unit->orderTarget.pt.x,
						unit->orderTarget.pt.y
					)
				)
					jump_to_78EAE = true;
				else //78E91
				if(function_00476610(unit))
					makeToHoldPosition(unit);

			}
			else
				jump_to_78EAE = true;

			if(jump_to_78EAE)
				function_00477820(unit, saved_mainOrderId);	//use attack range, may cause idle,
											//may look for target, and others...

		} //if different regions

	} //if order timer is at 0 and others order checks


	WRITE_TO_LOG("orders_AttackMoveEP END"<<std::endl);

} //void orders_AttackMoveEP(CUnit* unit)

;

void orders_AttackMove(CUnit* unit) {

	//WRITE_TO_LOG("orders_AttackMove");

	//function_00478370:
	//probably perform checks to see if the order
	//can be done, but which exactly I don't know

	if(
		function_00478370(unit,unit->mainOrderId) != 0 &&
		unit->mainOrderTimer == 0
	)
	{ //79058

		unit->mainOrderTimer = 15;

		if(
			unit->moveTarget.pt.x != unit->getX() ||
			unit->moveTarget.pt.y != unit->getY()
		)
			function_00477820(unit,unit->mainOrderId); //79092
		else
			unit->orderToIdle();

	}


	//WRITE_TO_LOG("orders_AttackMove END"<<std::endl);

} //void orders_AttackMove(CUnit* unit)

;

void orders_AttackUnit(CUnit* unit) {

	//WRITE_TO_LOG("orders_AttackUnit END");

	bool bStopThere = false;

	if(
		playerTable[unit->playerId].type != PlayerType::Computer 
		||
		(	unit->orderTarget.unit != NULL && 
			units_dat::BaseProperty[unit->orderTarget.unit->id] & UnitProperty::Building
		) 
		||
		!function_00462EA0(unit,0)	//if unit controlled by AI, do lots of things and
									//return true after/if validating a final order
	)
	{ //79C05

		//perform lots of checks, possibly in an attempt to
		//auto-select a better target if the unit has choice
		function_00477510(unit);

		//function perform tests to see if attack is possible
		//and how it should be done and return true if attack
		//can be done
		if(function_00478540(unit)) { //79C16

			if(unit->pAI != NULL)
				AI_AttackUnit(unit);

			getWeaponBeginIscript(unit,IscriptAnimation::GndAttkRpt);

		}

	}


	//WRITE_TO_LOG("orders_AttackUnit END"<<std::endl);

} //void orders_AttackUnit(CUnit* unit)

;

} //namespace hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

const u32 Func_unitCanSeeCloakedTarget = 0x00401D60;
bool unitCanSeeCloakedTarget(CUnit* unit, CUnit* target) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		PUSH unit
		MOV EAX, target
		CALL Func_unitCanSeeCloakedTarget
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

//Identical to function @ 0x00401DC0;
u32 getUnitMovableState(CUnit *unit) {
	if (unit->moveTarget.pt != unit->sprite->position)
		return 0;
	else 
	if (!(unit->status & UnitStatus::Unmovable))
		return 1;
	else
		return 2;
}

;

const u32 Func_IsInfestable = 0x00402210;
bool isInfestableUnit(CUnit *unit) {

  static Bool32 bPreResult;
  
  __asm {
    PUSHAD
    MOV EDX, unit
    CALL Func_IsInfestable
    MOV bPreResult, EAX
    POPAD
  }

  return (bPreResult != 0);

}

;

const u32 Func_CanInfest = 0x00402750;
bool unitCanInfest(CUnit* unit) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_CanInfest
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_IsTargetWithinMinRange = 0x00430F10;
bool isTargetWithinMinRange(CUnit* unit, CUnit* target, u32 range) {

	static Bool32 bResult;

	__asm {
		PUSHAD
		PUSH target
		PUSH range
		MOV ECX, unit
		CALL Func_IsTargetWithinMinRange
		MOV bResult, EAX
		POPAD
	}

	return (bResult != 0);

}

;

const u32 Func_AI_AttackUnit = 0x0043FFD0;
void AI_AttackUnit(CUnit* unit) {

	__asm {
		PUSHAD
		PUSH unit
		CALL Func_AI_AttackUnit
		POPAD
	}

}

;

const u32 Func_Sub443080 = 0x00443080;
//named according to attack_priority_inject.cpp
CUnit* findBestAttackTarget(CUnit* unit) {

	static CUnit* result;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub443080
		MOV EAX, result
		POPAD
	}

	return result;

}

;

const u32 Func_Sub462EA0 = 0x00462EA0;
bool function_00462EA0(CUnit* unit, u8 unknownByteValue) {

	static u32 _unknownByteValue = unknownByteValue;
	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EAX, unit
		PUSH _unknownByteValue
		CALL Func_Sub462EA0
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_Sub465780 = 0x00465780;
void function_00465780(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EDI, unit
		CALL Func_Sub465780
		POPAD
	}

}

;

const u32 Func_removeOrderFromUnitQueue = 0x004742D0;
void removeOrderFromUnitQueue(CUnit *unit) {

	static COrder* orderQueueHead = unit->orderQueueHead;

  __asm {
    PUSHAD
	MOV ECX, unit
	MOV EAX, orderQueueHead
	CALL Func_removeOrderFromUnitQueue
    POPAD
  }

}

;

const u32 Func_PerformAnotherOrder = 0x004745F0;
void performAnotherOrder(CUnit* unit, u8 orderId, Point16* pos, const CUnit* target, u16 targetUnitId) {

	__asm {
		PUSHAD
		PUSH target
		PUSH [pos]
		MOV BL, orderId
		MOVZX EDX, targetUnitId
		MOV ESI, unit
		XOR EDI, EDI
		CALL Func_PerformAnotherOrder
		POPAD
	}

}

;

const u32 Func_Sub474A70 = 0x00474A70;
void function_00474A70(CUnit* unit, CUnit* target, u8 orderId) {

	__asm {
		PUSHAD
		MOV CL, orderId
		MOV EDX, unit
		MOV EAX, target
		CALL Func_Sub474A70
		POPAD
	}

}

;

const u32 Func_OrderComputer_cl = 0x00475310;
void orderComputer_cl(CUnit* unit, u8 orderId) {

	__asm {
		PUSHAD
		MOV CL, orderId
		MOV ESI, unit
		CALL Func_OrderComputer_cl
		POPAD
	}

}

;

const u32 Func_isTargetWithinMinMovementRange = 0x004763D0;
bool isTargetWithinMinMovementRange(CUnit* unit, CUnit* target, u32 range) {										// EDI = unit or subunit,ECX = MaxWpnRange,EAX = target

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EDI, unit
		MOV EAX, target
		MOV ECX, range
		CALL Func_isTargetWithinMinMovementRange
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_Sub476610 = 0x00476610;
bool function_00476610(CUnit* unit) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV ESI, unit
		CALL Func_Sub476610
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_isUnitInWeaponRange = 0x00476870;
bool isUnitInWeaponRange(CUnit* unit, CUnit* target) {

	Bool32 pre_result;

	__asm {
		PUSHAD
		PUSH unit
		MOV EAX, target
		CALL Func_isUnitInWeaponRange
		MOV pre_result, EAX
		POPAD
	}

	return (pre_result != 0);

}

;

const u32 Func_getWeaponBeginIscript = 0x00476ED0;
void getWeaponBeginIscript(CUnit* unit, IscriptAnimation::Enum anim) {

	__asm {
		PUSHAD
		MOV EAX, unit
		MOV DL, anim
		CALL Func_getWeaponBeginIscript
		POPAD
	}

}

;

const u32 Func_Sub477510 = 0x00477510;
void function_00477510(CUnit* unit) {

	__asm {
		PUSHAD
		PUSH unit
		CALL Func_Sub477510
		POPAD
	}

}

;

const u32 Func_Sub477820 = 0x00477820;
void function_00477820(CUnit* unit, u8 orderId) {

	static u32 _orderId = orderId;

	__asm {
		PUSHAD
		PUSH _orderId
		MOV EAX, unit
		CALL Func_Sub477820
		POPAD
	}

}

;

const u32 Func_Sub478370 = 0x00478370;
bool function_00478370(CUnit* unit, u8 orderId) {

	static Bool32 bPreResult;
	static u32 _orderId = orderId;

	__asm {
		PUSHAD
		MOV EAX, unit
		PUSH _orderId
		CALL Func_Sub478370
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_Sub478540 = 0x00478540;
bool function_00478540(CUnit* unit) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_Sub478540
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

//Identical to Unit::isCritter() @ 0x0047B450
bool isUnitCritter(CUnit* unit) {

	bool bReturnValue;

	if(
		unit->id == UnitId::Critter_Rhynadon ||
		unit->id == UnitId::Critter_Bengalaas ||
		unit->id == UnitId::Critter_Ragnasaur ||
		unit->id == UnitId::Critter_Kakaru ||
		unit->id == UnitId::Critter_Scantid ||
		unit->id == UnitId::Critter_Ursadon
	)
		bReturnValue = true;
	else
		bReturnValue = false;

	return bReturnValue;

}

;

const u32 Func_Sub495400 = 0x00495400;
void function_00495400(CUnit* unit, CUnit* target) {

	__asm {
		PUSHAD
		MOV EDI, unit
		MOV EAX, target
		CALL Func_Sub495400
		POPAD
	}

}

;

const u32 Func_SAI_GetRegionIdFromPxEx = 0x0049C9F0;
u16 SAI_GetRegionIdFromPxEx(s32 x, s32 y) {

	static u16 result;

	__asm {
		PUSHAD
		MOV EDI, x
		MOV ECX, y
		CALL Func_SAI_GetRegionIdFromPxEx
		MOV result, AX
		POPAD
	}

	return result;

}

;

const u32 Func_isUnitVisible = 0x004E5DB0;
bool isUnitVisible(CUnit* unit) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV ESI, unit
		CALL Func_isUnitVisible
		MOV bPreResult ,EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

const u32 Func_isTargetVisible = 0x004E5E30;
bool isTargetVisible(CUnit* unit, CUnit* target) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV ESI, unit
		MOV EAX, target
		CALL Func_isTargetVisible
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);
	
}

;

//Identical to getRightClickActionOrder @ 0x004E5EA0;
u8 getRightClickActionOrder(CUnit* unit) {

	u8 result;

	if( unit->id == UnitId::ZergLurker && unit->status & UnitStatus::Burrowed )
		result = RightClickActions::NoMove_NormalAttack;
	else {

		u8 temp_result = units_dat::RightClickAction[unit->id];

		if(
			temp_result == 0 &&
			unit->status & UnitStatus::GroundedBuilding &&
			unit->isFactory()
		)
			result = RightClickActions::NormalMove_NoAttack;
		else
			result = temp_result;

	}

	return result;

}

;

//not related with assigning orders, but only with
//destinations of orders
const u32 Func_OrdersHoldPositionSuicidal = 0x004EB5B0;
void makeToHoldPosition(CUnit* unit) {

	__asm {
		PUSHAD
		MOV ESI, unit
		CALL Func_OrdersHoldPositionSuicidal
		POPAD
	}

}

;

u32 Func_moveToTarget = 0x004EB720;
bool moveToTarget(CUnit* unit, CUnit* target) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV ESI, unit
		MOV EDI, target
		CALL Func_moveToTarget
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}


;

const u32 Func_SetMoveTarget_xy = 0x004EB820;
bool SetMoveTarget_xy(CUnit* unit, int x, int y) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV ESI, unit
		MOV EBX, x
		MOV EDI, y
		CALL Func_SetMoveTarget_xy
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

//Related to path/movement decision
const u32 Func_sub_4EB290 = 0x004EB290;
void setNextWaypoint_Sub4EB290(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_sub_4EB290
		POPAD
	}
}


;

const u32 Func_Sub4EB900 = 0x004EB900;
bool function_004EB900(CUnit* unit, CUnit* target) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EAX, target
		MOV ECX, unit
		CALL Func_Sub4EB900
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}


;

const u32 Func_Sub4EB9C0 = 0x004EB9C0;
bool function_004EB9C0(CUnit* unit, int x, int y) {

	static Bool32 bPreResult;

	__asm {
		PUSHAD
		MOV EDX, unit
		MOV ECX, x
		MOV EAX, y
		CALL Func_Sub4EB9C0
		MOV bPreResult, EAX
		POPAD
	}

	return (bPreResult != 0);

}

;

} //Unnamed namespace

//End of helper functions
