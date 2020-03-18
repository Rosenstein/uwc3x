public RegisterEvents ( )
{

	// Event related entries follow
	register_event ( "TextMsg",			"game_commencing",	"a",	"2&#Game_C"						 );
	register_event ( "TextMsg",			"restart_round",	"a",	"2&#Game_will_restart_in"		 );
	register_event ( "TextMsg",			"Target_Bombed",	"a",	"2&#Target_Bombed"				 );
	register_event ( "TextMsg",			"setSpecMode",		"bd",	"2&ec_Mod"						 );
	register_event ( "StatusValue",		"setTeam",			"be",	"1=1"							 );
	//register_event ( "StatusValue",		"showStatus",		"be",	"1=2",		"2!0"				 );
	//register_event ( "StatusValue",		"hideStatus",		"be",	"1=1",		"2=0"				 );
	//register_event ( "StatusValue",		"showRank",			"bd",	"1=2"							 );
	register_event ( "StatusIcon",		"BuyZone",			"be",	"2=buyzone"						 );
	register_event ( "StatusIcon",		"got_defuse",		"be",	"1=1",		"1=2",	"2=defuser" );
	register_event ( "ResetHUD",		"new_round",		"b"										 );
	register_event ( "SetFOV",			"zoomed2",			"be",	"1<90"							 );
	register_event ( "SetFOV",			"unzoomed",			"be",	"1=90"							 );
	register_event ( "Damage",			"damage_event",		"b",	"2!0"							 );
	register_event ( "DeathMsg",		"death",			"a"										 );
	register_event ( "SendAudio",		"T_win",			"a",	"2=%!MRAD_terwin"				 );
	register_event ( "SendAudio",		"CT_win",			"a",	"2=%!MRAD_ctwin"				 );
	register_event ( "SendAudio",		"nade_thrown",		"bc",	"2=%!MRAD_FIREINHOLE"			 );
	register_event ( "WeapPickup",		"check_weap",		"b"										 );
	register_event ( "CurWeapon",		"change_weapon",	"be",	"1=1"							 );
	register_event ( "ArmorType",		"armor_type",		"be"									 );

	register_forward( FM_SetModel, "fw_setmodel" );
	register_think( "grenade", "think_grenade" );
	register_think("Mine","Mine_Think")
	register_forward(FM_AddToFullPack, "client_AddToFullPack")
}


public RegisterMessages ( )
{
	register_message( 23, "grenade_explosion" );
	register_message( 77, "fire_in_the_hole" );
	register_message( 99, "grenade_throw" );
}

public game_commencing ( )
{
	new players[32], numplayers, id;
	get_players ( players, numplayers );

	for ( new i=0; i<numplayers; i++ )
	{
		id=players[i];
		game_commence[id] = true;
	}
}

