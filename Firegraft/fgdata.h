#define USE_FIREGRAFT_EXE_EDITS

#ifdef USE_FIREGRAFT_EXE_EDITS

/*************************************************/
/* This file contains pointers to constants that */
/*    can be defined in Firegraft Exe Edits.     */
/* Replacing the hardcoded values in GPTP files  */
/*  by a reference to those constants allow you  */
/*      to use values defined in Firegraft       */
/*************************************************/

//This is based on the 1161.fgd available in my version of
//Firegraft, that has 2222 entries.
//I initially started this file basing myself on 
//http://broodwarai.com/wiki/index.php?title=Fgraft.1161.fgd
//but that one only had 1754 entries, so I started updating
//this file according to the changes.

#pragma once
#include "../definitions.h"
#include "structures.h"

#define FG_SCBW_DATA(type, name, offset) type const name = (type)offset;

//base adress : 0x400000, added to offsets in fgraft.1161.fgd to get the proper offset

namespace Firegraft_Offsets {

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Starting Units / Starting Buildings
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 0
//Use UnitId::enum for values
//Default value: 131 (UnitId::ZergHatchery)
FG_SCBW_DATA(const u8*,	startingBuildingZerg,									0x0049d7e1);

//Entry 1
//Use UnitId::enum for values
//Default value: 106 (UnitId::TerranCommandCenter)
FG_SCBW_DATA(const u8*,	startingBuildingTerran,									0x0049d7dd);

//Entry 2
//Use UnitId::enum for values
//Default value: 154 (UnitId::ProtossNexus)
FG_SCBW_DATA(const u8*,	startingBuildingProtoss,								0x0049d7d9);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Starting Units / Starting Workers
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 3
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, startingWorkersZergWorker1,								0x0049dada);

//Entry 4
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, startingWorkersZergWorker2,								0x0049db3d);

//Entry 5
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, startingWorkersZergWorker3,								0x0049db8a);

//Entry 6
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, startingWorkersZergWorker4,								0x0049dbd7);

//Entry 7
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, startingWorkersZergTeamWorker,							0x0049d9e4);

//Entry 8
//Use UnitId::enum for values
//Default value: 7 (UnitId::TerranSCV)
FG_SCBW_DATA(const u8*, startingWorkersTerranWorker1,							0x0049dad6);

//Entry 9
//Use UnitId::enum for values
//Default value: 7 (UnitId::TerranSCV)
FG_SCBW_DATA(const u8*, startingWorkersTerranWorker2,							0x0049db39);

//Entry 10
//Use UnitId::enum for values
//Default value: 7 (UnitId::TerranSCV)
FG_SCBW_DATA(const u8*, startingWorkersTerranWorker3,							0x0049db86);

//Entry 11
//Use UnitId::enum for values
//Default value: 7 (UnitId::TerranSCV)
FG_SCBW_DATA(const u8*, startingWorkersTerranWorker4,							0x0049dbd3);

//Entry 12
//Use UnitId::enum for values
//Default value: 7 (UnitId::TerranSCV)
FG_SCBW_DATA(const u8*, startingWorkersTerranTeamWorker,						0x0049d9e0);

//Entry 13
//Use UnitId::enum for values
//Default value: 64 (UnitId::ProtossProbe)
FG_SCBW_DATA(const u8*, startingWorkersProtossWorker1,							0x0049dad2);

//Entry 14
//Use UnitId::enum for values
//Default value: 64 (UnitId::ProtossProbe)
FG_SCBW_DATA(const u8*, startingWorkersProtossWorker2,							0x0049db35);

//Entry 15
//Use UnitId::enum for values
//Default value: 64 (UnitId::ProtossProbe)
FG_SCBW_DATA(const u8*, startingWorkersProtossWorker3,							0x0049db82);

//Entry 16
//Use UnitId::enum for values
//Default value: 64 (UnitId::ProtossProbe)
FG_SCBW_DATA(const u8*, startingWorkersProtossWorker4,							0x0049dbcf);

//Entry 17
//Use UnitId::enum for values
//Default value: 64 (UnitId::ProtossProbe)
FG_SCBW_DATA(const u8*, startingWorkersProtossTeamWorker,						0x0049d9dc);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Starting Units / Starting Zerg Units
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 18
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u8*, startingZergUnitsCreate1,								0x0049d682);

//Entry 19
//Use UnitId::enum for values
//Default value: 42 (UnitId::ZergOverlord)
FG_SCBW_DATA(const u8*, startingZergUnitsCreate2,								0x0049d728);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Supply
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 20
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyIndividualMaximumSupply,							0x00488fc7);

//Entry 21
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamMinimumSupply,								0x00488ff5);

//Entry 22
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyCheckMultiplierZerg,					0x00489022);

//Entry 23
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyMultiplierZerg,						0x0048903c);

//Entry 24
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyCheckMultiplierTerran,					0x0048905b);

//Entry 25
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyMultiplierTerran,						0x00489075);

//Entry 26
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyCheckMultiplierProtoss,				0x0048908d);

//Entry 27
//Default value is 400
//It is the double of the value displayed ingame
FG_SCBW_DATA(const u16*, supplyTeamSupplyMultiplierProtoss,						0x004890a7);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Peons / Resource Harvesting
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 29
//If a resource field has less than this, all the remaining 
//resources will be returned.  Gas mines will become depleted, 
//and mineral patches will be removed.
//Default value is 8
FG_SCBW_DATA(const u16*, resourceHarvestingCheckForDepleted,					0x0046965e);

//Entry 30
//The amount by which a resource field is reduced(added, since 
//the value is negative) when mining from it.
//This value is independent of how much minerals/gas is actually 
//returned by a "normal" resource chunk.
//Default value is -8
FG_SCBW_DATA(const u8*, resourceHarvestingFieldReduceValue,						0x00469664);

//Entry 31
//The amount of minerals returned from a mineral patch, 
//if it has more minerals than the field reduce value.
//Default value is 8
FG_SCBW_DATA(const u8*, resourceHarvestingMineralReturnedNormal,				0x0046967d);

//Entry 32
//The amount of minerals returned from a mineral patch, 
//if it has exactly the same amount of minerals as the 
//field reduce value.
//Default value is 8
FG_SCBW_DATA(const u8*, resourceHarvestingMineralReturnedAlmostDepleted,		0x00469688);

//Entry 33
//If (stored gas) - (field reduce value) is less than 
//this value, StarCraft issues the "gas depleted" message 
//with a sound effect. This is purely aesthetic and does 
//not affect the gameplay.
//Default value is 8
FG_SCBW_DATA(const u8*, resourceHarvestingGasDepletedCheck,						0x0046968d);

//Entry 34
//The amount of gas returned from a normal gas building.
//Default value is 8
FG_SCBW_DATA(const u8*, resourceHarvestingGasReturnedNormal,					0x004696a9);

//Entry 35
//The amount of resources per depleted gas container.
//Default value is 2
FG_SCBW_DATA(const u8*, resourceHarvestingGasReturnedDepleted,					0x004696c9);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Unit Morph / Command
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 41
//Use UnitId::enum for values
//Default value: 38 (UnitId::ZergHydralisk)
FG_SCBW_DATA(const u8*, unitMorphCommandCheckHydralisk,							0x004c19b6);

//Entry 42
//Use UnitId::enum for values
//Default value: 103 (UnitId::ZergLurker)
FG_SCBW_DATA(const u8*, unitMorphCommandCheckLurker,							0x004c19c1);

//Entry 43
//Use TechId::enum for values
//Default value: 32 (TechId::LurkerAspect)
FG_SCBW_DATA(const u8*, unitMorphCommandCheckTechLurker,						0x004c19cd);

//Entry 44
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u8*, unitMorphCommandCheckLarva,								0x004c19da);

//Entry 45
//Use UnitId::enum for values
//Default value: 43 (UnitId::ZergMutalisk)
FG_SCBW_DATA(const u8*, unitMorphCommandCheckMutalisk,							0x004c19e0);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Unit Morph / Order
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 47
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u8*, unitMorphOrderCheckLarva,								0x0045dfb6);

//Entry 48
//Use UnitId::enum for values
//Default value: 38 (UnitId::ZergHydralisk)
FG_SCBW_DATA(const u8*, unitMorphOrderCheckHydralisk,							0x0045dfbc);

//Entry 49
//Use UnitId::enum for values
//Default value: 43 (UnitId::ZergMutalisk)
FG_SCBW_DATA(const u8*, unitMorphOrderCheckMutalisk,							0x0045dfc2);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Unit Morph / OrderUnitToCocoon
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 50
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u8*, unitMorphOrderUnitToCocoonCheckLarva,					0x0045e028);

//Entry 51
//Use UnitId::enum for values
//Default value: 38 (UnitId::ZergHydralisk)
FG_SCBW_DATA(const u8*, unitMorphOrderUnitToCocoonCheckHydralisk,				0x0045e038);

//Entry 52
//Use UnitId::enum for values
//Default value: 43 (UnitId::ZergMutalisk)
FG_SCBW_DATA(const u8*, unitMorphOrderUnitToCocoonCheckMutalisk,				0x0045e042);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Unit Morph / Cancel
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 53
//Use UnitId::enum for values (even if it's expecting a signed value)
//Default value: 43 (UnitId::ZergMutalisk)
FG_SCBW_DATA(const s8*, unitMorphCancelCocoonMutalisk,							0x00468399);

//Entry 54
//Use UnitId::enum for values (even if it's expecting a signed value)
//Default value: 38 (UnitId::ZergHydralisk)
FG_SCBW_DATA(const s8*, unitMorphCancelLurkerEggHydralisk,						0x0046839d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Building Morph / Command
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 55
//Use UnitId::enum for values
//Default value: 130 (UnitId::ZergInfestedCommandCenter)
FG_SCBW_DATA(const u8*, buildingMorphCommandLowerIdBoundOriginal,				0x004c1935);

//Entry 56
//Use UnitId::enum for values
//Default value: 152 (UnitId::Special_CerebrateDaggoth)
FG_SCBW_DATA(const u8*, buildingMorphCommandUpperIdBoundOriginal,				0x004c193b);

//Entry 57
//Use UnitId::enum for values
//Default value: 130 (UnitId::ZergInfestedCommandCenter)
FG_SCBW_DATA(const u8*, buildingMorphCommandLowerIdBoundMorph,					0x004c1947);

//Entry 58
//Use UnitId::enum for values
//Default value: 152 (UnitId::Special_CerebrateDaggoth)
FG_SCBW_DATA(const u8*, buildingMorphCommandUpperIdBoundMorph,					0x004c194d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Create Unit / Building Morph / Cancel
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 63
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, buildingMorphCancelExtractorUnit,						0x0045daf4);

//Entry 64
//Use UnitId::enum for values
//Default value: 41 (UnitId::ZergDrone)
FG_SCBW_DATA(const u8*, buildingMorphCancelNonExtractorUnit,					0x0045db86);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / HP Regeneration
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 65
//Default value: 4
FG_SCBW_DATA(const s8*, hpRegenerationRate,										0x004ec386);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / Larva Spawn
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 68
//The value that is compared against the count of larva (see count maximum) 
//to determine if more larva should be spawned.
//Default value: 3
FG_SCBW_DATA(const u8*, larvaSpawnCompareMaximum,								0x004ea7ee);

//Entry 69
//The maximum number of larva that are counted for each building.
//Default value: 3
FG_SCBW_DATA(const u8*, larvaSpawnCountMaximum,									0x004e8ca5);

//Entry 70
//Default value: 37
FG_SCBW_DATA(const u8*, larvaSpawnSpawnTimer,									0x004ea81a);

//Entry 71
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u8*, larvaSpawnCreatedUnitID,								0x004ea83d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / Creep Spawn
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 72
//Default value: 15
FG_SCBW_DATA(const u8*, creepSpawnSpawnTimer,									0x004ea8bf);

//Entry 73
//Default value: 133
FG_SCBW_DATA(const u16*, creepSpawnCreepRange,									0x004ea8cf);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / Building Redzone Burn
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 74
//Default value: 33
FG_SCBW_DATA(const u8*, buildingBurningRedzoneBurnBurnPercentCheck,				0x004022ff);

//Entry 75
//Default value: 20
FG_SCBW_DATA(const s32*, buildingBurningRedzoneBurnDamagePerCycle,				0x004ec405);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Ground / Nuclear Strike / Remove nuke timer
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 77
//This timer is how long before the nuke is hidden during the strike.
//Default value: 90
FG_SCBW_DATA(const u8*, nuclearStrikeRemoveNukeTimer,							0x00464785);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / Shield Regeneration / Shield Points per cycle
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 78
//Default value: 7
FG_SCBW_DATA(const s8*, shieldRegenerationPointsPerCycle,						0x004ec2e5);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Ground / Recharge Shields / Recharge amount per cycle
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 79
//Divide this value by 256 to get the in-game shield points.
//Default value: 1280
FG_SCBW_DATA(const s32*, rechargeShieldsRechargeAmountPerCycle,					0x004934c7);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Ground / Recharge Shields / Energy amount per cycle
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 80
//Divide this value by 256 to get the in-game energy amount.
//Default value: 640
FG_SCBW_DATA(const s32*, rechargeShieldsEnergyAmountPerCycle,					0x004934ce);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Stimpack
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 81
//Default value: 10
FG_SCBW_DATA(const u8*, stimpackActionHpCheck,									0x004234db);

//Entry 82
//Default value: 10
FG_SCBW_DATA(const u8*, stimpackCommandHpCheck,									0x004c2f6c);

//Entry 83
//Default value: 10
FG_SCBW_DATA(const u16*, stimpackCommandHpSubtracted,							0x004c2fd6);

//Entry 84
//Default value: 37
FG_SCBW_DATA(const u8*, stimpackTimer,											0x004c2fe7);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Lockdown
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 85
//Default value: 131
FG_SCBW_DATA(const u8*, lockdownTimer,											0x0048b92b);

//Entry 86
//Use ImageId::enum for values
//Default value: 361 (ImageId::LockdownField_Small)
FG_SCBW_DATA(const u32*, lockdownImagesDatOverlayStart,							0x004553c4);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Spidermines
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 87
//Default value: 3
FG_SCBW_DATA(const u8*, spiderminesInitialCount,								0x004a0681);

//Entry 88
//Use UnitId::enum for values
//Default value: 13 (UnitId::TerranVultureSpiderMine)
FG_SCBW_DATA(const u8*, spiderminesSpaceCheckID,								0x00465127);

//Entry 89
//Use UnitId::enum for values
//Default value: 13 (UnitId::TerranVultureSpiderMine)
FG_SCBW_DATA(const u8*, spiderminesCreatedUnitId,								0x00465146);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Scanner
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 90
//Use UnitId::enum for values
//Default value: 33 (UnitId::Spell_ScannerSweep)
FG_SCBW_DATA(const u8*, scannerOrderSpaceCheckID,								0x00464f41);

//Entry 91
//Use UnitId::enum for values
//Default value: 33 (UnitId::Spell_ScannerSweep)
FG_SCBW_DATA(const u8*, scannerOrderCreatedUnitId,								0x00464f60);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Siege Mode Requirement
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 92
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeInTankModeRequirementUnit1,					0x004291ec);

//Entry 93
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeInTankModeRequirementUnit2,					0x004291f2);

//Entry 94
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeTankMoveRequirementUnit1,						0x00428871);

//Entry 95
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeTankMoveRequirementUnit2,						0x00428877);

//Entry 96
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeInSiegeModeRequirementUnit1,					0x0042919c);

//Entry 97
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeInSiegeModeRequirementUnit2,					0x004291a2);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Siege Mode Command
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 98
//Use UnitId::enum for values
//Default value: 5 (UnitId::TerranSiegeTankTankMode)
FG_SCBW_DATA(const u8*, siegeModeCommandSiegeModeUnit1,							0x004c1ea6);

//Entry 99
//Use UnitId::enum for values
//Default value: 23 (UnitId::Hero_EdmundDukeTankMode)
FG_SCBW_DATA(const u8*, siegeModeCommandSiegeModeUnit2,							0x004c1eac);

//Entry 100
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeCommandTankModeUnit1,							0x004c1f36);

//Entry 101
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeCommandTankModeUnit2,							0x004c1f3c);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Siege Mode Order / Unit Check
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 102
//Use UnitId::enum for values
//Default value: 5 (UnitId::TerranSiegeTankTankMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitCheckTankUnit1,						0x00464bec);

//Entry 103
//Use UnitId::enum for values
//Default value: 23 (UnitId::Hero_EdmundDukeTankMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitCheckTankUnit2,						0x00464bf2);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Siege Mode Order / Unit Change
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 104
//Use UnitId::enum for values
//Default value: 5 (UnitId::TerranSiegeTankTankMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitChangeTankUnit1,						0x00463315);

//Entry 105
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitChangeSiegeUnit1,						0x00463324);

//Entry 106
//Use UnitId::enum for values
//Default value: 23 (UnitId::Hero_EdmundDukeTankMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitChangeTankUnit2,						0x0046331a);

//Entry 107
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, siegeModeOrderUnitChangeSiegeUnit2,						0x0046331f);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Tank Mode Order / Unit Check
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 108
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitCheckSiegeUnit1,						0x00464b02);

//Entry 109
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitCheckSiegeUnit2,						0x00464b08);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Tank Mode Order / Unit Change
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 110
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitChangeSiegeUnit1,						0x00464b9e);

//Entry 111
//Use UnitId::enum for values
//Default value: 5 (UnitId::TerranSiegeTankTankMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitChangeTankUnit1,						0x00464ba2);

//Entry 112
//Use UnitId::enum for values
//Default value: 25 (UnitId::Hero_EdmundDukeSiegeMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitChangeSiegeUnit2,						0x00464b99);

//Entry 113
//Use UnitId::enum for values
//Default value: 23 (UnitId::Hero_EdmundDukeTankMode)
FG_SCBW_DATA(const u8*, tankModeOrderUnitChangeTankUnit2,						0x00464ba9);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Defensive Matrix
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 114
//Use ImageId::enum for values
//Default value: 371 (ImageId::DefensiveMatrixFront_Small)
FG_SCBW_DATA(const u16*, defensiveMatrixImagesDatOverlayStart,					0x00454fd7);

//Entry 115
//Use ImageId::enum for values
//Default value: 374 (ImageId::DefensiveMatrixBack_Small)
FG_SCBW_DATA(const u16*, defensiveMatrixImagesDatUnderlayStart,					0x00454feb);

