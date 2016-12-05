#define IDLESWITCHTIME	5.0f

enum MOUSEBUTTON
{
	MOUSEBTN_LEFT,
	MOUSEBTN_RIGHT,
	MOUSEBTN_WHEEL,
	MOUSEBTN_END,
};

typedef enum _UNITSTATE
{
	STATE_IDLE,
	STATE_WALK,
	STATE_RUN,
	STATE_ATTACK,
	STATE_END,
} USTATE;

enum MESHTYPE
{
	MESHTYPE_STATIC,
	MESHTYPE_DYNAMIC,
};

enum E_STATE
{
	E_STATE_IDLE,
	E_STATE_RUN,
	E_STATE_WAIT,
	E_STATE_DEFENCE,
	E_STATE_COMBO,
	E_STATE_SKILL,
	E_STATE_END,
};

//enum E_BOSS_STATE
//{
//	E_BOSS_STATE_IDLE,
//	E_BOSS_STATE_RUN,
//	E_BOSS_STATE_WAIT,
//	E_BOSS_STATE_COMBO,
//	E_BOSS_STATE_SKILL,
//	E_BOSS_STATE_END,
//};

enum E_ANIMATION_COMMON
{
	E_ANI_IDLE,
	E_ANI_RUN,
	E_ANI_WAIT,
};

enum E_ANIMATION_PLAYER
{
	/*E_ANI_IDLE,
	E_ANI_RUN,
	E_ANI_WAIT,*/
	E_ANI_DEFENCE_START = 3,
	E_ANI_DEFENCE_LOOP,
	E_ANI_DEFENCE_HIT,
	E_ANI_DEFENCE_CALCEL,
	E_ANI_COMBO1,
	E_ANI_COMBO1R,
	E_ANI_COMBO2,
	E_ANI_COMBO2R,
	E_ANI_COMBO3,
	E_ANI_COMBO3R,
	E_ANI_COMBO4,
	E_ANI_COMBO4R,
	E_ANI_COMBO5,
	E_ANI_STRIKE,
	E_ANI_DOUBLEATTACK,
	E_ANI_DOUBLEATTACKR,
	E_ANI_END,
};

enum E_ANIMATION_BOSS
{
	E_BOSS_LONGMOVE_END = 3,
	E_BOSS_LONGMOVE_RUN,
	E_BOSS_LONGMOVE_LOOP,
	E_BOSS_LONGMOVE_START,
	E_BOSS_HEAVYATK_END,
	E_BOSS_HEAVYATK_LOOP,
	E_BOSS_HEAVYATK_START,
	E_BOSS_ATK2,
	E_BOSS_ATK1,
	E_BOSS_END,
};

enum E_FONT_TYPE
{
	E_FONT_BOSS,
	E_FONT_END,
};