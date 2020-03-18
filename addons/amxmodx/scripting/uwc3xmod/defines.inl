
#define MOD	"UWC3X"
#define DEBUG_STARTXP 250000 // If in DEBUG mode, starting XP for players
#define DEBUG_CASH 16000  // If in DEBUG mode, starting Cash for players
#define STEAM_POWERED 1  // Running CS1.6 required for this plugin
#define MAX_PLAYERS 33  // Max number of players in the game ( this-1 )( 0 slot is unused )
#define MAX_LEVEL 51  // Max level a player can achieve ( this-1 )( 0 slot is unused )
#define MAX_ULTIMATES 4  // Max # of ultimates trainable by a player ( this-1 )( 0 slot is unused )
#define MAX_ATTRIBS 7  // Number of attributes is ( this-1 ) ( 0 slot is unused )
#define MAX_RESISTS 8  // Number of resists is ( this-1 ) ( 0 slot is unused )
#define MAX_SKILLS 65  // Number of skills is ( this-1 ) ( 0 slot is unused )

#define MAX_SKILL_LEVEL10 10 // Maximum level this skill can be trained - 10
#define MAX_SKILL_LEVEL8 8 // Maximum level this skill can be trained - 8
#define MAX_SKILL_LEVEL7 7 // Maximum level this skill can be trained - 6
#define MAX_SKILL_LEVEL6 6 // Maximum level this skill can be trained - 6
#define MAX_SKILL_LEVEL5 5 // Maximum level this skill can be trained - 5
#define MAX_SKILL_LEVEL4 4 // Maximum level this skill can be trained - 4
#define MAX_SKILL_LEVEL3 3 // Maximum level this skill can be trained - 3
#define MAX_SKILL_LEVEL2 2 // Maximum level this skill can be trained - 1
#define MAX_SKILL_LEVEL1 1 // Maximum level this skill can be trained - 1

#define MAX_UDOG_XP 2500  // Maximum ammount of xp to be lost in a underdog bonus/penalty
#define SKILLS_PER_SET 8  // Number of skills displayed per page of selectskill
#define ATTRIB_BASE 10  // The base amount for each player attribute
#define ATTRIB_MAX_VALUE 18 // The Maximum amount for each player attribute
#define ENH_MIN_LEVEL 20  // Default Min. level to start using enhancement XP
#define NOTICE_WAIT_TIME 15 // Time to wait before reminding about skillpoints
#define MONEY_PER_KILL 300		// Amount of money earned per skill-based kill
#define SKILLSET1_LEVEL 0  // Min. level to use these skills
#define SKILLSET2_LEVEL 5  // Min. level to use these skills
#define SKILLSET3_LEVEL 12 // Min. level to use these skills
#define SKILLSET4_LEVEL 16 // Min. level to use these skills

#define XP_PER_LEVEL 1000  // Amount to add for levels after 10 ( Fast XP )
#define XP_PER_LEVEL_LT 12800 // Amount to add for levels after 10 ( Long term XP )
#define XP_PER_LEVEL_BASE 5500 // Base amount, xp from lvl 10 ( Fast XP )
#define XP_PER_LEVEL_BASE_LT 38400 // Base amount, xp from lvl 10 ( Long term XP )

#define XP_BASE 60   // Base XP for xp gaining ( xpgiven )
#define XP_ADD_LEVEL 20  // Per level xp gain ( xpgiven )

// spawn protection defines
#define S_PROTECT_TIME 4.0 // How long spawn protection lasts

// Define the levels for achieving UWC3X Rank titles
#define RANK2_LEVEL 5  // Level needed for 2nd rank
#define RANK3_LEVEL 8  // Level needed for 3rd rank
#define RANK4_LEVEL 12  // Level needed for 4th rank
#define RANK5_LEVEL 16  // Level needed for 5th rank
#define RANK6_LEVEL 20  // Level needed for 6th rank
#define RANK7_LEVEL 24  // Level needed for 7th rank
#define RANK8_LEVEL 28  // Level needed for 8th rank
#define RANK9_LEVEL 30  // Level needed for 9th rank
#define RANK10_LEVEL 32  // Level needed for 10th rank
#define RANK11_LEVEL 34  // Level needed for 11th rank
#define RANK12_LEVEL 38  // Level needed for 12th rank
#define RANK13_LEVEL 45  // Level needed for 13th rank

