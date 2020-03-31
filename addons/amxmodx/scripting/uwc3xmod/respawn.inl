/* Respawn stuff*/

public func_spawn ( parm[2] )
{
	new id = parm[0];

	if ( !Util_Is_Valid_Player( id ) || !Util_IsValid_Team ( id ) || endround || freezetime )
	{
		return PLUGIN_CONTINUE;
	}

	if ( playeritem2[id] != MOLE )
	{
		playeritem2[id] = 0;
	}

	//generic catch all
	//Initialize_PlayerData(id, true);

	new team[32];
	get_user_team ( id, team, 31 );

	playerhasspawned[id] = true;
	deathmessageshown[id] = false;
	icon_controller ( id );
	user_spawn ( id );

	unammo[id]		= false;
	badaim[id]		= false;

	slowed[id]		= false;
	stunned[id]		= false;

	// Reset burning from flamethrower status
	isburning[id]	= 0;

	// Reset burning from napalm status
	isnburning[id]	= 0;

	// Reset poisoned status
	ispoisonedss[id] = 0;

	// Reset poisoned status
	isdiseasedcb[id] = 0;

	//reset Rot, cripple, cloak, depower, teamshield, etc status
	CheckCloak[id] = true;
	BlockPickup[id] = false;
	bIsRotting[id] = false;
	iscrippled[id] = 0;
	crippletype[id] = 0;
	playerCanBuyitem3[id] = 1;
	p_ShieldMaxDamageAbsorbed[id] = 0;
	UsedTeamShield[id] = 0;
	HasTeamShield[id]=false;

	// [08-19-04] Fix to prevent MOLE item from being used on Respawn
	hasrespawned[id] = true;
	
	//Cant grab some one when dead
	grab[id]=0;

	//Cant be grabbed when dead
	Remove_Grab( id );

	set_task ( 0.1, "spawn_player", 2,parm, 2 );

	parm[1] = 0;
	set_task ( 0.3, "spawn_player", 2,parm, 2 );
	set_task ( 0.5, "Give_Items", 2, parm, 2 );


	// Call routine to set user runspeed
	new parm[1];
	parm[0] = id;
	Set_Speed( parm );

	//RESET SHOPMENU3 TASKS
	if( task_exists( SHOPMENU3_RESET + id ) )
	{
		remove_task ( SHOPMENU3_RESET + id );
	}

	give_item ( id, "weapon_knife" );

	if ( cs_get_user_money ( id ) < get_cvar_num ( "mp_startmoney" ) )
	{
		cs_set_user_money ( id, get_cvar_num ( "mp_startmoney" ), 0 );
	}
	return PLUGIN_CONTINUE;
}

public spawn_player ( parm[2] )
{
	new id = parm[0];

	//removed just added
	//	playerhasspawned[id] and is_user_alive ( id ) checks so they dont get spawned if they are already spawned
	// UNTESTED if the above would have fixed any spawn death issues
	if ( !is_user_connected ( id ) || ( get_user_team ( id ) == SPEC ) || endround )
	{
		return PLUGIN_CONTINUE;
	}

	user_spawn ( id );

	//Moved to after user_spawn func call
	playerhasspawned[id] = true;

	//Set a default health in case its not set properly for whatever reason
	if( maxhealth[id] == 0 )
	{
		maxhealth[id] = 100;
	}

	if ( get_user_health ( id ) < maxhealth[id] )
	{
		set_user_health ( id, maxhealth[id] );
	}

	give_item ( id, "item_suit" );
	give_item ( id, "weapon_knife" );

	// [08-19-04] Give player 2 seconds Godmode after respawn
	set_user_godmode ( id, 1 );

	// [05-23-05] Set Player p_spawnprotection to 1
	p_spawnprotection[id] = 1;
	hasgodmode[id] = true;

	set_task ( S_PROTECT_TIME, "reset_respawngod", 2, parm, 2 );
	return PLUGIN_CONTINUE;
}

