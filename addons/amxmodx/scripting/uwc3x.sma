/*
* AMXX Plugin:  Ultimate Warcraft3 Expansion ( uwc3x )
*
* UWC3X is written for AMX Mod X
*
*************************************************************************************
*** 	Original UWC3 mod by K2mia with portions by Dumb and the Yaur.com community
*************************************************************************************
*
* This plugin is a new approach to the War3 and War3FT plugins created by
* SpaceDude and Pimp Daddy. UWC3 provides a raceless, skill/level based 
* system. Much of the internal workings of Warcraft3FT skills and items were 
* kept intact from Pimp Daddy's version, though the overall player structures
* have been changed to allow a flexible skill-based system. 
*
* Uwc3X takes this approach and attempts to add new items, new skills, and balance
* the mod and gameplay in such a way that makes the game fair and easier for lower
* level players while making the game more competitive and difficult for higher levels
*
*************************************************************************************
*
* Credits to:
* Original War3FT by Pimp Daddy ( OoTOAoO )
* Original Ultimate uwc3 by K2mia ( Andrew Cowan )
* the original UWC3 DEV team 
* Spacedude ( for War3 MOD )
* Ludwig Van ( for flamethrower )
* OLO ( for spectating rank info )
* JGHG for the mole code
* [AOL]Demandred, [AOL]LuckyJ for help coding it for steam
* [AOL]Demandred for freezetime exploit fix
* Denkkar for some of his code ( ie. STEAM_POWERED )
* joecool12321 for various health related fixes
* Tri Moon for various improvements ( No Race, war3menu, etc... )
* xeroblood for spotting some bugs for me : )
* bad-at-this for contributing the status bar code used for godmode ( big bad voodoo )
* kamikaze, (--eRRoR--), Dantallion, Left Nut and the Yaur Community for help w/testing
* lui for the delayed ultimate code
* Left Nut for all his hard work on balancing the skills
* Hawk552 for his work on jumpkick
* twistedeuphoria for his work on multijump
* the developers of DIABLO MOD for inspiring us
* (--eRRoR--) from the StormZone community for their work on finding bugs and some of the new sprites and sounds
* Dantallion for fatal strike and bug replication as well as help with some sounds
* A special THANKS to the YAUR community for their work and inspiration
* *** Everyone at amxmod.net for help ***
* 
*************************************************************************************/

new const UWC3XNAME[]		=	"Ultimate Warcraft3 Expansion"
new const UWC3XAUTHOR[]		=	"-=[Yaur]=-"
new const UWC3XVERSION[]	=	"1.0.82"

#pragma reqclass	xstats
#pragma reqlib		engine
#pragma reqlib		fun
#pragma reqlib		fakemeta
#pragma reqlib		cstrike
#pragma loadlib		sqlite
#pragma loadlib		mysql
#pragma dynamic		65536

#include <amxmodx>
#include <amxmisc>
#include <engine>
#include <fun>
#include <fakemeta> 
#include <cstrike>
#include <dbi>
#include <sqlx>
#include <string>
 
//Inline Code files
#include "uwc3xmod/defines.inl"
#include "uwc3xmod/vars.inl"
#include "uwc3xmod/cvars.inl"

#include "uwc3xmod/ultimates.inl"
#include "uwc3xmod/abilities.inl"
#include "uwc3xmod/enhancements.inl"

#include "uwc3xmod/utility.inl"
#include "uwc3xmod/stock.inl"
#include "uwc3xmod/storage.inl"
#include "uwc3xmod/Storage_MySQL.inl"
#include "uwc3xmod/Storage_SQLLite.inl"
#include "uwc3xmod/help.inl"
#include "uwc3xmod/menu.inl"
#include "uwc3xmod/ClientCommands.inl"

#include "uwc3xmod/Events.inl"
#include "uwc3xmod/Events_damage.inl"
#include "uwc3xmod/Events_log.inl"
#include "uwc3xmod/Events_Skills.inl"
#include "uwc3xmod/Events_ultimates.inl"

#include "uwc3xmod/mole.inl"
#include "uwc3xmod/respawn.inl"
#include "uwc3xmod/items.inl"
#include "uwc3xmod/shopmenu.inl"
#include "uwc3xmod/shopmenu2.inl"
#include "uwc3xmod/shopmenu3.inl"
#include "uwc3xmod/skills.inl"

#include "uwc3xmod/tasks.inl"
#include "uwc3xmod/xp.inl"
#include "uwc3xmod/chat.inl"

/* BEGIN CODE */

public plugin_modules ( )
{
	require_module ( "engine" );
	require_module ( "fun" );
	require_module ( "cstrike" );
	require_module ( "sqlx" );
}