// Define the UWC3X p_attribs[] index for each attribute
#define ATTRIBIDX_STR 1  // Strength Attribute
#define ATTRIBIDX_INT 2  // Intellect Attribute
#define ATTRIBIDX_DEX 3  // Dexterity Attribute
#define ATTRIBIDX_AGI 4  // Agility Attribute
#define ATTRIBIDX_CON 5  // Constitution Attribute
#define ATTRIBIDX_WIS 6	 // Wisdom Attribute

#define STR_HEALTH_BONUS 5 // Bonus health for each str enhancement
#define CON_HEAL_INTERVAL 5.0 // Task interval for Constitution health regen
#define DEX_EVADE_BONUS 0.02 // Dexterity bonus to Evasion skill
#define INT_IMPALE_LEVEL 11 // Intellect level needed for Impale bonus
#define INT_IMPALE_BONUS 0.03 // Intellect bonus to hit for Impale
#define INT_SIPHON_LEVEL 12 // Intellect level needed for Siphon Mana bonus
#define INT_SIPHON_BONUS 0.03 // Intellect bonus percent for Siphon Mana
#define INT_BANISH_LEVEL 13 // Intellect level needed for Banish bonus
#define INT_BANISH_BONUS 0.03 // Intellect bonus to hit for Banish
#define INT_HEX_LEVEL 14  // Intellect level needed for Hex bonus
#define INT_HEX_BONUS 0.03 // Intellect bonus to hit for Hex
#define INT_BASH_LEVEL 15  // Intellect level needed for Bash bonus
#define INT_BASH_BONUS 0.08 // Intellect bonus to hit for Bash
#define INT_TRUESHOT_LEVEL 16 // Intellect level needed for Trueshot bonus
#define INT_TRUESHOT_BONUS 0.04 // Intellect bonus damage for Trueshot
#define INT_SERPENT_LEVEL 17 // Intellect level needed for Serpent Ward bonus
#define INT_SERPENT_BONUS 2 // Intellect bonus # of serpent wards
#define INT_TELEPORT_LEVEL 17 // Intellect level needed for Teleport bonus
#define INT_TELEPORT_COOL 25.0 // Intellect bonus Teleport improved cooldown
#define INT_MASTER_LEVEL 18 // Intellect level to be considered Master
#define DEX_JUMPKICK_LEVEL 18 //Dexterity needed for Jumpkick Bonus

#define WIS_FIREDAMAGEBONUS 0.15
#define WIS_BASHBONUS 0.15
#define WIS_BANISHBONUS 0.15
#define WIS_JUMPKICKRESIST 0.33
#define WIS_IMPALERESIST 0.15
#define WIS_HEXRESIST 0.15
#define WIS_LIGHTNINGDAMAGEBONUS 0.15

#define DEX_JUMPKICK_KNOCKBACK_BONUS 5
#define JUMPKICK_KNOCKBACK 20

// Misc skill max values
#define SPIKED_MAX_DMG 25	// Max. damage Spiked Carapace can do
#define THORNS_MAX_DMG 30	// Max. damage Thorns Aura can do

// Define the UWC3X p_resists[] index for each resistance
#define RESISTIDX_POISON 1 // Poison Resistance
#define RESISTIDX_DISEASE 2 // Disease Resistance
#define RESISTIDX_ELECTRIC 3 // Electricity Resistance
#define RESISTIDX_FIRE 4  // Fire Resistance
#define RESISTIDX_MAGIC 5  // Magic Resistance
#define RESISTIDX_ROT 6  // Rot Resistance
#define RESISTIDX_ICE 7 // Ice Resistance