//Entry 116
//Default value: 64000
//Divide by 256 for ingame HP equivalent (250 HP for default value)
FG_SCBW_DATA(const u16*, defensiveMatrixDamageAmount,							0x00454ffd);

//Entry 117
//Default value: 168
FG_SCBW_DATA(const u8*, defensiveMatrixTimer,									0x00455005);

//Entry 118
//Use ImageId::enum for values
//Default value: 539 (ImageId::ScienceVesselOverlay_Part2)
FG_SCBW_DATA(const u16*, defensiveMatrixCasterImagesDatOverlay,					0x00455109);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Irradiate
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 119
//Use ImageId::enum for values
//Default value: 380 (ImageId::Irradiate_Small)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayStart,						0x00454e49);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Cloak / Energy Decrease
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 128
//Energy amount subtracted each cycle for Cloaking Field.  
//This value is interpreted as 1/255 of an energy point.
//Default value: 13
FG_SCBW_DATA(const u16*, cloakEnergyDecreaseCloakingField,						0x00491ac6);

//Entry 129
//Energy amount subtracted each cycle for Personnel Cloaking.
//This value is interpreted as 1/255 of an energy point.
//Default value: 10
FG_SCBW_DATA(const u16*, cloakEnergyDecreasePersonnelCloaking,					0x00491acf);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Infestation
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 133
//Use UnitId::enum for values
//Unit which can be infested.  ID must be less than 128.
//Default value: 106 (UnitId::TerranCommandCenter)
FG_SCBW_DATA(const s8*, infestationInfestableUnit,								0x0040221d);

//Entry 134
//Default value: 50
FG_SCBW_DATA(const s8*, infestationDamagedPercent,								0x00402259);

//Entry 135
//Timer for the length of time the queen is 'inside' the target.
//Default value: 60
FG_SCBW_DATA(const u16*, infestationQueenHideTimer,								0x004ea36f);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Spawn Broodlings
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 136
//Default value: 2
FG_SCBW_DATA(const u8*, spawnBroodlingsCreateCount,								0x004f4973);

//Entry 137
//Use UnitId::enum for values
//Default value: 40 (UnitId::ZergBroodling)
FG_SCBW_DATA(const u8*, spawnBroodlingsSpaceCheckID,							0x004f49eb);

//Entry 138
//Use UnitId::enum for values
//Default value: 40 (UnitId::ZergBroodling)
FG_SCBW_DATA(const u8*, spawnBroodlingsCreateUnitID,							0x004f4a0a);

//Entry 139
//The energy the unit starts with.  
//This value is 10 times the displayed energy.
//Default value: 1800
FG_SCBW_DATA(const u16*, spawnBroodlingsInitialEnergy,							0x004f4a53);

//Entry 140
//This number is the maximum energy(multiplied by 10), 
//which is shown in the status area.
//Default value: 1800
FG_SCBW_DATA(const u16*, spawnBroodlingsEnergyDisplayMaximum,					0x00425ae4);

//Entry 141
//This number is the maximum energy(times by 10) used to 
//determine how to display the status bar's energy.
//Default value: 1800
FG_SCBW_DATA(const u16*, spawnBroodlingsEnergyStatbarMaximum,					0x0047aa2a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Dark Swarm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 142
//Use UnitId::enum for values
//Default value: 202 (UnitId::Spell_DarkSwarm)
FG_SCBW_DATA(const u8*, darkSwarmSpaceCheckID,									0x004f48b1);

//Entry 143
//Use UnitId::enum for values
//Default value: 202 (UnitId::Spell_DarkSwarm)
FG_SCBW_DATA(const u8*, darkSwarmCreateUnitID,									0x004f48cd);

//Entry 144
//If the timer is higher than this value,
//it is reset to the timer value.
//Default value: 900
FG_SCBW_DATA(const u16*, darkSwarmTimerCheck,									0x004f491f);

//Entry 145
//Default value: 900
FG_SCBW_DATA(const u16*, darkSwarmTimer,										0x004f492a);

//Entry 146
//Use UnitId::enum for values
//This is the Unit ID which provides protection
//from ranged weapons.
//Default value: 202 (UnitId::Spell_DarkSwarm)
FG_SCBW_DATA(const u8*, darkSwarmRangeProtectionId,								0x0047624d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Plague
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 148
//Use ImageId::enum for values
//Default value: 388 (ImageId::PlagueOverlay_Small)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayStart,							0x004f4596);

//Entry 149
//Default value: 75
FG_SCBW_DATA(const u8*, plagueTimer,											0x004f45a6);

/////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Consume
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 151
//Amount of energy regained by consuming a unit.
//Default value: 50
FG_SCBW_DATA(const u8*, consumeEnergyGain,										0x004f4805);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Ensnare
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 152
//Use SpriteId::enum for values
//Default value: 364 (SpriteId::Ensnare)
FG_SCBW_DATA(const u16*, ensnareExplosionIdSpritesDat,							0x004f4840);

//Entry 153
//Units that pass this flag check are not Ensnared. 
//The default value is 0x4000000 (invincible units).
//Default value: 67108864 (also 0x4000000 or UnitStatus::Invincible)
FG_SCBW_DATA(const u32*, ensnareExclusionFlagCheck1Status,						0x004f46d9);

//Entry 154
//Use ImageId::enum for values
//Default value: 384 (ImageId::EnsnareOverlay_Small)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayStart,							0x004f4626);

//Entry 155
//Default value: 75
FG_SCBW_DATA(const u8*, ensnareTimer,											0x004f4636);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Hallucination
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 156
//Default value: 2
FG_SCBW_DATA(const u8*, hallucinationCreateCount,								0x004f6c6d);

//Entry 157
//The energy the unit starts with.  
//This value is 10 times the displayed energy.
//Default value: 1350
FG_SCBW_DATA(const u16*, hallucinationInitialEnergy,							0x004f6be3);

//Entry 158
//This number is the maximum energy(multiplied by 10), 
//which is shown in the status area.
//Default value: 1350
FG_SCBW_DATA(const u16*, hallucinationEnergyDisplayMaximum,						0x00425ad4);

//Entry 159
//This number is the maximum energy(times by 10) used to 
//determine how to display the status bar's energy.
//Default value: 1350
FG_SCBW_DATA(const u16*, hallucinationEnergyStatbarMaximum,						0x0047aa1a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Recall
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 162
//Use SpriteId::enum for values
//The sprites.dat id created at the casting location.
//Default value: 379 (SpriteId::Recall_Field)
FG_SCBW_DATA(const u16*, recallBeginRecallFieldIDSpritesDat,					0x004945f5);

//Entry 163
//Use SpriteId::enum for values
//The sprites.dat id created on top of the destination for each unit.
//Default value: 379 (SpriteId::Recall_Field)
FG_SCBW_DATA(const u16*, recallUnitTranportFieldIDSpritesDat,					0x00494384);

//Entry 164
//The amount of time between when the sprite is created and 
//when the units are moved.
//Default value: 22
FG_SCBW_DATA(const u8*, recallTimer,											0x00494677);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Stasis Field
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 165
//Use SpriteId::enum for values
//Default value: 361 (SpriteId::Stasis_Field_Hit)
FG_SCBW_DATA(const u16*, stasisFieldExplosionIdSpritesDat,						0x004f6a90);

//Entry 166
//Default value: 131
FG_SCBW_DATA(const u8*, stasisFieldTimer,										0x004f68f5);

//Entry 167
//Use ImageId::enum for values
//Default value: 365 (ImageId::StasisField_Small)
FG_SCBW_DATA(const u32*, stasisFieldImagesDatOverlayStart,						0x004f67f4);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Archon Warp
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 168
//Use UnitId::enum for values
//Default value: 67 (UnitId::ProtossHighTemplar)
FG_SCBW_DATA(const u8*, archonWarpCommandUnitCheck,								0x004c0ed9);

//Entry 170
//Use UnitId::enum for values
//The ID of the unit to be merged.  Must be less than 128.
//Default value: 68 (UnitId::ProtossArchon)
FG_SCBW_DATA(const s8*, archonWarpOrderMergeUnitId,								0x004949c6);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Restoration
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 171
//Use ImageId::enum for values
//Default value: 967 (ImageId::RestorationHit_Small)
FG_SCBW_DATA(const u16*, restorationImagesDatOverlayStart,						0x00455277);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Disruption Web
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 172
//Use UnitId::enum for values
//Default value: 105 (UnitId::Spell_DisruptionWeb)
FG_SCBW_DATA(const u8*, disruptionWebSpaceCheckID,								0x004f6b01);

//Entry 173
//Use UnitId::enum for values
//Default value: 105 (UnitId::Spell_DisruptionWeb)
FG_SCBW_DATA(const u8*, disruptionWebCreateUnitID,								0x004f6b1d);

//Entry 174
//Default value: 360
FG_SCBW_DATA(const u16*, disruptionWebTimerCheck,								0x004f6b6f);

//Entry 175
//Default value: 360
FG_SCBW_DATA(const u16*, disruptionWebTimer,									0x004f6b7a);

//Entry 176
//Default value: 105 (UnitId::Spell_DisruptionWeb)
FG_SCBW_DATA(const u8*, disruptionWebDisableGroundAttackId,						0x004eb3fd);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Mind Control
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 178
//Use ImageId::enum for values
//Default value: 973 (ImageId::MindControlHit_Small)
FG_SCBW_DATA(const u16*, mindControlImagesDatOverlayStart,						0x004f6a15);

//Entry 179
//Units that pass this flag check cannot be Mind Controlled. 
//By default, this includes buildings (0x1) (compared with 
//units_dat::BaseProperty[unit->id])
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u8*, mindControlExclusionFlagCheckUnitPrototype,				0x00491eef);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Self / Dark Archon Meld
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 181
//Use UnitId::enum for values
//Default value: 61 (UnitId::ProtossDarkTemplar)
FG_SCBW_DATA(const u8*, darkArchonMeldCommandUnitCheck,							0x004c0d19);

//Entry 183
//Use UnitId::enum for values
//Default value: 63 (UnitId::ProtossDarkArchon)
FG_SCBW_DATA(const s8*, darkArchonMeldOrderMeldUnitId,							0x004947a6);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Feedback
////////////////////////////////////////////////////////////////////////////////////////////////

Entry 184
Use SpriteId::enum for values
Same as feedbackImagesDatOverlayStart, but in case
Firegraft get fixed, it will be easier to find the
data with this additionnal link.
Default value: 500 (SpriteId::Feedback_Hit_Small)
FG_SCBW_DATA(const u16*, feedbackSpritesDatOverlayStart,						0x004f6e76);
		       //feedbackImagesDatOverlayStart,

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Optical Flare
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 185
//Use ImageId::enum for values
//Default value: 976 (ImageId::OpticalFlareHit_Small)
FG_SCBW_DATA(const u16*, opticalFlareImagesDatOverlayStart,						0x004551e9);

//Entry 186
//Blinded sight range.  As with the sight ranges in units.dat, 
//this cannot be above 11 unless using ExtendSightLimit.
//Default value: 2
FG_SCBW_DATA(const u16*, opticalFlareBlindedSightRange,							0x004e5b77);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Maelstrom
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 187
//Use SpriteId::enum for values
//Default value: 514 (SpriteId::Maelstrom_Hit)
FG_SCBW_DATA(const u16*, maelstromExplosionIdSpritesDat,						0x004f6862);

//Entry 188
//Default value: 22
FG_SCBW_DATA(const s8*, maelstromTimer,											0x004f67a3);

//Entry 189
//Use ImageId::enum for values
//Default value: 982 (ImageId::MaelstromOverlay_Small)
FG_SCBW_DATA(const u32*, maelstromImagesDatOverlayStart,						0x00455434);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Heal
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 191
//This value divided by 255 is ingame hitpoints.
//Default value: 200
FG_SCBW_DATA(const u16*, healTechHitpointCheck,									0x00463cd4);

//Entry 192
//This value divided by 255 is ingame hitpoints.
//Default value: 200
FG_SCBW_DATA(const u16*, healTechHitpointGain,									0x00463cdb);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Self / Cloaking Nearby Units
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 193
//Use UnitId::enum for values
//Default value: 71 (UnitId::ProtossArbiter)
FG_SCBW_DATA(const u8*, cloakNearbyUnitsUncloakableUnit1,						0x00491cd6);

//Entry 194
//Use UnitId::enum for values
//Default value: 86 (UnitId::Hero_Danimoth)
FG_SCBW_DATA(const u8*, cloakNearbyUnitsUncloakableUnit2,						0x00491cdc);

//Entry 195
//Use UnitId::enum for values
//Default value: 14 (UnitId::TerranNuclearMissile)
FG_SCBW_DATA(const u8*, cloakNearbyUnitsUncloakableUnit3,						0x00491d02);

////////////////////////////////////////////////////////////////////////////////////////////////
///Orders / Target / Attack / Medic Attack/Attack Move order
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 197
//Orders.dat ID for the medic to run for attack and attack move.  
//This is why heal is it's attack also.
//Default value: 177 (OrderId::HealMove)
FG_SCBW_DATA(const u8*, medicAttackMoveOrder,									0x0049ac0c);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / U-238 Shells
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 200
//Default value: 1
FG_SCBW_DATA(const u8*, u238shellsAquireRangeIncrease,							0x00476071);

//Entry 201
//Default value: 32
FG_SCBW_DATA(const s8*, u238shellsAttackRangeIncrease,							0x004758be);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Grooved Spines
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 202
//Default value: 1
FG_SCBW_DATA(const u8*, groovedSpinesAquireRangeIncrease,						0x00476093);

//Entry 203
//Default value: 32
FG_SCBW_DATA(const s8*, groovedSpinesAttackRangeIncrease,						0x004758df);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Singularity Charge
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 204
//Default value: 2
FG_SCBW_DATA(const u8*, singularityChargeAquireRangeIncrease,					0x004760b5);

//Entry 205
//Default value: 64
FG_SCBW_DATA(const s8*, singularityChargeAttackRangeIncrease,					0x00475919);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Singularity Charge Hero
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 206
//Default value: 2
FG_SCBW_DATA(const u8*, singularityChargeHeroAquireRangeIncrease,				0x004760d0);

//Entry 207
//Default value: 64
FG_SCBW_DATA(const s8*, singularityChargeHeroAttackRangeIncrease,				0x00475919);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Charon Boosters
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 208
//Default value: 3
FG_SCBW_DATA(const u8*, charonBoostersAquireRangeIncrease,						0x004760f5);

//Entry 209
//Default value: 96
FG_SCBW_DATA(const s8*, charonBoostersAttackRangeIncrease,						0x00475941);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Sight Range
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 210
//Upgraded sight range.  As with the sight ranges in units.dat, 
//this cannot be above 11 unless using ExtendSightLimit.
//Default value: 11
FG_SCBW_DATA(const u8*, ocularImplantsUpgradedSightRange,						0x004e5bab);

//Entry 211
//Upgraded sight range.  As with the sight ranges in units.dat, 
//this cannot be above 11 unless using ExtendSightLimit.
//Default value: 11
FG_SCBW_DATA(const u8*, antennaeUpgradedSightRange,								0x004e5bc5);

//Entry 212
//Upgraded sight range.  As with the sight ranges in units.dat, 
//this cannot be above 11 unless using ExtendSightLimit.
//Default value: 11
FG_SCBW_DATA(const u8*, sensorArrayUpgradedSightRange,							0x004e5bdf);

//Entry 213
//Upgraded sight range.  As with the sight ranges in units.dat, 
//this cannot be above 11 unless using ExtendSightLimit.
//Default value: 11
FG_SCBW_DATA(const u8*, apialSensorsUpgradedSightRange,							0x004e5bf7);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed / Upgrade Speed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 216
//Scout speed upgrade
//Default value: 1707
FG_SCBW_DATA(const u16*, speedUpgradegraviticThrusters,							0x0047b636);

//Entry 217
//Default value: 853
FG_SCBW_DATA(const u16*, speedUpgradeMinimumSpeedCheck,							0x0047b642);

//Entry 218
//Default value: 853
FG_SCBW_DATA(const u16*, speedUpgradeMinimumSpeedSet,							0x0047b649);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Energy
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 219
//Default value: 250
FG_SCBW_DATA(const u8*, titanReactorEnergyAmount,								0x004918b1);

//Entry 220
//Default value: 250
FG_SCBW_DATA(const u8*, moebiusReactorEnergyAmount,								0x004918cc);

//Entry 221
//Default value: 250
FG_SCBW_DATA(const u8*, apolloReactorEnergyAmount,								0x004918e7);

//Entry 222
//Default value: 250
FG_SCBW_DATA(const u8*, colossusReactorEnergyAmount,							0x00491902);

//Entry 223
//Default value: 250
FG_SCBW_DATA(const u8*, gameteMeiosisEnergyAmount,								0x0049191d);

//Entry 224
//Default value: 250
FG_SCBW_DATA(const u8*, metasynapticNodeEnergyAmount,							0x00491934);

//Entry 225
//Default value: 250
FG_SCBW_DATA(const u8*, khaydarinAmuletEnergyAmount,							0x0049194b);

//Entry 226
//Default value: 250
FG_SCBW_DATA(const u8*, khaydarinCoreEnergyAmount,								0x00491962);

//Entry 227
//Default value: 250
FG_SCBW_DATA(const u8*, argusJewelEnergyAmount,									0x00491979);

//Entry 228
//Energy amount is also applied to all heroes, 
//regardless of upgrade or unit type.
//Default value: 250
FG_SCBW_DATA(const u8*, cadecusReactorEnergyAmount,								0x00491990);

//Entry 229
//Default value: 250
FG_SCBW_DATA(const u8*, argusTalismanEnergyAmount,								0x004919a5);

//Entry 230
//Default value: 200
FG_SCBW_DATA(const u8*, defaultSpellcasterEnergyAmount,							0x004919ac);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Armor
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 231
//Default value: 2
FG_SCBW_DATA(const u8*, chitinousPlatingArmorIncrease,							0x0045402f);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Capacity / Reaver Capacity
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 232
//The initial amount of Scarabs a Reaver can build.
//Default value: 5
FG_SCBW_DATA(const s8*, reaverCapacityInitialScarabCapacity,					0x0046543e);

//Entry 233
//The number of additional Scarabs that can be built after upgrading.
//Default value: 5
FG_SCBW_DATA(const u8*, reaverCapacityUpgradeIncrease,							0x0046543b);

//Entry 234
//Amount of Scarabs a hero Reaver can build.
//Default value: 10
FG_SCBW_DATA(const u8*, reaverCapacityHeroScarabCount,							0x00465426);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Capacity / Carrier Capacity
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 235
//Initial amount of interceptors a carrier can build.
//Default value: 4
FG_SCBW_DATA(const s8*, carrierCapacityInitialInterceptorCapacity,				0x00465407);

//Entry 236
//Amount of Interceptors a Hero unit can build.
//Default value: 8
FG_SCBW_DATA(const u8*, carrierCapacityHeroInterceptorCapacity,					0x004653ee);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Spellcasters
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 238
//Default value: 8
FG_SCBW_DATA(const s8*, spellcastersEnergyRegain,								0x004eb55e);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Flying Buildings
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 240
//Default value: 256
FG_SCBW_DATA(const u16*, flyingBuildingsMovementTopSpeed,						0x00463b7e);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Independant Unit Size
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 241
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, independantUnitSizeIndependantWeaponDamagePercent,		0x00515b88);

//Entry 242
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, independantUnitSizeExplosiveWeaponDamagePercent,		0x00515b9c);