public CheckUserName( id )
{
	new username[33];
	get_user_info(id , "name" , username , 32);

	if ((strlen(username)) < 4 )
	{
		new randID = random_num(1, 999);
		format(username, 32, "Uwc3x|Yaur player%i", randID)
		set_user_info(id, "name", username);
		ShowUsername_Message(id);
	}

	return PLUGIN_CONTINUE;
}

public ShowUsername_Message( id )
{

	new message[4096] = "", temp[1024] = "";
	add( message, 4096, "<body bgcolor=#000000><font color=#FFB000>" );
	format( temp, 1024, "<center><b>About Your Username</b></center><p>" );
	add( message, 4096, temp );
	add( message, 4096, "<center><table width=800 border=1 cellpadding=4 cellspacing=4>" );
	add( message, 4096, "<tr><td valign=top width=50%><font color=#FFB000>" );
	add( message, 4096, "Hello,<br />Your username is less then 4 characters long, and this server has disabled that." );
	add( message, 4096, "<br />Typically people change their usernames to a short character name so that others can not see their charsheet." );
	add( message, 4096, "<br />We think thats pretty <b>lame of you</b>, so we are forcing you to have a 4 character or longer name." );
	add( message, 4096, "<br />This is to stop people from being able to hide their charsheets from others." );
	add( message, 4096, "<br /><br />As such, we have changed your username, please feel free to change it so long as it is over 3 characters" );
	add( message, 4096, "Thanks<br /><br />" );
	add( message, 4096, "The -=[Yaur]=- Clan" );
	add( message, 4096, "</td></tr></table></center>" );
	show_motd( id, message, "About Your Username" );

	return PLUGIN_CONTINUE;
}

public client_infochanged(id) {
	CheckUserName(id);
}

/* Added support to fix players losing XP to STEAM_ID_PENDING -Marticus 11/15/05 */ 
public client_authorized ( id )
{ 
	if ( CVAR_SAVE_XP ) 
	{
		xpreadytoload[id] = 1;
	}
	
	PlayerAuthed[id] = true;
	CheckUserName(id);
	return PLUGIN_CONTINUE ;
} 

public plugin_init ( )
{

	register_plugin ( UWC3XNAME, UWC3XVERSION, UWC3XAUTHOR );
	register_cvar ( "amx_uwc3x", UWC3XVERSION, FCVAR_SERVER );

	// Set messagning variables 
	gMsgScreenFade		= get_user_msgid ( "ScreenFade" );
	gmsgDeathMsg		= get_user_msgid ( "DeathMsg" );
	gmsgFade			= get_user_msgid ( "ScreenFade"	);
	gmsgShake			= get_user_msgid ( "ScreenShake" );
	gmsgStatusText		= get_user_msgid ( "StatusText"	);
	gmsgScoreInfo		= get_user_msgid ( "ScoreInfo" );
	gmsgStatusIcon		= get_user_msgid ( "StatusIcon" );
	
	register_dictionary ( "uwc3x.txt" );
	
	//Removed the Forward and used hookDrop for the client command instead
	//register_forward(FM_Touch, "Fwd_Touch");
	
	//Create the clcmds
	Initialize_CLCMD ( );
	
	//Create the Menus
	Initialize_Menus ( );
	
	//Register Events
	RegisterEvents( );
	
	//Register Message traps
	RegisterMessages ( );
	
	//Register the Log Events
	Initialize_LogEvents ( );

	//Create and Bind Cvars needed for Gameplay
	Register_Cvars ( );
	set_task(0.5, "Exec_User_CFG", TASK_EXEC_CFG);
	set_task(0.6, "Bind_Cvars", TASK_BIND_CVARS);
	
	//Set the initial Tasks we need
	Initialize_Tasks ( );
	
	//Init the hud messages
	InitHud();
	
	// set_task calls for functions needed by init or to run continuously
	set_task ( 10.0, "Check_UWC3X", TASK_CHECK_UWC3X, "", 0, "b" );
	set_task ( 1.0, "Check_UWC3X", TASK_CHECK_UWC3X_AGAIN );
	set_task ( 0.01, "TASK_Check_Duck", TASK_DO_NOW, "", 0, "b" );
	set_task ( 2.0, "TASK_CHECK_FOOTSTEPS", TASK_CHECK_FOOTSTEPS_NOID, "", 0, "b" );
	set_task ( 0.01, "TASK_CHECK_USER_SPEED", TASK_CHECK_USER_SPEED_NOID, "", 0, "b" );

	// Set weapon xp modifiers
	set_task(0.7, "XP_SetMultiplier", TASK_SET_XP_MULTIPLIER);
	
	// Set skills-based tables ( skill levels, effects, etc )
	set_task(0.8, "Set_Skill_Limits", TASK_SET_SKILL_LIMITS);
	
	//Load the XP Configuration and Storage Detection
	set_task(0.9, "LoadXPConfig", TASK_LOAD_XP_CONFIG);
	log_amx( "[%s] Initialized UWC3X Plugin Version %s", MOD, UWC3XVERSION );
}

