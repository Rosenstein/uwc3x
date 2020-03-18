//	Shared functions will go here, each ultimate will have its
//	own file with its main and supporting functions and methods


// Funtion will check a file to see if the mapname exists
// Added by Yippee Ki Yay Mo and (--eRRoR--)
bool:UWC3X_MapDisableCheck( szFileName[] )
{
	// Format the Orc Nade Disable File
	new szFile[128];
	get_configsdir( szFile, 127 );
	formatex( szFile, 127, "%s/uwc3x/disable/%s", szFile, szFileName );

	if ( !file_exists( szFile ) )
		return false;

	new iLineNum, szData[64], iTextLen, iLen;
	new szMapName[64], szRestrictName[64];
	get_mapname( szMapName, 63 );

	while ( read_file( szFile, iLineNum, szData, 63, iTextLen ) )
	{
		iLen = copyc( szRestrictName, 63, szData, '*' );

		if ( equali( szMapName, szRestrictName, iLen ) )
		{
			return true;
		}

		iLineNum++;
	}

	return false;
}

public cooldown2 ( parm[1] )
{
	new id = parm[0];

	if ( p_skills[id][SKILLIDX_TELEPORT] )
	{
		blinkdelayed[id] = false;
		icon_controller ( id );
	}

	return PLUGIN_CONTINUE;
}

public cooldown4 ( parm[2] )
{
	new id = parm[0];
	new enemy = parm[1];

	if ( p_skills[id][SKILLIDX_DEPOWER] )
	{
		ultimateused[id] = false;
		icon_controller ( id );
		UsedDepower[id] = 0;

		//Tell them they can use it again
		if( is_user_alive ( id ) && is_user_connected(id) && !is_user_bot(id))
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_READY", MOD );
		}
	}

	//If the var is enabled, and they are currently set to cant drop mode, reset it and tell them so
	if( CVAR_DEPOWER_CANT_DROP && BlockPickup[enemy] )
	{
		//Only tell them if they are alive :)
		if( Util_Should_Msg_Client_Alive ( enemy ) )
		{
			new name[32];
			get_user_name ( id, name, 31 );

			//Tell the user they can drop the TMP now :)
			client_print ( enemy, print_chat, "%L", enemy, "ULTIMATE_DEPOWER_WORE_OFF", MOD, name );
			client_print ( enemy, print_center, "%L", enemy, "ULTIMATE_DEPOWER_WORE_OFF", MOD, name );
		}

		BlockPickup[enemy] = false;
	}
	//If the var is enabled, and they are currently set to cant drop mode, reset it and tell them so
	if( CVAR_DEPOWER_CANT_DROP && BlockPickup[id] )
	{
		//Only tell them if they are alive :)
		if( Util_Should_Msg_Client_Alive ( id ) )
		{
			new name[32];
			get_user_name ( id, name, 31 );

			//Tell the user they can drop the TMP now :)
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_WORE_OFF", MOD, name );
			client_print ( id, print_center, "%L", id, "ULTIMATE_DEPOWER_WORE_OFF", MOD, name );
		}

		BlockPickup[id] = false;
	}

	return PLUGIN_CONTINUE;
}

public cooldown3 ( parm[1] )
{
	new id = parm[0];

	if( !is_user_alive( id ) || !is_user_connected( id ) )
	{
		if( task_exists( TASK_COOLDOWN3 + id ) )
		{
			remove_task( TASK_COOLDOWN3 + id );
		}

		return PLUGIN_CONTINUE;
	}

	if ( p_skills[id][SKILLIDX_TEAMSHIELD] )
	{
		ultimateused[id] = false;
		icon_controller ( id );
		UsedTeamShield[id] = 0;
		TeamShieldCooldown[id] = 0;

		//Tell them they can use it again
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_SIV_READY" );
		}

	}

	if( task_exists( TASK_COOLDOWN3 + id ) )
	{
		remove_task( TASK_COOLDOWN3 + id );
	}

	return PLUGIN_CONTINUE;
}

public cooldown ( parm[1] )
{
	new id = parm[0];
	if ( CVAR_RESTRICT_ULTIMATES == 0 )
	{
		ultimateused[id] = false;
		icon_controller ( id );
	}

	return PLUGIN_CONTINUE;
}

public cooldownGrab ( parm[1] )
{
	new id = parm[0];
	ultimateused[id] = false;
	icon_controller ( id );
	return PLUGIN_CONTINUE;
}

public cooldownGate ( parm[1] )
{
	new id = parm[0];
	gateused[id] = false;

	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		client_print( id, print_console, "[%s DEBUG] cooldownGate -> Setting gateused[id] = FALSE for player %s so now there is NO delay", MOD, debugname );
		log_amx( "[UWC3X] DEBUG :: cooldownGate -> Setting gateused[id] = FALSE for player %s so now there is NO delay", debugname );
	}

	ultimateused[id] = false;
	icon_controller ( id );
	return PLUGIN_CONTINUE;
}

public udelay_cooldown ( )
{
	u_delay = false;

	new numplayers, players[32];
	get_players ( players, numplayers );

	for ( new i = 0; i<numplayers; i++ )
	{
		icon_controller ( players[i] );
	}
	return PLUGIN_CONTINUE;
}


