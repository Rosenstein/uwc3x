new CVAR_ENABLE_UWC3X;
new CVAR_SAVE_XP;
new CVAR_SAVE_XP_SQL;
//new CVAR_REDIRECT_BOTTOM_SERVER;
//new CVAR_REDIRECT_MIDDLE_SERVER;
//new CVAR_REDIRECT_TOP_SERVER;
new CVAR_REDIRECT_BOTTOM_LEVEL;
new CVAR_REDIRECT_MIDDLE_LEVEL;
new CVAR_REDIRECT_TOP_LEVEL;
new CVAR_REDIRECT_ENABLE;
new CVAR_STARTING_XP;
new CVAR_BLINK_START_DISABLED;
new CVAR_EXPLODE_MAX_DAMAGE;
new CVAR_EXPLODE_MAX_RANGE;
new CVAR_BLAST_RADIUS;
new CVAR_WARN_SUICIDE;
new CVAR_XP_RADIUS;
new CVAR_ROUND_WIN_XP;
new CVAR_HOSTAGE_TOUCH_BONUS;
new CVAR_ATTEMPTED_DEFUSE_BONUS;
new CVAR_BOMB_EVENT_BONUS;
new CVAR_VIP_SPAWN_BONUS;
new CVAR_VIP_KILL_XP_BONUS;
new CVAR_HOSTAGE_KILL_XP_LOSS;
new CVAR_HEADSHOT_BONUS;
new CVAR_DEFUSER_KILL_BONUS;
new CVAR_VIP_ESCAPE_XP_BONUS;
new CVAR_BOMB_KILL_XP_BONUS;
new CVAR_BOMB_PLANT_XP_BONUS;
new CVAR_BOMB_DEFUSE_XP_BONUS;
new CVAR_RESCUE_HOSTIES_XP_BONUS;
new CVAR_KILL_HOSTIE_RESCUE_BONUS;
new CVAR_XP_BONUS;
new CVAR_REPAIR_XP;
new CVAR_MEND_WOUNDS_XP;
new CVAR_PHEONIX_XP;
new CVAR_DISPELL_HEX_XP;
new CVAR_HEALING_WAVE_XP;
new CVAR_SHOW_ICONS;
new CVAR_BLINK_RADIUS;
new Float:CVAR_XP_MULTIPLIER;
new CVAR_LOWRES_DEFAULT;
new Float:CVAR_NORMAL_SPEED;

new CVAR_ENABLE_ENHANCEMENTS;
new CVAR_ENHANCEMENT_MIN_LEVEL;
new CVAR_RESIST_MAX_TRAINABLE;
new CVAR_RESIST_MAX_POINTS;
new CVAR_ATTRIBS_MAX_POINTS;
new CVAR_DEBUG_MODE;
new CVAR_USE_DEBUG_CASH;
new Float:CVAR_SM1_ITEM_BOOT_SPEED;
new Float:CVAR_SM1_ITEM_FROST_SPEED;
new Float:CVAR_SM1_ITEM_MASK_PERCENT;
new CVAR_SM1_ITEM_CLAWS_DAMAGE;
new CVAR_SM1_ITEM_CLOAK_INVIS;
new CVAR_SM1_ITEM_HEATH_BONUS;
new CVAR_SM1_PRICE_ANKH;
new CVAR_SM1_PRICE_BOOTS;
new CVAR_SM1_PRICE_CLAWS;
new CVAR_SM1_PRICE_CLOAK;
new CVAR_SM1_PRICE_MASK;
new CVAR_SM1_PRICE_NECKLACE;
new CVAR_SM1_PRICE_FROST;
new CVAR_SM1_PRICE_HEALTH;
new CVAR_SM1_PRICE_TOMEXP;
new CVAR_SM2_PRICE_RESPAWN;
new CVAR_SM2_PRICE_MOLEPROTECT;
new CVAR_SM2_PRICE_HELM;
new CVAR_SM2_PRICE_AMULETCAT;
new CVAR_SM2_PRICE_FEATHER;
new CVAR_SM2_PRICE_INFERNO;
new CVAR_SM2_PRICE_RINGS;
new CVAR_SM2_PRICE_CHAMELEON;
new CVAR_SM2_PRICE_MOLE;
new CVAR_ENABLE_MOLE;
new CVAR_OBJECTIVES;
new CVAR_ULTIMATE_DELAY;
new CVAR_PLERYS_FOX_XP;
new CVAR_CENTER_HUD;
new CVAR_COMPETITIVE;

//starting level
new CVAR_STARTING_LEVEL, STARTING_LEVEL;
new STARTING_METHOD, CVAR_STARTING_METHOD;
new ENABLE_STARTING_SYSTEM, CVAR_ENABLE_STARTING_SYSTEM;

//Bot stuff
new ENABLE_BOT_SKILLS, CVAR_ENABLE_BOT_SKILLS;
new BOT_LEVEL, CVAR_BOT_LEVEL;

//orc nades
new CVAR_GLOVE_TIMER;
new CVAR_GLOVE_ORC_DAMAGE;
new CVAR_GLOVE_NAPALM;
new CVAR_HEALING_RANGE;

//Reset
new CVAR_ADMIN_DISABLE_RESET, ADMIN_DISABLE_RESET;
//Set Levels
new CVAR_ADMIN_DISABLE_SETLEVEL, ADMIN_DISABLE_SETLEVEL;

//ultimate cool downs
new Float:CVAR_VOODOO_COOLDOWN;
new Float:CVAR_FLAME_COOLDOWN;
new Float:CVAR_LIGHTNING_COOLDOWN;
new Float:CVAR_GATE_COOLDOWN;
new Float:CVAR_TELEPORT_COOLDOWN;
new Float:CVAR_ENTANGLE_COOLDOWN;
new Float:CVAR_VENGANCE_COOLDOWN;
new GRAB_COOLDOWN, Float:CVAR_GRAB_COOLDOWN;
new GRAB_CHANCE, Float:CVAR_GRAB_CHANCE;
new GATE_COOLDOWN2, CVAR_GATE_COOLDOWN2;
new FLASH_COOLDOWN, Float:CVAR_FLASH_COOLDOWN;
new LOCUST_COOLDOWN, Float:CVAR_LOCUST_COOLDOWN;
new Float:CVAR_UNLIMITED_AMMO_TIME, UNLIMITED_AMMO_TIME;
new Float:CVAR_BADAIM_TIME, BADAIM_TIME;
new Float:CVAR_SPLITTER_CHANCE, SPLITTER_CHANCE;
new CVAR_ADMIN_DEFAULT_FLAG;
new CVAR_ADMIN_SKILL_FLAG;
new CVAR_ADMIN_DISABLE_ADMINMENU;
new CVAR_ADMIN_DISABLE_GIVEXP;
new Float:CVAR_ATTRIB_MODIFIER;
new Float:CVAR_RESIST_MODIFIER;
new CVAR_UNDERDOG_ENABLE;
new CVAR_UNDERDOG_ENABLE_PENALTY;
new CVAR_UNDERDOG_HIGHLVL_MOD;
new Float:CVAR_UNDERDOG_MIDLVL_MOD;
new Float:CVAR_UNDERDOG_LOWLVL_MOD;
new CVAR_KILL_OBJECTIVES;
new CVAR_RESET_SKILLS;
//new CVAR_SHOW_PLAYER;
new Float:CVAR_BLINK_DELAY;
new CVAR_BLINK_PROTECTION;
new CVAR_BLINK_DIZINESS;
new Float:CVAR_BLINK_COOLDOWN;
new CVAR_BLINK_ENABLED;
//new CVAR_SPECTATOR_INFO;
new CVAR_SHOW_ITEMS_IN_HUD;
new CVAR_WEAPON_MULTIPLIER;
new CVAR_RESTRICT_ULTIMATES;