public CheckFrostNades( id )
{
	//Set to 0 as a default value
	hasFrostNade[id] = 0;

	//Only check if they have the skill
	if( p_skills[id][SKILLIDX_ICENADE] )
	{
		new weapons[32], num, i;
		get_user_weapons(id,weapons,num);

		for(i=0;i<num;i++)
		{
			if( IsWeaponSmokeGrenade( CSW_SMOKEGRENADE ) )
			{
				hasFrostNade[id] = 1;
				break;
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public restart_round ( )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new players[32], numplayers, id;
	get_players ( players, numplayers );

	for ( new i = 0; i < numplayers; i++ )
	{
		id = players[i];

		Initialize_PlayerData(id, true);
		playeritem[id] = 0;
		playeritem2[id] = 0;
		playeritem3[id] = 0;
		playertombs[id] = 0;
		he[id] = 0;
		threwnapalm[id] = 0;
		flashg[id] = 0;
		diedlastround[id] = false;
		p_spawnprotection[id ] = 0;

		if ( CVAR_SAVE_XP == 0 )
		{
			// Set player to level 0
			p_level[id]=0;

			if ( CVAR_DEBUG_MODE )
			{
				// Set player starting XP to DEBUG value
				playerxp[id] = DEBUG_STARTXP;
			}
			else
			{
				// Set player starting XP to 0
				playerxp[id] = 0;
			}

			for ( new j = 0; j < MAX_SKILLS; j++ )
			{
				// Set all skills to 0;
				p_skills[id][j] = 0;
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public new_round ( id )
{

	new origin[3], name[32];

	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	if ( !Util_Is_Valid_Player( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	bombstate = BOMB_NOTPLANTED;
	if ( game_commence[id] )
	{
		playeritem[id] = 0;
		playeritem2[id] = 0;
		playeritem3[id] = 0;
		diedlastround[id] = false;
		game_commence[id] = false;

		// Reset spawn sites internally

		for ( new i=0; i < MAX_PLAYERS; i++ )
		{
			Tspawnpts[i] = { 0, 0, 0 };
			CTspawnpts[i] = { 0, 0, 0 };
		}
	}

	//Reset the amount of tombs the player has purchased
	playertombs[id] = 0;

	//Reset the amounts of wards they have used
	wardsused[id] = 0;

	if ( dropskill[id] )
	{
		dropskill[id] = false;
	}

	// [09-13-04] Fix for Voodoo missing end_round task check - K2mia
	if ( task_exists ( TASK_RESET_GODMODE + id ) )
	{
		// Resets godmode
		remove_task ( TASK_RESET_GODMODE + id );

		set_user_health_log ( id, maxhealth[id] );
		hasgodmode[id] = false;
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 0, 100, 0, 0.05, 0.75, 2, 0.02, 10.0, 0.01, 0.1, 2 );
			show_hudmessage ( id, "Your Voodoo has been reset" );
		}
	}

	// [09-24-04] Added check for # skill points being in sync with player level - K2mia
	if ( CVAR_ROUND_CHECK )
	{
		new skillptamount = CVAR_SKILLPOINTS_PER_LEVEL;
		new pname[32];
		get_user_name ( id, pname, 31 );

		new skillcount = get_skillcount ( id ) ;

		if ( ( skillcount > skillptamount * p_level[id] ) || Ult_TooMany(id) )
		{
			if( Util_Is_Valid_Player( id ) && !is_user_bot(id) )
			{
				if( Util_Should_Msg_Client(id) )
				{	
					if( Ult_TooMany(id) )
					{
						client_print ( id, print_center, "%L", id, "ULT_TOO_MANY", MOD );
					}
					else
					{
						client_print ( id, print_center, "%L", id, "SKILL_TOO_MANY", MOD );
					}
				}
				
				if( Ult_TooMany(id) )
				{
					log_amx( "[UWC3X] TOO MANY ULTIMATES: ( %s ) level= ( %d ) allowed=( %d ) ultcount= ( %d )", pname, p_level[id], p_maxultimates[id], Get_Ult_Count( id ) );
				}
				else
				{
					log_amx( "[UWC3X] TOO MANY SKILLPOINTS: ( %s ) level= ( %d ) skillcount= ( %d )", pname, p_level[id], skillcount );
				}
			}

			for ( new j=0; j<MAX_SKILLS; j++ )
			{
				// Set all skills to 0
				p_skills[id][j] = 0;
			}

			ultlearned[id] = 0;
			displaylevel ( id, 3 );
			SaveXP ( id );
		}
		
	}
	// [09-24-04] End of Added check for # skill points being in sync with player level

	// Free this mole spawn position for use this round
	MOLEspawnpts[id] = 0;

	if ( CVAR_COMPETITIVE && !buycalled ){
		set_task ( get_cvar_float ( "mp_buytime" ) * 60.0, "set_buytime", 899 );
		buycalled = true;
	}

	icon_controller ( id );
	deathmessageshown[id] = false;
	to_be_revived[id] = false;
	vengeance_state[id] = VENG_READY;

	if ( CVAR_XP_BONUS_FOR_DAMAGE )
	{
		for ( new i=0; i < MAX_PLAYERS; i++ )
		{
			damageto[id][i] = -1;
		}
	}

	if ( CVAR_SAVE_XP && xpreadytoload[id] )
	{
		LoadXP ( id );
		xpreadytoload[id] = 0;
	}
	else if ( !CVAR_SAVE_XP )
	{
		if( is_user_connected( id ) && !is_user_bot(id) )
		{
			set_hudmessage ( 200, 100, 0, -1.0, 0.35, 0, 1.0, 15.0, 0.1, 0.2, 2 );
			show_hudmessage ( id, "Server Mode: Fast XP -- Long Term XP is Disabled" );
		}
	}

	if ( CVAR_DEBUG_MODE )
	{
		if( CVAR_USE_DEBUG_CASH )
		{
			cs_set_user_money ( id, DEBUG_CASH );
		}
	}

	// Store spawn pt for use with mole
	get_user_name ( id, name, 31 );
	get_user_origin ( id, origin );

	if ( get_user_team ( id ) == TEAM_T )
	{
		for ( new i=0; i<MAX_PLAYERS; i++ )
		{
			if ( ( Tspawnpts[i][0] + Tspawnpts[i][1] + Tspawnpts[i][2] ) == 0 )
			{
				Tspawnpts[i] = origin;
				break;
			}
		}
	}
	else
	{
		for ( new i=0; i<MAX_PLAYERS; i++ )
		{
			if ( ( CTspawnpts[i][0] + CTspawnpts[i][1] + CTspawnpts[i][2] ) == 0 )
			{
				CTspawnpts[i] = origin;
				break;
			}
		}
	}

	// [08-04-04] - Added check for resetting attribs/resists - K2mia
	if ( resetattrib[id] )
	{
		for ( new j=0; j<MAX_ATTRIBS; j++ )
		{
			// Set all attributes to the default
			p_attribs[id][j] = ATTRIB_BASE;
		}
		
		Set_Wisdom_Bonuses(id);
		resetattrib[id] = false;
	}

	if ( resetresist[id] )
	{
		for ( new j=0; j<MAX_RESISTS; j++ )
		{
			// Set all resistances to 0
			p_resists[id][j] = 0;
		}
		resetresist[id] = false;
	}

	if ( reloadskill[id] )
	{
		for ( new j=0; j<MAX_SKILLS; j++ )
		{
			// Set all skills to 0
			p_skills[id][j]=0;
		}

		ultlearned[id] = 0;
		Set_Ult_Count(id);
		reloadskill[id] = false;
		displaylevel ( id, 3 );
	}

	if( loadskillset[id] )
	{
		LoadSkillSet( id, s_loadskillset[id] )
		loadskillset[id] = false;
		displaylevel ( id, 3 );
	}

	if( saveskillset[id] )
	{
		SaveSkillSet( id, s_saveskillset[id] )
		saveskillset[id] = false;
		displaylevel ( id, 3 );
	}
	
	if (deleteskillset[id])
	{
		DeleteSkillSet(id, s_deleteskillset[id]);
		deleteskillset[id] = false;
		displaylevel(id, 3);
	}

	p_PlayerShieldedBy[id] = 0; // Are not shielding anyone
	HasTeamShield[id] = false; //Does not have a shield on them
	healingwaves[id] = 0;

	if ( playerhasspawned[id] )
	{	
		if ( p_skills[id][SKILLIDX_SERPWARD] )
		{
			// Serpent Ward
			serpents[id] = p_serpent[p_skills[id][SKILLIDX_SERPWARD]-1];
			if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_INT] >= INT_SERPENT_LEVEL ) )
			{
				serpents[id] += INT_SERPENT_BONUS;
			}
		}
		else
		{
			serpents[id] = 0;
		}
		
		Skills_Check ( id, true );

		if ( !freezetime && !ultimateused[id] )
		{
			icon_controller ( id );
		}

		if ( stunned[id] || slowed[id] )
		{
			set_user_maxspeed ( id, 240.0 );
		}

		if ( playeritem2[id] != MOLE )
		{
			playeritem2[id] = 0;
		}

		playeritem[id] = 0;
		playeritem2[id] = 0;
		playeritem3[id] = 0;
		playerCanBuyitem3[id] = 1;
		blessed[id] = false;
		gateused[id] = false;

		//Remove the Shield Check task and reset teh vars
		if( task_exists(TASK_SHIELD_CHECK_ID + id) )
		{
			remove_task( TASK_SHIELD_CHECK_ID + id );
		}

		changeskin ( id, 1 );
		displaylevel ( id, 3 );
		return PLUGIN_CONTINUE;
	}

	if ( hasmole[id] && playeritem2[id] != MOLE )
	{
		playeritem2[id] = MOLE;
	}

	//Set the ultimate cool down if they are in freezetime
	u_delay = false;
	if ( CVAR_ULTIMATE_DELAY && freezetime )
	{
		u_delay = true;

		if ( !task_exists ( 12385 ) )
		{
			set_task ( float(CVAR_ULTIMATE_DELAY) , "udelay_cooldown", 12385 );
		}
	}

	gateused[id] = false;
	bHexed[id] = false;

	//Remove the Shield Check task and reset teh vars
	if( task_exists(TASK_SHIELD_CHECK_ID + id) )
	{
		remove_task( TASK_SHIELD_CHECK_ID + id );
	}

	//if( task_exists( TASK_ULTIMATE_ENTANGLE_SEARCH + id ) )
	//{
	//	remove_task( TASK_ULTIMATE_ENTANGLE_SEARCH + id );
	//}

	//Reset the base events
	if ( task_exists ( TASK_DRAW_MEDIC_SPRITES ) )
	{
		// Stops the medic sprite display
		remove_task ( TASK_DRAW_MEDIC_SPRITES );
	}

	//Removes ROT
	if( task_exists ( 755 + id ) )
	{
		remove_task ( 755 + id );
	}

	if ( task_exists ( TASK_MONITOR_PLAYERS ) )
	{
		// Stops the monitor_players routine
		remove_task ( TASK_MONITOR_PLAYERS );
	}

	if ( task_exists ( 200+id ) )
	{
		// Stops any ultimates from continuing when the new round starts
		remove_task ( 200 + id );
	}

	if ( task_exists ( id + TASK_COOLDOWN_RESET ) )
	{
		// Stop any cooldowns in effect
		remove_task ( TASK_COOLDOWN_RESET + id );
	}

	if ( task_exists ( id + 645 ) )
	{
		// Remove bomb count down
		remove_task ( 645 + id );
	}

	if ( task_exists ( id + TASK_JUMPKICK ) )
	{
		// Remove jumpkick cooldown check
		remove_task ( id + TASK_JUMPKICK );
	}
	
	RemoveTaskIfExists(TASK_ON_FIRE_NAPALM + id);
	RemoveTaskIfExists(TASK_ON_FIRE + id);
	RemoveTaskIfExists(TASK_ON_SSPOISON + id);
	RemoveTaskIfExists(TASK_ON_CBDISEASE + id);
	RemoveTaskIfExists(TASK_ON_ROT + id);

	//RESET SHOPMENU3 TASKS
	if( task_exists( SHOPMENU3_RESET + id ) )
	{
		remove_task ( SHOPMENU3_RESET + id );
	}

	// [09-03-04] - Display the medic alert sprites - K2mia
	if ( CVAR_MEDIC_ALERTS == 2 )
	{
		set_task ( 1.0, "Draw_Medic_Repair_Sprites", TASK_DRAW_MEDIC_SPRITES );
	}

	// [09-24-04] - Added check for insane amounts of player health
	set_task ( 3.0, "monitor_players", TASK_MONITOR_PLAYERS );

	buytime = true;
	new parm[2];
	parm[0] = id;

	if ( freezecalled == 0 )
	{
		//changed freetime to boolean Smokey ( thanks to slmclarengt )
		freezetime = false;
		freezecalled = 1;
	}

	if ( CVAR_BLINK_START_DISABLED )
	{
		blinkdelayed[id] = true;
		set_task ( CVAR_BLINK_DELAY ,"cooldown2", TASK_COOLDOWN2 + id, parm, 1 );
	}

	if ( CVAR_WARN_SUICIDE )
	{
		suicideAttempt[id] = 0;
	}

	if ( is_user_connected ( id ) )
	{
		if ( playeritem2[id]==HELM )
		{
			set_user_hitzones ( 0, id, 253 );
		}
	}

	// Weapon Reincarnation
	set_task ( 0.1, "weapon_controller", TASK_WEAPOM_CONTROLLER, parm, 2 );

	// Perform a Limited init of player data
	Initialize_PlayerData ( id, true );

	// New round, reset endround state
	endround = false;

	// Reset hostagesaver state
	hostagesaver = 0;

	//Pick skills for the bots if there are any to pick
	if( is_user_bot( id ) )
	{
		if( CVAR_ENABLE_BOT_SKILLS )
		{
			Skills_PickBotStuff( id );
		}
	}

	// Check skill affects, set user health
	Skills_Check ( id, true );

	// Chec for Fan of Knives
	Task_Check_Fan ( id );

	// Check for Cloak of the chameleon
	Skills_Award_Cloak ( id );

	new speedparm[1];
	speedparm[0] = id;
	Set_Speed( speedparm );

	if ( CVAR_RESET_SKILLS )
	{
		if ( resetskill[id] )
		{
			for ( new j = 0; j < MAX_SKILLS; j++ )
			{
				//User wants to reset their skills, so lets set all skills to 0
				p_skills[id][j] = 0;
			}

			//Set their ultimates to 0
			ultlearned[id] = 0;

			// [obe:2005] set skillset stuff ( using xerobloods explode string stock ( ty :D ) )
			if ( set_skillset[id] )
			{
				new tempSkillArray[MAX_SKILLS][8], tempSetSkill[3][8], setskillID, setskillLevel, totalCount = 0;
				new bool:canHaveSkill;

				ExplodeString ( tempSkillArray, MAX_SKILLS, 7, str_skillset[id], '#' );

				for ( new j=0; j<MAX_SKILLS; j++ )
				{
					if ( !equali ( tempSkillArray[j],"" ) )
					{
						if ( contain ( tempSkillArray[j],"-" ) )
						{
							// skill isnt an ultimate
							ExplodeString ( tempSetSkill, 3, 7, tempSkillArray[j], '-' );

							// check to make sure player can actually level this skill up
							setskillID = str_to_num ( tempSetSkill[0] );
							setskillLevel = str_to_num ( tempSetSkill[1] );
							canHaveSkill = true;

							// Check if player has min. level
							if ( p_level[id] < skill_minlev[setskillID] )
							{
								canHaveSkill = false;

								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR1" );
								}

							}

							// Check if player isnt trying to add skills beyond their current level
							if ( totalCount + setskillLevel > p_level[id] )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR2" );
								}
							}

							// Check if player is already trained in this skill
							if ( p_skills[id][setskillID] )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR3" );
								}
							}

							// Check if player is trying to train a skill above its max ( if so, set it to the right max )
							if ( p_skills[id][setskillID] >= skill_limits[setskillID] )
							{
								setskillLevel = skill_limits[setskillID];
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR4" );
								}
							}

							// Check so players can only put 1 skill pt into a skill for each level over ( or equal ) to the min. level to train it
							new allowed_pts = ( p_level[id] - skill_minlev[setskillID] + 1 );
							if ( ( skill_limits[setskillID] > 1 ) && ( p_skills[id][setskillID] >= allowed_pts ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR5" );
								}
							}

							/*
								Specific skill-restrictions follow
								( some skills dont work with others )
							*/

							// Only allow Steel Skin if Vampiric and Leather Skin trained
							if ( setskillID == SKILLIDX_SSKIN && ( ( p_skills[id][SKILLIDX_LSKIN] < 3 ) || ! ( p_skills[id][SKILLIDX_VAMPIRIC] ) ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "STEAL_NOTICE2" );
								}
							}

							// Allow only one siphon skill
							if ( ( setskillID == SKILLIDX_SIPHON ) && ( p_skills[id][SKILLIDX_SAMMO] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SYPHON_ERROR1" );
								}
							}
							else if ( ( setskillID == SKILLIDX_SAMMO ) && ( p_skills[id][SKILLIDX_SIPHON] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SYPHON_ERROR2" );
								}
							}

							// Allow only one damage shield skill
							if ( ( setskillID == SKILLIDX_CARAPACE ) && ( p_skills[id][SKILLIDX_THORNS] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "DAMAGE_SKILL_ERROR1" );
								}
							}
							else if ( ( setskillID == SKILLIDX_THORNS ) && ( p_skills[id][SKILLIDX_CARAPACE] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "DAMAGE_SKILL_ERROR2" );
								}
							}

							//Make sure they still have the Cripple requirements
							if ( ( setskillID == SKILLIDX_CRIPPLE ) && ( p_skills[id][SKILLIDX_BASH] < 3 || p_skills[id][SKILLIDX_TRUESHOT] < 2) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "CRIPPLE_ERROR1" );
								}
							}

							// Allow only one of Shadow Strike / Carrion Beetles
							if ( ( setskillID == SKILLIDX_SSTRIKE ) && ( p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "POISON_DISEASE_ERROR1" );
								}

							}
							else if ( ( setskillID == SKILLIDX_CARRION ) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "POISON_DISEASE_ERROR2" );
								}
							}
							else if ( ( setskillID == SKILLIDX_ROT ) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_CRIPPLE] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "POISON_DISEASE_ERROR3" );
								}
							}
							else if ( ( setskillID == SKILLIDX_CRIPPLE ) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CARRION] ) )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "POISON_DISEASE_ERROR4" );
								}
							}


							if ( canHaveSkill )
							{
								p_skills[id][setskillID] = setskillLevel;
								totalCount += setskillLevel;
							}

						}
						else if ( contain ( tempSkillArray[j], "+" ) )
						{
							// Skill is an ultimate
							ExplodeString ( tempSetSkill, 3, 7, tempSkillArray[j], '+' );

							// Check to make sure player can actually level this skill up
							setskillID = str_to_num ( tempSetSkill[0] );
							setskillLevel = str_to_num ( tempSetSkill[1] );
							canHaveSkill = true;

							// Check if player has min. level
							if ( p_level[id] < skill_minlev[setskillID] )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR6" );
								}
							}

							// Check if player isnt trying to add skills beyond their current level
							if ( totalCount + setskillLevel > p_level[id] )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR7" );
								}
							}

							// Check if player is already trained in this skill
							if ( p_skills[id][setskillID] )
							{
								canHaveSkill = false;
								if( Util_Should_Msg_Client(id) )
								{
									client_print ( id, print_console, "%L", id, "SKILL_ERROR3" );
								}
							}

							// Allow only one of Vengeance / Suicide Bomber
							if ( ( setskillID == SKILLIDX_VENGEANCE ) && ( p_skills[id][SKILLIDX_SUICIDE] ) )
							{
								canHaveSkill = false;
							}
							else if ( ( setskillID == SKILLIDX_SUICIDE ) && ( p_skills[id][SKILLIDX_VENGEANCE] ) )
							{
								canHaveSkill = false;
							}

							// Player has trained maximum # of ultimate skills
							if ( ( ultlearned[id] >= p_maxultimates[id] ) && ( skill_ultimates[setskillID][0] ) ){
								canHaveSkill = false;
							}

							if ( canHaveSkill )
							{
								p_skills[id][setskillID] = setskillLevel;
								totalCount += setskillLevel;
								ultimateused[id] = false;
								ultlearned[id]++;
								Set_Ult_Count(id);
							}
						}
					}
				}

				set_skillset[id] = false;
			}

			//p_level[id] = 0;
			resetskill[id] = false;
			displaylevel ( id, 3 );
		}

		// [08-04-04] - Added check for resetting attribs/resists - K2mia
		if ( resetattrib[id] )
		{
			for ( new j=0; j<MAX_ATTRIBS; j++ )
			{
				// Set all attributes to the default
				p_attribs[id][j] = ATTRIB_BASE;
			}
			resetattrib[id] = false;
		}

		if ( resetresist[id] )
		{
			for ( new j=0; j<MAX_RESISTS; j++ )
			{
				// Set all resistances to 0
				p_resists[id][j] = 0;
			}
			resetresist[id] = false;
		}

		if ( reloadskill[id] )
		{
			for ( new j=0; j<MAX_SKILLS; j++ )
			{
				// Set all skills to 0
				p_skills[id][j]=0;
			}

			ultlearned[id] = 0;
			Set_Ult_Count(id);
			reloadskill[id] = false;
			displaylevel ( id, 3 );
		}

		if( loadskillset[id] )
		{
			LoadSkillSet( id, s_loadskillset[id] )
			loadskillset[id] = false;
			displaylevel ( id, 3 );
		}

		if( saveskillset[id] )
		{
			SaveSkillSet( id, s_saveskillset[id] )
			saveskillset[id] = false;
			displaylevel ( id, 3 );
		}

		// Reset dropskill for id to allow for selecting new skills - Marticus
		if ( dropskill[id] )
		{
			dropskill[id] = false;
		}

	}

	vengeance_used[id] = 0;

	new acount = get_attribcount ( id );
	new apts = get_availattribpts ( id );
	new rcount = get_resistcount ( id );
	new rpts = get_availresistpts ( id );

	if ( ( apts > 0 ) && ( acount < ( ( MAX_ATTRIBS-1 ) * ( ATTRIB_MAX_VALUE - ATTRIB_BASE ) ) ) && ( acount < ATTRIB_MAX_PTS ) )
	{
		Select_Attrib ( id );
	}
	else if ( ( rpts > 0 ) && ( rcount < ( ( MAX_RESISTS-1 ) * RESIST_MAX_VALUE ) ) && ( rcount < RESIST_MAX_PTS ) )
	{
		Select_Resist ( id );
	}
	else
	{
		// Determine if player has skills that can be learned
		new skillptsavail = get_availskillpts ( id );

		if ( skillptsavail )
		{
			select_skill ( id, 1 );
		}
	}

	return PLUGIN_CONTINUE;
}

