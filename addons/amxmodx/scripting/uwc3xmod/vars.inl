new bool:uwc3x;
new bool:buytime;
new bool:game_commence[MAX_PLAYERS] = false;

//MySQL and SQL Lite Vars
new ErrorCode;
new Handle:SqlConnection;
new Handle:g_SqlTuple;
new g_Error[512];
new Handle:Query;
new Handle:Query2;
new NumResults;
new NumResults2;
new steamid[35];
new player_id;
new skills_id;
new squery[8192];
new fullquery[8192];
new mtimet[32];
new bool:unammo[MAX_PLAYERS];
new bool:badaim[MAX_PLAYERS] = false;
new gReloadTime[MAX_PLAYERS];
new bool:use_addtofullpack
new player_b_mine[MAX_PLAYERS] = 0;	//Ability to lay down mines
new p_mines[MAX_SKILL_LEVEL3] = {1,2,3};

new gateused[MAX_PLAYERS] = false;

//new sqlhost[64], sqluser[32], sqlpass[32], sqldb[128], sqltable[31];
new bool:bDBConn = true;

// WC3 based variables ( not for player data )
// Next two variables used to define base XP settings for the first 10 levels
new xplevel_base[11] = {0,150,300,600,1000,1500,2100,2800,3600,4500,5500};
new xplevel_base_LT[11] = {0,150,300,600,1100,2000,3600,6400,12800,25600,38400};

new xplevel_lev[MAX_LEVEL] = 0; // Table of XP needed to achieve each level
new xpgiven_lev[MAX_LEVEL] = 0; // Table of XP given at each level
new xpgiven;// Used to store current level of XP given

// Default setting for the weaponxpmultiplier, modified later in plugin
new Float:weaponxpmultiplier[31] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};

// UWC3X Rank titles
new ranktitles[13][] = { "Orc Fodder", "Elf Acolyte", "Human Squire", "Undead Soldier", "Skilled Combatant", "Crypt Lord Zealot", "Arch Lich", "Blood Elf Champion", "Demon Hunter", "Emissary of Death", "Warchief", "World Destroyer", "Skull Breaker" };

// **************************************************************************
// BEGIN skills related variables declarations
// Defines many variables needed for the skills system
// **************************************************************************

new sortedskills[MAX_SKILLS];// Contains re-indexing after sort

//new skillset1[9][] = {"NOSKILL", "Vampiric Aura", "Levitation", "Devotion Aura", "Equipment Reincarnation", "Healing Wave", "Siphon Mana", "Impale", "Leather Skin" };
new skillset1[9][] = {"NOSKILL", "Vampiric Aura", "Levitation", "Devotion Aura", "Equipment Reincarnation", "Healing Wave", "Siphon Mana", "Impale", "Leather Skin"};
new skillset2[9][] = {"NOSKILL", "Unholy Aura", "Bash", "Critical Strike", "Repair Armor", "Banish","Hex", "Spiked Carapace", "Mend Wounds" };
new skillset3[9][] = {"NOSKILL", "Evasion", "Trueshot Aura", "Steel Skin", "Carrion Beetles", "Shadow Strike", "Entangle Roots", "Flame Strike", "Dispell Hex" };
new skillset4[9][] = {"NOSKILL", "Critical Grenade", "Serpent Ward", "Thorns Aura", "Invisibility", "Teleport", "Big Bad Voodoo", "Fan of Knives", "Vengeance" };
new skillset5[9][] = {"NOSKILL", "Siphon Ammo", "Blink", "Phoenix", "Napalm Grenade", "Gate", "Suicide Bomber", "Chain Lightning", "Decoy" };
new skillset6[9][] = {"NOSKILL", "Jump kick", "Multi Jump", "Wind Walker", "ROT", "Syv Shield", "Depower", "Cloak of the chameleon", "Cripple" };
new skillset7[9][] = {"NOSKILL", "Total Blindness", "Locust Swarm", "Disorient", "Endless Ammo", "Earth Quake", "Smite", "Cluster Grenade", "Ice Grenade" };
new skillset8[9][] = {"NOSKILL", "Helm Splitter", "Grab", "Hook Shot", "Ninja Rope", "Fatal Strike", "Blessing", "Claymore Mines", "NEWSKILL16" };

