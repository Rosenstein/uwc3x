
public __TaskShowHudChat(id)
{
	id -= __HUDCHAT_TASKID_UPDATE;
	
	new message[__HUDCHAT_MAXMSGLEN];
	new messages[((__HUDCHAT_MAXMSGLEN - 1) * __HUDCHAT_MAXLINES) + __HUDCHAT_MAXLINES];
	new m, len;
	
	for(m = 0; m < __HUDCHAT_MSGCOUNT[id]; m++)
	{
		ArrayGetString(__HUDCHAT_MESSAGES[id], m, message, charsmax(message));
		
		len += formatex(messages[len], charsmax(messages) - len, "%s%s", (len > 0) ? "^n" : "", message);
	}
	
	messages[len] = 0;
	
	set_hudmessage(__HUDCHAT_R, __HUDCHAT_G, __HUDCHAT_B, __HUDCHAT_POS_X, __HUDCHAT_POS_Y, 0, 0.0, (__HUDCHAT_UPDATEINTERVAL + 0.1), 0.0, 0.0, __HUDCHAT_CHANNEL);
	show_hudmessage(id, "%s", messages);
}

public __TaskRemoveHudChat(taskid)
{
	new id = taskid - __HUDCHAT_TASKID_REMOVE;
	
	if(__HUDCHAT_MSGCOUNT[id] > 0)
	{
		ArrayDeleteItem(__HUDCHAT_MESSAGES[id], 0);
		
		if(--__HUDCHAT_MSGCOUNT[id] > 0)
		{
			set_task(__HUDCHAT_REMOVETIME, "__TaskRemoveHudChat", taskid);
		}
	}
}


/* GENERIC */
public Task_Reset_Immunity ( parm[2] )
{
	
	if( Util_Should_Msg_Client(parm[0]) )
	{
		client_print ( parm[0], print_chat, "%L", parm[0], "RESISTANCE_ENDED", MOD, parm[1] );
	}
	
	temp_immunity[ parm[0] ] = false;
}

public Initialize_Tasks ( )
{
	
	// set_task calls for functions needed by init or to run continuously
	set_task ( 10.0,		"Check_UWC3X",		TASK_CHECK_UWC3X,	"",		0,	"b"		 );
	set_task ( 1.0,			"Check_UWC3X",		TASK_CHECK_UWC3X_AGAIN		 );
	//set_task ( 3.0,			"XP_SetChoice",		TASK_SET_XP_CHOICES			 );
	set_task ( 0.6,			"set_variables",	TASK_SET_VARIABLES			 );
	
	// TASK_Check_Duck used by decoy ultimate
	set_task ( 0.01,		"TASK_Check_Duck",	TASK_DO_NOW,		"",		0,	"b"		 );
	
	// Task_Award_FrostNades used by Frost Nades skill - awards a frost nade every 30 seconds
	set_task ( 30.00,		"Task_Award_FrostNades",	TASK_DO_NOW,		"",		0,	"b"		 );
	
	log_amx( "[UWC3X] Tasks Initialized [OK]");
}

public Task_Award_FrostNades( )
{
	
	if( endround || freezetime )
		return;
	
	new players[32];
	new numplayers;
	get_players ( players, numplayers );
	
	for ( new i=0; i< numplayers; ++i )
	{
		new id = players[i];
		
		if( !p_skills[id][SKILLIDX_ICENADE] || !is_user_alive(id) || !Util_IsValid_Team( id ) || !Util_Is_Valid_Player( id ) )
			continue;
		
		new HasSmokeNade = 0;
		
		// Check their weapons and see if they already have a smoke grenade
		new weapons[32], num, j;
		get_user_weapons(id,weapons,num);
		
		for(j=0;j<num;j++)
		{
			if( IsWeaponSmokeGrenade( weapons[j] ) )
			{
				//They do
				HasSmokeNade = 1;
				break;
			}
		}
		
		//if they dont, give them one
		if( !HasSmokeNade )
		{
			// gimme gimme
			hasFrostNade[id] = 1;
			give_item(id,"weapon_smokegrenade");
			
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ICEBOMB_GIVEN1", MOD );
				client_print ( id, print_center, "%L", id, "ICEBOMB_GIVEN2" );
			}
		}
	}
	
}

/* Gate */
public Task_Gate_User_Shopmenu ( parm[6] )
{
	// Opens a Gateway to Teleport the player back home
	
	new id = parm[5];
	new origin[3];
	new oldLocation[3];
	new Float:forigin[3];
	new Float:vicinity = 96.0;
	new entsFound[1];
	
	origin[0] = parm[0];
	origin[1] = parm[1];
	origin[2] = parm[2];
	
	forigin[0] = float ( parm[0] );
	forigin[1] = float ( parm[1] );
	forigin[2] = float ( parm[2] );
	
	// Perform a final check to make sure this MOLE spot wasn't taken
	new numplayers = find_sphere_class ( 0, "player", vicinity, entsFound, 1, forigin );
	
	if ( numplayers > 0 )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_COLLAPSE", MOD );
		}
		
		return PLUGIN_HANDLED;
	}
	
	get_user_origin ( id, oldLocation );
	oldLocation[2] += 30;
	
	// [09-05-04] - Display gate sprite ( tele ) 1 cycle
	message_begin ( MSG_ALL, SVC_TEMPENTITY );
	write_byte ( TE_SPRITE );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] );
	write_short ( gatespr );
	write_byte ( 10 );
	write_byte ( 255 );
	message_end ( );
	
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
	
	set_user_origin ( id, origin );
	
	if( Util_Should_Msg_Client( id ) )
	{
		message_begin ( MSG_ONE, gmsgShake, { 0, 0, 0 }, id );
		write_short ( 255<< 14 ); //ammount
		write_short ( 10 << 14 ); //lasts this long
		write_short ( 255<< 14 ); //frequency
		message_end ( );
	}
	
	return PLUGIN_CONTINUE;
}

