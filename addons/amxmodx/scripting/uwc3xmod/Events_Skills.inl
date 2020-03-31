/*
	Events that are related to skills will go here
*/

//dolskin
public Do_Leather_Skin( parm[2] )
{
	new id = parm[0];
	if (!endround && is_user_alive(id) && ( p_skills[id][SKILLIDX_LSKIN] > 0 ) )
	{
		set_task( p_lskin[p_skills[id][SKILLIDX_LSKIN]-1], "Do_Leather_Skin", id + 1200, parm, 2 );
	}

	new abonusmult = 0;
	new abonus = 0;
	new atotal = 0;

	// If Steel Skin trained use improved armor bonus
	if (p_skills[id][SKILLIDX_SSKIN])
		abonusmult = ARMORBONUS2;
	else
		abonusmult = ARMORBONUS1;

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

	atotal = (NORMALARMORMAX + abonus);

	if (get_user_armor(id) < atotal)
	{
		set_user_armor_log(id, (get_user_armor(id) + 2) );

		if (get_user_armor(id) > atotal)
		{
			set_user_armor_log(id, atotal );
		}
	}

	//new origin[3];
	//get_user_origin( id, origin );
	//
	//if( playeritem[id]!=CLOAK && ( !p_skills[id][SKILLIDX_INVIS] ) )
	//{
	//	if (CVAR_DMESSAGES)
	//	{
	//		log_amx("[UWC3X]::DEBUG_MESSAGES::Do_Leather_Skin:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	//	}
	//	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	//	write_byte( TE_IMPLOSION );
	//	write_coord(origin[0]); // initial position
	//	write_coord(origin[1]); // initial position
	//	write_coord(origin[2]); // initial position
	//	write_byte(100); // radius
	//	write_byte( 8 ); // count
	//	write_byte( 1 ); // life
	//	message_end();
	//}

	return PLUGIN_CONTINUE;
}



/*Healing Wave */
//healitnow
public Heal_It_Now( parm[2] )
{
	new id = parm[0];
	if (!p_skills[id][SKILLIDX_HEALWAVE])
		return PLUGIN_HANDLED;

	if ( !endround && is_user_alive( id ) && p_skills[id][SKILLIDX_HEALWAVE] )
	{
		set_task( p_heal[p_skills[id][SKILLIDX_HEALWAVE]-1], "Heal_It_Now", id + 90, parm, 2 );
	}

	Heal_It_Now2( parm );
	return PLUGIN_CONTINUE;
}


//healingnext
public Heal_It_Now2( parm[2] )
{
	// Healing Wave
	new id = parm[0];
	if (!p_skills[id][SKILLIDX_HEALWAVE])
		return PLUGIN_HANDLED;

	new origin[3];
	get_user_origin( id, origin );

	new players[32], teamname[32], numberofplayers;
	get_user_team( id, teamname, 31 );
	get_players(players, numberofplayers);

	new i,targetorigin[3], targetid = 0, distancebetween = 0, heal = 2, closestid = 0;

	// [5-21-04] Changed from heal of 1 to heal of 2 by K2mia
	for (i = 0; i < numberofplayers; ++i)
	{
		targetid = players[i];
		if ( get_user_team( id ) == get_user_team( targetid ) && is_user_alive( targetid ) )
		{
			get_user_origin( targetid, targetorigin );
			distancebetween = get_distance( origin, targetorigin );

			if (distancebetween < CVAR_HEALING_RANGE && !healinghit[targetid] )
			{
				closestid = targetid;
			}
		}
	}

	if ( closestid )
	{
		healingeffect( id, closestid, heal );
		parm[0] = targetid;
		parm[1] = heal;
		set_task( 0.2, "Heal_It_Now2", 27, parm, 2 );
	}
	else
	{
		for (i = 0; i < numberofplayers; ++i)
		{
			targetid = players[i];
			healinghit[targetid] = false;
		}
	}

	return PLUGIN_CONTINUE;
}

