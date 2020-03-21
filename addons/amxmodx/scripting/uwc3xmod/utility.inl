//
// XP Functions
//

bool:Util_Is_Valid_Player( id )
{
	if( id < 1 || id > MAX_PLAYERS )
	{
		return false;
	}

	if( !is_user_connected( id ) || !pev_valid( id ) )
	{
		return false;
	}

	if ( pev( id, pev_flags ) & FL_CLIENT )
	{
		return true;
	}

	return false;
}

bool:Util_Should_Msg_Client( id )
{
	if( Util_Is_Valid_Player(id) && !is_user_bot( id ) )
	{
		return true;
	}

	return false;
}

bool:Util_Should_Msg_Client_Alive( id )
{
	if( Util_Should_Msg_Client( id ) && is_user_alive( id ) )
	{
		return true;
	}

	return false;
}

bool:Util_Should_Msg_Client_Dead( id )
{
	if( Util_Should_Msg_Client( id ) && !is_user_alive( id ) )
	{
		return true;
	}

	return false;
}

bool:Util_IsValid_Team ( PlayerID )
{
	new bool:IsValidTeam = false;

	if ( ( get_user_team ( PlayerID ) == TEAM_CT || get_user_team ( PlayerID ) == TEAM_T ) && !Util_Player_Is_Spec( PlayerID) )
	{
		IsValidTeam = true;
	}

	return IsValidTeam;
}

bool:Util_IsSame_Team ( PlayerID, TargetID )
{
	new bool:IsValidTeam = false;

	if ( get_user_team ( PlayerID ) == get_user_team ( TargetID ) && Util_IsValid_Team ( PlayerID ) && Util_IsValid_Team ( TargetID ) )
	{
		IsValidTeam = true;
	}

	return IsValidTeam;
}

bool:Util_NotSame_Team ( PlayerID, TargetID )
{
	new bool:IsValidTeam = false;

	if ( get_user_team ( PlayerID ) != get_user_team ( TargetID ) && Util_IsValid_Team ( PlayerID ) && Util_IsValid_Team ( TargetID ) )
	{
		IsValidTeam = true;
	}

	return IsValidTeam;
}


bool:Util_Player_Is_Spec ( PlayerID )
{
	new bool:IsSpec = false;

	if ( get_user_team ( PlayerID ) == SPEC )
	{
		IsSpec = true;
	}

	return IsSpec;
}

