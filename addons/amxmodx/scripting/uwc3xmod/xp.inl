//
// XP Functions 
//

public XP_SetBase_Values ( )
{
	BOMBPLANTXP			= CVAR_BOMB_PLANT_XP_BONUS;
	DEFUSEXP			= CVAR_BOMB_DEFUSE_XP_BONUS;
	HOSTAGEXP			= CVAR_RESCUE_HOSTIES_XP_BONUS;
	KILLRESCUEMANXP			= CVAR_KILL_HOSTIE_RESCUE_BONUS;
	XPBONUS				= CVAR_XP_BONUS;
	KILL_BOMB_CARRIER		= CVAR_BOMB_KILL_XP_BONUS;
	HEADSHOT_BONUS			= CVAR_HEADSHOT_BONUS;
	DEFUSER_KILL_BONUS		= CVAR_DEFUSER_KILL_BONUS;
	VIP_ESCAPE_BONUS		= CVAR_VIP_ESCAPE_XP_BONUS;
	ROUNDXP				= CVAR_ROUND_WIN_XP;
	REPAIRXP			= CVAR_REPAIR_XP;
	SHEILDXP			= CVAR_SHEILD_XP;
	MENDXP				= CVAR_MEND_WOUNDS_XP;
	PHOENIXXP			= CVAR_PHEONIX_XP;
	DISPELLXP			= CVAR_DISPELL_HEX_XP;
	HEALWAVEXP			= CVAR_HEALING_WAVE_XP;
	BLESSXP				= CVAR_BLESS_XP;
}

public XP_SetChoice ( )
{

	if ( CVAR_SAVE_XP )
	{
		XP_UseSaved ( );
	}
	else
	{
		XP_UseFast ( );
	}

	return PLUGIN_CONTINUE;
}