//Entry 243
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, independantUnitSizeConcussiveWeaponDamagePercent,		0x00515bb0);

//Entry 244
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, independantUnitSizeIgnoreArmorDamagePercent,			0x00515bd8);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Small Unit Size
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 245
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, smallUnitSizeIndependantWeaponDamagePercent,			0x00515b8c);

//Entry 246
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 128
FG_SCBW_DATA(const u16*, smallUnitSizeExplosiveWeaponDamagePercent,				0x00515ba0);

//Entry 247
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, smallUnitSizeConcussiveWeaponDamagePercent,			0x00515bb4);

//Entry 248
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, smallUnitSizeIgnoreArmorDamagePercent,					0x00515bdc);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Medium Unit Size
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 249
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, mediumUnitSizeIndependantWeaponDamagePercent,			0x00515b90);

//Entry 250
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 192
FG_SCBW_DATA(const u16*, mediumUnitSizeExplosiveWeaponDamagePercent,			0x00515ba4);

//Entry 251
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 128
FG_SCBW_DATA(const u16*, mediumUnitSizeConcussiveWeaponDamagePercent,			0x00515bb8);

//Entry 252
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, mediumUnitSizeIgnoreArmorDamagePercent,				0x00515be0);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Large Unit Size
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 253
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, largeUnitSizeIndependantWeaponDamagePercent,			0x00515b94);

//Entry 254
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, largeUnitSizeExplosiveWeaponDamagePercent,				0x00515ba8);

//Entry 255
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 64
FG_SCBW_DATA(const u16*, largeUnitSizeConcussiveWeaponDamagePercent,			0x00515bbc);

//Entry 256
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, largeUnitSizeIgnoreArmorDamagePercent,					0x00515be4);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Normal Weapon Damage Percent
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 257
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 0
FG_SCBW_DATA(const u16*, independantUnitSizeNormalWeaponDamagePercent,			0x00515bc4);

//Entry 258
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, smallUnitSizeNormalWeaponDamagePercent,				0x00515bc8);

//Entry 259
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, mediumUnitSizeNormalWeaponDamagePercent,				0x00515bcc);

//Entry 260
//Damage percentage, determined by this/256, 
//applied to the damage calculation.
//Default value: 256
FG_SCBW_DATA(const u16*, largeUnitSizeNormalWeaponDamagePercent,				0x00515bd0);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Incomplete Buildings
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 272
//As with the sight ranges in units.dat, this cannot be above 11
//unless using ExtendSightLimit
//Default value: 4
FG_SCBW_DATA(const u8*, IncompleteBuildingsSightRange,							0x004e5b5d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Reaver
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 273
//Default value: 60
FG_SCBW_DATA(const u8*, reaverScarabCooldown,									0x0046669a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Armor / Chitinous Plating
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 274
//Use UnitId::enum for values
//Default value: 39 (UnitId::ZergUltralisk)
FG_SCBW_DATA(const u8*, chitinousPlatingAffectedUnit1,							0x00454005);

//Entry 275
//Use UnitId::enum for values
//Default value: 48 (UnitId::Hero_Torrasque)
FG_SCBW_DATA(const u8*, chitinousPlatingAffectedUnit2,							0x0045400b);

////////////////////////////////////////////////////////////////////////////////////////////////
///Unit / Properties / Detection Range
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 276
//Controls the detection range for buildings. Measured in pixels.
//Default value: 224
FG_SCBW_DATA(const u32*, detectionRangeGroundedBuildingDetectionRange,			0x004408de);

//Entry 277
//Any unit that passes this flag check are treated as grounded buildings for 
//the purpose of calculating detection range. By default, this value is 0x2
//(Grounded buildings).
//Default value: 2 (UnitStatus::GroundedBuilding)
FG_SCBW_DATA(const u8*, detectionRangeGroundedBuildingFlagCheckStatus,			0x004408da);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed / Speed Upgrade Type Connected to Unit
///
/// Entry 278 to 379
/// 0x004544cc (Vulture) to 0x54531 (Lurker)
/// Units with UnitId lower than Vulture or higher than
/// Lurker are not included (the bounds of the array in 
/// memory are obvious enough to tell).
///
///Allowed values: 
///		 0 - Ion Thrusters
///		 1 - Metabolic Boost & Adrenal Glands
///		 2 - Muscular Augments
///		 3 - Anabolic Synthesis
///		 4 - Pneumatized Carapace
///		 5 - Upgraded by default (Torrasque)
///		 6 - Upgraded by default (most heroes & Lurker)
///		 7 - Upgraded speed & Adrenal Glands
///		 8 - Leg Enhancements
///		 9 - Gravitic Drive
///		10 - Gravitic Thrusters
///		11 - Gravitic Boosters
///		12 - None.  
///		Note: These will only affect units produced after the upgrade.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace speedUpgradeEnum {
enum Enum{
	IonThrusters = 0,
	MetabolicBoostandAdrenalGlands = 1,
	MuscularAugments = 2,
	AnabolicSynthesis = 3,
	PneumatizedCarapace = 4,
	UpgradedByDefault_Torrasque = 5,
	UpgradedByDefault_MostHeroesandLurker = 6,
	UpgradedSpeedandAdrenalGlands = 7,
	LegEnhancements = 8,
	GraviticDrive = 9,
	GraviticThrusters = 10,
	GraviticBoosters = 11,
	None = 12
};
}

//Entry 278 to Entry 379
//Return a number to compare with speedUpgradeEnum to
//know the speed upgrade corresponding to the unit.
//If the unit is not handled through this array, this
//return speedUpgradeEnum::None (12).
u8 speedUpgradeTypeConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranVulture && unit_id <= UnitId::ZergLurker)
		return *(u8*)(0x004544cc + unit_id - 2);
	else
		return speedUpgradeEnum::None;

}

//Entry 278 to Entry 379
//Return the pointer to memory where the byte to be
//compared with speedUpgradeEnum and defined in Firegraft
//is.
//If the unit is not handled through this array, this
//return NULL
const u8* speedUpgradeTypeConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranVulture && unit_id <= UnitId::ZergLurker)
		return (u8*)(0x004544cc + unit_id - 2);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed / Ion Thrusters
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 380
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced 
//before the upgrade finished.
//Default value: 2 (UnitId::TerranVulture)
FG_SCBW_DATA(const u16*, ionThrustersBoostSpeedWhenUpgradeExistingUnit1,		0x00454096);

//Entry 381
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced 
//before the upgrade finished.
//Default value: 19 (UnitId::Hero_JimRaynorVulture)
FG_SCBW_DATA(const u16*, ionThrustersBoostSpeedWhenUpgradeExistingUnit2,		0x0045409c);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed / Anabolic Synthesis
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 382
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced 
//before the upgrade finished.
//Default value: 39 (UnitId::ZergUltralisk)
FG_SCBW_DATA(const u16*, anabolicSynthesisBoostSpeedWhenUpgradeExistingUnit1,	0x00454076);

//Entry 383
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced 
//before the upgrade finished.
//Default value: 48 (UnitId::Hero_Torrasque)
FG_SCBW_DATA(const u16*, anabolicSynthesisBoostSpeedWhenUpgradeExistingUnit2,	0x0045407c);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Attack Range Upgrade Type Connected to Unit
///
/// Entry 384 to 462
/// 0x0047596c (Marine) to 0x004759ba (Fenix (Dragoon))
/// Units with UnitId higher than Fenix (Dragoon) are not
/// included (the bounds of the array in memory are
/// obvious enough to tell).
///
///Allowed values: 
///		0 - U-238 Shells,
///		1 - Charon Boosters (Normal),
///		2 - Charon Boosters (Upgraded),
///		3 - Grooved Spines,
///		4 - Singularity Charge (Normal),
///		5 - Singularity Charge (Hero, Upgraded),
///		6 - None.
///		Note: both types of Charon Boosters require additional EXE edits
///		in the "Charon Boosters" section to work.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace rangeUpgradeEnum {
enum Enum {
	U238Shells = 0,
	CharonBoostersNormal = 1,
	CharonBoostersUpgraded = 2,
	GroovedSpines = 3,
	SingularityChargeNormal = 4,
	SingularityChargeHeroUpgraded = 5,
	None = 6
};
}

//Entry 384 to Entry 462
//Return a number to compare with rangeUpgradeEnum to
//know the range upgrade corresponding to the unit.
//If the unit is not handled through this array, this
//return rangeUpgradeEnum::None (6).
u8 rangeUpgradeTypeConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranMarine && unit_id <= UnitId::Hero_FenixDragoon)
		return *(u8*)(0x0047596c + unit_id);
	else
		return rangeUpgradeEnum::None;

}

//Entry 384 to Entry 462
//Return the pointer to memory where the byte to be
//compared with rangeUpgradeEnum and defined in Firegraft
//is.
//If the unit is not handled through this array, this
//return NULL
const u8* rangeUpgradeTypeConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranMarine && unit_id <= UnitId::Hero_FenixDragoon)
		return (u8*)(0x0047596c + unit_id);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Acquire Target Range Upgrade Type Connected to Unit
///
/// Entry 463 to 541
/// 0x00476124 (Marine) to 0x00476172 (Fenix (Dragoon))
/// Units with UnitId higher than Fenix (Dragoon) are not
/// included (the bounds of the array in memory are
/// obvious enough to tell).
///
///Allowed values: 
///		0 - U-238 Shells,
///		1 - Charon Boosters (Normal),
///		2 - Charon Boosters (Upgraded),
///		3 - Grooved Spines,
///		4 - Singularity Charge (Normal),
///		5 - Singularity Charge (Hero, Upgraded),
///		6 - None.
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 463 to Entry 541
//Return a number to compare with rangeUpgradeEnum to
//know the range upgrade corresponding to the unit.
//If the unit is not handled through this array, this
//return rangeUpgradeEnum::None (6).
u8 acquireTargetRangeUpgradeTypeConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranMarine && unit_id <= UnitId::Hero_FenixDragoon)
		return *(u8*)(0x00476124 + unit_id);
	else
		return rangeUpgradeEnum::None;

}

//Entry 463 to Entry 541
//Return the pointer to memory where the byte to be
//compared with rangeUpgradeEnum and defined in Firegraft
//is.
//If the unit is not handled through this array, this
//return NULL
const u8* acquireTargetRangeUpgradeTypeConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranMarine && unit_id <= UnitId::Hero_FenixDragoon)
		return (u8*)(0x00476124 + unit_id);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Heal
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 542
//Default value: 160
FG_SCBW_DATA(const u16*, healAcquireHealTargetRange,							0x004422e0);

//Entry 543
//Values larger than 127 will be considered "infinite."
//Default value: 30
FG_SCBW_DATA(const u8*, healMaximumHealRange,									0x00463cac);

//Entry 544
//Medics will stop to heal when a valid target is within 
//this range. Values larger than 127 will be considered
//"infinite."
//Default value: 30
FG_SCBW_DATA(const u8*, healHealMoveStopRange,									0x004641fd);

//Entry 546
//Measured in (energy * 256) and must be used along with 
//Entry 545 Code Hack. Otherwise, it may cause weird problems 
//and most likely crash the game. This EXE edit replaces -17.
//Default value: -17
FG_SCBW_DATA(const s8*, healModifyEnergyCostEnergyCheckedEachFrame,				0x00463ce2);

//Entry 547
//Measured in (energy * 256) and must be used along with
//Entry 545 Code Hack. Otherwise, it may cause weird problems 
//and most likely crash the game. This EXE edit replaces 87.
//Default value: 87
FG_SCBW_DATA(const s8*, healModifyEnergyCostEnergySubstractedEachFrame,			0x00463cfa);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 548
//Use UnitId::enum for values
//Parallel to other "apply to units produced before upgrade", 
//this data seems to be unused. It is added here merely for 
//completeness.
//Default value: 2 (UnitId::TerranVulture)
FG_SCBW_DATA(const u16*, ionThrustersBoostExistingUnitSpeedWhenUpgrade_Unused,	0x00454571);

//Entry 549
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 42 (UnitId::ZergOverlord)
FG_SCBW_DATA(const u16*, pneumatizedCarapaceBoostExistingUnitSpeedWhenUpgrade,	0x0045457d);

//Entry 550
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 37 (UnitId::ZergZergling)
FG_SCBW_DATA(const u16*, metabolicBoostBoostExistingUnitSpeedWhenUpgrade,		0x00454589);

//Entry 551
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 38 (UnitId::ZergHydralisk)
FG_SCBW_DATA(const u16*, muscularAugmentsBoostExistingUnitSpeedWhenUpgrade,		0x004545a8);

//Entry 552
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 65 (UnitId::ProtossZealot)
FG_SCBW_DATA(const u16*, legEnhancementsBoostExistingUnitSpeedWhenUpgrade,		0x004545b4);

//Entry 553
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 70 (UnitId::ProtossScout)
FG_SCBW_DATA(const u16*, graviticThrustersBoostExistingUnitSpeedWhenUpgrade,	0x004545c0);

//Entry 554
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 69 (UnitId::ProtossShuttle)
FG_SCBW_DATA(const u16*, graviticDriveBoostExistingUnitSpeedWhenUpgrade,		0x004545cc);

//Entry 555
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 84 (UnitId::ProtossObserver)
FG_SCBW_DATA(const u16*, graviticBoostersBoostExistingUnitSpeedWhenUpgrade,		0x004545d8);

//Entry 556
//Use UnitId::enum for values
//Parallel to other "apply to units produced before upgrade", 
//this data seems to be unused. It is added here merely for 
//completeness.
//Default value: 39 (UnitId::ZergUltralisk)
FG_SCBW_DATA(const u16*, anabolicSynthesisBoostExistingUnitSpeedWhenUpgrade_Unused, 0x004545e4);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Attack Speed / Adrenal Glands
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 557
//Use UnitId::enum for values
//This EXE edit is applied only to units that were produced
//before the upgrade finished.
//Default value: 37 (UnitId::ZergZergling)
FG_SCBW_DATA(const u16*, adrenalGlandsBoostSpeedWhenUpgradeExistingUnit,		0x00454595);

//Entry 558
//Use UnitId::enum for values
//Allows the unit to be affected by Adrenal Glands if 
//their Speed Upgrade type is set to 1 or 7. This only
//affects units born after the upgrade.
//Default value: 37 (UnitId::ZergZergling)
FG_SCBW_DATA(const u16*, adrenalGlandsUnitRequirement1,							0x004ec304);

//Entry 559
//Use UnitId::enum for values
//Allows the unit to be affected by Adrenal Glands if 
//their Speed Upgrade type is set to 1 or 7. This only
//affects units born after the upgrade.
//Default value: 54 (UnitId::Hero_DevouringOne)
FG_SCBW_DATA(const u16*, adrenalGlandsUnitRequirement2,							0x004ec30a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Unit Speed / Upgrade Speed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 560
//Use UnitId::enum for values
//This unit will have the Scout's upgrade speed instead of 
//150% of its original speed, if it receives a speed upgrade.
//Default value: 70 (UnitId::ProtossScout)
FG_SCBW_DATA(const u8*, UpgradeSpeedSpecialUpgradeFollowingUnit1,				0x0047b626);

//Entry 561
//Use UnitId::enum for values
//This unit will have the Scout's upgrade speed instead of 
//150% of its original speed, if it receives a speed upgrade.
//Default value: 80 (UnitId::Hero_Mojo)
FG_SCBW_DATA(const u8*, UpgradeSpeedSpecialUpgradeFollowingUnit2,				0x0047b62c);

//Entry 562
//Use UnitId::enum for values
//This unit will have the Scout's upgrade speed instead of 
//150% of its original speed, if it receives a speed upgrade.
//Default value: 88 (UnitId::Hero_Artanis)
FG_SCBW_DATA(const u8*, UpgradeSpeedSpecialUpgradeFollowingUnit3,				0x0047b632);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Weapon Range / Charon Boosters
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 563
//Use WeaponId::enum for values
//The unit that uses this weapon must have their Attack Range
//Upgrade Type set to either 1 (Charon Boosters (Normal)) or
//2 (Charon Boosters (Hero)) for the upgrades to take effect.
//Default value: 8 (WeaponId::HellfireMissilePack)
FG_SCBW_DATA(const u8*, charonBoostersAffectedWeaponIdNormal,					0x0047591f);

//Entry 564
//Use WeaponId::enum for values
//The unit that uses this weapon must have their Attack Range
//Upgrade Type set to either 1 (Charon Boosters (Normal)) or
//2 (Charon Boosters (Hero)) for the upgrades to take effect.
//Default value: 10 (WeaponId::HellfireMissilePack_AlanSchezar)
FG_SCBW_DATA(const s8*, charonBoostersAffectedWeaponIdHero,						0x00475933);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Mind Control
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 572
//Measured in pixels. This EXE edit uses a position that used to 
//be program code, and thus requires Entry 571 Code Hack to work. 
//The default value is 98615807.
//Default value: 98615807
FG_SCBW_DATA(const u32*, mindControlSpellCastingRange,							0x004f69d8);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Irradiate
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 576
//Use UnitId::enum for values
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u16*, irradiateImmuneUnit1,									0x00455553);