public round_start ( )
{
	//mapbounds_killer();

	new players[32], y, id, numberofplayers;
	get_players ( players, numberofplayers );

	for ( y = 0; y < numberofplayers; ++y )
	{
		id = players[y];
		Skills_Check ( id, false );
	}

}

public end_round ( )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	endround = true;
	buycalled = false;

	new players[32], y, id, numberofplayers;
	get_players ( players, numberofplayers );

	if ( task_exists ( 899 ) )
	{
		remove_task ( 899 );
	}

	for ( y = 0; y < numberofplayers; ++y )
	{
		spawnPointsused[y] = false;
	}

	for ( y = 0; y < numberofplayers; ++y )
	{
		id = players[y];
		
		if( task_exists ( 130 + id ))
		{
			if ( task_exists ( TASK_ENTANGLE_STOP + id ) )
			{
				remove_task ( TASK_ENTANGLE_STOP + id );
				stunned[id] = false;
			} 

			new roots_ent = create_entity("info_target");
			new args[1];
			args[0] = roots_ent;
			set_task(0.1, "Task_Destroy_Roots", TASK_ENTANGLE_STOP + id, args, 1);
		}

		if( task_exists( TASK_CLEANUP_MINE+id))
		{
			remove_task ( TASK_ENTANGLE_STOP + id );
		}

		if (p_skills[id][SKILLIDX_MINE])
		{
			new ent = create_entity("info_target");
			new args[2];
			args[0] = id;
			args[1] = ent;
			set_task(0.1, "TASK_Destroy_Mine", TASK_CLEANUP_MINE+id, args, 1);
		}
  		
		// Removes walker ( undead changing speed )
		if ( task_exists ( 600+id ) )
		{
			remove_task ( 600+id );
		}

		// Removes any current healing processes
		if ( task_exists ( id+90 ) )
		{
			remove_task ( id+90 );
		}

		// Removes any current con healing proocesses
		if ( task_exists ( id+1100 ) )
		{
			remove_task ( id+1100 );
		}

		// Removes any leather/steel skin proocesses
		if ( task_exists ( id+1200 ) )
		{
			remove_task ( id+1200 );
		}

		// Removes undead flashing process
		if ( task_exists ( 9000+id ) )
		{
			remove_task ( 9000+id );
		}

		// Removes hex jumping [obe:2005 fix]
		if ( task_exists ( 2000+id ) )
		{
			remove_task ( 2000+id );
		}

		// Remove any current cooldowns
		if ( task_exists ( 50+id ) )
		{
			remove_task ( 50+id );
		}

		//Remove Cripple
		if( task_exists ( TASK_RESET_CRIPPLE_ID + id ) )
		{
			remove_task ( TASK_RESET_CRIPPLE_ID + id );
		}

		// Remove any reset_maxspeeds occuring ( a person could to move during freezetime
		if ( task_exists ( TASK_RESET_MAXSPEED+id ) )
		{
			remove_task ( TASK_RESET_MAXSPEED+id );
			new parm[2];
			parm[0] = id;
			reset_maxspeed ( parm );
		}

		// Resets godmode
		if ( task_exists ( TASK_RESET_GODMODE+id ) )
		{
			remove_task ( TASK_RESET_GODMODE+id );
			new parm[2];
			parm[0] = id;
			Task_Reset_Godmode ( parm );
		}

		if ( is_user_alive ( id ) )
		{
			saveweapons ( id );
		}

		spawnedfromitem[id] = false;
		playerhasspawned[id] = false;

		if ( playeritem2[id] != CHAMELEON )
		{
			changeskin ( id,1 );
		}

		he[id]=0;
		threwnapalm[id] = 0;
		carrioncount[id] = 2;
		shadowcount[id] = 2;
		flashg[id] = 0;
		ismole[id] = false;
		blessed[id] = false;
		CheckCloak[id] = true;
		BlockPickup[id] = false;
		//itemsrunning[id]=true
			
		spawnPointsused[id] = false;
		
		HookCount[id] = 0;
		RopeCount[id] = 0;
		GrabCount[id] = 0;
		IsVip[id] = 0;
		
		gateused[id]  = false;
		
	}

	freezecalled = 0;
	pheonixexistsT = 0;
	pheonixexistsCT = 0;
	return PLUGIN_CONTINUE;
}