new BindSkills[] = {"Disorient", "Grab", "Hook Shot", "Ninja Rope", "Endless Ammo", "Earth Quake", "Smite", "Total Blindness", "Locust Swarm", "Big Bad Voodoo", "Mend Wounds", "Flame Strike", "Repair Armor", "Depower", "Decoy", "Entangle Roots", "Syv Shield", "Dispell Hex", "Serpent Ward", "Blessing" }
new SkillsNotForBots[] = { "Helm Splitter", "Cluster Bomb", "Claymore Mines" }

//for users saved skill sets
//new user_skillset1[MAX_PLAYERS];
//new user_skillset2[MAX_PLAYERS];
//new user_skillset3[MAX_PLAYERS];

// Minimum level to train skill
new skill_minlev[MAX_SKILLS];

// Skill level limits for each skill
new skill_limits[MAX_SKILLS];

// Ultimate skill commands
new skill_ultimates[MAX_SKILLS][32];

// All 3-lvl skills defined below
new Float:p_ankh[MAX_SKILL_LEVEL3] = {0.333,0.666,1.0}; // Equipment reincarnation
new Float:p_fan[MAX_SKILL_LEVEL3] = {0.05,0.10,0.15}; // Fan of Knives
new p_serpent[MAX_SKILL_LEVEL3] = {1,2,3}; // Serpent Ward

	// Maybe we should redo these as 10 level skills, and then setting the indexes in the skills.ini file
	new Float:p_blink  [MAX_SKILL_LEVEL6] = { 0.10, 0.25, 0.40, 0.55, 0.75, 1.00 }; // Blink
	new Float:p_phoenix[MAX_SKILL_LEVEL5] = { 0.15, 0.35, 0.55, 0.75, 1.00 }; // Pheonix
	new Float:p_evasion[MAX_SKILL_LEVEL7] = { 0.02, 0.03, 0.05, 0.07, 0.11, 0.14, 0.18 }; // Evasion
	
	new bool:blessed[MAX_PLAYERS] = false; // Is player blessed	

	// All 10-lvl skills defined next - skill values defined in set_skill_limits ( )
	// amulet of cat skill
	//new Float:p_cat[MAX_SKILL_LEVEL1];

	//jumpkick
	new p_jumpkick_damage[MAX_SKILL_LEVEL10];
	new p_jumpkick_push[MAX_SKILL_LEVEL10];

	// Vampiric Aura
	new Float:p_vampiric[MAX_SKILL_LEVEL10];
	// Vampiric Aura Max Health
	new p_vampirichealth[MAX_SKILL_LEVEL10];
	// Unholy Aura
	new Float:p_unholy[MAX_SKILL_LEVEL10];
	// Levitation
	new Float:p_levitation[MAX_SKILL_LEVEL10];
	// Invisibility
	new p_invisibility[MAX_SKILL_LEVEL10];

	//Multijump
	new p_maxjumps[MAX_SKILL_LEVEL10];
	
	//Hooks, grab, rope
	new p_hooks[MAX_SKILL_LEVEL10];
	new p_grabs[MAX_SKILL_LEVEL10];
	new Float:p_grabchance[MAX_SKILL_LEVEL10];
	new p_ropes[MAX_SKILL_LEVEL10];
	
	//fatal strike
	new Float:p_fatal_chance[MAX_SKILL_LEVEL10];
	new Float:p_fatal_damage[MAX_SKILL_LEVEL10];
	
	// Devotion Aura
	new p_devotion[MAX_SKILL_LEVEL10];
	// Bash
	new Float:p_bash[MAX_SKILL_LEVEL10];
	// Critical Strike
	new Float:p_critical[MAX_SKILL_LEVEL10];
	// Critical Grenade
	new Float:p_grenade[MAX_SKILL_LEVEL10];
	// Thorns Aura
	new Float:p_thorns[MAX_SKILL_LEVEL10];
	// Trueshot Aura
	new Float:p_trueshot[MAX_SKILL_LEVEL10];
	// Banish
	new Float:p_banish[MAX_SKILL_LEVEL10];
	// Siphon Mana
	new Float:p_mana[MAX_SKILL_LEVEL10];
	// Shadow Strike
	new Float:p_shadow[MAX_SKILL_LEVEL10];
	// Healing Wave
	new Float:p_heal[MAX_SKILL_LEVEL10];
	// Leather Skin
	new Float:p_lskin[MAX_SKILL_LEVEL10];
	// Hex
	new Float:p_hex[MAX_SKILL_LEVEL10];
	// Impale
	new Float:p_impale[MAX_SKILL_LEVEL10];
	// Spiked Carapace
	new Float:p_spiked[MAX_SKILL_LEVEL10];
	// Carrion Beetle
	new Float:p_carrion[MAX_SKILL_LEVEL10];
	// Siphon Ammo
	new Float:p_ammo[MAX_SKILL_LEVEL10];

	//Cloak of the what ever
	new Float:p_cloakskill[MAX_SKILL_LEVEL10];

	//Cluster Nades
	new grenade[MAX_PLAYERS], last;

	//ROT
	//new p_rot_bleed[MAX_SKILL_LEVEL10];
	//new p_rot_slow[MAX_SKILL_LEVEL10];
	//new p_rot_damage[MAX_SKILL_LEVEL10];
	new Float:p_rotchance[MAX_SKILL_LEVEL10];

	//TeamMate Shield
	new p_PlayerShieldedBy[MAX_PLAYERS];
	//new p_PlayerShieldDamage[MAX_PLAYERS];
	new p_ShieldMaxDamage[MAX_SKILL_LEVEL10];
	new p_ShieldMaxDamageAbsorbed[MAX_PLAYERS];
	//new issearchingShield[MAX_PLAYERS];
	new HasTeamShield[MAX_PLAYERS];
	new UsedTeamShield[MAX_PLAYERS];
	new TeamShieldCooldown[MAX_PLAYERS];