public plugin_precache ( ) 
{	
	PreCache_Sounds ( );
	PreCache_Models ( );
	PreCache_Sprites ( );
	
	return PLUGIN_CONTINUE;
}

public set_variables ( )
{
	//Set the base XP Values
	XP_SetBase_Values ( );
	
	//Checks to make sure enhancements are enabled and sets the values
	Initialize_Enhancements ( );

	//Check for Admin only skills, and set them accordingly
	SetAdminOnlySkills ( );

	//Checks for Custom Shopmenu Item prices and values
	SetUser_Defined_Item_Values ( );

	//See if the redirection system by level is enabled, and set the base values
	Check_Redirection_Level_System ( );
	
	XP_SetChoice();

	return PLUGIN_CONTINUE;
}

public client_connect ( id )
{
	hudchat_clear(id);
	client_cmd ( id, "hud_centerid 0" );
	g_specMode[id] = false;

	// Initialize player data ( NOT limited init mode )
	if( CVAR_DEBUG_MODE)
	{
		log_amx( "DEBUG :: SMA -> Initializing Player data - non limited" );
	}	
	
	Initialize_PlayerData ( id, false );
	kickflag[id] = 0;
	jumpnum[id] = 0;
	dojump[id] = false;
	
	if ( CVAR_LOWRES_DEFAULT )
	{
		// Reset lowres to true for player slot
		lowres[id] = true;
	}
	else
	{
		// Reset lowres boolean for thisplayer
		lowres[id] = false;
	}

	xpreadytoload[id] = 0;
	PlayerAuthed[id] = false;
	PrintConnectMessage ( id );
	return PLUGIN_CONTINUE;
}

public client_disconnect ( id )
{
	hudchat_clear(id);
	PlayerAuthed[id]	= false;	// Reset teh Authorized Steam Setting
	g_specMode[id]		= false;	// Reset spectator status for player
	isburning[id]		= 0;		// Reset burning status for player ( flamethrower )
	isnburning[id]		= 0;		// Reset burning status for player ( napalm burn )
	ispoisonedss[id]	= 0;		// Reset poisoned status for player
	isdiseasedcb[id]	= 0;		// Reset diseased status for player
	repairs[id]			= 0;		// Reset number of repairs done
	mends[id]			= 0;		// Reset number of mends done
	he[id]				= 0;		// Reset he grenade status
	threwnapalm[id]		= 0;		// Reset status of napalm gren for round
	diedlastround[id]	= false;	// Reset status for player death previous round
	lastpspage[id]		= 0;		// Reset last player skill page read to 0
	hasmole[id]			= false; 	// Reset mole item global
	itemsrunning[id]	= false;	// Reset itemsrunning for userid
	loadedlevel[id]		= 0;		// Reset status for having initial level loaded
	vengeance_used[id]	= 0;		// Reset vengeance status
	playeritem[id]		= 0;		// Reset Shopmenu Item
	playeritem2[id]		= 0;		// Reset Shopmenu2 Item
	playeritem3[id]		= 0;		// Reset Shopmenu3 Item
	playertombs[id]		= 0;		// Reset Tomes purchased
	unammo[id]			= false;
	badaim[id]			= false;
	hasFrostNade[id]	= false;
	isChilled[id]		= false;
	isFrozen[id]		= false;

	//Hook
	HkDelay[id] 		= 0.0
	HookCount[id] 		= 0
	hooked[id] 			= false
	
	//Jumpkick
	kickflag[id]		= 0;		// Reset kick flag

	//multijump
	dojump[id]			= false;
	jumpnum[id]			= 0;
	
	//User is not rotting
	bIsRotting[id]		= false;
	
	//Cloak of chameleon
	CheckCloak[id]		= true;
	
	//Team Shield stuff
	HasTeamShield[id]	= false;
	p_ShieldMaxDamageAbsorbed[id] = 0;
	UsedTeamShield[id]	= 0;
	TeamShieldCooldown[id]	= 0;

	//Depower
	UsedDepower[id]		= 0;
	BlockPickup[id]		= false;

	//Reset Cripple
	crippletype[id]		= 0;
	iscrippled[id]		= 0;
	
	if ( CVAR_LOWRES_DEFAULT )
	{
		// Reset lowres to true for player slot
		lowres[id] = true;
	}
	else
	{
		// Reset lowres boolean for thisplayer
		lowres[id] = false;
	}
	
	for ( new i=0; i<32; ++i )
	{
		// Reset due to Equipment Reincarnation
		savedweapons[id][i] = 0;
	}

	if ( playerxp[id] < 100 ) 
	{
		return PLUGIN_CONTINUE;
	}
	
	if ( CVAR_SAVE_XP && !is_user_bot ( id ) && playerxp[id] )
	{
		SaveSinglePlayerXP ( id );
		xpreadytoload[id] = 0;
	}

	PrintDisconnectMessage ( id );
	return PLUGIN_CONTINUE;
}