public Task_Gate_User ( parm[6] )
{
	// Opens a Gateway to Teleport the player back home
	
	new id = parm[5];
	new origin[3];
	new oldLocation[3];
	new Float:forigin[3];
	new Float:vicinity = 96.0;
	new entsFound[1];
	
	origin[0] = parm[0];
	origin[1] = parm[1];
	origin[2] = parm[2];
	
	forigin[0] = float ( parm[0] );
	forigin[1] = float ( parm[1] );
	forigin[2] = float ( parm[2] );
	
	// Perform a final check to make sure this MOLE spot wasn't taken
	new numplayers = find_sphere_class ( 0, "player", vicinity, entsFound, 1, forigin );
	
	if ( numplayers > 0 )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_GATE_COLLAPSE", MOD );
		}
		return PLUGIN_HANDLED;
	}
	
	--numgates[id];
	
	if( Util_Should_Msg_Client(id) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIAMTE_GATE", MOD );
	}
	
	ultimateused[id] = true;
	new cooldownparm[1];
	cooldownparm[0] = id;
	
	get_user_origin ( id, oldLocation );
	oldLocation[2] += 30;
	
	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists ( "sound/uwc3x/massteleporttarget.wav" ) ==1 )
		{
			emit_sound ( id, CHAN_ITEM, "uwc3x/massteleporttarget.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
		else
		{
			emit_sound ( id, CHAN_ITEM, "x/x_shoot1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}
	
	// [09-05-04] - Display gate sprite ( tele ) 1 cycle
	message_begin ( MSG_ALL, SVC_TEMPENTITY );
	write_byte ( TE_SPRITE );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] );
	write_short ( gatespr );
	write_byte ( 10 );
	write_byte ( 255 );
	message_end ( );
	
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
	
	set_user_origin ( id, origin );
	
	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists ( "sound/uwc3x/massteleporttarget.wav" ) ==1 )
		{
			emit_sound ( id, CHAN_ITEM, "uwc3x/massteleporttarget.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
		else
		{
			emit_sound ( id, CHAN_ITEM, "x/x_shoot1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}
	
	if( Util_Should_Msg_Client( id ) )
	{
		message_begin ( MSG_ONE, gmsgShake, { 0, 0, 0 }, id );
		write_short ( 255<< 14 ); //ammount
		write_short ( 10 << 14 ); //lasts this long
		write_short ( 255<< 14 ); //frequency
		message_end ( );
	}
	
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		client_print( id, print_console, "[%s DEBUG] Task_Gate_User -> Setting gateused[id] =true for player %s so now there is a 5 second delay", MOD, debugname );
		log_amx( "[UWC3X] DEBUG :: Task_Gate_User -> Setting gateused[id] =true for player %s so now there is a 5 second delay", debugname );
	}
	
	gateused[id] = true;
	set_task ( CVAR_GATE_COOLDOWN, "cooldownGate", TASK_COOLDOWN_RESET+id, cooldownparm, 1 );
	return PLUGIN_CONTINUE;
}

/* voodoo */
public Task_Reset_Godmode ( parm[] )
{
	new id = parm[0];
	
	new name[32];
	get_user_name ( id, name, 31 );
	
	if ( godshealth[id] < 1 )
	{
		set_user_health_log ( id, 30 );
	}
	else
	{
		set_user_health_log ( id, godshealth[id] );
	}
	
	hasgodmode[id] = false;
	
	set_task ( CVAR_VOODOO_COOLDOWN, "cooldown", TASK_COOLDOWN_RESET + id, parm, 1 );
	
	if( Util_Should_Msg_Client(id) )
	{
		set_hudmessage ( 0, 100, 0, 0.05, 0.75, 2, 0.02, 10.0, 0.01, 0.1, 2 );
		show_hudmessage ( id, "Your Voodoo has expired" );
	}
	
	icon_controller ( id );
	
	return PLUGIN_CONTINUE;
}



/* Teleport */
public Task_Blink_Controller ( parm[2] )
{
	new id = parm[0];
	new newLocation[3];
	new curLocation[3];
	new oldLocation[3];
	new origin[3];
	
	if ( parm[1] == 1 )
	{
		// Teleport failure check and unsticker
		new coolparm[1];
		coolparm[0] = id;
		
		newLocation = savedNewLoc[id];
		get_user_origin ( id, curLocation, 0 );
		
		if ( newLocation[2] == curLocation[2] )
		{
			// Teleportation Failure
			oldLocation = savedOldLoc[id];
			
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage ( 255, 255, 10, -1.0, -0.4, 1, 0.5, 3.0, 0.2, 0.2, 5 );
				show_hudmessage ( id, "%L", id, "ULTIMATE_TELEPORT_FAILED" );
			}
			
			set_user_origin ( id, oldLocation );
			
			parm[1] = 0;
			set_task ( 0.1, "Task_Blink_Controller", 0, parm, 2 );
			set_task ( CVAR_BLINK_COOLDOWN, "cooldown", TASK_COOLDOWN_RESET + id ,coolparm, 1 );
		}
		else
		{
			// Teleportation Success if not near player with immunity
			new teamname[32];
			new players[32];
			new numplayers;
			new targetorigin[3];
			new targetid;
			new bool:teleportSuccess = true;
			
			get_user_origin ( id, origin );
			get_user_team ( id, teamname, 31 );
			get_players ( players, numplayers );
			
			new idname[32];
			get_user_name ( id, idname, 31 );
			
			for ( new i=0; i< numplayers; ++i )
			{
				targetid = players[i];
				
				if ( Util_IsSame_Team ( id, targetid ) || Util_Player_Is_Spec ( targetid ) || !is_user_alive ( targetid ) )
				{
					continue;
				}
				
				if ( playeritem[targetid] == IMMUNITY || Util_IsPlayer_Immune ( targetid, 2 ) )
				{
					get_user_origin ( targetid, targetorigin );
					if ( get_distance ( origin, targetorigin )<= CVAR_BLINK_RADIUS )
					{
						oldLocation = savedOldLoc[id];
						
						if( Util_Should_Msg_Client(id) )
						{
							set_hudmessage ( 255, 255, 10, -1.0, -0.4, 1, 0.5, 5.0, 0.2, 0.2, 5 );
							show_hudmessage( id , "%L", id, "ULTIMATE_TEPELORT_IMMUNE" );
						}
						
						set_user_origin ( id, oldLocation );
						parm[1] = 0;
						set_task ( 0.1, "Task_Blink_Controller", 0, parm, 2 );
						set_task ( CVAR_TELEPORT_COOLDOWN, "cooldown", TASK_COOLDOWN_RESET + id, coolparm, 1 );
						teleportSuccess = false;
					}
				}
			}
			
			if ( teleportSuccess )
			{
				parm[1] = 2;
				
				// [08-05-04] - Added faster cooldown for Master Intellect
				new Float:tele_cool = CVAR_TELEPORT_COOLDOWN;
				
				if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_INT] >= INT_TELEPORT_LEVEL ) )
				{
					tele_cool -= INT_TELEPORT_COOL;
					if (tele_cool < 1.0)
					{
						tele_cool = 1.0;
					}
				}
				
				set_task ( tele_cool, "cooldown", TASK_COOLDOWN_RESET + id, coolparm, 1 );
				
				// Call phase 2 of the blindness
				set_task ( 0.6, "Task_Blink_Controller", 0, parm, 2 );
				
				// Sprays white bubbles everywhere
				get_user_origin ( id,origin );
				message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
				write_byte ( TE_SPRITETRAIL );
				write_coord ( origin[0] );
				write_coord ( origin[1] );
				write_coord ( origin[2] + 40 );
				write_coord ( origin[0] );
				write_coord ( origin[1] );
				write_coord ( origin[2] );
				write_short ( flaresprite );
				write_byte ( 30 ); // count
				write_byte ( 10 ); // life
				write_byte ( 1 ); // scale
				write_byte ( 50 ); // velocity
				write_byte ( 10 ); // randomness in velocity
				message_end ( );
				
				if ( CVAR_BLINK_DIZINESS == 1 )
				{
					
					if( Util_Should_Msg_Client( id ) )
					{
						
						// This will cause Teleportation Dizziness ( like a flash grenade )
						message_begin ( MSG_ONE,gmsgFade,{0,0,0},id );
						write_short ( 1<<15 );
						write_short ( 1<<10 );
						write_short ( 1<<12 );
						write_byte ( 255 );
						write_byte ( 255 );
						write_byte ( 255 );
						write_byte ( 255 );
						message_end ( );
					}
				}
			}
		}
	}
	else if ( parm[1] == 2 )
	{
		// Make the Teleport Blues hold..
		if ( CVAR_BLINK_DIZINESS == 2 )
		{
			
			if( Util_Should_Msg_Client( id ) )
			{
				
				// use the magic #1 for "one client"
				message_begin ( MSG_ONE, gmsgFade, {0,0,0}, id );
				write_short ( 1<<0 ); // fade lasts this long duration
				write_short ( 1<<0 ); // fade lasts this long hold time
				write_short ( 1<<2 ); // fade type HOLD
				write_byte ( 76 ); // fade red
				write_byte ( 163 ); // fade green
				write_byte ( 223 ); // fade blue
				write_byte ( 200 ); // fade alpha
				message_end ( );
			}
		}
		
		parm[1] = 0;
		set_task ( 3.0, "Task_Blink_Controller", 0, parm, 2 );
	}
	else
	{
		// Teleport Blueness goes away
		if ( CVAR_BLINK_DIZINESS == 2 )
		{
			
			
			if( Util_Should_Msg_Client( id ) )
			{
				
				// use the magic #1 for "one client"
				message_begin ( MSG_ONE, gmsgFade, {0,0,0}, id );
				write_short ( 1<<12 );// fade lasts this long duration
				write_short ( 1<<8 ); // fade lasts this long hold time
				write_short ( FFADE_OUT ); // fade type OUT
				write_byte ( 76 ); // fade red
				write_byte ( 163 ); // fade green
				write_byte ( 223 ); // fade blue
				write_byte ( 200 ); // fade alpha
				message_end ( );
			}
		}
	}
	
	return PLUGIN_CONTINUE;
}
public TASK_OOB_Check ( parm[2] )
{
	new id = parm[0];
	new mapname[32], origin[3];
	new bool:slay = false;
	
	get_mapname ( mapname, 32 );
	get_user_origin ( id, origin );
	
	new x = origin[0];
	new y = origin[1];
	new z = origin[2];
	
	if ( !is_user_connected ( id ) )
	{
		return;
	}
	
	new Float:porigin[3];
	entity_get_vector ( id, EV_VEC_origin, porigin );
	
	if ( PointContents ( porigin )==-6 )
	{
		slay = true;
	}
	
	if ( equali ( mapname,"de_dust" ) )
	{
		if ( z>220 )
		{
			slay = true;
		}
	}
	else if ( equali ( mapname,"awp_assault" ) )
	{
		if ( z>520 )
		{
			if ( ( y>2400 && y<2600 ) )
				slay = true;
		}
	}
	else if ( equali ( mapname,"de_dust_cz" ) )
	{
		if ( z>220 )
			slay = true;
	}
	else if ( equali ( mapname,"de_aztec_cz" ) )
	{
		if ( z>300 )
			slay = true;
	}
	else if ( equali ( mapname,"cs_assault_upc" ) )
	{
		if ( z>650 )
			slay = true;
	}
	else if ( equali ( mapname,"de_aztec" ) )
	{
		if ( z>300 )
			slay = true;
	}
	else if ( equali ( mapname,"de_cbble" ) )
	{
		if ( z>315 )
		{
			if ( ( x>-1320 && x<-1150 ) && ( y>2600 && y<2900 ) )
			{
				return;
			}
			else
			{
				slay = true;
			}
		}
	}
	else if ( equali ( mapname,"de_cbble_cz" ) )
	{
		if ( z>315 )
		{
			if ( ( x>-1320 && x<-1150 ) && ( y>2600 && y<2900 ) )
			{
				return;
			}
			else
			{
				slay = true;
			}
		}
	}
	else if ( equali ( mapname,"cs_assault" ) )
	{
		if ( z>700 )
			slay = true;
	}
	else if ( equali ( mapname,"cs_militia" ) )
	{
		if ( z>500 )
			slay = true;
	}
	else if ( equali ( mapname,"cs_militia_cz" ) )
	{
		if ( z>500 )
			slay = true;
	}
	else if ( equali ( mapname,"cs_italy" ) )
	{
		if ( z>-220 )
		{
			if ( y<-2128 )
			{
				slay = true;
			}
		}
		else if ( z>250 )
		{
			if ( ( x<-1000 && x>-1648 ) && ( y>1900 && y<2050 ) )
				slay = true;
			else if ( ( x<-1552 && x>-1648 ) && ( y>1520 && y<2050 ) )
				slay = true;
		}
	}
	else if ( equali ( mapname,"cs_italy_cz" ) )
	{
		if ( y>2608 )
			slay = true;
	}
	else if ( equali ( mapname,"de_dust2" ) )
	{
		if ( z>270 )
			slay = true;
	}
	else if ( equali ( mapname,"de_dust2_cz" ) )
	{
		if ( z>270 )
			slay = true;
	}
	else if ( equali ( mapname,"fy_dustworld" ) )
	{
		if ( z>82 )
			slay = true;
	}
	else if ( equali ( mapname,"fy_pool_day" ) )
	{
		if ( z>190 )
			slay = true;
	}
	else if ( equali ( mapname,"as_oilrig" ) )
	{
		if ( x > 1530 && get_user_team ( id ) == TEAM_CT )
			slay = true;
		else if ( x > 1700 )
			slay = true;
	}
	else if ( equali ( mapname,"cs_mice_final" ) )
	{
		if ( ( ( x >= 798 ) && ( x <= 860 ) ) && ( y <- 1430 ) )
			slay = true;
	}
	
	if ( slay )
	{
		new name[32];
		get_user_name ( id, name, 31 );
		
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_TELEPORT_SLAY", MOD );
		}
		
		set_user_health_log ( id, -1 );
	}
}


/* Flame strike */
public Task_FlameStrike_Spray ( args[] )
{
	//Task_FlameStrike_Spray
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	
	// Throws a shower of sprites or models
	write_byte ( 120 ) ;
	
	// start pos
	write_coord ( args[0] ) ;
	
	write_coord ( args[1] );
	write_coord ( args[2] );
	
	// velocity
	write_coord ( args[3] );
	write_coord ( args[4] );
	write_coord ( args[5] );
	// spr
	write_short ( fire ) ;
	
	// count
	write_byte ( 8 );
	
	// speed
	write_byte ( 70 ) ;
	
	// ( noise )
	write_byte ( 100 ) ;
	
	// ( rendermode )
	write_byte ( 5 );
	message_end ( );
	
	return PLUGIN_CONTINUE;
}

public TASK_Burn_Victim ( id, killer, ff )
{
	if (ff == 0 && Util_IsSame_Team(id, killer))
	{
		return PLUGIN_CONTINUE;
	}
	
	if ( isburning[id] == 1 || Util_IsPlayer_Immune ( id , 5 ) )
	{
		return PLUGIN_CONTINUE;
	}
	
	new hp, args[4];
	hp = get_user_health ( id );
	
	if ( hp > 250 )
	{
		hp = 250;
	}
	
	// [08-06-04] - Added Fire Resistance Checks - K2mia
	//new Float:ftimer = 1.5;
	new bool:shouldBurn = false;
	
	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] TASK_Burn_Victim :: isburning = %d", isburning[id]);
	}
	
	if ( USE_ENH && p_resists[id][RESISTIDX_FIRE] )
	{
		new Float:chance_to_avoid = ( p_resists[id][RESISTIDX_FIRE] >= RESIST_MAX_VALUE ) ?	1.00 : ( float ( p_resists[id][RESISTIDX_FIRE] ) / float ( RESIST_MAX_VALUE ) );
		new Float:randomnumber = random_float ( 0.0, 1.0 );
		
		if ( randomnumber < chance_to_avoid )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_FLAME_RESIST", MOD );
			}
			
			if( Util_Should_Msg_Client( killer ) )
			{
				client_print ( killer, print_chat, "%L", killer, "ULTIMATE_FLAME_DEFLECTED",	MOD );
			}
			
			return PLUGIN_CONTINUE;
		}
		else if ( ( randomnumber/2.0 ) < chance_to_avoid )
		{
			
			if( Util_Should_Msg_Client(player_id) )
			{
				client_print ( id, print_chat, "%L", id, "ULTIMATE_FLAME_FAILED", MOD );
			}
			
			if( Util_Should_Msg_Client(killer) )
			{
				client_print ( killer, print_chat, "%L", killer, "ULTIMATE_FLAME_FAILED", MOD );
			}
			
			if (CVAR_DEBUG_MODE)
			{
				log_amx("[UWC3X] TASK_Burn_Victim :: has res");
			}
			
			shouldBurn = true;
		}
	}
	//Added this check for the Fire
	else
	{
		if (CVAR_DEBUG_MODE)
		{
			log_amx("[UWC3X] TASK_Burn_Victim :: no res");
		}
		
		shouldBurn = true;
	}
	
	if (shouldBurn)
	{
		args[0] = id;
		args[1] = killer;
		
		isburning[id] = 1;
		SetTaskUnique(1.5, "EVENT_Set_On_Fire", TASK_ON_FIRE + id, args, 4, "b");
	}
	else
	{
		isburning[id] = 0;
	}
	
	return PLUGIN_CONTINUE;
}