public healingeffect( id, targetid, heal )
{
	/* Added by Smokey
	// [01-20-07] - Added Healing Wave XP
	// [01-22-07] - Added Healing Wave XP limits per round
	// [06-04-07] - Added Team check at the beginning
	*/

	if (!p_skills[id][SKILLIDX_HEALWAVE])
		return PLUGIN_HANDLED;

	new max_heals = 3;
	new bool:was_healed = false;
	healinghit[targetid] = true;

	//TEAM CHECK
	//If the user is not on the same team or they are not alive then return
	if ( !is_user_alive( targetid ) || !is_user_alive( id ) || ( get_user_team( id ) != get_user_team( targetid ) ) )
		return PLUGIN_HANDLED;

	new health = maxhealth[targetid] + ( playeritem[targetid] == HEALTH ? HEALTHBONUS : 0 );

	// Number of max heals based on player level
	if (p_level[id] >= 34)
		max_heals = 8;
	else if (p_level[id] > 30)
		max_heals = 7;
	else if (p_level[id] > 25)
		max_heals = 6;
	else if (p_level[id] > 20)
		max_heals = 5;
	else if (p_level[id] > 15)
		max_heals = 4;

	//only print message if in debug mode
	if( healingwaves[id] >= max_heals )
		return PLUGIN_HANDLED;
		
	if ( get_user_health( targetid ) < health )
	{
		was_healed = true;
		set_user_health_log( targetid, get_user_health( targetid ) + heal );
	}

	//Dont give them XP for healing themselves
	if( id == targetid )
		was_healed = false;

	if ( !was_healed )
		return PLUGIN_CONTINUE;

	// [09-26-04] Adjustment if maxhealth exceeded - K2mia
	if ( get_user_health( targetid ) > health )
		set_user_health_log( targetid, health );

	if ( was_healed )
	{
		//new origin[3];
		//get_user_origin( targetid, origin );
		//
		//if( playeritem[targetid] != CLOAK && ( !p_skills[targetid][SKILLIDX_INVIS] ) )
		//{
		//	if (CVAR_DMESSAGES)
		//	{
		//		log_amx("[UWC3X]::DEBUG_MESSAGES::healingeffect:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		//	}
		//	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
		//	write_byte( TE_IMPLOSION );
		//
		//	// initial position
		//	write_coord(origin[0]);
		//
		//	// initial position
		//	write_coord(origin[1]);
		//
		//	// initial position
		//	write_coord(origin[2]);
		//
		//	 // radius
		//	write_byte(100);
		//	// count
		//	write_byte( 8 );
		//	// life
		//	write_byte( 1 );
		//	message_end();
		//}

		healingwaves[id] += 1;

		//If healing wave XP is enabled
		if ( CVAR_HEALING_WAVE_XP )
		{
			new xpbonus = HEALWAVEXP + xpgiven_lev[p_level[id]];
			if ( CVAR_SAVE_XP )
				xpbonus += ( HEALWAVEXP * p_level[id] );

			// AWARD THE PLAYER THEIR XP
			playerxp[id] += xpbonus;

			/// LET THE PLAYER KNOW THAT WE GAVE THEM XP AND HOW MUCH
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility( id, print_console, "%L", id, "HEALING_WAVE_HEAL", MOD, xpbonus );
			}
		}
	}

	return PLUGIN_CONTINUE;
}

/* HEXED - JUMPING */
public jumper( parm[2] )
{
	new id = parm[0];
	client_cmd( id, "+jump;wait;-jump" );
	parm[1]++;

	if( !endround && is_user_alive( id ) )
	{
		set_task( 3.0, "jumper", 2000 + id, parm, 1 );
	}

	return PLUGIN_CONTINUE;
}

public walker( parm[2] )
{
	new id = parm[0];

	// Other function calls to do every .1 seconds
	client_cmd( id, "cl_minmodels 0" );

	if( CVAR_CENTER_HUD )
		client_cmd( id, "hud_centerid 0" );

	// End Other function calls
	if ( !endround )
	{
		set_task( 0.1, "walker", 600 + id, parm, 2 );
	}

	return PLUGIN_CONTINUE;
}