// Define the UWC3X p_skills[] index for each skill
#define SKILLIDX_VAMPIRIC 1
#define SKILLIDX_LEVITATION 2
#define SKILLIDX_DEVOTION 3
#define SKILLIDX_EQREINC 4
#define SKILLIDX_HEALWAVE 5
#define SKILLIDX_SIPHON 6
#define SKILLIDX_IMPALE 7
#define SKILLIDX_LSKIN 8
#define SKILLIDX_UNHOLY 9
#define SKILLIDX_BASH 10
#define SKILLIDX_CRITSTRIKE 11
#define SKILLIDX_REPAIR 12
#define SKILLIDX_BANISH 13
#define SKILLIDX_HEX 14
#define SKILLIDX_CARAPACE 15
#define SKILLIDX_MEND 16
#define SKILLIDX_EVASION 17
#define SKILLIDX_TRUESHOT 18
#define SKILLIDX_SSKIN 19
#define SKILLIDX_CARRION 20
#define SKILLIDX_SSTRIKE 21
#define SKILLIDX_ENTANGLE 22
#define SKILLIDX_FSTRIKE 23
#define SKILLIDX_DISHEX 24
#define SKILLIDX_CRITGREN 25
#define SKILLIDX_SERPWARD 26
#define SKILLIDX_THORNS 27
#define SKILLIDX_INVIS 28
#define SKILLIDX_TELEPORT 29
#define SKILLIDX_VOODOO 30
#define SKILLIDX_FAN 31
#define SKILLIDX_VENGEANCE 32
#define SKILLIDX_SAMMO 33
#define SKILLIDX_BLINK 34
#define SKILLIDX_PHOENIX 35
#define SKILLIDX_NAPALM 36
#define SKILLIDX_GATE 37
#define SKILLIDX_SUICIDE 38
#define SKILLIDX_LIGHTNING 39
#define SKILLIDX_DECOY 40

//New skill add
#define SKILLIDX_JUMPKICK 41
#define SKILLIDX_MULTIJUMP 42
#define SKILLIDX_CAT 43
#define SKILLIDX_ROT 44
#define SKILLIDX_TEAMSHIELD 45
#define SKILLIDX_DEPOWER 46
#define SKILLIDX_CLOAK 47
#define SKILLIDX_CRIPPLE 48
#define SKILLIDX_BLIND 49
#define SKILLIDX_LOCUST 50
#define SKILLIDX_DISORIENT 51
#define SKILLIDX_UAMMO 52
#define SKILLIDX_EARTHQUAKE 53
#define SKILLIDX_SMITE 54
#define SKILLIDX_CLUSTERNADE 55
#define SKILLIDX_ICENADE 56
#define SKILLIDX_SPLITTER 57
#define SKILLIDX_HOOK 59
#define SKILLIDX_GRAB 58
#define SKILLIDX_ROPE 60

//NEW SKILLS - not yet defined
#define SKILLIDX_FATAL 61
#define SKILLIDX_BLESS 62
#define SKILLIDX_MINE 63
#define SKILLIDX_NEWSKILL16 64

#define SKILLIDX_UNUSED2 65
#define MAX_SKILL_PAGES 8  // Number of pages of skill choices in select_skill ( )

#define VENG_READY 0		// Vengeance state is Ready
#define VENG_WAIT 1		// Vengeance state is waiting to be revived
#define VENG_DONE 2		// Vengeance state is done for this round

#define BOMB_NOTPLANTED 0
#define BOMB_PLANTED 1
#define BOMB_DEFUSED 2

#define CSW_WORLD 0		// World Spawn death, for weapon xp multiplier

//CLUSTER BOMB DEFS
#define MAX_CLUSTER_DAMAGE 25
#define CLUSTER_DAMAGE_RADIUS 300
#define MIN_FLY_DISTANCE 200
#define MAX_FLY_DISTANCE 400
#define UPWARD_ARC 200
#define SCORCH 47

//ICE Bomb
#define FROST_RADIUS	120.0
#define FROST_R	0
#define FROST_G	206
#define FROST_B	209

#define FROST_HIT_SELF 1
#define FROST_MAX_DAMAGE 15
#define FROST_MIN_DAMAGE 5