//Entry 577
//Use UnitId::enum for values
//Default value: 36 (UnitId::ZergEgg)
FG_SCBW_DATA(const u16*, irradiateImmuneUnit2,									0x00455559);

//Entry 578
//Use UnitId::enum for values
//Default value: 97 (UnitId::ZergLurkerEgg)
FG_SCBW_DATA(const u16*, irradiateImmuneUnit3,									0x0045555f);

//Entry 580
//Default value: -160
FG_SCBW_DATA(const s32*, irradiateSplashDamageLocationBoundaryLeft,				0x004555f0);

//Entry 581
//Default value: 160
FG_SCBW_DATA(const s32*, irradiateSplashDamageLocationBoundaryRight,			0x004555f5);

//Entry 582
//Default value: -160
FG_SCBW_DATA(const s32*, irradiateSplashDamageLocationBoundaryTop,				0x004555ff);

//Entry 583
//Default value: 160
FG_SCBW_DATA(const s32*, irradiateSplashDamageLocationBoundaryBottom,			0x00455609);

//Entry 584
//Values below 0 will be interpreted as "infinite." 
//Note that only units within the location bounds are 
//damaged by the splash.
//Default value: 32
FG_SCBW_DATA(const s8*, irradiateSplashRadius,									0x0045557b);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Maelstrom
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 585
//Default value: 1064
FG_SCBW_DATA(const u16*, maelstromCastingSoundSfxdataDatId,						0x004f6885);

//Entry 586
//Default value: -48
FG_SCBW_DATA(const s8*, maelstromEffectLocationBoundaryLeft, 					0x004f6893);

//Entry 587
//Default value: 48
FG_SCBW_DATA(const s8*, maelstromEffectLocationBoundaryRight,					0x004f6896);

//Entry 588
//Default value: -48
FG_SCBW_DATA(const s8*, maelstromEffectLocationBoundaryTop,						0x004f6899);

//Entry 589
//Default value: 48
FG_SCBW_DATA(const s8*, maelstromEffectLocationBoundaryBottom,					0x004f68a0);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Stasis Field
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 590
//Default value: -48
FG_SCBW_DATA(const s8*, stasisFieldEffectLocationBoundaryLeft, 					0x004f6ab2);

//Entry 591
//Default value: 48
FG_SCBW_DATA(const s8*, stasisFieldEffectLocationBoundaryRight,					0x004f6ab8);

//Entry 592
//Default value: -48
FG_SCBW_DATA(const s8*, stasisFieldEffectLocationBoundaryTop,					0x004f6ab5);

//Entry 593
//Default value: 48
FG_SCBW_DATA(const s8*, stasisFieldEffectLocationBoundaryBottom,				0x004f6ac3);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Target / Mind Control
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 594
//Default value: 1062
FG_SCBW_DATA(const u16*, mindControlCastingSoundSfxdataDatId,					0x004f6a65);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Ensnare
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 595
//Default value: -64
FG_SCBW_DATA(const s8*, ensnareEffectLocationBoundaryLeft, 						0x004f4862);

//Entry 596
//Default value: 64
FG_SCBW_DATA(const s8*, ensnareEffectLocationBoundaryRight,						0x004f4868);

//Entry 597
//Default value: -64
FG_SCBW_DATA(const s8*, ensnareEffectLocationBoundaryTop,						0x004f4865);

//Entry 598
//Default value: 64
FG_SCBW_DATA(const s8*, ensnareEffectLocationBoundaryBottom,					0x004f4873);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Plague
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 599
//Default value: -64
FG_SCBW_DATA(const s8*, plagueEffectLocationBoundaryLeft, 						0x004f4b38);

//Entry 600
//Default value: 64
FG_SCBW_DATA(const s8*, plagueEffectLocationBoundaryRight,						0x004f4b4d);

//Entry 601
//Default value: -64
FG_SCBW_DATA(const s8*, plagueEffectLocationBoundaryTop,						0x004f4b3f);

//Entry 602
//Default value: 64
FG_SCBW_DATA(const s8*, plagueEffectLocationBoundaryBottom,						0x004f4b42);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / EMP Shockwave
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 608
//Measured in (energy) x 256. This EXE edit uses a position 
//that used to be program code, and thus must be used along with 
//the entries 606 and 607 Code Hacks and entry 609.
//The original code is displayed as -4500.
//Default value: -4500
FG_SCBW_DATA(const s16*, empShockwaveEnergyReduction,							0x00492c85);

//Entry 609
//Measured in (shields) x 256. This EXE edit uses a position 
//that used to be program code, and thus must be used along with 
//the entries 606 and 607 Code Hacks and entry 608.
//The original code is displayed as 7073388.
//Default value: 7073388
FG_SCBW_DATA(const s32*, empShockwaveShieldReduction,							0x00492c93);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Weapon Damage Displayed
///
///Linked to Units / Properties / Upgrade Damage Displayed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 613
//Use UnitId::enum for values
//This unit's weapon damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 32 (UnitId::TerranFirebat)
FG_SCBW_DATA(const u16*, weaponDamageDisplayedMultiplyDamageShownForUnit1,		0x00475f16);

//Entry 614
//Use UnitId::enum for values
//This unit's weapon damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 10 (UnitId::Hero_GuiMontag)
FG_SCBW_DATA(const u16*, weaponDamageDisplayedMultiplyDamageShownForUnit2,		0x00475f25);

//Entry 615
//Use UnitId::enum for values
//This unit's weapon damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 65 (UnitId::ProtossZealot)
FG_SCBW_DATA(const u16*, weaponDamageDisplayedMultiplyDamageShownForUnit3,		0x00475f2b);

//Entry 616
//Use UnitId::enum for values
//This unit's weapon damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 77 (UnitId::Hero_FenixZealot)
FG_SCBW_DATA(const u16*, weaponDamageDisplayedMultiplyDamageShownForUnit4,		0x00475f31);

//Entry 617
//Does not affect actual damage dealt, and only modifies
//the value shown in the status display.
//Default value: 2
FG_SCBW_DATA(const u8*, weaponDamageDisplayedDamageMultiplierA,					0x00475f36);

//Entry 618
//Use UnitId::enum for values
//This unit's weapon damage is multiplied by Damage Multiplier B 
//when shown in the in-game status bar, OVERRIDING the 
//"damage factor" property in Weapons.DAT.
//Default value: 58 (UnitId::TerranValkyrie)
FG_SCBW_DATA(const u16*, weaponDamageDisplayedUnitWithCustomDamageMultiplier,	0x00475f39);

//Entry 619
//Does not affect actual damage dealt, and only modifies 
//the value shown in the status display.
//Default value: 1
FG_SCBW_DATA(const u8*, weaponDamageDisplayedDamageMultiplierB,					0x00475f3e);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Ground / Recharge Shields
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 620
//Measured in pixels.
//Default value: 128
FG_SCBW_DATA(const u32*, rechargeShieldsMaximumdistance,						0x00493e6a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Target / Corrosive Acid
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 621
//Default value: -64 
FG_SCBW_DATA(const s8*, corrosiveAcidEffectLocationBoundaryLeft, 				0x004f4778);

//Entry 622
//Default value: 64
FG_SCBW_DATA(const s8*, corrosiveAcidEffectLocationBoundaryRight,				0x004f4782);

//Entry 623
//Default value: -64
FG_SCBW_DATA(const s8*, corrosiveAcidEffectLocationBoundaryTop,					0x004f477f);

//Entry 624
//Default value: 64
FG_SCBW_DATA(const s8*, corrosiveAcidEffectLocationBoundaryBottom,				0x004f478d);

////////////////////////////////////////////////////////////////////////////////////////////////
///Abilities / Target / Glave Wurm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 625
//Default value: -96 
FG_SCBW_DATA(const s8*, glaveWurmBounceTargetSearchBoundaryLeft, 				0x0048b21a);

//Entry 626
//Default value: 96
FG_SCBW_DATA(const s8*, glaveWurmBounceTargetSearchBoundaryRight,				0x0048b21d);

//Entry 627
//Default value: -96
FG_SCBW_DATA(const s8*, glaveWurmBounceTargetSearchBoundaryTop,					0x0048b225);

//Entry 628
//Default value: 96
FG_SCBW_DATA(const s8*, glaveWurmBounceTargetSearchBoundaryBottom,				0x0048b22c);

////////////////////////////////////////////////////////////////////////////////////////////////
///Units / Properties / Upgrade Damage Displayed
///
///Linked to Units / Properties / Weapon Damage Displayed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 629
//Use UnitId::enum for values
//This unit's upgrade damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 32 (UnitId::TerranFirebat)
FG_SCBW_DATA(const u16*, upgradeDamageDisplayedMultiplyDamageShownForUnit1,		0x00475e7b);

//Entry 630
//Use UnitId::enum for values
//This unit's upgrade damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 10 (UnitId::Hero_GuiMontag)
FG_SCBW_DATA(const u16*, upgradeDamageDisplayedMultiplyDamageShownForUnit2,		0x00475e81);

//Entry 631
//Use UnitId::enum for values
//This unit's upgrade damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 65 (UnitId::ProtossZealot)
FG_SCBW_DATA(const u16*, upgradeDamageDisplayedMultiplyDamageShownForUnit3,		0x00475e87);

//Entry 632
//Use UnitId::enum for values
//This unit's upgrade damage is multiplied by Damage Multiplier A 
//when shown in the in-game status bar, AFTER the "damage factor" 
//property in Weapons.DAT has been applied.
//Default value: 77 (UnitId::Hero_FenixZealot)
FG_SCBW_DATA(const u16*, upgradeDamageDisplayedMultiplyDamageShownForUnit4,		0x00475e8d);

//Entry 633
//Does not affect actual damage dealt, and only modifies
//the value shown in the status display.
//Default value: 2
FG_SCBW_DATA(const u8*, upgradeDamageDisplayedDamageMultiplierA,				0x00475e92);

//Entry 634
//Use UnitId::enum for values
//This unit's upgrade damage is multiplied by Damage Multiplier B 
//when shown in the in-game status bar, OVERRIDING the 
//"damage factor" property in Weapons.DAT.
//Default value: 58 (UnitId::TerranValkyrie)
FG_SCBW_DATA(const u16*, upgradeDamageDisplayedUnitWithCustomDamageMultiplier,	0x00475e95);

//Entry 635
//Does not affect actual damage dealt, and only modifies 
//the value shown in the status display.
//Default value: 1
FG_SCBW_DATA(const u8*, upgradeDamageDisplayedDamageMultiplierB,				0x00475e9a);

////////////////////////////////////////////////////////////////////////////////////////////////
///Upgrades / Capacity / Carrier Capacity
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 641
//Warning: This modifies what used to be assembly code, and only 
//works when Entry 640 Code Hack is enabled. The original value 
//here is -115.
//Default value: -115
FG_SCBW_DATA(const s8*, carrierCapacityInterceptorCapacityUpgrade,				0x00465404);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Dark Swarm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 642
//Default value: 11
FG_SCBW_DATA(const u8*, darkSwarmUnitElevationLevel,							0x004f4904);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Disruption Web
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 643
//Default value: 11
FG_SCBW_DATA(const u8*, disruptionWebUnitElevationLevel,						0x004f6b54);

////////////////////////////////////////////////////////////////////////////////////////////////
///Tech / Ground / Dark Swarm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 644
//Applied to weapons set to 'Appear on Target Unit' or 
//'Appear on Target Site'.
//Default value: 30
FG_SCBW_DATA(const s8*, darkSwarmWeaponSpriteShiftDistance1Horizontal,			0x0048c0f2);

//Entry 645
//Applied to weapons set to 'Appear on Target Unit' or 
//'Appear on Target Site'.
//Default value: 30
FG_SCBW_DATA(const s8*, darkSwarmWeaponSpriteShiftDistance1Vertical,			0x0048c0dc);

//Entry 646
//Applied to weapons set to 'Fly (Follow Target)'.
//Default value: 30
FG_SCBW_DATA(const s8*, darkSwarmWeaponSpriteShiftDistance2Horizontal,			0x0048c1f3);

//Entry 647
//Applied to weapons set to 'Fly (Follow Target)'.
//Default value: 30
FG_SCBW_DATA(const s8*, darkSwarmWeaponSpriteShiftDistance2Vertical,			0x0048c1f0);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Unit Behavior / Detectors
///
/// Entry 648 to 746
/// 0x0043c914 (Science Vessel) to 0x0043c976 (Comsat Station)
/// Units with UnitId lower than Science Vessel or higher than
//  Comsat Station are not included (the bounds of the array
//  in memory are obvious enough to tell).
///
/// Decides how the AI responds to cloaked/burrowed enemies.
///
///Allowed values: 
///		0 - Bring to location, 
///		1 - Bring if not carrying units, 
///		2 - Cast Ensnare at location, 
///		3 - Cast Scan at location, 
///		4 - Do nothing.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace detectorBehaviorEnum{
enum Enum {
	BringToLocation = 0,
	BringIfNotCarryingUnits = 1,
	CastEnsnareAtLocation = 2,
	CastScanAtLocation = 3,
	DoNothing = 4
};
}

//Entry 648 to Entry 746
//Return a number to compare with detectorBehaviorEnum to
//know the behavior corresponding to the unit if it's
//called in answer to a detection.
//If the unit is not handled through this array, this
//return detectorBehavior::DoNothing (4).
u8 aiDetectorUnitsBehavior(u8 unit_id) {

	if(unit_id >= UnitId::TerranScienceVessel && unit_id <= UnitId::TerranComsatStation)
		return *(u8*)(0x0043c914 + unit_id - UnitId::TerranScienceVessel);
	else
		return detectorBehaviorEnum::DoNothing;

}

//Entry 648 to Entry 746
//Return the pointer to memory where the byte to be
//compared with detectorBehaviorEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* aiDetectorUnitsBehavior_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranScienceVessel && unit_id <= UnitId::TerranComsatStation)
		return (u8*)(0x0043c914 + unit_id - UnitId::TerranScienceVessel);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Unit Behavior / Detectors Actions
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 747
//Use OrderId::enum for values
//Default value: 146 (OrderId::Ensnare)
FG_SCBW_DATA(const u8*, aiDetectorUnitBehaviorQueenSpellOrderIdEnergyCostCheck,	0x0043c78b);

//Entry 748
//Use TechId::enum for values
//Default value: 17 (TechId::Ensnare)
FG_SCBW_DATA(const u8*, aiDetectorUnitBehaviorQueenSpellTechIdResearchCheck,	0x0043c7a4);

//Entry 749
//Use UnitId::enum for values
//Queens will ignore this type of unit even if it is 
//a burrowed/cloaked attacker.
//Default value: 103 (UnitId::ZergLurker)
FG_SCBW_DATA(const u8*, aiDetectorUnitBehaviorUnitIdImmuneToQueenSpell,			0x0043c787);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Dark Swarm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 750
//Actual miss chance = ([this value] + 1) / 256. If the unit is 
//also on higher ground, StarCraft uses the larger miss chance value. 
//Dark swarm takes priority over doodads.
//Default value: 255
FG_SCBW_DATA(const u8*, darkSwarmMissChance,									0x00476265);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Hit Chance
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 751
//Actual miss chance = ([this value] + 1) / 256. If the unit is also 
//on higher ground, StarCraft uses the larger miss chance value. 
//Dark swarm takes priority over doodads.
//Default value: 119
FG_SCBW_DATA(const u8*, hitChanceMissChanceUnderDoodad,							0x004762b1);

//Entry 752
//Actual miss chance = ([this value] + 1) / 256.
//Default value: 119
FG_SCBW_DATA(const u8*, hitChanceMissChanceOnHigherGroundCheck,					0x004765fa);

//Entry 753
//Actual miss chance = ([this value] + 1) / 256.
//Default value: 119
FG_SCBW_DATA(const u8*, hitChanceMissChanceOnHigherGroundValue,					0x004765fc);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Upgrades / Sight Range / Sight Range Upgrade Connected to Unit
///
/// Entry 755 to 838
/// 0x004e5c1c (Ghost) to 0x004e5c6f (Observer)
/// Marine or Units with UnitId higher than Observer are
/// not included (at this point, I decided to trust memory
/// array corresponding to that).
///
///Allowed values: 
///		0 - Ocular Implants, 
///		1 - Antennae,
///		2 - Apial Sensors,
///		3 - Sensor Array,
///		4 - None.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace sightUpgradeEnum {
enum Enum {
	OcularImplants = 0,
	Antennae = 1,
	ApialSensors = 2,
	SensorArray = 3,
	None = 4
};
}

//Entry 755 to Entry 838
//Return a number to compare with sightUpgradeEnum to
//know the sight range upgrade corresponding to the unit.
//If the unit is not handled through this array, this
//return sightUpgradeEnum::None (4).
u8 sightRangeUpgradeConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossObserver)
		return *(u8*)(0x004e5c1c + unit_id - UnitId::TerranGhost);
	else
		return sightUpgradeEnum::None;

}

//Entry 755 to Entry 838
//Return the pointer to memory where the byte to be
//compared with sightUpgradeEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* sightRangeUpgradeConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossObserver)
		return (u8*)(0x004e5c1c + unit_id - UnitId::TerranGhost);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Upgrades / Unit Energy / Energy Upgrade Connected to Unit
///
/// Entry 839 to 909
/// 0x004919e0 (Ghost) to 0x00491a26 (Arbiter)
/// Marine or Units with UnitId higher than Observer are
/// not included (at this point, I decided to trust memory
/// array corresponding to that).
///
///Allowed values: 
///		0 - Moebius Reactor,
///		1 - Apollo Reactor,
///		2 - Titan Reactor,
///		3 - Colossus Reactor,
///		4 - Caduceus Reactor,
///		5 - Gamete Meiosis,
///		6 - Metasynaptic Node,
///		7 - Argus Jewel,
///		8 - Argus Talisman,
///		9 - Khaydarin Amulet,
///		10 - Khaydarin Core,
///		11 - None.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace energyUpgradeEnum {
enum Enum {
	MoebiusReactor = 0,
	ApolloReactor = 1,
	TitanReactor = 2,
	ColossusReactor = 3,
	CaduceusReactor = 4,
	GameteMeiosis = 5,
	MetasynapticNode = 6,
	ArgusJewel = 7,
	ArgusTalisman = 8,
	KhaydarinAmulet = 9,
	KhaydarinCore = 10,
	None = 11
};
}