// **************************************************************************
// END skills related variables declarations
// **************************************************************************

// **************************************************************************
// BEGIN items related variables declarations
// Defines many variables needed for handling shopmenu items
// **************************************************************************

new itemname[9][] = {"Ankh of Reincarnation","Boots of Speed","Claws of Attack","Cloak of Shadows","Mask of Death","Necklace of Immunity","Orb of Frost","Periapt of Health","Tome of Experience"};
new shortitemname[9][] = {"Ankh","Boots","Claws","Cloak","Mask","Necklace","Orb","Periapt","Tome"};
new itemcost[9] = {1500,1500,1000,800,2000,800,2000,1000,4000};

new itemname2[9][] = {"Scroll of Respawning","Mole Protectant","Helm of Excellence","Amulet of the Cat","Sock of the Feather","Flaming Gloves of Warmth","Ring of Regeneration +1","Chameleon", "Mole"};
new shortitemname2[9][] = {"Scroll","Protectant","Helm","Amulet","Sock","Gloves","Ring","Chameleon", "Mole"};
new itemcost2[9] = {11000,1500,1550,1500,1500,1750,1000,8000,16000};

new itemname3[9][] = {"Lesser healing potion","Potion of Invisibility","Potion of Invulnerability","Scroll of Town Portal","Disease Cure","Poison Cure","Fire Cure","Rot Cure", "Dehex"};
new shortitemname3[9][] = {"Heal Potion","Inivisible","Invulnerable","Gate","Disease Cure","Poison Cure","Fire Cure","Rot Cure", "Dehex"};
new itemcost3[9] = {8000,8000,8000,8000,8000,8000,8000,8000,8000};

// [07-31-04] - These are now variables so they can be overridden by cfg file - K2mia
new Float:BOOTSPEED = BOOTSPEED_DEF;
new Float:MASKPERCENT = MASKPERCENT_DEF;
new Float:FROSTSPEED = FROSTSPEED_DEF;
new CLAWSOFATTACK = CLAWSOFATTACK_DEF;
new CLOAKINVISIBILITY = CLOAKINVISIBILITY_DEF;
new HEALTHBONUS = HEALTHBONUS_DEF;

// [08-01-04] - Admin Mode specifies skills reserved for admin use only
new bool:admin_only[MAX_SKILLS] = true;

// [04-07-05] - Invisibility Stacking array.. so lvl10 + cloak is good, not lvl1 + cloak : )

new cloakstack[10] = {0,5,15,25,35,45,55,65,75};

// **************************************************************************
// END items related variables declarations
// **************************************************************************

// **************************************************************************
// BEGIN player variables
// Defines many variables needed for keeping track of player data
// **************************************************************************