bool:Util_IsPlayer_Immune ( id , iItem )
{
	new bool:IsImmune = false;

	/*
	1=blink
	2=magic
	3-poison
	4=disease
	5=fire
	6=lightning
	7=rot
	8=ice
	*/

	switch( iItem)
	{
		case 1:
			if ( playeritem[id] == IMMUNITY || hasblink[id] )
			{
				IsImmune = true;
			}
		case 2:
			if ( magic_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 3:
			if ( poison_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 4:
			if ( disease_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 5:
			if ( fire_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 6:
			if ( electricity_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 7:
			if ( rot_saving_throw ( id ) )
			{
				IsImmune = true;
			}
		case 8:
			if ( ice_saving_throw ( id ) )
			{
				IsImmune = true;
			}
	}

	return IsImmune;
}

public PreCache_Sounds ( )
{
	precache_sound ( "ambience/particle_suck1.wav" );
	precache_sound ( "turret/tu_ping.wav" );
	precache_sound ( "weapons/cbar_hitbod3.wav" );
	precache_sound ( "ambience/thunder_clap.wav" );
	precache_sound ( "ambience/flameburst1.wav" );
	precache_sound ( "scientist/scream07.wav" );
	precache_sound ( "buttons/button10.wav" );
	precache_sound ( "fans/fan5.wav" );
	precache_sound ( "items/medshot5.wav" );
	precache_sound ( "items/suitchargeok1.wav" );
	precache_sound ( "player/pl_duct2.wav" );
	precache_sound ( "weapons/electro5.wav" );
	precache_sound ( "weapons/cbar_hitbod3.wav" );

	// sounds that can be replaced by others
	if (file_exists("sound/uwc3x/levelupcaster.wav"))
	{
		precache_sound("uwc3x/levelupcaster.wav");
	}
	else
	{
		precache_sound("plats/elevbell1.wav");
	}

	if (file_exists("sound/uwc3x/lightningbolt.wav"))
	{
		precache_sound("uwc3x/lightningbolt.wav");
	}
	else
	{
		precache_sound("weapons/gauss2.wav");
	}

	if (file_exists("sound/uwc3x/massteleporttarget.wav"))
	{
		precache_sound("uwc3x/massteleporttarget.wav");
	}
	else
	{
		precache_sound("x/x_shoot1.wav");
	}

	if (file_exists("sound/uwc3x/blinkarrival.wav"))
	{
		precache_sound("uwc3x/blinkarrival.wav");
	}
	else
	{
		precache_sound("x/x_shoot1.wav");
	}

	// rest
	if (file_exists("sound/uwc3x/antend.wav"))
	{
		precache_sound("uwc3x/antend.wav");
	}
	
	if (file_exists("sound/uwc3x/banishcaster.wav"))
	{
		precache_sound("uwc3x/banishcaster.wav");
	}
	
	if (file_exists("sound/uwc3x/bless.wav"))
	{
		precache_sound("uwc3x/bless.wav");
	}
	
	if (file_exists("sound/uwc3x/bond.wav"))
	{
		precache_sound("uwc3x/bond.wav");
	}
	
	if (file_exists("sound/uwc3x/carrionswarmdamage.wav"))
	{
		precache_sound("uwc3x/carrionswarmdamage.wav");
	}
	
	if (file_exists("sound/uwc3x/carrionswarmdamage1.wav"))
	{
		precache_sound("uwc3x/carrionswarmdamage1.wav");
	}
	
	if (file_exists("sound/uwc3x/carrionswarmlaunch.wav"))
	{
		precache_sound("uwc3x/carrionswarmlaunch.wav");
	}
	
	if (file_exists("sound/uwc3x/carrionswarmlaunch1.wav"))
	{
		precache_sound("uwc3x/carrionswarmlaunch1.wav");
	}
	
	if (file_exists("sound/uwc3x/critical_strike.wav"))
	{
		precache_sound("uwc3x/critical_strike.wav");
	}
	
	if (file_exists("sound/uwc3x/dehex.wav"))
	{
		precache_sound("uwc3x/dehex.wav");
	}
	
	if (file_exists("sound/uwc3x/depowered.wav"))
	{
		precache_sound("uwc3x/depowered.wav");
	}
	
	if (file_exists("sound/uwc3x/disorient-casted.wav"))
	{
		precache_sound("uwc3x/disorient-casted.wav");
	}
	
	if (file_exists("sound/uwc3x/disoriented.wav"))
	{
		precache_sound("uwc3x/disoriented.wav");
	}
	
	if (file_exists("sound/uwc3x/dispell_hex.wav"))
	{
		precache_sound("uwc3x/dispell_hex.wav");
	}
	
	if (file_exists("sound/uwc3x/divineshield.wav"))
	{
		precache_sound("uwc3x/divineshield.wav");
	}
	
	if (file_exists("sound/uwc3x/dohgodoh.wav"))
	{
		precache_sound("uwc3x/dohgodoh.wav");
	}
	
	if (file_exists("sound/uwc3x/earthquake_hit.wav"))
	{
		precache_sound("uwc3x/earthquake_hit.wav");
	}
	
	if (file_exists("sound/uwc3x/earthquake_launch.wav"))
	{
		precache_sound("uwc3x/earthquake_launch.wav");
	}
	
	if (file_exists("sound/uwc3x/entanglingroots.wav"))
	{
		precache_sound("uwc3x/entanglingroots.wav");
	}
	
	if (file_exists("sound/uwc3x/entanglingrootstarget1.wav"))
	{
		precache_sound("uwc3x/entanglingrootstarget1.wav");
	}
	
	if (file_exists("sound/uwc3x/error.wav"))
	{
		precache_sound("uwc3x/error.wav");
	}
	
	if (file_exists("sound/uwc3x/fatal_strike.wav"))
	{
		precache_sound("uwc3x/fatal_strike.wav");
	}
	
	if (file_exists("sound/uwc3x/flamestrike.wav"))
	{
		precache_sound("uwc3x/flamestrike.wav");
	}
	
	if (file_exists("sound/uwc3x/flamestriketargetwavenonloop1.wav"))
	{
		precache_sound("uwc3x/flamestriketargetwavenonloop1.wav");
	}
	
	if (file_exists("sound/uwc3x/frostnova.wav"))
	{
		precache_sound("uwc3x/frostnova.wav");
	}
	
	if (file_exists("sound/uwc3x/helmsplitter.wav"))
	{
		precache_sound("uwc3x/helmsplitter.wav");
	}
	
	if (file_exists("sound/uwc3x/helmsplitter2.wav"))
	{
		precache_sound("uwc3x/helmsplitter2.wav");
	}
	
	if (file_exists("sound/uwc3x/hex_infect.wav"))
	{
		precache_sound("uwc3x/hex_infect.wav");
	}
	
	if (file_exists("sound/uwc3x/impalehit.wav"))
	{
		precache_sound("uwc3x/impalehit.wav");
	}
	
	if (file_exists("sound/uwc3x/impalelaunch1.wav"))
	{
		precache_sound("uwc3x/impalelaunch1.wav");
	}
	
	if (file_exists("sound/uwc3x/impale_hit.wav"))
	{
		precache_sound("uwc3x/impale_hit.wav");
	}
	
	if (file_exists("sound/uwc3x/impale_launch.wav"))
	{
		precache_sound("uwc3x/impale_launch.wav");
	}
	
	if (file_exists("sound/uwc3x/infect_hex.wav"))
	{
		precache_sound("uwc3x/infect_hex.wav");
	}
	
	if (file_exists("sound/uwc3x/invul.wav"))
	{
		precache_sound("uwc3x/invul.wav");
	}
	
	if (file_exists("sound/uwc3x/levelup.wav"))
	{
		precache_sound("uwc3x/levelup.wav");
	}
	
	if (file_exists("sound/uwc3x/locustswarmloop.wav"))
	{
		precache_sound("uwc3x/locustswarmloop.wav");
	}
	
	if (file_exists("sound/uwc3x/meanswar.wav"))
	{
		precache_sound("uwc3x/meanswar.wav");
	}
	
	if (file_exists("sound/uwc3x/ninja-vanish.wav"))
	{
		precache_sound("uwc3x/ninja-vanish.wav");
	}
	
	if (file_exists("sound/uwc3x/ninja.wav"))
	{
		precache_sound("uwc3x/ninja.wav");
	}
	
	if (file_exists("sound/uwc3x/pickupitem.wav"))
	{
		precache_sound("uwc3x/pickupitem.wav");
	}
	
	if (file_exists("sound/uwc3x/potion.wav"))
	{
		precache_sound("uwc3x/potion.wav");
	}
	
	if (file_exists("sound/uwc3x/reincarnation.wav"))
	{
		precache_sound("uwc3x/reincarnation.wav");
	}
	
	if (file_exists("sound/uwc3x/rot_hit.wav"))
	{
		precache_sound("uwc3x/rot_hit.wav");
	}
	
	if (file_exists("sound/uwc3x/rot_launch.wav"))
	{
		precache_sound("uwc3x/rot_launch.wav");
	}
	
	if (file_exists("sound/uwc3x/shadowstrikebirth.wav"))
	{
		precache_sound("uwc3x/shadowstrikebirth.wav");
	}
	
	if (file_exists("sound/uwc3x/shadowstrikebirth1.wav"))
	{
		precache_sound("uwc3x/shadowstrikebirth1.wav");
	}
	
	if (file_exists("sound/uwc3x/shadowstrikemissile.wav"))
	{
		precache_sound("uwc3x/shadowstrikemissile.wav");
	}
	
	if (file_exists("sound/uwc3x/shadowstrikemissile1.wav"))
	{
		precache_sound("uwc3x/shadowstrikemissile1.wav");
	}
	
	if (file_exists("sound/uwc3x/shield.wav"))
	{
		precache_sound("uwc3x/shield.wav");
	}
	
	if (file_exists("sound/uwc3x/sm3_cure.wav"))
	{
		precache_sound("uwc3x/sm3_cure.wav");
	}
	
	if (file_exists("sound/uwc3x/smokin.wav"))
	{
		precache_sound("uwc3x/smokin.wav");
	}
	
	if (file_exists("sound/uwc3x/suicide_charging.wav"))
	{
		precache_sound("uwc3x/suicide_charging.wav");
	}
	
	if (file_exists("sound/uwc3x/teleport.wav"))
	{
		precache_sound("uwc3x/teleport.wav");
	}
	
	if (file_exists("sound/uwc3x/tomes.wav"))
	{
		precache_sound("uwc3x/tomes.wav");
	}
	
	if (file_exists("sound/uwc3x/ultimateerror.wav"))
	{
		precache_sound("uwc3x/ultimateerror.wav");
	}
	
	if (file_exists("sound/uwc3x/ultimate_stopped.wav"))
	{
		precache_sound("uwc3x/ultimate_stopped.wav");
	}
	
	if (file_exists("sound/uwc3x/xbow_fire1.wav"))
	{
		precache_sound("uwc3x/xbow_fire1.wav");
	}
	
	if (file_exists("sound/uwc3x/xbow_hit2.wav"))
	{
		precache_sound("uwc3x/xbow_hit2.wav");
	}
	
	if (file_exists("sound/uwc3x/yarr.wav"))
	{
		precache_sound("uwc3x/yarr.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm1_gtome.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm1_gtome.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm1_tome.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm1_tome.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_cure.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_cure.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_dehex.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_dehex.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_fire.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_fire.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_gate.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_gate.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_heal.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_heal.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_inv.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_inv.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_invul.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_invul.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm3_inv_done.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm3_inv_done.wav");
	}
	
	if (file_exists("sound/uwc3x/shopmenu/sm_pickupitem.wav"))
	{
		precache_sound("uwc3x/shopmenu/sm_pickupitem.wav");
	}
}

public Check_UWC3X ( )
{

	if ( CVAR_ENABLE_UWC3X == 0 )
	{
		uwc3x = false;
		set_msg_block ( gmsgDeathMsg, BLOCK_NOT );
	}
	else
	{
		uwc3x = true;
		set_msg_block ( gmsgDeathMsg, BLOCK_SET );
	}

	return PLUGIN_CONTINUE;
}

public amx_restartround(id, level)
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_console, "%L", id, "NO_ACCESS" );
			}

			return PLUGIN_HANDLED;
		}
	}

	new time[32], name[32];
	read_argv ( 1, time, 31 );
	new iTime = str_to_num(time);
	get_user_name ( id, name, 31 );

	// [9-30-04] Added logging of amx_givexp ( ) command - K2mia
	log_amx( "[UWC3X] Command Issuesd :: amx_restartround ( ) by %s time %d", name, iTime );
	restart_round_command(iTime);
	return PLUGIN_CONTINUE;
}

public restart_round_command(time)
{
	set_cvar_num("sv_restartround",time);
	return PLUGIN_CONTINUE;
}