//Entry 839 to Entry 909
//Return a number to compare with energyUpgradeEnum to
//know the energy upgrade corresponding to the unit.
//If the unit is not handled through this array, this
//return energyUpgradeEnum::None (11).
u8 energyUpgradeConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossArbiter)
		return *(u8*)(0x004919e0 + unit_id - UnitId::TerranGhost);
	else
		return energyUpgradeEnum::None;

}

//Entry 839 to Entry 909
//Return the pointer to memory where the byte to be
//compared with energyUpgradeEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* energyUpgradeConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossArbiter)
		return (u8*)(0x004919e0 + unit_id - UnitId::TerranGhost);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Peons / Resource Harvesting
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 922
//Default value: 75
FG_SCBW_DATA(const u8*, resourceHarvestingMineralHarvestingTime,				0x004698bf);

//Entry 923
//Default value: 37
FG_SCBW_DATA(const u8*, resourceHarvestingGasHarvestingTime,					0x00469aeb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Corrosive Acid
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 924
//Default value: 3
FG_SCBW_DATA(const u8*, corrosiveAcidWeaponCooldownIncreaseMinimumCheck,		0x00475ddc);

//Entry 925
//Default value: 3
FG_SCBW_DATA(const u8*, corrosiveAcidWeaponCooldownIncreaseMinimumSet,			0x00475de0);

//Entry 926
//Each layer of Acid Spores increases weapon cooldown by 
//(base cooldown) / (divisor), where (divisor) = 2 ^ (shift factor). 
//This EXE edit cannot be used along with Entry 968 Code Hack.
//Default value: 3
FG_SCBW_DATA(const u8*, corrosiveAcidWeaponCooldownIncreaseShiftFactor,			0x00475dd9);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Ground / Nuclear Strike
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 928
//Default value: 500
FG_SCBW_DATA(const u32*, nuclearStrikeMinimumNukeDamageCheck,					0x0048ad9c);

//Entry 929
//Default value: 500
FG_SCBW_DATA(const u32*, nuclearStrikeMinimumNukeDamageValue,					0x0048ada3);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Orders / Target / Carrier Attack
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 933
//A carrier is allowed to move (base range + this value) matrices 
//away from the target unit while its interceptors are attacking it.
//Default value: 2
FG_SCBW_DATA(const s8*, carrierAttackInterceptorAttackRangeLeeway,				0x004658d9);

//Entry 935
//Default value: 128
FG_SCBW_DATA(const s32*, carrierAttackInterceptorHealAmountPerCycle,			0x004668ec);

//Entry 938
//Default value: 15
FG_SCBW_DATA(const u8*, carrierAttackDelayBeforeAttackingOnInterceptorLaunch,	0x00465fea);

//Entry 939
//Default value: 7
FG_SCBW_DATA(const u8*, carrierAttackDelayBetweenSuccessiveInterceptorLaunches,	0x00466718);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Halo Rockets
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 940
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 1
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition01_X,							0x00513650);

//Entry 941
//Default value: 1
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition01_Y,							0x00513654);

//Entry 942
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 51
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition02_X,							0x00513658);

//Entry 943
//Default value: 31
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition02_Y,							0x0051365c);

//Entry 944
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 7
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition03_X,							0x00513660);

//Entry 945
//Default value: 12
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition03_Y,							0x00513664);

//Entry 946
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -36
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition04_X,							0x00513668);

//Entry 947
//Default value: -52
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition04_Y,							0x0051366c);

//Entry 948
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -49
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition05_X,							0x00513670);

//Entry 949
//Default value: 25
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition05_Y,							0x00513674);

//Entry 950
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 40
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition06_X,							0x00513678);

//Entry 951
//Default value: -46
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition06_Y,							0x0051367c);

//Entry 952
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -4
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition07_X,							0x00513680);

//Entry 953
//Default value: -19
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition07_Y,							0x00513684);

//Entry 954
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 28
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition08_X,							0x00513688);

//Entry 955
//Default value: 50
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition08_Y,							0x0051368c);

//Entry 956
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 50
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition09_X,							0x00513690);

//Entry 957
//Default value: -15
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition09_Y,							0x00513694);

//Entry 958
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -54
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition10_X,							0x00513698);

//Entry 959
//Default value: -13
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition10_Y,							0x0051369c);

//Entry 960
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 11
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition11_X,							0x005136a0);

//Entry 961
//Default value: -53
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition11_Y,							0x005136a4);

//Entry 962
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: 15
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition12_X,							0x005136a8);

//Entry 963
//Default value: -9
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition12_Y,							0x005136ac);

//Entry 964
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -19
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition13_X,							0x005136b0);

//Entry 965
//Default value: 50
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition13_Y,							0x005136b4);

//Entry 966
//If you set this value to zero, StarCraft will recognize it as an 
//end-of-array mark and will loop back to the first bullet position
//instead (i.e. use the first one only).
//Default value: -17
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition14_X,							0x005136b8);

//Entry 967
//Default value: 8
FG_SCBW_DATA(const s32*, haloRocketsBulletPosition14_Y,							0x005136bc);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Corrosive Acid
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 969
//Values larger than 9 may crash the game.
//Default value: 9
FG_SCBW_DATA(const u8*, corrosiveAcidMaximumStackLevelCheck,					0x004f4487);

//Entry 970
//Values larger than 9 may crash the game.
//Default value: 9
FG_SCBW_DATA(const u8*, corrosiveAcidMaximumStackLevelTimerArraySize,			0x004f452d);

//Entry 971
//Default value: 150
FG_SCBW_DATA(const u8*, corrosiveAcidTimerDefault,								0x004f4541);

//Entry 972
//If the target has maximum stack of acid spores, this value 
//is used to refresh the last stack in the timer array.
//Default value: 150
FG_SCBW_DATA(const u8*, corrosiveAcidTimerRefreshingMaxedOutTimerArray,			0x004f4537);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Unselectable Units
///
/// Entry 973 to 1167
/// Units with UnitId lower than 0x0046edac (Nuclear Missile) 
/// or higher than 0x0046ee6e (Right Pit Door) are not 
/// included (at this point, I decided to trust memory
/// array corresponding to that).
///
///Allowed values: 
///		0 - unselectable, 
///		1 - selectable
////////////////////////////////////////////////////////////////////////////////////////////////

namespace selectableStateEnum {
enum Enum {
	Unselectable = 0, 
	Selectable = 1
};
}

//Entry 973 to Entry 1167
//Return a number to compare with selectableStateEnum to
//know if the unit is selectable (will display the value
//in memory though bool would seem a more logical return
//value)
//If the unit is not handled through this array, this
//return selectableStateEnum::Selectable (1) (since it
//seems what's not in array would be selectable)
u8 unselectableUnitsStateUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranNuclearMissile && unit_id <= UnitId::Special_RightPitDoor)
		return *(u8*)(0x0046ee6e + unit_id - UnitId::TerranNuclearMissile);
	else
		return selectableStateEnum::Selectable;

}

//Entry 973 to Entry 1167
//Return the pointer to memory where the byte to be
//compared with selectableStateEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* unselectableUnitsStateUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranNuclearMissile && unit_id <= UnitId::Special_RightPitDoor)
		return (u8*)(0x0046ee6e + unit_id - UnitId::TerranNuclearMissile);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Hallucination
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1180
//Measured in pixels. This EXE edit uses a position that used to be program code, 
//and thus requires Entry 1179 Code Hack to work. 
//The default value is 98615807.
//Default value: 98615807
FG_SCBW_DATA(const u32*, hallucinationCustomSpellRange,							0x004f6c51);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Feedback
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1183
//Measured in pixels. This EXE edit uses a position that used to be program code, 
//and thus requires Entry 1182 Code Hack to work. 
//The default value is 98615807.
//Default value: 98615807
FG_SCBW_DATA(const u32*, feedbackCustomSpellRange,								0x004f6d86);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Defensive Matrix
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1186
//Measured in pixels. This EXE edit uses a position that used to be program code, 
//and thus requires Entry 1185 Code Hack to work. 
//The default value is 98615552.
//Default value: 98615552
FG_SCBW_DATA(const u32*, defensiveMatrixCustomSpellRange,						0x004550b5);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Ground / Nuclear Strike
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1189
//Measured in pixels. This EXE edit uses a position that used to be program code, 
//and thus requires Entry 1188 Code Hack to work. 
//The default value is 881232888.
//Default value: 881232888
FG_SCBW_DATA(const u32*, nuclearStrikeCustomNuclearStrikeRange,					0x00479233);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Subterranean Spines
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1191
//Effectively, this value is the minimum cooldown for Lurker attacks. 
//Values larger than 32 may cause the game to crash.
//Default value: 32
FG_SCBW_DATA(const u8*, subterraneanSpinesMaximumIndexForLurkerAttackArray,		0x004ed23f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Orders / Self / Unload Transport
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1192
//Affects Siege Tanks and Goliaths.
//Default value: 15
FG_SCBW_DATA(const u8*, unloadTransportWeaponCooldownOnExitingTransportSubunits, 0x004e7ffd);

//Entry 1193
//Default value: 30
FG_SCBW_DATA(const u8*, unloadTransportWeaponCooldownOnExitingTransportReaver,	0x004e80b6);

//Entry 1194
//Default value: 30
FG_SCBW_DATA(const u8*, unloadTransportSpellCooldownOnExitingTransport,			0x004e80a7);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Spellcasters
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1195
//Use UnitId::enum for values
//Default value: 172 (UnitId::ProtossShieldBattery)
FG_SCBW_DATA(const u16*, spellcastersUnitThatUsesCustomStartingEnergy,			0x0049edb3);

//Entry 1196
//Actual energy amount is (this value) / 256.
//Default value: 25600
FG_SCBW_DATA(const u16*, spellcastersCustomStartingEnergyValue,					0x0049edc7);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Bunker
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1198
//Use SpriteId::enum for values
//Default value: 377 (SpriteId::Bunker_Overlay)
FG_SCBW_DATA(const u32*, bunkerAttackSpriteOverlaySpritesDatIdNormal,			0x004780a7);

//Entry 1199
//Use SpriteId::enum for values
//Default value: 378 (SpriteId::FlameThrower)
FG_SCBW_DATA(const u32*, bunkerAttackSpriteOverlaySpritesDatIdFlame,			0x00478046);

//Entry 1200
//Use UnitId::enum for values
//Default value: 32 (UnitId::TerranFirebat)
FG_SCBW_DATA(const u16*, bunkerUnit1ThatUsesFlameSpriteUnitsDatId,				0x00477fda);

//Entry 1201
//Use UnitId::enum for values
//Default value: 10 (UnitId::Hero_GuiMontag)
FG_SCBW_DATA(const u16*, bunkerUnit2ThatUsesFlameSpriteUnitsDatId,				0x00477fe1);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Subterranean Spines
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1202
//Use WeaponId::enum for values
//This uses a weapons.dat ID (this info was removed from 
//the name to save space)
//Default value: 109 (WeaponId::SubterraneanSpines)
FG_SCBW_DATA(const u8*, subterraneanSpinesWeaponThatUsesLurkerAttackArray,		0x0048b8e6);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Spells / Spellcasting AI Connected to Unit
///
/// Entry 1204 to 1274
/// 0x004a1bd4 (Ghost) to 0x004a1c1a (Arbiter)
/// Marine or Units with UnitId higher than Observer are
/// not included (at this point, I decided to trust memory
/// array corresponding to that).
///
///Allowed values: 
///		0 - Ghost,
///		1 - ScienceVessel, 
///		2 - BattleCruiser, 
///		3 - Medic, 
///		4 - Queen, 
///		5 - Defiler, 
///		6 - Corsair, 
///		7 - DarkArchon, 
///		8 - HighTemplar, 
///		9 - Arbiter, 
///		10 - None
///		Note: using full names since there's more space here
///		than in Firegraft.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace aiSpellcastingAIEnum {
enum Enum {
	Ghost = 0,
	ScienceVessel = 1,
	BattleCruiser = 2,
	Medic = 3,
	Queen = 4,
	Defiler = 5,
	Corsair = 6,
	DarkArchon = 7,
	HighTemplar = 8,
	Arbiter = 9,
	None = 10
};
}

//Entry 1204 to Entry 1274
//Return a number to compare with energyUpgradeEnum to
//know the ai behavior for spellcaster corresponding to 
//the unit.
//If the unit is not handled through this array, this
//return aiSpellcastingAIEnum::None (11).
u8 aiSpellcastingAIConnectedToUnit(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossArbiter)
		return *(u8*)(0x004a1bd4 + unit_id - UnitId::TerranGhost);
	else
		return aiSpellcastingAIEnum::None;

}

//Entry 1204 to Entry 1274
//Return the pointer to memory where the byte to be
//compared with aiSpellcastingAIEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* aiSpellcastingAIConnectedToUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranGhost && unit_id <= UnitId::ProtossArbiter)
		return (u8*)(0x004a1bd4 + unit_id - UnitId::TerranGhost);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Weapon Damage Displayed
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1275
//Use WeaponId::enum for values
//This uses a weapons.dat ID (this info was removed from 
//the name to save space)
//This weapon will have the "per rocket" string appended 
//in the status display.
//Default value: 103 (WeaponId::HaloRockets)
FG_SCBW_DATA(const u8*, weaponDamageDisplayedWeaponToAppendSpecialString,		0x004576da);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Self / Stimpack
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1276
//Default value: 2560
FG_SCBW_DATA(const u32*, stimpackAIuseHitpointCheck,							0x004554a6);

//Entry 1277
//Default value: 2560
FG_SCBW_DATA(const u32*, stimpackAIuseHitpointSubtracted,						0x004554d3);

//Entry 1278
//Default value: 37
FG_SCBW_DATA(const u8*, stimpackAIuseTimer,										0x004554e5);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Stim Packs AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1279
//The AI will use Stim Packs only if the current target's 
//HP + shields is same or bigger than this value.
//Default value: 100
FG_SCBW_DATA(const u8*, aiStimpackMinimumTargetHpPlusShields,					0x00440142);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Lockdown AI / Target search boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1280
//Default value: 1024
FG_SCBW_DATA(const s32*, aiLockdownTargetSearchBoundaryIdle,					0x004426f1);

//Entry 1281
//Default value: 1024
FG_SCBW_DATA(const s32*, aiLockdownTargetSearchBoundaryIdleCampaignBonus,		0x004426ec);

//Entry 1282
//Default value: 288
FG_SCBW_DATA(const s32*, aiLockdownTargetSearchBoundaryUnderAttack,				0x004426cf);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Lockdown AI / High-priority
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1283
//Use UnitId::enum for values
//AI-controlled Ghosts will attempt to Lockdown this unit 
//even if it is not attacking any allies.
//Default value: 72 (UnitId::ProtossCarrier)
FG_SCBW_DATA(const u8*, aiLockdownHighPriorityUnit1,							0x004415d1);

//Entry 1284
//Use UnitId::enum for values
//AI-controlled Ghosts will attempt to Lockdown this unit 
//even if it is not attacking any allies.
//Default value: 83 (UnitId::ProtossReaver)
FG_SCBW_DATA(const u8*, aiLockdownHighPriorityUnit2,							0x004415d6);

//Entry 1285
//Use UnitId::enum for values
//AI-controlled Ghosts will attempt to Lockdown this unit 
//if it is carrying transports.
//Default value: 69 (UnitId::ProtossShuttle)
FG_SCBW_DATA(const u8*, aiLockdownHighPriorityTransport1,						0x004415b6);