new CVAR_GRENADE_PROTECTION;
new CVAR_PUNISH_TK_KILLS;
new CVAR_SKILLPOINTS_PER_LEVEL;
new CVAR_ENABLE_ADMIN_ONLY_SKILLS;
new CVAR_MEDIC_ALERTS;
new CVAR_ENABLE_BEGINERS_LUCK;
new CVAR_FORCE_VENGANCE_DELAY;
new CVAR_XP_BONUS_FOR_DAMAGE;
new CVAR_ROUND_CHECK;
new CVAR_ADMINSKILL_VENGANCE;
new CVAR_ADMINSKILL_FANOFKNIVES;
new CVAR_ADMINSKILL_BLINK;
new CVAR_ADMINSKILL_TRUESHOT;
new CVAR_ADMINSKILL_VOODOO;
new CVAR_ADMINSKILL_REPAIR;
new CVAR_ADMINSKILL_NAPALM;
new CVAR_ADMINSKILL_BUY_MOLE;
new CVAR_ADMINSKILL_SUICIDE;
new CVAR_ADMINSKILL_EARTHQUAKE, ADMINSKILL_EARTHQUAKE;
new CVAR_ADMINSKILL_SMITE, ADMINSKILL_SMITE;
new CVAR_ADMINSKILL_CLUSTERNADE, ADMINSKILL_CLUSTERNADE;
new CVAR_ADMINSKILL_ICENADE, ADMINSKILL_ICENADE;
new CVAR_ADMINSKILL_ROPE, ADMINSKILL_ROPE;
new CVAR_ADMINSKILL_HOOK, ADMINSKILL_HOOK;
new CVAR_ADMINSKILL_GRAB, ADMINSKILL_GRAB;

new CVAR_MYSQL_HOSTNAME[64];
new CVAR_MYSQL_USERNAME[32];
new CVAR_MYSQL_PASSWORD[32];
new CVAR_MYSQL_DATABASE[128];
new CVAR_MYSQL_TABLE[31];
new CVAR_SAVE_BY;
new CVAR_MAX_TOMES;
/*
new CVAR_ALLOW_UWC3X_VOTE;
new CVAR_VOTE_DELAY_BETWEEN;
new CVAR_VOTE_TIME_TO_VOTE;
new CVAR_VOTE_SHOW_ANSWERS;
new CVAR_VOTE_UWC3X_RATIO;
new CVAR_WEBSITE_URL;
new CVAR_ENABLE_SHOPMENU3;
new CVAR_DAYS_BEFORE_DELETE;
new CVAR_LOCUSTS_COOLDOWN;
new CVAR_RESTRICT_HE_NADE;
new CVAR_POSITION;
*/

//Shopmenu3
new CVAR_SM3_PRICE_HEAL;
new CVAR_SM3_PRICE_INVIS;
new CVAR_SM3_PRICE_INVUL;
new CVAR_SM3_PRICE_GATE;
new CVAR_SM3_PRICE_DISEASE;
new CVAR_SM3_PRICE_POISON;
new CVAR_SM3_PRICE_FIRE;
new CVAR_SM3_PRICE_ROTITEM;
new CVAR_SM3_PRICE_DEHEX;
new SM3_PRICE_HEAL;
new SM3_PRICE_INVIS;
new SM3_PRICE_INVUL;
new SM3_PRICE_GATE;
new SM3_PRICE_DISEASE;
new SM3_PRICE_POISON;
new SM3_PRICE_FIRE;
new SM3_PRICE_ROTITEM;
new SM3_PRICE_DEHEX;

//JUMPKICK
new JUMPKICK_RADIUS;
new JUMPKICK_COOLDOWN;
new Float:CVAR_JUMPKICK_RADIUS;
new Float:CVAR_JUMPKICK_COOLDOWN;

//Teamshield
new CVAR_SHEILD_XP;
new SHEILD_XP;
new TEAMSHIELD_COOLDOWN;
new Float:CVAR_TEAMSHIELD_COOLDOWN;

//DEPOWER
new DEPOWER_COOLDOWN;
new Float:CVAR_DEPOWER_COOLDOWN;
new DEPOWER_CANT_DROP;
new CVAR_DEPOWER_CANT_DROP;

//CRIPPLE
new Float:CVAR_CRIPPLE_CHANCE1;
new Float:CVAR_CRIPPLE_CHANCE2;
new CRIPPLE_CHANCE1, CRIPPLE_CHANCE2
new CVAR_CRIPPLE_BLOCK_ULTS, CRIPPLE_BLOCK_ULTS;

//HTML Writing
new WRITE_HTML;
new CVAR_WRITE_HTML;

//HTML Background URL
new HTML_BACKGROUND_URL;
new CVAR_HTML_BACKGROUND_URL[128];

//HTML Text Color
new HTML_TEXT_COLOR;
new CVAR_HTML_TEXT_COLOR[16];

//Saved Skillsets
new SAVED_SKILLSETS;
new CVAR_SAVED_SKILLSETS

//SQL Method
//new SQL_METHOD, CVAR_SQL_METHOD;

new ENABLE_UWC3X;
new SAVE_BY;
new SAVE_XP;
new SAVE_XP_SQL;
new REDIRECT_BOTTOM_SERVER;
new REDIRECT_MIDDLE_SERVER;
new REDIRECT_TOP_SERVER;
new REDIRECT_BOTTOM_LEVEL;
new REDIRECT_MIDDLE_LEVEL;
new REDIRECT_TOP_LEVEL;
new REDIRECT_ENABLE;
new MAX_TOMES;
//new ENABLE_STARTING_XP;
new STARTING_XP;
new BLINK_START_DISABLED;
new EXPLODE_MAX_DAMAGE;
new EXPLODE_MAX_RANGE;
new BLAST_RADIUS;
new WARN_SUICIDE;
new XP_RADIUS;
new ROUND_WIN_XP;
new HOSTAGE_TOUCH_BONUS;
new ATTEMPTED_DEFUSE_BONUS;
new BOMB_EVENT_BONUS;
new VIP_SPAWN_BONUS;
new VIP_KILL_XP_BONUS;
new HOSTAGE_KILL_XP_LOSS;
new HEADSHOT_BONUS;
new DEFUSER_KILL_BONUS;
new VIP_ESCAPE_XP_BONUS;
new BOMB_KILL_XP_BONUS;
new BOMB_PLANT_XP_BONUS;
new BOMB_DEFUSE_XP_BONUS;
new RESCUE_HOSTIES_XP_BONUS;
new KILL_HOSTIE_RESCUE_BONUS;
new XP_BONUS;
new REPAIR_XP;
new MEND_WOUNDS_XP;
new PHEONIX_XP;
new DISPELL_HEX_XP;
new HEALING_WAVE_XP;
new MYSQL_HOSTNAME;
new MYSQL_USERNAME;
new MYSQL_PASSWORD;
new MYSQL_DATABASE;
new MYSQL_TABLE;
new SHOW_ICONS;
new BLINK_RADIUS;
new XP_MULTIPLIER;
new LOWRES_DEFAULT;
new NORMAL_SPEED;
new ENABLE_ENHANCEMENTS;
new ENHANCEMENT_MIN_LEVEL;
new RESIST_MAX_TRAINABLE;
new RESIST_MAX_POINTS;
new ATTRIBS_MAX_POINTS;
new DEBUG_MODE;
new USE_DEBUG_CASH;
new SM1_ITEM_BOOT_SPEED;
new SM1_ITEM_FROST_SPEED;
new SM1_ITEM_MASK_PERCENT;
new SM1_ITEM_CLAWS_DAMAGE;
new SM1_ITEM_CLOAK_INVIS;
new SM1_ITEM_HEATH_BONUS;
new SM1_PRICE_ANKH;
new SM1_PRICE_BOOTS;
new SM1_PRICE_CLAWS;
new SM1_PRICE_CLOAK;
new SM1_PRICE_MASK;
new SM1_PRICE_NECKLACE;
new SM1_PRICE_FROST;
new SM1_PRICE_HEALTH;
new SM1_PRICE_TOMEXP;
new SM2_PRICE_RESPAWN;
new SM2_PRICE_MOLEPROTECT;
new SM2_PRICE_HELM;
new SM2_PRICE_AMULETCAT;
new SM2_PRICE_FEATHER;
new SM2_PRICE_INFERNO;
new SM2_PRICE_RINGS;
new SM2_PRICE_CHAMELEON;
new SM2_PRICE_MOLE;
new ENABLE_MOLE;
new OBJECTIVES;
new ULTIMATE_DELAY;
new PLERYS_FOX_XP;
new CENTER_HUD;
new COMPETITIVE;

//orc nades
new GLOVE_TIMER;
new GLOVE_ORC_DAMAGE;
new GLOVE_NAPALM;
new HEALING_RANGE;

//ultimate cool downs
new VOODOO_COOLDOWN;
new FLAME_COOLDOWN;
new LIGHTNING_COOLDOWN;
new GATE_COOLDOWN;
new TELEPORT_COOLDOWN;
new ENTANGLE_COOLDOWN;
new VENGANCE_COOLDOWN;