public XP_UseFast ( )
{
	BOMBPLANTXP /= 3;
	DEFUSEXP /= 3;
	HOSTAGEXP /= 3;
	KILLRESCUEMANXP /= 3;
	XPBONUS /= 3;
	KILL_BOMB_CARRIER /= 3;
	HEADSHOT_BONUS /= 3;
	DEFUSER_KILL_BONUS /= 3;
	VIP_ESCAPE_BONUS /= 3;
	ROUNDXP /= 3;
	REPAIRXP /= 1;
	DISPELLXP /= 1;
	MENDXP /= 1;
	PHOENIXXP /= 1;
	SHEILDXP /=1;
	HEALWAVEXP /= 1;
	BLESSXP /=1;

	for ( new j = 0; j < MAX_LEVEL; j++ )
	{
		// Sets the amount of xp needed for next level
		if ( j <= 10 )
		{
			xplevel_lev[j] = xplevel_base[j];
		}
		else
		{
			xplevel_lev[j] = XP_PER_LEVEL_BASE + ( ( j-10 ) * XP_PER_LEVEL );
		}

		// Sets the amount of xp given for each level
		xpgiven_lev[j] = XP_BASE + ( j * XP_ADD_LEVEL );

		if ( CVAR_XP_MULTIPLIER )
		{
			new Float:xpmultiplier = CVAR_XP_MULTIPLIER;
			xplevel_lev[j] = floatround ( xplevel_lev[j] * xpmultiplier );

			// Use additional multipliers for higher levels
			if ( j >= 30 )
			{
				xplevel_lev[j] = floatround ( xplevel_lev[j] * 3.0 );
			}
			else if ( j >= 20 )
			{
				xplevel_lev[j] = floatround ( xplevel_lev[j] * 2.0 );
			}
			else if ( j >= 10 )
			{
				xplevel_lev[j] = floatround ( xplevel_lev[j] * 1.5 );
			}
		}
	}

	// Set the attribute and resistance pt costs ( based on xplevel table )
	attrib_pt_cost = floatround ( ( xplevel_lev[10] / 10 ) * CVAR_ATTRIB_MODIFIER );
	resist_pt_cost = floatround ( ( xplevel_lev[5] / 10 ) * CVAR_RESIST_MODIFIER );

	return PLUGIN_CONTINUE;

}
public XP_UseSaved ( )
{
	BOMBPLANTXP /= 10;
	DEFUSEXP /= 10;
	HOSTAGEXP /= 10;
	KILLRESCUEMANXP /= 10;
	XPBONUS /= 10;
	KILL_BOMB_CARRIER /= 10;
	HEADSHOT_BONUS /= 10;
	DEFUSER_KILL_BONUS /= 10;
	VIP_ESCAPE_BONUS /= 10;
	ROUNDXP /= 10;
	REPAIRXP /= 10;
	DISPELLXP /= 10;
	MENDXP /= 10;
	PHOENIXXP /= 10;
	HEALWAVEXP/= 10;
	SHEILDXP /=10;
	BLESSXP /=10;

	for ( new j=0; j < MAX_LEVEL; j++ )
	{
		// Sets the amount of xp needed for next level
		if ( j <= 10 )
		{
			xplevel_lev[j] = xplevel_base_LT[j];
		}
		else
		{
			xplevel_lev[j] = XP_PER_LEVEL_BASE_LT + ( ( j-10 ) * XP_PER_LEVEL_LT ) + floatround ( float ( j/20 ) * XP_PER_LEVEL_LT );
		}

		// Sets the amount of xp given for each level
		xpgiven_lev[j] = ( XP_BASE + ( j * XP_ADD_LEVEL ) ) / 4;

		if ( CVAR_XP_MULTIPLIER )
		{
			xplevel_lev[j] = floatround ( xplevel_lev[j] * CVAR_XP_MULTIPLIER );

			// [07-11-2004] K2mia - Use additional multipliers for higher levels
			if ( j >= 30 )
			{
				xplevel_lev[j] += floatround ( xplevel_lev[j-1] * 1.25 );
			}
			else if ( j >= 20 )
			{
				xplevel_lev[j] += floatround ( xplevel_lev[j-1] * 1.00 );
			}
			else if ( j >= 10 )
			{
				xplevel_lev[j] += floatround ( xplevel_lev[j-1] * 0.75 );
			}
			else
			{
				if ( j >= 1 )
				{
					xplevel_lev[j] += floatround ( xplevel_lev[j-1] * 0.50 );
				}
			}
		}
	}

	// Set the attribute and resistance pt costs ( based on xplevel table )
	attrib_pt_cost = floatround ( ( xplevel_lev[10] / 10 ) * CVAR_ATTRIB_MODIFIER );
	resist_pt_cost = floatround ( ( xplevel_lev[5] / 10 ) * CVAR_RESIST_MODIFIER );

	return PLUGIN_CONTINUE;
}


public XP_SetMultiplier ( )
{
	if( CVAR_DEBUG_MODE)
	{
		log_amx( "[UWC3X] CVAR_WEAPON_MULTIPLIER=%d", CVAR_WEAPON_MULTIPLIER);
	}

	if ( !CVAR_WEAPON_MULTIPLIER )
	{
		log_amx( "[UWC3X] XP Multiplier Initialized [FAILED] - mp_weaponxpmodifier Cvar not present");
	}
	else
	{
		weaponxpmultiplier[CSW_WORLD]		= 0.0;
		weaponxpmultiplier[CSW_USP]			= 1.0;
		weaponxpmultiplier[CSW_DEAGLE]		= 1.0;
		weaponxpmultiplier[CSW_GLOCK18]		= 2.0;
		weaponxpmultiplier[CSW_ELITE]		= 1.0;
		weaponxpmultiplier[CSW_P228]		= 1.0;
		weaponxpmultiplier[CSW_FIVESEVEN]	= 1.5;

		weaponxpmultiplier[CSW_XM1014]		= 1.25;
		weaponxpmultiplier[CSW_M3]			= 1.5;

		weaponxpmultiplier[CSW_MP5NAVY]		= 1.0;
		weaponxpmultiplier[CSW_UMP45]		= 1.25;
		weaponxpmultiplier[CSW_P90]			= 1.25;
		weaponxpmultiplier[CSW_TMP]			= 1.5;
		weaponxpmultiplier[CSW_MAC10]		= 1.5;

		weaponxpmultiplier[CSW_AWP]			= 1.0;
		weaponxpmultiplier[CSW_M4A1]		= 1.0;
		weaponxpmultiplier[CSW_AK47]		= 1.0;
		weaponxpmultiplier[CSW_AUG]			= 1.0;
		weaponxpmultiplier[CSW_SG552]		= 1.0;
		weaponxpmultiplier[CSW_G3SG1]		= 1.5;
		weaponxpmultiplier[CSW_SG550]		= 1.5;
		weaponxpmultiplier[CSW_M249]		= 1.25;
		weaponxpmultiplier[CSW_SCOUT]		= 2.0;

		weaponxpmultiplier[CSW_HEGRENADE]	= 1.0;
		weaponxpmultiplier[CSW_KNIFE]		= 2.0;

		weaponxpmultiplier[CSW_C4]			= 1.0;
		weaponxpmultiplier[CSW_SMOKEGRENADE]= 1.0;
		weaponxpmultiplier[CSW_FLASHBANG]	= 1.0;
	}
	log_amx( "[UWC3X] XP Multiplier Initialized [OK]");

} 