//Entry 1286
//Use UnitId::enum for values
//AI-controlled Ghosts will attempt to Lockdown this unit 
//if it is carrying transports.
//Default value: 11 (UnitId::TerranDropship)
FG_SCBW_DATA(const u8*, aiLockdownHighPriorityTransport2,						0x004415bb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / EMP Shockwave AI / Target search boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1288
//Default value: 2048
FG_SCBW_DATA(const s32*, aiEmpShockwaveTargetSearchBoundaryIdle,				0x00442544);

//Entry 1289
//Default value: 288
FG_SCBW_DATA(const s32*, aiEmpShockwaveTargetSearchBoundaryUnderAttack,			0x0044253d);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / EMP Shockwave AI / Total shields in area
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1290
//For each potential target, the AI adds up the total amount of 
//shields of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 160
FG_SCBW_DATA(const s32*, aiEmpShockwaveTotalShieldsInAreaSearchBoundary,		0x00441416);

//Entry 1291
//If a potential target area has total shield points equal or 
//bigger than this value, the AI will select that target.
//Default value: 200
FG_SCBW_DATA(const u32*, aiEmpShockwaveTotalShieldsInAreaComparedValue,			0x00441439);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / EMP Shockwave AI / Total energy in area
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1293
//For each potential target, the AI adds up the total amount of 
//energy of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 160
FG_SCBW_DATA(const s32*, aiEmpShockwaveTotalEnergyInAreaSearchBoundary,			0x004414a5);

//Entry 1294
//If a potential target area has total energy points equal or 
//bigger than this value, the AI will select that target.
//Default value: 200
FG_SCBW_DATA(const u32*, aiEmpShockwaveTotalEnergyInAreaComparedValue,			0x004414c8);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Defensive Matrix AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1295
//Default value: 2048
FG_SCBW_DATA(const s32*, aiDefensiveMatrixTargetSearchBoundaryIdle,				0x004431d4);

//Entry 1296
//Default value: 288
FG_SCBW_DATA(const s32*, aiDefensiveMatrixTargetSearchBoundaryUnderAttack,		0x004431cd);

//Entry 1297
//The target's maximum HP must be same or bigger than 
//this value.
//Default value: 100
FG_SCBW_DATA(const u8*, aiDefensiveMatrixMinimumBaseHp,							0x004425fe);

//Entry 1298
//The target's current HP must be (after rounding up) 
//same or smaller than this value.
//Divide by 256 for ingame value.
//Default value: 19200
FG_SCBW_DATA(const u32*, aiDefensiveMatrixMaximumCurrentHp,						0x00442612);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Irradiate AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1299
//Default value: 2048
FG_SCBW_DATA(const s32*, aiIrradiateTargetSearchBoundaryIdle,					0x00442679);

//Entry 1300
//Default value: 288
FG_SCBW_DATA(const s32*, aiIrradiateTargetSearchBoundaryUnderAttack,			0x00442672);

//Entry 1301
//Use UnitId::enum for values
//AI-controlled Science Vessels will Irradiate 
//high-priority targets even when they are not 
//under attack.
//Default value: 42 (UnitId::ZergOverlord)
FG_SCBW_DATA(const u8*, aiIrradiateHighPriorityTarget1,							0x00441546);

//Entry 1302
//Use UnitId::enum for values
//AI-controlled Science Vessels will Irradiate 
//high-priority targets even when they are not 
//under attack.
//Default value: 34 (UnitId::TerranMedic)
FG_SCBW_DATA(const u8*, aiIrradiateHighPriorityTarget2,							0x0044154c);

//Entry 1303
//AI-controlled Science Vessels will treat any unit 
//that passes this AND flag check as high-priority 
//targets. By default, this includes peons (0x8).
//Default value: 8 (UnitProperty::Worker)
FG_SCBW_DATA(const u8*, aiIrradiateHighPriorityFlagCheckUnitPrototype,			0x00441540);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Yamato Gun AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1304
//Default value: -512
FG_SCBW_DATA(const s32*, aiYamatoGunTargetSearchBoundaryUnderAttackTop,			0x00442d66);

//Entry 1305
//Default value: 512
FG_SCBW_DATA(const s32*, aiYamatoGunTargetSearchBoundaryUnderAttackBottom,		0x00442d6e);

//Entry 1306
//Default value: -512
FG_SCBW_DATA(const s32*, aiYamatoGunTargetSearchBoundaryUnderAttackLeft,		0x00442d52);

//Entry 1307
//Default value: 512
FG_SCBW_DATA(const s32*, aiYamatoGunTargetSearchBoundaryUnderAttackRight,		0x00442d58);

//Entry 1308
//The target's current HP + shields must be same 
//or bigger than this value.
//Default value: 200
FG_SCBW_DATA(const u8*, aiYamatoGunMinimumCurrentHpPlusShield,					0x004425fe);

//Entry 1309
//The target's current HP + shields must be same 
//or smaller than this value.
//Default value: 450
FG_SCBW_DATA(const u8*, aiYamatoGunMaximumCurrentHpPlusShield,					0x004425fe);

//Entry 1310
//Use UnitId::enum for values
//Default value: 36 (UnitId::ZergEgg)
FG_SCBW_DATA(const u8*, aiYamatoGunWorthlessTarget,								0x0044212c);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Spawn Broodlings AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1312
//Default value: 288
FG_SCBW_DATA(const s32*, aiSpawnBroodlingsTargetSearchBoundaryIdle,				0x00442b02);

//Entry 1313
//Default value: 2048
FG_SCBW_DATA(const s32*, aiSpawnBroodlingsTargetSearchBoundaryUnderAttack,		0x00442b09);

//Entry 1314
//For an idle Queen to cast Broodlings on a non-priority unit, 
//the target's current HP + shields must be same or bigger 
//than this value.
//Default value: 100
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsMinimumCurrentHpPlusShields,			0x004420a2);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Spawn Broodlings AI / High-priority target
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1315
//Use UnitId::enum for values
//Default value: 30 (UnitId::TerranSiegeTankSiegeMode)
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsHighPriorityTarget1,					0x004420ad);

//Entry 1316
//Use UnitId::enum for values
//Default value: 5 (UnitId::TerranSiegeTankTankMode)
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsHighPriorityTarget2,					0x004420b3);

//Entry 1317
//Use UnitId::enum for values
//Default value: 34 (UnitId::TerranMedic)
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsHighPriorityTarget3,					0x004420b9);

//Entry 1318
//AI-controlled Queens will treat any unit that passes 
//this AND flag check as high-priority targets. 
//By default, this includes peons (0x8).
//Default value: 8 (UnitProperty::Worker)
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsHighPriorityFlagCheckUnitPrototype,	0x004420a7);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Dark Swarm AI / Target search boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1320
//Default value: 1024
FG_SCBW_DATA(const s32*, aiDarkSwarmTargetSearchBoundaryIdle,					0x00442871);

//Entry 1321
//Default value: 1024
FG_SCBW_DATA(const s32*, aiDarkSwarmTargetSearchBoundaryIdleCampaignBonus,		0x0044286c);

//Entry 1322
//Default value: 288
FG_SCBW_DATA(const s32*, aiDarkSwarmTargetSearchBoundaryUnderAttack,			0x0044284f);

//Entry 1323
//AI-controlled Defilers will not use Dark Swarm on any 
//friendly/allied unit that passes this AND flag check. 
//By default, this includes air units (0x4).
//Default value: 4 (UnitProperty::Flyer)
FG_SCBW_DATA(const u8*, aiDarkSwarmExclusionFlagCheckStatus,					0x004418d4);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Plague AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1325
//Default value: 4096
FG_SCBW_DATA(const s32*, aiPlagueTargetSearchBoundaryIdle,						0x004427f4);

//Entry 1326
//Default value: 288
FG_SCBW_DATA(const s32*, aiPlagueTargetSearchBoundaryUnderAttack,				0x004427ed);

//Entry 1327
//AI-controlled Defilers will not cast Plague on any unit 
//that passes this AND flag check. 
//By default, this includes hero units (0x40).
//Default value: 64 (UnitProperty::Hero)
FG_SCBW_DATA(const u8*, aiPlagueExclusionFlagCheckStatus,						0x004417e2);

//Entry 1328
//For each potential target, the AI adds up the total amount
//of HP of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiPlagueTotalEnemyHpInAreaSearchBoundary,				0x004417fb);

//Entry 1329
//If a potential target area has total HP equal or bigger than 
//this value, the AI will select that target.
//Default value: 250
FG_SCBW_DATA(const u32*, aiPlagueTotalEnemyHpInAreaComparedValue,				0x00441827);

//Entry 1332
//For each potential target, the AI adds up the total amount of HP 
//of all ally units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiPlagueTotalAllyLifeInAreaSearchBoundary,				0x0044183f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Ensnare AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1334
//Default value: 1024
FG_SCBW_DATA(const s32*, aiEnsnareTargetSearchBoundaryIdle,						0x00442791);

//Entry 1335
//Default value: 1024
FG_SCBW_DATA(const s32*, aiEnsnareTargetSearchBoundaryIdleCampaignBonus,		0x0044278c);

//Entry 1336
//Default value: 288
FG_SCBW_DATA(const s32*, aiEnsnareTargetSearchBoundaryUnderAttack,				0x0044276f);

//Entry 1338
//AI-controlled Queens will not cast Ensnare on any unit that passes
//this AND flag check. By default, this includes buildings (0x20000).
//Default value: 131072 (UnitProperty::CreepBuilding)
FG_SCBW_DATA(const u8*, aiEnsnareExclusionFlagCheckStatus,						0x004417e2);

//Entry 1340
//For each potential target, the AI adds up the total amount of 
//HP + shields of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiEnsnareTotalEnemyLifeInAreaSearchBoundary,			0x0044172b);

//Entry 1341
//If a potential target area has total HP + shields equal or bigger 
//than this value, the AI will select that target.
//Default value: 250
FG_SCBW_DATA(const u32*, aiEnsnareTotalEnemyLifeInAreaComparedValue,			0x00441757);

//Entry 1343
//For each potential target, the AI adds up the total amount of HP 
//of all ally units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiEnsnareTotalAllyLifeInAreaSearchBoundary,			0x0044176f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Parasite AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1345
//Default value: 2048
FG_SCBW_DATA(const s32*, aiParasiteTargetSearchBoundaryIdle,					0x00442aa4);

//Entry 1346
//Default value: 288
FG_SCBW_DATA(const s32*, aiParasiteTargetSearchBoundaryUnderAttack,				0x00442a9d);

//Entry 1347
//For an idle Queen to cast Parasite on a non-priority unit, 
//the target's current HP + shields must be same or bigger 
//than this value.
//Default value: 300
FG_SCBW_DATA(const u32*, aiParasiteMinimumCurrentHpPlusShields,					0x00441c31);

//Entry 1353
//AI-controlled Queens will treat any unit that passes 
//this AND flag check as high-priority targets. 
//By default, this includes peons (0x8).
//Default value: 8 (UnitProperty::Worker)
FG_SCBW_DATA(const u8*, aiParasiteHighPriorityFlagCheckUnitPrototype,			0x00441c26);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Psionic Storm AI / Target search boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1354
//Default value: 1024
FG_SCBW_DATA(const s32*, aiPsionicStormSearchBoundaryIdle,						0x00442966);

//Entry 1355
//Default value: 1024
FG_SCBW_DATA(const s32*, aiPsionicStormTargetSearchBoundaryIdleCampaignBonus,	0x00442961);

//Entry 1356
//Default value: 288
FG_SCBW_DATA(const s32*, aiPsionicStormTargetSearchBoundaryUnderAttack,			0x00442944);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Psionic Storm AI / Total enemy life in area
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1357
//Default value: -96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalEnemyLifeInAreaSearchBoundaryTop,	0x00441999);

//Entry 1358
//Default value: 96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalEnemyLifeInAreaSearchBoundaryBottom,	0x004419a0);

//Entry 1359
//Default value: -96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalEnemyLifeInAreaSearchBoundaryLeft,	0x0044198e);

//Entry 1360
//Default value: 96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalEnemyLifeInAreaSearchBoundaryRight,	0x00441991);

//Entry 1361
//If a potential target area has total HP + shields equal or bigger 
//than this value, the AI will select that target.
//Default value: 250
FG_SCBW_DATA(const u32*, aiPsionicStormTotalEnemyLifeInAreaComparedValue,		0x004419da);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Psionic Storm AI / Total ally life in area
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1363
//Default value: -96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalAllyLifeInAreaSearchBoundaryTop,		0x00441a02);

//Entry 1364
//Default value: 96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalAllyLifeInAreaSearchBoundaryBottom,	0x00441a09);

//Entry 1365
//Default value: -96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalAllyLifeInAreaSearchBoundaryLeft,	0x004419f8);