public TASK_Check_BurnZone ( id, vec[3], aimvec[3], speed1, speed2, radius )
{
	new maxplayers, tbody, tid, ff = 0;
	get_user_aiming ( id, tid, tbody, 550 );
	
	if ( cvar_exists ( "mp_friendlyfire" ) )
	{
		new ffcvar = get_cvar_num ( "mp_friendlyfire" );
		
		if ( ( ffcvar == 0 ) || ( ffcvar == 1 ) )
		{
			ff = ffcvar;
		}
	}
	
	if( is_user_alive( tid ) )
	{
		TASK_Burn_Victim ( tid, id, ff ) ;
	}
	
	new burnvec1[3],burnvec2[3],length1;
	
	burnvec1[0]=aimvec[0]-vec[0];
	burnvec1[1]=aimvec[1]-vec[1];
	burnvec1[2]=aimvec[2]-vec[2];
	
	length1=sqrt ( burnvec1[0]*burnvec1[0]+burnvec1[1]*burnvec1[1]+burnvec1[2]*burnvec1[2] );
	burnvec2[0] = burnvec1[0] * speed2/length1;
	burnvec2[1] = burnvec1[1] * speed2/length1;
	burnvec2[2] = burnvec1[2] * speed2/length1;
	burnvec1[0] = burnvec1[0] * speed1/length1;
	burnvec1[1] = burnvec1[1] * speed1/length1;
	burnvec1[2] = burnvec1[2] * speed1/length1;
	burnvec1[0] += vec[0];
	burnvec1[1] += vec[1];
	burnvec1[2] += vec[2];
	burnvec2[0] += vec[0];
	burnvec2[1] += vec[1];
	burnvec2[2] += vec[2];
	
	new target[32], idx, origin[3];
	get_players( target, maxplayers );
	
	for ( new i = 0; i <= maxplayers; i++ )
	{
		idx = target[i];
		
		// Testing to see if this solves the
		// Invalid player id 0 error
		if ( !Util_Is_Valid_Player( idx ) )
			continue;
		
		get_user_origin ( idx, origin );
		FS_Should_Burn_Victim ( origin, burnvec1, burnvec2, radius, idx, id, ff );
	}
	
	return PLUGIN_CONTINUE;
}