public XP_ShowTable ( id )
{

	if( Util_Should_Msg_Client(id) )
	{
		client_print_utility ( id, print_console, "%L ^n", id, "UWC3X_XP_TABLE_HEADER" );
		client_print_utility ( id, print_console, "%L ^n", id, "ENH_COST_TABLE", attrib_pt_cost, resist_pt_cost );
	}		

	for ( new j=1; j < MAX_LEVEL; j++ )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L ^n", id, "UWC3X_XP_TABLE", j, ( xplevel_lev[j] - xplevel_lev[j-1] ), xplevel_lev[j] );
		}		
	}

	return PLUGIN_HANDLED;
}


public XP_AdminShowXP ( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	new player = cmd_target2 ( id, arg );

	if ( !player ) 
	{
		return PLUGIN_HANDLED;
	}

	get_user_name ( player, name, 31 );
	if( Util_Should_Msg_Client(id) )
	{
		client_print_utility ( id, print_chat, "%L", id, "ADMIN_SHOWXP", name, playerxp[player] );
	}		
	return PLUGIN_HANDLED;

}

public XP_DeleteXP ( id )
{
	p_level[id] = 0;
	playerxp[id] = 0;

	// Set all skills to 0
	for ( new j=0; j < MAX_SKILLS; j++ )
	{
		p_skills[id][j] = 0;
	}

	// Set all attributes for this player slot to the base amount
	for ( new j=0; j < MAX_ATTRIBS; j++ )
	{
		p_attribs[id][j] = ATTRIB_BASE;
	}

	// Set all resistances for this player slot to 0
	for ( new j=0; j < MAX_RESISTS; j++ )
	{
		p_resists[id][j] = 0;
	}

	resetskill[id] = true;
	resetattrib[id] = true;
	resetresist[id] = true;

	displaylevel ( id,1 );
	if( Util_Should_Msg_Client(id) )
	{
		//client_print_utility ( id, print_chat, "%L", id, "DELETE_XP", MOD );
		hudchat_show(id, "%L", id, "DELETE_XP");
		hudchat_update(id);
	}		

}

public XP_Reload ( id )
{
	if( Util_Should_Msg_Client(id) )
	{
		//client_print_utility( id, print_center, "%L", id, "RELOAD_XP" );
		hudchat_show(id, "%L", id, "RELOAD_XP");
		hudchat_update(id);
	}		
	//xpreadytoload[id] = 1;
	
	//Forces this to load Async 
	LoadXPCommand ( id );
}
public amx_takexp ( id, level )
{

	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_GIVEXP )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], xp[10], name[32], iXP;
	read_argv ( 1, arg, 31 );
	read_argv ( 2, xp, 9 );
	get_user_name ( id, name, 31 );
	iXP = str_to_num ( xp );

	// [9-30-04] Added logging of amx_givexp ( ) command - K2mia
	log_amx( "[UWC3X] %L amx_takexp ( ) %s %s", id, "COMAND_ISSUED", name, arg, xp );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			if( Util_Should_Msg_Client(players[a]) )
			{
				//client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_TAKE_XP", iXP );
				hudchat_show(players[a], "%L", players[a], "ADMIN_TAKE_XP", iXP);
				hudchat_update(players[a]);
			}		
				
			playerxp[players[a]] -= iXP;
			displaylevel ( players[a], 1 );
		}

		return PLUGIN_HANDLED;
	}

	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{
			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			if( Util_Should_Msg_Client(players[a]) )
			{
				//client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_TAKE_XP", iXP );
				hudchat_show(players[a], "%L", players[a], "ADMIN_TAKE_XP", iXP);
				hudchat_update(players[a]);
			}		

			playerxp[players[a]]-= iXP;
			displaylevel ( players[a],1 );
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(id) )
		{
			//client_print_utility ( id, print_chat, "%L", players[a], "ADMIN_TAKE_XP", iXP );
			hudchat_show(id, "%L", id, "ADMIN_TAKE_XP", iXP);
			hudchat_update(id);
		}		
		playerxp[player]-= iXP;
		displaylevel ( player, 1 );
	}

	return PLUGIN_HANDLED;
}