// Main player variables

	new bool:PlayerAuthed[MAX_PLAYERS]=false;

	// Player level ( indexed by player id )
	new p_level[MAX_PLAYERS];

	//Wisdom bonuses
	new p_maxultimates[MAX_PLAYERS];
	new p_wisdom_banishresist[MAX_PLAYERS];
	new p_wisdom_bashresist[MAX_PLAYERS];
	new p_wisdom_lightningdamagebonus[MAX_PLAYERS];
	new p_wisdom_firedamagebonus[MAX_PLAYERS];
	new p_wisdom_impaleresist[MAX_PLAYERS];
	new p_wisdom_hexresist[MAX_PLAYERS];
	new p_wisdom_jumpkickresist[MAX_PLAYERS];

	// Player attributes ( indexed by player id )
	new p_attribs[MAX_PLAYERS][MAX_ATTRIBS];
	// Player resistances ( indexed by player id )
	new p_resists[MAX_PLAYERS][MAX_RESISTS];
	// Player skills ( indexed by player id )
	new p_skills[MAX_PLAYERS][MAX_SKILLS];
	// Player experience ( indexed by player id )
	new playerxp[MAX_PLAYERS];
	// Itemslot1 ( indexed by player id )
	new playeritem[MAX_PLAYERS];
	// Itemslot2 ( indexed by player id )
	new playeritem2[MAX_PLAYERS];
	// Itemslot3 ( indexed by player id )
	new playeritem3[MAX_PLAYERS];
	new playerCanBuyitem3[MAX_PLAYERS];
	
	new bHexed[MAX_PLAYERS] = false;

	//Saved Skill sets
	new deleteskillset[MAX_PLAYERS];
	new loadskillset[MAX_PLAYERS];
	new saveskillset[MAX_PLAYERS];
	new s_loadskillset[MAX_PLAYERS];
	new s_saveskillset[MAX_PLAYERS];
	new s_deleteskillset[MAX_PLAYERS];

	//Depower
	new UsedDepower[MAX_PLAYERS];
	new bool:BlockPickup[MAX_PLAYERS]=false;

	//Cloak of Chameleon check - only occurs once per spawn
	new bool:CheckCloak[MAX_PLAYERS]=true;

	//Number of "Tombs of Experience" indexed by player ID
	new playertombs[MAX_PLAYERS] = 0;
	new p_tombs;

	//Jumpkick
	new kickflag[MAX_PLAYERS];

	//Multijump
	new jumpnum[MAX_PLAYERS] = 0;
	new bool:dojump[MAX_PLAYERS] = false;

	//Blessed
	new blessings[MAX_PLAYERS];
	new BLESSXP;
	
	//ROT
	new ROTtrail, ROTspr;
	new sprite_blood_spray, sprite_blood_drop;
	new bool:bIsRotting[MAX_PLAYERS] = false;
	new rotcount[MAX_PLAYERS] = 0;

	//EarthQuake
	//new sprite_boom;
	new quaked[MAX_PLAYERS];

	//Fireball
	new sprite_beam;

	//Cripple
	new iscrippled[MAX_PLAYERS] = 0;
	new crippletype[MAX_PLAYERS] = 0;

	//Ice Bombs
	new hasFrostNade[MAX_PLAYERS];
	new isChilled[MAX_PLAYERS];
	new isFrozen[MAX_PLAYERS];
	new novaDisplay[MAX_PLAYERS];
	new Float:oldSpeed[MAX_PLAYERS];

	// Players rank
	new p_rank[MAX_PLAYERS][18];
	// Players current team
	new currentteam[MAX_PLAYERS];
	// Has the death message been shown this round?
	new deathmessageshown[MAX_PLAYERS];
	// Used in hide or show Status routines
	new g_friend[MAX_PLAYERS];
	// Number of ultimates a player has learned
	new ultlearned[MAX_PLAYERS] = 0;
	// Player glowing
	new iglow[MAX_PLAYERS][4];
	// CT spawnpt ( origins )
	new CTspawnpts[MAX_PLAYERS][3];
	// T spawnpt ( origins )
	new Tspawnpts[MAX_PLAYERS][3];
	// MOLE spawn pts ( reset each round )
	new MOLEspawnpts[MAX_PLAYERS];
	// Max. health for player
	new maxhealth[MAX_PLAYERS];
	// Max. armor for player
	new maxarmor[MAX_PLAYERS];
	// Damage dealt table for added XP
	new damageto[MAX_PLAYERS][MAX_PLAYERS];
	// Player has spawnprotection ( indexed by player id )
	new p_spawnprotection[MAX_PLAYERS];