public Initialize_PlayerData ( id, limited )
{
	if (CVAR_DEBUG_MODE)
	{
		log_amx( "[UWC3X] Initialize_PlayerData :: id=%d; limited=%d", id, limited);
	}
	
	//clear the hud chats
	hudchat_clear(id);

	unammo[id]				= false;
	badaim[id]				= false;
	hasFrostNade[id]		= false;
	isChilled[id]			= false;
	isFrozen[id]			= false;

	//Kick Flag
	kickflag[id]			= 0;
	jumpnum[id]				= 0;

	//multijump
	dojump[id]				= false;

	//User is not rotting
	bIsRotting[id]			= false;
	blessings[id]           = 0;

	//Team Shield stuff
	HasTeamShield[id]		= false;
	p_ShieldMaxDamageAbsorbed[id] = 0;
	UsedTeamShield[id]		= 0;
	TeamShieldCooldown[id]	= 0;

	//Cloak of chameleon
	CheckCloak[id]			= true;

	//Depower
	UsedDepower[id]			= 0;
	BlockPickup[id]			= false;

	//Reset Cripple
	crippletype[id]			= 0;
	iscrippled[id]			= 0;

	isburning[id]			= 0;		// Init player burning from flamethrower status
	isnburning[id]			= 0;		// Init player burning from napalm status


	// Init player item slot 1 / slot 2 / slot 3 and can buy an item
	playeritem3[id] 		= 0;
	playerCanBuyitem3[id] 	= 1;
	healingwaves[id] 		= 0;
	bHexed[id]				= false;
	
	gateused[id] 			= false;
	
	// Init # of ultimates learned
	wardsused[id]			= 0;
	HookCount[id] 			= 0
	hooked[id] 				= false;
	rope[id] 				= false;
	hook[id] 				= false;
	grab[id] 				= false;
	HookCount[id] 			= 0;
	GrabCount[id] 			= 0;
	RopeCount[id] 			= 0;

	issearching[id]			= false;	// Init player searching state ( for some ultimates )
	stunned[id]				= false;	// Init player stunned state
	slowed[id]				= false;	// Init player slowed state
	hasblink[id]			= false;	// Init player has blink status
	ultimateused[id]		= false;	// Init ultimateused status
	decoyused[id]			= false;	// Init decoyused status for round
	medicalert[id]			= false;	// Init medicalert status
	temp_immunity[id]		= false;	// Init temporary immunity status
	hasrespawned[id]		= false; 	// Init player has respawned status
	ispoisonedss[id]		= 0;		// Init ispoisoned from s. strike status
	isdiseasedcb[id]		= 0;		// Init isdiseased from carion status
	repairs[id]				= 0;		// Init # of repairs performed for round
	mends[id]				= 0;		// Init # of mends performed for round
	dispells[id]			= 0;		// Init # of dispells performed for round
	he[id]					= 0;		// Init player he-grenade status
	threwnapalm[id]			= 0;		// Init player has thrown a napalm nade status
	vengeance_used[id]		= 0;		// Init player's Vengeance used status
	vampiric_hits[id]		= 0;		// Init vampiric aura hits
	playertombs[id]			= 0;		// Sets no Tomes purchased
	HkDelay[id] 			= 0.0;
	HookCount[id] 			= 0;
	GrabCount[id] 			= 0;
	RopeCount[id] 			= 0;
	hooked[id] 				= false;
	hook[id] 				= false;
	rope[id] 				= false;
	hook[id] 				= false;
	bHexed[id]				= false;

	if ( limited)
	{
		// Limited initialize only, for new_round event mainly - now we exit since its limited
		return PLUGIN_CONTINUE;
	}

	if ( CVAR_LOWRES_DEFAULT )
	{
		// Init player's lowres setting to on
		lowres[id] = true;
	}
	else
	{
		// Init player's lowres setting to off
		lowres[id] = false;
	}

	playeritem[id] 			= 0;
	playeritem2[id] 		= 0;
	ultlearned[id] 			= 0;
	HkDelay[id] 			= 0.0

	// Init player level to 0
	p_level[id] 			= 0;

	// Init playerxp to 0
	playerxp[id] 			= 0;

	// Init player has loaded xp/level data state
	loadedlevel[id] 		= 0;

	// Set all skills for this player slot to 0
	for ( new j=0; j<MAX_SKILLS; j++ )
	{
		p_skills[id][j] = 0;
	}

	// Set all attributes for this player slot to the base amount
	for ( new j=0; j<MAX_ATTRIBS; j++ )
	{
		p_attribs[id][j] = ATTRIB_BASE;
	}

	// Set all resistances for this player slot to 0
	for ( new j=0; j<MAX_RESISTS; j++ )
	{
		p_resists[id][j] = 0;
	}

	return PLUGIN_CONTINUE;
}