new ADMIN_DEFAULT_FLAG;
new ADMIN_SKILL_FLAG;
new ADMIN_DISABLE_ADMINMENU;
new ADMIN_DISABLE_GIVEXP;
new ATTRIB_MODIFIER;
new RESIST_MODIFIER;
new UNDERDOG_ENABLE;
new UNDERDOG_ENABLE_PENALTY;
new UNDERDOG_HIGHLVL_MOD;
new UNDERDOG_MIDLVL_MOD;
new UNDERDOG_LOWLVL_MOD;
new KILL_OBJECTIVES;
new RESET_SKILLS;
//new SHOW_PLAYER;
new BLINK_DELAY;
new BLINK_PROTECTION;
new BLINK_DIZINESS;
new BLINK_COOLDOWN;
new BLINK_ENABLED;
//new SPECTATOR_INFO;
new SHOW_ITEMS_IN_HUD;
new WEAPON_MULTIPLIER;
new RESTRICT_ULTIMATES;

new GRENADE_PROTECTION;
new PUNISH_TK_KILLS;
new SKILLPOINTS_PER_LEVEL;
new ENABLE_ADMIN_ONLY_SKILLS;
new MEDIC_ALERTS;
new ENABLE_BEGINERS_LUCK;
new FORCE_VENGANCE_DELAY;
new XP_BONUS_FOR_DAMAGE;
new ROUND_CHECK;
new ADMINSKILL_VENGANCE;
new ADMINSKILL_FANOFKNIVES;
new ADMINSKILL_BLINK;
new ADMINSKILL_TRUESHOT;
new ADMINSKILL_VOODOO;
new ADMINSKILL_REPAIR;
new ADMINSKILL_NAPALM;
new ADMINSKILL_BUY_MOLE;
new ADMINSKILL_SUICIDE;
/*
new ALLOW_UWC3X_VOTE;
new VOTE_DELAY_BETWEEN;
new VOTE_TIME_TO_VOTE;
new VOTE_SHOW_ANSWERS;
new VOTE_UWC3X_RATIO;
new WEBSITE_URL;
new ENABLE_SHOPMENU3;
new DAYS_BEFORE_DELETE;
new LOCUSTS_COOLDOWN;
new RESTRICT_HE_NADE;
new SAVE_BY;
new POSITION;
*/

//HOOK
new CVAR_HOOK_STYLE, HOOK_STYLE;
new CVAR_HOOK_MOVEACC, HOOK_MOVEACC;
new CVAR_HOOK_REELSPEED, HOOK_REELSPEED;
new CVAR_HOOK_CREELSPEED, HOOK_CREELSPEED;
new HOOK_NO_OOB, CVAR_HOOK_NO_OOB;

new CVAR_ROPE_NOVIP, ROPE_NOVIP;
new CVAR_HOOK_NOVIP, HOOK_NOVIP;
new CVAR_GRAB_NOVIP, GRAB_NOVIP;
new CVAR_GRAB_SPEED, GRAB_SPEED;
new CVAR_HOOK_SPEED, HOOK_SPEED;
new CVAR_ROPE_SPEED, ROPE_SPEED;

new CVAR_BLESS_XP;
new BLESS_XP;


//Fatal Chance
new Float:CVAR_FATAL_CHANCE, FATAL_CHANCE 