//Entry 1366
//Default value: 96
FG_SCBW_DATA(const s8*, aiPsionicStormTotalAllyLifeInAreaSearchBoundaryRight,	0x004419fb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Hallucination AI / Target search boundary Idle
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1368
//Default value: -1024
FG_SCBW_DATA(const s32*, aiHallucinationTargetSearchBoundaryIdleTop,			0x0044325d);

//Entry 1369
//Default value: 1024
FG_SCBW_DATA(const s32*, aiHallucinationTargetSearchBoundaryIdleBottom,			0x00443265);

//Entry 1370
//Default value: -1024
FG_SCBW_DATA(const s32*, aiHallucinationTargetSearchBoundaryIdleLeft,			0x00443249);

//Entry 1371
//Default value: 1024
FG_SCBW_DATA(const s32*, aiHallucinationTargetSearchBoundaryIdleRight,			0x0044324f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Hallucination AI / Target Units
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1374
//Use UnitId::enum for values
//Default value: 72 (UnitId::ProtossCarrier)
FG_SCBW_DATA(const u8*, aiHallucinationTarget1,									0x00442906);

//Entry 1375
//Use UnitId::enum for values
//Default value: 70 (UnitId::ProtossScout)
FG_SCBW_DATA(const u8*, aiHallucinationTarget2,									0x0044290c);

//Entry 1376
//Use UnitId::enum for values
//Default value: 71 (UnitId::ProtossArbiter)
FG_SCBW_DATA(const u8*, aiHallucinationTarget3,									0x00442912);

//Entry 1377
//Use UnitId::enum for values
//Default value: 68 (UnitId::ProtossArchon)
FG_SCBW_DATA(const u8*, aiHallucinationTarget4,									0x00442918);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Recall AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1378
//Use UnitId::enum for values
//Default value: 72 (UnitId::ProtossCarrier)
FG_SCBW_DATA(const u8*, aiRecallTarget1,										0x00442906);

//Entry 1379
//Use UnitId::enum for values
//Default value: 82 (UnitId::Hero_Gantrithor)
FG_SCBW_DATA(const u8*, aiRecallTarget2,										0x0044290c);

//Entry 1380
//Use UnitId::enum for values
//Default value: 83 (UnitId::ProtossReaver)
FG_SCBW_DATA(const u8*, aiRecallTarget3,										0x00442912);
	
//Entry 1381
//Use UnitId::enum for values
//Default value: 81 (UnitId::Hero_Warbringer)
FG_SCBW_DATA(const u8*, aiRecallTarget4,										0x00442918);

//Entry 1382
//The target's shield points must be (after rounding down) same or 
//smaller than this value.Divide by 256 for ingame value."
//Default value: 2560
FG_SCBW_DATA(const u32*, aiRecallMaximumShieldPoints,							0x004407cb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Stasis Field AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1384
//Default value: 1024
FG_SCBW_DATA(const s32*, aiStasisFieldSearchBoundaryIdle,						0x004429e1);

//Entry 1385
//Default value: 1024
FG_SCBW_DATA(const s32*, aiStasisFieldTargetSearchBoundaryIdleCampaignBonus,	0x004429dc);

//Entry 1386
//Default value: 288
FG_SCBW_DATA(const s32*, aiStasisFieldTargetSearchBoundaryUnderAttack,			0x004429bf);

//Entry 1387
//AI-controlled Arbiters will not use Stasis Field on any unit 
//that passes this AND flag check. 
//By default, this includes buildings (0x1).
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u8*, aiStasisFieldExclusionFlagCheckUnitPrototype,			0x00441a84);

//Entry 1389
//For each potential target, the AI adds up the total amount of 
//HP + shields of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiStasisFieldTotalEnemyLifeInAreaSearchBoundary,		0x00441add);

//Entry 1390
//If a potential target area has total HP + shields equal or bigger 
//than this value, the AI will select that target.
//Default value: 250
FG_SCBW_DATA(const u32*, aiStasisFieldTotalEnemyLifeInAreaComparedValue,		0x00441b09);

//Entry 1391
//For each potential target, the AI adds up the total amount of 
//HP + shields of all ally units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiStasisFieldTotalAllyLifeInAreaSearchBoundary,		0x00441b21);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Restoration AI / Target search boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1394
//Default value: -1024
FG_SCBW_DATA(const s32*, aiRestorationTargetSearchBoundaryTop,					0x00440c62);

//Entry 1395
//Default value: 1024
FG_SCBW_DATA(const s32*, aiRestorationTargetSearchBoundaryBottom,				0x00440c6a);

//Entry 1396
//Default value: -1024
FG_SCBW_DATA(const s32*, aiRestorationTargetSearchBoundaryLeft,					0x00440c4e);

//Entry 1397
//Default value: 1024
FG_SCBW_DATA(const s32*, aiRestorationTargetSearchBoundaryRight,				0x00440c54);

//Entry 1398
//The target's current HP + shields must be bigger than this value.
//Default value: 60
FG_SCBW_DATA(const u32*, aiRestorationMinimumCurrentHpPlusShields,				0x00440824);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Disruption Web AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1405
//Default value: 2048
FG_SCBW_DATA(const s32*, aiDisruptionWebSearchBoundaryIdle,						0x00442ce1);

//Entry 1406
//Default value: 2048
FG_SCBW_DATA(const s32*, aiDisruptionWebTargetSearchBoundaryIdleCampaignBonus,	0x00442cdc);

//Entry 1407
//Default value: 288
FG_SCBW_DATA(const s32*, aiDisruptionWebTargetSearchBoundaryUnderAttack,		0x00442cbf);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Mind Control AI /
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1409
//Default value: -1024
FG_SCBW_DATA(const s32*, aiMindControlTargetSearchBoundaryTop,					0x00442b82);

//Entry 1410
//Default value: 1024
FG_SCBW_DATA(const s32*, aiMindControlTargetSearchBoundaryBottom,				0x00442b8a);

//Entry 1411
//Default value: -1024
FG_SCBW_DATA(const s32*, aiMindControlTargetSearchBoundaryLeft,					0x00442b6e);

//Entry 1412
//Default value: 1024
FG_SCBW_DATA(const s32*, aiMindControlTargetSearchBoundaryRight,				0x00442b74);


//Entry 1413
//AI-controlled Dark Archons will not Mind Control any unit 
//that passes this AND flag check. 
//By default, this includes hero units (0x40).
//Default value: 64 (UnitProperty::Hero)
FG_SCBW_DATA(const u8*, aiMindControlExclusionFlagCheckUnitPrototype,			0x00441c6e);

//Entry 1414
//Use UnitId::enum for values
//This unit will not be targeted if it is empty.
//Default value: 69 (UnitId::ProtossShuttle)
FG_SCBW_DATA(const u8*, aiMindControlHighPriorityTransportUnit1,				0x00441c73);

//Entry 1415
//Use UnitId::enum for values
//This unit will not be targeted if it is empty.
//Default value: 11 (UnitId::TerranDropship)
FG_SCBW_DATA(const u8*, aiMindControlHighPriorityTransportUnit2,				0x00441c78);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Mind Control AI - High-Priority Targets
///
/// Entry 1416 to 1514
/// 0x00441cd4 (Siege Tank (Tank Mode)) to 0x00441d36 (Lurker)
/// Units with UnitId lower than Siege Tank or higher than Lurker are
/// not included (at this point, I decided to trust memory
/// array corresponding to that).
///
///Allowed values: 
///		0 - high priority, 
///		1 - low priority 
///		(will not Mind Control if either mineral or gas cost is lower than a Dark Templar's mineral/gas cost)
////////////////////////////////////////////////////////////////////////////////////////////////

namespace aiMindControlPriorityEnum {
enum Enum {
	HighPriority = 0, 
	LowPriority = 1
};
}

//Entry 1416 to Entry 1514
//Return a number to compare with aiMindControlPriorityEnum
//to know the mind control priority corresponding to 
//the unit.
//If the unit is not handled through this array, this
//return aiMindControlPriorityEnum::LowPriority (1).
u8 aiMindControlHighPriorityTarget(u8 unit_id) {

	if(unit_id >= UnitId::TerranSiegeTankTankMode && unit_id <= UnitId::ZergLurker)
		return *(u8*)(0x004a1bd4 + unit_id - UnitId::TerranSiegeTankTankMode);
	else
		return aiMindControlPriorityEnum::LowPriority;

}

//Entry 1416 to Entry 1514
//Return the pointer to memory where the byte to be
//compared with aiSpellcastingAIEnum and defined in 
//Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* aiMindControlHighPriorityTarget_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranSiegeTankTankMode && unit_id <= UnitId::ZergLurker)
		return (u8*)(0x004a1bd4 + unit_id - UnitId::TerranSiegeTankTankMode);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Feedback Web AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1515
//Default value: 288
FG_SCBW_DATA(const s32*, aiFeedbackTargetSearchBoundaryUnderAttack,				0x00442bbf);

//Entry 1516
//Default value: 1024
FG_SCBW_DATA(const s32*, aiFeedbackTargetSearchBoundaryIdle,					0x00442be1);

//Entry 1517
//Default value: 1024
FG_SCBW_DATA(const s32*, aiFeedbackTargetSearchBoundaryIdleCampaignBonus,		0x00442bdc);

//Entry 1518
//AI-controlled Dark Archons will not use Feedback on any unit 
//that passes this AND flag check. 
//By default, this includes grounded buildings. (0x2).
//Default value: 2 (UnitStatus::GroundedBuilding)
FG_SCBW_DATA(const u8*, aiFeedbackExclusionFlagCheckStatus,						0x00441d71);

//Entry 1519
//AI-controlled Dark Archons will not use Feedback on any unit 
//that passes this AND flag check. 
//By default, this includes hero units (0x40).
//Default value: 64 (UnitProperty::Hero)
FG_SCBW_DATA(const u8*, aiFeedbackExclusionFlagCheckUnitPrototype,				0x00441d76);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Optical Flare AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1521
//Default value: 1024
FG_SCBW_DATA(const s32*, aiOpticalFlareTargetSearchBoundaryIdle,				0x00442a44);

//Entry 1522
//Default value: 288
FG_SCBW_DATA(const s32*, aiOpticalFlareTargetSearchBoundaryUnderAttack,			0x00442a3d);

//Entry 1524
//AI-controlled Medics will not use Optical Flare on any unit 
//that passes this AND flag check. 
//By default, this includes buildings (0x1).
FG_SCBW_DATA(const u8*, aiOpticalFlareExclusionFlagCheckUnitPrototype,			0x00441b6b);

//Entry 1526
//For a Medic to cast Optical Flare on a non-priority unit, 
//the target's current HP + shields must be bigger than 
//this value.
//Default value: 80
FG_SCBW_DATA(const u8*, aiOpticalFlareMinimumCurrentHpPlusShields,				0x00441b95);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Maelstrom AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1527
//Default value: 1024
FG_SCBW_DATA(const s32*, aiMaelstromTargetSearchBoundaryIdle,					0x00442c66);

//Entry 1528
//Default value: 1024
FG_SCBW_DATA(const s32*, aiMaelstromTargetSearchBoundaryIdleCampaignBonus,		0x00442c61);

//Entry 1529
//Default value: 288
FG_SCBW_DATA(const s32*, aiMaelstromTargetSearchBoundaryUnderAttack,			0x00442c44);

//Entry 1531
//AI-controlled Dark Archons will use Maelstrom only on units that 
//pass this AND flag check. 
//By default, this includes organic units (0x10000).
//Default value: 65536 (UnitProperty::Organic)
FG_SCBW_DATA(const u32*, aiMaelstromInclusionFlagCheckUnitPrototype,			0x00441dde);

//Entry 1532
//AI-controlled Dark Archons will not use Maelstrom on any unit that 
//passes this AND flag check. 
//By default, this includes buildings (0x1).
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u32*, aiMaelstromExclusionFlagCheckUnitPrototype,			0x00441e1e);

//Entry 1533
//Use UnitId::enum for values 
//AI-controlled Dark Archons will always attempt to cast Maelstrom 
//on this unit if it is carrying transports.
//Default value: 42 (UnitId::ZergOverlord)
FG_SCBW_DATA(const u16*, aiMaelstromHighPriorityTransportUnit,					0x00441dfb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Maelstrom AI / Life in Area
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1389
//For each potential target, the AI adds up the total amount of 
//HP + shields of all enemy units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiMaelstromTotalEnemyLifeInAreaSearchBoundary,			0x00441e64);

//Entry 1390
//If a potential target area has total HP + shields equal or bigger 
//than this value, the AI will select that target.
//Default value: 250
FG_SCBW_DATA(const u32*, aiMaelstromTotalEnemyLifeInAreaComparedValue,			0x00441e8b);

//Entry 1391
//For each potential target, the AI adds up the total amount of 
//HP + shields of all ally units within a box surrounding the target. 
//This value determines the size of the box.
//Default value: 96
FG_SCBW_DATA(const s32*, aiMaelstromTotalAllyLifeInAreaSearchBoundary,			0x00441ea3);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Maelstrom AI - Blacklist
///
/// Entry 1539 to 1601
/// 0x00441ee0 (Larva) to 0x00441f1e (Lurker Egg)
/// Units with UnitId lower than Larva or higher than Lurker Egg
/// are not included (at this point, I decided to trust memory
/// array corresponding to that).
///
/// Allowed values: 
///		0 - blacklisted, 
///		1 - not blacklisted
////////////////////////////////////////////////////////////////////////////////////////////////

namespace aiMaelstromBlacklistEnum {
enum Enum {
	Blacklisted = 0, 
	NotBlacklisted = 1
};
}

//Entry 1539 to Entry 1601
//Return a number to compare with aiMaelstromBlacklistEnum
//to know if the unit is blacklisted from targets of
//Maelstrom.
//If the unit is not handled through this array, this
//return aiMaelstromBlacklistEnum::NotBlacklisted (1).
u8 aiMaelstromBlacklistedTarget(u8 unit_id) {

	if(unit_id >= UnitId::ZergLarva && unit_id <= UnitId::ZergLurkerEgg)
		return *(u8*)(0x00441ee0 + unit_id - UnitId::ZergLarva);
	else
		return aiMindControlPriorityEnum::LowPriority;

}

//Entry 1539 to Entry 1601
//Return the pointer to memory where the byte to be
//compared with aiMaelstromBlacklistEnum and defined
//in Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* aiMaelstromBlacklistedTarget_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::ZergLarva && unit_id <= UnitId::ZergLurkerEgg)
		return (u8*)(0x00441ee0 + unit_id - UnitId::ZergLarva);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Abilities / Nuclear Strike AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1602
//Default value: -192
FG_SCBW_DATA(const s32*, aiNuclearStrikeTotalEnemyLifeInAreaSearchBoundaryTop,	0x0044167b);

//Entry 1603
//Default value: 192
FG_SCBW_DATA(const s32*, aiNuclearStrikeTotalEnemyLifeInAreaSearchBoundaryBottom,0x00441685);

//Entry 1604
//Default value: -192
FG_SCBW_DATA(const s32*, aiNuclearStrikeTotalEnemyLifeInAreaSearchBoundaryLeft,	0x0044166c);

//Entry 1605
//Default value: 192
FG_SCBW_DATA(const s32*, aiNuclearStrikeTotalEnemyLifeInAreaSearchBoundaryRight,0x00441671);

//Entry 1606
//If a potential target area has total HP + shields equal or bigger 
//than this value, the AI will select that target. 
//Note that defensive structures and Lurkers are automatically 
//assigned a value of 800.
//Default value: 800
FG_SCBW_DATA(const u32*, aiNuclearStrikeTotalEnemyLifeInAreaComparedValue,		0x004416af);

////////////////////////////////////////////////////////////////////////////////////////////////
/// AI Management / Tech / Spawn Broodlings AI
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1607
//AI-controlled Queens will not spawn Broodlings on any unit 
//that passes this AND flag check. 
//By default, this includes heroes (0x40).
//Default value: 64 (UnitProperty::Hero)
FG_SCBW_DATA(const u8*, aiSpawnBroodlingsExclusionFlagCheckUnitPrototype,		0x00442087);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Spawn Broodlings
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1620
//If the target unit passes this flag check, no Broodlings 
//will be created. 
//By default, this includes hallucinations (0x40000000).
//Default value: 1073741824 (UnitStatus::IsHallucination)
FG_SCBW_DATA(const u32*, spawnBroodlingsBroodlingCreationFlagCheckStatus,		0x004f4951);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Consume
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1621
//If the target unit passes this flag check, 
//it will not give energy when Consumed. 
//By default, this includes hallucinations (0x40000000).
//Default value: 1073741824 (UnitStatus::IsHallucination)
FG_SCBW_DATA(const u32*, consumeEnergyGainFlagCheckStatus,						0x004f47f3);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Recall / Effect location boundary
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1622
//Default value: -64
FG_SCBW_DATA(const s8*, recallEffectLocationBoundaryTop,						0x004944b5);

//Entry 1623
//Default value: 64
FG_SCBW_DATA(const s8*, recallEffectLocationBoundaryBottom,						0x004944b8);

//Entry 1624
//Default value: -64 
FG_SCBW_DATA(const s8*, recallEffectLocationBoundaryLeft, 						0x004944ae);

//Entry 1625
//Default value: 64
FG_SCBW_DATA(const s8*, recallEffectLocationBoundaryRight,						0x004944bb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Recall / Exclusion flag check
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1626
//Units that pass this flag check are not recalled. 
//By default, this excludes buildings (0x1).
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u8*, recallExclusionFlagCheck1UnitPrototype,					0x00494421);

//Entry 1627
//Units that pass this flag check are not recalled. 
//By default, this excludes invincible units (0x4000000).
//Default value: 67108864 (UnitStatus::Invincible)
FG_SCBW_DATA(const u32*, recallExclusionFlagCheck2Status,						0x0049442d);

//Entry 1628
//Units that pass this flag check are not recalled. 
//By default, this excludes burrowed units (0x10).
//Default value: 16 (UnitStatus::Burrowed)
FG_SCBW_DATA(const u8*, recallExclusionFlagCheck3Status,						0x00494435);

//Entry 1629
//Units that pass this flag check are not recalled. 
//By default, this excludes hallucinations (0x40000000).
//Default value: 1073741824
FG_SCBW_DATA(const u32*, recallExclusionFlagCheck4Status,						0x0049444c);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Recall / Unit that cannot be recalled
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1631
//Use UnitId::enum for values 
//Default value: 35 (UnitId::ZergLarva)
FG_SCBW_DATA(const u16*, recallUnitThatCannotBeRecalled1,						0x0049443a);

//Entry 1631
//Use UnitId::enum for values 
//Default value: 36 (UnitId::ZergEgg)
FG_SCBW_DATA(const u16*, recallUnitThatCannotBeRecalled2,						0x00494440);

//Entry 1632
//Use UnitId::enum for values 
//Default value: 97 (UnitId::ZergLurkerEgg)
FG_SCBW_DATA(const u16*, recallUnitThatCannotBeRecalled3,						0x00494446);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Stasis Field
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1634
//Units that pass this flag check are immune to Stasis Field. 
//By default, this includes invincible units (0x4000000).
//Default value: 67108864 (UnitStatus::Invincible)
FG_SCBW_DATA(const u32*, stasisFieldImmunityFlagCheck1Status,					0x004f68db);

//Entry 1635
//Units that pass this flag check are immune to Stasis Field. 
//By default, this includes buildings (0x1).
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u8*, stasisFieldImmunityFlagCheck2UnitPrototype,				0x004f68ec);

//Entry 1636
//Units that pass this flag check are immune to Stasis Field. 
//By default, this includes burrowed units (0x10).
//Default value: 16 (UnitStatus::Burrowed)
FG_SCBW_DATA(const u8*, stasisFieldImmunityFlagCheck3Status,					0x004f68f0);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Restoration, Mind Control, Optical Flare / Self-destruction flag check
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1637
//Units that pass this flag check are destroyed by Restoration. 
//By default, this includes hallucinations (0x40000000).
//Default value: 1073741824 (UnitStatus::IsHallucination)
FG_SCBW_DATA(const u32*, restorationSelfDestructionFlagCheckStatus,				0x00455251);

//Entry 1638
//Units that pass this flag check are destroyed by Mind Control. 
//By default, this includes hallucinations (0x40000000).
//Default value: 1073741824 (UnitStatus::IsHallucination)
FG_SCBW_DATA(const u32*, mindControlSelfDestructionFlagCheckStatus,				0x004f69f9);

//Entry 1639
//Units that pass this flag check are destroyed by Optical Flare. 
//By default, this includes hallucinations (0x40000000).
//Default value: 1073741824 (UnitStatus::IsHallucination)
FG_SCBW_DATA(const u32*, opticalFlareSelfDestructionFlagCheckStatus,			0x0045517c);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Abilities / Target / Glave Wurm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1640
//Because StarCraft only checks for the two previous bounce targets, 
//each projectile will usually cycle among three targets, 
//unless one of the targets die mid-bounce. 
//Large values (around 40 or more?) cause the game to crash. 
//See also: Damage divisor apply check
//Default value: 3
FG_SCBW_DATA(const u8*, glaveWurmBounceCount,									0x0048c1b7);

//Entry 1641
//Default value: 3
FG_SCBW_DATA(const u8*, glaveWurmDamageDivisor,									0x0048b7c4);

//Entry 1642
//This value controls how many times the damage is divided 
//for each last bounce. For practical results, 
//this value must be 1 less than the bounce count.
//Default value: 2
FG_SCBW_DATA(const u8*, glaveWurmBounceDamageDivisorApplyCheck,					0x0048b7bb);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Weapon Cooldown
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1643
//Default value: 250
FG_SCBW_DATA(const u32*, weaponCooldownMaximumCooldownComparedValue,			0x00475e24);

//Entry 1644
//Default value: 250
FG_SCBW_DATA(const u32*, weaponCooldownMaximumCooldownSetValue,					0x00475e36);

//Entry 1645
//Default value: 5
FG_SCBW_DATA(const u8*, weaponCooldownMinimumCooldownComparedValue,				0x00475e2c);

//Entry 1646
//Default value: 5
FG_SCBW_DATA(const u8*, weaponCooldownMinimumCooldownSetValue,					0x00475e30);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Psionic Storm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1649
//This value controls all weapons that have the 
//"Persist on Target Site" behavior. 
//Technically, such weapons can deal damage when 
//the weapon sprite's timer is not  zero, 
//and is cleanly divisible by this value 
//(i.e. the remainder/modulo is zero).
//Default value: 7
FG_SCBW_DATA(const u32*, psionicStormIntervalBetweenDamageHits,					0x0048bcd7);

//Entry 1650
//Use WeaponId::enum for values 
//If the weapon with this weapons.dat ID deals 
//splash damage, it will not stack.
//Default value: 84 (WeaponId::PsiStorm)
FG_SCBW_DATA(const u8*, psionicStormWeaponsDatIdCheck,							0x0048b5db);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Splash Damage
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1651
//Use WeaponId::enum for values 
//Default value: 84 (WeaponId::PsiStorm)
FG_SCBW_DATA(const u8*, splashDamageWeaponsDatIdThatCanDamageSelf,				0x0048b57f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Psionic Storm
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1653
//The actual number of frames is (this value) * 8.
//Default value: 7
FG_SCBW_DATA(const u8*, psionicStormNoStackCooldown,							0x0048b5f2);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Splash Damage / Damage divisors
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1654
//Default value: 1
FG_SCBW_DATA(const u8*, splashDamageInnerSplashDamageDivisorRadialPerEnemy,		0x0048b615);

//Entry 1655
//Default value: 1
FG_SCBW_DATA(const u8*, splashDamageInnerSplashDamageDivisorAir,				0x0048b89b);

//Entry 1656
//Default value: 2
FG_SCBW_DATA(const u8*, splashDamageMediumSplashDamageDivisor,					0x0048b65d);

//Entry 1657
//Default value: 4
FG_SCBW_DATA(const u8*, splashDamageOuterSplashDamageDivisor,					0x0048b66f);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Splash Damage / Partial Immunity
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1658
//Units that pass this flag check are immune to the medium/outer splash damage. 
//By default, this includes burrowed units (0x10). 
//Note that these units are still affected by the inner splash damage.
//Default value: 16 (UnitStatus::Burrowed)
FG_SCBW_DATA(const u8*, splashDamagePartialImmunityFlagCheckStatus,				0x0048b62c);

//Entry 1659
//Use UnitId::enum for values 
//This unit is completely unaffected by the medium/outer splash damage of 
//weapons that have the "Splash (air)" type.
//Default value: 73 (UnitId::ProtossInterceptor)
FG_SCBW_DATA(const u8*, splashDamageUnitThatIsPartiallyImmuneToAirSplash,		0x0048b641);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Game Loop / Unit Timers
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1660
//Every (this value) number of frames, the game updates the following 
//special ability-related timers: Stasis Field, Stim Packs, Ensnare, 
//Defensive Matrix, Irradiate, Lockdown, Maelstrom, Plague, 
//Psi Storm (no-stack timer), and Acid Spores.
//Default value: 8
FG_SCBW_DATA(const u8*, gameLoopUnitTimersIntervalBetweenEffectTimerUpdates,	0x004ec340);

//Entry 1661
//Controls various order-related delays, such as burrowing/unburrowing 
//delays, the length of pauses between queued orders, interval between 
//launching/returning interceptors, etc. Not completely understood.
//Default value: 8
FG_SCBW_DATA(const u8*, gameLoopUnitTimersIntervalBetweenOrderChanges1,			0x004ec711);

//Entry 1662
//Controls various order-related delays. Not completely understood.
//Default value: 8
FG_SCBW_DATA(const u8*, gameLoopUnitTimersIntervalBetweenOrderChanges2,			0x004ebf56);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Limits / Bullet Limits
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1664
//Use WeaponId::enum for values 
//Default value is 103 (Halo Rockets).
//Default value: 103 (WeaponId::HaloRockets)
FG_SCBW_DATA(const u8*, limitsBulletLimitsSpecialLimitLimitedWeaponId,			0x0048c270);

//Entry 1665
//If the current bullet count reaches this limit, 
//"specially limited" weapons will not fire. 
//This limit value must be between 0 and 100.
//Default value: 80
FG_SCBW_DATA(const u8*, limitsBulletLimitsSpecialLimitLimitAmount,				0x0048c279);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Ensnare
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1668
//Units that pass this flag check are not Ensnared. 
//The default value is 0x10 (burrowed units).
//Default value: 16 (UnitStatus::Burrowed)
FG_SCBW_DATA(const u8*, ensnareExclusionFlagCheck2Status,						0x004f46e0);

//Entry 1669
//Units that pass this flag check are not Ensnared. 
//The default value is 0x1 (buildings).
//Default value: 1 (UnitProperty::Building)
FG_SCBW_DATA(const u8*, ensnareExclusionFlagCheck3SpecialAbility,				0x004f46cf);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Mind Control - Blacklist
///
/// Entry 1670 to 1754
/// 0x00491fc8 (Vulture Spider Mine) to 0x0049201c (Lurker Egg)
/// Units with UnitId lower than Spider Mine or higher than 
/// Lurker Egg are not included (at this point, I decided to 
/// trust memory array corresponding to that).
///
/// Allowed values: 
//		0 - Cannot be Mind Controlled, 
//		1 - Can be Mind Controlled.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace mindControlBlacklistEnum {
enum Enum {
	CannotBeMindControlled = 0, 
	CanBeMindControlled = 1
};
}

//Entry 1670 to Entry 1754
//Return a number to compare with mindControlBlacklistEnum
//to know if the unit can be mind controlled or not.
//If the unit is not handled through this array, this
//return mindControlBlacklistEnum::CanBeMindControlled (1).
u8 mindControlBlacklistedTarget(u8 unit_id) {

	if(unit_id >= UnitId::TerranVultureSpiderMine && unit_id <= UnitId::ZergLurkerEgg)
		return *(u8*)(0x00491fc8 + unit_id - UnitId::TerranVultureSpiderMine);
	else
		return aiMindControlPriorityEnum::LowPriority;

}

//Entry 1670 to Entry 1754
//Return the pointer to memory where the byte to be
//compared with mindControlBlacklistEnum and defined
//in Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* mindControlBlacklistedTarget_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::TerranVultureSpiderMine && unit_id <= UnitId::ZergLurkerEgg)
		return (u8*)(0x00491fc8 + unit_id - UnitId::TerranVultureSpiderMine);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Irradiate
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1755
//Use ImageId::enum for values
//Default value: 380 (ImageId::Irradiate_Small)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayStartRemoveOnWearOff,			0x00493026);

//Entry 1758
//Use ImageId::enum for values
//Default value: 382 (ImageId::Irradiate_Large)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayEndRemoveOnWearOff,			0x00493021);

//Entry 1759
//Use ImageId::enum for values
//Default value: 380 (ImageId::Irradiate_Small)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayStartRemoveOnBurrow,			0x004F472C);

//Entry 1760
//Use ImageId::enum for values
//Default value: 382 (ImageId::Irradiate_Large)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayEndRemoveOnBurrow,			0x004F4727);

//Entry 1761
//Use ImageId::enum for values
//Default value: 380 (ImageId::Irradiate_Small)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayStartRemoveOnRestoration,		0x004552F7);

//Entry 1762
//Use ImageId::enum for values
//Default value: 382 (ImageId::Irradiate_Large)
FG_SCBW_DATA(const u32*, irradiateImagesDatOverlayEndRemoveOnRestoration,		0x004552F2);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Ensnare
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1763
//Use ImageId::enum for values
//Default value: 384 (ImageId::EnsnareOverlay_Small)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayStartRemoveOnWearOff,			0x00492FC5);

//Entry 1764
//Use ImageId::enum for values
//Default value: 386 (ImageId::EnsnareOverlay_Large)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayEndRemoveOnWearOff,				0x00492FC0);

//Entry 1765
//Use ImageId::enum for values
//Default value: 384 (ImageId::EnsnareOverlay_Small)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayStartRemoveOnBurrow,			0x004F4747);

//Entry 1766
//Use ImageId::enum for values
//Default value: 386 (ImageId::EnsnareOverlay_Large)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayEndRemoveOnBurrow,				0x004F4742);

//Entry 1767
//Use ImageId::enum for values
//Default value: 384 (ImageId::EnsnareOverlay_Small)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayStartRemoveOnRestoration,		0x0045529E);

//Entry 1768
//Use ImageId::enum for values
//Default value: 386 (ImageId::EnsnareOverlay_Large)
FG_SCBW_DATA(const u32*, ensnareImagesDatOverlayEndRemoveOnRestoration,			0x00455299);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Plague
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1769
//Use ImageId::enum for values
//Default value: 388 (ImageId::PlagueOverlay_Small)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayStartRemoveOnWearOff,			0x004930D0);

//Entry 1770
//Use ImageId::enum for values
//Default value: 390 (ImageId::PlagueOverlay_Large)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayEndRemoveOnWearOff,				0x004930CB);

//Entry 1771
//Use ImageId::enum for values
//Default value: 388 (ImageId::PlagueOverlay_Small)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayStartRemoveOnBurrow,				0x004F4762);

//Entry 1772
//Use ImageId::enum for values
//Default value: 390 (ImageId::PlagueOverlay_Large)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayEndRemoveOnBurrow,				0x004F475D);

//Entry 1773
//Use ImageId::enum for values
//Default value: 388 (ImageId::PlagueOverlay_Small)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayStartRemoveOnRestoration,		0x004552CE);

//Entry 1774
//Use ImageId::enum for values
//Default value: 390 (ImageId::PlagueOverlay_Large)
FG_SCBW_DATA(const u32*, plagueImagesDatOverlayEndRemoveOnRestoration,			0x004552C9);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Lockdown
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1775
//Use ImageId::enum for values
//Default value: 361 (ImageId::LockdownField_Small)
FG_SCBW_DATA(const u32*, lockdownImagesDatOverlayStartRemove,					0x00454DE5);

//Entry 1776
//Use ImageId::enum for values
//Default value: 363 (ImageId::LockdownField_Large)
FG_SCBW_DATA(const u32*, lockdownImagesDatOverlayEndRemove,						0x00454DE0);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Maelstrom
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1777
//Use ImageId::enum for values
//Default value: 982 (ImageId::MaelstromOverlay_Small)
FG_SCBW_DATA(const u32*, maelstromImagesDatOverlayStartRemove,					0x00454D75);

//Entry 1778
//Use ImageId::enum for values
//Default value: 984 (ImageId::MaelstromOverlay_Large)
FG_SCBW_DATA(const u32*, maelstromImagesDatOverlayEndRemove,					0x00454D70);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Ground / Stasis Field
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1779
//Use ImageId::enum for values
//Default value: 365 (ImageId::StasisField_Small)
FG_SCBW_DATA(const u32*, stasisFieldImagesDatOverlayStartRemove,				0x004F6340);

//Entry 1780
//Use ImageId::enum for values
//Default value: 367 (ImageId::StasisField_Large)
FG_SCBW_DATA(const u32*, stasisFieldImagesDatOverlayEndRemove,					0x004F633B);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Mind Control
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 1781
//Use UnitId::enum for values 
//Default value: 63 (UnitId::ProtossDarkArchon)
FG_SCBW_DATA(const u8*, mindControlUnitIdCheckForRemovingShields,				0x004F693C);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Triggers / Give Units To Player - Tech Transfer
///
/// Entry 1782 to 2057
/// 0x005011c8 (Entry 1 - Unit ID) to 0x005013ee (Entry 46 - Tech 5)
/// Data are group of 6, there's the UnitId entry follow by 5
/// TechId entries.
/// Unlike previous cases handled through functions, those return
/// 16 bits values.
/// Each entry offset is separated from the similar one of the next 
/// group by a value of 12 (0x0c)
////////////////////////////////////////////////////////////////////////////////////////////////

namespace giveUnitsToPlayerTechTransfer {

const int minEntry = 1;
const int maxEntry = 46;

//Return a value to compare with UnitId to get the
//id of the unit for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return 228 (UnitId::None)
u16 getUnitIdForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011c8 + (entryNumber-1) * 12);
	else
		return UnitId::None;

}