/* Regeneration */
public regenerate( parm[] )
{
	// [08-10-04] - Subroutine completely rewritten - K2mia
	new id = parm[0];

	if( playeritem2[id] != REGEN )
	{
		return PLUGIN_HANDLED;
	}

	new bonus = rings[id];

	set_hudmessage( 0, 100, 0, 0.05, 0.65, 2, 0.02, 10.0, 0.01, 0.1, 2 );
	set_task( 2.0, "regenerate", TASK_REGENERATE + id, parm, 2 );

	if( get_user_health( id ) > 1500 )
	{
		return PLUGIN_HANDLED;
	}

	new health = maxhealth[id] + ( playeritem[id] == HEALTH ? HEALTHBONUS : 0 );

	if ( get_user_health( id ) < health )
	{
		set_user_health_log( id, get_user_health( id ) + bonus );
	}

	return PLUGIN_CONTINUE;

}


/* Napalm Grenade burn */
public on_fire_napalm( args[] )
{
	new rx, ry, rz, forigin[3];
	new id = args[0];

	new killer = args[1];

	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] on_fire_napalm :: isnburning - %d", isnburning[id]);
	}
	
	//client_print_utility( 0, print_console,
	// "In on_fire_napalm( ) id=( %d ) killer=( %d ) isnburning=( %d )", id, killer, isnburning[id] )

	if( !is_user_alive( id ) || ( isnburning[id] == 0 ) )
		return PLUGIN_CONTINUE;

	rx = random_num( -30, 30 );
	ry = random_num( -30, 30 );
	rz = random_num( -30, 30 );
	get_user_origin( id, forigin );

	if( Util_Should_Msg_Client(id) )
	{
		emit_sound( id, CHAN_ITEM, "ambience/flameburst1.wav", 0.6, ATTN_NORM, 0, PITCH_NORM );
	}

	// [09-05-04] Attach fireball sprite to player for 1 cycle
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::on_fire_napalm:: dest=%d; msg_type=%d;", MSG_ALL, SVC_TEMPENTITY);
	}
	message_begin( MSG_ALL, SVC_TEMPENTITY );
	write_byte( TE_PLAYERATTACHMENT );
	write_byte( id );
	write_coord( 0 ); // z axis for sprite
	write_short( blast ); // blast sprite
	write_short( 9 );
	message_end( );

	//TE_SPRITE - additive sprite, plays 1 cycle
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::on_fire_napalm:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte( 17 );
	write_coord( forigin[0]+rx ); // coord, coord, coord ( position )
	write_coord( forigin[1]+ry );
	write_coord( forigin[2]+10+rz );
	write_short( burning ); // short ( sprite index )
	write_byte( 30 ); // byte ( scale in 0.1's )
	write_byte( 200 ); // byte ( brightness )
	message_end( );

	//Smoke
	if (CVAR_DMESSAGES)
	{
		log_amx("[UWC3X]::DEBUG_MESSAGES::on_fire_napalm:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
	}
	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte( 5 );
	write_coord( forigin[0]+( rx * 2 ) ); // coord, coord, coord ( position )
	write_coord( forigin[1]+( ry * 2 ) );
	write_coord( forigin[2]+100+( rz * 2 ) );
	write_short( g_sModelIndexSmoke );// short ( sprite index )
	write_byte( 60 ); // byte ( scale in 0.1's )
	write_byte( 15 ); // byte ( framerate )
	message_end( );

	if( is_user_alive( id ) == 0 )
		return PLUGIN_CONTINUE;

	do_damage( id, killer, 5, 17, 2, 0, 0, 0 );

	return PLUGIN_CONTINUE;
}