public Ult_Can_Use ( id , IDX )
{
	if ( !CVAR_ENABLE_UWC3X )
	{
		return false;
	}

	if( !is_user_alive( id ) )
	{
		if( Util_Should_Msg_Client_Dead(id))
		{
			//client_print ( id, print_chat, "%L", id, "SHHH_DEAD_MESSAGE" );
			hudchat_show(id, "%L", id, "SHHH_DEAD_MESSAGE");
			hudchat_update(id);
		}

		return false;
	}


	if ( freezetime )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "You may not use your ultimate during freezetime" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}

		return false;
	}
	else if( ultimateused[id])
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "Your ultimates are not ready to be used." );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if( !ultlearned[id])
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "You do not have any ultimates trained." );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}

	if ( ismole[id] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "Moles cannot use ultimates" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}

	if ( u_delay )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "Ultimates are disabled for the^nfirst %d seconds of the round", CVAR_ULTIMATE_DELAY );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}





	if ( IDX == SKILLIDX_FSTRIKE && !p_skills[id][SKILLIDX_FSTRIKE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_FLAME_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_TELEPORT && !p_skills[id][SKILLIDX_TELEPORT] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_TELEPORT_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_VOODOO && !p_skills[id][SKILLIDX_VOODOO] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_VOODOO_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_GATE && !p_skills[id][SKILLIDX_GATE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_LIGHTNING && !p_skills[id][SKILLIDX_LIGHTNING] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_LGHTNG_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_DECOY && !p_skills[id][SKILLIDX_DECOY] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_ENTANGLE && !p_skills[id][SKILLIDX_ENTANGLE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_ENTANGLE_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_TEAMSHIELD && !p_skills[id][SKILLIDX_TEAMSHIELD] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_TEAMSHIELD_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_DEPOWER && !p_skills[id][SKILLIDX_DEPOWER] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_LOCUST && !p_skills[id][SKILLIDX_LOCUST] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_LOCUST_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_BLIND && !p_skills[id][SKILLIDX_BLIND] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_BLIND_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_DISORIENT && !p_skills[id][SKILLIDX_DISORIENT] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DISORIENT_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_UAMMO && !p_skills[id][SKILLIDX_UAMMO] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_UAMMO_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_EARTHQUAKE && !p_skills[id][SKILLIDX_EARTHQUAKE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_EARTHQUAKE_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_SMITE && !p_skills[id][SKILLIDX_SMITE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_SMITE_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_HOOK && !p_skills[id][SKILLIDX_HOOK] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_HOOK_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_ROPE && !p_skills[id][SKILLIDX_ROPE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_ROPE_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_GRAB && !p_skills[id][SKILLIDX_GRAB] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GRAB_UNTRAINED" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}
	else if ( IDX == SKILLIDX_SUICIDE && !p_skills[id][SKILLIDX_SUICIDE] )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_WCSUICIDE_UNTRAINED", MOD );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}
		return false;
	}

	if ( endround && ( IDX != SKILLIDX_GATE && IDX != SKILLIDX_TELEPORT ) )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
			show_hudmessage ( id, "You may not use your ultimate after the round is over" );
			emit_sound( id, CHAN_ITEM, "uwc3x/error.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		}

		return false;
	}

	if( CVAR_CRIPPLE_BLOCK_ULTS )
	{
		if( iscrippled[id] )
		{
			if( crippletype[id] == 1 )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print ( id, print_chat, "%L", id, "ULTIMATE_CRIPPLE_ENEMY3", MOD );
				}
				return false;
			}
			if( crippletype[id] == 2 )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print ( id, print_chat, "%L", id, "ULTIMATE_CRIPPLE_ENEMY3", MOD );
				}
				return false;
			}
		}
	}

	if ( IDX == SKILLIDX_GATE )
	{
		if ( numgates[id] == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_NO_MORE", MOD );
			}
			return false;
		}

		if( gateused[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_COOLDOWN", MOD, CVAR_GATE_COOLDOWN2 );
			}

			return false;
		}
	}
	else if ( IDX == SKILLIDX_DECOY )
	{
		if ( decoy[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_ONE", MOD );
			}
			return false;
		}

		if ( decoyused[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_LIMIT", MOD );
			}
			return false;
		}

		if ( skinchanged[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_HEXED", MOD );
			}
			return false;
		}
	}
	else if( IDX == SKILLIDX_TEAMSHIELD )
	{
		if( TeamShieldCooldown[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_TEAMSHIELD_COOLDOWN", MOD, CVAR_TEAMSHIELD_COOLDOWN );
			}
			return false;
		}

		if( UsedTeamShield[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_TEAMSHIELD_ACTIVE", MOD );
			}
			return false;
		}
	}
	else if( IDX == SKILLIDX_DEPOWER )
	{
		if( UsedDepower[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_COOLDOWN", MOD, CVAR_DEPOWER_COOLDOWN );
			}
			return false;
		}
	}
	else if( IDX == SKILLIDX_HOOK )
	{
		if(IsVip[id] && CVAR_HOOK_NOVIP )
		{
			client_print ( id, print_chat, "%L", id, "HOOK_NO_VIP", MOD );
			return false;
		}

		if( CVAR_DEBUG_MODE )
		{
			new debugname[32];
			get_user_name ( id, debugname, 31 );
			client_print( id, print_console, "[%s DEBUG] Ult_Can_Use - HOOK -> Player:%s Hook Count:%d Skill points:%d allowed hooks:%d ", MOD, debugname, HookCount[id],p_skills[id][SKILLIDX_HOOK], p_hooks[p_skills[id][SKILLIDX_HOOK]] );
			log_amx( "[UWC3X] DEBUG :: Ult_Can_Use - HOOK -> Player:%s Hook Count:%d Skill points:%d allowed hooks:%d ", debugname, HookCount[id],p_skills[id][SKILLIDX_HOOK], p_hooks[p_skills[id][SKILLIDX_HOOK]] );
		}

		if(HookCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "HOOK_NONE_LEFT", MOD )
			return false
		}
	}
	else if( IDX == SKILLIDX_GRAB )
	{
		if(IsVip[id] && CVAR_GRAB_NOVIP )
		{
			client_print ( id, print_chat, "%L", id, "GRAB_NO_VIP", MOD );
			return false;
		}

		if( CVAR_DEBUG_MODE )
		{
			new debugname[32];
			get_user_name ( id, debugname, 31 );
			client_print( id, print_console, "[%s DEBUG] Ult_Can_Use - GRAB -> Player:%s GRAB Count:%d Skill points:%d allowed GRABS:%d ", MOD, debugname, GrabCount[id],p_skills[id][SKILLIDX_GRAB], p_grabs[p_skills[id][SKILLIDX_GRAB]] );
			log_amx( "[UWC3X] DEBUG :: Ult_Can_Use - GRAB -> Player:%s GRAB Count:%d Skill points:%d allowed GRABS:%d ", debugname,GrabCount[id],p_skills[id][SKILLIDX_GRAB], p_grabs[p_skills[id][SKILLIDX_GRAB]] );
		}

		if(GrabCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "GRAB_NONE_LEFT", MOD )
			return false
		}
	}
	else if( IDX == SKILLIDX_ROPE )
	{
		if(IsVip[id] && CVAR_ROPE_NOVIP )
		{
			client_print ( id, print_chat, "%L", id, "ROPE_NO_VIP", MOD );
			return false;
		}

		if( CVAR_DEBUG_MODE )
		{
			new debugname[32];
			get_user_name ( id, debugname, 31 );
			client_print( id, print_console, "[%s DEBUG] Ult_Can_Use - ROPE -> Player:%s ROPE Count:%d Skill points:%d allowed ROPES:%d ", MOD, debugname, RopeCount[id],p_skills[id][SKILLIDX_ROPE], p_ropes[p_skills[id][SKILLIDX_ROPE]] );
			log_amx( "[UWC3X] DEBUG :: Ult_Can_Use - ROPE -> Player:%s ROPE Count:%d Skill points:%d allowed ROPES:%d ", debugname,RopeCount[id],p_skills[id][SKILLIDX_ROPE], p_ropes[p_skills[id][SKILLIDX_ROPE]] );
		}

		if(RopeCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "ROPE_NONE_LEFT", MOD )
			return false
		}
	}

	return true;

}

public Ult_TooMany( id )
{
	if( p_maxultimates[id] < Get_Ult_Count( id ) )
		return true;

	return false;
}

public Ult_CanTrain( id )
{
	if( p_maxultimates[id] > Get_Ult_Count( id ) )
		return true;

	return false;
}

public Get_Ult_Count( id )
{

	new count = 0;

	for ( new j = 1; j < MAX_SKILLS; j++ )
	{
		if( skill_ultimates[j][0] && p_skills[id][j] )
		{
			count++;
		}
	}

	return count;
}


public Set_Ult_Count( id )
{
	new count = 0;
	for ( new j = 1; j < MAX_SKILLS; j++ )
	{
		if( skill_ultimates[j][0] && p_skills[id][j] )
		{
			count++;
		}
	}

	ultlearned[id]=count;
	if( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: Set_Ult_Count -> ultlearned[id] = %d", ultlearned[id] );
	}
}

/* Chain Lightning */
public Ult_ChainLightning ( id )
{
	if ( !Ult_Can_Use ( id , SKILLIDX_LIGHTNING ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "lightning.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_LIGHTNING_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	if ( !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_CHAIN_Search ( parm );
	}

	return PLUGIN_HANDLED;
}

/* Gate */
public Ult_Gate ( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_GATE ) )
	{
		return PLUGIN_HANDLED;
	}

	// Call the front end to the gate routine
	Do_Gate ( id );

	return PLUGIN_HANDLED;

}

public Do_Gate_Shopmenu( id )
{
	new numplayers = 0;
	new Float:vicinity = 96.0;
	new entsFound[1];
	new Float:origin[3];
	new porigin[3];
	new szEnt[32];
	new bool:spotOpen = false;
	new team = get_user_team ( id );

	if ( team == TEAM_T )
	{
		copy ( szEnt, 31, "info_player_deathmatch" );
	}
	else if ( team == TEAM_CT )
	{
		copy ( szEnt, 31, "info_player_start" );
	}
	else
	{
		//SPEC
		return PLUGIN_HANDLED;
	}

	//Cant grab some one gating
	grab[id]=0;

	//Cant be grabbed when gated
	Remove_Grab( id );	
	
	new curEnt = find_ent_by_class ( -1, szEnt );

	while ( curEnt > 0 )
	{
		numplayers = 0;

		entity_get_vector ( curEnt, EV_VEC_origin, origin );
		numplayers = find_sphere_class ( 0, "player", vicinity, entsFound, 1, origin );

		if ( numplayers == 0 )
		{
			spotOpen = true;
			break;
		}

		curEnt = find_ent_by_class ( curEnt, szEnt );
	}

	if ( spotOpen )
	{
		porigin[0] = floatround ( origin[0] );
		porigin[1] = floatround ( origin[1] );
		porigin[2] = floatround ( origin[2] );

		new parm2[6];
		parm2[0] = porigin[0];
		parm2[1] = porigin[1];
		parm2[2] = porigin[2];
		parm2[3] = 0;
		parm2[4] = team;
		parm2[5] = id;

		set_task ( 0.1, "Task_Gate_User_Shopmenu", 2, parm2, 7 );

		// [09-05-04] - Display gate sprite ( tele ) 1 cycle
		new idorigin[3];
		get_user_origin ( id, idorigin );
		Remove_Grab( id );	

		message_begin ( MSG_ALL, SVC_TEMPENTITY );
		write_byte ( TE_SPRITE );
		write_coord ( idorigin[0] );
		write_coord ( idorigin[1] );
		write_coord ( idorigin[2] );
		write_short ( gatespr );
		write_byte ( 10 );
		write_byte ( 255 );
		message_end ( );
	}
	else
	{
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_FAILED", MOD );
		}

	}

	return PLUGIN_HANDLED;

}