public Register_Cvars ( )
{
	ENABLE_UWC3X					=			register_cvar ( "sv_uwc3x",						"1"				 );

	SAVE_XP_SQL						=			register_cvar ( "mp_save_method",				"1"				 );
	XP_MULTIPLIER					=			register_cvar ( "mp_xpmultiplier",				"1.50"			 );
	SAVE_XP							=			register_cvar ( "mp_savexp",					"1"				 );
	//SQL_METHOD						=			register_cvar ( "mp_sql_method",				"2"				 );

	//redirection system
	REDIRECT_BOTTOM_SERVER			=			register_cvar ( "UWX_rdsvr_bottom",				"0"				 );
	REDIRECT_MIDDLE_SERVER			=			register_cvar ( "UWX_rdsvr_middle",				"0"				 );
	REDIRECT_TOP_SERVER				=			register_cvar ( "UWX_rdsvr_top",				"0"				 );
	REDIRECT_BOTTOM_LEVEL			=			register_cvar ( "UWX_rdlvl_bottom",				"0"				 );
	REDIRECT_MIDDLE_LEVEL			=			register_cvar ( "UWX_rdlvl_middle",				"0"				 );
	REDIRECT_TOP_LEVEL				=			register_cvar ( "UWX_rdlvl_top",				"0"				 );
	REDIRECT_ENABLE					=			register_cvar ( "UWX_rd",						"0"				 );
	ENABLE_STARTING_SYSTEM			=			register_cvar ( "UWX_enable_starting_system",	"1"				 );

	//CVAR_WEBSITE_URL				=			register_cvar ( "UWX_site_URL",					"Yaur.com"	 	 );
	STARTING_METHOD					=			register_cvar ( "UWX_starting_method",			"1"				 );
	STARTING_XP						=			register_cvar ( "UWX_starting_xp",				"150000"		 );
	STARTING_LEVEL					=			register_cvar ( "UWX_starting_level",			"15"			 );
	ENABLE_BOT_SKILLS				=			register_cvar ( "UWX_enable_bot_skills",		"1"				 );
	BOT_LEVEL						=			register_cvar ( "UWX_bot_level",				"15"			 );

	//Set MYSQL Items
	MYSQL_HOSTNAME					=			register_cvar ( "UWX_sql_host",					"127.0.0.1"		 );
	MYSQL_USERNAME					=			register_cvar ( "UWX_sql_user",					"root"			 );
	MYSQL_PASSWORD					=			register_cvar ( "UWX_sql_pass",					"pass"			 );
	MYSQL_DATABASE					=			register_cvar ( "UWX_sql_db",					"uwc3x"			 );
	MYSQL_TABLE						=			register_cvar ( "UWX_sql_table",				"uwc3x"			 );

	//Set XP Bonuses for events
	XP_RADIUS						=			register_cvar ( "UWX_xp_radius",				"750"			);
	ROUND_WIN_XP					=			register_cvar ( "UWX_round_win_XP",				"10"			);
	HOSTAGE_TOUCH_BONUS				=			register_cvar ( "UWX_hostage_touch_bonus",		"0"				 );

	VIP_SPAWN_BONUS					=			register_cvar ( "UWX_VIP_spawn_bonus",			"0"				 );
	VIP_ESCAPE_XP_BONUS				=			register_cvar ( "UWX_VIP_escape_bonus",			"60"			 );
	VIP_KILL_XP_BONUS				=			register_cvar ( "UWX_VIP_kill_bonus",			"60"			 );

	HEADSHOT_BONUS					=			register_cvar ( "UWX_headshot_bonus",			"30"			 );
	DEFUSER_KILL_BONUS				=			register_cvar ( "UWX_defuser_kill_bonus",		"60"			 );

	BOMB_EVENT_BONUS				=			register_cvar ( "UWX_bomb_event_bonus",			"0"				 );
	BOMB_KILL_XP_BONUS				=			register_cvar ( "UWX_kill_bomb_carrier_bonus",	"60"			 );
	BOMB_PLANT_XP_BONUS				=			register_cvar ( "UWX_bombplanterxp",			"60"			 );
	BOMB_DEFUSE_XP_BONUS			=			register_cvar ( "UWX_defusexp",					"60"			 );
	ATTEMPTED_DEFUSE_BONUS			=			register_cvar ( "UWX_attempt_defuse_bonus",		"0"				 );

	RESCUE_HOSTIES_XP_BONUS			=			register_cvar ( "UWX_hostagexp",				"60"			 );
	KILL_HOSTIE_RESCUE_BONUS		=			register_cvar ( "UWX_killrescuemanxp",			"60"			 );
	HOSTAGE_KILL_XP_LOSS			=			register_cvar ( "UWX_hostage_kill_xp",	 		"1"				 );
	XP_BONUS						=			register_cvar ( "UWX_xpbonus",					"60"			 );

	//Set starting XP for these team skills
	REPAIR_XP						=			register_cvar ( "UWX_repair_XP",				"60"			 );
	MEND_WOUNDS_XP					=			register_cvar ( "UWX_mend_XP",					"60"			 );
	PHEONIX_XP						=			register_cvar ( "UWX_phoenix_XP",				"90"			 );
	DISPELL_HEX_XP					=			register_cvar ( "UWX_dispell_XP",				"90"			 );
	HEALING_WAVE_XP					=			register_cvar ( "UWX_healingwave_XP",			"90"			 );
	LOWRES_DEFAULT					=			register_cvar ( "UWX_lowres_default",			"1"				 );
	NORMAL_SPEED					=			register_cvar ( "UWX_normalspeed",				"250.0"			 );
	ENABLE_ENHANCEMENTS				=			register_cvar ( "UWX_use_enh",					"1"				 );
	ENHANCEMENT_MIN_LEVEL			=			register_cvar ( "UWX_enh_minlevel",				"34"			 );
	RESIST_MAX_TRAINABLE			=			register_cvar ( "UWX_max_resistvalue",			"100"			 );
	RESIST_MAX_POINTS				=			register_cvar ( "UWX_max_resistpts",			"500"			 );
	ATTRIBS_MAX_POINTS				=			register_cvar ( "UWX_max_attribpts",			"40"			 );
	DEBUG_MODE						=			register_cvar ( "UWX_DEBUG",					"0"				 );
	USE_DEBUG_CASH					=			register_cvar ( "UWX_USE_DEBUG_CASH",			"0"				 );
	//Shopmenu items
	SM1_ITEM_BOOT_SPEED				=			register_cvar ( "UWX_BOOTSPEED",				"275.0"			 );
	SM1_ITEM_FROST_SPEED			=			register_cvar ( "UWX_FROSTSPEED",				"125.0"			 );
	SM1_ITEM_MASK_PERCENT			=			register_cvar ( "UWX_MASKPERCENT",				"0.3"			 );
	SM1_ITEM_CLAWS_DAMAGE			=			register_cvar ( "UWX_CLAWSOFATTACK",			"6"				 );
	SM1_ITEM_CLOAK_INVIS			=			register_cvar ( "UWX_CLOAKINVISIBILITY",		"180"			 );
	SM1_ITEM_HEATH_BONUS			=			register_cvar ( "UWX_HEALTHBONUS",				"15"			 );

	//Shopmenu1 item prices
	SM1_PRICE_ANKH					=			register_cvar ( "UWX_price_ANKH",				"1500"			 );
	SM1_PRICE_BOOTS					=			register_cvar ( "UWX_price_BOOTS",				"1500"			 );
	SM1_PRICE_CLAWS					=			register_cvar ( "UWX_price_CLAWS",				"1000"			 );
	SM1_PRICE_CLOAK					=			register_cvar ( "UWX_price_CLOAK",				"800"			 );
	SM1_PRICE_MASK					=			register_cvar ( "UWX_price_MASK",				"2000"			 );
	SM1_PRICE_NECKLACE				=			register_cvar ( "UWX_price_IMMUNITY",			"800"			 );
	SM1_PRICE_FROST					=			register_cvar ( "UWX_price_FROST",				"2000"			 );
	SM1_PRICE_HEALTH				=			register_cvar ( "UWX_price_HEALTH",				"1000"			 );
	SM1_PRICE_TOMEXP				=			register_cvar ( "UWX_price_TOME",				"4000"			 );

	//Shopmenu2 item prices
	SM2_PRICE_RESPAWN				=			register_cvar ( "UWX_price_RESPAWN",			"11000"			 );
	SM2_PRICE_MOLEPROTECT			=			register_cvar ( "UWX_price_PROTECTANT",			"1500"			 );
	SM2_PRICE_HELM					=			register_cvar ( "UWX_price_HELM",				"1550"			 );
	SM2_PRICE_AMULETCAT				=			register_cvar ( "UWX_price_CAT",				"1500"			 );
	SM2_PRICE_FEATHER				=			register_cvar ( "UWX_price_FEATHER",			"1500"			 );
	SM2_PRICE_INFERNO				=			register_cvar ( "UWX_price_INFERNO",			"1750"			 );
	SM2_PRICE_RINGS					=			register_cvar ( "UWX_price_REGEN",				"1000"			 );
	SM2_PRICE_CHAMELEON				=			register_cvar ( "UWX_price_CHAMELEON",			"9000"			 );
	SM2_PRICE_MOLE					=			register_cvar ( "UWX_price_MOLE",				"16000"			 );

	//Is the mole enabled?
	ENABLE_MOLE						=			register_cvar ( "UWX_Enable_Mole",				"1"				 );
	SHOW_ICONS						=			register_cvar ( "UWX_show_icons",				"1"				 );

	//Teleport
	BLINK_RADIUS 					=			register_cvar ( "UWX_blink_radius",				"500"			 );
	BLINK_START_DISABLED			=			register_cvar ( "UWX_blinkstartdisabled",		"0"				 );

	//Suicide Bomber
	EXPLODE_MAX_DAMAGE				=			register_cvar ( "UWX_explosion_max_damage",		"50"			 );
	EXPLODE_MAX_RANGE				=			register_cvar ( "UWX_explosion_range",			"300"			 );
	BLAST_RADIUS					=			register_cvar ( "UWX_blast_radius",				"250"			 );
	WARN_SUICIDE					=			register_cvar ( "UWX_warn_suicide",				"1"				 );

	OBJECTIVES						=			register_cvar ( "UWX_objectives",				"1"				);
	ULTIMATE_DELAY					=			register_cvar ( "UWX_ultimatedelay",			"0"				);
	PLERYS_FOX_XP					=			register_cvar ( "UWX_min_b4_XP",				"2"				);
	CENTER_HUD						=			register_cvar ( "UWX_centerhud",				"1"				);

	ADMIN_DEFAULT_FLAG				=			register_cvar ( "UWX_admin_flag",				"1048576"		);
	ADMIN_SKILL_FLAG				=			register_cvar ( "UWX_admin_flag_skills",		"1048576"		);
	ADMIN_DISABLE_ADMINMENU			=			register_cvar ( "UWX_disable_adminmenu",		"0"				);
	ADMIN_DISABLE_GIVEXP			=			register_cvar ( "UWX_disable_givexp",			"0"				);
	ATTRIB_MODIFIER					=			register_cvar ( "UWX_attrib_xpmodifier",		"1.0"			);
	RESIST_MODIFIER					=			register_cvar ( "UWX_resist_xpmodifier",		"1.0"			);
	UNDERDOG_ENABLE					=			register_cvar ( "UWX_underdog_kills",			"1"				);
	UNDERDOG_ENABLE_PENALTY			=			register_cvar ( "UWX_underdog_xp_penalty",		"1"				); //enable the underdog xp penalty
	UNDERDOG_HIGHLVL_MOD			=			register_cvar ( "UWX_highlevel_modifier",		"2"				); // For levels above 30
	UNDERDOG_MIDLVL_MOD				=			register_cvar ( "UWX_midlevel_modifier",		"2.25"			); // For levels above 20
	UNDERDOG_LOWLVL_MOD				=			register_cvar ( "UWX_lowlevel_modifier",		"1.75"			); // For levels above 10
	COMPETITIVE						=			register_cvar ( "UWX_competitive",				"0"			 );

	//Orc nades
	GLOVE_TIMER						=			register_cvar ( "UWX_glove_timer",				"25"		 );
	GLOVE_ORC_DAMAGE				=			register_cvar ( "UWX_glove_orc_damage",			"1"			 );
	GLOVE_NAPALM					=			register_cvar ( "UWX_glove_napalm_damage",		"0"			 );

	HEALING_RANGE					=			register_cvar ( "UWX_healing_range",			"750"		 );

	//Ultimate cool downs
	VOODOO_COOLDOWN					=			register_cvar ( "UWX_bigbadvoodoo_cooldown",	"35.0"		 );
	FLAME_COOLDOWN					=			register_cvar ( "UWX_flamestrike_cooldown",		"35.0"		 );
	LIGHTNING_COOLDOWN				=			register_cvar ( "UWX_chainlightning_cooldown",	"35.0"		 );
	GATE_COOLDOWN					=			register_cvar ( "UWX_gate_cooldown",			"5.0"		 );
	GATE_COOLDOWN2					=			register_cvar ( "UWX_gate_cooldown_int",		"5"		 	 );
	TELEPORT_COOLDOWN				=			register_cvar ( "UWX_teleport_cooldown",		"35.0"		 );
	ENTANGLE_COOLDOWN				=			register_cvar ( "UWX_entanglingroots_cooldown",	"35.0"		 );
	VENGANCE_COOLDOWN				=			register_cvar ( "UWX_vengance_cooldown",		"35.0"		 );
	GRAB_COOLDOWN					=			register_cvar ( "UWX_grab_cooldown",			"15.0"		 );
	GRAB_CHANCE						=			register_cvar ( "UWX_grab_chance",				"0.50"		 );
	
	FLASH_COOLDOWN					=			register_cvar ( "UWX_flash_cooldown",			"25.0"		 );
	LOCUST_COOLDOWN					=			register_cvar ( "UWX_locusts_cooldown",			"35.0"		 );

	BLINK_DELAY						=			register_cvar ( "UWX_blink_delay",				"15.0"		 );
	BLINK_PROTECTION				=			register_cvar ( "UWX_blink_protection",			"1"			 );
	BLINK_DIZINESS					=			register_cvar ( "UWX_blink_diziness",			"1"			 );
	BLINK_COOLDOWN					=			register_cvar ( "UWX_blink_cooldown",			"3.0"		 );
	BLINK_ENABLED					=			register_cvar ( "UWX_blinkenabled",				"1"			 );
	//SPECTATOR_INFO					=			register_cvar ( "UWX_spec_info",				"1"			 );
	SHOW_ITEMS_IN_HUD				=			register_cvar ( "UWX_items_in_hud",				"0"			 );
	WEAPON_MULTIPLIER				=			register_cvar ( "mp_weaponxpmodifier",			"1"			 );
	RESTRICT_ULTIMATES				=			register_cvar ( "sv_restrictultimate",			"0"			 );
	GRENADE_PROTECTION				=			register_cvar ( "mp_grenadeprotection",			"0"			 );

	KILL_OBJECTIVES					=			register_cvar ( "UWX_kill_objectives",			"1"			 );
	RESET_SKILLS					=			register_cvar ( "UWX_reset_skills",				"1"			 );
	//SHOW_PLAYER						=			register_cvar ( "UWX_show_player",				"1"			 );

	ROUND_CHECK						=			register_cvar ( "UWX_round_check",				"1"			 );
	XP_BONUS_FOR_DAMAGE				=			register_cvar ( "UWX_dmgxpbonus",				"1"			 );
	MEDIC_ALERTS					=			register_cvar ( "UWX_medicalerts",				"2"			 );
	FORCE_VENGANCE_DELAY			=			register_cvar ( "UWX_force_vengeance",			"1"			 );
	ENABLE_BEGINERS_LUCK			=			register_cvar ( "UWX_luck_skill",				"1"			 );
	ENABLE_ADMIN_ONLY_SKILLS		=			register_cvar ( "UWX_admin_mode",				"1"			 );
	SKILLPOINTS_PER_LEVEL			=			register_cvar ( "UWX_skillpoints_per_level",	"1"			 );
	PUNISH_TK_KILLS					=			register_cvar ( "UWX_punish_TK",				"0"			 );

	ADMINSKILL_VENGANCE				=			register_cvar ( "UWX_vengance_adminonly",		"0"			 );
	ADMINSKILL_FANOFKNIVES			=			register_cvar ( "UWX_fanofknives_adminonly",	"0"			 );
	ADMINSKILL_BLINK				=			register_cvar ( "UWX_blink_adminonly",			"0"			 );
	ADMINSKILL_TRUESHOT				=			register_cvar ( "UWX_trueshot_adminonly",		"0"			 );
	ADMINSKILL_VOODOO				=			register_cvar ( "UWX_voodoo_adminonly",			"0"			 );
	ADMINSKILL_REPAIR				=			register_cvar ( "UWX_repair_adminonly",			"0"			 );
	ADMINSKILL_NAPALM				=			register_cvar ( "UWX_napalm_adminonly",			"0"			 );
	ADMINSKILL_BUY_MOLE				=			register_cvar ( "UWX_Enable_AdminMole",			"0"			 );
	ADMINSKILL_SUICIDE				=			register_cvar ( "UWX_suicide_adminonly",		"0"			 );
	ADMINSKILL_ICENADE				=			register_cvar ( "UWX_icenade_adminonly",		"0"			 );
	ADMINSKILL_EARTHQUAKE			=			register_cvar ( "UWX_earthquake_adminonly",		"0"			 );
	ADMINSKILL_CLUSTERNADE			=			register_cvar ( "UWX_clusternade_adminonly",	"0"			 );
	ADMINSKILL_SMITE				=			register_cvar ( "UWX_smite_adminonly",			"0"			 );
	ADMINSKILL_ROPE					=			register_cvar ( "UWX_rope_adminonly",			"0"			 );
	ADMINSKILL_HOOK					=			register_cvar ( "UWX_hook_adminonly",			"0"			 );
	ADMINSKILL_GRAB					=			register_cvar ( "UWX_grab_adminonly",			"0"			 );
	


	// Set 1 to save by STEAMID, 2 to save by player name (not yet supported)
	SAVE_BY							=			register_cvar ( "UWX_saveby",					"1"			);
	MAX_TOMES						=			register_cvar ( "UWX_max_tomes", 				"10"		);

	JUMPKICK_RADIUS					=			register_cvar ( "UWX_jumpkick_radius", 			"70.0" 		);
	JUMPKICK_COOLDOWN				=			register_cvar ( "UWX_jumpkick_cooldown", 		"3.0" 		);
	SHEILD_XP						=			register_cvar ( "UWX_team_shield_xp", 			"120" 		);
	TEAMSHIELD_COOLDOWN				=			register_cvar ( "UWX_team_shield_cooldown", 	"35.0" 		);

	//Shopmenu3
	SM3_PRICE_HEAL					=			register_cvar ( "UWX_price_HEAL",				"8000"		 );
	SM3_PRICE_INVIS					=			register_cvar ( "UWX_price_INVIS",				"8000"		 );
	SM3_PRICE_INVUL					=			register_cvar ( "UWX_price_INVUL",				"8000"		 );
	SM3_PRICE_GATE					=			register_cvar ( "UWX_price_GATE",				"8000"		 );
	SM3_PRICE_DISEASE				=			register_cvar ( "UWX_price_DISEASE",			"8000"		 );
	SM3_PRICE_POISON				=			register_cvar ( "UWX_price_POISON",				"8000"		 );
	SM3_PRICE_FIRE					=			register_cvar ( "UWX_price_FIRE",				"8000"		 );
	SM3_PRICE_ROTITEM				=			register_cvar ( "UWX_price_ROTITEM",			"8000"		 );
	SM3_PRICE_DEHEX					=			register_cvar ( "UWX_price_DEHEX",				"8000"		 );

	WRITE_HTML						=			register_cvar ( "UWX_write_html", 				"1" 		);
	HTML_BACKGROUND_URL				=			register_cvar ( "UWX_html_bg_url",				""			);
	HTML_TEXT_COLOR					=			register_cvar ( "UWX_html_text_color",			"FFB000"	);
	SAVED_SKILLSETS					=			register_cvar ( "UWX_enable_savedskillsets", 	"1"			);
	DEPOWER_COOLDOWN				=			register_cvar ( "UWX_depower_cooldown", 		"45.0" 		);
	DEPOWER_CANT_DROP				=			register_cvar ( "UWX_depower_disallow_drop", 	"1" 		);
	CRIPPLE_CHANCE1					=			register_cvar ( "UWX_cripple_chance1", 			"0.05" 		);
	CRIPPLE_CHANCE2					=			register_cvar ( "UWX_cripple_chance2", 			"0.15" 		);
	ADMIN_DISABLE_RESET				=			register_cvar ( "UWX_disable_reset", 			"0" 		);
	ADMIN_DISABLE_SETLEVEL			=			register_cvar ( "UWX_disable_setlevel", 		"0" 		);
	CRIPPLE_BLOCK_ULTS				=			register_cvar ( "UWX_cripple_blocks_ultimates", "0" 		);
	UNLIMITED_AMMO_TIME				=			register_cvar ( "UWX_unlimited_ammo_time", 		"5.0" 		);
	BADAIM_TIME						=			register_cvar ( "UWX_badaim_time", 				"15.0" 		);
	SPLITTER_CHANCE					=			register_cvar ( "UWX_splitter_chance", 			"0.15" 		);
	
	/*
	LOCUSTS_COOLDOWN				=			register_cvar ( "UWX_locusts_cooldown",			"35.0"		 );
	ALLOW_UWC3X_VOTE				=			register_cvar ( "sv_allowwar3vote",				"0"			 );
	VOTE_DELAY_BETWEEN				=			register_cvar ( "amx_vote_delay",				"60"		 );
	VOTE_TIME_TO_VOTE				=			register_cvar ( "amx_vote_time",				"10"		 );
	VOTE_SHOW_ANSWERS				=			register_cvar ( "amx_vote_answers",				"1"			 );
	VOTE_UWC3X_RATIO				=			register_cvar ( "amx_votewar3_ratio",			"0.70"		 );
	DAYS_BEFORE_DELETE				=			register_cvar ( "sv_daysbeforedelete",			"31"		 );
	ENABLE_SHOPMENU3				=			register_cvar ( "UWX_enable_shopmenu3",			"1"			 );
	POSITION						=			register_cvar ( "UWX_position",					"0"			 );
	*/
	
	//Hook
	HOOK_NOVIP					=				register_cvar ( "UWX_hook_no_vip",				"1"			 );
	ROPE_NOVIP					=				register_cvar ( "UWX_rope_no_vip",				"1"			 );
	GRAB_NOVIP					=				register_cvar ( "UWX_grab_no_vip",				"1"			 );
	GRAB_SPEED					=				register_cvar ( "UWX_grab_speed",				"5"			 );
	HOOK_SPEED					=				register_cvar ( "UWX_hook_speed",				"5"			 );
	ROPE_SPEED					=				register_cvar ( "UWX_rope_speed",				"5"		 	 );

	HOOK_STYLE					=				register_cvar ( "UWX_hook_style",				"0"		 	 );
	HOOK_MOVEACC				=				register_cvar ( "UWX_hook_move_accelleration",	"150"		 );
	HOOK_REELSPEED				=				register_cvar ( "UWX_hook_reelspeed",			"400"		 );
	HOOK_CREELSPEED				=				register_cvar ( "UWX_hook_creelspeed",			"800"		 );
	HOOK_NO_OOB					=				register_cvar ( "UWX_hook_no_oobd",				"1"		 	 );
		
	FATAL_CHANCE				=				register_cvar ( "UWX_fatal_slay_chance",		"0.02"		 );
	BLESS_XP                    =            	register_cvar ( "UWX_BLESS_XP",                	"400"        );          	
	
	log_amx( "[UWC3X] Cvars Initialized [OK]");
}