/* DEPOWER */
public TASK_DEPOWER_Search ( parm[2] )
{
	new players[32], numofplayers, enemy, body, id = parm[0];
	get_players ( players, numofplayers );
	get_user_aiming ( id, enemy, body );
	
	//If your team mate is not on your team, or your not aiming directly at him
	//Then you should keep looking - otherwise we have it
	if ( ( 0 < enemy <= MAX_PLAYERS ) && ( enemy != id ) && ( get_user_team ( id ) != get_user_team ( enemy ) ) && is_user_alive ( id ) && is_user_alive ( enemy ) )
	{
		new name[32], name2[32];
		get_user_name ( enemy, name, 31 );
		get_user_name ( id, name2, 31 );
		
		issearching[id] = false;
		ultimateused[id] = true;
		icon_controller ( id );
		
		if( CVAR_DEPOWER_CANT_DROP )
		{
			BlockPickup[id] = true;
			BlockPickup[enemy] = true;
			
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_chat, "%L", enemy, "ULTIMATE_DEPOWER_ENEMY2", MOD );
			}
			if( Util_Should_Msg_Client(enemy) )
			{
				client_print ( enemy, print_chat, "%L", enemy, "ULTIMATE_DEPOWER_ENEMY2", MOD );
			}
			
		}
		
		Ult_DEPOWER_REPLACE_GUNS( id );
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_DEPOWER_YOU1", MOD, name );
			
			if ( file_exists ( "sound/uwc3x/depowered.wav" ) == 1 )
			{
				emit_sound ( id, CHAN_STATIC, "uwc3x/depowered.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
			
		}
		
		Ult_DEPOWER_REPLACE_GUNS( enemy );
		if( Util_Should_Msg_Client(enemy) )
		{
			client_print ( enemy, print_chat, "%L", enemy, "ULTIMATE_DEPOWER_ENEMY1", MOD, name2 );
			
			if ( file_exists ( "sound/uwc3x/depowered.wav" ) == 1 )
			{
				emit_sound ( enemy, CHAN_STATIC, "uwc3x/depowered.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
			
		}
		
		UsedDepower[id] = 1;
		
		new cooldownparm[2];
		cooldownparm[0] = id;
		cooldownparm[1] = enemy;
		set_task ( CVAR_DEPOWER_COOLDOWN, "cooldown4", TASK_COOLDOWN4 + id, cooldownparm, 2 );
	}
	else
	{
		//Keep searching
		issearching[id] = true;
		icon_controller ( id );
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if ( parm[1] > 0 && get_user_health ( id ) >=0 )
		{
			set_task ( 0.1, "TASK_DEPOWER_Search", TASK_ULTIMATE_DEPOWER_SEARCH + id, parm, 3 );
		}
		else
		{
			issearching[id] = false;
			icon_controller ( id );
		}
	}
	
	return PLUGIN_CONTINUE;
	
}



/* TEAM SHIELD */
public TASK_SHIELD_Search( parm[2] )
{
	new players[32], numofplayers, body;
	
	//These are opposite of the functions - keep that in mind
	new id = parm[0]; //Player providing the shield
	new teammate; //Guy who is getting the shield
	
	get_players ( players, numofplayers );
	get_user_aiming ( id, teammate, body );
	
	//If your team mate is not on your team, or your not aiming directly at him
	//Then you should keep looking - otherwise we have it
	if ( is_user_connected ( id ) && is_user_connected ( teammate ) && is_user_alive ( id ) && is_user_alive ( teammate ) && ( !HasTeamShield[teammate] && !UsedTeamShield[id])  &&  ( 0 < teammate <= MAX_PLAYERS ) && ( teammate != id ) && ( get_user_team ( id ) == get_user_team ( teammate ) ) )
	{
		new name[32], name2[32];
		get_user_name ( teammate, name, 31 );
		get_user_name ( id, name2, 31 );
		
		issearching[id] = false;
		ultimateused[id] = true;
		icon_controller ( id );
		
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_SIV_SHIELDER", name );
			
			if ( file_exists ( "sound/uwc3x/divineshield.wav" ) == 1 )
			{
				emit_sound ( id, CHAN_STATIC, "uwc3x/divineshield.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
		
		if( Util_Should_Msg_Client( teammate ) )
		{
			client_print ( teammate, print_chat, "%L", teammate, "ULTIMATE_SIV_PLAYER", name2 );
			
			if ( file_exists ( "sound/uwc3x/divineshield.wav" ) == 1 )
			{
				emit_sound ( teammate, CHAN_STATIC, "uwc3x/divineshield.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
		
		HasTeamShield[teammate]=true;
		if( CVAR_DEBUG_MODE)
		{
			log_amx( "[UWC3X] DEBUG :: TASK_SHIELD_Search -> TeamShield -> Shielder: %s Player: %s HasTeamShield[teammate]=true", name2, name );
		}
		
		p_PlayerShieldedBy[teammate] = id;
		p_ShieldMaxDamageAbsorbed[teammate] = 0;
		UsedTeamShield[id] = 1;
		
		new parm[3];
		parm[0] = teammate; //The guy with the shield
		parm[1] = id; //The guy who provided the shield
		parm[2] = 0;
		
		set_task ( 1.0, "TASK_SHIELD_CHECK", TASK_SHIELD_CHECK_ID + id, parm, 3 );
	}
	else
	{
		
		//Keep searching
		issearching[id] = true;
		icon_controller ( id );
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if ( parm[1] > 0 && get_user_health ( id ) >=0 )
		{
			set_task ( 0.1, "TASK_SHIELD_Search", TASK_ULTIMATE_SHIELD_SEARCH + id, parm, 3 );
		}
		else
		{
			issearching[id] = false;
			icon_controller ( id );
		}
		
	}
	
	return PLUGIN_CONTINUE;
}

public TASK_SHIELD_CHECK ( parm[3] )
{
	
	new id = parm[0]; //The guy with the shield
	new teammate = parm[1]; //The guy who provided the shield
	new shield_damage = parm[2];
	
	if ( ( get_user_team ( id ) != get_user_team ( teammate ) ) || !is_user_connected ( id ) || !is_user_connected ( teammate ) )
	{
		HasTeamShield[id]=false;
		
		//Remove teh Shield Check task
		if( task_exists(TASK_SHIELD_CHECK_ID + id) )
		{
			remove_task( TASK_SHIELD_CHECK_ID + id );
		}
		
		return PLUGIN_CONTINUE;
	}
	
	new MaxDamage = p_ShieldMaxDamage[p_skills[teammate][SKILLIDX_TEAMSHIELD]]
	new name[32], name2[32];
	
	get_user_name ( id, name, 31 );
	get_user_name ( teammate, name2, 31 );
	
	if( shield_damage <  MaxDamage )
	{
		HasTeamShield[id]=true;
		if( CVAR_DEBUG_MODE)
		{
			log_amx( "[UWC3X] DEBUG :: TASK_SHIELD_CHECK( ) -> TeamShield -> Setting HasTeamShield[teammate]=true");
		}
		
		p_PlayerShieldedBy[id] = teammate;
		parm[2] = p_ShieldMaxDamageAbsorbed[id];
		set_task ( 1.0, "TASK_SHIELD_CHECK", TASK_SHIELD_CHECK_ID + id, parm, 3 );
	}
	else
	{
		//Tell them its done
		if( Util_Should_Msg_Client(id) )
		{
			client_print ( id, print_chat, "%L", id, "ULTIMATE_SIV_SHIELDER_EXPIRED" );
		}
		if( Util_Should_Msg_Client(teammate) )
		{
			client_print ( teammate, print_chat, "%L", teammate, "ULTIMATE_SIV_PLAYER_EXPIRED", name2 );
		}
		
		//REmove teh Shield Check task
		if( task_exists(TASK_SHIELD_CHECK_ID + id) )
		{
			remove_task( TASK_SHIELD_CHECK_ID + id );
		}
		
		//Reset the vars
		HasTeamShield[id]=false;
		if( CVAR_DEBUG_MODE)
		{
			log_amx( "[UWC3X] DEBUG :: TASK_SHIELD_CHECK( ) -> TeamShield -> Setting HasTeamShield[teammate]=false -> Expired");
		}
		
		//Set cooldown
		new cooldownparm[1];
		cooldownparm[0] = teammate;
		
		//Now that its done, start the cooldown
		TeamShieldCooldown[teammate] = 1;
		set_task ( CVAR_TEAMSHIELD_COOLDOWN, "cooldown3", TASK_COOLDOWN3 + teammate, cooldownparm, 1 );
	}
	
	return PLUGIN_CONTINUE;
	
}


/* Chain lightning */
public TASK_CHAIN_Search ( parm[2] )
{
	new id = parm[0];
	new enemyz, body;
	get_user_aiming ( id, enemyz, body );
	
	if ( 0 < enemyz <=32 && ( get_user_team ( enemyz ) != get_user_team ( id ) ) && playeritem[enemyz] != IMMUNITY && !hasblink[enemyz] && is_user_alive ( id ) && is_user_alive ( enemyz ) )
	{
		ultimateused[id] = true;
		icon_controller ( id );
		new linewidth = 80;
		new damage = 75;
		issearching[id] = false;
		
		// [08-05-04] - Added Electricity resistance check - K2mia
		new actual_damage = damage;
		if ( USE_ENH && p_resists[enemyz][RESISTIDX_ELECTRIC] )
		{
			actual_damage = actual_damage - floatround ( ( float ( p_resists[enemyz][RESISTIDX_ELECTRIC] ) / float ( RESIST_MAX_VALUE ) ) * float ( actual_damage ) );
			
			if ( p_resists[enemyz][RESISTIDX_ELECTRIC] == RESIST_MAX_VALUE )
			{
				if( Util_Should_Msg_Client(enemyz) )
				{
					client_print ( enemyz, print_chat, "%L", enemyz, "ULTIMATE_LGHTNG_RESISTALL", MOD );
				}
			}
			else
			{
				if( Util_Should_Msg_Client(enemyz) )
				{
					client_print ( enemyz, print_chat, "%L", enemyz, "ULTIMATE_LGHTNG_RESIST", MOD );
				}
			}
		}
		
		EVENT_Do_Bolt ( id, enemyz, linewidth, actual_damage, id );
		
		new lightparm[4];
		lightparm[0]=enemyz;
		lightparm[1]=damage;
		lightparm[2]=linewidth;
		lightparm[3]=id;
		
		set_task ( 0.2, "TASK_CHAIN_Damage", TASK_CHAIN_DAMAGE, lightparm, 4 );
		
		new cooldownparm[1];
		cooldownparm[0] = id;
		set_task ( CVAR_LIGHTNING_COOLDOWN, "cooldown", TASK_COOLDOWN_RESET + id, cooldownparm, 1 );
	}
	else
	{
		issearching[id] = true;
		icon_controller ( id );
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if ( parm[1] > 0 && get_user_health ( id )>=0 )
		{
			set_task ( 0.1, "TASK_CHAIN_Search", TASK_ULTIMATE_CHAIN_SEARCH + id, parm, 2 );
		}
		else
		{
			issearching[id] = false;
			icon_controller ( id );
		}
	}
	
	return PLUGIN_CONTINUE;
}

public TASK_CHAIN_Damage ( parm[4] )
{
	// Chain Lightning
	new id = parm[0];
	new caster = parm[3];
	new origin[3], numberofplayers, players[32], targetorigin[3], i;
	new targetid = 0;
	new distancebetween = 0;
	new damage = parm[1]*2/3;
	new linewidth = parm[2]*2/3;
	new closestdistance = 0;
	new closestid = 0;
	
	get_user_origin ( id, origin );
	get_players ( players, numberofplayers );
	
	for ( i = 0; i < numberofplayers; ++i )
	{
		targetid = players[i];
		
		if ( get_user_team ( id ) != get_user_team ( targetid ) )
		{
			continue;
		}
		
		if ( get_user_team ( id ) == get_user_team ( targetid ) && is_user_alive ( targetid ) && is_user_alive ( id ) )
		{
			get_user_origin ( targetid, targetorigin );
			distancebetween = get_distance ( origin, targetorigin );
			if ( distancebetween < LIGHTNING_RANGE && playeritem[targetid] != IMMUNITY && !lightninghit[targetid] && !hasblink[targetid] && Util_IsPlayer_Immune ( targetid, 2 ) )
			{
				if ( distancebetween < closestdistance || closestid == 0 )
				{
					closestdistance = distancebetween;
					closestid = targetid;
				}
			}
		}
	}
	
	if ( closestid )
	{
		new actual_damage = damage;
		// [08-05-04] - Added Electricity resistance check - K2mia
		if ( USE_ENH && p_resists[closestid][RESISTIDX_ELECTRIC] )
		{
			actual_damage -= ( p_resists[closestid][RESISTIDX_ELECTRIC] / 100 ) * actual_damage;
			
			if ( p_resists[closestid][RESISTIDX_ELECTRIC] == RESIST_MAX_VALUE )
			{
				if( is_user_connected( closestid ) && !is_user_bot( closestid ) )
				{
					client_print ( closestid, print_chat, "%L", closestid, "ULTIMATE_LGHTNG_RESISTALL", MOD );
				}
			}
			else
			{
				if( is_user_connected( closestid ) && !is_user_bot( closestid ) )
				{
					client_print ( closestid, print_chat, "%L", closestid, "ULTIMATE_LGHTNG_RESIST", MOD );
				}
			}
		}
		
		//Increase damage by 20% if they have the wisdom for it
		if( p_wisdom_lightningdamagebonus[id] )
		{
			actual_damage += floatround( damage * WIS_LIGHTNINGDAMAGEBONUS );
			
			if ( CVAR_DEBUG_MODE )
			{
				client_print( id, print_console, "[%s DEBUG] Wisdom modified damage - NEW damage=( %d )", MOD, actual_damage );
			}
		}
		
		EVENT_Do_Bolt ( id, closestid, linewidth, actual_damage, caster );
		parm[0] = targetid;
		parm[1] = damage;
		parm[2] = linewidth;
		parm[3] = caster;
		
		set_task ( 0.2, "TASK_CHAIN_Damage", TASK_CHAIN_DAMAGE, parm, 4 );
		
	}
	else
	{
		for ( i = 0; i < numberofplayers; ++i )
		{
			targetid = players[i];
			lightninghit[targetid] = false;
		}
	}
	return PLUGIN_CONTINUE;
}



/* Suicide Bomber */
//apacheexplode
public TASK_Suicide_Explode ( parm[] )
{
	// Suicide Bomber
	new id = parm[0];
	if ( ( get_user_team ( id ) == SPEC ) || !is_user_connected( id ) )
	{
		return PLUGIN_CONTINUE;
	}
	
	new origin[3];
	get_user_origin ( id, origin );
	
	// random explosions
	message_begin ( MSG_PVS, SVC_TEMPENTITY, origin );
	
	// This just makes a dynamic light now
	write_byte ( TE_EXPLOSION );
	
	write_coord ( origin[0] + random_num ( -100, 100 ) );
	write_coord ( origin[1] + random_num ( -100, 100 ) );
	write_coord ( origin[2] + random_num ( -50, 50 ) );
	write_short ( g_sModelIndexFireball );
	
	// scale * 10
	write_byte ( random_num ( 0,20 ) + 20 );
	
	// framerate
	write_byte ( 12 );
	
	write_byte ( TE_EXPLFLAG_NONE );
	message_end ( );
	
	// lots of smoke
	message_begin ( MSG_PVS, SVC_TEMPENTITY, origin );
	
	write_byte ( TE_SMOKE );
	write_coord ( origin[0] + random_num ( -100, 100 ) );
	write_coord ( origin[1] + random_num ( -100, 100 ) );
	write_coord ( origin[2] + random_num ( -50, 50 ) );
	write_short ( g_sModelIndexSmoke );
	write_byte ( 60 ); // scale * 10
	write_byte ( 10 ); // framerate
	message_end ( );
	
	new players[32], targetorigin[3], numberofplayers, i, targetid;
	new distancebetween, damage, multiplier;
	
	get_players ( players, numberofplayers );
	
	for ( i = 0; i < numberofplayers; ++i )
	{
		targetid = players[i];
		
		if ( ( get_user_team ( targetid ) == SPEC ) || !is_user_alive ( targetid ) || !is_user_connected ( targetid ) )
		{
			continue;
		}
		
		get_user_origin ( targetid, targetorigin );
		distancebetween = get_distance ( origin, targetorigin );
		
		if ( distancebetween < CVAR_EXPLODE_MAX_RANGE && Util_NotSame_Team ( id, targetid ) )
		{
			if ( temp_immunity[targetid]  || Util_IsPlayer_Immune ( targetid, 1 ) || Util_IsPlayer_Immune ( targetid, 2 )  )
			{
				//They resistted
				temp_immunity[targetid] = false;
				
				if( Util_Should_Msg_Client( targetid ) )
				{
					client_print ( targetid, print_chat, "%L", targetid, "ULTIMATE_SUICIDE_RESIST", MOD );
				}
				
				new iparm[2];
				
				iparm[0] = targetid;
				copy( iparm[1], 31, "Suicide Bomber" );
				set_task ( 1.5, "Task_Reset_Immunity", TASK_RESET_IMMUNITY+targetid, iparm, 2 );
			}
			else
			{
				//They did not resist
				multiplier = CVAR_EXPLODE_MAX_DAMAGE * CVAR_EXPLODE_MAX_DAMAGE / CVAR_EXPLODE_MAX_RANGE;
				damage = ( CVAR_EXPLODE_MAX_RANGE - distancebetween ) * multiplier;
				damage = sqrt ( damage );
				
				if ( is_user_alive ( targetid ) )
				{
					do_damage ( targetid, id, damage, 12, 3, 0, 0, 0 );
				}
				
			}
		}
		
		if ( distancebetween < CVAR_EXPLODE_MAX_RANGE )
		{
			if( Util_Should_Msg_Client( targetid ) )
			{
				message_begin ( MSG_ONE, gmsgShake, {0, 0, 0}, targetid );
				write_short ( 1<<14 );// amplitude
				write_short ( 1<<13 );// duration
				write_short ( 1<<14 );// frequency
				message_end ( );
			}
		}
	}
	
	--parm[1];
	
	if ( parm[1] > 0 )
	{
		set_task ( 0.1, "TASK_Suicide_Explode", TASK_SUICIDE_EXPLODE_NOID, parm, 2 );
	}
	
	return PLUGIN_CONTINUE;
}

public TASK_Destroy_Mine ( args[] )
{
	new id = args[0];
	new ents = -1;
	
	ents = find_ent_by_owner(ents,"Mine",id)
	while (ents > 0)
	{
		remove_entity ( ents );
		ents = find_ent_by_owner(ents,"Mine",id)
	}
	
	remove_entity ( args[1] );
}

public TASK_Cleanup_Mine( args[])
{
	//new id = args[0];
	new ent = args[1];
	remove_entity(ent);
}

/* Decoy */
public TASK_Cleanup_Decoy ( args[] )
{
	
	new id = args[0];
	new ent = args[1];
	
	new Float:orig[3];
	
	entity_get_vector ( ent, EV_VEC_origin, orig );
	message_begin ( MSG_BROADCAST,SVC_TEMPENTITY );
	write_byte ( 11 );
	write_coord ( floatround ( orig[0] ) );
	write_coord ( floatround ( orig[1] ) );
	write_coord ( floatround ( orig[2] ) );
	message_end ( );
	
	decoy[id] = 0;
	
	remove_entity ( ent );
	
	if( Util_Should_Msg_Client(id) )
	{
		client_print ( id, print_chat, "%L", id, "ULTIMATE_DECOY_EXPIRED" );
	}
}

public TASK_CHECK_USER_SPEED( )
{
	for ( new i = 1; i <= get_maxplayers ( ); ++i )
	{
		if ( is_user_alive ( i ) )
		{
			new speedparm[1];
			speedparm[0] = i;
			Set_Speed( speedparm );
		}
	}
}

public TASK_CHECK_FOOTSTEPS ( )
{
	for ( new i = 1; i <= get_maxplayers ( ); ++i )
	{
		if ( is_user_alive ( i ) )
			Set_Cat_Footsteps( i );
	}
}
public TASK_Check_Duck ( )
{
	
	for ( new i = 1; i <= get_maxplayers ( ); ++i )
	{
		if ( is_user_alive ( i ) )
		{
			if ( decoy[i] )
			{
				if ( get_user_button ( i )& IN_DUCK )
				{
					if ( !pIsDucking[i] )
					{
						pIsDucking[i] = true;
						DoOnce[i] = true;
					}
				}
				else
				{
					if ( pIsDucking[i] )
					{
						//client_print ( i, print_chat, "Stopped ducking" )
						pIsDucking[i] = false;
						DoOnce[i] = true;
					}
				}
			}
		}
	}
	return PLUGIN_CONTINUE;
}

public Task_Server_Frame ( )
{
	new id;
	new Float:vel[3];
	new Float:speed;
	new Float:new_frame = get_gametime ( );
	new Float:newAngle[3];
	new Float:orig[3];
	new Float:framerate = 30.0;
	new Float:MinBox[3];
	new Float:MaxBox[3];
	new Float:vRetVector[3];
	new Float:tmpVec[3];
	
	if ( ( new_frame - last_frame ) < ( 1.0 / framerate ) )
	{
		return PLUGIN_CONTINUE;
	}
	
	last_frame = new_frame;
	
	for ( id=0; id < MAX_PLAYERS; id++ )
	{
		if ( !decoy[id] || !is_user_connected ( id ) )
		{
			continue;
		}
		
		if ( pIsDucking[id] )
		{
			MinBox[0] = 0.0;
			MinBox[1] = 0.0;
			MinBox[2] = -20.0; //change to -40 for standing models
			MaxBox[0] = 0.0;
			MaxBox[1] = 0.0;
			MaxBox[2] = 0.0;
		}
		else
		{
			MinBox[0] = 0.0;
			MinBox[1] = 0.0;
			MinBox[2] = -40.0; //change to -20 for crouching models
			MaxBox[0] = 0.0;
			MaxBox[1] = 0.0;
			MaxBox[2] = 0.0;
		}
		
		entity_set_vector ( decoy[id], EV_VEC_mins, MinBox );
		entity_get_vector ( id, EV_VEC_v_angle, vRetVector );
		
		vRetVector[0] = float ( 0 );
		
		entity_set_vector ( decoy[id], EV_VEC_angles, vRetVector );
		entity_get_vector ( decoy[id], EV_VEC_velocity, vel );
		
		if ( vel[0] != 0.0 && vel[1] != 0.0 )
		{
			vel[2] = 0.0;
			vector_to_angle ( vel, newAngle );
		}
		
		vel[2] = 0.0;
		speed = vector_length ( vel );
		
		if ( speed <= 5 && pIsDucking[id] )
		{
			if ( DoOnce[id] )
			{
				entity_get_vector ( decoy[id], EV_VEC_origin, orig );
				orig[2] = orig[2] - 20;
				entity_set_vector ( decoy[id], EV_VEC_origin, orig );
				DoOnce[id] = false;
			}
			
			decoy_seq[id] = 2;
			entity_set_int ( decoy[id], EV_INT_sequence, 2 );
			
			MinBox[0] = -20.0;
			MinBox[1] = -20.0;
			MinBox[2] = -20.0;
			MaxBox[0] = 20.0;
			MaxBox[1] = 20.0;
			MaxBox[2] = 40.0;
			
			entity_set_vector ( decoy[id], EV_VEC_mins, MinBox );
			entity_set_vector ( decoy[id], EV_VEC_maxs, MaxBox );
			
			tmpVec[0] = 40.0; tmpVec[1] = 40.0; tmpVec[2] = 80.0;
			entity_set_vector ( decoy[id], EV_VEC_size, tmpVec );
		}
		else if ( speed <= 5 && !pIsDucking[id] )
		{
			if ( DoOnce[id] )
			{
				entity_get_vector ( decoy[id], EV_VEC_origin, orig );
				orig[2] = orig[2] + 20;
				entity_set_vector ( decoy[id], EV_VEC_origin, orig );
				DoOnce[id] = false;
			}
			
			decoy_seq[id] = 1;
			entity_set_int ( decoy[id], EV_INT_sequence, 1 );
			
			MinBox[0] = -20.0;
			MinBox[1] = -20.0;
			MinBox[2] = -40.0;
			MaxBox[0] = 20.0;
			MaxBox[1] = 20.0;
			MaxBox[2] = 40.0;
			
			entity_set_vector ( decoy[id],EV_VEC_mins, MinBox );
			entity_set_vector ( decoy[id],EV_VEC_maxs, MaxBox );
			
			tmpVec[0] = 40.0;
			tmpVec[1] = 40.0;
			tmpVec[2] = 80.0;
			entity_set_vector ( decoy[id], EV_VEC_size, tmpVec );
		}
		
		decoy_fstep[id] = 5.0;
		decoy_frame[id] += decoy_fstep[id];
		
		if ( decoy_frame[id] >= 254.0 )
		{
			decoy_frame[id] = 0.0;
		}
		
		entity_set_float ( decoy[id], EV_FL_frame, decoy_frame[id] );
	}
	
	return PLUGIN_CONTINUE;
	
}



/* Entangle Roots */
public Task_Destroy_Roots ( args[] )
{
	remove_entity ( args[0] );
}


public searchtarget(parm[2])
{
	new id = parm[0];
	new enemy, body;
	get_user_aiming(id,enemy,body);
	
	if ( (0<enemy<=32) && (p_resists[enemy][RESISTIDX_MAGIC] >= RESIST_MAX_VALUE) || (!temp_immunity[enemy] && magic_saving_throw(enemy)) )
	{
		temp_immunity[enemy] = true;
		if ( Util_Should_Msg_Client( enemy ) )
		{
			client_print ( enemy, print_chat, "%L", enemy, "ULTIMATE_ENGANGLE_RESISTANT", MOD );
		}
		
		new iparm[2];
		iparm[0] = enemy;
		iparm[1] = 1;
		set_task ( 5.0, "Task_Reset_Immunity", TASK_RESET_IMMUNITY + id, iparm, 2 );
	}
	
	if ( 0<enemy<=32 && !stunned[enemy] && get_user_team(id)!=get_user_team(enemy) && playeritem[enemy]!=IMMUNITY && !hasblink[enemy] && is_user_alive(id) && is_user_alive(enemy) && !temp_immunity[enemy] )
	{
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);
		
		if ( Util_Should_Msg_Client( id ) )
		{
			if ( file_exists ( "sound/uwc3x/entanglingroots.wav" ) == 1 )
			{
				emit_sound ( id, CHAN_STATIC, "uwc3x/entanglingroots.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
		
		new waitparm[6];
		waitparm[0]=enemy;
		waitparm[1]=100;
		waitparm[5]=floatround(get_user_maxspeed(enemy));
		set_user_maxspeed(enemy,1.0);
		Task_Entangle_Stop(waitparm);
		
		stunned[enemy]=true;
		new cooldownparm[1];
		cooldownparm[0]=id;
		set_task ( CVAR_ENTANGLE_COOLDOWN, "cooldown", 50 + id, cooldownparm, 1 );
	}
	else
	{
		issearching[id]=true;
		icon_controller(id);
		new counter = parm[1];
		while (counter >= 0)
		{
			counter -= 10;
			if (counter==0)
				emit_sound(id,CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
		
		--parm[1]
		if (parm[1]>0 && get_user_health(id)>0)
		{
			set_task(0.1, "searchtarget", TASK_ULTIMATE_ENTANGLE_SEARCH+id, parm, 2);
		}
		else
		{
			issearching[id]=false;
			icon_controller(id);
		}
	}
	return PLUGIN_CONTINUE;
}


public Task_Entangle_Stop ( parm[6] )
{
	new id=parm[0];
	new origin[3];
	get_user_origin ( id, origin );
	
	if ( origin[0] == parm[2] && origin[1] == parm[3] && origin[2] == parm[4] )
	{
		new normalspeed = parm[5];
		new resetparm[2];
		resetparm[0] = id;
		resetparm[1] = normalspeed;
		set_task ( float ( parm[1]/10 ), "reset_maxspeed", TASK_RESET_MAXSPEED + id , resetparm, 2 );
		
		new entangleparm[2];
		entangleparm[0] = parm[0];
		entangleparm[1] = parm[1];
		Event_Entangle ( entangleparm );
	}
	else
	{
		parm[2] = origin[0];
		parm[3] = origin[1];
		parm[4] = origin[2];
		set_task ( 0.1, "Task_Entangle_Stop", TASK_ENTANGLE_STOP +id, parm, 6 );
	}
	
	return PLUGIN_CONTINUE;
}




/* Constitution regeneration */
public con_heal( parm[] )
{
	
	new id = parm[0];
	new heal = parm[1];
	new Float:interval = CON_HEAL_INTERVAL;
	
	if ( !endround && is_user_alive( id ) && ( p_attribs[id][ATTRIBIDX_CON] > ATTRIB_BASE ) )
	{
		new econ = (p_attribs[id][ATTRIBIDX_CON] - ATTRIB_BASE );
		if ( econ != heal )
		{
			parm[1] = econ;
			heal = econ ;
		}
		
		set_task( interval, "con_heal", id + CONSTITUTION_REGEN, parm, 2 );
	}
	
	new health = 0;
	new bool:was_healed = false;
	
	health = maxhealth[id] + ( playeritem[id] == HEALTH ? HEALTHBONUS : 0 );
	if ( get_user_health( id ) < health )
	{
		was_healed = true;
		set_user_health_log( id, get_user_health( id ) + heal );
	}
	
	// [09-26-04] Adjustment if maxhealth exceeded - K2mia
	if ( get_user_health( id ) > health )
	{
		set_user_health_log( id, health );
	}
	
	if (!was_healed)
	{
		return PLUGIN_CONTINUE;
	}
	
	new origin[3];
	get_user_origin( id, origin );
	
	if( playeritem[id] != CLOAK && ( !p_skills[id][SKILLIDX_INVIS] ) )
	{
		message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
		write_byte( TE_IMPLOSION );
		write_coord( origin[0] ); // initial position
		write_coord( origin[1] ); // initial position
		write_coord( origin[2] ); // initial position
		write_byte( 100 ); // radius
		write_byte( 8 ); // count
		write_byte( 1 ); // life
		message_end();
	}
	
	return PLUGIN_CONTINUE;
}
public Task_Check_Const_Regen( id )
{
	
	// [08-04-04] - Constitution health regen code - K2mia
	if (p_attribs[id][ATTRIBIDX_CON] > ATTRIB_BASE)
	{
		// Remove running task for Con Health
		if (task_exists(id+1100))
		{
			remove_task(id+1100);
		}
		
		new newparm[2];
		newparm[0] = id;
		newparm[1] = ( p_attribs[id][ATTRIBIDX_CON] - ATTRIB_BASE );
		
		set_task( 1.0, "con_heal", id + CONSTITUTION_REGEN, newparm, 2 );
	}
	else
	{
		if (task_exists(id+1100))
		{
			remove_task(id+1100);
		}
	}
	
	return PLUGIN_CONTINUE;
}


/* Check for leather skin or steel skin bonus */
public Task_Check_Skin_Bonus( id )
{
	
	// [09-04-04] - Modified for helmet and suit checks, maxarmor modifier - K2mia
	if (p_skills[id][SKILLIDX_LSKIN])
	{
		// Set player adjusted max. armor for use with repair armor
		new abonusmult = 0;
		new abonus = 0;
		
		// If Steel Skin trained use improved armor bonus
		if (p_skills[id][SKILLIDX_SSKIN])
		{
			helmet[id] = true;
			abonusmult = ARMORBONUS2;
		}
		else
		{
			helmet[id] = false;
			abonusmult = ARMORBONUS1;
		}
		
		if (p_level[id] > 30)
			abonus = (abonusmult * 6);
		else if (p_level[id] > 25)
			abonus = (abonusmult * 5);
		else if (p_level[id] > 20)
			abonus = (abonusmult * 4);
		else if (p_level[id] > 15)
			abonus = (abonusmult * 3);
		else if (p_level[id] > 10)
			abonus = (abonusmult * 2);
		else
			abonus = abonusmult;
		
		hassuit[id] = true;
		maxarmor[id] = (NORMALARMORMAX + abonus);
		
	}
	else
	{
		// Set player default max. armor for use with repair armor
		if (get_user_armor(id) > 0)
		{
			maxarmor[id] = 100;
			hassuit[id] = true;
		}
		else
		{
			maxarmor[id] = 0;
		}
	}
	
	return PLUGIN_CONTINUE;
}


/* MOLE AND FAN OF KNIVES */
public Task_Check_Fan( id )
{
	if ( p_skills[id][SKILLIDX_FAN] && is_user_alive( id ) )
	{
		//Fan of Knives
		new Float:randomnumber = random_float( 0.0, 1.0 );
		if ( randomnumber <= p_fan[p_skills[id][SKILLIDX_FAN]-1] )
		{
			new parm[2];
			parm[0] = id;
			parm[1] = 7;
			set_task( 0.1, "Check_spot", TASK_CHECK_SPOT + 12, parm, 2 );
		}
	}
}

public Task_Transport2( parm[6] )
{
	// Teleports the MOLE to the opposing team's base (new version)
	new id = parm[5];
	new origin[3];
	new Float:forigin[3];
	new Float:vicinity = 96.0;
	new entsFound[1];
	
	origin[0] = parm[0];
	origin[1] = parm[1];
	origin[2] = parm[2];
	
	forigin[0] = float( parm[0] );
	forigin[1] = float( parm[1] );
	forigin[2] = float( parm[2] );
	
	// Perform a final check to make sure this MOLE spot wasn't taken
	new numplayers = find_sphere_class( 0, "player", vicinity, entsFound, 1, forigin );
	
	if (numplayers > 0)
	{
		if (hasmole[id] && is_user_connected( id ) && !is_user_bot( id ) )
		{
			client_print( id, print_chat, "%L", id, "MOLE_NO_SLOT" );
		}
		else
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "MOLE_SLOT" );
			}
		}
		
		return PLUGIN_HANDLED;
	}
	
	if( Util_Should_Msg_Client(id) )
	{
		client_print( id, print_chat, "%L", id, "MOLE_READY", origin[0], origin[1], origin[2] );
	}
	
	
	ismole[id] = true;
	changeskin( id, 0 );
	set_user_origin( id, origin );
	
	if( Util_Should_Msg_Client(id) )
	{
		client_print( id, print_chat, "%L", id, "MOLE_BLIND", MOD );
		
		message_begin( MSG_ONE, gMsgScreenFade, { 0, 0, 0 }, id );
		write_short( 1<<15 );
		write_short( 1<<10 );
		write_short( 0 );
		write_byte( 255 );
		write_byte( 255 );
		write_byte( 255 );
		write_byte( 255 );
		message_end();
		
		message_begin(MSG_ONE,gmsgShake,{0,0,0},id);
		write_short( 255<<14 ); //ammount
		write_short( 10<<14 ); //lasts this long
		write_short( 255<<14 ); //frequency
		message_end();
	}
	
	if ( playeritem2[id] == MOLE)
	{
		playeritem2[id] = 0;
	}
	
	hasmole[id] = false;
	return PLUGIN_CONTINUE;
}

public Check_spot( parm[] )
{
	new id = parm[0];
	
	if (get_user_team(id) == 1)
	{
		mole_CT( id );
	}
	else if (get_user_team(id) == 2)
	{
		mole_T( id );
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "MOLE_JOIN_TEAM" );
		}
	}
	
	return PLUGIN_HANDLED;
}


//Jumpkick
public Task_Jumpkick_Cooldown( parm[] )
{
	new id = parm[0];
	kickflag[id] = 0;
}


//TeamShield
public Task_Teamshield_Cooldown( parm[] )
{
	//new id = parm[0];
	
}

public Task_Reset_Shopmenu3( parm[] )
{
	new id = parm[0];
	
	if( !is_user_connected( id ) || !is_user_alive( id ) )
		return PLUGIN_HANDLED;
	
	new reset_item = parm[1];
	playeritem3[id] = 0;
	
	if( reset_item == 1)
	{
		playerCanBuyitem3[id] = 1;
		
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 3.0, 0.1, 0.2, 1);
			show_hudmessage(id, "%L", id, "SM3_CAN_BUY", MOD);
		}
		
	}
	else if( reset_item == 2 )
	{
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 5.0, 0.1, 0.2, 1);
			show_hudmessage(id, "%L", id, "SM3_VULNERABLE", MOD);
		}
	}
	else if( reset_item == 3 )
	{
		set_entity_visibility ( id, 1 );
		if( Util_Should_Msg_Client(id) )
		{
			set_hudmessage(0, 255, 255, 0.0, 0.55, 0, 6.0, 3.0, 0.1, 0.2, 1);
			show_hudmessage(id, "%L", id, "SM3_VISIBLE", MOD);
			if ( file_exists( "sound/uwc3x/shopmenu/sm3_inv_done.wav" ) == 1 )
			{
				emit_sound( id, CHAN_STATIC, "uwc3x/shopmenu/sm3_inv_done.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}
	}
	
	return PLUGIN_CONTINUE;
	
}


public Task_Reset_Cripple( parm[] )
{
	new id = parm[0];
	new enemy = parm[2];
	stunned[id] = false;
	slowed[id] = false;
	crippletype[id] = 0;
	iscrippled[id] = 0;
	
	//Only care if they are alive and actually are crippled, otherwise dont reset
	if( is_user_alive( id ) && iscrippled[id] )
	{
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print( id, print_chat, "%L", id, "ULTIMATE_CRIPPLE_WORE_OFF1", MOD );
			client_print( id, print_center, "%L", id, "ULTIMATE_CRIPPLE_WORE_OFF2" );
		}
		
		if( Util_Should_Msg_Client_Alive( enemy ) )
		{
			new idname[32];
			get_user_name( id, idname, 31 );
			
			client_print( enemy, print_chat, "%L", enemy, "ULTIMATE_CRIPPLE_WORE_OFF3", MOD, idname );
			client_print( enemy, print_center, "%L", enemy, "ULTIMATE_CRIPPLE_WORE_OFF4", idname );
		}
		
		//set_user_maxspeed(id,oldSpeed[id]);
		//oldSpeed[id] = 0.0;
		//new speedparm[1];
		//speedparm[0] = id;
		//Set_Speed( speedparm );
		//set_task( 0.1, "reset_maxspeed", TASK_RESET_MAXSPEED + id, parm, 3 );
	}
	
	new normalspeed = floatround( get_user_maxspeed( id ) );
	new parm[2];
	parm[0] = id;
	parm[1] = normalspeed;
	set_task( 1.0, "reset_maxspeed", TASK_RESET_MAXSPEED+id, parm, 2 );
	
}


// Locust Swarm
public Task_locust_function( id )
{
	new parm[11];
	parm[7]=id;
	new players[32], numberofplayers, i, player, possibility[MAX_PLAYERS], count = 0;
	get_players(players, numberofplayers);
	
	for (i = 0; i < numberofplayers; ++i)
	{
		player=players[i];
		
		if( Util_Is_Valid_Player( player ) && Util_NotSame_Team(player,id) && is_user_alive(player) && ( playeritem[player]!=IMMUNITY || !hasblink[player] ) )
		{
			possibility[count] = player;
			count++;
		}
	}
	
	if (count==0)
	{
		if( Util_Should_Msg_Client_Alive( id )  )
		{
			set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
			show_hudmessage(id,"No valid targets found, please try again later!");
		}
		
		log_amx( "[UWC3X] DEBUG :: Task_locust_function -> count=0");
		return PLUGIN_CONTINUE;
	}
	
	parm[6] = 0 // Initialize target parameter
	
	//client_print(id, print_console, "DEBUG: before-count=(%d) parm6=(%d)", count, parm[6])
	
	// Prevents target from being the server
	while (parm[6] == 0)
	{
		parm[6] = possibility[random_num(0, count)]
	}
	
	//client_print(id, print_console, "DEBUG: after-count=(%d) parm6=(%d)", count, parm[6])
	
	if ( parm[6] > numberofplayers || !Util_Is_Valid_Player( parm[6] ) )
	{
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
			show_hudmessage(id,"No valid targets found!")
			return PLUGIN_CONTINUE
		}
	}
	
	new debugname[32];
	get_user_name(parm[6],debugname,31);
	
	if( CVAR_DEBUG_MODE)
	{
		log_amx( "[UWC3X] DEBUG :: Task_locust_function -> VALID Player=%d %s  -> Moving on", parm[6], debugname );
	}
	
	new origin[3], origin2[3];
	get_user_origin(id,origin);
	get_user_origin(parm[6],origin2);
	parm[0]=origin[0];
	parm[1]=origin[1];
	parm[2]=origin[2];
	ultimateused[id]=true;
	Task_locust_drawfunnels(parm);
	
	if( Util_Should_Msg_Client_Alive( id ) )
	{
		if (file_exists("sound/uwc3x/locustswarmloopwav.wav")==1)
		{
			emit_sound(id, CHAN_ITEM, "uwc3x/locustswarmloopwav.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
		}
	}
	
	return PLUGIN_CONTINUE;
}

public Task_locust_drawfunnels(parm[])
{
	new MULTIPLIER = 150; // the lower the number the faster it reaches the target
	new id = parm[6];
	new caster = parm[7];
	new origin[3], funnel[3], name[32], name2[32];
	get_user_name(id,name,31);
	get_user_name(caster,name2,31);
	
	if( Util_Should_Msg_Client_Alive( caster ) )
	{
		if (file_exists("sound/uwc3x/locustswarmloopwav.wav")==1)
		{
			emit_sound(caster, CHAN_ITEM, "uwc3x/locustswarmloopwav.wav", 1.0,ATTN_NORM, 0, PITCH_NORM);
		}
	}
	
	if( Util_Should_Msg_Client_Alive( id ) )
	{
		if (file_exists("sound/uwc3x/locustswarmloopwav.wav")==1)
		{
			emit_sound(id, CHAN_ITEM, "uwc3x/locustswarmloopwav.wav", 1.0,ATTN_NORM, 0, PITCH_NORM);
		}
	}
	
	if ( Util_IsPlayer_Immune ( id, 2 )  )
	{
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print( id, print_chat, "[%s] Your magic resistance protects you from a Locust Swarm", MOD);
		}
		
		if( Util_Should_Msg_Client_Alive( caster )  )
		{
			set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
			show_hudmessage(caster,"Your locusts were resistsed by Player %s ", name );
		}
		
		if( CVAR_DEBUG_MODE)
		{
			log_amx( "[UWC3X] DEBUG :: Task_locust_drawfunnels -> Locusts Avoided Resistance Check - Caster=%s Player %s ", name2, name );
		}
		
		ultimateused[caster]=true;
		icon_controller(caster);
		return PLUGIN_CONTINUE;
	}
	
	if( CVAR_DEBUG_MODE)
	{
		log_amx( "[UWC3X] DEBUG :: Task_locust_drawfunnels -> Locusts Hit - Caster=%s Player %s", name2, name );
	}
	get_user_origin(id,origin);
	
	funnel[0]=parm[0];                       // Origin of the funnel
	funnel[1]=parm[1];
	funnel[2]=parm[2];
	
	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte( TE_LARGEFUNNEL );
	write_coord(funnel[0]);         // origin, x
	write_coord(funnel[1]);         // origin, y
	write_coord(funnel[2]);         // origin, z
	write_short(snow);              // sprite (0 for none)
	write_short(0);                 // 0 for collapsing, 1 for sending outward
	message_end();
	
	new xdist = diff(origin[0],funnel[0]);
	new ydist = diff(origin[1],funnel[1]);
	new zdist = diff(origin[2],funnel[2]);
	
	if (diff(origin[0],(funnel[0]-MULTIPLIER))<xdist)
		parm[0]=funnel[0]-MULTIPLIER;
	else if(diff(origin[0],(funnel[0]+MULTIPLIER))<xdist)
		parm[0]=funnel[0]+MULTIPLIER;
	else
		parm[0]=origin[0];
	
	if (diff(origin[1],(funnel[1]-MULTIPLIER))<ydist)
		parm[1]=funnel[1]-MULTIPLIER;
	else if(diff(origin[1],(funnel[1]+MULTIPLIER))<ydist)
		parm[1]=funnel[1]+MULTIPLIER;
	else
		parm[1]=origin[1];
	
	if (diff(origin[2],(funnel[2]-MULTIPLIER))<zdist)
		parm[2]=funnel[2]-MULTIPLIER;
	else if(diff(origin[2],(funnel[2]+MULTIPLIER))<zdist)
		parm[2]=funnel[2]+MULTIPLIER;
	else
		parm[2]=origin[2];
	
	if (!endround)
	{
		if (!(xdist<50 && ydist<50 && zdist<50))
		{
			set_task( 0.1, "Task_locust_drawfunnels", id+800, parm, 11 );
		}
		else
		{
			new pDamageMultiplier = pDamageMultiplier = p_skills[caster][SKILLIDX_LOCUST];
			new actual_damage = 20 * pDamageMultiplier;
			
			if( CVAR_DEBUG_MODE)
			{
				log_amx( "[UWC3X] DEBUG :: Task_locust_drawfunnels -> pDamageMultiplier=%d actual_damage=%d", pDamageMultiplier, actual_damage );
			}
			
			do_damage(id, caster, actual_damage, 15, 3, 0, 0, 0);
			
			new Float:speed = get_user_maxspeed( id );
			if(speed > 1.0 && speed != oldSpeed[id])
			{
				oldSpeed[id] = speed;
			}
			
			set_user_maxspeed( id, LOCUSTSPEED );
			
			if( Util_Should_Msg_Client_Alive( caster )  )
			{
				set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
				show_hudmessage(caster,"Your locusts hurt Player %s ", name );
			}
			
			new parm[2];
			parm[0] = id;
			reset_maxspeed ( parm );
			
			set_task( float( 2 * p_skills[caster][SKILLIDX_LOCUST]), "reset_maxspeed", TASK_RESET_MAXSPEED+id, parm, 1 );
			
			ultimateused[caster]=true;
			icon_controller(caster);
			new cooldownparm[1];
			cooldownparm[0]=caster;
			set_task(CVAR_LOCUST_COOLDOWN,"cooldown",50+id,cooldownparm,1);
		}
	}
	
	return PLUGIN_CONTINUE;
}



//Total Blindness 
public Task_Search_Flash( parm[2] )
{
	new id = parm[0];
	new enemy, body;
	get_user_aiming(id,enemy,body);
	
	if( Util_Is_Valid_Player(enemy) && !stunned[enemy] && Util_NotSame_Team(id,enemy) && playeritem[enemy]!=IMMUNITY && !hasblink[enemy] && is_user_alive(id) && is_user_alive(enemy) && (p_resists[enemy][RESISTIDX_MAGIC] < RESIST_MAX_VALUE) && !magic_saving_throw(enemy) )
	{
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);
		
		new name[32], ename[32];
		get_user_name( id , name, 31);
		get_user_name( enemy , ename, 31);
		
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			client_print(id, print_chat, "%L", id, "ULTIMATE_BLIND_YOU", MOD, ename);
		}
		
		if( Util_Should_Msg_Client_Alive( enemy ) )
		{
			client_print(enemy, print_center, "%L", enemy, "ULTIMATE_BLIND_ENEMY", name);
			Task_Ult_Do_Flash( enemy );
		}
		
		new cooldownparm[1];
		cooldownparm[0]=id;
		set_task( CVAR_FLASH_COOLDOWN, "cooldown", 50+id, cooldownparm, 1);
	}
	else
	{
		issearching[id]=true;
		icon_controller(id);
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if (parm[1]>0 && get_user_health(id)>0)
		{
			set_task(0.1, "Task_Search_Flash", 200+id, parm, 2);
		}
		else
		{
			issearching[id]=false;
			icon_controller(id);
		}
	}
	return PLUGIN_CONTINUE;
}