public Target_Bombed ( )
{
	new players[32], numberofplayers, i, parm[1];
	get_players ( players, numberofplayers );

	for ( i = 0; i < numberofplayers; ++i )
	{
		parm[0] = players[i];
		set_task ( 0.1, "check_alive", 2, parm, 1 );
	}
}

public T_win ( )
{
	Event_Team_Win( TEAM_T );
}

public CT_win ( )
{
	Event_Team_Win( TEAM_CT );
}

public Event_Team_Win( TEAM )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new CTnum = count_CT ( );
	new Tnum = count_T ( );

	new a, players[32], sName[32], numberofplayers;

	if ( ( Tnum + CTnum ) < CVAR_PLERYS_FOX_XP )
	{
		return PLUGIN_HANDLED;
	}

	if ( Tnum > 0 && CTnum > 0 )
	{
		//nothing goes here???
	}
	else
	{
		return PLUGIN_HANDLED;
	}

	get_players ( players, numberofplayers );

	for ( a = 0; a < numberofplayers; ++a )
	{
		if ( get_user_team ( players[a] ) == TEAM )
		{
			new temp = ( ROUNDXP + xpgiven_lev[p_level[players[a]]] );

			if ( CVAR_OBJECTIVES )
			{
				get_user_name ( players[a],sName,31 );

				if( is_user_connected( players[a] ) && !is_user_bot( players[a] ) )
				{
					//client_print ( players[a], print_center, "%L", players[a], "WON_ROUND_XP", MOD, sName, temp );
					hudchat_show(players[a], "%L", players[a], "WON_ROUND_XP",  sName, temp);
					hudchat_update(players[a]);
				}
			}

			playerxp[players[a]] += temp;
			displaylevel ( players[a], 3 );
		}
	}

	return PLUGIN_CONTINUE;
}

public nade_thrown ( )
{
	new parm[2];
	parm[0] = read_data ( 1 );
	set_task ( 0.1, "hethrowevent", parm[0] );
	return PLUGIN_HANDLED;
}