public Bind_Cvars ( )
{
	//Set String Items
	get_pcvar_string ( MYSQL_HOSTNAME, CVAR_MYSQL_HOSTNAME,	63 );
	get_pcvar_string ( MYSQL_USERNAME, CVAR_MYSQL_USERNAME,	31 );
	get_pcvar_string ( MYSQL_PASSWORD, CVAR_MYSQL_PASSWORD,	31 );
	get_pcvar_string ( MYSQL_DATABASE, CVAR_MYSQL_DATABASE,	31 );
	get_pcvar_string ( MYSQL_TABLE, CVAR_MYSQL_TABLE, 31 );
	//get_pcvar_string ( REDIRECT_BOTTOM_SERVER, CVAR_REDIRECT_BOTTOM_SERVER,	31 );
	//get_pcvar_string ( REDIRECT_MIDDLE_SERVER, CVAR_REDIRECT_MIDDLE_SERVER,	31 );
	//get_pcvar_string ( REDIRECT_TOP_SERVER, CVAR_REDIRECT_TOP_SERVER, 31 );
	get_pcvar_string( HTML_BACKGROUND_URL, CVAR_HTML_BACKGROUND_URL, 127 );
	get_pcvar_string( HTML_TEXT_COLOR, CVAR_HTML_TEXT_COLOR, 15 );

	//Set Numbers
	CVAR_ENABLE_UWC3X			=	get_pcvar_num ( ENABLE_UWC3X );
	CVAR_SAVE_BY				=	get_pcvar_num ( SAVE_BY );
	//CVAR_SQL_METHOD				=	get_pcvar_num ( SQL_METHOD );
	CVAR_REDIRECT_BOTTOM_LEVEL	=	get_pcvar_num ( REDIRECT_BOTTOM_LEVEL );
	CVAR_REDIRECT_MIDDLE_LEVEL	=	get_pcvar_num ( REDIRECT_MIDDLE_LEVEL );
	CVAR_REDIRECT_TOP_LEVEL		=	get_pcvar_num ( REDIRECT_TOP_LEVEL );
	CVAR_REDIRECT_ENABLE		=	get_pcvar_num ( REDIRECT_ENABLE );
	CVAR_ENABLE_STARTING_SYSTEM	=	get_pcvar_num ( ENABLE_STARTING_SYSTEM );
	CVAR_STARTING_XP			=	get_pcvar_num ( STARTING_XP );
	CVAR_STARTING_LEVEL			=	get_pcvar_num ( STARTING_LEVEL );
	CVAR_STARTING_METHOD		=	get_pcvar_num ( STARTING_METHOD );
	CVAR_SAVE_XP_SQL			=	get_pcvar_num ( SAVE_XP_SQL );
	CVAR_SAVE_XP				=	get_pcvar_num ( SAVE_XP );
	CVAR_XP_RADIUS				=	get_pcvar_num ( XP_RADIUS );
	CVAR_ROUND_WIN_XP			=	get_pcvar_num ( ROUND_WIN_XP );
	CVAR_HOSTAGE_TOUCH_BONUS	=	get_pcvar_num ( HOSTAGE_TOUCH_BONUS );
	CVAR_VIP_SPAWN_BONUS		=	get_pcvar_num ( VIP_SPAWN_BONUS );
	CVAR_VIP_ESCAPE_XP_BONUS	=	get_pcvar_num ( VIP_ESCAPE_XP_BONUS );
	CVAR_VIP_KILL_XP_BONUS		=	get_pcvar_num ( VIP_KILL_XP_BONUS);
	CVAR_HEADSHOT_BONUS			=	get_pcvar_num ( HEADSHOT_BONUS );
	CVAR_DEFUSER_KILL_BONUS		=	get_pcvar_num ( DEFUSER_KILL_BONUS );
	CVAR_BOMB_EVENT_BONUS		=	get_pcvar_num ( BOMB_EVENT_BONUS );
	CVAR_BOMB_KILL_XP_BONUS		=	get_pcvar_num ( BOMB_KILL_XP_BONUS );
	CVAR_BOMB_PLANT_XP_BONUS	=	get_pcvar_num ( BOMB_PLANT_XP_BONUS );
	CVAR_BOMB_DEFUSE_XP_BONUS	=	get_pcvar_num ( BOMB_DEFUSE_XP_BONUS );
	CVAR_ATTEMPTED_DEFUSE_BONUS	=	get_pcvar_num ( ATTEMPTED_DEFUSE_BONUS );
	CVAR_RESCUE_HOSTIES_XP_BONUS=	get_pcvar_num ( RESCUE_HOSTIES_XP_BONUS );
	CVAR_KILL_HOSTIE_RESCUE_BONUS=	get_pcvar_num ( KILL_HOSTIE_RESCUE_BONUS );
	CVAR_XP_BONUS				=	get_pcvar_num ( XP_BONUS );
	CVAR_REPAIR_XP				=	get_pcvar_num ( REPAIR_XP );
	CVAR_MEND_WOUNDS_XP			=	get_pcvar_num ( MEND_WOUNDS_XP );
	CVAR_PHEONIX_XP				=	get_pcvar_num ( PHEONIX_XP );
	CVAR_DISPELL_HEX_XP			=	get_pcvar_num ( DISPELL_HEX_XP );
	CVAR_HEALING_WAVE_XP		=	get_pcvar_num ( HEALING_WAVE_XP );
	CVAR_LOWRES_DEFAULT			=	get_pcvar_num ( LOWRES_DEFAULT );
	CVAR_ENABLE_ENHANCEMENTS	=	get_pcvar_num ( ENABLE_ENHANCEMENTS );
	CVAR_ENHANCEMENT_MIN_LEVEL	=	get_pcvar_num ( ENHANCEMENT_MIN_LEVEL );
	CVAR_RESIST_MAX_TRAINABLE	=	get_pcvar_num ( RESIST_MAX_TRAINABLE );
	CVAR_RESIST_MAX_POINTS		=	get_pcvar_num ( RESIST_MAX_POINTS );
	CVAR_ATTRIBS_MAX_POINTS		=	get_pcvar_num ( ATTRIBS_MAX_POINTS );
	CVAR_DEBUG_MODE				=	get_pcvar_num ( DEBUG_MODE );
	CVAR_USE_DEBUG_CASH			=	get_pcvar_num ( USE_DEBUG_CASH );

	CVAR_SM1_ITEM_CLAWS_DAMAGE	=	get_pcvar_num ( SM1_ITEM_CLAWS_DAMAGE );
	CVAR_SM1_ITEM_CLOAK_INVIS	=	get_pcvar_num ( SM1_ITEM_CLOAK_INVIS );
	CVAR_SM1_ITEM_HEATH_BONUS	=	get_pcvar_num ( SM1_ITEM_HEATH_BONUS );
	CVAR_SM1_PRICE_ANKH			=	get_pcvar_num ( SM1_PRICE_ANKH );
	CVAR_SM1_PRICE_BOOTS		=	get_pcvar_num ( SM1_PRICE_BOOTS );
	CVAR_SM1_PRICE_CLAWS		=	get_pcvar_num ( SM1_PRICE_CLAWS );
	CVAR_SM1_PRICE_CLOAK		=	get_pcvar_num ( SM1_PRICE_CLOAK );
	CVAR_SM1_PRICE_MASK			=	get_pcvar_num ( SM1_PRICE_MASK );
	CVAR_SM1_PRICE_NECKLACE		=	get_pcvar_num ( SM1_PRICE_NECKLACE );
	CVAR_SM1_PRICE_FROST		=	get_pcvar_num ( SM1_PRICE_FROST );
	CVAR_SM1_PRICE_HEALTH		=	get_pcvar_num ( SM1_PRICE_HEALTH );
	CVAR_SM1_PRICE_TOMEXP		=	get_pcvar_num ( SM1_PRICE_TOMEXP );
	CVAR_SM2_PRICE_RESPAWN		=	get_pcvar_num ( SM2_PRICE_RESPAWN );
	CVAR_SM2_PRICE_MOLEPROTECT	=	get_pcvar_num ( SM2_PRICE_MOLEPROTECT );
	CVAR_SM2_PRICE_HELM			=	get_pcvar_num ( SM2_PRICE_HELM );
	CVAR_SM2_PRICE_AMULETCAT	=	get_pcvar_num ( SM2_PRICE_AMULETCAT );
	CVAR_SM2_PRICE_FEATHER		=	get_pcvar_num ( SM2_PRICE_FEATHER );
	CVAR_SM2_PRICE_INFERNO		=	get_pcvar_num ( SM2_PRICE_INFERNO );
	CVAR_SM2_PRICE_RINGS		=	get_pcvar_num ( SM2_PRICE_RINGS );
	CVAR_SM2_PRICE_CHAMELEON	=	get_pcvar_num ( SM2_PRICE_CHAMELEON );
	CVAR_SM2_PRICE_MOLE			=	get_pcvar_num ( SM2_PRICE_MOLE );
	CVAR_ENABLE_MOLE			=	get_pcvar_num ( ENABLE_MOLE );
	CVAR_SHOW_ICONS				=	get_pcvar_num ( SHOW_ICONS );
	CVAR_BLINK_RADIUS			= 	get_pcvar_num ( BLINK_RADIUS );
	CVAR_BLINK_START_DISABLED	=	get_pcvar_num ( BLINK_START_DISABLED );
	CVAR_EXPLODE_MAX_DAMAGE		=	get_pcvar_num ( EXPLODE_MAX_DAMAGE );
	CVAR_EXPLODE_MAX_RANGE		=	get_pcvar_num ( EXPLODE_MAX_RANGE );
	CVAR_BLAST_RADIUS			=	get_pcvar_num ( BLAST_RADIUS );
	CVAR_WARN_SUICIDE			=	get_pcvar_num ( WARN_SUICIDE );
	CVAR_OBJECTIVES				=	get_pcvar_num ( OBJECTIVES );
	CVAR_ULTIMATE_DELAY			=	get_pcvar_num ( ULTIMATE_DELAY );
	CVAR_PLERYS_FOX_XP			=	get_pcvar_num ( PLERYS_FOX_XP );
	CVAR_CENTER_HUD				=	get_pcvar_num ( CENTER_HUD );
	CVAR_ADMIN_DEFAULT_FLAG		=	get_pcvar_num ( ADMIN_DEFAULT_FLAG );
	CVAR_ADMIN_SKILL_FLAG		=	get_pcvar_num ( ADMIN_SKILL_FLAG );
	CVAR_ADMIN_DISABLE_ADMINMENU=	get_pcvar_num ( ADMIN_DISABLE_ADMINMENU );
	CVAR_ADMIN_DISABLE_GIVEXP	=	get_pcvar_num ( ADMIN_DISABLE_GIVEXP );
	CVAR_UNDERDOG_ENABLE		=	get_pcvar_num ( UNDERDOG_ENABLE );
	CVAR_UNDERDOG_ENABLE_PENALTY=	get_pcvar_num ( UNDERDOG_ENABLE_PENALTY );
	CVAR_UNDERDOG_HIGHLVL_MOD	=	get_pcvar_num ( UNDERDOG_HIGHLVL_MOD );
	CVAR_COMPETITIVE			=	get_pcvar_num ( COMPETITIVE );
	CVAR_GLOVE_TIMER			=	get_pcvar_num ( GLOVE_TIMER );
	CVAR_GLOVE_ORC_DAMAGE		=	get_pcvar_num ( GLOVE_ORC_DAMAGE );
	CVAR_GLOVE_NAPALM			=	get_pcvar_num ( GLOVE_NAPALM );
	CVAR_HEALING_RANGE			=	get_pcvar_num ( HEALING_RANGE );
	CVAR_BLINK_PROTECTION		=	get_pcvar_num ( BLINK_PROTECTION );
	CVAR_BLINK_DIZINESS			=	get_pcvar_num ( BLINK_DIZINESS );
	CVAR_BLINK_ENABLED			=	get_pcvar_num ( BLINK_ENABLED );
	//CVAR_SPECTATOR_INFO			=	get_pcvar_num ( SPECTATOR_INFO );
	CVAR_SHOW_ITEMS_IN_HUD		=	get_pcvar_num ( SHOW_ITEMS_IN_HUD );
	CVAR_WEAPON_MULTIPLIER		=	get_pcvar_num ( WEAPON_MULTIPLIER );
	CVAR_RESTRICT_ULTIMATES		=	get_pcvar_num ( RESTRICT_ULTIMATES );
	CVAR_GRENADE_PROTECTION		=	get_pcvar_num ( GRENADE_PROTECTION );
	CVAR_KILL_OBJECTIVES		=	get_pcvar_num ( KILL_OBJECTIVES );
	CVAR_RESET_SKILLS			=	get_pcvar_num ( RESET_SKILLS );
	//CVAR_SHOW_PLAYER			=	get_pcvar_num ( SHOW_PLAYER );
	CVAR_ROUND_CHECK			=	get_pcvar_num ( ROUND_CHECK );
	CVAR_XP_BONUS_FOR_DAMAGE	=	get_pcvar_num ( XP_BONUS_FOR_DAMAGE );
	CVAR_MEDIC_ALERTS			=	get_pcvar_num ( MEDIC_ALERTS );
	CVAR_FORCE_VENGANCE_DELAY	=	get_pcvar_num ( FORCE_VENGANCE_DELAY );
	CVAR_ENABLE_BEGINERS_LUCK	=	get_pcvar_num ( ENABLE_BEGINERS_LUCK );
	CVAR_ENABLE_ADMIN_ONLY_SKILLS=	get_pcvar_num ( ENABLE_ADMIN_ONLY_SKILLS );
	CVAR_SKILLPOINTS_PER_LEVEL	=	get_pcvar_num ( SKILLPOINTS_PER_LEVEL );
	CVAR_PUNISH_TK_KILLS		=	get_pcvar_num ( PUNISH_TK_KILLS );
	CVAR_ADMINSKILL_VENGANCE	=	get_pcvar_num ( ADMINSKILL_VENGANCE );
	CVAR_ADMINSKILL_FANOFKNIVES	=	get_pcvar_num ( ADMINSKILL_FANOFKNIVES );
	CVAR_ADMINSKILL_BLINK		=	get_pcvar_num ( ADMINSKILL_BLINK );
	CVAR_ADMINSKILL_TRUESHOT	=	get_pcvar_num ( ADMINSKILL_TRUESHOT );
	CVAR_ADMINSKILL_VOODOO		=	get_pcvar_num ( ADMINSKILL_VOODOO );
	CVAR_ADMINSKILL_REPAIR		=	get_pcvar_num ( ADMINSKILL_REPAIR );
	CVAR_ADMINSKILL_NAPALM		=	get_pcvar_num ( ADMINSKILL_NAPALM );
	CVAR_ADMINSKILL_BUY_MOLE	=	get_pcvar_num ( ADMINSKILL_BUY_MOLE );
	CVAR_ADMINSKILL_SUICIDE		=	get_pcvar_num ( ADMINSKILL_SUICIDE );
	CVAR_ADMINSKILL_EARTHQUAKE	=	get_pcvar_num ( ADMINSKILL_EARTHQUAKE );
	CVAR_ADMINSKILL_SMITE		=	get_pcvar_num ( ADMINSKILL_SMITE );
	CVAR_ADMINSKILL_CLUSTERNADE	=	get_pcvar_num ( ADMINSKILL_CLUSTERNADE );
	CVAR_ADMINSKILL_ICENADE		=	get_pcvar_num ( ADMINSKILL_ICENADE );
	CVAR_ADMINSKILL_ROPE		=	get_pcvar_num ( ADMINSKILL_ROPE );
	CVAR_ADMINSKILL_HOOK		=	get_pcvar_num ( ADMINSKILL_HOOK );
	CVAR_ADMINSKILL_GRAB		=	get_pcvar_num ( ADMINSKILL_GRAB );

	CVAR_MAX_TOMES				=	get_pcvar_num ( MAX_TOMES );
	CVAR_HOSTAGE_KILL_XP_LOSS	=	get_pcvar_num ( HOSTAGE_KILL_XP_LOSS );

	//Set Floats
	CVAR_XP_MULTIPLIER			=	get_pcvar_float ( XP_MULTIPLIER );
	CVAR_NORMAL_SPEED			=	get_pcvar_float ( NORMAL_SPEED );
	CVAR_ATTRIB_MODIFIER		=	get_pcvar_float ( ATTRIB_MODIFIER );
	CVAR_RESIST_MODIFIER		=	get_pcvar_float ( RESIST_MODIFIER );
	CVAR_UNDERDOG_MIDLVL_MOD	=	get_pcvar_float ( UNDERDOG_MIDLVL_MOD ); // For levels above 20
	CVAR_UNDERDOG_LOWLVL_MOD	=	get_pcvar_float ( UNDERDOG_LOWLVL_MOD ); // For levels above 10
	CVAR_VOODOO_COOLDOWN		=	get_pcvar_float ( VOODOO_COOLDOWN );
	CVAR_FLAME_COOLDOWN			=	get_pcvar_float ( FLAME_COOLDOWN );
	CVAR_LIGHTNING_COOLDOWN		=	get_pcvar_float ( LIGHTNING_COOLDOWN );
	CVAR_GATE_COOLDOWN			=	get_pcvar_float ( GATE_COOLDOWN );
	CVAR_GATE_COOLDOWN2			=	get_pcvar_num	( GATE_COOLDOWN2 );
	CVAR_TELEPORT_COOLDOWN		=	get_pcvar_float ( TELEPORT_COOLDOWN );
	CVAR_ENTANGLE_COOLDOWN		=	get_pcvar_float ( ENTANGLE_COOLDOWN );
	CVAR_VENGANCE_COOLDOWN		=	get_pcvar_float ( VENGANCE_COOLDOWN );
	CVAR_FLASH_COOLDOWN			=	get_pcvar_float ( FLASH_COOLDOWN );
	CVAR_LOCUST_COOLDOWN		=	get_pcvar_float ( LOCUST_COOLDOWN );
	CVAR_GRAB_COOLDOWN			=	get_pcvar_float ( GRAB_COOLDOWN );
	CVAR_GRAB_CHANCE			=	get_pcvar_float ( GRAB_CHANCE );
	
	CVAR_BLINK_DELAY			=	get_pcvar_float ( BLINK_DELAY );
	CVAR_BLINK_COOLDOWN			=	get_pcvar_float ( BLINK_COOLDOWN );
	CVAR_SM1_ITEM_BOOT_SPEED	=	get_pcvar_float ( SM1_ITEM_BOOT_SPEED );
	CVAR_SM1_ITEM_FROST_SPEED	=	get_pcvar_float ( SM1_ITEM_FROST_SPEED );
	CVAR_SM1_ITEM_MASK_PERCENT	=	get_pcvar_float ( SM1_ITEM_MASK_PERCENT );

	//JUMPKICK
	CVAR_JUMPKICK_RADIUS		=	get_pcvar_float( JUMPKICK_RADIUS );
	CVAR_JUMPKICK_COOLDOWN		=	get_pcvar_float( JUMPKICK_COOLDOWN );

	//Teamshield
	CVAR_TEAMSHIELD_COOLDOWN	=	get_pcvar_float( TEAMSHIELD_COOLDOWN );
	CVAR_SHEILD_XP				=	get_pcvar_num ( SHEILD_XP );

	//Depower
	CVAR_DEPOWER_COOLDOWN		=	get_pcvar_float( DEPOWER_COOLDOWN );
	CVAR_DEPOWER_CANT_DROP		=	get_pcvar_num( DEPOWER_CANT_DROP );

	//Cripple
	CVAR_CRIPPLE_CHANCE1		=	get_pcvar_float( CRIPPLE_CHANCE1 );
	CVAR_CRIPPLE_CHANCE2		=	get_pcvar_float( CRIPPLE_CHANCE2 );
	CVAR_CRIPPLE_BLOCK_ULTS 	=	get_pcvar_num( CRIPPLE_BLOCK_ULTS );

	//BOTS
	CVAR_ENABLE_BOT_SKILLS		=	get_pcvar_num( ENABLE_BOT_SKILLS );
	CVAR_BOT_LEVEL				=	get_pcvar_num( BOT_LEVEL );

	//Shopmenu3
	CVAR_SM3_PRICE_HEAL			=	get_pcvar_num( SM3_PRICE_HEAL );
	CVAR_SM3_PRICE_INVIS		=	get_pcvar_num( SM3_PRICE_INVIS );
	CVAR_SM3_PRICE_INVUL		=	get_pcvar_num( SM3_PRICE_INVUL );
	CVAR_SM3_PRICE_GATE			=	get_pcvar_num( SM3_PRICE_GATE );
	CVAR_SM3_PRICE_DISEASE		=	get_pcvar_num( SM3_PRICE_DISEASE );
	CVAR_SM3_PRICE_POISON		=	get_pcvar_num( SM3_PRICE_POISON );
	CVAR_SM3_PRICE_FIRE			=	get_pcvar_num( SM3_PRICE_FIRE );
	CVAR_SM3_PRICE_ROTITEM		=	get_pcvar_num( SM3_PRICE_ROTITEM );
	CVAR_SM3_PRICE_DEHEX		=	get_pcvar_num( SM3_PRICE_DEHEX );

	CVAR_WRITE_HTML				=	get_pcvar_num( WRITE_HTML );
	CVAR_SAVED_SKILLSETS		=	get_pcvar_num( SAVED_SKILLSETS );
	CVAR_ADMIN_DISABLE_RESET	=	get_pcvar_num( ADMIN_DISABLE_RESET );
	CVAR_ADMIN_DISABLE_SETLEVEL	=	get_pcvar_num( ADMIN_DISABLE_SETLEVEL );
	CVAR_SPLITTER_CHANCE		=	get_pcvar_float( SPLITTER_CHANCE );
	CVAR_UNLIMITED_AMMO_TIME	=	get_pcvar_float( UNLIMITED_AMMO_TIME );
	CVAR_BADAIM_TIME			=	get_pcvar_float( BADAIM_TIME );

	//Hook
	CVAR_HOOK_STYLE				=	get_pcvar_num( HOOK_STYLE );
	CVAR_HOOK_MOVEACC			=	get_pcvar_num( HOOK_MOVEACC );
	CVAR_HOOK_REELSPEED			=	get_pcvar_num( HOOK_REELSPEED );
	CVAR_HOOK_CREELSPEED		=	get_pcvar_num( HOOK_CREELSPEED );
	CVAR_HOOK_NO_OOB			=	get_pcvar_num( HOOK_NO_OOB );
	
	CVAR_HOOK_NOVIP				=	get_pcvar_num( HOOK_NOVIP );
	CVAR_ROPE_NOVIP				=	get_pcvar_num( ROPE_NOVIP );
	CVAR_GRAB_NOVIP				=	get_pcvar_num( GRAB_NOVIP );
	CVAR_GRAB_SPEED				=	get_pcvar_num( GRAB_SPEED );
	CVAR_HOOK_SPEED				=	get_pcvar_num( HOOK_SPEED );
	CVAR_ROPE_SPEED				=	get_pcvar_num( ROPE_SPEED );
	
	CVAR_FATAL_CHANCE			=	get_pcvar_float( FATAL_CHANCE );
	CVAR_BLESS_XP            	=   get_pcvar_num ( BLESS_XP );
	
	log_amx( "[UWC3X] Bound CVARS [OK]");

}

public Exec_User_CFG ( )
{
	new basedir[64];
	new cfgfile[64];
	get_customdir(basedir, 63);
	format(cfgfile, 63, "%s/uwc3x/UWC3X.cfg", basedir);

	if ( file_exists( cfgfile ) )
	{
		log_amx( "[UWC3X] Startup :: Loading Configuration File [ UWC3X.cfg ]..." );
		server_cmd( "exec %s", cfgfile);
		log_amx( "[UWC3X] Startup :: Configuration File Loaded [OK]" );
		log_amx( "[UWC3X] User Config File Initialized [OK]");
	}
	else
	{
		log_amx( "[UWC3X] Startup ERROR :: Configuration File NOT FOUND [ Using Default settings ]" );
		log_amx( "[UWC3X] User Config File Initialized [FAILED ] - File not found");
	}
}