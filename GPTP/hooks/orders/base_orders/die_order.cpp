#include "die_order.h"
#include <SCBW/api.h>

//helper functions def

namespace {

CThingy* createThingy(u32 spriteId, s16 x, s16 y, u32 playerId);		//0x00488210
void clearUnitSprites(CSprite* unit_sprite, CSprite* subunit_sprite);	//0x00496F00
void function_00497480(CSprite* thingySprite, u32 visibility_flags);	//0x00497480
void _UnitDestructor(CUnit* unit);										//0x004A0740
void UnitDestructor(CUnit* unit);										//0x004A0990
void hideAndDisableUnit(CUnit* unit);									//0x004E6340

} //unnamed namespace

namespace hooks {

void orders_Die(CUnit* unit) {

	bool jump_to_795AB = false;

	if(unit->userActionFlags & 4)
		hideAndDisableUnit(unit);

	if(unit->subunit != NULL) {

		clearUnitSprites(unit->sprite,unit->subunit->sprite);

		if(unit->subunit->subunit != NULL) {

			if(units_dat::BaseProperty[(unit->subunit->subunit)->id] & UnitProperty::Subunit) {
				UnitDestructor(unit->subunit->subunit);
				unit->subunit->subunit = NULL;
			}

			_UnitDestructor(unit->subunit);
			unit->subunit->sprite->free();

			unit->subunit->sprite = NULL;
			unit->subunit = NULL;

		}

	}

	unit->mainOrderState = 1;

	if(!(unit->sprite->flags & CSprite_Flags::Hidden)) {

		if(
			!(unit->status & UnitStatus::IsHallucination) ||
			unit->status & UnitStatus::IsSelfDestructing
		)
			jump_to_795AB = true;
		else {

			CThingy* hallucination_smoke;

			scbw::playSound(SoundId::Protoss_TEMPLAR_PTeHal01_WAV,unit);

			hallucination_smoke = 
				createThingy(
					SpriteId::Hallucination_Death1,
					unit->getX(),
					unit->getY(),
					0
				);

			if(hallucination_smoke != NULL) {

				//allow players to see smoke if could already see unit vanishing
				function_00497480(hallucination_smoke->sprite,unit->sprite->visibilityFlags);

			}

		}

	}

	if(!jump_to_795AB) {//79566

		hideAndDisableUnit(unit);

		if(unit->subunit != NULL) {

			if(units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit) {
				UnitDestructor(unit->subunit);
				unit->subunit = NULL;
			}

		}

		_UnitDestructor(unit);
		unit->sprite->free();
		unit->sprite = NULL;

	}
	else {
		unit->sprite->playIscriptAnim(IscriptAnimation::Death,true);
		_UnitDestructor(unit);
	}

}

;


//StarCraft.exe+79480- push ebp
//StarCraft.exe+79481- mov ebp,esp
//StarCraft.exe+79483- push ebx
//StarCraft.exe+79484- mov ebx,[ebp+08]					//EBX = unit
//StarCraft.exe+79487- test byte ptr [ebx+00000093],04	//test(unit->userActionFlags & 4)
//StarCraft.exe+7948E- push esi
//StarCraft.exe+7948F- push edi
//StarCraft.exe+79490- je StarCraft.exe+79499			//if not jump

//StarCraft.exe+79492- mov eax,ebx					//EAX = unit
//StarCraft.exe+79494- call StarCraft.exe+E6340		//unitDeathSomething_0

//79499:

//StarCraft.exe+79499- mov eax,[ebx+70]			//EAX = unit->subunit
//StarCraft.exe+7949C- test eax,eax				//if(unit->subunit == NULL)
//StarCraft.exe+7949E- je StarCraft.exe+794E6	//jump

//StarCraft.exe+794A0- mov ecx,[eax+0C]				//ECX = unit->subunit->sprite
//StarCraft.exe+794A3- mov esi,[ebx+0C]				//ESI = unit->sprite
//StarCraft.exe+794A6- call StarCraft.exe+96F00		//clearUnitSprites

//StarCraft.exe+794AB- mov esi,[ebx+70]			//ESI = unit->subunit
//StarCraft.exe+794AE- mov ecx,[esi+70]			//ECX = (unit->subunit)->subunit
//StarCraft.exe+794B1- test ecx,ecx				//if(ECX == NULL)
//StarCraft.exe+794B3- je StarCraft.exe+794CF	//jump

//StarCraft.exe+794B5- movzx eax,word ptr [ecx+64]						//EAX = ((unit->subunit)->subunit)->id
//StarCraft.exe+794B9- test byte ptr [eax*4+StarCraft.exe+264080],10	//test(units_dat::BaseProperty[((unit->subunit)->subunit)->id] & UnitProperty::Subunit
//StarCraft.exe+794C1- je StarCraft.exe+794CF							//jump if not

//StarCraft.exe+794C3- call StarCraft.exe+A0990		//UnitDestructor

//StarCraft.exe+794C8- mov [esi+70],00000000		//(unit->subunit)->subunit = NULL

//794CF:

//StarCraft.exe+794CF- mov eax,esi					//EAX = unit->subunit
//StarCraft.exe+794D1- call StarCraft.exe+A0740		//_UnitDestructor

//StarCraft.exe+794D6- mov edi,[esi+0C]				//EDI = (unit->subunit)->sprite
//StarCraft.exe+794D9- call StarCraft.exe+97B40		//SpriteDestructor (CSprite->free())

//StarCraft.exe+794DE- xor eax,eax			//EAX = 0
//StarCraft.exe+794E0- mov [esi+0C],eax		//unit->subunit->sprite = NULL
//StarCraft.exe+794E3- mov [ebx+70],eax		//unit->subunit = NULL

//794E6:

//StarCraft.exe+794E6- mov ecx,[ebx+0C]				//ECX = unit->sprite
//StarCraft.exe+794E9- mov byte ptr [ebx+4E],01		//unit->mainOrderState = 1
//StarCraft.exe+794ED- test byte ptr [ecx+0E],20	//if(unit->sprite->flags & CSprite_Flags::Hidden)
//StarCraft.exe+794F1- jne StarCraft.exe+79566		//jump

//StarCraft.exe+794F3- mov eax,[ebx+000000DC]		//EAX = unit->status
//StarCraft.exe+794F9- test eax,40000000
//StarCraft.exe+794FE- je StarCraft.exe+795AB		//if(!(unit->status & UnitStatus::IsHallucination)) jump

//StarCraft.exe+79504- test eax,eax				//if(unit->status & UnitStatus::IsSelfDestructing)
//StarCraft.exe+79506- js StarCraft.exe+795AB	//jump

//StarCraft.exe+7950C- push 00						//PUSH 0
//StarCraft.exe+7950E- mov esi,ebx					//ESI = unit
//StarCraft.exe+79510- push 01						//PUSH 1
//StarCraft.exe+79512- mov ebx,0000026B				//EBX = SoundId::Protoss_TEMPLAR_PTeHal01_WAV
//StarCraft.exe+79517- call StarCraft.exe+8ED50		//BWFXN_PlaySndFromSrc

//StarCraft.exe+7951C- mov ecx,[ebp+08]				//ECX = unit
//StarCraft.exe+7951F- mov eax,[ecx+0C]				//EAX = unit->sprite
//StarCraft.exe+79522- mov cx,[eax+16]				//CX = unit->sprite->position.y
//StarCraft.exe+79526- mov ax,[eax+14]				//AX = unit->sprite->position.x
//StarCraft.exe+7952A- movsx edx,ax					//EDX = unit->sprite->position.x
//StarCraft.exe+7952D- push 00						//PUSH 0
//StarCraft.exe+7952F- push edx						//PUSH unit->sprite->position.x
//StarCraft.exe+79530- movsx edi,cx					//EDI = unit->sprite->position.y
//StarCraft.exe+79533- push 00000176				//PUSH SpriteId::Hallucination_Death1
//StarCraft.exe+79538- call StarCraft.exe+88210		//createThingy

//StarCraft.exe+7953D- test eax,eax				//if(r_createThingy == NULL)
//StarCraft.exe+7953F- je StarCraft.exe+79563	//jump

//StarCraft.exe+79541- mov ecx,[ebp+08]				//ECX = unit
//StarCraft.exe+79544- mov edx,[ecx+0C]				//EDX = unit->sprite
//StarCraft.exe+79547- mov dl,[edx+0D]				//DL = unit->sprite->elevationLevel
//StarCraft.exe+7954A- mov esi,[eax+0C]				//ESI = r_createThingy->sprite
//StarCraft.exe+7954D- inc dl						//DL = unit->sprite->elevationLevel + 1
//StarCraft.exe+7954F- mov [esi+0D],dl				//r_createThingy->sprite->elevationLevel = unit->sprite->elevationLevel + 1
//StarCraft.exe+79552- mov ecx,[ecx+0C]				//ECX = unit->sprite
//StarCraft.exe+79555- mov ebx,[eax+0C]				//EBX = r_createThingy->sprite
//StarCraft.exe+79558- xor edx,edx					//EDX = 0
//StarCraft.exe+7955A- mov dl,[ecx+0C]				//DL = unit->sprite->visibilityFlags
//StarCraft.exe+7955D- push edx						//PUSH unit->sprite->visibilityFlags
//StarCraft.exe+7955E- call StarCraft.exe+97480		//sub_497480

//79563:

//StarCraft.exe+79563- mov ebx,[ebp+08]				//EBX = unit

//79566:

//StarCraft.exe+79566- mov eax,ebx					//EAX = unit
//StarCraft.exe+79568- call StarCraft.exe+E6340		//unitDeathSomething_0 (hide unit)

//StarCraft.exe+7956D- mov ecx,[ebx+70]			//ECX = unit->subunit
//StarCraft.exe+79570- test ecx,ecx				//if(unit->subunit == NULL)
//StarCraft.exe+79572- je StarCraft.exe+7958E	//jump

//StarCraft.exe+79574- movzx eax,word ptr [ecx+64]						//EAX = unit->subunit->id
//StarCraft.exe+79578- test byte ptr [eax*4+StarCraft.exe+264080],10	//if(units_dat::BaseProperty[unit->subunit->id] & UnitProperty::Subunit)
//StarCraft.exe+79580- je StarCraft.exe+7958E							//continue

//StarCraft.exe+79582- call StarCraft.exe+A0990		//UnitDestructor

//StarCraft.exe+79587- mov [ebx+70],00000000		//unit->subunit = NULL

//7958E:

//StarCraft.exe+7958E- mov eax,ebx					//EAX = unit
//StarCraft.exe+79590- call StarCraft.exe+A0740		//_UnitDestructor

//StarCraft.exe+79595- mov edi,[ebx+0C]				//EDI = unit->sprite
//StarCraft.exe+79598- call StarCraft.exe+97B40		//SpriteDestructor

//StarCraft.exe+7959D- pop edi
//StarCraft.exe+7959E- pop esi
//StarCraft.exe+7959F- mov [ebx+0C],00000000		//unit->sprite = NULL
//StarCraft.exe+795A6- pop ebx
//StarCraft.exe+795A7- pop ebp
//StarCraft.exe+795A8- ret 0004

//795AB:

//StarCraft.exe+795AB- push 01						//PUSH 1
//StarCraft.exe+795AD- push 01						//PUSH 1
//StarCraft.exe+795AF- call StarCraft.exe+99D00		//playSpriteIscript

//StarCraft.exe+795B4- mov eax,ebx					//EAX = unit
//StarCraft.exe+795B6- call StarCraft.exe+A0740		//_UnitDestructor

//StarCraft.exe+795BB- pop edi
//StarCraft.exe+795BC- pop esi
//StarCraft.exe+795BD- pop ebx
//StarCraft.exe+795BE- pop ebp
//StarCraft.exe+795BF- ret 0004

} //namespace hooks