/* Cluster Grenades */
public grenade_throw()
{
	if ( get_msg_args() < 2 )
		return PLUGIN_HANDLED_MAIN;

	if ( get_msg_arg_int( 1 ) == 12 && get_msg_arg_int( 2 ) == 0 )
		add_grenade_owner( last );

	return PLUGIN_CONTINUE;
}

public fire_in_the_hole( id, dest, ent )
{
	if ( get_msg_args() != 5 )
		return PLUGIN_CONTINUE;

	new temp[17];
	get_msg_arg_string( 5, temp, 17 );

	if ( equali( temp, "#Fire_in_the_hole" ) )
	{
		new name[32];
		entity_get_string( ent, EV_SZ_netname, name, 32 );
		last = find_player( "a", name );
	}

	return PLUGIN_CONTINUE;
}

public pfn_touch( ptr, ptd )
{

	//Gets the indentifying strings of each entity
	new identify[15], compare[15], Float:origin[3];

	if ( ptr == 0 )
		identify = "world";
	else
		entity_get_string( ptr, EV_SZ_classname, identify, 15 );

	if ( ptd == 0 )
		compare = "world"
	else if ( is_valid_ent( ptd ) )
		entity_get_string( ptd, EV_SZ_classname, compare, 15 );

	//Ensures that the grenade cluster argument is always the 'ptr'
	if ( ptr == 0 || equali( compare, "grenade_cluster" ) )
		return PLUGIN_HANDLED;

	if (ptd == 0)
		return PLUGIN_CONTINUE
		
	new szClassName[32]
	entity_get_string(ptd, EV_SZ_classname, szClassName, 31)
	
	if (ptr != 0)
	{
		new szClassNameOther[32]
		entity_get_string(ptr, EV_SZ_classname, szClassNameOther, 31)
		if(equal(szClassName, "Mine") && equal(szClassNameOther, "player"))
		{
			new owner = pev(ptd,pev_owner)
			//Touch
			if (get_user_team(owner) != get_user_team(ptr))
			{
				new Float:origin[3]
				pev(ptd,pev_origin,origin)
				Explode_Origin(owner,origin,55,150)
				remove_entity(ptd)
			}
		}
	}	

	//Checks to see if it is a grenade cluster hitting another object. If it is it explodes and deals damage
	if ( equali( identify, "grenade_cluster" ) )
	{
		entity_get_vector( ptr, EV_VEC_origin, origin );

		//Deals radius damage to the spot of collision
		new player[32], players, location[3], origin2[3], distance, Float:multiplier, owner;
		origin2[0] = floatround( origin[0] );
		origin2[1] = floatround( origin[1] );
		origin2[2] = floatround( origin[2] );

		//Get the owner
		owner = entity_get_edict( ptr, EV_ENT_owner );

		//if the owner is invalid or the owner doesnt have the skill, then leave the function
		if( !Util_Is_Valid_Player( owner ) || !p_skills[owner][SKILLIDX_CLUSTERNADE] )
		{
			return PLUGIN_CONTINUE;
		}

		get_players( player, players, "a" );

		for ( new i = 0; i < players; i++ )
		{
			get_user_origin( player[i], location );
			distance = get_distance( origin2, location );

			if ( distance < CLUSTER_DAMAGE_RADIUS )
			{
				multiplier = floatdiv( float( CLUSTER_DAMAGE_RADIUS - distance ), float( CLUSTER_DAMAGE_RADIUS ) );
				new damage = floatround( floatmul( multiplier, float( MAX_CLUSTER_DAMAGE ) ) );
				do_damage ( player[i], owner, damage, 28, 2, 0, 0, 0 );
			}
		}

		//Paints the explosion
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::pfn_touch:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
		write_byte( TE_EXPLOSION );
		write_coord( floatround( origin[0] ) );
		write_coord( floatround( origin[1] ) );
		write_coord( floatround( origin[2] ) );
		write_short( g_sModelIndexFireball );
		write_byte( 50 );
		write_byte( 15 );
		write_byte( 0 );
		message_end();

		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::pfn_touch:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
		write_byte( TE_EXPLOSION );
		write_coord( floatround( origin[0] ) );
		write_coord( floatround( origin[1] ) );
		write_coord( floatround( origin[2] ) );
		write_short( fire );
		write_byte( 50 );
		write_byte( 15 );
		write_byte( 0 );
		message_end();

		//If the grenade hit the ground or a wall then this draws a land scar
		if ( ptd == 0 )
		{
			if (CVAR_DMESSAGES)
			{
				log_amx("[UWC3X]::DEBUG_MESSAGES::pfn_touch:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
			}
			message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
			write_byte( TE_WORLDDECAL );
			write_coord( floatround( origin[0] ) );
			write_coord( floatround( origin[1] ) );
			write_coord( floatround( origin[2] ) );
			write_byte( SCORCH );
			message_end();
		}

		remove_entity( ptr ); //Removes the grenade cluster so that it does not enter an infinite loop

		return PLUGIN_HANDLED;
	}

	return PLUGIN_CONTINUE;
}

public grenade_explosion()
{
	if (get_msg_arg_int( 1 ) == 3 && get_msg_arg_int ( 6 ) == 25 && get_msg_arg_int ( 7 ) == 30 )
	{
		new cluster, Float:vAngle[3], Float:angles[3], Float:velocity[3], Float:origin[3], pos[3];
		new Rvelocity[3], Float:distance, Float:actualDistance, Float:multiplier;

		pos[0] = floatround( get_msg_arg_float( 2 ) );
		pos[1] = floatround( get_msg_arg_float( 3 ) );
		pos[2] = floatround( get_msg_arg_float( 4 ) );

		origin[0] = float( pos[0] );
		origin[1] = float( pos[1] );
		origin[2] = float( pos[2] );

		new Float:minBox[3] = { -1.0, ... };
		new Float:maxBox[3] = { 1.0, ... };

		/* Get the owner of the Grenade */
		new owner = get_grenade_owner();

		if( !Util_Is_Valid_Player( owner ) )
		{
			return PLUGIN_CONTINUE;
		}

		/*and then look up their skill points in cluster grenade */
		new CLUSTERS = p_skills[owner][SKILLIDX_CLUSTERNADE];

		if( CLUSTERS == 0 )
		{
			return PLUGIN_CONTINUE;
		}

		if ( CVAR_DEBUG_MODE )
		{
			new idname[32];
			get_user_name( owner , idname, 31 );
			client_print_utility( 0, print_console, "DEBUG :: grenade_explosion -> Player=%s CLUSTERS = %d ", idname, CLUSTERS );
			log_amx( "DEBUG :: grenade_explosion -> Player=%s CLUSTERS = %d ", idname, CLUSTERS );
		}

		//This will launch the above specified number of clusters
		for (new i = 0; i < CLUSTERS; i++)
		{
			//Create a random direction for the cluster to fly
			velocity[0] = random_float( float( MIN_FLY_DISTANCE ), float( MAX_FLY_DISTANCE ) );

			if ( random_num( 0, 1 ) == 1 )
				velocity[0] = floatmul( velocity[0], -1.0 );

			velocity[1] = random_float( float( MIN_FLY_DISTANCE ), float( MAX_FLY_DISTANCE ) );

			if ( random_num( 0, 1 ) == 1 )
				velocity[1] = floatmul( velocity[1], -1.0 );

			velocity[2] = float( UPWARD_ARC );

			Rvelocity[0] = pos[0] + floatround( velocity[0] );
			Rvelocity[1] = pos[1] + floatround( velocity[1] );
			Rvelocity[2] = pos[2] + floatround( velocity[2] );

			//Create the distance the cluster will fly
			distance = random_float( float( MIN_FLY_DISTANCE ), float( MAX_FLY_DISTANCE ) );
			actualDistance = float( get_distance( pos, Rvelocity ) );
			multiplier = floatdiv( distance, actualDistance );

			velocity[0] = floatmul( velocity[0], multiplier );
			velocity[1] = floatmul( velocity[1], multiplier );
			velocity[2] = floatmul( velocity[2], multiplier );

			//Create the angles for the facing of the cluster.
			//PS: I have no idea how to do the angle thing really. This is a blind attempt.
			vector_to_angle( velocity, angles );
			vector_to_angle( velocity, vAngle );

			//Create the entity of the cluster
			cluster = create_entity( "info_target" );

			//Set the identifying string of the cluster's entity
			entity_set_string( cluster, EV_SZ_classname, "grenade_cluster");

			//Set the model for the cluster's entity
			entity_set_model( cluster, "models/grenade.mdl" );

			//Set the bounds for the cluster's entity
			entity_set_vector( cluster, EV_VEC_mins, minBox);
			entity_set_vector( cluster, EV_VEC_maxs, maxBox);

			//Set the origin for the cluster's entity (NOTE: The clusters will spawn in the same spot, but they will be set to ignore eachother
			entity_set_origin( cluster, origin );

			//Set the angles of the cluster's entity
			entity_set_vector( cluster, EV_VEC_angles, angles );
			entity_set_vector( cluster, EV_VEC_v_angle, vAngle );

			//Set the behavior specific variables for the cluster's entity
			entity_set_int( cluster, EV_INT_movetype, 6 ); //Has gravity and registers collisions
			entity_set_int( cluster, EV_INT_solid, 1 ); //Collisions do not block

			//Record who the owner of this nade is
			entity_set_edict( cluster, EV_ENT_owner, get_grenade_owner() );

			//Make the cluster fly!
			entity_set_vector( cluster, EV_VEC_velocity, velocity ) ;
		}
	}
	return PLUGIN_CONTINUE;
}


// apply the effects of being chilled
public chill_player(id)
{
	// don't mess with their speed if they are frozen
	if(isFrozen[id])
		set_user_maxspeed(id,1.0); // 0.0 doesn't work
	else
	{
		new speed = floatround(get_user_maxspeed(id) * ( FROST_CHILL_SPEED / 100.0));
		set_user_maxspeed(id,float(speed));
	}

	if( Util_Should_Msg_Client( id ) )
	{
		// add a blue tint to their screen
		new sf = get_user_msgid("ScreenFade");
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::chill_player:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, sf, id);
		}
		message_begin(MSG_ONE,sf,{0,0,0},id);
		write_short(~0); // duration
		write_short(~0); // hold time
		write_short(0x0004); // flags: FFADE_STAYOUT, ignores the duration, stays faded out until new ScreenFade message received
		write_byte(FROST_R); // red
		write_byte(FROST_G); // green
		write_byte(FROST_B); // blue
		write_byte(100); // alpha
		message_end();
	}

	// make them glow and have a trail
	set_user_rendering(id,kRenderFxGlowShell,FROST_R,FROST_G,FROST_B,kRenderNormal,1);

	// bug fix
	if(!isFrozen[id])
		set_beamfollow(id,30,8,FROST_R,FROST_G,FROST_B,100);
}