public hethrowevent ( id )
{
	new szModel[64] , grenadeid = 0, rgb[3];
	grenadeid = get_grenade ( id );
	
	//[31-12-2010] - Check for valid map for grenade use
	if ( UWC3X_MapDisableCheck( "cgrenade.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "CGRENADE_SKILL_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	// [10-05-04] - Check for Valid grenade entity
	if ( !is_valid_ent ( grenadeid ) )
	{
		return PLUGIN_CONTINUE;
	}

	entity_get_string ( grenadeid, EV_SZ_model, szModel, 63 );

	if ( p_skills[id][SKILLIDX_CRITGREN] && p_skills[id][SKILLIDX_NAPALM] )
	{
		rgb = { 255, 32, 32 };
	}
	else if ( p_skills[id][SKILLIDX_CRITGREN] )
	{
		rgb = { 32, 255, 32 };
	}
	else if ( p_skills[id][SKILLIDX_NAPALM] )
	{
		rgb = { 32, 32, 255 };
	}

	if ( grenadeid && equal ( szModel, "models/w_hegrenade.mdl" ) )
	{
		if ( p_skills[id][SKILLIDX_CRITGREN] || p_skills[id][SKILLIDX_NAPALM] )
		{
			if ( ( playeritem2[id] == INFERNO && CVAR_GLOVE_ORC_DAMAGE ) || ( playeritem2[id] != INFERNO ) )
			{
				message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
				write_byte ( TE_BEAMFOLLOW );
				write_short ( grenadeid ); // entity
				write_short ( m_iTrail ); // model
				write_byte ( 20 );  // life
				write_byte ( 10 );  // width
				write_byte ( rgb[0] ); // r, g, b
				write_byte ( rgb[1] ); // r, g, b
				write_byte ( rgb[2] ); // r, g, b
				write_byte ( 210 ); // Brightness
				message_end ( ); // move PHS/PVS data sending here ( SEND_ALL,SEND_PVS,SEND_PHS )
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public Event_Planted_Bomb( id )
{
	// Bomb planted
	new origin[3],teamname[32], player[32], numplayers = 0, targetorigin[3], targetid, fC4Timer, temp = 0, sName[32];

	get_user_origin ( id, origin );
	get_user_team ( id, teamname, 31 );
	get_players ( player, numplayers );

	bombCarrier = 0;
	fC4Timer = get_cvar_num ( "mp_c4timer" );

	// Set BOMB_PLANTED state, bomb was planted
	bombstate = BOMB_PLANTED;

	// Used to help reincarnation after dying from bomb
	set_task ( fC4Timer - 1.0, "check_for_living", 645 + id );
	set_task ( float ( fC4Timer ) + 1.0, "check_for_living2", 645 + id );

	if ( CVAR_OBJECTIVES )
	{
		temp = 3 * xpgiven_lev[p_level[id]];
		playerxp[id] += temp;
		get_user_name ( id, sName, 31 );

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			//client_print ( id, print_center, "%L", id, "BOMB_PLANT_XP1", MOD, sName, temp );
			hudchat_show(id, "%L", id, "BOMB_PLANT_XP1",  sName, temp);
			hudchat_update(id);
		}
	}

	for ( new i = 0; i < numplayers; ++i )
	{
		targetid = player[i];

		if ( get_user_team ( targetid ) != TEAM_T )
			continue;

		get_user_origin ( targetid, targetorigin );

		// [09-27-04] Modified playerlist so now have to check for living status - K2mia
		if ( is_user_alive ( targetid ) && ( get_distance ( origin, targetorigin ) <= CVAR_XP_RADIUS ) )
		{
			if ( CVAR_OBJECTIVES )
			{
				temp = BOMBPLANTXP + xpgiven_lev[p_level[targetid]];
				playerxp[targetid] += temp;
				get_user_name ( targetid, sName, 31 );

				if( is_user_connected( targetid ) && !is_user_bot( targetid ) )
				{
					//client_print ( targetid, print_center, "%L", targetid, "BOMB_PLANT_XP2", MOD, sName, temp );
					hudchat_show(targetid, "%L", targetid, "BOMB_PLANT_XP2",  sName, temp);
					hudchat_update(targetid);
				}
			}
		}
	}

	displaylevel ( targetid, 1 );
}

public Event_Defused_Bomb( id )
{
	// Bomb defused
	new origin[3],teamname[32], player[32], numplayers = 0, targetorigin[3], targetid, temp = 0, sName[32], i;

	get_user_origin ( id, origin );
	get_user_team ( id, teamname, 31 );
	get_players ( player, numplayers );

	// Set BOMB_DEFUSED state, bomb was defused
	bombstate = BOMB_DEFUSED;

	if ( CVAR_OBJECTIVES )
	{
		temp = 3 * xpgiven_lev[p_level[id]];
		playerxp[id] += temp;
		get_user_name ( id, sName, 31 );

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			//client_print ( id, print_center, "%L", id, "BOMB_DEFUSE_XP1", MOD, sName, temp );
			hudchat_show(id, "%L", id, "BOMB_DEFUSE_XP1",  sName, temp, temp);
			hudchat_update(id);
		}
	}

	for ( i = 0; i < numplayers; ++i )
	{
		targetid = player[i];

		if ( get_user_team ( targetid ) != TEAM_CT )
		{
			continue;
		}

		get_user_origin ( targetid, targetorigin );

		// [09-27-04] Modified playerlist so now have to check for living status - K2mia
		if ( is_user_alive ( targetid ) && ( get_distance ( origin, targetorigin ) <= CVAR_XP_RADIUS ) )
		{
			if ( CVAR_OBJECTIVES )
			{
				temp = DEFUSEXP + xpgiven_lev[p_level[targetid]];
				playerxp[targetid] += temp;
				get_user_name ( targetid, sName, 31 );

				if( Util_Should_Msg_Client_Alive( id ) )
				{
					//client_print ( targetid, print_center, "%L", targetid, "BOMB_DEFUSE_XP2", MOD, sName, temp );
					hudchat_show(targetid, "%L", targetid, "BOMB_DEFUSE_XP2",  sName, temp);
					hudchat_update(targetid);
				}
			}
		}

		displaylevel ( targetid, 1 );
	}
}

public Event_Defuse_Try( id, Kit )
{
	// Bomb defusing with a kit
	if ( CVAR_ATTEMPTED_DEFUSE_BONUS )
	{
		if ( ( ++bombDefuserIndex[id] == 1 ) && ( get_user_team ( id ) == TEAM_CT ) )
		{
			if ( CVAR_OBJECTIVES )
			{
				new temp = 0, sName;
				if( Kit)
				{
					temp = ( 1/6 * DEFUSEXP ) + xpgiven_lev[p_level[id]];
					if( Util_Should_Msg_Client_Alive( id ) )
					{
						//client_print ( id, print_center, "%L", id, "BOMB_DEFUSE_XP3", MOD, sName, temp );
						hudchat_show(id, "%L", id, "BOMB_DEFUSE_XP3",  sName, temp );
						hudchat_update(id);
					}
				}
				else
				{
					temp = xpgiven_lev[p_level[id]];
					if( Util_Should_Msg_Client_Alive( id ) )
					{
						//client_print ( id, print_center, "%L", id, "BOMB_DEFUSE_XP4", MOD, id, temp );
						hudchat_show(id, "%L", id, "BOMB_DEFUSE_XP4",  id, temp);
						hudchat_update(id);
					}
				}
				playerxp[id] += temp;
			}
			displaylevel ( id, 1 );
		}
	}
}


public Event_Spawn_Bomb( id )
{
	// Spawned with the bomb
	if ( CVAR_BOMB_EVENT_BONUS )
	{
		if ( CVAR_OBJECTIVES )
		{
			new sName[32], temp = 0;
			get_user_name ( id, sName, 31 );
			temp = xpgiven_lev[p_level[id]];
			playerxp[id] += temp;

			if( Util_Should_Msg_Client_Alive( id ) )
			{
				//client_print ( id, print_center, "%L", id, "BOMB_SPAWN", MOD, sName, temp );
				hudchat_show(id, "%L", id, "BOMB_SPAWN", sName, temp);
				hudchat_update(id);
			}
		}
		displaylevel ( id, 1 );
	}
}
public Event_Bomb_Got( id, PickedUp )
{
	new sName[32], temp = xpgiven_lev[p_level[id]];

	if ( CVAR_BOMB_EVENT_BONUS )
	{
		if ( CVAR_OBJECTIVES )
		{
			get_user_name ( id, sName, 31 );

			if( PickedUp )
			{
				// Picked up the bomb
				if( Util_Should_Msg_Client_Alive( id ) )
				{
					//client_print ( id, print_center, "%L", id, "BOMB_PICKUP", MOD, sName, temp );
					hudchat_show(id, "%L", id, "BOMB_PICKUP", sName, temp);
					hudchat_update(id);
				}

				if( temp > 0 )
				{
					playerxp[id] += temp;
				}
			}
			else
			{
				// Dropped bomb
				if( Util_Should_Msg_Client_Alive( id ) )
				{
					//client_print ( id, print_center, "%L", id, "BOMB_DROP", MOD, sName, temp );
					hudchat_show(id, "%L", id, "BOMB_DROP", sName, temp);
					hudchat_update(id);
				}

				if( temp > 0 )
				{
					playerxp[id] -= temp;
				}
			}
		}
	}

	displaylevel ( id, 1 );
}

public Event_Hostage( id, Touched, Rescued, Killed )
{
	new temp = 0, sName[32];
	get_user_name( id, sName, 31 );

	if( Killed && CVAR_HOSTAGE_KILL_XP_LOSS && CVAR_OBJECTIVES )
	{
		// Hostage killed
		temp = xpgiven_lev[p_level[id]];

		if( Util_Should_Msg_Client_Alive( id ))
		{
			//client_print ( id, print_center, "%L", id, "HOSTAGE_KILL", MOD,sName, ( temp ) );
			hudchat_show(id, "%L", id, "HOSTAGE_KILL",sName, ( temp ));
			hudchat_update(id);
		}
	}
	else if( Touched && CVAR_HOSTAGE_TOUCH_BONUS && CVAR_OBJECTIVES )
	{
		// Hostage touched
		temp = xpgiven_lev[p_level[id]];

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			//client_print ( id, print_center, "%L", id, "HOSTAGE_TOUCH", MOD, sName, temp );
			hudchat_show(id, "%L", id, "HOSTAGE_TOUCH", sName, temp);
			hudchat_update(id);
		}
	}
	else if( Rescued && CVAR_OBJECTIVES )
	{
		// Hostage rescued
		new origin[3], teamname[32], player[32], numplayers, targetorigin[3], targetid;
		get_user_origin ( id, origin );
		get_user_team ( id, teamname, 31 );
		get_players ( player, numplayers );
		temp = 1 * xpgiven_lev[p_level[id]];

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			//client_print ( id, print_center, "%L", id, "HOSTAGE_RESCUE1", MOD, sName, temp );
			hudchat_show(id, "%L", id, "HOSTAGE_RESCUE1", sName, temp);
			hudchat_update(id);
		}

		// Supporters and self
		for ( new i=0; i<numplayers; ++i )
		{
			new temp2 = 0;
			targetid = player[i];

			//Only give CTs XP for hostie recues
			if ( get_user_team ( targetid ) != TEAM_CT )
			{
				continue;
			}

			get_user_origin ( targetid, targetorigin );

			// [09-27-04] Modified playerlist so now have to check for living status - K2mia
			// modified this to no longer have the objectives clausal since its higher up now due to multiple checks
			if ( is_user_alive ( targetid ) && ( get_distance ( origin, targetorigin ) <= CVAR_XP_RADIUS ) )
			{
				temp2 = HOSTAGEXP + xpgiven_lev[p_level[targetid]];
				playerxp[targetid] += temp2;
				get_user_name ( targetid, sName, 31 );

				if( Util_Should_Msg_Client_Alive( id ) )
				{
					//client_print ( targetid, print_center, "%L", targetid, "HOSTAGE_RESCUE2", MOD, sName, temp );
					hudchat_show(targetid, "%L", targetid, "HOSTAGE_RESCUE2", sName, temp);
					hudchat_update(targetid);
				}
			}

			//moved this to inside the enumeration since targetid is being assigned here
			displaylevel ( targetid, 1 );
		}
	}

	if( temp > 0 )
	{
		if( Killed )
		{
			playerxp[id] -= temp;
		}
		else
		{
			playerxp[id] += temp;
		}

		displaylevel ( id, 1 );
	}

}

public Event_VIP ( id, Spawned, Escaped, Killed )
{
	new sName[32], sNameVIP[MAX_NAME_LENGTH], temp = 0;

	if( Killed )
	{
		get_user_name ( vipID, sNameVIP, MAX_NAME_LENGTH );

		// VIP assassinated
		if ( CVAR_VIP_KILL_XP_BONUS )
		{
			temp = VIP_KILL_BONUS + xpgiven_lev[p_level[id]];
			if( Util_Should_Msg_Client_Alive( id ) )
			{
				//client_print ( id, print_center, "%L", id, "VIP_KILL", MOD, sName, temp, sNameVIP );
				hudchat_show(id, "%L", id, "VIP_KILL", sName, temp, sNameVIP);
				hudchat_update(id);
			}
		}
	}
	else if( Spawned )
	{
		vipID = id;
		IsVip[id] = 1;

		// VIP spawn
		if ( CVAR_VIP_SPAWN_BONUS )
		{
			temp = xpgiven_lev[p_level[id]];
			if( Util_Should_Msg_Client_Alive( id ) )
			{
				//client_print ( id, print_center, "%L", id, "VIP_SPAWN", MOD, sName, temp );
				hudchat_show(id, "%L", id, "VIP_SPAWN",  sName, temp);
				hudchat_update(id);
			}
		}
	}
	else if( Escaped )
	{
		// VIP escaped
		new origin[3], teamname[32], player[32], numplayers, targetorigin[3], targetid, nName[31];
		get_user_origin ( id, origin );
		get_user_team ( id, teamname, 31 );
		get_players ( player, numplayers );
		get_user_name( id, sName, 31 );
		temp = xpgiven_lev[p_level[id]] ;

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			//client_print ( id, print_center, "%L", id, "VIP_ESCAPE1", MOD, sName, temp );
			hudchat_show(id, "%L", id, "VIP_ESCAPE1",  sName, temp);
			hudchat_update(id);
		}

		for ( new i = 0; i < numplayers; ++i )
		{
			targetid = player[i];

			if ( get_user_team ( targetid ) != TEAM_CT )
			{
				continue;
			}

			get_user_origin ( targetid, targetorigin );

			// [09-27-04] Added check for alive status of player - K2mia
			if ( is_user_alive ( targetid ) && ( get_distance ( origin, targetorigin ) <= CVAR_XP_RADIUS ) && ( targetid != id ) )
			{
				temp = VIP_ESCAPE_BONUS + xpgiven_lev[p_level[targetid]];
				get_user_name ( targetid, nName, 31 );
				playerxp[id] += temp;

				if( Util_Should_Msg_Client_Alive( targetid ) )
				{
					//client_print ( targetid, print_center, "%L", targetid, "VIP_ESCAPE2", MOD, nName, temp, sName );
					hudchat_show(targetid, "%L", targetid, "VIP_ESCAPE2",  nName, temp, sName);
					hudchat_update(targetid);
				}
			}

			displaylevel ( targetid, 1 );
		}
	}

	if( temp > 0 )
	{
		playerxp[id] += temp;
		displaylevel ( id, 1 );
	}
}


/* main function that calls suporting functions above */
public event_player_action ( )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new sArg[MAX_VAR_LENGTH], sAction[MAX_VAR_LENGTH], sName[MAX_NAME_LENGTH], id, iUserId;
	new CTnum = count_CT ( );
	new Tnum = count_T ( );

	if ( ( Tnum + CTnum ) < CVAR_PLERYS_FOX_XP )
	{
		return PLUGIN_HANDLED;
	}

	//reversed and took out an empty clausal
	if ( Tnum < 0 && CTnum < 0 )
	{
		return PLUGIN_HANDLED;
	}

	read_logargv ( 0, sArg, MAX_VAR_LENGTH );
	read_logargv ( 2, sAction, MAX_VAR_LENGTH );
	parse_loguser ( sArg, sName, MAX_NAME_LENGTH, iUserId );
	id = find_player ( "k", iUserId );

	// Prevents the server from gaining XP
	if ( id == 0 )
	{
		return PLUGIN_CONTINUE;
	}

	if ( equal ( sAction, "Planted_The_Bomb" ) )
	{
		Event_Planted_Bomb( id );
	}
	else if ( equal ( sAction, "Defused_The_Bomb" ) )
	{
		Event_Defused_Bomb( id );
	}
	else if ( equal ( sAction, "Begin_Bomb_Defuse_With_Kit" ) )
	{
		Event_Defuse_Try( id, true);
	}
	else if ( equal ( sAction, "Begin_Bomb_Defuse_Without_Kit" ) )
	{
		Event_Defuse_Try( id, false);
	}
	else if ( equal ( sAction, "Spawned_With_The_Bomb" ) )
	{
		Event_Spawn_Bomb( id );
	}
	else if ( equal ( sAction, "Dropped_The_Bomb" ) )
	{
		Event_Bomb_Got( id, false );
	}
	else if ( equal ( sAction, "Got_The_Bomb" ) )
	{
		Event_Bomb_Got( id, true );
	}
	else if ( equal ( sAction, "Touched_A_Hostage" ) )
	{
		Event_Hostage( id, true, false, false );
	}
	else if ( equal ( sAction, "Rescued_A_Hostage" ) )
	{
		Event_Hostage( id, false, true, false );
	}
	else if ( equal ( sAction, "Killed_A_Hostage" ) )
	{
		Event_Hostage( id, false, false, true );
	}
	else if ( equal ( sAction, "Became_VIP" ) )
	{
		Event_VIP ( id, true, false, false );
	}
	else if ( equal ( sAction, "Assassinated_The_VIP" ) )
	{
		Event_VIP ( id, false, false, true );
	}
	else if ( equal ( sAction, "Escaped_As_VIP" ) )
	{
		Event_VIP ( id, false, true, false );
	}

	return PLUGIN_HANDLED;
}
public Event_Mine_createKill(id, attacker, weaponDescription[] )
{
	new FFon = get_cvar_num("mp_friendlyfire");

	if (FFon && Util_IsSame_Team ( id, attacker ) )
	{
		set_user_frags(attacker, get_user_frags(attacker) - 1);

		if( Util_Should_Msg_Client_Alive( attacker ) )
		{
			client_print(attacker,print_center,"You killed a teammate");
		}

		new money = cs_get_user_money(attacker);

		if (money != 0)
			cs_set_user_money(attacker,money - 150,1);

	}
	else if (Util_NotSame_Team ( id, attacker ) )
	{
		set_user_frags(attacker, get_user_frags(attacker) + 1);
		new money = cs_get_user_money(attacker);

		if (money < 16000)
			cs_set_user_money(attacker,money + 300,1);
	}

	Event_Log_logKill( attacker, id, weaponDescription );

	//Kill the victim and block the messages
	set_msg_block(gmsgDeathMsg,BLOCK_ONCE);
	set_msg_block(gmsgScoreInfo,BLOCK_ONCE);

	if( Util_Is_Valid_Player( id ) && is_user_alive( id ) )
	{
		user_kill(id);
		//user_kill removes a frag, this gives it back
		set_user_frags(id,get_user_frags(id) + 1);
	}

	message_begin( MSG_ALL, gmsgDeathMsg,{0,0,0},0) 
	write_byte(attacker) 
	write_byte(id) 
	write_byte(0) 
	write_string(weaponDescription) 
	message_end() 
	
	message_begin(MSG_ALL,gmsgScoreInfo) 
	write_byte(attacker) 
	write_short(get_user_frags(attacker)) 
	write_short(get_user_deaths(attacker)) 
	write_short(0) 
	write_short(get_user_team(attacker)) 
	message_end() 
	
	message_begin(MSG_ALL,gmsgScoreInfo) 
	write_byte(id) 
	write_short(get_user_frags(id)) 
	write_short(get_user_deaths(id)) 
	write_short(0) 
	write_short(get_user_team(id)) 
	message_end() 

}