//Return a pointer to the memory area where the
//value to compare with UnitId to get the id of 
//the unit for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
const u16* getUnitIdForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011c8 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with TechId to get the
//id of tech1 for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return TechId::None.
//If this value is set to 44 (None), it will be treated 
//as an end-of-array mark; all tech IDs after this will 
//be ignored (this means the next Tech functions will
//return invalid or useless values)
u16 getTech1ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011ca + (entryNumber-1) * 12);
	else
		return TechId::None;

}

//Return a pointer to the memory area where the
//value to compare with TechId to get the id of 
//tech1 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech1ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011ca + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with TechId to get the
//id of tech2 for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return TechId::None.
//If this value is set to 44 (None), it will be treated 
//as an end-of-array mark; all tech IDs after this will 
//be ignored (this means the next Tech functions will
//return invalid or useless values)
u16 getTech2ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011cc + (entryNumber-1) * 12);
	else
		return TechId::None;

}

//Return a pointer to the memory area where the
//value to compare with TechId to get the id of 
//tech2 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech2ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011cc + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with TechId to get the
//id of tech3 for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return TechId::None.
//If this value is set to 44 (None), it will be treated 
//as an end-of-array mark; all tech IDs after this will 
//be ignored (this means the next Tech functions will
//return invalid or useless values)
u16 getTech3ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011ce + (entryNumber-1) * 12);
	else
		return TechId::None;

}

//Return a pointer to the memory area where the
//value to compare with TechId to get the id of 
//tech3 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech3ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011ce + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with TechId to get the
//id of tech4 for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return TechId::None.
//If this value is set to 44 (None), it will be treated 
//as an end-of-array mark; all tech IDs after this will 
//be ignored (this means the next Tech functions will
//return invalid or useless values)
u16 getTech4ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011d0 + (entryNumber-1) * 12);
	else
		return TechId::None;

}

//Return a pointer to the memory area where the
//value to compare with TechId to get the id of 
//tech4 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech4ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011d0 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with TechId to get the
//id of tech5 for the current group of data.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return TechId::None.
u16 getTech5ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005011d2 + (entryNumber-1) * 12);
	else
		return TechId::None;

}

//Return a pointer to the memory area where the
//value to compare with TechId to get the id of 
//tech5 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerTechTransfer::minEntry and
//giveUnitsToPlayerTechTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous tech descriptions)
const u16* getTech5ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005011d2 + (entryNumber-1) * 12);
	else
		return NULL;

}

} //namespace giveUnitsToPlayerTechTransfer

////////////////////////////////////////////////////////////////////////////////////////////////
/// Game / Triggers / Give Units To Player - Upgrade Transfer
///
/// Entry 2058 to 2182
/// 0x005012e0 (Entry 1 - Unit ID) to 0x005013d8 (Entry 25 - Tech 4)
/// Data are group of 5, there's the UnitId entry follow by 4
/// UpgradeId entries.
/// Unlike previous cases handled through functions, those return
/// 16 bits values.
/// Each entry offset is separated from the similar one of the next 
/// group by a value of 10 (0x0a)
////////////////////////////////////////////////////////////////////////////////////////////////

namespace giveUnitsToPlayerUpgradeTransfer {

const int minEntry = 1;
const int maxEntry = 25;

//Return a value to compare with UnitId to get the
//id of the unit for the current group of data.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return 228 (UnitId::None)
u16 getUnitIdForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005012e0 + (entryNumber-1) * 12);
	else
		return UnitId::None;

}

//Return a pointer to the memory area where the
//value to compare with UnitId to get the id of 
//the unit for the current group of data is.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return NULL.
const u16* getUnitIdForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005012e0 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with UpgradeId to get
//the id of tech1 for the current group of data.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return UpgradeId::None.
//If this value is set to 61 (None), it will be treated 
//as an end-of-array mark; all upgrade IDs after this 
//will  be ignored (this means the next Tech functions 
//will return invalid or useless values)
u16 getTech1ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005012e2 + (entryNumber-1) * 12);
	else
		return UpgradeId::None;

}

//Return a pointer to the memory area where the
//value to compare with UpgradeId to get the id 
//of tech1 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech1ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005012e2 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with UpgradeId to get
//the id of tech2 for the current group of data.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return UpgradeId::None.
//If this value is set to 61 (None), it will be treated 
//as an end-of-array mark; all upgrade IDs after this 
//will  be ignored (this means the next Tech functions 
//will return invalid or useless values)
u16 getTech2ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005012e4 + (entryNumber-1) * 12);
	else
		return UpgradeId::None;

}

//Return a pointer to the memory area where the
//value to compare with UpgradeId to get the id 
//of tech2 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech2ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005012e4 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with UpgradeId to get
//the id of tech3 for the current group of data.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return UpgradeId::None.
//If this value is set to 61 (None), it will be treated 
//as an end-of-array mark; all upgrade IDs after this 
//will  be ignored (this means the next Tech functions 
//will return invalid or useless values)
u16 getTech3ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005012e6 + (entryNumber-1) * 12);
	else
		return UpgradeId::None;

}

//Return a pointer to the memory area where the
//value to compare with UpgradeId to get the id 
//of tech3 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous function description)
const u16* getTech3ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005012e6 + (entryNumber-1) * 12);
	else
		return NULL;

}

//Return a value to compare with UpgradeId to get
//the id of tech4 for the current group of data.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return UpgradeId::None.
u16 getTech4ForEntry(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return *(u16*)(0x005012e8 + (entryNumber-1) * 12);
	else
		return UpgradeId::None;

}

//Return a pointer to the memory area where the
//value to compare with UpgradeId to get the id 
//of tech4 for the current group of data is.
//Use a value between 
//giveUnitsToPlayerUpgradeTransfer::minEntry and
//giveUnitsToPlayerUpgradeTransfer::maxEntry
//else it will return NULL.
//This will always return an offset, but it may be
//an unused one (see previous tech descriptions)
const u16* getTech4ForEntry_Pointer(int entryNumber) {

	if(entryNumber >= minEntry && entryNumber <= maxEntry)
		return (u16*)(0x005012e8 + (entryNumber-1) * 12);
	else
		return NULL;

}

} //namespace giveUnitsToPlayerUpgradeTransfer

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Creep Spreader / Creep spreading type for unit
///
/// Entry 2187 to 2202
/// 0x004138b0 (Hatchery) to 0x004138bf (Sunken Colony)
/// Units with UnitId lower than Hatchery or higher than 
/// Sunken Colony are not included (at this point, I decided to 
/// trust memory array corresponding to that).
///
/// Allowed values: 
///			0 - Spreads creep (morphed from drone), 
///			1 - spreads creep (morphed from building), 
///			2 - does not spread creep. 
///	This edit only controls creep destruction; creep creation can be enabled by changing the unit's idle order in units.dat.
////////////////////////////////////////////////////////////////////////////////////////////////

namespace creepSpreadingTypeEnum {
enum Enum {
	SpreadsCreepMorphedFromDrone = 0, 
	SpreadsCreepMorphedFromBuilding = 1, 
	DoesNotSpreadCreep = 2
};
}

//Entry 2187 to Entry 2202
//Return a number to compare with creepSpreadingTypeEnum
//to know the creep spreading type of the unit.
//If the unit is not handled through this array, this
//return creepSpreadingTypeEnum::DoesNotSpreadCreep (2).
u8 creepSpreadingTypeForUnit(u8 unit_id) {

	if(unit_id >= UnitId::ZergHatchery && unit_id <= UnitId::ZergSunkenColony)
		return *(u8*)(0x004138b0 + unit_id - UnitId::ZergHatchery);
	else
		return creepSpreadingTypeEnum::DoesNotSpreadCreep;

}

//Entry 2187 to Entry 2202
//Return the pointer to memory where the byte to be
//compared with creepSpreadingTypeEnum and defined
//in Firegraft is.
//If the unit is not handled through this array, this
//return NULL
const u8* creepSpreadingTypeForUnit_Pointer(u8 unit_id) {

	if(unit_id >= UnitId::ZergHatchery && unit_id <= UnitId::ZergSunkenColony)
		return (u8*)(0x004138b0 + unit_id - UnitId::ZergHatchery);
	else
		return NULL;

}

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Bunker
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 2203
//Should probably be a multiple of 32.
//Default value: 64
FG_SCBW_DATA(const u32*, bunkerBonusAttackRange,								0x0047587E);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Self / Spidermines
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 2204
//Default value: 60
FG_SCBW_DATA(const u8*, spiderminesDelayBeforeInitialBurrow,					0x00463E0B);

//Entry 2205
//Default value: 30
FG_SCBW_DATA(const u8*, spiderminesSelfDestructTriggerDistance,					0x00463EFC);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Tech / Target / Infestation
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 2213
//Use UnitId::enum for values 
//This unit uses Infestation as its attack order.
//Default value: 45 (UnitId::ZergQueen)
FG_SCBW_DATA(const u16*, infestationAutoInfestingUnit1Check1,					0x00402756);

//Entry 2214
//Use UnitId::enum for values 
//This unit uses Infestation as its attack order.
//Default value: 49 (UnitId::Hero_Matriarch)
FG_SCBW_DATA(const u16*, infestationAutoInfestingUnit2Check1,					0x0040275c);

//Entry 2215
//Use UnitId::enum for values 
//This unit uses Infestation as its attack order.
//Default value: 45 (UnitId::ZergQueen)
FG_SCBW_DATA(const u16*, infestationAutoInfestingUnit1Check2,					0x0043cf70);

//Entry 2216
//Use UnitId::enum for values 
//This unit uses Infestation as its attack order.
//Default value: 49 (UnitId::Hero_Matriarch)
FG_SCBW_DATA(const u16*, infestationAutoInfestingUnit2Check2,					0x0043cf76);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Orders / Self / Hold Position
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 2213
//Use UnitId::enum for values 
//Default value: 45 (UnitId::ZergQueen)
FG_SCBW_DATA(const u16*, holdPositionUnitThatUsesQueenHoldUnit1,				0x004c2106);

//Entry 2214
//Use UnitId::enum for values 
//Default value: 49 (UnitId::Hero_Matriarch)
FG_SCBW_DATA(const u16*, holdPositionUnitThatUsesQueenHoldUnit2,				0x004c210c);

////////////////////////////////////////////////////////////////////////////////////////////////
/// Units / Properties / Bunker
////////////////////////////////////////////////////////////////////////////////////////////////

//Entry 2221
//Use RaceId::enum for values
//Allowed values: 0 - Zerg, 1 - Terran, 2 - Protoss. 
//This EXE edit has no effect if Entry 2220 Jump Hack 
//is active.
//Default value: 1 (RaceId::Terran)
FG_SCBW_DATA(const u16*, bunkerRaceIdAllowedToEnter,							0x004E6E7B);

}

#endif
