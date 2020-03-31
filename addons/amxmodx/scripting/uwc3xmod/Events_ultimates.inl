/* Ultimate events */

//Lightnign bolt
public EVENT_Do_Bolt ( id, targetid, linewidth, damage, caster )
{

	lightninghit[targetid] = true;

	new parm[1];
	parm[0] = id;
	icon_controller ( id );

	do_damage ( targetid, caster, damage, 11, 3, 0, 0, 0 );

	if ( get_user_armor ( targetid )- damage <= 0 )
	{
		set_user_armor_log ( targetid, 0 );
	}
	else
	{
		set_user_armor_log ( targetid, ( get_user_armor ( targetid )-damage ) ) ;
	}

	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Do_Bolt:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( TE_BEAMENTS );

	// start entity
	write_short ( id );

	// entity
	write_short ( targetid );

	// model
	write_short ( lightning );

	// starting frame
	write_byte ( 0 );

	// frame rate
	write_byte ( 15 );

	// life
	write_byte ( 10 );

	// line width
	write_byte ( linewidth );

	// noise amplitude
	write_byte ( 10 );

	// r, g, b
	write_byte ( 255 );

	// r, g, b
	write_byte ( 255 );

	// r, g, b
	write_byte ( 10 );

	// brightness
	write_byte ( 255 );

	// scroll speed
	write_byte ( 0 );

	message_end ( );

	new origin[3];
	get_user_origin ( targetid,origin );

	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Do_Bolt:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( TE_ELIGHT );

	// entity
	write_short ( targetid );

	// initial position
	write_coord ( origin[0] );

	// initial position
	write_coord ( origin[1] );

	// initial position
	write_coord ( origin[2] );

	// radius
	write_coord ( 100 );

	// r, g, b
	write_byte ( 255 );

	// r, g, b
	write_byte ( 255 );

	// r, g, b
	write_byte ( 10 );

	// life
	write_byte ( 10 );

	// decay rate
	write_coord ( 0 );
	message_end ( );

	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists ( "sound/uwc3x/lightningbolt.wav" ) )
		{
			emit_sound ( id, CHAN_ITEM, "uwc3x/lightningbolt.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
		else
		{
			emit_sound ( id, CHAN_ITEM, "weapons/gauss2.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}

	return PLUGIN_CONTINUE;
}



//Suicide Bomber
public EVENT_Suicide_Implosion ( parm[] )
{
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: EVENT_Suicide_Implosion -> start()");
	}

	new id = parm[0];

	if ( !Util_IsValid_Team( id ) || !Util_Is_Valid_Player( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Suicide_Implosion:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( TE_IMPLOSION );
	write_coord ( parm[2] );
	write_coord ( parm[3] );
	write_coord ( parm[4] );
	write_byte ( 100 );
	write_byte ( 20 );
	write_byte ( 5 );
	message_end ( );

	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: EVENT_Suicide_Implosion -> end()");
	}
	return PLUGIN_CONTINUE;

}

//blastcircles
public EVENT_Suicide_Blast ( parm[] )
{
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: EVENT_Suicide_Blast -> start()");
	}

	new id = parm[0];

	if ( !Util_IsValid_Team( id ) || !Util_Is_Valid_Player( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	new origin[3];
	get_user_origin ( id, origin );

	// blast circles
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Suicide_Blast:: dest=%d; msg_type=%d;", MSG_PAS, SVC_TEMPENTITY);
	}
	message_begin ( MSG_PAS, SVC_TEMPENTITY, origin );
	write_byte ( TE_BEAMCYLINDER );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] - 16 );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] - 16 + CVAR_BLAST_RADIUS );
	write_short ( m_iSpriteTexture );

	// startframe
	write_byte ( 0 );

	// framerate
	write_byte ( 0 );

	// life
	write_byte ( 6 );

	 // width
	write_byte ( 16 );

	// noise
	write_byte ( 0 );
	write_byte ( 188 );
	write_byte ( 220 );
	write_byte ( 255 );

	//brightness
	write_byte ( 255 );

	// speed
	write_byte ( 0 );

	message_end ( );

	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Suicide_Blast:: dest=%d; msg_type=%d;", MSG_PAS, SVC_TEMPENTITY);
	}
	message_begin ( MSG_PAS, SVC_TEMPENTITY, origin );
	write_byte ( TE_BEAMCYLINDER );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] - 16 );
	write_coord ( origin[0] );
	write_coord ( origin[1] );
	write_coord ( origin[2] - 16 + ( CVAR_BLAST_RADIUS / 2 ) );
	write_short ( m_iSpriteTexture );
	write_byte ( 0 ); // startframe
	write_byte ( 0 ); // framerate
	write_byte ( 6 ); // life
	write_byte ( 16 ); // width
	write_byte ( 0 ); // noise
	write_byte ( 188 );
	write_byte ( 220 );
	write_byte ( 255 );
	write_byte ( 255 ); //brightness
	write_byte ( 0 ); // speed
	message_end ( );

	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: EVENT_Suicide_Blast -> end()");
	}

	return PLUGIN_CONTINUE;
}