public Event_Jumpkick_createKill(id, attacker, weaponDescription[] )
{
	new FFon = get_cvar_num("mp_friendlyfire");

	if (FFon && Util_IsSame_Team ( id, attacker ) )
	{
		set_user_frags(attacker, get_user_frags(attacker) - 1);

		if( Util_Should_Msg_Client_Alive( attacker ) )
		{
			client_print(attacker,print_center,"You killed a teammate");
		}

		new money = cs_get_user_money(attacker);

		if (money != 0)
			cs_set_user_money(attacker,money - 150,1);

	}
	else if (Util_NotSame_Team ( id, attacker ) )
	{
		set_user_frags(attacker, get_user_frags(attacker) + 1);
		new money = cs_get_user_money(attacker);

		if (money < 16000)
			cs_set_user_money(attacker,money + 300,1);

	}

	Event_Log_logKill( attacker, id, weaponDescription );

	//Kill the victim and block the messages
	set_msg_block(gmsgDeathMsg,BLOCK_ONCE);
	set_msg_block(gmsgScoreInfo,BLOCK_ONCE);

	if( Util_Is_Valid_Player( id ) && is_user_alive( id ) )
	{
		user_kill(id);
		//user_kill removes a frag, this gives it back
		set_user_frags(id,get_user_frags(id) + 1);
	}

	//Replaced HUD death message
	message_begin(MSG_ALL,gmsgDeathMsg,{0,0,0},0);
	write_byte(attacker);
	write_byte(id);
	write_byte(0);
	write_string(weaponDescription);
	message_end();

	//Update killers scorboard with new info
	message_begin(MSG_ALL,gmsgScoreInfo);
	write_byte(attacker);
	write_short(get_user_frags(attacker));
	write_short(get_user_deaths(attacker));
	write_short(0);
	write_short(get_user_team(attacker));
	message_end();

	//Update victims scoreboard with correct info
	message_begin(MSG_ALL,gmsgScoreInfo);
	write_byte(id);
	write_short(get_user_frags(id));
	write_short(get_user_deaths(id));
	write_short(0);
	write_short(get_user_team(id));
	message_end();

}