//-------- Helper function definitions. Do NOT modify! --------//

namespace {

//original referenced name was replaceSprite (but this one is probably
//more accurate since it does create something rather than replacing)
const u32 Func_CreateThingy = 0x00488210;
CThingy* createThingy(u32 spriteId, s16 x, s16 y, u32 playerId) {

	static CThingy* thingy;
	s32 x_ = x;

	__asm {
		PUSHAD
		PUSH playerId
		MOVSX EDI, y
		PUSH x_
		PUSH spriteId
		CALL Func_CreateThingy
		MOV thingy, EAX
		POPAD
	}

	return thingy;

}

;

const u32 Func_clearUnitSprites = 0x00496F00;
void clearUnitSprites(CSprite* unit_sprite, CSprite* subunit_sprite) {

	__asm {
		PUSHAD
		MOV ECX, subunit_sprite
		MOV ESI, unit_sprite
		CALL Func_clearUnitSprites
		POPAD
	}

}

;

const u32 Func_Sub497480 = 0x00497480;
void function_00497480(CSprite* thingySprite, u32 visibility_flags) {

	__asm {
		PUSHAD
		MOV EBX, thingySprite
		PUSH visibility_flags
		CALL Func_Sub497480
		POPAD
	}

}

;

const u32 Func__UnitDestructor = 0x004A0740;
void _UnitDestructor(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func__UnitDestructor
		POPAD
	}

}

;

const u32 Func_UnitDestructor = 0x004A0990;
void UnitDestructor(CUnit* unit) {

	__asm {
		PUSHAD
		MOV ECX, unit
		CALL Func_UnitDestructor
		POPAD
	}

}

;

const u32 Func_unitDeathSomething_0 = 0x004E6340;
void hideAndDisableUnit(CUnit* unit) {

	__asm {
		PUSHAD
		MOV EAX, unit
		CALL Func_unitDeathSomething_0
		POPAD
	  }

}

;

} //Unnamed namespace

//End of helper functions