#define FROST_FREEZECHANCE_MAX 100.0
#define FROST_FREEZECHANCE_MIN 40.0
//#define FROST_FREEZE_DURATION 4.0
#define FROST_FREEZE_SPEED 150.0

#define FROST_CHILLCHANCE_MAX 100.0
#define FROST_CHILLCHANCE_MIN 100.0
//#define FROST_CHILL_DURATION 8.0
#define FROST_CHILL_SPEED 180.0


// **************************************************************************
// BEGIN Backwards-Compatible Defs from War3 and War3FT
// The following #defines come straight from Warcraft3 FT plugin
// **************************************************************************

// Shopmenu 1 items list
#define ANKH 1
#define BOOTS 2
#define CLAWS 3
#define CLOAK 4
#define MASK 5
#define IMMUNITY 6
#define FROST 7
#define HEALTH 8
#define TOME 9

// Shopmenu 2 items list
#define RESPAWN 1
#define PROTECTANT 2
#define HELM 3
#define CAT 4
#define FEATHER 5
#define INFERNO 6
#define REGEN 7
#define CHAMELEON 8
#define MOLE 9

// Shopmeun3 items List TODO
#define HEAL 1
#define INVIS 2
#define INVUL 3
#define GATE 4
#define DISEASE 5
#define POISON 6
#define FIRE 7
#define ROTITEM 8
#define DEHEX 9

// Item default values Item Values
#define BOOTSPEED_DEF 275.0
#define CLAWSOFATTACK_DEF 6
#define CLOAKINVISIBILITY_DEF 150
#define MASKPERCENT_DEF 0.3
#define FROSTSPEED_DEF 125.0
#define HEALTHBONUS_DEF 15
#define INVIS_STACK_OFFSET 70  // difference between stacked invisibility with knife out and not.. higher = more visible

#define CRIPPLESPEED1 1.0
#define CRIPPLESPEED2 200.0
#define CBSPEED 215.0
#define ROTTINGSPEED 210.0
#define LOCUSTSPEED 215.0

#define ARMORBONUS1 10
#define ARMORBONUS2 15
#define NORMALARMORMAX 100

// Team Numbers for get_user_team ( id )
#define SPEC 0
#define TEAM_T 1
#define TEAM_CT 2

// Team Strings for gTeamString
#define SPEC_STR "SPECTATOR"
#define TEAM_T_STR "TERRORIST"
#define TEAM_CT_STR "CT"

// HOOK
#define DELTA_T 0.1
#define BEAMLIFE 100
#define BOOSTPOWER 500
#define HOOK_DELAY 0.5

// NEVER CHANGE THESE !!! DISASTEROUS RESULTS ( Message Defines )

#define TE_BEAMENTPOINT 1
#define TE_KILLBEAM 99

#define TE_BEAMPOINTS 0
#define TE_EXPLOSION 3
#define TE_EXPLFLAG_NONE 0
#define TE_SMOKE 5
#define TE_BEAMENTS 8
#define TE_IMPLOSION 14
#define TE_SPRITETRAIL 15
#define TE_SPRITE 17
#define TE_BEAMCYLINDER 21
#define TE_BEAMFOLLOW 22
#define TE_ELIGHT 28
#define TE_WORLDDECAL 116
#define TE_PLAYERATTACHMENT 124
#define TE_LARGEFUNNEL 100
#define FFADE_IN   0x0000
#define FFADE_OUT  0x0001

#define MAX_NAME_LENGTH 31
#define MAX_VAR_LENGTH 64

#define MAXGLOW 150
#define ULTIMATESEARCHTIME 50
#define TELEPORT_RADIUS 50
#define LIGHTNING_RANGE 500

//822, 823, 824, 825, 826