public amx_resetresists( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_RESET )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_resetresists ( ) reset player %s attribs", id, "COMAND_ISSUED", name, arg );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			Reset_Resists ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_RESISTS", MOD );
			}		
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{
			Reset_Resists ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_RESISTS", MOD );
			}		
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		Reset_Resists ( player );
		if( Util_Should_Msg_Client(player) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_RESET_RESISTS", MOD );
		}		
	}

	return PLUGIN_HANDLED;
}
public amx_reseteverything( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_RESET )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_reseteverything ( ) reset player %s attribs", id, "COMAND_ISSUED", name, arg );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			Reset_Resists ( players[a] );
			Reset_Attribs ( players[a] );
			Skills_Reset ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_ALL", MOD );
			}		
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{
			Reset_Resists ( players[a] );
			Reset_Attribs ( players[a] );
			Skills_Reset ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_ALL", MOD );
			}		
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		Reset_Resists ( player );
		Reset_Attribs ( player );
		Skills_Reset ( player );
		if( Util_Should_Msg_Client(player) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_RESET_ALL", MOD );
		}		
	}

	return PLUGIN_HANDLED;

}



public amx_maxresists( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_maxresists ( ) reset player %s resists", id, "COMAND_ISSUED", name, arg );

	new player = cmd_target2 ( id, arg );

	if ( !player ) 
	{
		return PLUGIN_HANDLED;
	}

	for ( new j=0; j<MAX_RESISTS; j++ )
	{
		// Set all resistances to 0
		p_resists[player][j] = RESIST_MAX_VALUE;
	}

	resetresist[player] = false;

	if( Util_Should_Msg_Client(player) )
	{
		client_print_utility ( player, print_chat, "%L", player, "ADMIN_MAX_RESISTS", MOD );
	}		

	return PLUGIN_HANDLED;
}

public amx_maxattribs( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_maxresists ( ) reset player %s resists", id, "COMAND_ISSUED", name, arg );

	new player = cmd_target2 ( id, arg );
	if ( !player ) 
	{
		return PLUGIN_HANDLED;
	}

	for ( new j=0; j<MAX_ATTRIBS; j++ )
	{
		// Set all attributes to the default
		p_attribs[player][j] = ATTRIB_MAX_VALUE;
	}
	
	Set_Wisdom_Bonuses(player);
	resetattrib[player] = false;

	if( Util_Should_Msg_Client(player) )
	{
		client_print_utility ( player, print_chat, "%L", player, "ADMIN_MAX_ATTRIBS", MOD );
	}		

	return PLUGIN_HANDLED;
}


public amx_resetattribs( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_RESET )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_resetattribs ( ) reset player %s attribs", id, "COMAND_ISSUED", name, arg );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			Reset_Attribs ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_ATTRIBS", MOD );
			}		
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{
			Reset_Attribs ( players[a] );
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_ATTRIBS", MOD );
			}		
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		Reset_Attribs ( player );
		if( Util_Should_Msg_Client(player) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_RESET_ATTRIBS", MOD );
		}		
	}

	return PLUGIN_HANDLED;
}