public Do_Gate ( id )
{
	new numplayers = 0;
	new Float:vicinity = 96.0;
	new entsFound[1];
	new Float:origin[3];
	new porigin[3];
	new szEnt[32];
	new bool:spotOpen = false;
	new team = get_user_team ( id );

	if ( team == TEAM_T )
	{
		copy ( szEnt, 31, "info_player_deathmatch" );
	}
	else if ( team == TEAM_CT )
	{
		copy ( szEnt, 31, "info_player_start" );
	}
	else
	{
		//SPEC
		return PLUGIN_HANDLED;
	}
	
	//Cant grab some one gating
	grab[id]=0;

	//Cant be grabbed when gated
	Remove_Grab( id );	

	new curEnt = find_ent_by_class ( -1, szEnt );

	while ( curEnt > 0 )
	{
		numplayers = 0;

		entity_get_vector ( curEnt, EV_VEC_origin, origin );
		numplayers = find_sphere_class ( 0, "player", vicinity, entsFound, 1, origin );

		if ( numplayers == 0 )
		{
			spotOpen = true;
			break;
		}

		curEnt = find_ent_by_class ( curEnt, szEnt );
	}

	if ( spotOpen )
	{
		porigin[0] = floatround ( origin[0] );
		porigin[1] = floatround ( origin[1] );
		porigin[2] = floatround ( origin[2] );

		new parm2[6];
		parm2[0] = porigin[0];
		parm2[1] = porigin[1];
		parm2[2] = porigin[2];
		parm2[3] = 0;
		parm2[4] = team;
		parm2[5] = id;

		set_task ( 0.1, "Task_Gate_User", 2, parm2, 6 );

		// [09-05-04] - Display gate sprite ( tele ) 1 cycle
		new idorigin[3];
		get_user_origin ( id, idorigin );

		message_begin ( MSG_ALL, SVC_TEMPENTITY );
		write_byte ( TE_SPRITE );
		write_coord ( idorigin[0] );
		write_coord ( idorigin[1] );
		write_coord ( idorigin[2] );
		write_short ( gatespr );
		write_byte ( 10 );
		write_byte ( 255 );
		message_end ( );
	}
	else
	{
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_FAILED", MOD );
		}
	}

	return PLUGIN_HANDLED;

}




/* FLAMESTRIKE */
public Ult_FlameStrike ( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_FSTRIKE ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !ultimateused[id] )
	{
		//Flame Strike
		Do_FlameThrower ( id );
		flame_count[id]++;

		if ( flame_count[id] > 5 )
		{
			ultimateused[id] = true;
			icon_controller ( id );
			flame_count[id] = 0;
		}
	}

	return PLUGIN_HANDLED;
}