public client_PreThink ( id ) 
{
	//If they are a bot, not alive, or not connected, then we dont care about them
	if( !is_user_alive(id) || !is_user_connected(id)  || is_user_bot( id ) ) 
		return PLUGIN_CONTINUE;

	//Disable slow down after jumping
	entity_set_float ( id, EV_FL_fuser2, 0.0 );
	
	if(badaim[id])
	{
		new Float:badvec[3] = {100.0,100.0,100.0};
		for(new j = 0;j<6;j++)
		{
			entity_set_vector(id,EV_VEC_punchangle,badvec);  
			entity_set_vector(id,EV_VEC_punchangle,badvec);
			entity_set_vector(id,EV_VEC_punchangle,badvec);  //Three's a charm!
		}
	}
	
	// if they are frozen, make sure they don't move at all
	if(isFrozen[id])
	{
		// stop motion
		entity_set_vector(id,EV_VEC_velocity,Float:{0.0,0.0,0.0});

		new button = get_user_button(id), oldbuttons = entity_get_int(id,EV_INT_oldbuttons);
		new flags = entity_get_int(id,EV_INT_flags);

		// if are on the ground and about to jump, set the gravity too high to really do so
		if( (button & IN_JUMP) && !(oldbuttons & IN_JUMP) && (flags & FL_ONGROUND) )
		{
			// I CAN'T STAND THE PRESSURE
			entity_set_float(id,EV_FL_gravity,999999.9); 
		}
		else
		{
			// otherwise, set the gravity so low that they don't fall
			entity_set_float(id,EV_FL_gravity,0.000001); // 0.0 doesn't work
		}
	}

	//Multi Jump
	new MJ_SKILL = p_skills[id][SKILLIDX_MULTIJUMP];
	if( MJ_SKILL ) 
	{
		new nbut = get_user_button(id);
		new obut = get_user_oldbutton(id);
		
		new maxjumps = p_maxjumps[ MJ_SKILL ];
				
		if((nbut & IN_JUMP) && !(get_entity_flags(id) & FL_ONGROUND) && !(obut & IN_JUMP))
		{			
			if( jumpnum[id] < maxjumps )
			{				
				dojump[id] = true;
				jumpnum[id]++;
				return PLUGIN_CONTINUE;
			}
		}
		
		if((nbut & IN_JUMP) && (get_entity_flags(id) & FL_ONGROUND))
		{
			jumpnum[id] = 0;
			return PLUGIN_CONTINUE;
		}
	}

	//Jumpkick
	if( p_skills[id][SKILLIDX_JUMPKICK] )
	{
		if( kickflag[id] == 0 && (entity_get_int(id, EV_INT_button) & 2 ) )
		{	
			client_cmd(id,"-jump");
			new ent,Float:origin[3];
			entity_get_vector(id,EV_VEC_origin,origin);
			
			while((ent = find_ent_in_sphere(ent,origin,CVAR_JUMPKICK_RADIUS)) != 0) 
			{
				if(!is_user_alive(ent) || ent == id || get_user_team(id) == get_user_team(ent))
					continue;

				kickflag[id] = 1;
				new parm[1];
				parm[0] = id;
									
				set_task( CVAR_JUMPKICK_COOLDOWN,"Task_Jumpkick_Cooldown", TASK_JUMPKICK + id, parm, 1 );
				damage_ent(ent,id);
			} 
		}
	}
	
	return PLUGIN_CONTINUE;
	
}

public client_PostThink(id)
{
	//If they are a bot, not alive, or not connected, then we dont care about them
	if( !is_user_alive(id) || !is_user_connected(id) || is_user_bot( id ) ) 
		return PLUGIN_CONTINUE;
		
	new MJ_SKILL = p_skills[id][SKILLIDX_MULTIJUMP];
			
	if( MJ_SKILL ) 
	{
		if( dojump[id] == true )
		{
			new Float:velocity[3];
			entity_get_vector(id,EV_VEC_velocity,velocity);
			velocity[2] = random_float(265.0,285.0);
			entity_set_vector(id,EV_VEC_velocity,velocity);
			dojump[id] = false;
			return PLUGIN_CONTINUE;
		}
	}
	
	return PLUGIN_CONTINUE;
}	

public plugin_end ( )
{
	if ( CVAR_ENABLE_UWC3X && CVAR_SAVE_XP )
	{
		SaveAllPlayersXP ( );
	}
	
	EndHud();
	return PLUGIN_CONTINUE;
}