public Task_Ult_Do_Flash(id)
{
	
	if( Util_Should_Msg_Client(id) )
	{
		
		message_begin(MSG_ONE,gMsgScreenFade,{0,0,0},id);
		write_short( 2<<12 );
		write_short( 2<<12 );
		write_short( 1<<1 );
		write_byte( 0 );
		write_byte( 0 );
		write_byte( 0 );
		write_byte( 255 );
		message_end();
		
		if( Util_Should_Msg_Client_Alive( id ) )
		{
			emit_sound(id,CHAN_BODY, "weapons/flashbang-2.wav", 1.0, ATTN_NORM, 0, PITCH_HIGH);
		}
	}
}

public reloadAmmo(id)
{
	if (!Util_Is_Valid_Player(id))
		return;
	
	if (gReloadTime[id] >= get_systime() - 1)
		return;
	
	gReloadTime[id] = get_systime();
	
	new clip, ammo, wpn[32];
	new wpnid = get_user_weapon(id, clip, ammo);
	
	if( !IsWeaponPrimary( wpnid ) && !IsWeaponSecondary( wpnid ) )
		return;
	
	if (clip == 0)
	{
		get_weaponname(wpnid,wpn,31);
		new iWPNidx = -1;
		while((iWPNidx = find_ent_by_class(iWPNidx, wpn)) != 0)
		{
			if(id == entity_get_edict(iWPNidx, EV_ENT_owner))
			{
				cs_set_weapon_ammo(iWPNidx, getMaxClipAmmo(wpnid));
				break;
			}
		}
	}
}