// Player effects and gear variables
new bool:spawnedfromitem[MAX_PLAYERS] = false; // Is player spawned from item
new bool:gotShield[MAX_PLAYERS];// Does player have tactical shield
new bool:resetskill[MAX_PLAYERS];// Is player waiting to reset skills
new bool:dropskill[MAX_PLAYERS];// Is player currently dropping skills
new bool:resetattrib[MAX_PLAYERS];// Is player waiting to reset attributes
new bool:resetresist[MAX_PLAYERS];// Is player waiting to reset resists
new bool:teleportmenu[MAX_PLAYERS];// Is player viewing teleport menu
new bool:hasgodmode[MAX_PLAYERS];// Does player have godmode ( voodoo )
new bool:phoenix[MAX_PLAYERS];// Is player a Phoenix
new bool:skinchanged[MAX_PLAYERS];// Has player's skin changed
new bool:give_items[MAX_PLAYERS] = false;// Does player get items back on respawn
new bool:playerhasspawned[MAX_PLAYERS];// Has player spawned yet
new bool:ismole[MAX_PLAYERS]=false;// Is player a mole
new bool:justgivennade[MAX_PLAYERS] = false; // Was player given a nade
new bool:itemsrunning[MAX_PLAYERS] = false;// Is player seeing items HUD display
new bool:blinkdelayed[MAX_PLAYERS];// Is player in blink delay time
new bool:g_specMode[MAX_PLAYERS];// Is player spectating
new bool:diedlastround[MAX_PLAYERS];// Did the player die last round
new bool:hasrespawned[MAX_PLAYERS] = false; // Did the player respawn this round
new bool:isBuyzone[MAX_PLAYERS];// Is player in a buyzone
//new bool:p_evadenextshot[MAX_PLAYERS];// Has player passed next shot evade test
new bool:p_evadethisshot[MAX_PLAYERS];// Did player evade this shot
new bool:ultimateused[MAX_PLAYERS];// Has an ultimate been used
new bool:stunned[MAX_PLAYERS];// Is player stunned
new bool:slowed[MAX_PLAYERS];// Is player slowed
new bool:issearching[MAX_PLAYERS];// Is player in search mode ( ultimate )
new bool:lightninghit[MAX_PLAYERS];// Is player hit by chain lightning
new bool:changingteam[MAX_PLAYERS];// Is player in the process of team change
new bool:helmet[MAX_PLAYERS];// Is player wearing a helmet
new bool:hassuit[MAX_PLAYERS]; // Is player wearing armor
new bool:hasdefuse[MAX_PLAYERS];// Does the player have a defuser
new hasnvision[MAX_PLAYERS];			// Does player have nightvision
new bool:knifeselected[MAX_PLAYERS]; // Is player wielding a knife
new bool:spawnPointsused[MAX_PLAYERS] = false; // No longer used
new bool:to_be_revived[MAX_PLAYERS] = false; // Is player about to be revived
new bool:hasmole[MAX_PLAYERS] = false; // New global for mole item
new bool:medicalert[MAX_PLAYERS] = false; // Has medic alert been sent this round
new bool:lowres[MAX_PLAYERS] = false; // Is player using a low res display
new bool:reloadskill[MAX_PLAYERS] = false; // Is player waiting to load a skillset
new bool:temp_immunity[MAX_PLAYERS] = false; // Does player have temporary immunity

new suicideAttempt[MAX_PLAYERS];						// Did player attempt suicide bomber
new savedOldLoc[MAX_PLAYERS][3];						// Used for failed Teleports
new savedNewLoc[MAX_PLAYERS][3]; 						// Used for new Teleport location
new teleportid[MAX_PLAYERS][32];						// Used for Teleport ultimate
new godshealth[MAX_PLAYERS];							// Health for player w/ godmode