// apply the effects of being frozen
public freeze_player(id)
{
	new Float:speed = get_user_maxspeed(id);

	// remember their old speed for when they get unfrozen,
	// but don't accidentally save their frozen speed
	if(speed > 1.0 && speed != oldSpeed[id])
	{
		// save their unchilled speed
		if(isChilled[id])
		{
			new speed = floatround(get_user_maxspeed(id) / (FROST_CHILL_SPEED / 100.0));
			oldSpeed[id] = float(speed);
		}
		else
			oldSpeed[id] = speed;
	}

	// stop them from moving
	set_user_maxspeed(id,1.0); // 0.0 doesn't work
	entity_set_vector(id,EV_VEC_velocity,Float:{0.0,0.0,0.0});
	entity_set_float(id,EV_FL_gravity,0.000001); // 0.0 doesn't work
}

// a player's chill runs out
public remove_chill(taskid)
{
	remove_task(taskid);
	new id = taskid - TASK_REMOVE_CHILL;

	// no longer chilled
	if(!isChilled[id])
		return;

	isChilled[id] = 0;

	// only apply effects to this player if they are still connected
	if(Util_Should_Msg_Client(id))
	{
		// clear screen fade
		new sf = get_user_msgid("ScreenFade");
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::remove_chill:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, sf, id);
		}
		message_begin(MSG_ONE,sf,{0,0,0},id);
		write_short(0); // duration
		write_short(0); // hold time
		write_short(0); // flags
		write_byte(0); // red
		write_byte(0); // green
		write_byte(0); // blue
		write_byte(0); // alpha
		message_end();

		// kill their trail
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::remove_chill:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(TE_KILLBEAM);
		write_short(id);
		message_end();
	}

	// restore speed and remove glow
	new speed = floatround(get_user_maxspeed(id) / (FROST_CHILL_SPEED / 100.0));
	set_user_maxspeed(id,float(speed));
	set_user_rendering(id);

}