public Do_FlameThrower ( id )
{
	if( Util_Should_Msg_Client_Alive( id ) )
	{
		if ( file_exists ( "sound/uwc3x/flamestrike.wav" ) )
		{
			emit_sound ( id, CHAN_WEAPON, "uwc3x/flamestrike.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}

	new vec[3], aimvec[3], length, velocityvec[3];
	new speed = 10;
	get_user_origin ( id, vec );
	get_user_origin ( id, aimvec, 2 );
	new dist = get_distance ( vec, aimvec );

	if ( flame_count[id] == 1 )
	{
		new parm[1];
		parm[0] = id;
		set_task ( CVAR_FLAME_COOLDOWN, "cooldown", TASK_COOLDOWN_RESET + id, parm, 1 );
	}
	new speed1 = 160;
	new speed2 = 350;
	new radius = 105;

	if ( dist < 50 )
	{
		radius = 0;
		speed = 5;
	}
	else if ( dist < 150 )
	{
		speed1 = speed2 = 1;
		speed = 5;
		radius = 50;
	}
	else if ( dist < 200 )
	{
		speed1 = speed2 = 1;
		speed = 5;
		radius = 90;
	}
	else if ( dist < 250 )
	{
		speed1 = speed2 = 90;
		speed = 6;
		radius = 90;
	}
	else if ( dist < 300 )
	{
		speed1 = speed2 = 140;
		speed = 7;
	}
	else if ( dist < 350 )
	{
		speed1 = speed2 = 190;
		speed = 7;
	}
	else if ( dist < 400 )
	{
		speed1 = 150;
		speed2 = 240;
		speed = 8;
	}
	else if ( dist < 450 )
	{
		speed1 = 150;
		speed2 = 290;
		speed = 8;
	}
	else if ( dist < 500 )
	{
		speed1 = 180;
		speed2 = 340;
		speed = 9;
	}

	velocityvec[0]= aimvec[0]-vec[0];
	velocityvec[1]= aimvec[1]-vec[1];
	velocityvec[2]= aimvec[2]-vec[2];
	length = sqrt ( velocityvec[0] * velocityvec[0] + velocityvec[1] * velocityvec[1] + velocityvec[2] * velocityvec[2] );
	velocityvec[0]= velocityvec[0] * speed/length;
	velocityvec[1]= velocityvec[1] * speed/length;
	velocityvec[2]= velocityvec[2] * speed/length;

	new args[8];
	args[0] = vec[0];
	args[1] = vec[1];
	args[2] = vec[2];
	args[3] = velocityvec[0];
	args[4] = velocityvec[1];
	args[5] = velocityvec[2];
	set_task ( 0.1, "Task_FlameStrike_Spray", TASK_FLAMESTRIKE_SPRAY, args, 8, "a", 2 );
	TASK_Check_BurnZone ( id, vec, aimvec, speed1, speed2, radius );
}

public FS_Should_Burn_Victim ( origin[3], burnvec1[3], burnvec2[3], radius, i, id, ff )
{
	if ( ( is_user_alive ( i ) ) && (i != id ) )
	{
		if ( ( get_distance ( origin, burnvec1 ) < radius ) || ( get_distance ( origin, burnvec2 ) < radius ) )
		{
			if (CVAR_DEBUG_MODE)
			{
				log_amx("[UWC3X] FS_Should_Burn_Victim :: isburning - %d", isburning[id]);
			}
			
			TASK_Burn_Victim ( i, id, ff );
		}
	}
}

/* Suicide Bomber */
public Ult_Suicide_Bomber ( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_SUICIDE ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "suicide.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_SUICIDE_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) )
	{
		if ( CVAR_WARN_SUICIDE )
		{
			if ( suicideAttempt[id] )
			{
				if( Util_Is_Valid_Player( id ) && is_user_alive( id ) )
				{
					user_kill ( id,1 );
				}
			}
			else
			{
				new parm[1];
				parm[0] = id;
				icon_controller ( id );
				suicideAttempt[id] = 1;

				if( Util_Should_Msg_Client_Alive( id ) )
				{
					set_hudmessage ( 178, 14, 41, -1.0, -0.4, 1, 0.5, 1.7, 0.2, 0.2, 5 );
					show_hudmessage( id , "%L", id, "ULTIMATE_WCSUICIDE_ARMED" );

					if ( file_exists ( "sound/uwc3x/suicide_charging.wav" ) == 1 )
					{
						emit_sound( id, CHAN_AUTO, "uwc3x/suicide_charging.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}					
				}

			}
		}
		else
		{
			if( Util_Is_Valid_Player( id ) && is_user_alive( id ) )
			{
				user_kill ( id,1 );
			}
		}
	}

	return PLUGIN_HANDLED;
}


/* Teleport */
public Ult_Teleport ( id )
{

	if ( !Ult_Can_Use ( id , SKILLIDX_TELEPORT ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "teleport.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_TELEPORT_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}


	if ( is_user_alive ( id ) && !ultimateused[id] )
	{
		if ( CVAR_BLINK_ENABLED != 0 )
		{

			new oldLocation[3];
			new newLocation[3];
			new parm[3];
			parm[0] = id;

			if ( CVAR_BLINK_DIZINESS == 2 )
			{
				if( Util_Should_Msg_Client(id) )
				{
					// This will cause Teleportation Blueness
					message_begin ( MSG_ONE, gmsgFade, {0,0,0}, id ); // use the magic #1 for "one client"
					write_short ( 1<<12 ); // fade lasts this long duration
					write_short ( 1<<8 ); // fade lasts this long hold time
					write_short ( FFADE_IN ); // fade type IN
					write_byte ( 76 ); // fade red
					write_byte ( 163 ); // fade green
					write_byte ( 223 ); // fade blue
					write_byte ( 200 ); // fade alpha
					message_end ( );
				}
			}

			get_user_origin ( id, oldLocation );

			// Makes sure nearby enemy doesn't have immunity
			new teamname[32], players[32], numplayers, targetorigin[3], targetid;
			get_user_team ( id, teamname, 31 );
			get_players ( players, numplayers );

			new idname[32];
			get_user_name ( id, idname, 31 );

			for ( new i = 0; i < numplayers; ++i )
			{
				targetid = players[i];

				if ( get_user_team ( id ) == get_user_team ( targetid ) || get_user_team ( targetid ) == SPEC || !is_user_alive ( targetid ) )
				{
					continue;
				}

				if ( Util_IsPlayer_Immune ( id , 2 ) )
				{
					get_user_origin ( targetid, targetorigin );

					if ( get_distance ( oldLocation, targetorigin ) <= CVAR_BLINK_RADIUS )
					{
						if( Util_Should_Msg_Client_Alive( id ))
						{
							set_hudmessage ( 255, 255, 10, -1.0, -0.4, 1, 0.5, CVAR_BLINK_COOLDOWN, 0.2, 0.2,5 );
							show_hudmessage( id , "%L", LANG_PLAYER, "ULTIMATE_TELEPORT_IMMUNITY" );
						}

						new coolparm[1];
						coolparm[0] = id;

						set_task ( CVAR_TELEPORT_COOLDOWN, "cooldown", 50 + id, coolparm, 1 );

						if( Util_Should_Msg_Client_Alive( id ) )
						{
							if ( file_exists ( "sound/uwc3x/teleport.wav" ) )
							{
								emit_sound ( id,CHAN_STATIC, "uwc3x/teleport.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
							}
						}

						return PLUGIN_HANDLED;
					}
				}
			}
		  // END Makes sure nearby enemy doesn't have immunity


		  // Make sure it doesn't teleport you back into the ground.
			oldLocation[2] += 30;
			savedOldLoc[id] = oldLocation;
			get_user_origin ( id, newLocation, 3 );
			if ( ( newLocation[0] - oldLocation[0] ) > 0 )
			{
				newLocation[0] -= 50;
			}
			else
			{
				newLocation[0] += 50;
			}

			if ( ( newLocation[1] - oldLocation[1] ) > 0 )
			{
				newLocation[1] -= 50;
			}
			else
			{
				newLocation[1] += 50;
			}

			newLocation[2] += 40;

			savedNewLoc[id] = newLocation;

			if( Util_Should_Msg_Client_Alive( id ) )
			{
				if ( file_exists ( "sound/uwc3x/teleport.wav" ) )
				{
					emit_sound ( id,CHAN_STATIC, "uwc3x/teleport.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}

			// blast circles
			message_begin ( MSG_PAS, SVC_TEMPENTITY, oldLocation );
			write_byte ( TE_BEAMCYLINDER );
			write_coord ( oldLocation[0] );
			write_coord ( oldLocation[1] );
			write_coord ( oldLocation[2] + 10 );
			write_coord ( oldLocation[0] );
			write_coord ( oldLocation[1] );
			write_coord ( oldLocation[2] + 10 + TELEPORT_RADIUS );
			write_short ( m_iSpriteTexture );
			write_byte ( 0 ); // startframe
			write_byte ( 0 ); // framerate
			write_byte ( 3 ); // life
			write_byte ( 60 ); // width
			write_byte ( 0 ); // noise
			write_byte ( 255 ); // red
			write_byte ( 255 ); // green
			write_byte ( 255 ); // blue
			write_byte ( 255 ); //brightness
			write_byte ( 0 ); // speed
			message_end ( );

			// Stop bomb planting...
			client_cmd ( id,"-use" );
			
			//Cant grab some one teleporting
			grab[id]=0;

			//Cant be grabbed when teleporting
			Remove_Grab( id );	

			if ( CVAR_BLINK_PROTECTION )
			{
				new mapname[32];
				get_mapname ( mapname,32 );
				if ( equali ( mapname, "as_oilrig" ) )
				{
					if ( newLocation[0] > 1530 && get_user_team ( id ) == TEAM_CT )
					{
						client_cmd ( id, "kill" );
						if( Util_Should_Msg_Client_Alive( id ) )
						{
							client_print ( id, print_chat, "%L", id, "ULTIMATE_TELEPORT_SLAY", MOD );
						}
						return PLUGIN_HANDLED;
					}
				}
			}

			// Test sending player, should work most of the time.
			set_user_origin ( id, newLocation );
			new Float:PlayerOrigin[3];
			entity_get_vector ( id, EV_VEC_origin, PlayerOrigin );

			if ( CVAR_BLINK_PROTECTION )
			{
				set_task ( 1.5, "TASK_OOB_Check", TASK_OUT_OF_BOUNDS_CHECK+id, parm, 2 );
			}

			// Check if Blink laned you in a wall, if so, abort
			parm[1] = 1;

			set_task ( 0.1, "Task_Blink_Controller", TASK_BLINK_CONTROLLER, parm, 2 );

			ultimateused[id] = true;
			icon_controller ( id );

			if ( file_exists ( "sound/uwc3x/teleport.wav" ) )
			{
				emit_sound ( id,CHAN_ITEM, "uwc3x/teleport.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}

			message_begin ( MSG_PAS, SVC_TEMPENTITY, newLocation );
			write_byte ( TE_BEAMCYLINDER );
			write_coord ( newLocation[0] );
			write_coord ( newLocation[1] );
			write_coord ( newLocation[2] + 90 );
			write_coord ( newLocation[0] );
			write_coord ( newLocation[1] );
			write_coord ( newLocation[2] + 90 + TELEPORT_RADIUS );
			write_short ( m_iSpriteTexture );
			write_byte ( 0 ); // startframe
			write_byte ( 0 ); // framerate
			write_byte ( 3 ); // life
			write_byte ( 60 ); // width
			write_byte ( 0 ); // noise
			write_byte ( 255 ); // red
			write_byte ( 255 ); // green
			write_byte ( 255 ); // blue
			write_byte ( 255 ); //brightness
			write_byte ( 0 ); // speed
			message_end ( );
		}
		else
		{
			new i, j, tmp, numberofplayers;
			new distancebetween, distancebetween2, targetid, targetid2;
			new origin[3], targetorigin[3], targetorigin2[3], teamname[32];
			get_user_team ( id, teamname, 31 );

			//get_players ( teleportid[id],numberofplayers,"ae",teamname )
			get_players ( teleportid[id],numberofplayers );
			get_user_origin ( id,origin );

			for ( i=0; i<numberofplayers; i++ )
			{
				// Sort by closest to furthest
				for ( j=i+1; j<numberofplayers; j++ )
				{
					targetid = teleportid[id][i];

					if ( get_user_team ( id ) != get_user_team ( targetid ) )
					{
						continue;
					}

					get_user_origin ( targetid, targetorigin );
					distancebetween = get_distance ( origin, targetorigin );
					targetid2 = teleportid[id][j];
					get_user_origin ( targetid2, targetorigin2 );
					distancebetween2 = get_distance ( origin, targetorigin2 );
					if ( distancebetween2 < distancebetween && targetid2 != id )
					{
						// Don't put self first
						tmp = teleportid[id][i];
						teleportid[id][i] = teleportid[id][j];
						teleportid[id][j] = tmp;
					}
					else if ( targetid==id )
					{
						// Put self last
						tmp = teleportid[id][i];
						teleportid[id][i] = teleportid[id][j];
						teleportid[id][j] = tmp;
					}
				}
			}

			if ( numberofplayers > 9 )
			{
				numberofplayers = 9;
			}
			else
			{
				// Remove self from list
				--numberofplayers;
			}

			if ( numberofplayers )
			{
				remove_task ( TASK_MENU_TELEPORT+id );
				teleportmenu[id] = true;
				new menuparm[2];
				menuparm[0] = id;
				menuparm[1] = numberofplayers;
				Menu_Teleport ( menuparm );
			}
			else
			{
				if( Util_Should_Msg_Client_Alive( id ) )
				{
					set_hudmessage ( 178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5 );
					show_hudmessage ( id, "No valid targets found!" );
				}
			}
		}
	}

	return PLUGIN_HANDLED;

}

/* VooDoo */
public Ult_VooDoo ( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_VOODOO) )
	{
		return PLUGIN_HANDLED;
	}

	if ( !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = 3;

		godshealth[id] = get_user_health ( id );
		hasgodmode[id] = true;

		set_user_health_log ( id, get_user_health ( id ) + 2048 );

		new Float:fTime = 5.0;
		new iByte = 4;

		if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_INT] >= INT_MASTER_LEVEL ) )
		{
			iByte = 4;
			fTime = 5.0;
		}
		else
		{
			fTime = 3.0;
			iByte = 2;
		}

		set_task ( fTime, "Task_Reset_Godmode", TASK_RESET_GODMODE + id, parm, 2 );

		if( Util_Should_Msg_Client(id) )
		{
			message_begin ( MSG_ONE, 108, { 0, 0, 0 }, id );

			// Bar ( thanks to bad-at-this )
			// duration
			write_byte ( iByte );

			// duration
			write_byte ( 0 );

			message_end ( );
		}

		if( Util_Should_Msg_Client_Alive( id ) )
		{
			if ( file_exists ( "sound/uwc3x/divineshield.wav" ) == 1 )
			{
				emit_sound ( id, CHAN_STATIC, "uwc3x/divineshield.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}

		ultimateused[id] = true;
		icon_controller ( id );
	}

	return PLUGIN_HANDLED;

}

//TeamShield
public Ult_TeamShield ( id )
{
	//protect_id = id of player to protect
	//user_is is the ID of the player who gets the damage

	if ( !Ult_Can_Use ( id, SKILLIDX_TEAMSHIELD) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{

		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_SHIELD_Search ( parm );
		//set_task ( 0.1, "TASK_SHIELD_Search", TASK_ULTIMATE_SHIELD_SEARCH + id, parm, 2 );
	}

	return PLUGIN_CONTINUE;
}

/* Entengle roots */
public Ult_Entangle ( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_ENTANGLE ) )
	{
		return PLUGIN_HANDLED;
	}
	if ( is_user_alive ( id ) && Util_Is_Valid_Player( id ) )
	{
		if( !issearching[id] && !ultimateused[id] )
		{
			new parm[2];
			parm[0] = id;
			parm[1] = ULTIMATESEARCHTIME;
			searchtarget ( parm );
		}
	}
	return PLUGIN_CONTINUE;
}

/* Decoy */
public Ult_Decoy ( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_DECOY ) )
	{
		return PLUGIN_HANDLED;
	}

	new sClass[32], target, body, cargs[2];
	new arg[64], vec[3], aimvec[3];
	new Float:arg2[3];
	new Float:b_orig[3];
	new model[32], pmodel[128];
	new decoyEnt = create_entity ( "info_target" );

	get_user_origin ( id, vec );
	get_user_origin ( id, aimvec, 2 );

	// [07-20-04] - Fix for people spawning decoys on other players to trap them
	get_user_aiming ( id, target, body );

	//formerly ( 0 < target <= MAX_PLAYERS )
	if ( Util_Is_Valid_Player( target) )
	{
		entity_get_string ( target, EV_SZ_classname, sClass, 32 );
		if ( equal ( sClass, "player" ) )
		{
			if( Util_Should_Msg_Client_Alive( id ) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_PLAYER", MOD );
			}

			return PLUGIN_HANDLED;
		}
	}

	b_orig[0] = float ( aimvec[0] );
	b_orig[1] = float ( aimvec[1] );
	b_orig[2] = float ( aimvec[2] + 35 );

	entity_get_string ( id, EV_SZ_classname, arg, 63 );
	entity_set_string ( decoyEnt, EV_SZ_classname, "decoy_entity" );
	entity_set_origin ( decoyEnt, b_orig );

	entity_set_byte ( decoyEnt, EV_BYTE_controller1, 127 );

	entity_get_vector ( id, EV_VEC_absmin, arg2 );
	entity_set_vector ( decoyEnt, EV_VEC_absmin, arg2 );

	entity_get_vector ( id, EV_VEC_absmax, arg2 );
	entity_set_vector ( decoyEnt, EV_VEC_absmax, arg2 );

	entity_get_vector ( id, EV_VEC_mins, arg2 );
	entity_set_vector ( decoyEnt, EV_VEC_mins, arg2 );

	entity_get_vector ( id, EV_VEC_maxs, arg2 );
	entity_set_vector ( decoyEnt, EV_VEC_maxs, arg2 );

	entity_get_vector ( id, EV_VEC_size, arg2 );
	entity_set_vector ( decoyEnt, EV_VEC_size, arg2 );

	// [10-08-04] Check for Goombah before setting decoy skin - K2mia
	if ( skinchanged[id] )
	{
		format ( pmodel, 127, "models/player/zombie/zombie.mdl" );
	}
	else
	{
		get_user_info ( id, "model", model, 31 );
		format ( pmodel, 127, "models/player/%s/%s.mdl", model, model );
	}

	entity_set_model ( decoyEnt, pmodel );

	entity_set_float ( decoyEnt, EV_FL_health,99999200.0 );
	entity_set_float ( decoyEnt, EV_FL_takedamage, 1.0 );
	entity_set_float ( decoyEnt, EV_FL_dmg_take, 1.0 );

	entity_set_int ( decoyEnt, EV_INT_movetype, 13 );
	entity_set_int ( decoyEnt, EV_INT_solid, 2 );
	entity_set_int ( decoyEnt, EV_INT_spawnflags, 0 );
	entity_set_int ( decoyEnt, EV_INT_sequence, 1 );

	decoy[id] = decoyEnt;
	decoy_frame[id] = 0.0;
	decoy_seq[id] = 0;
	decoyused[id] = true;

	cargs[0] = id;
	cargs[1] = decoyEnt;
	set_task ( 15.0, "TASK_Cleanup_Decoy", TASK_CLEANUP_DECOY, cargs, 2 );

	return PLUGIN_CONTINUE;
}



/* DEPOWER */
public Ult_DePower( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_DEPOWER ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "depower.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] && !UsedDepower[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_DEPOWER_Search ( parm );
	}

	return PLUGIN_HANDLED;
}
public Ult_DEPOWER_REPLACE_GUNS ( id )
{
	if( id == 0)
		return PLUGIN_CONTINUE;

	new wpnList[32] = 0;
	new number = 0;
	new wpname[32];

	get_user_weapons( id , wpnList , number );

	for ( new i = 0; i < number; i++)
	{
		//Skip pistols, grenades, knife - only go for primary weapons
		if ( !IsWeaponPrimary( wpnList[i] ) )
		{
			continue;
		}

		//Get the weapon name
		get_weaponname( wpnList[i] , wpname , 31 );

		//and make them drop it
		engclient_cmd( id , "drop" , wpname );

	}

	give_item( id , "weapon_tmp" );
	give_item( id , "ammo_9mm" );

	return PLUGIN_CONTINUE;
}

//Pass in the ID of the user DOING the damage (enemy) and it will return the Cripple type
public Ult_Cripple( id )
{
	//Make sure they have the skill first
	if ( p_skills[id][SKILLIDX_CRIPPLE] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber <= CVAR_CRIPPLE_CHANCE1 )
		{
			return 1;
		}
		else if( randomnumber <= CVAR_CRIPPLE_CHANCE2 )
		{
			return 2;
		}
	}

	return 0;

}

/* Smite */
public Ult_Smite( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_SMITE ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( UWC3X_MapDisableCheck( "smite.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_SMITE_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}
	
	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_Smite_Search ( parm );
	}

	return PLUGIN_HANDLED;

}

/* Earth Quake */
public Ult_EarthQuake( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_EARTHQUAKE ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "earthquake.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_EARTHQUAKE_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_EarthQuake_Search ( parm );
	}

	return PLUGIN_HANDLED;
}


/*Locust Swarm */
public Ult_Locust(id)
{

	if ( !Ult_Can_Use ( id, SKILLIDX_LOCUST ) )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( UWC3X_MapDisableCheck( "swarm.cfg" ) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_SWARM_DISABLED", MOD );
		emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		if( Util_Should_Msg_Client_Alive( id )  )
		{
			set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
			show_hudmessage(id,"Searching for player(s)...");
		}

		Task_locust_function(id);
	}

	return PLUGIN_HANDLED;
}

/* Flash of Light */
public Ult_Flash( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_BLIND ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		Task_Search_Flash( parm );
	}

	return PLUGIN_HANDLED
}

public Ult_UnlimitedAmmo( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_UAMMO ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);

		Task_Switch_UnlimitedAmmoOn( id );

		new barTime = floatround( CVAR_UNLIMITED_AMMO_TIME );

		if( Util_Should_Msg_Client(id) )
		{
			message_begin ( MSG_ONE, 108, { 0, 0, 0 }, id );

			// Bar ( thanks to bad-at-this )
			// duration
			write_byte ( barTime );

			// duration
			write_byte ( 0 );

			message_end ( );
		}

		new parm[1];
		parm[0] = id;
		set_task ( CVAR_UNLIMITED_AMMO_TIME, "Task_Switch_UnlimitedAmmoOff", TASK_RESET_AMMO_ID + id, parm, 1 );

	}

	return PLUGIN_HANDLED
}


public Ult_BadAim( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_DISORIENT ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		Task_Search_BadAim( parm );
	}

	return PLUGIN_HANDLED
}

public Ult_FireBall(id)
{
	if ( !Ult_Can_Use ( id, SKILLIDX_DISORIENT ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		Task_Do_FireBall( parm );
	}

	return PLUGIN_HANDLED
}

public Task_Do_FireBall( parm[] )
{

	new id = parm[1];

	if ( is_user_alive(id))
	{

		new Float:vOrigin[3];
		new fEntity;
		entity_get_vector(id,EV_VEC_origin, vOrigin);
		fEntity = create_entity("info_target");
		entity_set_model(fEntity, "models/rpgrocket.mdl");
		entity_set_origin(fEntity, vOrigin);
		entity_set_int(fEntity,EV_INT_effects,64);
		entity_set_string(fEntity,EV_SZ_classname,"fireball");
		entity_set_int(fEntity,EV_INT_movetype,5);
		entity_set_edict(fEntity,EV_ENT_owner,id);

		//Send forward
		new Float:fl_iNewVelocity[3];
		VelocityByAim(id, 400, fl_iNewVelocity);
		entity_set_vector(fEntity, EV_VEC_velocity, fl_iNewVelocity);

		message_begin(MSG_BROADCAST, SVC_TEMPENTITY);
		write_byte(22);
		write_short(fEntity);
		write_short(sprite_beam);
		write_byte(45);
		write_byte(4);
		write_byte(255);
		write_byte(0);
		write_byte(0);
		write_byte(25);
		message_end();
	}
	return PLUGIN_HANDLED;

}















//ROPE
public Ult_Rope( id )
{
	if(rope[id])
	{
		rope_off(id);
	}
	else
	{
		rope_on(id);
	}

	return PLUGIN_HANDLED;
}


public rope_on(id)
{

	if ( !Ult_Can_Use ( id, SKILLIDX_ROPE ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] && !rope[id] )
	{
		icon_controller ( id );
		ultimateused[id] = true;

		set_task(0.1,"rope_prethink",id+100000,"",0,"b");
		rope[id]=true;
		rope_to[id][0]=999999;
		rope_prethink(id+100000);

		if( Util_Should_Msg_Client(id) )
		{
			if ( file_exists ( "sound/uwc3x/xbow_hit2.wav" ) == 1 )
			{
				emit_sound(id,CHAN_STATIC,"uwc3x/xbow_hit2.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
			}
		}

		RopeCount[id] = (RopeCount[id] -1);

		if( RopeCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "ROPE_NONE_LEFT", MOD )
			return PLUGIN_HANDLED;
		}
		else
		{
			if( CVAR_DEBUG_MODE )
			{
				new debugname[32];
				get_user_name ( id, debugname, 31 );
				log_amx( "[UWC3X] DEBUG :: rope_on -> player %s  RopesLeft=%d", debugname, RopeCount[id] );
			}

			if( RopeCount[id] == 0 )
			{
				client_print( id ,print_chat, "%L", id, "ROPE_NONE_LEFT", MOD );
			}
			else
			{
				client_print(id,print_chat, "%L", id, "ROPE_COUNT", MOD, RopeCount[id]);
			}
		}

	}

	return PLUGIN_HANDLED;
}

public rope_off(id)
{
	rope[id]=false;
	ultimateused[id] = false;
	return PLUGIN_HANDLED;
}

public rope_prethink(id)
{
	id -= 100000;
	if(!is_user_alive(id))
	{
		rope[id]=false;
	}

	if(!rope[id])
	{
		remove_task(id+100000);
		return PLUGIN_HANDLED;
	}

	//Get Id's origin
	static origin1[3];
	get_user_origin(id,origin1);

	static Float:origin1_F[3];
	origin1_F[0] = float(origin1[0]);
	origin1_F[1] = float(origin1[1]);
	origin1_F[2] = float(origin1[2]);

	//Check to see if this is the first time prethink is being run
	if(rope_to[id][0]==999999)
	{
		static origin2[3];
		get_user_origin(id,origin2,3);
		rope_to[id][0]=origin2[0];
		rope_to[id][1]=origin2[1];
		rope_to[id][2]=origin2[2];

		static Float:origin2_F[3];
		origin2_F[0] = float(origin2[0]);
		origin2_F[1] = float(origin2[1]);
		origin2_F[2] = float(origin2[2]);

		static Float:distance[3];
		distance[0] = floatabs(origin1_F[0] - origin2_F[0]);
		distance[1] = floatabs(origin1_F[1] - origin2_F[1]);
		distance[2] = floatabs(origin1_F[2] - origin2_F[2]);
		rope_totaldis[id] = floatsqroot(distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2]);
	}

	//Create green beam
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(1);		//TE_BEAMENTPOINT
	write_short(id);		// start entity
	write_coord(rope_to[id][0]);
	write_coord(rope_to[id][1]);
	write_coord(rope_to[id][2]);
	write_short(beamsprite);
	write_byte(1);		// framestart
	write_byte(1);		// framerate
	write_byte(1);		// life in 0.1's
	write_byte(5);		// width
	write_byte(0);		// noise
	write_byte(0);		// red
	write_byte(255);	// green
	write_byte(0);		// blue
	write_byte(200);	// brightness
	write_byte(0);		// speed
	message_end();

	//Calculate Velocity;
	static Float:velocity[3];
	get_velo(id,velocity);

	static Float:velocity2[3];
	velocity2[0] = (rope_to[id][0] - origin1_F[0]) * 3.0;
	velocity2[1] = (rope_to[id][1] - origin1_F[1]) * 3.0;

	static Float:yy;
	yy = velocity2[0]*velocity2[0] + velocity2[1]*velocity2[1];

	static Float:xx;
	xx = ( CVAR_ROPE_SPEED * 20.0) / floatsqroot(yy);

	velocity[0] += velocity2[0]*xx;
	velocity[1] += velocity2[1]*xx;

	if(rope_to[id][2] - origin1_F[2] >= rope_totaldis[id] && velocity[2]<0.0) velocity[2] *= -1;

	set_velo(id,velocity);

	return PLUGIN_CONTINUE;
}


//GRAB
public Ult_Grab( id )
{
	if( grab[id] )
	{
		grab_off(id);
	}
	else
	{
		grab_on(id);
	}

	return PLUGIN_HANDLED
}

public grab_on(id)
{

	if ( !Ult_Can_Use ( id, SKILLIDX_GRAB ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( is_user_alive ( id ) && !issearching[id] && !ultimateused[id] && !grab[id] )
	{
		new parm[2];
		parm[0] = id;
		parm[1] = ULTIMATESEARCHTIME;
		TASK_GRAB_Search ( parm );
	}

	return PLUGIN_HANDLED
}

public grab_on2(id)
{
	if(is_user_connected(id))
	{
		static target, trash
		target=0
		get_user_aiming(id,target,trash)
		if(target && is_valid_ent2(target) && target!=id && !Util_IsSame_Team(target,id) && Util_IsValid_Team(target ) )
		{
			if( Util_Is_Valid_Player( target ) )
			{
				if(is_user_alive(target) )
				{
					if( !GrabResisted( target, id ) )
					{
						if ( CVAR_DEBUG_MODE )
						{
							client_print( id, print_console, "DEBUG :: TASK_GRAB_Search -> failed to resist" );
							log_amx( "[UWC3X] DEBUG :: TASK_GRAB_Search -> failed to resist" );
						}	
					
						client_print(id, print_chat, "%L", id, "GRAB_FOUND", MOD);
						client_print(id, print_center, "%L", id, "GRAB_FOUND", MOD);
						grabem(id,target)
					}
					else
					{
						if ( CVAR_DEBUG_MODE )
						{
							client_print( id, print_console, "DEBUG :: grabem -> resisted" );
							log_amx( "[UWC3X] Debug :: grabem -> resisted" );
						}	
					}
				}
			}
			else if(get_solidity(target)!=4)
			{
				client_print(id, print_chat, "%L", id, "GRAB_FOUND", MOD);
				client_print(id, print_center, "%L", id, "GRAB_FOUND", MOD);
				grabem(id,target)
			}
		}
		else
		{
			set_task(0.1,"grab_on2",id)
		}
	}
}

public grabem(id,target)
{
	grab[id]=target;

	icon_controller ( id );
	ultimateused[id] = true;
	
	
	if ( CVAR_DEBUG_MODE )
	{
		new name1[32], name2[32];
		get_user_name ( target, name1, 31 );
		get_user_name ( id, name2, 31 );
		client_print(id, print_console, "DEBUG :: grabem -> player %s target:%s", name2, name1 );
		log_amx( "[UWC3X] Debug :: grabem -> player %s target:%s", name2, name1 );
	}	

	set_rendering2(target,kRenderFxGlowShell,255,0,0,kRenderTransAlpha,70);
	if( Util_Is_Valid_Player( target ))
		set_user_gravity(target,0.0);

	grab_totaldis[id] = 0.0;

	set_task(0.1,"grab_prethink",id+1000,"",0,"b");

	grab_prethink(id+1000);

	if( Util_Should_Msg_Client(target) )
	{
		if ( file_exists ( "sound/uwc3x/xbow_fire1.wav" ) == 1 )
		{
			emit_sound ( id, CHAN_STATIC, "uwc3x/xbow_fire1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}
	
	GrabCount[id] = ( GrabCount[id] -1 );

	if( GrabCount[id] == 0 )
	{
		client_print( id ,print_chat, "%L", id, "GRAB_NONE_LEFT", MOD )
		return PLUGIN_HANDLED;
	}
	else
	{
		if( CVAR_DEBUG_MODE )
		{
			new debugname[32];
			get_user_name ( id, debugname, 31 );
			log_amx( "[UWC3X] DEBUG :: grabem -> player %s  GrabsLeft=%d", debugname, GrabCount[id] );
		}

		if( GrabCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "GRAB_NONE_LEFT", MOD );
		}
		else
		{
			client_print(id,print_chat, "%L", id, "GRAB_COUNT", MOD, GrabCount[id]);
		}
	}

	return PLUGIN_HANDLED;

}

public grab_off(id)
{
	if(is_user_connected(id))
	{
		if(grab[id]==-1)
		{
			client_print(id, print_chat, "%L", id, "GRAB_NOTARGETS", MOD);
			client_print(id, print_center, "%L", id, "GRAB_NOTARGETS", MOD);
			grab[id]=0;
		}
		else if(grab[id])
		{
			client_print(id, print_chat, "%L", id, "GRAB_LETGO", MOD);
			client_print(id, print_center, "%L", id, "GRAB_LETGO", MOD);
			set_rendering2(grab[id]);

			if( Util_Is_Valid_Player( grab[id] ) && is_user_alive(grab[id]))
				set_user_gravity(grab[id],1.0);

			grab[id]=0;
		}
	}

	new cooldownGrabParm[1];
	cooldownGrabParm[0] = id;
	set_task(CVAR_GRAB_COOLDOWN, "cooldownGrab", TASK_GRAB_COOLDOWN+id, cooldownGrabParm, 1);
	return PLUGIN_HANDLED;
}

public grab_prethink(id)
{
	id -= 1000;

	if(!is_user_connected(id) && grab[id]>0)
	{
		set_rendering2(grab[id]);
		if( Util_Is_Valid_Player( grab[id] ) && is_user_alive(grab[id])) set_user_gravity(grab[id],1.0);
		grab[id]=0;
	}

	if(!grab[id] || grab[id]==-1)
	{
		remove_task(id+1000);
		return PLUGIN_HANDLED;
	}

	//Get Id's, target's, and Where Id is looking's origins
	static origin1[3];
	get_user_origin(id,origin1);
	static Float:origin2_F[3], origin2[3];
	get_origin(grab[id],origin2_F);
	origin2[0] = floatround(origin2_F[0]);
	origin2[1] = floatround(origin2_F[1]);
	origin2[2] = floatround(origin2_F[2]);
	static origin3[3];
	get_user_origin(id,origin3,3);

	//Create red beam
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(1);		//TE_BEAMENTPOINT
	write_short(id);		// start entity
	write_coord(origin2[0]);
	write_coord(origin2[1]);
	write_coord(origin2[2]);
	write_short(beamsprite);
	write_byte(1);		// framestart
	write_byte(1);		// framerate
	write_byte(1);		// life in 0.1's
	write_byte(5);		// width
	write_byte(0);		// noise
	write_byte(255);		// red
	write_byte(0);		// green
	write_byte(0);		// blue
	write_byte(200);		// brightness
	write_byte(0);		// speed
	message_end();

	//Convert to floats for calculation
	static Float:origin1_F[3];
	static Float:origin3_F[3];
	origin1_F[0] = float(origin1[0]);
	origin1_F[1] = float(origin1[1]);
	origin1_F[2] = float(origin1[2]);
	origin3_F[0] = float(origin3[0]);
	origin3_F[1] = float(origin3[1]);
	origin3_F[2] = float(origin3[2]);

	//Calculate target's new velocity
	static Float:distance[3];

	if(!grab_totaldis[id])
	{
		distance[0] = floatabs(origin1_F[0] - origin2_F[0]);
		distance[1] = floatabs(origin1_F[1] - origin2_F[1]);
		distance[2] = floatabs(origin1_F[2] - origin2_F[2]);
		grab_totaldis[id] = floatsqroot(distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2]);
	}
	distance[0] = origin3_F[0] - origin1_F[0];
	distance[1] = origin3_F[1] - origin1_F[1];
	distance[2] = origin3_F[2] - origin1_F[2];

	static Float:grab_totaldis2;
	grab_totaldis2 = floatsqroot(distance[0]*distance[0] + distance[1]*distance[1] + distance[2]*distance[2]);

	static Float:que
	que = grab_totaldis[id] / grab_totaldis2;

	static Float:origin4[3]
	origin4[0] = ( distance[0] * que ) + origin1_F[0];
	origin4[1] = ( distance[1] * que ) + origin1_F[1];
	origin4[2] = ( distance[2] * que ) + origin1_F[2];

	static Float:velocity[3]
	velocity[0] = (origin4[0] - origin2_F[0]) * ( CVAR_GRAB_SPEED / 1.666667);
	velocity[1] = (origin4[1] - origin2_F[1]) * ( CVAR_GRAB_SPEED / 1.666667);
	velocity[2] = (origin4[2] - origin2_F[2]) * ( CVAR_GRAB_SPEED / 1.666667);

	set_velo(grab[id],velocity);

	return PLUGIN_CONTINUE;
}



public Ult_Hook2( id )
{

	if(hook[id])
	{
		hook_off(id);
	}
	else
	{
		hook_on(id);
	}

	return PLUGIN_HANDLED;
}

public hook_on ( id )
{

	if ( !Ult_Can_Use ( id, SKILLIDX_HOOK ) )
	{
		return PLUGIN_HANDLED;
	}

	if(hook[id])
	{
		return PLUGIN_HANDLED;
	}

	icon_controller ( id );
	ultimateused[id] = true;

	set_user_gravity(id,0.0);
	set_task(0.1,"hook_prethink",id+10000,"",0,"b");
	hook[id]=true;
	hook_to[id][0]=999999;
	hook_prethink(id+10000);

	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists ( "sound/uwc3x/xbow_hit2.wav" ) == 1 )
		{
			emit_sound(id,CHAN_STATIC,"uwc3x/xbow_hit2.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}

	HookCount[id] = ( HookCount[id] -1);

	if( HookCount[id] == 0 )
	{
		client_print( id ,print_chat, "%L", id, "HOOK_NONE_LEFT", MOD )
		return PLUGIN_HANDLED;
	}
	else
	{
		if( CVAR_DEBUG_MODE )
		{
			new debugname[32];
			get_user_name ( id, debugname, 31 );
			log_amx( "[UWC3X] DEBUG :: Ult_Hook -> player %s  HooksLeft=%d", debugname, HookCount[id] );
		}

		if( HookCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "HOOK_NONE_LEFT", MOD );
		}
		else
		{
			client_print(id,print_chat, "%L", id, "HOOK_COUNT", MOD, HookCount[id]);
		}
	}

	return PLUGIN_HANDLED;

}

public hook_off(id)
{
	if(is_user_alive(id))
		set_user_gravity(id);

	hook[id]=false;
	ultimateused[id] = true;

	new cooldownGrabParm[1];
	cooldownGrabParm[0] = id;
	set_task(CVAR_GRAB_COOLDOWN, "cooldownGrab", TASK_GRAB_COOLDOWN+id, cooldownGrabParm, 1);

	return PLUGIN_HANDLED;
}

public hook_prethink(id)
{
	id -= 10000;
	if(!is_user_alive(id))
	{
		hook[id]=false;
	}
	if(!hook[id])
	{
		remove_task(id+10000);
		return PLUGIN_HANDLED;
	}

	//Get Id's origin
	static origin1[3];
	get_user_origin(id,origin1);

	if(hook_to[id][0]==999999)
	{
		static origin2[3];
		get_user_origin(id,origin2,3);
		hook_to[id][0]=origin2[0];
		hook_to[id][1]=origin2[1];
		hook_to[id][2]=origin2[2];
	}

	//Create blue beam
	message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
	write_byte(1);		//TE_BEAMENTPOINT
	write_short(id);		// start entity
	write_coord(hook_to[id][0]);
	write_coord(hook_to[id][1]);
	write_coord(hook_to[id][2]);
	write_short(beamsprite);
	write_byte(1);		// framestart
	write_byte(1);		// framerate
	write_byte(2);		// life in 0.1's
	write_byte(5);		// width
	write_byte(0);		// noise
	write_byte(0);		// red
	write_byte(0);		// green
	write_byte(255);		// blue
	write_byte(200);		// brightness
	write_byte(0);		// speed
	message_end();

	//Calculate Velocity
	static Float:velocity[3];
	velocity[0] = (float(hook_to[id][0]) - float(origin1[0])) * 3.0;
	velocity[1] = (float(hook_to[id][1]) - float(origin1[1])) * 3.0;
	velocity[2] = (float(hook_to[id][2]) - float(origin1[2])) * 3.0;

	static Float:yy;
	yy = velocity[0]*velocity[0] + velocity[1]*velocity[1] + velocity[2]*velocity[2];

	static Float:xx;
	xx = ( CVAR_HOOK_SPEED * 120.0) / floatsqroot(yy);

	velocity[0] *= xx;
	velocity[1] *= xx;
	velocity[2] *= xx;

	set_velo(id,velocity);

	return PLUGIN_CONTINUE;
}








public Ult_Hook( id )
{
	if ( !Ult_Can_Use ( id, SKILLIDX_HOOK ) )
	{
		return PLUGIN_HANDLED;
	}

	new HOOK_COUNT_IDX = p_skills[id][SKILLIDX_HOOK];
	new HOOKCOUNTint = p_hooks[HOOK_COUNT_IDX];

	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: Ult_Hook -> player %s  wchook HOOK_COUNT_IDX=%d   HOOKCOUNTint=%d", debugname, HOOK_COUNT_IDX, HOOKCOUNTint );
	}

	if ( is_user_alive ( id ) && !ultimateused[id] && !hooked[id] )
	{
		DO_HOOK ( id );
		HookCount[id] = ( HookCount[id] -1);
		ultimateused[id] = true;
		icon_controller ( id );

		if( HookCount[id] == 0 )
		{
			client_print( id ,print_chat, "%L", id, "HOOK_NONE_LEFT", MOD )
			return false
		}
		else
		{
			new HooksLeft = HOOKCOUNTint - HookCount[id];

			if( CVAR_DEBUG_MODE )
			{
				new debugname[32];
				get_user_name ( id, debugname, 31 );
				log_amx( "[UWC3X] DEBUG :: Ult_Hook -> player %s  HooksLeft=%d", debugname, HooksLeft );
			}

			if( HooksLeft == 0 )
			{
				client_print( id ,print_chat, "%L", id, "HOOK_NONE_LEFT", MOD )
			}
			else
			{
				client_print(id,print_chat, "%L", id, "HOOK_COUNT", MOD, HooksLeft)
			}
		}
	}
	else
	{
		HOOK_release( id );
	}

	return PLUGIN_HANDLED;
}

public DO_HOOK(id)
{
	new parm[1], user_origin[3];
	parm[0] = id;

	hooked[id] = true;
	get_user_origin(id, user_origin);
	get_user_origin(id, hooklocation[id], 3);
	hooklength[id] = get_distance(hooklocation[id],user_origin);
	global_gravity = get_cvar_num("sv_gravity");
	set_user_gravity(id,0.001);
	HOOK_beamentpoint(id);

	if( Util_Should_Msg_Client(id) )
	{
		emit_sound(id, CHAN_STATIC, "uwc3x/xbow_hit2.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
	}

	set_task(DELTA_T, "TASK_hooktask", TASK_HOOK + id, parm, 2, "b");

	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: DO_HOOK -> player %s  in function", debugname );
	}
}