new carrioncount[MAX_PLAYERS] = 2;						// How many carrion beetles left in round
new shadowcount[MAX_PLAYERS] = 2;						// How many shadow strikes left in round
new hasblink[MAX_PLAYERS] = false;						// Has blink skill?
new isburning[MAX_PLAYERS];								// Is player on fire?
new isnburning[MAX_PLAYERS];							// Is player on fire from napalm?
new repairs[MAX_PLAYERS];								// Number of repair clicks per round
new healingwaves[MAX_PLAYERS];							// Number of Healing wave xp per round
new dispells[MAX_PLAYERS];								// Number of dispell hex clicks per round
new mends[MAX_PLAYERS];									// Number of mend clicks per round
new healinghit[MAX_PLAYERS];							// Healing event hit
new flame_count[MAX_PLAYERS];							// Number of flamethrowers fired this round
new he[MAX_PLAYERS];									// Has HE gren?
new threwnapalm[MAX_PLAYERS];							// Has Player Thrown a Napalm Nade
new serpents[MAX_PLAYERS];								// How many serpants player has
new flashg[MAX_PLAYERS];								// Has flashbang gren?
new armorondeath[MAX_PLAYERS];							// Does player get armor back
new savedweapons[MAX_PLAYERS][32];						// Saved weapons for player ( equip reinc )
new savednumber[MAX_PLAYERS] = 0;						// Number of saved items ( equip reinc )
new rings[MAX_PLAYERS];									// Number of rings a player has bought
new nadetime[MAX_PLAYERS];								// Timer or gloves of warmth
new zoomed[MAX_PLAYERS];								// Is player zoomed in w/ weapon
new alive_before_explosion[MAX_PLAYERS] = false;		// Was player alive before Bomb
new serpentteam[MAX_PLAYERS];							// Which team does a ward belong to
new wardsused[MAX_PLAYERS] = 0;								// How many wards a player has used
new nSkillsPage[MAX_PLAYERS] = 1;						// Global for skills selection pager
new vampiric_hits[MAX_PLAYERS] = 0;						// Number of Vampiric Aura hits / round
new xpreadytoload[MAX_PLAYERS] = 0;						// XP ready to load from vault
new lastpspage[MAX_PLAYERS] = 0;						// Last player skills page read
new ispoisonedss[MAX_PLAYERS] = 0;						// Has been poisoned by Shadow Strike
new isdiseasedcb[MAX_PLAYERS] = 0;						// Has been diseased by Carrion Beetles
new numgates[MAX_PLAYERS] = 0;							// Number of Gates remaining this round
new loadedlevel[MAX_PLAYERS] = 0;						// Has saved xp-levels been loaded yet
new vengeance_used[MAX_PLAYERS] = 0;					// Has Vengeance been used this round
new vengeance_state[MAX_PLAYERS] = 0;					// Vengeance state for this round
new bool:set_skillset[MAX_PLAYERS];						// Is player waiting to set a skill set
new str_skillset[MAX_PLAYERS][256];						// The string of the skillset to be set

// **************************************************************************
// END player variables
// **************************************************************************

// **************************************************************************
// BEGIN miscellaneous variables
// Defines variables needed for a variety of tasks, no specific category
// **************************************************************************

new bool:freezetime = false;//changed freetime to boolean Smokey ( thanks to slmclarengt )
//new freezetime = 0		// Are we in freezetime mode
new freezecalled = 0;		// Is freezetime over
new pheonixexistsT;			// Is there at least one T phoenix
new pheonixexistsCT;		// Is there at least one CT phoenix
new vipID = 0;				// Player ID for VIP
new hostagesaver;			// Player ID that saved hostage ( s )
new bombDefuserIndex[33];	// Player IDs defusing the bomb
new bombCarrier;			// Player ID carrying the bomb
new bombdefuser;			// Player ID thhat completed defuse
new bombstate;				// Bomb state ( 0, 1 or 2 )

new bool:endround;			// Has round ended or still going
new bool:u_delay = false;	// Is there an ultimate delay at round start
new bool:no_he = false;		// Orc nades allowed or not
new bool:buycalled = false;	// Buytime over or not
new bool:givenade;			// Do gloves give an orc nade or not
new bool:givepistol;		// Pistols allowed or not ( restrictions )