public check_say ( id )
{

	new said[32], arg1[32], arg2[32], tsaid[32];
	read_args ( said, 31 );

	tsaid = said;
	remove_quotes ( tsaid );
	strbreak ( tsaid, arg1, 32, arg2, 32 );

	//if ( equali ( said,"^"/war3menu^"" ) || equali ( said,"^"war3menu^"" ) || equali ( said,"^"/wc3menu^"" ) || equali ( said,"^"wc3menu^"" ) || equali ( said,"^"/warcraft^"" ) || equali ( said,"^"warcraft^"" ) )
	//	main_menu ( id );
	//else if ( equali ( said, "^"/news^"" ) || equali ( said, "^"news^"" ) )
	//	show_news ( id );
	if ( equali ( said, "^"/help^"" ) || equali ( said, "^"help^"" ) || equali ( said, "^"uwc3menu^"" ) || equali ( said, "^"uwc3xmenu^"" ) )
		uwc3x_info ( id );
	else if ( equali ( said, "^"/commands^"" ) || equali ( said, "^"commands^"" ) )
		uwc3x_commands ( id );
	//else if ( equali ( said, "^"/tips^"" ) || equali ( said, "^"uwc3tips^"" ) || equali ( said, "^"uwc3xtips^"" ) )
	//	uwc3x_tips ( id );
	//else if ( equali ( said, "^"/tips2^"" ) || equali ( said, "^"uwc3tips2^"" ) || equali ( said, "^"uwc3xtips2^"" ) )
	//	uwc3x_tips2 ( id );
	else if ( equali ( said, "^"/war3help^"" ) || equali ( said, "^"war3help^"" ) || equali ( said, "^"uwc3xhelp^"" ) || equali ( said, "^"uwc3help^"" ) )
		uwc3x_info ( id );
	else if ( equali ( said, "^"/changerace^"" ) || equali ( said, "^"changerace^"" ) )
		change_race ( id );
	else if ( equali ( said, "^"/selectrace^"" ) || equali ( said, "^"selectrace^"" ) )
		change_race ( id );
	else if ( equali ( said,"^"/level^"" ) || equali ( said,"^"level^"" ) )
		displaylevel ( id,0 );
	else if ( equali ( said,"^"/character^"" ) || equali ( said,"^"character^"" ) || equali ( said,"^"/charactersheet^"" ) || equali ( said,"^"charactersheet^"" ) || equali ( said,"^"/charsheet^"" ) || equali ( said,"^"charsheet^"" ) )
		character_sheet ( id );
	else if ( equali ( arg1,"/whois" ) || equali ( arg1,"whois" ) )
	{
		cmd_whois ( id, arg2 );
		return PLUGIN_HANDLED;
	}
	else if ( equali ( said,"^"/binds^"" ) || equali ( said,"^"binds^"" ) ||  equali ( said,"^"/showbinds^"" ) || equali ( said,"^"showbinds^"" )  ||  equali ( said,"^"uwc3xbinds^"" ) || equali ( said,"^"uwc3binds^"" ) )
		uwc3x_ultimates ( id );
	else if ( equali ( said,"^"/selectskill^"" ) || equali ( said,"^"selectskill^"" ) )
		select_skill ( id,1 );
	else if ( equali ( said,"^"/dropskill^"" ) || equali ( said,"^"dropskill^"" ) )
		drop_skill ( id,1 );
	else if ( equali ( said,"^"/selectattrib^"" ) || equali ( said,"^"selectattrib^"" ) )
		Select_Attrib ( id );
	else if ( equali ( said,"^"/selectresist^"" ) || equali ( said,"^"selectresist^"" ) )
		Select_Resist ( id );
	else if ( equali ( said,"^"/savexp^"" ) || equali ( said,"^"savexp^"" ) )
		ShowSaveText ( id );
	else if ( equali ( said,"^"/saveskills^"" ) || equali ( said,"^"saveskills^"" ) )
		ShowSaveText ( id );
	else if ( equali ( said,"^"/saveattribs^"" ) || equali ( said,"^"saveattribs^"" ) )
		ShowSaveText ( id );
	else if ( equali ( said,"^"/saveresists^"" ) || equali ( said,"^"saveresists^"" ) )
		ShowSaveText ( id );
	else if ( equali ( said,"^"/saveall^"" ) || equali ( said,"^"saveall^"" ) )
		ShowSaveText ( id );
	else if ( equali ( said,"^"/deletexp^"" ) || equali ( said,"^"deletexp^"" ) )
		XP_DeleteXP ( id );
	else if ( equali ( said,"^"/reset_skills^"" ) || equali ( said,"^"reset_skills^"" ) )
		Skills_Reset ( id );
	else if ( equali ( said,"^"/resetskills^"" ) || equali ( said,"^"resetskills^"" ) )
		Skills_Reset ( id );
	else if ( equali ( said,"^"/resetattribs^"" ) || equali ( said,"^"resetattribs^"" ) || equali ( said,"^"/resetattributes^"" ) || equali ( said,"^"resetattributes^"" ) )
		Reset_Attribs ( id );
	else if ( equali ( said,"^"/resetresists^"" ) || equali ( said,"^"resetresists^"" ) )
		Reset_Resists ( id );
	else if ( equali ( said,"^"/uwc3xversion^"" ) || equali ( said,"^"uwc3xversion^"" ) || equali ( said,"^"/modinfo^"" ) || equali ( said,"^"modinfo^"" ) )
	{
		//client_print( id, print_chat, "You are playing %s version %s by %s",UWC3XNAME,UWC3XVERSION,UWC3XAUTHOR );
		hudchat_show(id, "%L", id, "UWC3X_VERSION", UWC3XNAME,UWC3XVERSION,UWC3XAUTHOR);
		hudchat_update(id);
	}
	else if ( equali ( said,"^"/reseteverything^"" ) || equali ( said,"^"reseteverything^"" ) || equali ( said,"^"/resetall^"" ) || equali ( said,"^"resetall^"" ) )
	{
		Reset_Resists ( id );
		Reset_Attribs ( id );
		Skills_Reset ( id );
	}
	else if ( equali ( said,"^"/playerskills^"" ) || equali ( said,"^"playerskills^"" ) )
		player_skills ( id );
	else if ( equali ( said,"^"/who^"" ) || equali ( said,"^"who^"" ) )
		cmd_who ( id );
	else if ( equali ( said,"^"/skillsinfo^"" ) || equali ( said,"^"skillsinfo^"" ) )
		Menu_Skills ( id );
	else if ( equali ( said,"^"/skillsinfo1^"" ) || equali ( said,"^"skillsinfo1^"" ) )
		skills_info ( id,1 );
	else if ( equali ( said,"^"/skillsinfo2^"" ) || equali ( said,"^"skillsinfo2^"" ) )
		skills_info ( id,2 );
	else if ( equali ( said,"^"/skillsinfo3^"" ) || equali ( said,"^"skillsinfo3^"" ) )
		skills_info ( id,3 );
	else if ( equali ( said,"^"/skillsinfo4^"" ) || equali ( said,"^"skillsinfo4^"" ) )
		skills_info ( id,4 );
	else if ( equali ( said,"^"/skillsinfo5^"" ) || equali ( said,"^"skillsinfo5^"" ) )
		skills_info ( id,5 );
	else if ( equali ( said,"^"/skillsinfo6^"" ) || equali ( said,"^"skillsinfo6^"" ) )
		skills_info ( id,6 );
	else if ( equali ( said,"^"/skillsinfo7^"" ) || equali ( said,"^"skillsinfo7^"" ) )
		skills_info ( id,7 );
	else if ( equali ( said,"^"/skillsinfo8^"" ) || equali ( said,"^"skillsinfo8^"" ) )
		skills_info ( id,8 );
	else if ( equali ( said,"^"/attribinfo^"" ) || equali ( said,"^"attribinfo^"" ) || equali ( said,"^"/attribsinfo^"" ) || equali ( said,"^"attribsinfo^"" ) )
		uwc3x_attributes ( id );
	else if ( equali ( said,"^"/resistinfo^"" ) || equali ( said,"^"resistinfo^"" ) || equali ( said,"^"/resistsinfo^"" ) || equali ( said,"^"resistsinfo^"" ) )
		uwc3x_resistances ( id );
	else if ( equali ( said,"^"/shopmenu^"" ) || equali ( said,"^"shopmenu^"" ) )
		ShopMenu ( id );
	else if ( equali ( said,"^"/shopmenu2^"" ) || equali ( said,"^"shopmenu2^"" ) )
		ShopMenu2 ( id );
	else if ( equali ( said,"^"/shopmenu3^"" ) || equali ( said,"^"shopmenu3^"" ) )
		ShopMenu3 ( id );
	else if ( equali ( said,"^"/itemsinfo^"" ) || equali ( said,"^"itemsinfo^"" ) )
		Show_Items_Info1 ( id );
	else if ( equali ( said,"^"/itemsinfo2^"" ) || equali ( said,"^"itemsinfo2^"" ) )
		Show_Items_Info2 ( id );
	else if ( equali ( said,"^"/itemsinfo3^"" ) || equali ( said,"^"itemsinfo3^"" ) )
		Show_Items_Info3 ( id );
	else if ( equali ( said,"^"/toggle_lowres^"" ) || equali ( said,"^"toggle_lowres^"" ) )
		toggle_lowres ( id );
	else if ( equali ( said, "^"/rings^"" ) || equali ( said,"^"rings^"" ) || equali ( said,"^"/rings5^"" ) || equali ( said,"^"rings5^"" ) )
		rings5 ( id );

	else if ( equali ( said,"^"/save skillset1^"" ) || equali ( said,"^"save skillset1^"" ) )
		Save_SkillSet ( id, 1 );
	else if ( equali ( said,"^"/save skillset2^"" ) || equali ( said,"^"save skillset2^"" ) )
		Save_SkillSet ( id, 2 );
	else if ( equali ( said,"^"/save skillset3^"" ) || equali ( said,"^"save skillset3^"" ) )
		Save_SkillSet ( id, 3 );
	else if ( equali ( said,"^"/save skillset4^"" ) || equali ( said,"^"save skillset4^"" ) )
		Save_SkillSet ( id, 4 );
	else if ( equali ( said,"^"/save skillset5^"" ) || equali ( said,"^"save skillset5^"" ) )
		Save_SkillSet ( id, 5 );

	else if ( equali ( said,"^"/load skillset1^"" ) || equali ( said,"^"load skillset1^"" ) )
		Load_SkillSet ( id, 1 );
	else if ( equali ( said,"^"/load skillset2^"" ) || equali ( said,"^"load skillset2^"" ) )
		Load_SkillSet ( id, 2 );
	else if ( equali ( said,"^"/load skillset3^"" ) || equali ( said,"^"load skillset3^"" ) )
		Load_SkillSet ( id, 3 );
	else if ( equali ( said,"^"/load skillset4^"" ) || equali ( said,"^"load skillset4^"" ) )
		Load_SkillSet ( id, 4 );
	else if ( equali ( said,"^"/load skillset5^"" ) || equali ( said,"^"load skillset5^"" ) )
		Load_SkillSet ( id, 5 );
	else if ( equali ( said,"^"/load skillset5^"" ) || equali ( said,"^"load skillset5^"" ) )
		Load_SkillSet ( id, 5 );

	else if ( equali ( said,"^"/del skillset1^"" ) || equali ( said,"^"del skillset1^"" ) )
		Delete_SkillSet ( id, 1 );
	else if ( equali ( said,"^"/del skillset2^"" ) || equali ( said,"^"del skillset2^"" ) )
		Delete_SkillSet ( id, 2 );
	else if ( equali ( said,"^"/del skillset3^"" ) || equali ( said,"^"del skillset3^"" ) )
		Delete_SkillSet ( id, 3 );
	else if ( equali ( said,"^"/del skillset4^"" ) || equali ( said,"^"del skillset4^"" ) )
		Delete_SkillSet ( id, 4 );
	else if ( equali ( said,"^"/del skillset5^"" ) || equali ( said,"^"del skillset5^"" ) )
		Delete_SkillSet ( id, 5 );
	else if ( equali ( said,"^"/del skillset5^"" ) || equali ( said,"^"del skillset5^"" ) )
		Delete_SkillSet ( id, 5 );

	else if ( equali ( said,"^"/reloadxp^"" ) || equali ( said,"^"reloadxp^"" ) || equali ( said,"^"/loadxp^"" ) || equali ( said,"^"loadxp^"" ) )
		XP_Reload ( id );
	else if ( equali ( said,"^"/reloadskills^"" ) || equali ( said,"^"reloadskills^"" ) || equali ( said,"^"/loadskills^"" ) || equali ( said,"^"loadskills^"" ) )
		XP_Reload ( id );

	return PLUGIN_CONTINUE;
}