// a player's freeze runs out
public remove_freeze(taskid)
{
	remove_task(taskid);
	new id = taskid - TASK_REMOVE_FREEZE;

	// no longer frozen
	if(!isFrozen[id])
		return;

	// if nothing happened to the model
	if(is_valid_ent(novaDisplay[id]))
	{
		// get origin of their frost nova
		new origin[3], Float:originF[3];
		entity_get_vector(novaDisplay[id],EV_VEC_origin,originF);
		FVecIVec(originF,origin);

		// add some tracers
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::remove_freeze:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(14); // TE_IMPLOSION
		write_coord(origin[0]); // x
		write_coord(origin[1]); // y
		write_coord(origin[2] + 8); // z
		write_byte(64); // radius
		write_byte(10); // count
		write_byte(3); // duration
		message_end();

		// add some sparks
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::remove_freeze:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(9); // TE_SPARKS
		write_coord(origin[0]); // x
		write_coord(origin[1]); // y
		write_coord(origin[2]); // z
		message_end();

		// add the shatter
		if (CVAR_DMESSAGES)
		{
			log_amx("[UWC3X]::DEBUG_MESSAGES::remove_freeze:: dest=%d; msg_type=%d;", MSG_BROADCAST, SVC_TEMPENTITY);
		}
		message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
		write_byte(108); // TE_BREAKMODEL
		write_coord(origin[0]); // x
		write_coord(origin[1]); // y
		write_coord(origin[2] + 24); // z
		write_coord(16); // size x
		write_coord(16); // size y
		write_coord(16); // size z
		write_coord(random_num(-50,50)); // velocity x
		write_coord(random_num(-50,50)); // velocity y
		write_coord(25); // velocity z
		write_byte(10); // random velocity
		write_short(glassGibs); // model
		write_byte(10); // count
		write_byte(25); // life
		write_byte(0x01); // flags: BREAK_GLASS
		message_end();

		// play a sound and remove the model
		emit_sound(novaDisplay[id],CHAN_BODY,"uwc3x/impalelaunch1.wav",1.0,ATTN_NORM,0,PITCH_LOW);
		remove_entity(novaDisplay[id]);
	}

	isFrozen[id] = 0;
	novaDisplay[id] = 0;

	// only apply effects to this player if they are still connected
	if(is_user_connected(id))
	{
		// restore gravity
		entity_set_float(id,EV_FL_gravity,1.0);

		// if they are still chilled, set the speed rightly so. otherwise, restore it to complete regular.
		if(isChilled[id])
		{
			set_beamfollow(id,30,8,FROST_R,FROST_G,FROST_B,100); // bug fix

			new speed = floatround(oldSpeed[id] * ( FROST_CHILL_SPEED / 100.0));
			set_user_maxspeed(id,float(speed));
		}
		else
			set_user_maxspeed(id,oldSpeed[id]);
	}

	oldSpeed[id] = 0.0;
}