// [6-24-2004] Added variables for new decoy skill - K2mia
new decoy[MAX_PLAYERS] = 0;							// Decoys stored for each player
new Float:decoy_frame[MAX_PLAYERS] = 0.0;			// Used in server_frame ( )
new Float:decoy_fstep[MAX_PLAYERS] = 0.0;			// Frame step time
new Float:last_frame = 0.0;							// Last server_frame saved
new decoy_seq[MAX_PLAYERS] = 0;						// Current sequence for each decoy
new bool:DoOnce[MAX_PLAYERS] = false;				// Used for handling crouch mode
new bool:decoyused[MAX_PLAYERS] = false;			// Has decoy been used this round
new bool:pIsDucking[MAX_PLAYERS] = false;			// Is player crouching or not

// [7-29-2004] Added variables for attributes and resistances - K2mia
// Min. level to start using enh XP
new enh_minlevel = 0;
 // Cost in EXP for 1 attribute pt
new attrib_pt_cost = 0;
 // Cost in EXP for 1 resistance pt
new resist_pt_cost = 0;
// Now is a variable instead of constant
new RESIST_MAX_VALUE = 100;
// Max. number of attrib pts earned
new ATTRIB_MAX_PTS = 40;
 // Max. number of resist pts earned
new RESIST_MAX_PTS = 500;

// Code taken from plmenu.sma ( default AMX file )
new g_menuPosition[33];
new g_menuPlayers[33][32];
new g_menuPlayersNum[33];
new g_menuOption[33];
new g_menuSettings[33];

new VIP_ESCAPE_BONUS;
new VIP_KILL_BONUS;
new KILL_BOMB_CARRIER;
new BOMBPLANTXP;
new DEFUSEXP;
new HOSTAGEXP;
new KILLRESCUEMANXP;
new XPBONUS;
new ROUNDXP;
new REPAIRXP;
new DISPELLXP;
new MENDXP;
new PHOENIXXP;
new HEALWAVEXP;
new SHEILDXP;
new USE_ENH = 0;

// Sprites
new g_sModelIndexFireball;
new g_sModelIndexSmoke;
new glassGibs, trailSpr;
//new iBeam4;
new m_iTrail;
new m_iSpriteTexture;
new lightning;
new flaresprite;
new shadow;
new fire;
new burning;
new carrion;
new cbgreen;
new poison;
new spikes;
new thorns;
new snow;
new medicspr;
new shieldspr;
new medshieldspr;
new rotmedshieldspr;
new blast;
new gatespr;

// Captured Messages
new gMsgScreenFade;
new gmsgStatusText;
new gmsgDeathMsg;
new gmsgFade;
new gmsgShake;
new gmsgScoreInfo;
new gmsgStatusIcon;
//new gmsgIcon;

// Team Ids
#define UNASSIGNED 0;
#define TS 1;
#define CTS 2;
#define AUTO_TEAM 5;

// For Icon events
//#define ICON_HIDE 0;
//#define ICON_SHOW 1;
//#define ICON_FLASH 2;

// Temporary Fix for HE nades not being read in czero
new Float:he_origin[33][3];
// End Temporary Fix

// Model names for T and CT skins
new CTSkins[4][] = { "sas", "gsg9", "urban", "gign" };
new TSkins[4][] = { "arctic","leet","guerilla","terror" };

new forwardontolevel[3] = {50,50,50};
new forwardontoserver[3][64];
new bool:levelredirection = false;


// HOOKS
new ob_pl1,ob_pl2;
new bool:mapbounds_checked;
new global_gravity;
new beam;

new IsVip[MAX_PLAYERS];

new Float:HkDelay[MAX_PLAYERS];
new hooklocation[MAX_PLAYERS][3];
new hooklength[MAX_PLAYERS];
new bool:hooked[MAX_PLAYERS];
new Float:beamcreated[MAX_PLAYERS];

//Used for Grab
new GrabCount[MAX_PLAYERS];
new grab[MAX_PLAYERS];
new Float:grab_totaldis[MAX_PLAYERS];
new bool:has_grab[MAX_PLAYERS];

//Used for Hook
new HookCount[MAX_PLAYERS];
new bool:hook[MAX_PLAYERS];
new hook_to[MAX_PLAYERS][3];
new bool:has_hook[MAX_PLAYERS];

//Used for Rope
new RopeCount[MAX_PLAYERS];
new bool:rope[MAX_PLAYERS];
new rope_to[MAX_PLAYERS][3];
new Float:rope_totaldis[MAX_PLAYERS];
new bool:has_rope[MAX_PLAYERS];
new beamsprite;