public reset_respawngod ( args[] )
{
	new id = args[0];

	if ( !is_user_connected ( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	set_user_godmode ( id, 0 );
	p_spawnprotection[id] = 0;
	hasgodmode[id] = false;

	if( Util_Should_Msg_Client(id) && args[1] )
	{
		//client_print_utility ( id, print_chat, "%L", id, "RESPAWN_GRACE_END", MOD );
		hudchat_show(id, "%L", id, "RESPAWN_GRACE_END");
		hudchat_update(id);
	}

	return PLUGIN_CONTINUE;
}
public check_for_reviving ( victim_id )
{
	new players[32], numberofplayers, y;
	get_players ( players, numberofplayers );

	if ( get_user_team ( victim_id ) == TEAM_T && pheonixexistsT > 0 )
	{
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug:: In TEAM_T pheonix respawn check");
		}

		for ( y = 0; y < numberofplayers; ++y )
		{
			new id = players[y];
			new name[32];
			get_user_name ( id, name, 31 );

			if ( CVAR_DEBUG_MODE )
			{
				new name2[32];
				get_user_name ( victim_id, name2, 31 );
				log_amx( "[UWC3X] Debug:: %s - get_availskillpts(id)=%d", name, get_availskillpts(id) );
				log_amx( "[UWC3X] Debug:: %s - phoenix(id)=%d", name, phoenix[id] );
				log_amx( "[UWC3X] Debug:: %s - to_be_revived(victim_id)=%s", name, name2 );
				log_amx( "[UWC3X] Debug:: %s - endround=%d", name, endround );
				log_amx( "[UWC3X] Debug:: %s - is_user_alive(id)=%d", name, is_user_alive(id) );
			}

			if (phoenix[id] && !to_be_revived[victim_id] && !endround && id!=victim_id && !changingteam[victim_id] && is_user_alive ( id ) && ( get_user_team ( id )==get_user_team ( victim_id ) ) && !is_user_alive ( victim_id ) && get_user_team ( victim_id )!=SPEC )
			{
				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] Debug:: In TEAM_T player is respawned!");
				}

				phoenix[id] = false;
				//phoenix[victim_id]=false;
				new parm[2];
				parm[0] = victim_id;

				// Spawns player
				set_task ( 0.7, "func_spawn", 2, parm, 2 ) ;

				if( Util_Should_Msg_Client(id) )
				{
					//set_hudmessage ( 200, 100, 0, -1.6, 0.1, 0, 1.0, 5.0, 0.1, 0.2, 2 );
					//show_hudmessage ( victim_id, "%s has revived you", name );
					//client_print_utility ( victim_id, print_chat, "%L", victim_id, "PHEONIX_REVIVE4", MOD, name );
					hudchat_show(victim_id, "%L", victim_id, "PHEONIX_REVIVE4", name);
					hudchat_update(victim_id);
				}

				get_user_name ( victim_id, name, 31 );

				// [07-27-04] - Now gives XP bonus for reviving a teammate
				new xpbonus = PHOENIXXP + xpgiven_lev[p_level[id]];
				if ( CVAR_SAVE_XP )
				{
					xpbonus += ( PHOENIXXP * p_level[id] );
				}

				playerxp[id] += xpbonus;


				if( Util_Should_Msg_Client(id) )
				{
					//client_print_utility ( id, print_chat, "%L", id,"PHEONIX_REVIVE2", MOD, name, xpbonus );
					//show_hudmessage ( id, "%You have revived %s, way to go!", name );
					hudchat_show(id, "%L", id, "PHEONIX_REVIVE2", name, xpbonus);
					hudchat_update(id);
				}

				to_be_revived[victim_id] = true;
				pheonixexistsT--;
				return PLUGIN_CONTINUE;
			 }
		}
	}
	else if ( get_user_team ( victim_id )== TEAM_CT && pheonixexistsCT > 0 )
	{
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug:: In TEAM_CT pheonix respawn check");
		}
		
		for ( y = 0; y < numberofplayers; ++y )
		{
			new id = players[y];

			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug:: get_availskillpts(id)=%d", get_availskillpts(id) );
				log_amx( "[UWC3X] Debug:: phoenix(id)=%d", phoenix[id] );
				log_amx( "[UWC3X] Debug:: to_be_revived(victim_id)=%d", to_be_revived[victim_id] );
				log_amx( "[UWC3X] Debug:: endround=%d", endround );
				log_amx( "[UWC3X] Debug:: changingteam[victim_id]=%d", changingteam[victim_id] );
				log_amx( "[UWC3X] Debug:: is_user_alive(id)=%d", is_user_alive(id) );
			}

			if (phoenix[id] && !to_be_revived[victim_id] && !endround && id!=victim_id && !changingteam[victim_id] && is_user_alive(id) && get_user_team(id)==get_user_team(victim_id) && !is_user_alive(victim_id) && get_user_team(victim_id)!=SPEC)
			{
				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] Debug:: In TEAM_CT player is respawned!");
				}

				phoenix[id] = false;
				//phoenix[victim_id]=false;
				new parm[2], name[32];
				parm[0] = victim_id;

				// Spawns player
				set_task ( 0.7, "func_spawn", 2, parm, 2 ) ;
				get_user_name ( id, name, 31 );

				if( Util_Should_Msg_Client(id) )
				{
					//set_hudmessage ( 200, 100, 0, -1.6, 0.1, 0, 1.0, 5.0, 0.1, 0.2, 2 );
					//show_hudmessage ( victim_id, "%s has revived you", name );
					//client_print_utility ( victim_id, print_chat, "%L", victim_id, "PHEONIX_REVIVE4", MOD, name );
					hudchat_show(victim_id, "%L", victim_id, "PHEONIX_REVIVE4", name);
					hudchat_update(victim_id);
				}

				get_user_name ( victim_id, name, 31 );

				// [07-27-04] - Now gives XP bonus for reviving a teammate
				new xpbonus = PHOENIXXP + xpgiven_lev[p_level[id]];
				if ( CVAR_SAVE_XP )
				{
					xpbonus += ( PHOENIXXP * p_level[id] );
				}

				playerxp[id] += xpbonus;

				if( Util_Should_Msg_Client(id) )
				{
					//client_print_utility ( id, print_chat, "%L", id,"PHEONIX_REVIVE2", MOD, name, xpbonus );
					//show_hudmessage ( id, "%You have revived %s, way to go!", name );
					hudchat_show(id, "%L", id, "PHEONIX_REVIVE2", name, xpbonus);
					hudchat_update(id);
				}

				to_be_revived[victim_id] = true;
				pheonixexistsCT--;
				return PLUGIN_CONTINUE;
			}
		}
	}

	return PLUGIN_CONTINUE;
}