public set_user_armor_log ( id, armor )
{

	// [10-05-04] Added the next check to prevent entity errors
	if ( !is_user_connected ( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	new name[32];
	get_user_name ( id, name, 31 );
	set_user_armor ( id, armor );
	return PLUGIN_CONTINUE;

}
public set_user_health_log ( id, health )
{

	// [10-05-04] Added the next check to prevent entity errors
	if ( !is_user_connected ( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	new name[32];
	get_user_name ( id, name, 31 );
	set_user_health ( id, health );
	return PLUGIN_CONTINUE;

}
public fullupdate ( id )
{
	new name[32],steamid[32];
	get_user_name ( id, name, 31 );
	get_user_authid( id, steamid, 31 );

	log_amx( "[UWC3X] FULLUPDATE: User:%s  SteamID:%s  -- Attempted to use the fullupdate command!", name, steamid );
	return PLUGIN_HANDLED;
}


public count_T ( )
{
	return Util_CountTeam ( TEAM_T );
}

public count_CT ( )
{
	return Util_CountTeam ( TEAM_CT );
}

public Util_CountTeam ( TEAM )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new players[32], numberofplayers, count = 0;
	get_players ( players, numberofplayers );

	for ( new i = 0; i < numberofplayers; ++i )
	{
		new id = players[i];
		if ( TEAM == TEAM_CT )
		{
			if ( get_user_team ( id ) == TEAM_CT )
			{
				count += 1;
			}
		}
		else
		{
			if ( get_user_team ( id ) == TEAM_T )
			{
				count += 1;
			}
		}
	}

	return count;
}

public sqrt ( num )
{
	new div = num;
	new result = 1;

	while ( div > result )
	{
		// end when div == result, or just below
		div = ( div + result ) / 2; // take mean value as new divisor
		result = num / div;
	}

	return div;
}

public PreCache_Models ( )
{
	if ( file_exists ( "models/player/zombie/zombie.mdl" ) )
	{
		precache_model ( "models/player/zombie/zombie.mdl" );
	}

	if ( file_exists ( "models/roots2.mdl" ) )
	{
		precache_model ( "models/roots2.mdl" );
	}

	//Fireball
	if ( file_exists ( "models/rpgrocket.mdl" ) )
	{
		precache_model("models/rpgrocket.mdl");
	}

	//Ice Bomb
	if ( file_exists ( "models/frostnova.mdl" ) )
	{
		precache_model("models/frostnova.mdl");
	}

	//Ice Bomb
	if ( file_exists ( "models/mine.mdl" ) )
	{
		precache_model("models/mine.mdl");
	}

	glassGibs = precache_model("models/glassgibs.mdl");

	// Precache std CS player models for use with decoy ability
	precache_model ( "models/player/leet/leet.mdl" );
	precache_model ( "models/player/arctic/arctic.mdl" );
	precache_model ( "models/player/guerilla/guerilla.mdl" );
	precache_model ( "models/player/terror/terror.mdl" );
	precache_model ( "models/player/gign/gign.mdl" );
	precache_model ( "models/player/sas/sas.mdl" );
	precache_model ( "models/player/gsg9/gsg9.mdl" );
	precache_model ( "models/player/urban/urban.mdl" );
	precache_model ( "models/player/vip/vip.mdl" );
	precache_model ( "models/guerilla.mdl" );
}

public PreCache_Sprites ( )
{
	g_sModelIndexFireball = precache_model ( "sprites/zerogxplode.spr" );
	g_sModelIndexSmoke = precache_model ( "sprites/steam1.spr" );
	m_iSpriteTexture = precache_model ( "sprites/shockwave.spr" );
	flaresprite = precache_model ( "sprites/blueflare2.spr" );
	m_iTrail = precache_model ( "sprites/smoke.spr" );
	lightning = precache_model ( "sprites/lgtning.spr" );
	shadow = precache_model ( "sprites/xspark3.spr" );
	carrion = precache_model ( "sprites/carrion.spr" );
	fire = precache_model ( "sprites/explode1.spr" );
	burning = precache_model ( "sprites/xfire.spr" );

	// [09-02-04] Added sprites for medic, shield and combo, and other effects
	medicspr = precache_model ( "sprites/medic3.spr" );
	shieldspr = precache_model ( "sprites/shield3.spr" );
	medshieldspr = precache_model ( "sprites/medshield1.spr" );
	rotmedshieldspr = precache_model ( "sprites/rotmedshield.spr" );
	blast = precache_model ( "sprites/blast2.spr" );
	gatespr = precache_model ( "sprites/gate1.spr" );
	cbgreen = precache_model ( "sprites/bm7.spr" );
	poison = precache_model ( "sprites/poison1.spr" );
	spikes = precache_model ( "sprites/spikes1.spr" );
	thorns = precache_model ( "sprites/thorns2.spr" );

	//[11-AUG-2009] Added sprites for rot and rottrail.Sprites created by (--eRRoR--)
	ROTtrail = precache_model ( "sprites/rot_trail.spr" );
	ROTspr = precache_model ( "sprites/rot_infects.spr" );
	sprite_blood_spray = precache_model("sprites/bloodsprayROT.spr")
	sprite_blood_drop = precache_model("sprites/bloodROT.spr")

	//Earth Quake
	//sprite_boom = g_sModelIndexFireball;

	//FireBall
	sprite_beam = g_sModelIndexFireball;

	//Ice Bombs
	trailSpr = precache_model("sprites/laserbeam.spr");
	
	//Hook
	beam = precache_model("sprites/zbeam4.spr");
	beamsprite = precache_model("sprites/dot.spr");
}

public Check_Redirection_Level_System ( )
{
	if ( CVAR_REDIRECT_ENABLE != 0 )
	{
		levelredirection = true;
	}
	else
	{
		levelredirection = false;
		return;
	}

	if ( CVAR_REDIRECT_TOP_LEVEL != 0 )
	{
		forwardontolevel[2] = CVAR_REDIRECT_TOP_LEVEL;
		log_amx( "[UWC3X] Redirection System : UW_rdlvl_top -> %d", CVAR_REDIRECT_TOP_LEVEL );

		get_pcvar_string ( REDIRECT_TOP_SERVER, forwardontoserver[2], 64 );
		log_amx( "[UWC3X] Redirection System : UW_rdsvr_top --> %s", forwardontoserver[2] );
	}

	if ( CVAR_REDIRECT_MIDDLE_LEVEL != 0 )
	{
		forwardontolevel[1] = CVAR_REDIRECT_MIDDLE_LEVEL;
		get_pcvar_string ( REDIRECT_MIDDLE_SERVER, forwardontoserver[1], 64 );
	}

	if ( CVAR_REDIRECT_BOTTOM_LEVEL != 0 )
	{
		forwardontolevel[0] = CVAR_REDIRECT_BOTTOM_LEVEL;
		get_pcvar_string ( REDIRECT_BOTTOM_SERVER, forwardontoserver[0], 64 );
	}

	if ( forwardontolevel[2] && levelredirection )
	{
		log_amx( "[UWC3X] Redirection System : Greater than level %d --> %s", forwardontolevel[2], forwardontoserver[2] );
	}

	if ( forwardontolevel[1] && levelredirection )
	{
		log_amx( "[UWC3X] Redirection System : Greater than level %d --> %s", forwardontolevel[1], forwardontoserver[1] );
	}

	if ( forwardontolevel[0] && levelredirection )
	{
		log_amx( "[UWC3X] Redirection System : Greater than level %d --> %s" ,forwardontolevel[0], forwardontoserver[0] );
	}
	else
	{
		levelredirection = false;
		log_amx( "[UWC3X] Redirection System : ERROR No bottom redirection level. --> Deactivated" );
	}

}

//glow_change
public ChangeGlow ( parm[] )
{
	new id = parm[0];

	// [10-05-04] Added the next check to prevent entity errors
	if ( !is_user_connected ( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	if ( p_skills[id][SKILLIDX_INVIS] )
	{
		// Don't glow if player is invisible
		iglow[id][0] = 0;
		iglow[id][1] = 0;
		iglow[id][2] = 0;
		iglow[id][3] = 0;
	}
	else if ( playeritem[id] == CLOAK )
	{
		// Don't glow if player is invisible
		iglow[id][0] = 0;
		iglow[id][1] = 0;
		iglow[id][2] = 0;
		iglow[id][3] = 0;
	}
	else if ( iglow[id][0] > 5 )
	{
		set_user_rendering ( id, kRenderFxGlowShell, iglow[id][0], 0, 0, kRenderNormal, 16 );
		iglow[id][0] -= 5;
		set_task ( 0.2, "ChangeGlow", TASK_CHANGE_GLOW1, parm, 2 );
	}
	else if ( iglow[id][1] > 5 )
	{
		set_user_rendering ( id, kRenderFxGlowShell, 0, iglow[id][1], 0, kRenderNormal, 16 );
		iglow[id][1] -= 5;
		set_task ( 0.2, "ChangeGlow", TASK_CHANGE_GLOW1, parm, 2 );
	}
	else if ( iglow[id][2] > 5 )
	{
		set_user_rendering ( id, kRenderFxGlowShell, 0, 0, iglow[id][2], kRenderNormal, 16 );
		iglow[id][2] -= 5;
		set_task ( 0.2, "ChangeGlow",TASK_CHANGE_GLOW1,parm,2 );
	}
	else if ( iglow[id][3] > 5 )
	{
		set_user_rendering ( id, kRenderFxGlowShell, iglow[id][3], iglow[id][3], iglow[id][3], kRenderNormal, 16 );
		iglow[id][3] -= 5;
		set_task ( 0.2, "ChangeGlow", TASK_CHANGE_GLOW1, parm, 2 );
	}
	else
	{
		iglow[id][0] = 0;
		iglow[id][1] = 0;
		iglow[id][2] = 0;
		iglow[id][3] = 0;
		set_user_rendering ( id );
	}

	return PLUGIN_CONTINUE;

}


public zoomed2 ( id )
{
	zoomed[id] = 1;
}

public unzoomed ( id )
{
	zoomed[id] = 0;
}

public Uwc3_GetUserSpeed( id )
{

}

public reset_maxspeed ( parm[] )
{
	new id = parm[0];
	if ( !Util_Is_Valid_Player ( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	stunned[id] = false;
	slowed[id] = false;

	//Using the Set_Speed function to set their speed instead
	new speedparm[1];
	speedparm[0] = id;
	Set_Speed( speedparm );

	//set_user_maxspeed ( parm[0], float ( normalspeed ) );
	return PLUGIN_CONTINUE;
}
public admin_loc ( id )
{
	new origin[3];
	get_user_origin ( id,origin );
	if( Util_Should_Msg_Client(id) )
	{
		client_print ( id, print_chat, "%L", id, "ADMIN_SHOW_LOCATION", MOD, origin[0], origin[1], origin[2] );
	}
	return PLUGIN_HANDLED;
}

public toggle_lowres ( id )
{

	if ( !uwc3x )
	{
		return PLUGIN_HANDLED;
	}

	if ( lowres[id] )
	{
		lowres[id] = false;
		if( Util_Should_Msg_Client(id) )
		{
			hudchat_show(id, "%L", id, "LOW_RES_OFF");
			hudchat_update(id);
			//client_print ( id, print_chat, "%L", id, "LOW_RES_OFF", MOD );
		}
	}
	else
	{
		lowres[id] = true;
		if( Util_Should_Msg_Client(id) )
		{
			hudchat_show(id, "%L", id, "LOW_RES_ON");
			hudchat_update(id);
			//client_print ( id, print_chat, "%L", id, "LOW_RES_ON", MOD );
		}
	}

	return PLUGIN_HANDLED;
}

public setSpecMode ( id )
{
	new arg[12];
	read_data ( 2 , arg , 11 );
	g_specMode[ id ] = ( arg[10] == '2' ) ? true : false;
}



//public hideStatus ( id )
//{
//	if ( CVAR_SHOW_PLAYER )
//	{
//		if( Util_Should_Msg_Client(id) )
//		{
//			set_hudmessage ( 0,0,0,0.0,0.0,0, 0.0, 0.01, 0.0, 0.0, 4 );
//			show_hudmessage ( id,"" );
//		}
//	}
//}
//public showRank ( id )
//{
//
//	if ( !CVAR_SPECTATOR_INFO )
//	{
//		return PLUGIN_CONTINUE;
//	}
//
//	if ( !g_specMode[id] )
//	{
//		return PLUGIN_CONTINUE;
//	}
//
//	new a = read_data ( 2 );
//
//	if ( !is_user_connected ( a ) )
//	{
//		return PLUGIN_CONTINUE;
//	}
//
//	new name[32];
//	get_user_name ( a, name, 31 );
//
//	if ( playerxp[a] < 0 )
//	{
//		playerxp[a] = 0;
//	}
//
//	return PLUGIN_CONTINUE;
//
//}
//
//public showStatus ( id )
//{
//	new pid = read_data ( 2 );
//
//	if ( get_user_team ( id )==get_user_team ( pid ) && ( playeritem2[pid]==CHAMELEON || skinchanged[pid] ) && is_user_alive ( pid ) )
//	{
//		if( Util_Should_Msg_Client_Alive( id ) )
//		{
//			client_print ( id, print_center, "%L", id, "SAME_TEAM" );
//			if ( file_exists ( "sound/uwc3x/antend.wav" ) ==1 )
//			{
//				emit_sound ( id,CHAN_ITEM, "uwc3x/antend.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
//			}
//		}
//	}
//
//	if ( CVAR_SHOW_PLAYER && !freezetime )
//	{
//		new name[32], color1 = 0,color2 = 0;
//		get_user_name ( pid, name, 31 );
//
//		if ( get_user_team ( pid ) == 1 )
//		{
//			color1 = 255;
//		}
//		else
//		{
//			color2 = 255;
//		}
//
//		if ( g_friend[id] == 1 )
//		{
//			set_hudmessage ( color1,50,color2,-1.0,0.60,1, 0.01, 3.0, 0.01, 0.01, 4 );
//			new health = get_user_health ( pid );
//
//			if ( health>1500 )
//			{
//				health = health-2048;
//			}
//			else if ( health>500 )
//			{
//				health = health-1024;
//			}
//
//			if( Util_Should_Msg_Client_Alive( id ) )
//			{
//				//show_hudmessage ( id,"%s -- %d HP / %d AP", name, health, get_user_armor ( pid ) );
//				hudchat_show(id, "%L", id, "EXAMINE_ENEMY_HPAP", name, health, get_user_armor ( pid ));
//				hudchat_update(id);
//			}
//		}
//		else
//		{
//			if( Util_Should_Msg_Client_Alive( id ) )
//			{
//				hudchat_show(id,name);
//				hudchat_update(id);
//				//set_hudmessage ( color1,50,color2,-1.0,0.60,1, 0.01, 3.0, 0.01, 0.01, 4 );
//				//show_hudmessage ( id,name );
//			}
//		}
//	}
//}
//
//



public BuyZone ( id )
{
	if ( read_data ( 1 ) )
	{
		isBuyzone[id] = true;
	}
	else
	{
		isBuyzone[id] = false;
	}

	return PLUGIN_CONTINUE;
}

public setTeam ( id )
{
	g_friend[id] = read_data ( 2 );
}

public set_buytime ( )
{
	buytime = false;
}


public get_nade_origin ( parm[] )
{
	new id = parm[0];
	new grenadeid = parm[1];

	new Float:origin[3];
	new Float:porigin[3];

	//Entvars_Get_Vector( grenadeid, EV_VEC_origin, origin );
	entity_get_vector( grenadeid, EV_VEC_origin, origin );

	he_origin[id][0] = origin[0];
	he_origin[id][1] = origin[1];
	he_origin[id][2] = origin[2];

	//Entvars_Get_Vector ( id, EV_VEC_origin, porigin );
	entity_get_vector( id, EV_VEC_origin, porigin );
	set_task ( 0.1, "get_nade_origin", TASK_GET_NADE_ORIGIN, parm, 2 );
}
public reset_he_origin ( parm[] )
{
	//new enemy = parm[0];
	he_origin[ parm[0] ][0] =- 1.234;
	he_origin[ parm[0] ][1] =- 1.234;
	he_origin[ parm[0] ][2] =- 1.234;
}

public check_alive ( parm[] )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	//new id = parm[0];

	if ( alive_before_explosion[ parm[0] ] && !is_user_alive ( parm[0] ) )
	{
		diedlastround[ parm[0] ] = true;
		alive_before_explosion[ parm[0] ] = false;
	}

	return PLUGIN_CONTINUE;
}

public changeskin ( id, reset )
{
	if( !Util_Is_Valid_Player( id ) )
		return PLUGIN_HANDLED;

	if ( reset == 1 )
	{
		cs_reset_user_model ( id );
		skinchanged[id] = false;
		return PLUGIN_HANDLED;
	}
	else if ( reset == 2 )
	{
		cs_set_user_model ( id,"zombie" );
		skinchanged[id] = true;
		return PLUGIN_HANDLED;
	}
	else
	{
		new num = random_num ( 0,3 );

		if ( get_user_team ( id )==TEAM_T )
		{
			cs_set_user_model ( id,CTSkins[num] );
		}
		else
		{
			cs_set_user_model ( id,TSkins[num] );
		}

		skinchanged[id]=true;
	}

	return PLUGIN_CONTINUE;
}

public IsWeaponKnife( iWeaponID )
{

	if( iWeaponID == CSW_KNIFE )
	{
		return true;
	}

	return false;
}

public IsWeaponSmokeGrenade( iWeaponID )
{
	if( iWeaponID == CSW_SMOKEGRENADE )
		return true;

	return false;
}

public IsWeaponGrenade( iWeaponID )
{
	if( iWeaponID == CSW_HEGRENADE || IsWeaponSmokeGrenade( iWeaponID ) || iWeaponID == CSW_FLASHBANG )
	{
		return true;
	}

	return false;
}
public IsWeaponPrimary( iWeaponID )
{
	if( IsWeaponSecondary( iWeaponID ) || IsWeaponGrenade( iWeaponID ) || IsWeaponKnife( iWeaponID ) )
	{
		return false;
	}

	return true;

}

public IsWeaponSecondary( iWeaponID )
{
	if ( iWeaponID == CSW_ELITE || iWeaponID == CSW_P228 || iWeaponID == CSW_FIVESEVEN || iWeaponID == CSW_USP || iWeaponID == CSW_GLOCK18 || iWeaponID == CSW_DEAGLE || iWeaponID == CSW_P90 )
	{
		return true;
	}

	return false;
}


public Cloak_changeskin( id )
{
	new num = random_num ( 0,3 );

	if ( get_user_team ( id )==TEAM_T )
	{
		cs_set_user_model ( id,CTSkins[num] );
	}
	else
	{
		cs_set_user_model ( id,TSkins[num] );
	}

	return PLUGIN_CONTINUE;
}


public Fwd_Touch(Ent, id)
{

	if( !is_user_connected( id ) || !is_user_alive( id ) || ( get_user_team ( id ) == SPEC ) )
		return FMRES_IGNORED;

	static model[32], classname[32];

	pev(Ent, pev_classname, classname , sizeof classname - 1);
	pev(Ent, pev_model, model, sizeof model - 1);

	if( ( containi(classname, "weapon_") != -1 && containi(model, "w_") != -1 ) && BlockPickup[id] )
	{
		//message to client telling them of the blocked pickup
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			hudchat_show(id, "%L", id, "ULTIMATE_DEPOWER_ENEMY2", MOD);
			hudchat_update(id);
			//client_print ( id, print_center, "%L", id, "ULTIMATE_DEPOWER_ENEMY2", MOD );
		}

		return FMRES_SUPERCEDE;
	}

	return FMRES_IGNORED;
}


//freezetimedone
public logevent_round_start ( )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	freezetime = false;
	use_addtofullpack = false;
	new players[32], numberofplayers, id, i, parm[1];
	get_players ( players, numberofplayers );

	for ( i = 0; i < numberofplayers; ++i )
	{

		if ( !is_user_connected ( players[i] ) )
		{
			return PLUGIN_CONTINUE;
		}

		parm[0] = players[i];
		//set_user_maxspeed ( id,240.0 );
		set_user_maxspeed ( players[i],240.0 );
		set_task ( 0.1, "unfreezespeed", TASK_UNFREEZE_SPEED );
		set_task ( 0.1, "Set_Speed", TASK_SET_SPEED, parm, 1 );

		if ( CVAR_BLINK_START_DISABLED )
		{
			if ( ! ( p_skills[ players[i] ][SKILLIDX_TELEPORT] ) )
			{
				icon_controller ( id );
				ultimateused[id] = false;
			}
		}
		else
		{
			icon_controller ( id );
			ultimateused[id] = false;
		}

		displaylevel ( id,3 );
	}

	return PLUGIN_CONTINUE;
}

public unfreezespeed ( )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new players[32], numberofplayers, i;
	get_players ( players, numberofplayers );

	for ( i = 0; i < numberofplayers; ++i )
	{
		change_weapon ( players[i] );
	}

	return PLUGIN_CONTINUE;
}

public teamselect ( id )
{
	new arg[2];
	read_argv ( 1,arg,1 );

	if ( currentteam[id] != str_to_num ( arg ) )
	{
		changingteam[id] = true;
	}
	else
	{
		changingteam[id] = false;
	}
}

public icon_controller ( id )
{
	if ( !CVAR_SHOW_ICONS || ( freezetime ) || ( u_delay ) || ( p_skills[id][SKILLIDX_TELEPORT] && blinkdelayed[id] && CVAR_BLINK_START_DISABLED ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( !ultlearned[id] )
	{
		// Player doesn't know any ultimates, no icons to display
		return PLUGIN_HANDLED;
	}

	return PLUGIN_CONTINUE;

}

public mapbounds_killer()
{
	if( CVAR_HOOK_NO_OOB == 0)
		return PLUGIN_CONTINUE;

	if (!mapbounds_checked) 
	{
		new nump = get_pluginsnum();
		new filename[64],temp[5];
		for(new i=0;i<nump;++i)
		{
			get_plugin(i,filename,63,temp,4,temp,4,temp,4,temp,4);

			if (equali(filename,"amx_ejl_outofbounds.amx"))
			{
				ob_pl1 = 1;
			}
			else if (equali(filename,"out_of_bounds.amx"))
			{
				ob_pl2 = 1;
			}
		}
		mapbounds_checked = true;
	}

	if (CVAR_HOOK_NO_OOB == 1) 
	{
		if(ob_pl1 == 1)
			pause("ac","amx_ejl_outofbounds.amx");
			
		if(ob_pl2 == 1)
			pause("ac","out_of_bounds.amx");
	}
	else 
	{
		if(ob_pl1 == 1)
			unpause("ac","amx_ejl_outofbounds.amx");
			
		if(ob_pl2 == 1)
			unpause("ac","out_of_bounds.amx");
	}

	return PLUGIN_CONTINUE;
}

public check_for_living ( )
{
	new players[32], numberofplayers, i, id;
	get_players ( players, numberofplayers );

	for ( i = 0; i < numberofplayers; ++i )
	{
		id = players[i];
		if ( is_user_alive ( id ) )
		{
			alive_before_explosion[id] = true;
			saveweapons ( id );
		}
	}

	return PLUGIN_CONTINUE;
}

public check_for_living2 ( )
{
	new players[32], numberofplayers, i, id;
	get_players ( players, numberofplayers );

	if ( bombstate == BOMB_PLANTED )
	{
		for ( i = 0; i < numberofplayers; ++i )
		{
			id = players[i];
			if ( !is_user_alive ( id ) )
			{
				diedlastround[id] = true;
			}
		}
	}
}




public monitor_players ( )
{
	new pname[32], players[32], numofplayers;
	get_players ( players, numofplayers );

	// Max. allowed discrepancy between health and maxhealth
	new allowed_diff = 5;

	for ( new i = 0; i < numofplayers; i++ )
	{
		// This Player ID
		new id = players[i];

		if ( is_user_alive ( id ) )
		{
			new health = maxhealth[id] + ( playeritem[id] == HEALTH ? HEALTHBONUS : 0 );

			//Make sure that it is never 0
			if( health == 0 )
			{
				health = 100;
			}

			if ( get_user_health ( id ) > health )
			{
				get_user_name ( id, pname, 31 );

				if ( hasgodmode[id] )
				{
					if ( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] In monitor_players ( ) :: [%s] Kept health ( Voodoo Active or Respawned ) Has= ( %d ) Max= ( %d )", pname, get_user_health ( id ), health );
					}
				}
				else
				{
					if ( CVAR_DEBUG_MODE )
					{
						if ( ( get_user_health ( id ) - health ) > allowed_diff )
						{
							log_amx( "[UWC3X] In monitor_players ( ) :: [%s] Reset health ( Voodoo Inactive  or Respawn grace over ) Has= ( %d ) Max= ( %d )", pname, get_user_health ( id ), health );
						}
					}

					set_user_health_log ( id, health );
				}
			}
		}
	}

	set_task ( 10.0, "monitor_players", TASK_MONITOR_PLAYERS );
	return PLUGIN_CONTINUE;
}

public hookDrop(id)
{

	new i_ammo, i_clip;
	new idgun = get_user_weapon( id, i_clip, i_ammo );

	if ( ( idgun == CSW_TMP ) && BlockPickup[id] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			hudchat_show(id, "%L", id, "ULTIMATE_DEPOWER_ENEMY2", MOD);
			hudchat_update(id);
			//client_print ( id, print_center, "%L", id, "ULTIMATE_DEPOWER_ENEMY2", MOD );
		}

		return PLUGIN_HANDLED;
	}

	return PLUGIN_CONTINUE;
}

public GetWeaponName ( weapon )
{
	new weaponname[32];

	switch ( weapon )
	{
		case 1:
			weaponname = "p228";
		case 3:
			weaponname = "scout";
		case 4:
			weaponname = "grenade";
		case 5:
			weaponname = "xm1014";
		case 7:
			weaponname = "mac10";
		case 8:
			weaponname = "aug";
		case 10:
			weaponname = "elite";
		case 11:
			weaponname = "fiveseven";
		case 12:
			weaponname = "ump45";
		case 13:
			weaponname = "sg550";
		case 16:
			weaponname = "usp";
		case 17:
			weaponname = "glock18";
		case 18:
			weaponname = "awp";
		case 19:
			weaponname = "mp5navy";
		case 20:
			weaponname = "m249";
		case 21:
			weaponname = "m3";
		case 22:
			weaponname = "m4a1";
		case 23:
			weaponname = "tmp";
		case 24:
			weaponname = "g3sg1";
		case 26:
			weaponname = "deagle";
		case 27:
			weaponname = "sg552";
		case 28:
			weaponname = "ak47";
		case 29:
			weaponname = "knife";
		case 30:
			weaponname = "p90";
	}

	return weaponname;
}

//Basicly see's if we can draw a straight line to the target without interference
public UTIL_IsInView(id,target)
{
	if(id == 0 || target == 0)
	{
		return false;
	}

	new Float:IdOrigin[3], Float:TargetOrigin[3], Float:ret[3]
	new iIdOrigin[3], iTargetOrigin[3]

	get_user_origin(id,iIdOrigin,1)
	get_user_origin(target,iTargetOrigin,1)

	IVecFVec(iIdOrigin,IdOrigin)
	IVecFVec(iTargetOrigin, TargetOrigin)

	if ( trace_line ( 1, IdOrigin, TargetOrigin, ret ) == target)
		return true

	if ( get_distance_f(TargetOrigin,ret) < 10.0)
		return true

	return false
}


public Float:radius_calucation(Float:origin1[3],Float:origin2[3],Float:radius,Float:maxVal,Float:minVal)
{
	if(maxVal <= 0.0)
		return 0.0;

	if(minVal >= maxVal)
		return minVal;

	new Float:percent;

	// figure out how far away the points are
	new Float:distance = vector_distance(origin1,origin2);

	// if we are close enough, assume we are at the center
	if(distance < 40.0)
		return maxVal;

	// otherwise, calculate the distance range
	else
		percent = 1.0 - (distance / radius);

	// we have the technology...
	return minVal + (percent * (maxVal - minVal));
}

// displays x y z axis
public show_xyz(origin[3],radius)
{
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(0); // TE_BEAMPOINTS
	write_coord(origin[0]); // start x
	write_coord(origin[1]); // starty
	write_coord(origin[2] + 1); // start z
	write_coord(origin[0] + radius); // end x
	write_coord(origin[1]); // end y
	write_coord(origin[2] + 1); // end z
	write_short(trailSpr); // sprite
	write_byte(0); // starting frame
	write_byte(0); // framerate
	write_byte(100); // life
	write_byte(8); // line width
	write_byte(0); // noise
	write_byte(255); // r
	write_byte(0); // g
	write_byte(0); // b
	write_byte(200); // brightness
	write_byte(0); // scroll speed
	message_end();

	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(0); // TE_BEAMPOINTS
	write_coord(origin[0]); // start x
	write_coord(origin[1]); // starty
	write_coord(origin[2] + 1); // start z
	write_coord(origin[0]); // end x
	write_coord(origin[1] + radius); // end y
	write_coord(origin[2] + 1); // end z
	write_short(trailSpr); // sprite
	write_byte(0); // starting frame
	write_byte(0); // framerate
	write_byte(100); // life
	write_byte(8); // line width
	write_byte(0); // noise
	write_byte(0); // r
	write_byte(255); // g
	write_byte(0); // b
	write_byte(200); // brightness
	write_byte(0); // scroll speed
	message_end();

	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(0); // TE_BEAMPOINTS
	write_coord(origin[0]); // start x
	write_coord(origin[1]); // starty
	write_coord(origin[2]); // start z
	write_coord(origin[0]); // end x
	write_coord(origin[1]); // end y
	write_coord(origin[2] + radius); // end z
	write_short(trailSpr); // sprite
	write_byte(0); // starting frame
	write_byte(0); // framerate
	write_byte(100); // life
	write_byte(8); // line width
	write_byte(0); // noise
	write_byte(0); // r
	write_byte(0); // g
	write_byte(255); // b
	write_byte(200); // brightness
	write_byte(0); // scroll speed
	message_end();
}

// give an entity a trail
public set_beamfollow(ent,life,width,r,g,b,brightness)
{
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(22); // TE_BEAMFOLLOW
	write_short(ent); // ball
	write_short(trailSpr); // sprite
	write_byte(life); // life
	write_byte(width); // width
	write_byte(r); // r
	write_byte(g); // g
	write_byte(b); // b
	write_byte(brightness); // brightness
	message_end();
}

// blue blast
public create_blast(origin[3], tempRadius)
{
	// smallest ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 385); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(FROST_R); // red
	write_byte(FROST_G); // green
	write_byte(FROST_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// medium ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 470); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(FROST_R); // red
	write_byte(FROST_G); // green
	write_byte(FROST_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// largest ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 555); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(FROST_R); // red
	write_byte(FROST_G); // green
	write_byte(FROST_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// light effect
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(27); // TE_DLIGHT
	write_coord(origin[0]); // x
	write_coord(origin[1]); // y
	write_coord(origin[2]); // z
	write_byte(tempRadius); // radius
	write_byte(FROST_R); // r
	write_byte(FROST_G); // g
	write_byte(FROST_B); // b
	write_byte(8); // life
	write_byte(60); // decay rate
	message_end();
}

public create_eq_blast(origin[3], EQ_RADIUS)
{

	new EQ_R, EQ_G, EQ_B;

	EQ_R = 139;
	EQ_G = 69;
	EQ_B = 19;

	// smallest ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 385); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(EQ_R); // red
	write_byte(EQ_G); // green
	write_byte(EQ_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// medium ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 470); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(EQ_R); // red
	write_byte(EQ_G); // green
	write_byte(EQ_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// largest ring
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(21); // TE_BEAMCYLINDER
	write_coord(origin[0]); // start X
	write_coord(origin[1]); // start Y
	write_coord(origin[2]); // start Z
	write_coord(origin[0]); // something X
	write_coord(origin[1]); // something Y
	write_coord(origin[2] + 555); // something Z
	write_short(m_iSpriteTexture); // sprite
	write_byte(0); // startframe
	write_byte(0); // framerate
	write_byte(4); // life
	write_byte(60); // width
	write_byte(0); // noise
	write_byte(EQ_R); // red
	write_byte(EQ_G); // green
	write_byte(EQ_B); // blue
	write_byte(100); // brightness
	write_byte(0); // speed
	message_end();

	// light effect
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(27); // TE_DLIGHT
	write_coord(origin[0]); // x
	write_coord(origin[1]); // y
	write_coord(origin[2]); // z
	write_byte(EQ_RADIUS); // radius
	write_byte(EQ_R); // r
	write_byte(EQ_G); // g
	write_byte(EQ_B); // b
	write_byte(8); // life
	write_byte(60); // decay rate
	message_end();
}



public get_origin(ent,Float:origin[3])
{
#if defined engine
	return entity_get_vector(id,EV_VEC_origin,origin)
#else
	return pev(ent,pev_origin,origin)
#endif
}

public set_velo(id,Float:velocity[3])
{
#if defined engine
	return set_user_velocity(id,velocity)
#else
	return set_pev(id,pev_velocity,velocity)
#endif
}

public get_velo(id,Float:velocity[3])
{
#if defined engine
	return get_user_velocity(id,velocity)
#else
	return pev(id,pev_velocity,velocity)
#endif
}

public is_valid_ent2(ent)
{
#if defined engine
	return is_valid_ent(ent)
#else
	return pev_valid(ent)
#endif
}

public get_solidity(ent)
{
#if defined engine
	return entity_get_int(ent,EV_INT_solid)
#else
	return pev(ent,pev_solid)
#endif
}

public UTIL_Kill(attacker,id,weapon[])
{
	
	if(get_user_team(attacker)!=get_user_team(id))
		set_user_frags(attacker,get_user_frags(attacker) +1);

	if(get_user_team(attacker)==get_user_team(id))
		set_user_frags(attacker,get_user_frags(attacker) -1);
		
	//if (cs_get_user_money(attacker) + 150 <= 16000)
	cs_set_user_money(attacker,cs_get_user_money(attacker)+150)
	//else
	//	cs_set_user_money(attacker,16000)
	
	//do_damage(id, attacker, 55, 31, 3, 0,0,0);
	//award_kill(attacker,id)
	//user_kill(id,1) 

	if(get_user_health(id) < 55 )
	{
		Event_Mine_createKill(id,attacker,"Clarmore Mine!");
		new name[32],aname[32];
		get_user_name ( id, name, 31 );
		get_user_name ( attacker, aname, 31 );

		if( Util_Should_Msg_Client(attacker) )
		{
			client_print( attacker, print_center, "%L", attacker, "MINE2", name );
		}

		if( is_user_connected( id ) && !is_user_bot( id ) )
		{
			client_print( id, print_center, "%L", id, "MINE1", aname );
		}
	}
	else
	{
		fakedamage(id,"Claymore", float(55) , DMG_CRUSH );
	}

	return PLUGIN_CONTINUE;
	
}

public GetSafeUserName(index, name[], len)
{
	get_user_name(index, name, len);
	MakeSafeTextForQuery(name, len);
}

public MakeSafeTextForQuery(text[], len)
{
	replace_all(text, len, "'", "''");
}

SetTaskUnique(Float:time, const function[], id = 0, const any:parameter[] = "", len = 0, const flags[] = "", repeat = 0)
{
	RemoveTaskIfExists(id);
	
	set_task(time, function, id, parameter, len, flags, repeat);
}

bool:RemoveTaskIfExists(id)
{
	if (task_exists(id))
	{
		remove_task(id);
	}
}

/* ==================================================================================================== */