public client_AddToFullPack(ent_state,e,edict_t_ent,edict_t_host,hostflags,player,pSet) 
{
	//No players need this rather cpu consuming function - dont run
	if (!use_addtofullpack)
		return FMRES_HANDLED
		
	if (!pev_valid(e)|| !pev_valid(edict_t_ent) || !pev_valid(edict_t_host))
		return FMRES_HANDLED
			
	new classname[32]
	pev(e,pev_classname,classname,31)
	
	new hostclassname[32]
	pev(edict_t_host,pev_classname,hostclassname,31)
			
	//Hide mines from enemies
	if (equal(classname,"Mine") && !player && equal(hostclassname,"player"))
	{
		new owner = pev(e,pev_owner)	
		//Hide for enemies
		if (get_user_team(owner) != get_user_team(edict_t_host))
			set_rendering(e,kRenderFxNone, 0,0,0, kRenderTransTexture,60)	
	}
	return FMRES_HANDLED
}

public Explode_Origin(id,Float:origin[3],damage,dist)
{
	message_begin(MSG_BROADCAST, SVC_TEMPENTITY)
	write_byte(3)
	write_coord(floatround(origin[0]))
	write_coord(floatround(origin[1]))
	write_coord(floatround(origin[2]))
	write_short(g_sModelIndexFireball)
	write_byte(50)
	write_byte(15)
	write_byte(0)
	message_end()
	
	new Players[32], playerCount, a
	get_players(Players, playerCount, "ah") 
	
	for (new i=0; i<playerCount; i++) 
	{
		a = Players[i] 
		
		new Float:aOrigin[3]
		pev(a,pev_origin,aOrigin)
				
		if (get_user_team(id) != get_user_team(a) && get_distance_f(aOrigin,origin) < dist+0.0)
		{
			do_damage(a, id, damage, 31, 3, 0,0,0);

			//new dam = damage-player_dextery[a]*2
			//if (get_user_health(a)-damage < 5)
			//	UTIL_Kill(id,a,"grenade")
			//else
			//{
			//	set_user_health(a,get_user_health(a)-damage)
			//	//Effect_Bleed(a,248)
			//}
		}
	}
}

public Mine_Think(ent)
{
	if (endround || freezetime || u_delay)
		remove_entity(ent)
	else
		entity_set_float(ent,EV_FL_nextthink,halflife_time() + 1.0) 
}