public amx_resetskills( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_RESET )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], name[32];
	read_argv ( 1, arg, 31 );
	get_user_name ( id, name, 31 );

	log_amx( "[UWC3X] %L amx_resetskills ( ) reset player %s skills", id, "COMAND_ISSUED", name, arg );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			Skills_Reset( players[a] );
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_SKILLS", MOD );
			}		
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{
			Skills_Reset( players[a] );
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_RESET_SKILLS", MOD );
			}		
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		Skills_Reset( player );
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_RESET_SKILLS", MOD );
		}		
	}

	return PLUGIN_HANDLED;


}

public amx_setlevel ( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}		
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_SETLEVEL )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}		
		return PLUGIN_HANDLED;
	}

	new arg[32], newlevel[10], name[32], pname[32], iLevel, xp_needed;
	read_argv ( 1, arg, 31 );
	read_argv ( 2, newlevel, 9 );
	get_user_name ( id, name, 31 );
	iLevel = str_to_num ( newlevel );
	xp_needed = xplevel_lev[iLevel];

	log_amx( "[UWC3X] %L amx_setlevel ( ) %s %s", id, "COMAND_ISSUED", name, arg, iLevel );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			get_user_name( players[a], pname, 31 )
			
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_SET_LEVEL", MOD, iLevel );
			}
			
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_chat, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
				client_print_utility ( id, print_console, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
			}		

			playerxp[players[a]] = xp_needed;
			displaylevel ( players[a], 1 );
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}		
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{

			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			get_user_name( players[a], pname, 31 )
			
			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_SET_LEVEL", MOD, iLevel );
			}
			
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_chat, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
				client_print_utility ( id, print_console, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
			}	
			
			playerxp[players[a]]= xp_needed;
			displaylevel ( players[a],1 );
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(player) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_SET_LEVEL", MOD, iLevel );
		}	
		
		get_user_name( player, pname, 31 )
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_chat, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
			client_print_utility ( id, print_console, "%L", id, "ADMIN_SET_LEVEL_RESPONSE", pname, iLevel );
		}	
		playerxp[player] = xp_needed;
		displaylevel ( player, 1 );
	}

	return PLUGIN_HANDLED;

}
public amx_givexp ( id, level )
{
	if ( ! ( get_user_flags ( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if ( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility ( id, print_console, "%L", id, "NO_ACCESS");
			}	
			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_GIVEXP )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility ( id, print_console, "%L", id, "COMMAND_DISABLED" );
		}	
		return PLUGIN_HANDLED;
	}

	new arg[32], xp[10], name[32], iXP;
	read_argv ( 1, arg, 31 );
	read_argv ( 2, xp, 9 );
	get_user_name ( id, name, 31 );
	iXP = str_to_num ( xp );

	// [9-30-04] Added logging of amx_givexp ( ) command - K2mia
	log_amx( "[UWC3X] %L amx_givexp ( ) %s %s", id, "COMAND_ISSUED", name, arg, xp );

	if ( equali ( arg, "@ALL" ) )
	{
		new players[32], inum;
		get_players ( players,inum );

		for ( new a=0;a<inum;++a )
		{
			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_GIVE_XP", MOD, iXP );
			}	
				
			playerxp[players[a]]+= iXP;
			displaylevel ( players[a], 1 );
		}
		return PLUGIN_HANDLED;
	}
	if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players ( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				console_print ( id, "%L", id, "NO_MATCHING_CLIENTS" );
			}	
			return PLUGIN_HANDLED;
		}

		for ( new a=0;a<inum;++a )
		{

			//Dont give levels to bots
			if( is_user_bot(players[a]))
				continue;

			if( Util_Should_Msg_Client(players[a]) )
			{
				client_print_utility ( players[a], print_chat, "%L", players[a], "ADMIN_GIVE_XP", MOD, iXP );
			}	
			playerxp[players[a]]+= iXP;
			displaylevel ( players[a],1 );
		}
	}
	else
	{
		new player = cmd_target2 ( id, arg );

		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(player) )
		{
			client_print_utility ( player, print_chat, "%L", player, "ADMIN_GIVE_XP", MOD, iXP );
		}	
		playerxp[player]+= iXP;
		displaylevel ( player, 1 );
	}

	return PLUGIN_HANDLED;
}