public Task_Switch_UnlimitedAmmoOn( id )
{
	new name[32];
	get_user_name( id , name, 31);
	
	new intTime = floatround( CVAR_UNLIMITED_AMMO_TIME );
	
	if( Util_Should_Msg_Client_Alive( id )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage(id,"You now have unlimited Ammo for %i seconds!", intTime );
		client_print(id, print_chat, "%L", id, "ULTIMATE_UAMMO_YOU1", MOD, intTime );
	}
	
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] Debug:: Task_Switch_UnlimitedAmmoOff -> unammo[ %s ] = ON ", name );
	}
	
	unammo[id] = true;
}

public Task_Switch_UnlimitedAmmoOff( parm[] )
{
	new id = parm[0];
	new name[32];
	get_user_name( id , name, 31);
	
	if( Util_Should_Msg_Client_Alive( id )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage(id,"Your unlimited Ammo is now gone, better reload fast!");
		client_print(id, print_chat, "%L", id, "ULTIMATE_UAMMO_YOU2", MOD);
	}
	
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] Debug:: Task_Switch_UnlimitedAmmoOff -> unammo[ %s ] = OFF ", name );
	}
	
	
	unammo[id] = false;
}

public Task_Search_BadAim( parm[] )
{
	new id = parm[0];
	new enemy, body;
	get_user_aiming(id,enemy,body);
	
	if( Util_Is_Valid_Player(enemy) && !stunned[enemy] && Util_NotSame_Team(id,enemy) && playeritem[enemy]!=IMMUNITY && !hasblink[enemy] && is_user_alive(id) && is_user_alive(enemy) && !magic_saving_throw(enemy) )
	{
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);
		
		new name[32], ename[32];
		get_user_name( id , name, 31);
		get_user_name( enemy , ename, 31);
		Task_Switch_BadAimOn( id, enemy );
		
		new barTime = floatround( CVAR_BADAIM_TIME );
		
		if( Util_Should_Msg_Client( enemy ) )
		{
			message_begin ( MSG_ONE, 108, { 0, 0, 0 }, enemy );
			
			// Bar ( thanks to bad-at-this )
			// duration
			write_byte ( barTime );
			
			// duration
			write_byte ( 0 );
			message_end ( );
		}
		
		new parm[2];
		parm[0] = id;
		parm[1] = enemy;
		
		set_task ( CVAR_BADAIM_TIME, "Task_Switch_BadAimOff", TASK_RESET_BADAIM_ID + enemy, parm, 2 );
		
		new cooldownparm[1];
		cooldownparm[0]=id;
		set_task( CVAR_FLASH_COOLDOWN ,"cooldown",50+id,cooldownparm,1);
	}
	else
	{
		issearching[id]=true;
		icon_controller(id);
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if (parm[1]>0 && get_user_health(id)>0)
		{
			set_task(0.1,"Task_Search_BadAim", 200+id, parm, 2);
		}
		else
		{
			issearching[id]=false;
			icon_controller(id);
		}
	}
	return PLUGIN_CONTINUE;
}