public fw_setmodel(ent,model[])
{

	if( !is_valid_ent(ent) )
		return FMRES_IGNORED;

	// not a smoke grenade
	if(!equali(model,"models/w_smokegrenade.mdl"))
		return FMRES_IGNORED;

	// not yet thrown
	if(entity_get_float(ent,EV_FL_gravity) == 0.0)
	{
		return FMRES_IGNORED;
	}

	new owner = entity_get_edict(ent,EV_ENT_owner);

	if( p_skills[owner][SKILLIDX_ICENADE] )
	{
		//Check for frost nade
		CheckFrostNades( owner );

		if( !hasFrostNade[owner] )
		{
			return FMRES_IGNORED;
		}
	}
	else
	{
		return FMRES_IGNORED;
	}


	// store team in the grenade
	entity_set_int(ent,EV_INT_team,get_user_team(owner));

	// hide icon
	if( hasFrostNade[owner] )
	{
		hasFrostNade[owner] = 0;
		if( Util_Should_Msg_Client( owner ) )
		{
			message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},owner);
			write_byte(0); // status (0=hide, 1=show, 2=flash)
			write_string("dmg_cold"); // sprite name
			write_byte(FROST_R); // red
			write_byte(FROST_G); // green
			write_byte(FROST_B); // blue
			message_end();
		}
	}

	// give it a blue glow and a blue trail
	set_rendering(ent,kRenderFxGlowShell,FROST_R,FROST_G,FROST_B);
	set_beamfollow(ent,10,10,FROST_R,FROST_G,FROST_B,100);

	// hack? flag to remember to track this grenade's think
	entity_set_int(ent,EV_INT_bInDuck,1);

	// track for when it will explode
	set_task(1.6,"grenade_explode",ent);
	//grenade_explode(ent);

	return FMRES_IGNORED;
}

// think, grenade. think, damnit!
public think_grenade(ent)
{
	if( !is_valid_ent(ent))
		return PLUGIN_CONTINUE;

	// hack? not a smoke grenade, or at least not a popular one
	if( !entity_get_int(ent,EV_INT_bInDuck) )
		return PLUGIN_CONTINUE;

	// stop it from exploding
	return PLUGIN_HANDLED;
}

// and boom goes the dynamite
public grenade_explode(ent)
{
	if( !is_valid_ent(ent))
	{
		return;
	}

	// make the smoke
	new origin[3], Float:originF[3];
	entity_get_vector(ent,EV_VEC_origin,originF);
	FVecIVec(originF,origin);

	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(5); // TE_SMOKE
	write_coord(origin[0]); // x
	write_coord(origin[1]); // y
	write_coord(origin[2]); // z
	write_short(g_sModelIndexSmoke); // sprite
	write_byte(random_num(35,45)); // scale
	write_byte(5); // framerate
	message_end();

	// debug
	//show_xyz(origin,floatround(FROST_RADIUS));

	// get grenade's owner
	new owner = entity_get_edict(ent,EV_ENT_owner);

	//Set skill level vars
	new tempSkillLevel 	= p_skills[owner][SKILLIDX_ICENADE];
	new Float:tempRadius= tempSkillLevel * FROST_RADIUS;
	new tmpMaxDamage 	= tempSkillLevel * FROST_MAX_DAMAGE;
	new tmpMinDamage 	= tempSkillLevel * FROST_MIN_DAMAGE;

	// explosion
	create_blast(origin, floatround(tempRadius));
	emit_sound(ent,CHAN_WEAPON,"uwc3x/frostnova.wav",1.0,ATTN_NORM,0,PITCH_NORM);

	new players[32], targetorigin[3], numberofplayers, i, player, distancebetween;
	get_players ( players, numberofplayers );
	for ( i = 0; i < numberofplayers; ++i )
	{
		player = players[i];

		if( !Util_Is_Valid_Player( player ) || !is_user_alive ( player ) )
			continue;

		//Skip team mates if FF is not on
		if( ( get_cvar_num("mp_friendlyfire") == 0) && Util_IsSame_Team( player, owner ) )
			continue;
			
		new idname[32], ename[32];
		get_user_name( player, idname, 31 );
		get_user_name( owner, ename, 31 );

		get_user_origin ( player, targetorigin );
		distancebetween = get_distance ( origin, targetorigin );
		new wasFrozen;
		new Float:playerOrigin[3];
		entity_get_vector(player,EV_VEC_origin,playerOrigin);

		if ( distancebetween < tempRadius && Util_NotSame_Team ( owner, player ) )
		{
			new Float:chillChance = radius_calucation(playerOrigin,originF, tempRadius,FROST_CHILLCHANCE_MAX,FROST_CHILLCHANCE_MIN);
			new Float:freezeChance = radius_calucation(playerOrigin,originF,tempRadius,FROST_FREEZECHANCE_MAX,FROST_FREEZECHANCE_MIN);

			// deal damage
			if( tmpMaxDamage > 0.0)
			{
				new Float:damage = radius_calucation(playerOrigin,originF,tempRadius,float(tmpMaxDamage),float(tmpMinDamage) );

				// half damage for friendlyfire
				if ( Util_IsSame_Team( player, owner ) || temp_immunity[player] || Util_IsPlayer_Immune ( player, 8 ) )
				{
				
					if( !Util_IsSame_Team( player, owner ) )
					{
						//They resistted
						temp_immunity[player] = true;
						
						if( Util_Should_Msg_Client_Alive( player ) )
						{
							//client_print ( player, print_center, "%L", player, "ULTIMATE_ICEBOMB_RESIST2", idname );
							hudchat_show(player, "%L", player, "ULTIMATE_ICEBOMB_RESIST2", idname);
							hudchat_update(player);
						}
						
						if( Util_Should_Msg_Client_Alive( owner ) )
						{
							//client_print ( owner, print_center, "%L", owner, "ULTIMATE_ICEBOMB_RESIST4", ename );
							hudchat_show(owner, "%L", owner, "ULTIMATE_ICEBOMB_RESIST4", ename);
							hudchat_update(owner);
						}
						
						new iparm[2];
						iparm[0] = player;
						copy( iparm[1], 31, "Ice Bomb" );
						set_task ( 1.5, "Task_Reset_Immunity", TASK_RESET_IMMUNITY + player, iparm, 2 );
					}
					else
					{
						//They did not resist, its same team, but still gets half damage for FF
					}

					damage *= 0.5;
				}

				//do damage
				do_damage ( player, owner, floatround(damage), 29, 2, 0, 0, 0 );
			}	
				
			// check for freeze
			if(random_num(1,100) <= floatround(freezeChance) && !isFrozen[player])
			{
				wasFrozen = 1;
				freeze_player(player);
				isFrozen[player] = 1;

				emit_sound(player,CHAN_BODY,"uwc3x/impale_hit.wav",1.0,ATTN_NORM,0,PITCH_HIGH);
				set_task( 4.0,"remove_freeze", TASK_REMOVE_FREEZE +player );

				// if they don't already have a frostnova
				if(!is_valid_ent(novaDisplay[player]))
				{
					// create the entity
					new nova = create_entity("info_target");

					// give it a size
					new Float:maxs[3], Float:mins[3];
					maxs = Float:{ 8.0, 8.0, 4.0 };
					mins = Float:{ -8.0, -8.0, -4.0 };
					entity_set_size(nova,mins,maxs);

					// random orientation
					new Float:angles[3];
					angles[1] = float(random_num(0,359));
					entity_set_vector(nova,EV_VEC_angles,angles);

					// put it at their feet
					new Float:playerMins[3], Float:novaOrigin[3];
					entity_get_vector(player,EV_VEC_mins,playerMins);
					entity_get_vector(player,EV_VEC_origin,novaOrigin);
					novaOrigin[2] += playerMins[2];
					entity_set_vector(nova,EV_VEC_origin,novaOrigin);

					// mess with the model
					entity_set_model(nova,"models/frostnova.mdl");
					entity_set_float(nova,EV_FL_animtime,1.0)
					entity_set_float(nova,EV_FL_framerate,1.0)
					entity_set_int(nova,EV_INT_sequence,0);
					set_rendering(nova,kRenderFxNone,FROST_R,FROST_G,FROST_B,kRenderTransColor,100);

					// remember this
					novaDisplay[player] = nova;
				}
			}

			// check for chill
			if(random_num(1,100) <= floatround(chillChance) && !isChilled[player])
			{
				chill_player(player);
				isChilled[player] = 1;

				// don't play sound if player just got frozen,
				// reason being it will be overriden and I like the other sound better
				if(!wasFrozen)
					emit_sound(player,CHAN_BODY,"player/pl_duct2.wav",1.0,ATTN_NORM,0,PITCH_LOW);

				set_task( 5.5 ,"remove_chill", TASK_REMOVE_CHILL+player );
			}
		}

		// get rid of the old grenade
		remove_entity(ent);
	}
}