//Flame Strike
public EVENT_Set_On_Fire ( args[] )
{

	new rx, ry, rz, forigin[3];
	new id = args[0];
	new killer = args[1];
	
	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] EVENT_Set_On_Fire :: isburning - %d", isburning[id]);
	}

	if ( !is_user_alive ( id ) || ( isburning[id] == 0 ) )
	{
		return PLUGIN_CONTINUE;
	}

	rx = random_num ( -30, 30 );
	ry = random_num ( -30, 30 );
	rz = random_num ( -30, 30 );
	get_user_origin ( id, forigin );

	//TE_SPRITE - additive sprite, plays 1 cycle
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Set_On_Fire:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( 17 );

	// coord, coord, coord ( position )
	write_coord ( forigin[0] + rx );
	write_coord ( forigin[1] + ry );
	write_coord ( forigin[2] + 10 + rz );

	 // short ( sprite index )
	write_short ( burning );

	// byte ( scale in 0.1's )
	write_byte ( 30 );

	// byte ( brightness )
	write_byte ( 200 );
	message_end ( );

	//Smoke
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::EVENT_Set_On_Fire:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin ( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte ( 5 );

	// coord, coord, coord ( position )
	write_coord ( forigin[0] + ( rx*2 ) );
	write_coord ( forigin[1] + ( ry*2 ) );
	write_coord ( forigin[2] + 100 + ( rz*2 ) );

	// short ( sprite index )
	write_short ( g_sModelIndexSmoke );

	// byte ( scale in 0.1's )
	write_byte ( 60 );

	// byte ( framerate )
	write_byte ( 15 );

	message_end ( );

	new damage = 10;

	//Increase damage by 20% if they have the wisdom for it
	if( p_wisdom_firedamagebonus[killer] )
	{
		damage += floatround( damage * WIS_FIREDAMAGEBONUS );

		if ( CVAR_DEBUG_MODE )
		{
			client_print_utility( killer, print_console, "[%s DEBUG] Wisdom modified damage - NEW damage=( %d )", MOD, damage );
			log_amx( "[UWC3X] DEBUG :: Wisdom modified damage - NEW damage=( %d )", damage );
		}
	}
	
	do_damage ( id, killer, damage, 13, 1, 0, 0, 0 );
	return PLUGIN_CONTINUE;
}