public Task_Switch_BadAimOn( id, enemy )
{
	new idname[32], ename[32];
	get_user_name( id , idname, 31);
	get_user_name( enemy , ename, 31);
	
	badaim[enemy] = true;
	new intTime = floatround(CVAR_BADAIM_TIME);
	
	if( Util_Should_Msg_Client_Alive( enemy )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage( enemy,"You have been disoreinted by %s for %d seconds!!!!", idname, intTime );
		client_print(enemy, print_chat, "%L", enemy, "ULTIMATE_BADAIM_ENEMY1", MOD, idname, intTime );
		
		if ( file_exists( "sound/uwc3x/disorient-casted.wav" ) == 1 )
		{
			emit_sound( enemy, CHAN_STATIC, "uwc3x/disorient-casted.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}
	
	if( Util_Should_Msg_Client_Alive( id )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage( id,"%s has been disoriented for %d seconds!!!", ename, intTime );
		client_print(id, print_chat, "%L", id, "ULTIMATE_BADAIM_YOU1", MOD, ename, intTime );
	}
}

public Task_Switch_BadAimOff( parm[] )
{
	new id = parm[0];
	new enemy = parm[1];
	new idname[32], ename[32];
	get_user_name( id , idname, 31);
	get_user_name( enemy , ename, 31);
	
	if( Util_Should_Msg_Client_Alive( enemy )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage(enemy,"You are no longer disoriented!");
		client_print(enemy, print_chat, "%L", enemy, "ULTIMATE_BADAIM_YOU3", MOD);
	}
	
	if( Util_Should_Msg_Client_Alive( id )  )
	{
		set_hudmessage(178, 14, 41, -1.0, 0.3, 0, 1.0, 5.0, 0.1, 0.2, 5);
		show_hudmessage(id,"%s is no longer disoriented!", ename);
		client_print(id, print_chat, "%L", id, "ULTIMATE_BADAIM_ENEMY3", MOD, ename);
	}
	
	badaim[enemy] = false;
}

//Smite
public TASK_Smite_Search( parm[] )
{
	new id = parm[0];
	new enemy, body;
	get_user_aiming(id,enemy,body);
	
	if( Util_Is_Valid_Player(enemy) && !stunned[enemy] && Util_NotSame_Team(id,enemy) && playeritem[enemy]!=IMMUNITY && !hasblink[enemy] && is_user_alive(id) && is_user_alive(enemy) && !magic_saving_throw(enemy) )
	{
		
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);
		
		//Lightning bolt and sound - #1
		Event_Smite( enemy );
		new Float:damage = float( p_level[enemy] ) * 1.5;
		new actual_damage = floatround(damage);
		
		//Add wisdom modifier
		if( p_wisdom_lightningdamagebonus[id] )
		{
			actual_damage += floatround( damage * WIS_LIGHTNINGDAMAGEBONUS );
			
			if ( CVAR_DEBUG_MODE )
			{
				client_print( id, print_console, "[%s DEBUG] Wisdom modified damage - NEW damage=( %d )", MOD, actual_damage );
			}
		}
		
		if ( CVAR_DEBUG_MODE )
		{
			client_print( id, print_console, "[%s DEBUG] Wisdom modified damage - NEW damage=( %d )", MOD, actual_damage );
		}
		
		//Damage - done only once :)
		do_damage ( enemy, id, actual_damage, 26, 3, 0, 0, 0 );
		
		//Lightning bolt and sound - #2
		Event_Smite( enemy );
		
		new cooldownparm[1];
		cooldownparm[0]=id;
		set_task( CVAR_FLASH_COOLDOWN ,"cooldown",50+id,cooldownparm,1);
	}
	else
	{
		issearching[id]=true;
		icon_controller(id);
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if (parm[1]>0 && get_user_health(id)>0)
		{
			set_task(0.1,"TASK_Smite_Search", 200+id, parm, 2);
		}
		else
		{
			issearching[id]=false;
			icon_controller(id);
		}
	}
	return PLUGIN_CONTINUE;
}

public TASK_EarthQuake_Search( parm[] )
{
	new id = parm[0];
	new enemy, body;
	get_user_aiming(id,enemy,body);
	
	if( Util_Is_Valid_Player(enemy) && !stunned[enemy] && Util_NotSame_Team(id,enemy) && playeritem[enemy]!=IMMUNITY && !hasblink[enemy] && is_user_alive(id) && is_user_alive(enemy) && !magic_saving_throw(enemy) )
	{
		issearching[id]=false;
		ultimateused[id]=true;
		icon_controller(id);
		
		new param[6], origin[3];
		get_user_origin( enemy, origin );
		param[0] = enemy;
		param[1] = 1 + p_skills[id][SKILLIDX_EARTHQUAKE];
		param[2] = id
		param[3] = 1
		
		new tMAX_RANGE = 150 * p_skills[id][SKILLIDX_EARTHQUAKE];
		create_eq_blast(origin, tMAX_RANGE);
		set_task ( 0.2, "EarthQuake_DO", TASK_RESET_BADAIM_ID + enemy, param, 4 );
		
		new cooldownparm[1];
		cooldownparm[0]=id;
		set_task( CVAR_FLASH_COOLDOWN ,"cooldown",50+id,cooldownparm,1);
	}
	else
	{
		issearching[id]=true;
		icon_controller(id);
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if (parm[1]>0 && get_user_health(id)>0)
		{
			set_task(0.1,"TASK_EarthQuake_Search", 200+id, parm, 2);
		}
		else
		{
			issearching[id]=false;
			icon_controller(id);
		}
	}
	return PLUGIN_CONTINUE;
}


public EarthQuake_DO( parm[] )
{
	new enemy = parm[0]; //original enemy
	new counterparam = parm[1]; //decremented counter
	new id = parm[2]; //original caster
	
	//Get the origin of the original enemy cast
	new origin[3];
	get_user_origin( enemy, origin );
	
	
	if( Util_Should_Msg_Client (enemy) )
	{
		message_begin( MSG_ONE, gmsgShake, { 0, 0, 0 }, enemy );
		write_short( 255<< 14 ); //ammount
		write_short( 10 << 14 ); //lasts this long
		write_short( 255<< 14 ); //frequency
		message_end( );
	}
	
	new players[32], targetorigin[3], numberofplayers, i, targetid;
	new distancebetween, damage, multiplier;
	get_players ( players, numberofplayers );
	new tMAX_RANGE = 150 * p_skills[id][SKILLIDX_EARTHQUAKE];
	new tMAX_DAMAGE = 15 * p_skills[id][SKILLIDX_EARTHQUAKE];
	
	for ( i = 0; i < numberofplayers; ++i )
	{
		targetid = players[i];
		
		if( !Util_Is_Valid_Player( targetid ) || Util_IsSame_Team( targetid, id ) || !is_user_alive ( targetid ) )
			continue;
		
		if( !parm[3] && targetid == enemy)
		{
			//make sure we only hit the original enemy once with the ultimate through the loops
			continue;
		}
		
		//Make sure we hit the person only once
		if( quaked[targetid] == 1 )
		{
			continue;
		}
		
		get_user_origin ( targetid, targetorigin );
		distancebetween = get_distance ( origin, targetorigin );
		
		if ( distancebetween < tMAX_RANGE && Util_NotSame_Team ( id, targetid ) )
		{
			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( targetid, ename, 31 );
			
			multiplier = tMAX_DAMAGE * tMAX_DAMAGE / tMAX_RANGE;
			damage = ( tMAX_RANGE - distancebetween ) * multiplier;
			damage = sqrt ( damage );
			
			//Dont let Max Damage get higher then the max allowed
			if( damage > tMAX_DAMAGE )
				damage = tMAX_DAMAGE;
			
			if ( temp_immunity[targetid] || Util_IsPlayer_Immune ( targetid, 2 ) )
			{
				//They resistted
				temp_immunity[targetid] = true;
				
				if( !quaked[targetid] )
				{
					if( Util_Should_Msg_Client_Alive( targetid ) )
					{
						client_print ( targetid, print_chat, "%L", targetid, "ULTIMATE_EARTHQUAKE_RESIST1", MOD, idname );
						client_print ( targetid, print_center, "%L", targetid, "ULTIMATE_EARTHQUAKE_RESIST2", idname );
					}
				}
				
				if( Util_Should_Msg_Client_Alive( id ) )
				{
					client_print ( id, print_chat, "%L", id, "ULTIMATE_EARTHQUAKE_RESIST3", MOD, ename );
					client_print ( id, print_center, "%L", id, "ULTIMATE_EARTHQUAKE_RESIST4", ename );
				}
				
				new iparm[2];
				
				iparm[0] = targetid;
				copy( iparm[1], 31, "Earth Quake" );
				set_task ( 1.5, "Task_Reset_Immunity", TASK_RESET_IMMUNITY+targetid, iparm, 2 );
				
				//Deal half damage becuase of the resist
				if ( is_user_alive ( targetid ) )
				{
					damage = floatround( damage  * 0.5);
					do_damage ( targetid, id, damage, 27, 3, 0, 0, 0 );
					quaked[targetid] = 1;
					
					if( targetid == enemy )
						parm[3] = 0;
				}
			}
			else
			{
				if ( is_user_alive ( targetid ) )
				{
					
					if( !quaked[targetid] )
					{
						if( Util_Should_Msg_Client_Alive( targetid ) )
						{
							client_print ( targetid, print_chat, "%L", targetid, "ULTIMATE_EARTHQUAKE_YOU1", MOD, idname );
							client_print ( targetid, print_center, "%L", targetid, "ULTIMATE_EARTHQUAKE_YOU2", idname );
						}
					}
					
					if( Util_Should_Msg_Client_Alive( id ) )
					{
						client_print ( id, print_chat, "%L", id, "ULTIMATE_EARTHQUAKE_DAMAGE1", MOD, ename );
						client_print ( id, print_center, "%L", id, "ULTIMATE_EARTHQUAKE_DAMAGE2", ename );
					}
					
					do_damage ( targetid, id, damage, 27, 3, 0, 0, 0 );
					quaked[targetid] = 1;
					
					if( targetid == enemy )
						parm[3] = 0;
				}
			}
		}
		
		if ( distancebetween < tMAX_RANGE )
		{
			if( Util_Should_Msg_Client( targetid ) )
			{
				message_begin( MSG_ONE, gmsgShake, { 0, 0, 0 }, targetid );
				write_short( 255<< 14 ); //ammount
				write_short( 10 << 14 ); //lasts this long
				write_short( 255<< 14 ); //frequency
				message_end( );
				
				message_begin( MSG_ONE, gmsgShake, { 0, 0, 0 }, targetid );
				write_short( 255<< 14 ); //ammount
				write_short( 10 << 14 ); //lasts this long
				write_short( 255<< 14 ); //frequency
				message_end( );
			}
		}
	}
	
	--counterparam;
	
	if ( counterparam > 0 )
	{
		parm[0] = enemy; //original enemy
		parm[1] = counterparam; //decremented counter
		parm[2] = id; //original caster
		
		set_task ( 0.1, "EarthQuake_DO", TASK_SUICIDE_EXPLODE_NOID, parm, 4 );
	}
	else if( counterparam == 0)
	{
		//Now that we are done, reset everyones quaked status so they can be quaked once again later
		for( i = 0; i < numberofplayers; ++i )
		{
			new quakeid = players[i];
			quaked[quakeid] = 0;
		}
	}
	
	return PLUGIN_CONTINUE;
}



/* HOOK */
public TASK_hooktask(parm[])
{
	new id = parm[0];
	
	if (CVAR_HOOK_STYLE == 0) hookstyle_classic(id);
	else if (CVAR_HOOK_STYLE == 1) hookstyle_reel(id,false);
		else if (CVAR_HOOK_STYLE == 2) hookstyle_reel(id,true);
		else if (CVAR_HOOK_STYLE == 3) hookstyle_cheapreel(id);
		
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: TASK_hooktask -> player %s - Hook style=%d", debugname, CVAR_HOOK_STYLE );
	}
	
}

public TASK_GRAB_Search( parm[2] )
{
	//These are opposite of the functions - keep that in mind
	new id = parm[0]; //Player providing the shield
	grab[id]=-1
	static target, trash
	target=0
	get_user_aiming(id,target,trash)
	
	if(target && is_valid_ent2(target) && target!=id && !Util_IsSame_Team(target,id) && Util_IsValid_Team(target ) )
	{
		issearching[id] = false;
		ultimateused[id] = true;
		icon_controller ( id );
		
		//formerly target<=maxplayers
		if( Util_Is_Valid_Player( target ) || ( get_solidity(target)!=4) )
		{
			if( !GrabResisted( target, id ) )
			{
				if ( CVAR_DEBUG_MODE )
				{
					client_print( id, print_console, "DEBUG :: TASK_GRAB_Search -> failed to resist" );
					log_amx( "[UWC3X] DEBUG :: TASK_GRAB_Search -> failed to resist" );
				}
				
				grabem(id,target);
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
	else
	{
		//Keep searching
		issearching[id] = true;
		icon_controller ( id );
		new counter = parm[1];
		
		while ( counter >= 0 )
		{
			counter -= 10;
			
			if ( counter == 0 )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					emit_sound ( id, CHAN_ITEM, "turret/tu_ping.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}
		}
		
		--parm[1];
		
		if ( parm[1] > 0 && get_user_health ( id ) >=0 )
		{
			set_task ( 0.1, "TASK_GRAB_Search", TASK_HOOK + id, parm, 3 );
		}
		else
		{
			issearching[id] = false;
			icon_controller ( id );
		}
	}
	
	return PLUGIN_CONTINUE;
}
/* AMXX-Studio Notes - DO NOT MODIFY BELOW HERE
*{\\ rtf1\\ ansi\\ deff0{\\ fonttbl{\\ f0\\ fnil Tahoma;}}\n\\ viewkind4\\ uc1\\ pard\\ lang1048\\ f0\\ fs16 \n\\ par }
*/