#define TASK_DO_NOW 0
#define TASK_GET_NADE_ORIGIN 2
#define TASK_CHANGE_GLOW1 15
#define TASK_CHANGE_GLOW2 16
#define TASK_CHANGE_GLOW3 17
#define TASK_CHANGE_GLOW4 18
#define TASK_SET_SPEED 19
#define TASK_UNFREEZE_SPEED 19
#define TASK_OUT_OF_BOUNDS_CHECK 23
#define	TASK_CHAIN_DAMAGE 27
#define	TASK_ENTANGLE_STOP 29
#define	TASK_SUICIDE_EXPLODE_NOID 33
#define TASK_CHECK_SPOT 56 //PLUS ID
#define TASK_CLOAK_AWARD_SOUND 83
#define TASK_HEAL_IT_NOW 90 //PLUS ID
#define TASK_RESET_IMMUNITY 201 //PLUS ID
#define TASK_ULTIMATE_SEARCH 260 //PLUS ID
#define TASK_RESET_CRIPPLE 301
#define TASK_DRAW_MEDIC_SPRITES 357
#define TASK_MONITOR_PLAYERS 358
#define TASK_RESET_CRIPPLE_ID 334
#define TASK_CHECK_USER_SPEED_NOID 367
#define TASK_CHECK_UWC3X 456
#define TASK_CHECK_UWC3X_AGAIN 457
#define TASK_SET_XP_CHOICES 458
#define TASK_SET_VARIABLES 459
#define TASK_SET_SKILL_LIMITS 461
#define TASK_SET_XP_MULTIPLIER 462
#define TASK_EXEC_CFG 463
#define TASK_BIND_CVARS 464
#define TASK_LOAD_XP_CONFIG 465
#define TASK_SHOW_ITEMS 466 //PLUS ID
#define TASK_COOLDOWN_RESET 500 //PLUS ID
#define TASK_SHIELD_CHECK_ID 550 //PLUS ID
#define TASK_MENU_TELEPORT 666
#define SHOPMENU3_RESET 865
#define TASK_CLEANUP_DECOY 866
#define TASK_CLEANUP_MINE 11000
#define TASK_RESET_MAXSPEED 1000
#define CONSTITUTION_REGEN 1100
#define TASK_LEATHER_SKIN 1200 //PLUS ID
#define SHOPMENU3_PLAY_SOUND 2200
#define TASK_JUMPKICK 2500
#define TASK_CHECK_FOOTSTEPS_NOID 2600
#define TASK_RESET_GODMODE 4500
#define TASK_REGENERATE 9000
#define TASK_NADE_TIMER 9400
#define TASK_WEAPOM_CONTROLLER 10091
#define TASK_FLAMESTRIKE_SPRAY 10000
#define TASK_BLINK_CONTROLLER 10098
#define TASK_COOLDOWN2 11000 //PLUS ID
#define TASK_COOLDOWN3 11033 //PLUS ID
#define TASK_COOLDOWN4 11066 //PLUS ID

#define TASK_ULTIMATE_ENTANGLE_SEARCH 11200 //PLUS ID
#define TASK_ULTIMATE_DEPOWER_SEARCH 11233 //PLUS ID
#define TASK_ULTIMATE_SHIELD_SEARCH 11266 //PLUS ID
#define TASK_ULTIMATE_CHAIN_SEARCH 11300 //PLUS ID
#define TASK_ON_FIRE_NAPALM 11333 //PLUS ID
#define TASK_RESET_AMMO_ID 11366 // PLUS ID
#define TASK_RESET_BADAIM_ID 11433 // PLUS ID
#define TASK_REMOVE_CHILL	11466 // PLUS ID
#define TASK_REMOVE_FREEZE	11533 // PLUS ID
#define TASK_HOOK 11566 //PLUS ID
#define TASK_GRAB_COOLDOWN 11633 //plus id
//#define TASK_ROPE_COOLDOWN 11666 //plus id
#define TASK_ON_FIRE 11733 // PLUS ID
// **************************************************************************
// END Backwards-Compatible Defs from War3 and War3FT
// **************************************************************************

#define _hudchat_included
#define __HUDCHAT_MAXLINES		5
#define __HUDCHAT_MAXMSGLEN		175
#define __HUDCHAT_UPDATEINTERVAL	0.5

#define __HUDCHAT_POS_X			0.25
#define __HUDCHAT_POS_Y			0.05

#define __HUDCHAT_TASKID_UPDATE		32462847
#define __HUDCHAT_TASKID_REMOVE		56723876

#define x1 0
#define y1 1
#define z1 2