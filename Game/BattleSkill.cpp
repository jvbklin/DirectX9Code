//=================================================================================
//
//    Battle Skill cpp
//    Author : Lin He                                        çÏê¨ì˙ : 2019/01/13
//
//=================================================================================

#include "BattleSkill.h"

const Skill& GetSkill(SKILL_ENUM skill_id)
{
	return skill_data[skill_id];
}

const Alchemy& GetAlchemy(ALCHEMY_ENUM alchemy_id)
{
	return alchemy_data[alchemy_id];
}