//Entangle Roots
public Event_Entangle ( parm[2] )
{
	// Entangle Roots ( DOESN'T WORK ON BOTS )
	new id = parm[0];
	new origin[3];
	new parm2[1];
	new vec[3];
	new Float:rsize[2][3] = { {-50.0, -50.0, -50.0}, {50.0, 50.0, 50.0} };
	new Float:fOrigin[3];
	new roots_ent = create_entity ( "info_target" );
	new args[1];

	get_user_origin ( id, origin );

	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists ( "sound/uwc3x/entanglingrootstarget1.wav" ) == 1 )
		{
			emit_sound ( id, CHAN_ITEM, "uwc3x/entanglingrootstarget1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
		else
		{
			emit_sound ( id, CHAN_ITEM, "weapons/electro5.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}
	}

	parm2[0] = id;
	set_task ( 20.0, "cooldown", TASK_COOLDOWN_RESET + id, parm2, 1 );

	// ****************************************************************************
	// [09-01-04] - Entangling Roots gfx redone, root model by steve french - K2mia
	get_user_origin ( id, vec );
	fOrigin[0] = float ( vec[0] );
	fOrigin[1] = float ( vec[1] );
	fOrigin[2] = float ( vec[2] ) - 35.0;

	entity_set_string ( roots_ent, EV_SZ_classname, "roots" );
	entity_set_model ( roots_ent, "models/roots2.mdl" );
	entity_set_int ( roots_ent, EV_INT_body, 3 );
	entity_set_int ( roots_ent, EV_INT_sequence, 0 );
	set_size ( roots_ent, rsize[0], rsize[1] );
	entity_set_origin ( roots_ent, fOrigin );

	args[0] = roots_ent;
	set_task ( 10.0, "Task_Destroy_Roots", 130+id, args, 1 );
	// [09-01-04] - Entangling Roots gfx redone, root model by steve french - K2mia
	// ****************************************************************************

	return PLUGIN_CONTINUE;
}

public Event_SetMaxHealth( id, sethealth )
{
	// Set player's max. health for use with mend
	if ( p_skills[id][SKILLIDX_DEVOTION] )
	{
		// Devotion Aura
		maxhealth[id] = p_devotion[p_skills[id][SKILLIDX_DEVOTION]-1];
	}
	else
	{
		maxhealth[id] = 100;
	}

	if (USE_ENH && (p_attribs[id][ATTRIBIDX_STR] > ATTRIB_BASE))
	{
		// Player has enhanced their strength attribute
		maxhealth[id] += ( STR_HEALTH_BONUS * ( p_attribs[id][ATTRIBIDX_STR] - ATTRIB_BASE ) );
	}

	if ( sethealth )
	{
		set_user_health_log( id, maxhealth[id] );
	}

	return PLUGIN_CONTINUE;
}

public Event_Smite( victim )
{
	new origin[3], srco[3];
	get_user_origin(victim,origin);

	origin[2] -= 26;
	srco[0] = origin[0]+150;
	srco[1] = origin[1]+150;
	srco[2] = origin[2]+400;

	if( Util_Should_Msg_Client( victim ) )
	{
		emit_sound(victim,CHAN_ITEM, "ambience/thunder_clap.wav", 1.0, ATTN_NORM, 0, PITCH_NORM)
	}

	Event_Smite_Lightning(srco,origin);
}

public Event_Smite_Lightning( vec1[3],vec2[3] )
{

	//Lightning
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::Event_Smite_Lightning:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin( MSG_BROADCAST,SVC_TEMPENTITY)
	write_byte( 0 )
	write_coord(vec1[0]);
	write_coord(vec1[1]);
	write_coord(vec1[2]);
	write_coord(vec2[0]);
	write_coord(vec2[1]);
	write_coord(vec2[2]);
	write_short( lightning );
	write_byte( 1 ); // framestart
	write_byte( 5 ); // framerate
	write_byte( 2 ); // life
	write_byte( 20 ); // width
	write_byte( 30 ); // noise
	write_byte( 200 ); // r, g, b
	write_byte( 200 ); // r, g, b
	write_byte( 200 ); // r, g, b
	write_byte( 200 ); // brightness
	write_byte( 200 ); // speed
	message_end();

	//Sparks
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::Event_Smite_Lightning:: dest=%d; msg_type=%d;", MSG_PVS, SVC_TEMPENTITY);
	}
	message_begin( MSG_PVS, SVC_TEMPENTITY,vec2);
	write_byte( 9 )
	write_coord( vec2[0] );
	write_coord( vec2[1] );
	write_coord( vec2[2] );
	message_end();

	//Smoke
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::Event_Smite_Lightning:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin( MSG_BROADCAST,SVC_TEMPENTITY,vec2);
	write_byte( 5 );
	write_coord(vec2[0]);
	write_coord(vec2[1]);
	write_coord(vec2[2]);
	write_short( g_sModelIndexSmoke );
	write_byte( 10 );
	write_byte( 10 );
	message_end();
}