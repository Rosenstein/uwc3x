//								Damage Events

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

public get_deathbystr( deathby, string[], len )
{

	switch ( deathby )
	{
		case 1:
			format( string, len, "%s", "UWC3X Carrion Beetles" ); // Carrion Beetles
		case 2:
			format( string, len, "%s", "UWC3X Thorns Aura" ); // Thorns Aura
		case 3:
			format( string, len, "%s", "UWC3X Trueshot Aura" ); // Trueshot Aura
		case 4:
			format( string, len, "%s", "UWC3X Spiked Carapace" ); // Spiked Carapace
		case 5:
			format( string, len, "%s", "UWC3X Banish" ); // Banish
		case 6:
			format( string, len, "%s", "UWC3X Critical Strike" ); // Critical Strike
		case 7:
			format( string, len, "%s", "UWC3X Critical Grenade" ); // Critical Grenade
		case 8:
			format( string, len, "%s", "UWC3X Claws of Attack" ); // Claws of Attack
		case 9:
			format( string, len, "%s", "UWC3X Shadow Strike" ); // Shadow Strike
		case 10:
			format( string, len, "%s", "UWC3X Blink" ); // Blink > Big Bad Voodoo
		case 11:
			format( string, len, "%s", "UWC3X Chain Lightning" ); // Chain Lightning Kill
		case 12:
			format( string, len, "%s", "UWC3X Suicide Bomber" ); // Suicide Bomber Kill
		case 13:
			format( string, len, "%s", "UWC3X Flame Strike" ); // Flame Strike Kill
		case 14:
			format( string, len, "%s", "UWC3X Serpant Ward" ); // Serpant Ward Kill
		case 15:
			format( string, len, "%s", "UWC3X Locust Swarm" ); // Locust Kill
		case 16:
			format( string, len, "%s", "UWC3X Necklace of Immunity" );// Necklace of Immunity
		case 17:
			format( string, len, "%s", "UWC3X Napalm Grenade" ); // Napalm Grenade
		case 18:
			format( string, len, "%s", "UWC3X Poison" ); // S. Strike Poison
		case 19:
			format( string, len, "%s", "UWC3X Disease" ); // C. Beetles Disease
		case 20:
			format( string, len, "%s", "UWC3X Beginner's Luck" ); // Beginner's Luck
		case 21:
			format( string, len, "%s", "UWC3X Critical Backfire" ); // Critical Backfire
		case 22:
			format( string, len, "%s", "UWC3X Magic Resistance" ); // Magic Resistance
		case 23:
			format( string, len, "%s", "UWC3X Jumpkick" ); // Jump Kick
		case 24:
			format( string, len, "%s", "UWC3X TeamShield" ); // Team Shield
		case 25:
			format( string, len, "%s", "UWC3X Rot" ); // Rot
		case 26:
			format( string, len, "%s", "UWC3X Smite" ); // Smite - Lightning based attack
		case 27:
			format( string, len, "%s", "UWC3X Earthquake" ); // Earthqauke - elemental based attack
		case 28:
			format( string, len, "%s", "UWC3X Cluster Bombs" ); // Cluster Bomb
		case 29:
			format( string, len, "%s", "UWC3X Ice Bomb" ); // Ice Bomb
		case 30:
			format( string, len, "%s", "UWC3X Fatal Strike" ); //Fatal Strike
		case 31:
			format( string, len, "%s", "UWC3X Claymore Mine" ); //Claymore
	}
}

public do_damage ( id, enemy, damage, deathby, victim_or_enemy, weapon, bodypart, userdead )
{
	// id is attacked, attacker , damage , victim = 1, enemy = 2

	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new idname[32], ename[32];
	get_user_name( id, idname, 31 );
	get_user_name( enemy, ename, 31 );

	if ( CVAR_XP_BONUS_FOR_DAMAGE )
	{
		damageto[enemy][id] += damage;
	}

	new userkilled = 0, string[48];
	// Get the string form of deathby
	get_deathbystr( deathby, string, 47 );

	if( userdead || !is_user_alive( id ) )
	{
		remove_effects(id);
		return PLUGIN_HANDLED;
	}

	if ( hasblink[id] && ( weapon == 10 || weapon == 11 || weapon == 12 || weapon == 13 || weapon == 15 ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( hasgodmode[id] && !hasblink[enemy] && playeritem[enemy] != IMMUNITY && !Util_IsPlayer_Immune ( enemy, 2 ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( get_user_health( id ) - damage<=0 )
	{
		userkilled = 1;
	}

	if ( get_user_health( id ) - damage<=1024 && get_user_health( id )>500 )
	{
		userkilled = 1;
	}

	if ( userkilled )
	{
		set_user_health_log( id, -1 );
	}
	else
	{
		set_user_health_log( id, get_user_health( id ) - damage );
	}

	if ( userkilled && is_user_connected( enemy ) && Util_NotSame_Team ( id, enemy ) )
	{
		cs_set_user_money( enemy, cs_get_user_money( enemy ) + MONEY_PER_KILL );
	}

	if ( userkilled )
	{
		diedlastround[id] = true;
	}

	if ( userkilled && id != enemy )
	{
		get_deathbystr( deathby, string, 47 );
	}

	new name[32], e_name[32];
	get_user_name( id, name, 31 );
	get_user_name( enemy, e_name, 31 );

	xpgiven = xpgiven_lev[p_level[enemy]];

	if ( userkilled && ( ( victim_or_enemy == 2 ) || ( victim_or_enemy == 3 ) ) && ( id != enemy ) && ( userdead == 0 ) )
	{
		// A skill resulted in a player's death
		if ( !is_user_connected( id ) || !is_user_connected( enemy ) )
			return PLUGIN_CONTINUE;

		set_user_frags( enemy, get_user_frags( enemy )+1 );
		set_user_frags( id, get_user_frags( id )+1 );

		//logKill( enemy, id, string )
		if ( Util_NotSame_Team ( id, enemy ) )
		{
			playerxp[enemy] += xpgiven;

			if ( CVAR_KILL_OBJECTIVES )
			{
				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "OBJECTIVES_XP", MOD, xpgiven, name, string );
				}

			}

			new e_steamid[32], i_steamid[32], e_team[16], i_team[16] ;
			get_user_authid( enemy, e_steamid, 31 );
			get_user_authid( id, i_steamid, 31 );

			if ( cs_get_user_team( id ) == CS_TEAM_T )
			{
				format( i_team, 15, "TERRORIST" );
			}
			else if ( cs_get_user_team( id ) == CS_TEAM_CT )
			{
				format( i_team, 15, "CT" );
			}
			else
			{
				format( i_team, 15, "SPECTATOR" );
			}

			if ( cs_get_user_team( enemy ) == CS_TEAM_T )
			{
				format( e_team, 15, "TERRORIST" );
			}
			else if ( cs_get_user_team( enemy ) == CS_TEAM_CT )
			{
				format( e_team, 15, "CT" );
			}
			else
			{
				format( e_team, 15, "SPECTATOR" );
			}

			log_message( "^"%s<%d><%s><%s>^" killed ^"%s<%d><%s><%s>^" with ^"%s^"", e_name, get_user_userid( enemy ), e_steamid, e_team, name, get_user_userid( id ), i_steamid, i_team, string );
			displaylevel( id, 1 );
		}
		
		if( !deathmessageshown[id] )
		{
			deathmessageshown[id] = true;
			message_begin( MSG_ALL, gmsgDeathMsg, { 0, 0, 0 }, 0 );
			write_byte( enemy );
			write_byte( id );
			write_byte( 0 );
			write_string( string );
			message_end( );
		}

		return PLUGIN_HANDLED;

	}

	//moved outside the next function
	// due to all aggressive auras
	new headshot;

	if ( bodypart == 1 )
	{
		headshot=1;
	}
	else
	{
		headshot=0;
	}

	if ( userkilled && ( victim_or_enemy == 1 ) && ( id != enemy ) && ( userdead == 0 ) )
	{

		new weaponname[32];
		weaponname = GetWeaponName( weapon );

		//logKill( enemy, id, weaponname )
		if ( is_user_connected( id ) )
			set_user_frags( id, get_user_frags( id )+1 );

		if ( is_user_connected( enemy ) )
			set_user_frags( enemy, get_user_frags( enemy )+1 );

		if ( !CVAR_WEAPON_MULTIPLIER && Util_NotSame_Team ( id, enemy ) )
		{
			playerxp[enemy] += xpgiven;
			if ( CVAR_KILL_OBJECTIVES )
			{
				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_console, "%L", enemy, "OBJECTIVES_XP", MOD, xpgiven, name, string );
				}
				
				if( headshot == 1 )
				{
					playerxp[enemy] += HEADSHOT_BONUS;
					if( Util_Should_Msg_Client(enemy) )
					{
						client_print( enemy, print_console, "%L", enemy, "OBJECTIVES_XP_HS", MOD, HEADSHOT_BONUS, name, string );
					}
				}
				
			}
		}
		else if( Util_NotSame_Team ( id, enemy ) )
		{
			playerxp[enemy] += floatround( xpgiven * weaponxpmultiplier[weapon] );
			if ( CVAR_KILL_OBJECTIVES )
			{
				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_console, "%L", enemy, "OBJECTIVES_XP",MOD, floatround( xpgiven * weaponxpmultiplier[weapon] ), name, string );
				}
				
				if( headshot == 1 )
				{
					playerxp[enemy] += HEADSHOT_BONUS;
					if( Util_Should_Msg_Client(enemy) )
					{
						client_print( enemy, print_console, "%L", enemy, "OBJECTIVES_XP_HS", MOD, HEADSHOT_BONUS, name, string );
					}
				}
				
			}
		}
		else if( Util_IsSame_Team ( id, enemy ) )
		{
			if( CVAR_PUNISH_TK_KILLS )
			{
				//player TK'ed, remove XP
				playerxp[enemy] -= floatround( xpgiven * weaponxpmultiplier[weapon] );

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_console, "%L", enemy, "TK_XP", MOD, floatround( xpgiven * weaponxpmultiplier[weapon] ), name, string );
				}
			}
		}

		if( !deathmessageshown[id] )
		{
			deathmessageshown[id] = true;
			message_begin( MSG_ALL, gmsgDeathMsg, { 0, 0, 0 }, 0 );
			write_byte( enemy );
			write_byte( id );
			write_byte( headshot );
			write_string( weaponname );
			message_end( );
			displaylevel( enemy, 1 );
		}
	}

	return PLUGIN_CONTINUE;
}

public damage_event( id )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new weapon = 0, bodypart = 0, damage, name1[32], name2[32], enemy;

	enemy = get_user_attacker( id, weapon, bodypart );
	damage = read_data( 2 );
	get_user_name( id, name1, 31 );
	get_user_name( enemy, name2, 31 );

	if( p_spawnprotection[id] == 1 )
	{

		if( Util_Should_Msg_Client(enemy) )
		{
			//client_print( enemy, print_chat, "%L", enemy, "IMPALE3", MOD, name1 );

			//impale
			if ( file_exists( "sound/uwc3x/impalehit.wav" ) == 1 )
			{
				emit_sound( enemy, CHAN_ITEM, "uwc3x/impalehit.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}
		}

		if( Util_Should_Msg_Client( enemy ) )
		{
			message_begin( MSG_ONE, gmsgShake, { 0, 0, 0 }, enemy );
			write_short( 255<< 14 ); //ammount
			write_short( 10 << 14 ); //lasts this long
			write_short( 255<< 14 ); //frequency
			message_end( );
		}

		return PLUGIN_HANDLED;
	}

	if ( CVAR_MEDIC_ALERTS == 1 && !medicalert[id] )
	{
		// Send out medic alert calls to all medics on the team
		medicalert[id] = true;

		new pid, players[32], pnum=0;
		get_players( players, pnum );

		for ( new i = 0; i < pnum; i++ )
		{
			pid = players[i];

			if ( is_user_alive( id ) && !is_user_bot( pid ) && is_user_alive( pid ) && is_user_connected( id ) && is_user_connected( pid ) && ( Util_IsSame_Team ( id, pid ) ) )
			{
				if ( ( p_skills[pid][SKILLIDX_MEND] == 3 ) && ( isburning[id] || isnburning[id] ) )
				{
					client_print( pid, print_chat, "%L", pid, "MEDIC1", MOD, name1 );
				}
				else if ( ( p_skills[pid][SKILLIDX_MEND] == 3 ) && bIsRotting[id] )
				{
					client_print( pid, print_chat, "%L", pid, "MEDIC2", MOD, name1 );
				}
				else if ( ( p_skills[pid][SKILLIDX_MEND] == 2 ) && ispoisonedss[id] )
				{
					client_print( pid, print_chat, "%L", pid, "MEDIC3", MOD, name1 );
				}
				else if ( ( p_skills[pid][SKILLIDX_MEND] == 2 ) && isdiseasedcb[id] )
				{
					client_print( pid, print_chat, "%L", pid, "MEDIC4", MOD, name1 );
				}
				else if ( p_skills[pid][SKILLIDX_MEND] )
				{
					client_print( pid, print_chat, "%L", pid, "MEDIC5", MOD, name1 );
				}
			}
		}
	}

	//put in this check to solve array problem
	/*
	[AMXX] Displaying debug trace (plugin "uwc3x.amxx")
	[AMXX] Run time error 4: index out of bounds
	[AMXX]  [0] Events_damage.inl::damage_event (line 382)
	*/

	if ( enemy == id || !enemy || enemy == 0 || weapon == 0 )
		return PLUGIN_HANDLED;

	if ( CVAR_XP_BONUS_FOR_DAMAGE )
	{
		if( is_user_connected(enemy) && is_user_connected(id) )
		{
			damageto[enemy][id] += damage;
		}
	}

	//if( !is_user_bot(enemy) || ismole[enemy] )
	//{
	//	if ( playeritem2[id] == PROTECTANT || hasblink[id] )
	//	{
	//		// Mole Protectant
	//		damage = read_data( 2 );
	//		set_user_health_log( id, get_user_health( id ) + damage );
	//		client_print( id, print_chat, "%L", id, "MOLE_DEFLECT", MOD );
	//		return PLUGIN_HANDLED;
	//	}
	//}

	if( ismole[enemy] )
	{
		if ( playeritem2[id] == PROTECTANT || hasblink[id] )
		{
			// Mole Protectant
			damage = read_data( 2 );
			set_user_health_log( id, get_user_health( id ) + damage );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "MOLE_DEFLECT", MOD );
			}

			return PLUGIN_HANDLED;
		}
	}

	if( hasgodmode[id] )
	{
		// Godmode handler, check for necklace which will counter w/ extra dmg
		damage = read_data( 2 );

		if( hasblink[enemy] || playeritem[enemy] == IMMUNITY )
		{
			godshealth[id] = godshealth[id] - damage;

			if( godshealth[id] < 0 )
			{
				do_damage( id, enemy, godshealth[id]+2048, 16, 1, weapon, bodypart, 0 );
			}
		}
		else if ( Util_IsPlayer_Immune ( enemy, 2 ) )
		{
			godshealth[id] = godshealth[id] - damage;

			if( godshealth[id] < 0 )
			{
				do_damage( id, enemy, godshealth[id] + 2048, 22, 1, weapon, bodypart, 0 );
			}
		}
		else
		{
			set_user_health_log( id, get_user_health( id ) + damage );
			return PLUGIN_HANDLED;
		}
	}

	damage = read_data( 2 );

	if( HasTeamShield[id] )
	{
		new PlayerShieldedBy = p_PlayerShieldedBy[id];
		new trained = p_skills[PlayerShieldedBy][SKILLIDX_TEAMSHIELD];
		new DamageAbsorbed = p_ShieldMaxDamageAbsorbed[PlayerShieldedBy];

		new name[32], friend_name[32];
		get_user_name ( id, name, 31 );
		get_user_name ( PlayerShieldedBy, friend_name, 31 );

		new temp_a = 0;

		//make sure all parties are still alive
		if( is_user_alive(id) && is_user_alive( PlayerShieldedBy ) && is_user_connected(id) && is_user_connected( PlayerShieldedBy ) )
		{
			if( DamageAbsorbed <= p_ShieldMaxDamage[trained] )
			{
				while( ( DamageAbsorbed < p_ShieldMaxDamage[trained] ) && ( damage > 0 ) )
				{
					damage--;
					DamageAbsorbed++;
					temp_a++;

					if( damage <= 0)
						break;
				}

				if( temp_a  > 0)
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print( id, print_chat, "%L", id, "TEAMSHIELD_ABSORB1", MOD, friend_name, temp_a );
					}

					if( Util_Should_Msg_Client( PlayerShieldedBy ) )
					{
						client_print( PlayerShieldedBy, print_chat, "%L", PlayerShieldedBy, "TEAMSHIELD_ABSORB2", MOD, temp_a, name );
					}

					do_damage( PlayerShieldedBy, id, temp_a, 24, 1, weapon, bodypart, 0 );
					damageto[id][enemy] -= temp_a;
					p_ShieldMaxDamageAbsorbed[PlayerShieldedBy] += temp_a;
					set_user_health ( id, get_user_health ( id ) + temp_a );

					//Give the guy some XP
					ability_TeamShieldXP( id, PlayerShieldedBy );
				}

				//Need to re-check if they have a shield at this point
				new parm[3];
				parm[0] = id; //The guy with the shield
				parm[1] = PlayerShieldedBy; //The guy who provided the shield
				parm[2] = 0;
				set_task ( 1.0, "TASK_SHIELD_CHECK", TASK_SHIELD_CHECK_ID + id, parm, 3 );
			}

			//if there is no damage left, no sense in continuing
			if( damage <= 0 )
			{
				return PLUGIN_HANDLED;
			}
		}
		else
		{
			//One of the two is not alive, reset status
			HasTeamShield[id] = false;
		}

	}
	// [08-10-04] - Evasion completely rewritten and modified for Dexterity bonus - K2mia
	// [07-30-04] - Moved Evasion check to be before other skill checks - K2mia
	if ( p_skills[id][SKILLIDX_EVASION] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:evade_percent = p_evasion[p_skills[id][SKILLIDX_EVASION]-1];

		if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_DEX] > ATTRIB_BASE ) )
		{
			new edex = ( p_attribs[id][ATTRIBIDX_DEX] - ATTRIB_BASE );
			evade_percent += ( float( edex ) * DEX_EVADE_BONUS );
		}

		if ( is_user_alive( id ) && ( randomnumber <= evade_percent ) )
		{
			p_evadethisshot[id] = true;
		}
		else
		{
			p_evadethisshot[id] = false;
		}

		if ( p_evadethisshot[id] )
		{
			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			damage = read_data( 2 );

			set_user_health_log( id, get_user_health( id ) + damage );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id,"EVADE1", MOD, ename );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy,"EVADE2", MOD, idname );
			}

			if ( iglow[id][2] < 1 )
			{
				new parm[2];
				parm[0] = id;
				set_task( 0.01, "ChangeGlow", 7, parm, 2 );
			}

			iglow[id][2] += damage;
			iglow[id][0] = 0;
			iglow[id][1] = 0;
			iglow[id][3] = 0;

			if ( iglow[id][2]>MAXGLOW )
				iglow[id][2] = MAXGLOW;

			if( Util_Should_Msg_Client( id ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 0 ); // fade red
				write_byte( 0 ); // fade green
				write_byte( 255 ); // fade blue
				write_byte( iglow[id][2] ); // fade alpha
				message_end( );
			}
		}
	// End of Elf Evasion
	}

	if ( CVAR_DEBUG_MODE )
	{
		client_print( 0, print_console, "[%s DEBUG In damage_event( )] <%s => %s> damage=( %d ) was_evaded?=( %d )", MOD, name2, name1, damage, p_evadethisshot[id] );
	}

	if ( p_skills[enemy][SKILLIDX_CRITSTRIKE] && p_skills[enemy][SKILLIDX_TRUESHOT] )
	{
		// Check for chance of Trueshot/Crit Strike backfire on enemy
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber < ( ( p_skills[enemy][SKILLIDX_CRITSTRIKE] + p_skills[enemy][SKILLIDX_TRUESHOT] )/2 ) )
		{
			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			// [09-03-04] Modified backfire damage to be half a player's health
			damage = ( get_user_health( enemy ) / 2 );
			do_damage( enemy, id, damage, 21, 2, weapon, bodypart, 0 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id,"CRIT_STRIKE_BACKFIRE2", MOD, ename );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy,"CRIT_STRIKE_BACKFIRE1", MOD );
			}

			if ( iglow[enemy][0] < 1 )
			{
				new parm[2];
				parm[0] = enemy;
				set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
			}

			iglow[enemy][0] += damage;
			iglow[enemy][1] = 0;
			iglow[enemy][2] = 0;
			iglow[enemy][3] = 0;

			if ( iglow[enemy][0] > MAXGLOW )
				iglow[enemy][0] = MAXGLOW;

			if( Util_Should_Msg_Client( id ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 255 ); // fade red
				write_byte( 0 ); // fade green
				write_byte( 125 ); // fade blue
				write_byte( iglow[enemy][0] ); // fade alpha
				message_end( );
			}
		}
		// End of Backfire from Crit. Strike and Trueshot
	}

	// Shadow Strike
	// [08-05-04] - Evasion now protects against Shadow Strike
	if ( p_skills[enemy][SKILLIDX_SSTRIKE] && !p_evadethisshot[id] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );

		new Float:ss_chance = p_shadow[p_skills[enemy][SKILLIDX_SSTRIKE]-1];

		if ( USE_ENH && p_resists[id][RESISTIDX_POISON] )
		{
			ss_chance = ss_chance - ( ( float( p_resists[id][RESISTIDX_POISON] ) / float( RESIST_MAX_VALUE ) ) * ss_chance );
		}

		// [07-14-04] - Now only poisons a person one time - K2mia
		// removed ( p_resists[id][RESISTIDX_POISON] < RESIST_MAX_VALUE ) &&
		//from if statement
		if ( ( randomnumber <= ss_chance ) && ( shadowcount[enemy] > 0 ) && is_user_alive( id ) && !ispoisonedss[id] )
		{
			new idorigin[3];
			new enemyorigin[3];
			get_user_origin( id, idorigin );
			get_user_origin( enemy, enemyorigin );
			message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
			write_byte( TE_SPRITETRAIL );
			write_coord( enemyorigin[0] );
			write_coord( enemyorigin[1] );
			write_coord( enemyorigin[2] );
			write_coord( idorigin[0] );
			write_coord( idorigin[1] );
			write_coord( idorigin[2] );
			write_short( shadow ); // short ( sprite index )
			write_byte( 50 ); // byte ( count )
			write_byte( 15 ); // byte ( life in 0.1's )
			write_byte( 3 ); // byte ( scale in 0.1's )
			write_byte( 2 ); // byte ( velocity along vector in 10's )
			write_byte( 6 ); // byte ( randomness of velocity in 10's )
			message_end( );
			set_hudmessage( 200, 100, 0, 0.2, 0.2, 0, 1.0, 5.0, 0.1, 0.2, 2 );
			shadowcount[enemy]--;

			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );


			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "POISON2", MOD, ename );
				if ( file_exists( "sound/uwc3x/shadowstrikebirth1.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/shadowstrikebirth1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "POISON1", MOD, idname );

				if ( file_exists( "sound/uwc3x/shadowstrikebirth1.wav" ) == 1 )
				{
					emit_sound( enemy, CHAN_STATIC, "uwc3x/shadowstrikebirth1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}

			// 6-19-2004 - Damage modified to be based on level ( K2mia )
			damage = floatround( p_level[enemy] / 2.0 );
			do_damage( id, enemy, damage, 9, 1, weapon, bodypart, 0 );
			ispoisonedss[id] = 1;

			// [ 09-06-04] - Attach poison1.spr to the infected
			message_begin( MSG_ALL, SVC_TEMPENTITY );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 );
			write_short( poison );
			write_short( 25 );
			message_end( );

			new args[2];
			args[0] = id;
			args[1] = enemy;
			
			SetTaskUnique(2.0, "do_sspoison", TASK_ON_SSPOISON + id, args, 2, "b");

		}
		else if ( ( randomnumber <= p_shadow[p_skills[enemy][SKILLIDX_SSTRIKE]-1] ) && ( shadowcount[enemy] > 0 ) && is_user_alive( id ) && !ispoisonedss[id] )
		{
			// If we are here then the resistance is what caused Shadow Strike to fail
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "POISON3", MOD );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "POISON4", MOD );
			}

		}
	}
	else if ( p_skills[enemy][SKILLIDX_SSTRIKE] && p_evadethisshot[id] )
	{
		if ( CVAR_DEBUG_MODE )
		{
			client_print( id, print_console, "[%s DEBUG In damage_event( )] Shot evaded, Shadow Strike check skipped", MOD );
		}
	}
	// End of Shadow Strike

	//ROT
	if ( p_skills[enemy][SKILLIDX_ROT] && !p_evadethisshot[id] )
	{

		new Float:randomnumber = random_float( 0.0, 1.0 );
		new bool:savethrow=false;

		//see if they have rot resist, and if so - do a save throw
		if( p_resists[id][RESISTIDX_ROT] )
		{
			if( rot_saving_throw( id ) == 1 )
			{
				savethrow=true;
			}
		}

		new rotskill = p_skills[enemy][SKILLIDX_ROT];
		
		if ( rotskill > 0 && ( randomnumber <= p_rotchance[rotskill-1] ) && !savethrow && is_user_alive( id ) && !bIsRotting[id] )
		{
			new idorigin[3];
			new enemyorigin[3];
			get_user_origin( id, idorigin );
			get_user_origin( enemy, enemyorigin );

			message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
			write_byte( TE_SPRITETRAIL );
			write_coord( enemyorigin[0] );
			write_coord( enemyorigin[1] );
			write_coord( enemyorigin[2] );
			write_coord( idorigin[0] );
			write_coord( idorigin[1] );
			write_coord( idorigin[2] );
			write_short( ROTtrail ); // short ( sprite index ) -> this is the trail
			write_byte( 50 ); // byte ( count )
			write_byte( 15 ); // byte ( life in 0.1's )
			write_byte( 1 ); // byte ( scale in 0.1's )
			write_byte( 2 ); // byte ( velocity along vector in 10's )
			write_byte( 6 ); // byte ( randomness of velocity in 10's )
			message_end( );
			set_hudmessage( 200, 100, 0, 0.2, 0.2, 0, 1.0, 5.0, 0.1, 0.2, 2 );

			rotcount[enemy]--;

			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "ROT2", MOD, ename );

				if ( file_exists( "sound/uwc3x/dohgodoh.wav" ) == 1 )
					emit_sound( id, CHAN_STATIC, "uwc3x/dohgodoh.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );

			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", id, "ROT1", MOD, idname );

				if ( file_exists( "sound/uwc3x/carrionswarmlaunch1.wav" ) == 1 )
					emit_sound( enemy, CHAN_STATIC, "uwc3x/carrionswarmlaunch1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
			}

			if( !bIsRotting[id] )
			{
				bIsRotting[id] = true;
			}

			Skill_Rot_Handler( id );
			damage = floatround( p_level[enemy] / 2.0 );
			do_damage( id, enemy, damage, 25, 1, weapon, bodypart, 0 );

            // Attach ROTspr.spr to the infected
			message_begin( MSG_ALL, SVC_TEMPENTITY );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 );
			write_short( ROTspr );
			write_short( 25 );
			message_end( );

			new args[2];
			args[0] = id;
			args[1] = enemy;
			
			SetTaskUnique(3.0, "do_rot", TASK_ON_ROT + id , args, 2, "b");
		}
		else if ( ( savethrow ) && is_user_alive( id ) && !bIsRotting[id] )
		{
			// If we are here then the resistance is what caused Rot to fail
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "ROT3", MOD );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "ROT4", MOD );
			}

		}
	}
	//END OF ROT

	// Carrion Beetle
	// [08-05-04] - Evasion now protects against Carrion Beetles
	if( p_skills[enemy][SKILLIDX_CARRION] && !p_evadethisshot[id] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:cb_chance = p_carrion[p_skills[enemy][SKILLIDX_CARRION]-1];

		if ( USE_ENH && p_resists[id][RESISTIDX_DISEASE] )
		{
			cb_chance = cb_chance - ( ( float( p_resists[id][RESISTIDX_DISEASE] ) / float( RESIST_MAX_VALUE ) ) * cb_chance );
		}

		new idname[32], ename[32];
		get_user_name( id, idname, 31 );
		get_user_name( enemy, ename, 31 );

		// [07-14-04] - Now only diseases a person one time - K2mia
		//removed ( p_resists[id][RESISTIDX_DISEASE] < RESIST_MAX_VALUE ) &&
		//from if statement
		if ( ( randomnumber <= cb_chance ) && ( carrioncount[enemy] > 0 ) && is_user_alive( id ) && !isdiseasedcb[id] )
		{
			new idorigin[3];
			new enemyorigin[3];
			get_user_origin( id, idorigin );
			get_user_origin( enemy, enemyorigin );
			message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
			write_byte( TE_SPRITETRAIL );
			write_coord( enemyorigin[0] );
			write_coord( enemyorigin[1] );
			write_coord( enemyorigin[2] );
			write_coord( idorigin[0] );
			write_coord( idorigin[1] );
			write_coord( idorigin[2] );
			write_short( carrion ); // short ( sprite index )
			write_byte( 50 ); // byte ( count )
			write_byte( 15 ); // byte ( life in 0.1's )
			write_byte( 1 ); // byte ( scale in 0.1's )
			write_byte( 2 ); // byte ( velocity along vector in 10's )
			write_byte( 6 ); // byte ( randomness of velocity in 10's )
			message_end( );
			set_hudmessage( 200, 100, 0, 0.2, 0.2, 0, 1.0, 5.0, 0.1, 0.2, 2 );
			carrioncount[enemy]--;

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "DISEASE2", MOD, ename );

				if ( file_exists( "sound/uwc3x/carrionswarmdamage1.wav" ) == 1 )
				{
					emit_sound( id, CHAN_STATIC, "uwc3x/carrionswarmdamage1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "DISEASE1", MOD, idname );

				if ( file_exists( "sound/uwc3x/carrionswarmlaunch1.wav" ) == 1 )
				{
					emit_sound( enemy, CHAN_STATIC, "uwc3x/carrionswarmlaunch1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}
			}

			// 6-19-2004 - Carrion Beetles damage modified, now based on level ( K2mia )
			damage = floatround( p_level[enemy] / 2.0 );
			do_damage( id, enemy, damage, 1, 1, weapon, bodypart, 0 );

			isdiseasedcb[id] = 1;

			// [ 09-02-04] - Attach bm2.spr to the infected
			message_begin( MSG_ALL, SVC_TEMPENTITY );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 );
			write_short( cbgreen );
			write_short( 25 );
			message_end( );

			new args[2];
			args[0] = id;
			args[1] = enemy;
			
			SetTaskUnique(3.0, "do_cbdisease", TASK_ON_CBDISEASE + id, args, 2, "b");
		}
		else if ( ( randomnumber <= p_carrion[p_skills[enemy][SKILLIDX_CARRION]-1] ) && ( carrioncount[enemy] > 0 ) && is_user_alive( id ) && !isdiseasedcb[id] )
		{
			// If we are here then the resistance is what caused Carrion Beetles to fail
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "DISEASE3", MOD );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "DISEASE4", MOD );
			}
		}
	}
	else if ( p_skills[enemy][SKILLIDX_CARRION] && p_evadethisshot[id] )
	{
		if ( CVAR_DEBUG_MODE )
		{
			client_print( id, print_console, "[%s DEBUG In damage_event( )] Shot evaded, Carrion Beetles check skipped", MOD );
		}

	}
	// End of Carrion Beetle


	// New Beginner's Luck implied skill for levels 0-4
	if ( CVAR_ENABLE_BEGINERS_LUCK && ( id != enemy ) && ( 0 < id <= MAX_PLAYERS ) && ( 0 < enemy <= MAX_PLAYERS ) )
	{
		// [07-25-04] - Beginner's Luck skill ( evade chance for victim, dbl dmg for attacker )

		if ( ( 0 <= p_level[id] <= 4 ) && ( p_level[enemy] >= 15 ) && ( get_user_health( id ) > damage ) )
		{
			// [07-25-04] - Beginner's Luck skill check for evaded shot
			new Float:nEvadeChance = ( 0.50 - ( float( p_level[id] ) * 0.10 ) );
			new Float:randomnumber = random_float( 0.0, 1.0 );

			if ( randomnumber <= nEvadeChance )
			{
				// Player evades this shot
				new nHealth = get_user_health( id ) + damage;
				set_user_health_log( id, nHealth );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "BEGIN_LUCK1", MOD, name2 );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "BEGIN_LUCK2", MOD, name1 );
				}

			}
		}
		else if ( ( 0 <= p_level[enemy] <= 4 ) && ( p_level[id] >= 15 ) && !p_evadethisshot[id] )
		{
			// [07-25-04] - Beginner's Luck skill check for double damage
			new Float:nDblChance = ( p_level[enemy] == 4 ) ? 0.10 : ( 0.80 - ( float( p_level[enemy] ) * 0.20 ) );
			new Float:randomnumber = random_float( 0.0, 1.0 );

			if ( randomnumber <= nDblChance )
			{
				// Player gets double attack bonus
				new nDmg = damage;
				do_damage( id, enemy, nDmg, 20, 1, weapon, bodypart, 0 );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "BEGIN_LUCK4", MOD, name2 );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "BEGIN_LUCK3", MOD, name1 );
				}

			}
		}
	}


	// Thorns Aura
	if ( p_skills[id][SKILLIDX_THORNS] && !p_evadethisshot[id] )
	{
		damage = read_data( 2 );
		//new orig_dmg = damage;

		damage = floatround( float( damage ) * p_thorns[p_skills[id][SKILLIDX_THORNS]-1] );
		damage = ( damage < THORNS_MAX_DMG ) ? damage : THORNS_MAX_DMG;

		//if ( CVAR_DEBUG_MODE )
		//{
		//	new idname[32], ename[32];
		//	get_user_name( id, idname, 31 );
		//	get_user_name( enemy, ename, 31 );
		//	client_print( enemy, print_console, "THORNS DEBUG: You attacked %s ( has thorns ) orig_dmg=( %d ) thorns_dmg=( %d ) orig_health=( %d ) after_thorns_health=( %d )", idname, orig_dmg, damage, get_user_health( enemy ), ( get_user_health( enemy )-damage ) );
		//	log_amx( "[UWC3X] THORNS DEBUG: %s attacked %s ( has thorns ) orig_dmg=( %d ) thorns_dmg=( %d ) orig_health=( %d ) after_thorns_health=( %d )", ename, idname, orig_dmg, damage, get_user_health( enemy ), ( get_user_health( enemy )-damage ) );
		//}

		do_damage( enemy, id, damage, 2, 2, weapon, bodypart, 0 );

		if ( iglow[enemy][0] < 1 )
		{
			new parm[2];
			parm[0] = enemy;
			set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
		}

		new idname[32], ename[32];
		get_user_name( id, idname, 31 );
		get_user_name( enemy, ename, 31 );

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "THORNS2", MOD, ename );
		}

		if( Util_Should_Msg_Client(enemy) )
		{
			client_print( enemy, print_chat, "%L", enemy, "THORNS1", MOD, idname );
		}

		iglow[enemy][0] += 3 * damage;
		iglow[enemy][1] = 0;
		iglow[enemy][2] = 0;
		iglow[enemy][3] = 0;

		if ( iglow[enemy][0] > MAXGLOW )
			iglow[enemy][0] = MAXGLOW;

		if( Util_Should_Msg_Client( enemy ) )
		{

			// [09-09-04] - Added thorns armor effect - K2mia
			//message_begin( MSG_ALL, SVC_TEMPENTITY )
			message_begin( MSG_ONE, SVC_TEMPENTITY, { 0, 0, 0 }, enemy );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 ); // for thorns
			write_short( thorns );
			write_short( 25 );
			message_end( );

			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 255 ); // fade red
			write_byte( 0 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[enemy][0] ); // fade alpha
			message_end( );
			// End of Thorns Aura
		}
	}

	// Trueshot
	// [08-10-04] - Evasion now protects against Trueshot strikes - K2mia
	if ( p_skills[enemy][SKILLIDX_TRUESHOT] && !p_evadethisshot[id] )
	{
		damage = read_data( 2 );

		new SkillLevel = ( p_skills[enemy][SKILLIDX_TRUESHOT] -1 );

		if( SkillLevel > 0 )
		{
			new Float:ts_dmg = p_trueshot[ SkillLevel ];

			if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_TRUESHOT_LEVEL ) )
			{
				ts_dmg += INT_TRUESHOT_BONUS;

				if ( CVAR_DEBUG_MODE )
				{
					client_print( enemy, print_console, "[%s DEBUG] Intellect-Trueshot damage modified=( %f )", MOD, ts_dmg );
				}
			}

			damage = floatround( float( damage ) * ts_dmg );
			do_damage( id, enemy, damage, 3, 1, weapon, bodypart, 0 );

			if ( iglow[id][0] < 1 )
			{
				new parm[2];
				parm[0] = id;
				set_task( 0.01, "ChangeGlow", 14, parm, 2 );
			}

			iglow[id][0] += 2 * damage;
			iglow[id][1] = 0;
			iglow[id][2] = 0;
			iglow[id][3] = 0;

			if ( iglow[id][0] > MAXGLOW )
				iglow[id][0] = MAXGLOW;

			if( Util_Should_Msg_Client( id ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 255 ); // fade red
				write_byte( 0 ); // fade green
				write_byte( 0 ); // fade blue
				write_byte( iglow[id][0] ); // fade alpha
				message_end( );
			}
		}
	}
	// End of Trueshot

	// Spiked Carapace
	if ( p_skills[id][SKILLIDX_CARAPACE] && !p_evadethisshot[id] )
	{
		damage = read_data( 2 );
		damage = floatround( float( damage ) * p_spiked[p_skills[id][SKILLIDX_CARAPACE]-1] );
		damage = ( damage < SPIKED_MAX_DMG ) ? damage : SPIKED_MAX_DMG;
		do_damage( enemy, id, damage, 4, 2, weapon, bodypart, 0 );

		new idname[32], ename[32];
		get_user_name( id, idname, 31 );
		get_user_name( enemy, ename, 31 );

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "SPIKED2", MOD, ename );
		}

		if( Util_Should_Msg_Client(enemy) )
		{
			client_print( enemy, print_chat, "%L", enemy, "SPIKED1", MOD, idname );
		}

		if( get_user_armor( id )<101 )
		{
			set_user_armor_log( id, ( get_user_armor( id )+damage ) );
		}

		if ( iglow[enemy][0] < 1 )
		{
			new parm[2];
			parm[0] = enemy;
			set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
		}

		iglow[enemy][0] += 3 * damage;
		iglow[enemy][1] = 0;
		iglow[enemy][2] = 0;
		iglow[enemy][3] = 0;

		if ( iglow[enemy][0] > MAXGLOW )
			iglow[enemy][0] = MAXGLOW;

		if( Util_Should_Msg_Client( enemy ) )
		{
			// [09-07-04] - Added spiked armor effect - K2mia
			//message_begin( MSG_ALL, SVC_TEMPENTITY )
			message_begin( MSG_ONE, SVC_TEMPENTITY, { 0, 0, 0 }, enemy );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 ); // for spikes symbol
			write_short( spikes );
			write_short( 25 );
			message_end( );

			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 255 ); // fade red
			write_byte( 0 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[enemy][0] ); // fade alpha
			message_end( );
		}
	}
	// End of Spiked Carapace


	// Impale
	// [08-10-04] - Evasion now protects against Impale - K2mia
	if ( p_skills[enemy][SKILLIDX_IMPALE] && !p_evadethisshot[id] )
	{
		//Wisdom check

		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:impale_chance = p_impale[p_skills[enemy][SKILLIDX_IMPALE]-1];

		if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_IMPALE_LEVEL ) )
		{
			impale_chance += INT_IMPALE_BONUS;
		}

		// If they have a chance
		if ( randomnumber <= impale_chance )
		{
			//Check wisdom
			if( !ImpaleResisted( id, enemy ) )
			{
				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "IMPALE2", MOD );

					if ( file_exists( "sound/uwc3x/impalehit.wav" ) == 1 )
					{
						emit_sound( id, CHAN_ITEM, "uwc3x/impalehit.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}	
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "IMPALE1", MOD, idname );
				}

				if( Util_Should_Msg_Client( id ) )
				{
					message_begin( MSG_ONE, gmsgShake, { 0, 0, 0 }, id );
					write_short( 255<< 14 ); //ammount
					write_short( 10 << 14 ); //lasts this long
					write_short( 255<< 14 ); //frequency
					message_end( );
				}
			}
		}
	}
	// End of Impale

	// Hex
	// [08-10-04] - Evasion now protects against Hex - K2mia
	if ( p_skills[enemy][SKILLIDX_HEX] && !p_evadethisshot[id] )
	{
		//Check for wisdom bonus and make a save throw
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:hex_chance = p_hex[p_skills[enemy][SKILLIDX_HEX]-1];

		if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_HEX_LEVEL ) )
		{
			hex_chance += INT_HEX_BONUS;
		}

		if ( ( randomnumber <= hex_chance ) && !skinchanged[id] )
		{
			if( !HexResisted( id, enemy ) )
			{
				changeskin( id, 2 );
				new parm[2];
				parm[0] = id;
				parm[1] = 0;
				jumper( parm );

				bHexed[id] = true;

				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "HEX1", MOD, ename );
					if ( file_exists( "sound/uwc3x/hex_infect.wav" ) == 1 )
					{
						emit_sound( id, CHAN_STATIC, "uwc3x/hex_infect.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}	
                }
				
				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "HEX2", MOD, idname );
				}
			}
		}
	}
	// End of Hex

	// Banish
	// [08-10-04] - Evasion now protects against Banish - K2mia
	if ( p_skills[enemy][SKILLIDX_BANISH] && !p_evadethisshot[id] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:banish_chance = p_banish[p_skills[enemy][SKILLIDX_BANISH]-1];

		if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_BANISH_LEVEL ) )
		{
			banish_chance += INT_BANISH_BONUS;
		}

		if ( randomnumber <= banish_chance )
		{
			if( !BanishResisted( id, enemy ) )
			{
				new parm[2];
				parm[0] = id;

				if( randomnumber>9 )
				{
					user_slap( id, 0 );
					user_slap( id, 0 );
					user_slap( id, 0 );
					do_damage( id, id, 9, 5, 2, weapon, bodypart, 0 );
				}
				else
				{
					user_slap( id, 0 );
					user_slap( id, 0 );
					user_slap( id, 0 );
					do_damage( id, id, 7, 5, 2, weapon, bodypart, 0 );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					if ( file_exists( "sound/uwc3x/banishcaster.wav" ) == 1 )
						emit_sound( enemy, CHAN_STATIC, "uwc3x/banishcaster.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
				}

				if ( iglow[id][3] < 1 )
				{
					parm[0] = id;
					parm[1] = 0;
					set_task( 0.01, "ChangeGlow", 11, parm, 2 );
				}

				iglow[id][3] += 100;
				iglow[id][0] = 0;
				iglow[id][1] = 0;
				iglow[id][2] = 0;

				if ( iglow[id][3]>MAXGLOW )
					iglow[id][3] = MAXGLOW;

				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "BANISH2", MOD, ename );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "BANISH1", MOD, idname );
				}

				if( Util_Should_Msg_Client( id ) )
				{
					message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
					write_short( 1<<10 ); // fade lasts this long duration
					write_short( 1<<10 ); // fade lasts this long hold time
					write_short( 1<<12 ); // fade type ( in / out )
					write_byte( 255 ); // fade red
					write_byte( 255 ); // fade green
					write_byte( 255 ); // fade blue
					write_byte( iglow[id][3] ); // fade alpha
					message_end( );
				}
			}
		}
	}
	// End of Banish

	// Siphon Ammo
	// Evasion protects against Siphon Ammo
	if ( p_skills[enemy][SKILLIDX_SAMMO] && !p_evadethisshot[id] )
	{
		new i_ammo, e_ammo, i_clip, e_clip;
		new idgun = get_user_weapon( id, i_clip, i_ammo );
		new enemygun = get_user_weapon( enemy, e_clip, e_ammo );


		//Only continue if the weapon ids are not 29 - this solves an invalid gun ID error
		/*
			[CSTRIKE] Invalid weapon id 29
			Displaying debug trace (plugin "uwc3x.amxx")
			Run time error 10: native error (native "cs_set_user_bpammo")
			[0] uwc3_dmgevents.inc::damage_event (line 1172)
		*/

		//Makes sure that the weapon is primary or secondary, otherwise bail
		if ( ( IsWeaponPrimary( enemygun ) || IsWeaponSecondary( enemygun ) ) && ( enemygun != 29 && idgun != 29 ) )
		{
			// [08-07-04] - Money modified by high intellect bonus
			new Float:ammo_percent = p_ammo[p_skills[enemy][SKILLIDX_SAMMO]-1];
			new x_ammo = floatround( ammo_percent * i_ammo );

			if ( !is_user_connected( id ) || !is_user_connected( enemy ) )
				return PLUGIN_CONTINUE;

			if ( x_ammo < 1 )
				return PLUGIN_CONTINUE;

			cs_set_user_bpammo( enemy, enemygun, e_ammo+x_ammo );
			cs_set_user_bpammo( id, idgun, i_ammo-x_ammo );

			new idname[32], ename[32];
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "SYPHON2", MOD, x_ammo, ename );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "SYPHON1", MOD, x_ammo, idname );
			}

			if ( iglow[enemy][1] < 1 )
			{
				new parm[2];
				parm[0] = enemy;
				set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW3, parm, 2 );
			}

			iglow[enemy][1] += damage;
			iglow[enemy][0] = 0;
			iglow[enemy][2] = 0;
			iglow[enemy][3] = 0;

			if ( iglow[enemy][1]>MAXGLOW )
				iglow[enemy][1] = MAXGLOW;

			if( Util_Should_Msg_Client( enemy ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 50 ); // fade red
				write_byte( 50 ); // fade green
				write_byte( 50 ); // fade blue
				write_byte( iglow[enemy][1] ); // fade alpha
				message_end( );
			}
		}

	}
	// End of Siphon Armor

	// Siphon Mana
	// [08-10-04] - Evasion now protects against Siphon Mana - K2mia
	if ( p_skills[enemy][SKILLIDX_SIPHON] && !p_evadethisshot[id] )
	{
		new money = cs_get_user_money( id );

		// [08-07-04] - Money modified by high intellect bonus
		new Float:money_percent = p_mana[p_skills[enemy][SKILLIDX_SIPHON]-1];

		if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_SIPHON_LEVEL ) )
		{
			money_percent += INT_SIPHON_BONUS;
		}

		money = floatround( money_percent * money );

		if ( !is_user_connected( id ) || !is_user_connected( enemy ) )
			return PLUGIN_CONTINUE;

		cs_set_user_money( enemy, cs_get_user_money( enemy )+money, 1 );
		cs_set_user_money( id, cs_get_user_money( id )-money, 1 );

		new idname[32], ename[32];
		get_user_name( id, idname, 31 );
		get_user_name( enemy, ename, 31 );

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "SYPHON4", MOD, money, ename );
		}

		if( Util_Should_Msg_Client(enemy) )
		{
			client_print( enemy, print_chat, "%L", enemy, "SYPHON3", MOD, money, idname );
		}

		if ( iglow[enemy][1] < 1 )
		{
			new parm[2];
			parm[0] = enemy;
			set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW3, parm, 2 );
		}

		iglow[enemy][1] += damage;
		iglow[enemy][0] = 0;
		iglow[enemy][2] = 0;
		iglow[enemy][3] = 0;

		if ( iglow[enemy][1]>MAXGLOW )
			iglow[enemy][1] = MAXGLOW;

		if( Util_Should_Msg_Client( enemy ) )
		{
			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 120 ); // fade red
			write_byte( 120 ); // fade green
			write_byte( 120 ); // fade blue
			write_byte( iglow[enemy][1] ); // fade alpha
			message_end( );
		}

	}
	// End of Siphon Mana

	// Vampiric Aura
	// [08-10-04] - Evasion now protects against Vampiric Aura - K2mia
	// [08-04-04] - Modified Vampiric to not pass test if enemy in full health - K2mia
	if ( p_skills[enemy][SKILLIDX_VAMPIRIC] && ( get_user_health( enemy ) < maxhealth[enemy] ) && !p_evadethisshot[id] )
	{
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: events_damage -> Vampiric Aura -> start()");
		}
		damage = read_data( 2 );
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: Original damage=%d ", damage );
			log_amx( "[UWC3X] DEBUG :: Original Health=%d ", get_user_health( enemy ) );
		}

		damage = floatround( float( damage ) * p_vampiric[p_skills[enemy][SKILLIDX_VAMPIRIC]-1] );

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: Skill Points = %d ", p_skills[enemy][SKILLIDX_VAMPIRIC] );
			log_amx( "[UWC3X] DEBUG :: Vampiric Max Life = %d  ( p_vampirichealth[p_skills[enemy][SKILLIDX_VAMPIRIC]-1])", p_vampirichealth[p_skills[enemy][SKILLIDX_VAMPIRIC]-1] );
			log_amx( "[UWC3X] DEBUG :: Vampiric Percentage = %f ", p_vampiric[p_skills[enemy][SKILLIDX_VAMPIRIC]-1] );
			log_amx( "[UWC3X] DEBUG :: Max Health = %d ", maxhealth[enemy] );
			log_amx( "[UWC3X] DEBUG :: Vampiric Life to give based on damage =%d ", damage );
		}

		//If the amount is less then 1, then set it to 1 so they at least get something
		if( damage < 1 )
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG :: damage < 1 setting to 1 ");
			}
			damage = 1;
		}
		else
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG :: damage (%d) > 1 ", damage);
			}
		}

		// [09-29-04] Rewrote Vampiric ceiling checks - K2mia
		// Set max_health to be the lesser of p_vampiric or maxhealth[enemy]
		new max_health = ( ( maxhealth[enemy] > p_vampirichealth[p_skills[enemy][SKILLIDX_VAMPIRIC]-1] ) ? p_vampirichealth[p_skills[enemy][SKILLIDX_VAMPIRIC]-1] : maxhealth[enemy] );
		new idname[32], ename[32];

		// Add in healthbonus if player has health item
		if ( playeritem[enemy] == HEALTH )
			max_health += HEALTHBONUS;

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: new max_health (%d) ", max_health);
			log_amx( "[UWC3X] DEBUG :: Before - Enemy Health (%d) ", get_user_health( enemy ) );
		}

		if ( get_user_health( enemy ) < max_health )
		{
			new new_health = ( get_user_health( enemy ) + damage );

			if ( new_health > max_health )
				new_health = max_health;

			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug :: The Vampiric Aura from %s steals %d health from %s", ename, damage, idname );
			}
			set_user_health_log( enemy, new_health );
		}

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: After - Enemy Health  = %d", get_user_health( enemy ) );
		}

		if ( p_skills[enemy][SKILLIDX_SSKIN] )
		{
			// Steel Skin, give armor to the enemy
			set_user_armor_log( enemy, ( get_user_armor( enemy )+damage ) );

			new abonusmult = ARMORBONUS2;
			new abonus = 0;
			new atotal = 0;

			if ( p_level[enemy] > 30 )
				abonus = ( abonusmult * 6 );
			else if ( p_level[enemy] > 25 )
				abonus = ( abonusmult * 5 );
			else if ( p_level[enemy] > 20 )
				abonus = ( abonusmult * 4 );
			else if ( p_level[enemy] > 15 )
				abonus = ( abonusmult * 3 );
			else if ( p_level[enemy] > 10 )
				abonus = ( abonusmult * 2 );
			else
				abonus = abonusmult;

			atotal = ( NORMALARMORMAX + abonus );

			if ( get_user_armor( enemy ) > atotal )
				set_user_armor_log( enemy, atotal );

			if ( vampiric_hits[enemy] % 5 == 0 && is_user_connected(enemy) && !is_user_bot(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "STEALSKIN", MOD );
			}

		}

		vampiric_hits[enemy] += 1;

		if ( vampiric_hits[enemy] % 5 == 0 )
		{
			// Only show Vampiric Aura messages after every 5 hits
			get_user_name( id, idname, 31 );
			get_user_name( enemy, ename, 31 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "VAMPIRIC2", MOD, ename );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", id, "VAMPIRIC1", MOD, idname );
			}
		}

		if ( iglow[enemy][1] < 1 )
		{
			new parm[2];
			parm[0] = enemy;
			set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW3, parm, 2 );
		}

		iglow[enemy][1] += damage;
		iglow[enemy][0] = 0;
		iglow[enemy][2] = 0;
		iglow[enemy][3] = 0;

		if ( iglow[enemy][1]>MAXGLOW )
			iglow[enemy][1] = MAXGLOW;

		if( Util_Should_Msg_Client( enemy ) )
		{

			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 0 ); // fade red
			write_byte( 255 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[enemy][1] ); // fade alpha
			message_end( );
		}

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: events_damage -> Vampiric Aura -> end()");
		}
	}
	// End of Vampiric Aura

	//CRIPPLE
	if( p_skills[enemy][SKILLIDX_CRIPPLE] && !p_evadethisshot[id] )
	{
		new cType = cripple_user ( enemy );
		if( cType > 0 )
		{
			do_cripple ( id, enemy, cType )
		}
	}

	// Bash
	// [08-10-04] - Evasion now protects against Bash - K2mia
	if ( p_skills[enemy][SKILLIDX_BASH] && !p_evadethisshot[id] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:bash_chance = p_bash[p_skills[enemy][SKILLIDX_BASH]-1];

		if ( USE_ENH && ( p_attribs[enemy][ATTRIBIDX_INT] >= INT_BASH_LEVEL ) )
		{
			bash_chance += INT_BASH_BONUS;
		}

		//reduce chance by 20% if they have the wisdom for it
		if( p_wisdom_bashresist[id] )
		{
			bash_chance = bash_chance - ( bash_chance * WIS_BASHBONUS );
		}

		if ( ( randomnumber <= bash_chance ) && ( get_user_maxspeed( id ) > 10 ) && !slowed[id] )
		{
			if( !BashResisted( id, enemy ) )
			{
				// Cannot bash if already bashed or frosted
				new normalspeed = floatround( get_user_maxspeed( id ) );
				set_user_maxspeed( id, 1.0 );
				stunned[id] = true;
				new parm[2];
				parm[0] = id;
				parm[1] = normalspeed;
				set_task( 1.0, "reset_maxspeed", TASK_RESET_MAXSPEED+id, parm, 2 );

				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "BASH2", MOD, ename );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "BASH1", MOD, idname );
				}

				if ( iglow[id][3] < 1 )
				{
					parm[0] = id;
					parm[1] = 0;
					set_task( 0.01, "ChangeGlow", 11, parm, 2 );
				}

				iglow[id][3] += 100;
				iglow[id][0] = 0;
				iglow[id][1] = 0;
				iglow[id][2] = 0;

				if ( iglow[id][3]>MAXGLOW )
					iglow[id][3] = MAXGLOW;

				if( Util_Should_Msg_Client( id ) )
				{
					message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
					write_short( 1<<10 ); // fade lasts this long duration
					write_short( 1<<10 ); // fade lasts this long hold time
					write_short( 1<<12 ); // fade type ( in / out )
					write_byte( 255 ); // fade red
					write_byte( 255 ); // fade green
					write_byte( 255 ); // fade blue
					write_byte( iglow[id][3] ); // fade alpha
					message_end( );
				}
			}
		}
	}
	// End of Bash

	// Critical Strike
	// [08-10-04] - Evasion now protects against Critical Strike - K2mia
	if ( p_skills[enemy][SKILLIDX_CRITSTRIKE] && !p_evadethisshot[id] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new SkillLevel = ( p_skills[enemy][SKILLIDX_CRITSTRIKE] -1);

		if( SkillLevel > 0 )
		{

			if ( randomnumber <= p_critical[ SkillLevel ] )
			{
				damage = read_data( 2 );
				// Changed to only do double damage
				damage = floatround( float( damage ) * 1 )

				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );

				if ( hasgodmode[id] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print( id, print_chat, "%L", id, "CRIT_STRIKE2", MOD );
					}

					if( Util_Should_Msg_Client(enemy) )
					{
						client_print( enemy, print_chat, "%L", enemy, "CRIT_STRIKE1", MOD );
					}

				}
				else
				{
					do_damage( id, enemy, damage, 6, 1, weapon, bodypart, 0 );

					if( Util_Should_Msg_Client(id) )
					{
						client_print( id, print_chat, "%L", id, "CRIT_STRIKE4", MOD, ename );
					}

					if( Util_Should_Msg_Client(enemy) )
					{
						client_print( enemy, print_chat, "%L", enemy, "CRIT_STRIKE3", MOD, idname );
					}

				}

				if ( iglow[id][0] < 1 )
				{
					new parm[2];
					parm[0] = id;
					set_task( 0.01, "ChangeGlow", 12, parm, 2 );
				}

				iglow[id][0] += damage;
				iglow[id][1] = 0;
				iglow[id][2] = 0;
				iglow[id][3] = 0;

				if ( iglow[id][0] > MAXGLOW )
					iglow[id][0] = MAXGLOW;

				if( Util_Should_Msg_Client( id ) )
				{
					message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
					write_short( 1<<10 ); // fade lasts this long duration
					write_short( 1<<10 ); // fade lasts this long hold time
					write_short( 1<<12 ); // fade type ( in / out )
					write_byte( 255 ); // fade red
					write_byte( 0 ); // fade green
					write_byte( 0 ); // fade blue
					write_byte( iglow[id][0] ); // fade alpha
					message_end( );
				}
			}
		}
	}
	// Critical Strike

	// Critical Grenade
	// [08-10-04] - Evasion now protects against Critical Grenades - K2mia
	if ( p_skills[enemy][SKILLIDX_CRITGREN] && !p_evadethisshot[id] )
	{
		new bool:allow = true;
		if( playeritem2[enemy] == INFERNO )
		{
			if( CVAR_GLOVE_ORC_DAMAGE )
			{
				allow = true;
			}
			else
			{
				allow = false;
			}
		}
		else
		{
			allow = true;
		}

		if( no_he )
			allow = false;

		if ( weapon == 4 && Util_IsPlayer_Immune ( id, 2 )  )
		{
			allow = false;
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "CRIT_GRENADE1", MOD );
			}
		}

		if ( weapon == 4 && allow )
		{
			damage = read_data( 2 );
			damage = floatround( float( damage ) * p_grenade[p_skills[enemy][SKILLIDX_CRITGREN]-1] );
			do_damage( id, enemy, damage, 7, 1, weapon, bodypart, 0 );
			new name[32] ;
			get_user_name( id, name, 31 );

			if ( iglow[id][0] < 1 )
			{
				new parm[2];
				parm[0] = id;
				set_task( 0.01, "ChangeGlow", 13, parm, 2 );
			}

			iglow[id][0] += damage;
			iglow[id][1] = 0;
			iglow[id][2] = 0;
			iglow[id][3] = 0;

			if ( iglow[id][0] > MAXGLOW )
				iglow[id][0] = MAXGLOW ;

			if( Util_Should_Msg_Client( id ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 255 ); // fade red
				write_byte( 0 ); // fade green
				write_byte( 0 ); // fade blue
				write_byte( iglow[id][0] ); // fade alpha
				message_end( );
			}
		}
	// End of Critical Grenade
	}

	// Napalm Grenade
	// [08-10-04] - Evasion now protects against Napalm Grenades - K2mia
	if ( p_skills[enemy][SKILLIDX_NAPALM] && !p_evadethisshot[id] )
	{

		if ( threwnapalm[enemy] )
			return PLUGIN_CONTINUE;

		new bool:allow = true;
		if( playeritem2[enemy] == INFERNO )
		{
			if( CVAR_GLOVE_NAPALM )
			{
				allow = true;
			}
			else
			{
				allow = false;
			}
		}
		else
		{
			allow = true;
		}

		if( no_he )
			allow = false;

		// Necklace of Immunity now protects against Napalm
		if ( playeritem[id] == IMMUNITY )
			allow = false;

		if ( weapon == 4 && allow )
		{
			threwnapalm[enemy] += 1;
			damage = read_data( 2 );
			do_damage( id, enemy, damage, 17, 1, weapon, bodypart, 0 );

			if( Util_Should_Msg_Client(id) )
			{
				emit_sound( id, CHAN_WEAPON , "scientist/scream07.wav", 1.0, ATTN_NORM, 0, PITCH_HIGH );
			}

			// [09-05-04] Attach fireball sprite to player for 1 cycle
			message_begin( MSG_ALL, SVC_TEMPENTITY );
			write_byte( TE_PLAYERATTACHMENT );
			write_byte( id );
			write_coord( 0 ); // z axis for sprite
			write_short( blast ); // blast sprite
			write_short( 9 );
			message_end( );

			burn_victim_napalm( id, enemy, 0 );

			new name[32], ename[32];
			get_user_name( id, name, 31 );
			get_user_name( enemy, ename, 31 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "NAPALM_GRENADE1", MOD, ename );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "NAPALM_GRENADE2", MOD, name );
			}

		}
	}
	// End of Napalm Grenade

	// Helm Splitter
	if ( p_skills[enemy][SKILLIDX_SPLITTER] )
	{
		new idname[32], ename[32];
		get_user_name( id, idname, 31 );
		get_user_name( enemy, ename, 31 );

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: Splitter -> Start()");
		}

		if( playeritem2[id] == HELM )
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG :: playeritem2[%s] == HELM", idname );
			}

			new Float:randomnumber = random_float( 0.0, 1.0 );
			new Float:splitter_percent = CVAR_SPLITTER_CHANCE;

			if( p_attribs[id][ATTRIBIDX_DEX] > ATTRIB_BASE )
			{
				new Float:sTemp = float( p_attribs[id][ATTRIBIDX_DEX] - ATTRIB_BASE ) / 100.0 ;
				splitter_percent -= sTemp;

				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] DEBUG :: Dex bonus of %f has been subtracted from attacker - new chance is  %f ", ename, splitter_percent );
				}
			}

			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG :: %s has skill vs %s :: Random number %f and splitter_percent %f ", ename, idname, randomnumber, splitter_percent );
			}

			if ( is_user_alive( id ) && is_user_alive( enemy ) && ( randomnumber <= splitter_percent ) )
			{
				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] DEBUG :: Random number <= Chance ( %f <= %f ) - Removing item from %s, play sound and alert clients", randomnumber, splitter_percent, idname );
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "HELMET_SHATTERED1", MOD );
					if ( file_exists ( "sound/uwc3x/helmsplitter.wav" ) ==1 )
					{
						emit_sound ( enemy, CHAN_ITEM, "uwc3x/helmsplitter.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}
					else
					{
						if ( CVAR_DEBUG_MODE )
						{
							log_amx( "[UWC3X] DEBUG :: Sound Doesnt exist!");
						}
					}
				}

				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "HELMET_SHATTERED2", MOD, ename );
					if ( file_exists ( "sound/uwc3x/helmsplitter.wav" ) ==1 )
					{
						emit_sound ( id, CHAN_STATIC, "uwc3x/helmsplitter.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}
					else
					{
						if ( CVAR_DEBUG_MODE )
						{
							log_amx( "[UWC3X] DEBUG :: Sound Doesnt exist!");
						}
					}
				}

				//Get rid of the Shopmenu2 Helmet as well as the armor helmet
				set_user_hitzones( 0 , id , 255 );
				playeritem2[id] = 0;
				helmet[id] = false;
			}
		}
		else
		{
			//Enemy doesnt have HELM
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG :: Player %s doesnt have a helm", idname );
			}
		}

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: Splitter -> End()");
		}
	}
	//END HELM SPLITTER
	
	// Fatal Strike
	// [10-05-09] - New critical strike based on the skill written by Deimos
	if ( p_skills[enemy][SKILLIDX_FATAL])
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new SkillLevel = p_skills[enemy][SKILLIDX_FATAL];
		if( SkillLevel > 0 )
		{
			new Float:fatal_chance = p_fatal_chance[SkillLevel-1];
			if ( randomnumber <= fatal_chance )
			{
				damage = read_data( 2 );
			
				if( SkillLevel == skill_limits[SKILLIDX_FATAL])
				{
					//check for the fatal strike
					new Float:slay_random = random_float( 0.0, 1.0 );
					
					if ( slay_random <= CVAR_FATAL_CHANCE )
					{
						//set the damage equal to 200 - this should be enough to kill anyone
						damage = 200;
					}
					else
					{
						//They didnt get slayed, just do extra damage
						// Changed to do extra damage
						damage = floatround( float( damage ) * p_fatal_damage[SkillLevel-1] )
					}
				}
				else
				{
					//They dont have skill mastery, just do extra damage
					// Changed to do extra damage
					damage = floatround( float( damage ) * p_fatal_damage[SkillLevel-1] )
				}
			
				new idname[32], ename[32];
				get_user_name( id, idname, 31 );
				get_user_name( enemy, ename, 31 );
				
				do_damage( id, enemy, damage, 30, 1, weapon, bodypart, 0 );
				
				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "FATAL_STRIKE2", MOD, ename );
					if ( file_exists( "sound/uwc3x/critical_hit_02.wav" ) == 1 )
					{
						emit_sound( id, CHAN_STATIC, "uwc3x/critical_hit_02.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}
				}

				if( Util_Should_Msg_Client(enemy) )
				{
					client_print( enemy, print_chat, "%L", enemy, "FATAL_STRIKE1", MOD, idname );
					if ( file_exists( "sound/uwc3x/critical_hit_02.wav" ) == 1 )
					{
						emit_sound( enemy, CHAN_STATIC, "uwc3x/critical_hit_02.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
					}
				}

				if ( iglow[id][0] < 1 )
				{
					new parm[2];
					parm[0] = id;
					set_task( 0.01, "ChangeGlow", 12, parm, 2 );
				}

				iglow[id][0] += damage;
				iglow[id][1] = 0;
				iglow[id][2] = 0;
				iglow[id][3] = 0;

				if ( iglow[id][0] > MAXGLOW )
				{
					iglow[id][0] = MAXGLOW;
				}

				if( Util_Should_Msg_Client( id ) )
				{
					message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
					write_short( 1<<10 ); // fade lasts this long duration
					write_short( 1<<10 ); // fade lasts this long hold time
					write_short( 1<<12 ); // fade type ( in / out )
					write_byte( 255 ); // fade red
					write_byte( 0 ); // fade green
					write_byte( 0 ); // fade blue
					write_byte( iglow[id][0] ); // fade alpha
					message_end( );
				}
			}
		}
	}
	// Fatal Strike

	// Claws of Attack
	// [08-10-04] - Evasion now protects against all item-based attacks - K2mia
	if ( ( playeritem[enemy] == CLAWS ) && !p_evadethisshot[id] )
	{
		damage = CLAWSOFATTACK;
		do_damage( id, enemy, damage, 8, 1, weapon, bodypart, 0 );

		if ( iglow[id][0] < 1 )
		{
			new parm[2];
			parm[0] = id;
			set_task( 0.01, "ChangeGlow", 14, parm, 2 );
		}

		iglow[id][0] += 2 * damage;
		iglow[id][1] = 0;
		iglow[id][2] = 0;
		iglow[id][3] = 0;

		if ( iglow[id][0] > MAXGLOW )
			iglow[id][0] = MAXGLOW;

		if( Util_Should_Msg_Client( id ) )
		{
			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 255 ); // fade red
			write_byte( 0 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[id][0] ); // fade alpha
			message_end( );
		}
	}
	// End of Claws of Attack

	//Begin Shopmenu3 Invulerbility - takes off 6 damage (re-adds it as health)
	else if ( ( playeritem3[id] == INVUL ) && !p_evadethisshot[id] )
	{
		new max_health = maxhealth[id];

		// Add in healthbonus if player has health item
		if ( playeritem[id] == HEALTH )
		{
			max_health += HEALTHBONUS;
		}

		if ( get_user_health( id ) < max_health )
		{
			new new_health = ( get_user_health( id ) + 6 );

			if ( new_health > max_health )
			{
				new_health = max_health;
			}

			set_user_health ( id, new_health );
			set_user_health_log( id, new_health );
		}
	}
	//END Shopmenu3 Invulerbility

	// Mask of Death
	else if ( playeritem[enemy] == MASK )
	{
		damage = read_data( 2 );
		damage = floatround( float( damage ) * MASKPERCENT );

		new health = get_user_health( enemy ) + damage;

		if ( health > maxhealth[enemy] )
			health = maxhealth[enemy];

		set_user_health_log( enemy, health );

		if ( iglow[enemy][1] < 1 )
		{
			new parm[2];
			parm[0] = enemy;
			set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW3, parm, 2 );
		}

		iglow[enemy][1] += damage;
		iglow[enemy][0] = 0;
		iglow[enemy][2] = 0;
		iglow[enemy][3] = 0;

		if ( iglow[enemy][1]>MAXGLOW )
			iglow[enemy][1] = MAXGLOW;

		if( Util_Should_Msg_Client( enemy ) )
		{
			message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, enemy );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 0 ); // fade red
			write_byte( 255 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[enemy][1] ); // fade alpha
			message_end( );
		}
	}
	// End of Mask of Death

	// Frost ( DOESN'T WORK ON BOTS )
	else if ( playeritem[enemy] == FROST && !p_evadethisshot[id] )
	{
		if ( get_user_maxspeed( id )>10 && !slowed[id] )
		{
			// Cannot frost if bashed or frosted
			new Float:speed = get_user_maxspeed( id );
			if(speed > 1.0 && speed != oldSpeed[id])
			{
				oldSpeed[id] = speed;
			}

			// Replace "id" with "enemy" to test bash on self
			set_user_maxspeed( id, FROSTSPEED );

			slowed[id] = true;
			new parm[2];
			parm[0] = id;
			parm[1] = floatround(speed);
			set_task( 1.0, "reset_maxspeed", TASK_RESET_MAXSPEED+id, parm, 2 );

			if ( iglow[id][3] < 1 )
			{
				parm[0] = id;
				parm[1] = 0;
				set_task( 0.01, "ChangeGlow", 11, parm, 2 );
			}

			iglow[id][3] += 100;
			iglow[id][0] = 0;
			iglow[id][1] = 0;
			iglow[id][2] = 0;

			if ( iglow[id][3]>MAXGLOW )
				iglow[id][3] = MAXGLOW;

			if( Util_Should_Msg_Client( id ) )
			{
				message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
				write_short( 1<<10 ); // fade lasts this long duration
				write_short( 1<<10 ); // fade lasts this long hold time
				write_short( 1<<12 ); // fade type ( in / out )
				write_byte( 255 ); // fade red
				write_byte( 255 ); // fade green
				write_byte( 255 ); // fade blue
				write_byte( iglow[id][3] ); // fade alpha
				message_end( );
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public death( )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new killer_id = read_data( 1 );
	new victim_id = read_data( 2 );
	new headshot = read_data( 3 );

	new kname[32], vname[32];
	get_user_name( killer_id, kname, 31 );
	get_user_name( victim_id, vname, 31 );

	// [07-27-04] - Added Logging for all deaths to determine if Voodoo is bugged
	if ( !is_user_connected( victim_id ) )
		return PLUGIN_CONTINUE;

	// Determine if victim has Nightvision
	hasnvision[victim_id] = cs_get_user_nvg( victim_id );

	if ( task_exists( 2000+victim_id ) )
	{
		// Remove the function that makes you jump if you're goombad
		remove_task( 2000+victim_id );
	}

	// Remove icon because you don't have an ultimate when you're dead
	icon_controller( victim_id );

	// For use w/mole protectant
	ismole[victim_id] = false;

	if ( playeritem2[victim_id] == CHAMELEON || skinchanged[victim_id] )
		changeskin( victim_id, 1 );

	if ( playeritem2[victim_id] == HELM )
		set_user_hitzones( 0, victim_id, 255 );

	//Cant grab some one when dead
	grab[victim_id]=0;

	//Cant be grabbed when dead
	Remove_Grab( victim_id );

	if( playeritem2[victim_id] == RESPAWN && !changingteam[victim_id] )
	{
		new parm[2];
		parm[0] = victim_id;
		parm[1] = 6;

		if( playeritem2[victim_id] != MOLE )
		{
			playeritem2[victim_id] = 0;
			rings[victim_id] = 0;
		}

		playeritem[victim_id] = 0;
		set_task( 0.5, "func_spawn", 72, parm, 2 );
		spawnedfromitem[victim_id] = true;
	}

	rings[victim_id] = 0;
	set_user_footsteps( victim_id, 0 );

	new weaponname[20], weapon;
	read_data( 4, weaponname, 31 );
	get_user_attacker( victim_id, weapon );

	if( !deathmessageshown[victim_id] && killer_id != victim_id && !equal( weaponname, "world" ) )
	{
		deathmessageshown[victim_id] = true;
		message_begin( MSG_ALL, gmsgDeathMsg, { 0, 0, 0 }, 0 );
		write_byte( killer_id );
		write_byte( victim_id );
		write_byte( headshot );
		write_string( weaponname );
		write_string( weaponname );
		message_end( );
	}

	changingteam[victim_id] = false;
	diedlastround[victim_id] = true;
	
	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] death :: VENGEANCE :: CHECK :: id=%d; vengeance_used=%d; vengeance_state=%d;", victim_id, vengeance_used[victim_id], vengeance_state[victim_id])
	}

	// Player either has ultimate Vengeance OR Suicide Bomber
	if ( p_skills[victim_id][SKILLIDX_VENGEANCE] && ( !hasblink[killer_id] || killer_id == victim_id ) && !u_delay )
	{
		// Vengeance
		new parm[2];
		parm[0] = victim_id;
		parm[1] = 6;

		// [07-14-04] Vengeance check within ultimate timer - K2mia
		if ( CVAR_FORCE_VENGANCE_DELAY )
		{
			if (CVAR_DEBUG_MODE)
			{
				log_amx("[UWC3X] death :: VENGEANCE :: FREE :: id=%d; vengeance_used=%d; vengeance_state=%d;", victim_id, vengeance_used[victim_id], vengeance_state[victim_id])
			}
		
			// Only check for end of round
			if( !endround && !vengeance_used[victim_id] )
			{
				vengeance_used[victim_id] = 1;
				vengeance_state[victim_id] = VENG_WAIT ;
				set_task( 1.2, "func_spawn", 2, parm, 2 );
				ultimateused[victim_id] = true;
			}
		}
		else
		{
			if (CVAR_DEBUG_MODE)
			{
				log_amx("[UWC3X] death :: VENGEANCE :: RESTRICT :: id=%d; vengeance_used=%d; vengeance_state=%d;", victim_id, vengeance_used[victim_id], vengeance_state[victim_id])
			}
			
			// Restrict Vengeance if another ultimate was recently used
			if( !endround && !ultimateused[victim_id] && !vengeance_used[victim_id] )
			{
				vengeance_used[victim_id] = 1;
				vengeance_state[victim_id] = VENG_WAIT ;
				set_task( 1.2, "func_spawn", 2, parm, 2 );
				ultimateused[victim_id] = true;
			}
		}

		// [08-27-04] - Vengeance cooldown added, so ultimates can again be used
		set_task( CVAR_VENGANCE_COOLDOWN , "cooldown", TASK_COOLDOWN_RESET + victim_id, parm, 1 );

	}
	// End of Vengeance

	// Suicide Bomber
	else if ( p_skills[victim_id][SKILLIDX_SUICIDE] && !hasblink[killer_id] && !changingteam[victim_id] && !u_delay && !( UWC3X_MapDisableCheck( "suicide.cfg" ) ) )
	{
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: events_damage -> Suicide Bomber -> start()");
		}

		if( Util_Should_Msg_Client(victim_id) )
		{
			emit_sound( victim_id, CHAN_ITEM, "ambience/particle_suck1.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}

		new parm[5], origin[3];
		get_user_origin( victim_id, origin );
		parm[0] = victim_id;
		parm[1] = 6;
		parm[2] = origin[0];
		parm[3] = origin[1];
		parm[4] = origin[2];

		set_task( 0.1, "EVENT_Suicide_Implosion", 1, parm, 5 );
		set_task( 0.2, "TASK_Suicide_Explode", TASK_SUICIDE_EXPLODE_NOID, parm, 5 );
		set_task( 0.3, "EVENT_Suicide_Blast", 3, parm, 5 );
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: events_damage -> Suicide Bomber -> end()");
		}

	}
	// End of Suicide Bomber

	// [10-19-04] Do not invoke Phoenix if waiting for Vengeance respawn - K2mia
	if ( vengeance_state[victim_id] != VENG_WAIT )
		check_for_reviving( victim_id );

	saveweapons( victim_id );
	xpgiven = xpgiven_lev[p_level[killer_id]];

	if ( killer_id && killer_id != victim_id && victim_id )
	{
		new name[32];
		get_user_name( victim_id, name, 31 );

		if ( Util_IsSame_Team ( killer_id, victim_id ) )
		{
			if( CVAR_PUNISH_TK_KILLS )
			{
				// Negative experience awarded for team kill
				if ( CVAR_KILL_OBJECTIVES )
				{
					playerxp[killer_id] -= xpgiven;

					if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
					{
						client_print( killer_id, print_center, "[%s] You have been penalized %d XP for killing %s - Jerk!", MOD, xpgiven, name );
					}

				}
			}
		}
		else
		{
			if ( ! CVAR_WEAPON_MULTIPLIER )
			{
				if ( CVAR_KILL_OBJECTIVES )
				{
					playerxp[killer_id] += xpgiven;

					if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
					{
						client_print( killer_id, print_chat, "[%s] You are awarded %d XP for killing %s", MOD, xpgiven, name );
					}

				}
			}
			else
			{
				if ( CVAR_KILL_OBJECTIVES )
				{
					playerxp[killer_id] += floatround( xpgiven * weaponxpmultiplier[weapon] );

					if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
					{
						client_print( killer_id, print_chat, "[%s] You are awarded %d XP for killing %s", MOD, xpgiven, name );
					}
				}
			}

			if ( victim_id == hostagesaver && Util_NotSame_Team ( victim_id, killer_id ) )
			{
				playerxp[killer_id] += KILLRESCUEMANXP;

				if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
				{
					client_print( killer_id, print_chat, "[%s] You received %d XP for killing the hostage rescuer", MOD, KILLRESCUEMANXP );
				}
			}
		}

		if ( CVAR_XP_BONUS_FOR_DAMAGE )
		{
			// [7-1-04] K2mia => Added partial kill XP for majority dmg dealer
			new mdmg = 0; // current max dmg done to victim_id
			new dmg_id = killer_id; // current max damager
			new dmgxp = 0;

			new pid, numplayers, players[32];
			get_players( players, numplayers );

			for ( new i = 0; i< numplayers; i++ )
			{
				pid = players[i];

				if ( damageto[pid][victim_id] > mdmg )
				{
					mdmg = damageto[pid][victim_id];
					dmg_id = pid;
				}

				// [09-14-04] Prevent dmg from being used again - K2mia
				damageto[pid][victim_id] = -1;
			}

			new kteam = get_user_team( killer_id );

			// [08-22-04] - Prevent SPEC from getting serious injury XP
			if ( ( dmg_id != killer_id ) && ( dmg_id != victim_id ) && ( kteam == TEAM_T || kteam == TEAM_CT ) )
			{
				dmgxp = xpgiven_lev[p_level[dmg_id]];
				new dname[32];
				get_user_name( dmg_id, dname, 31 );

				if ( Util_IsSame_Team ( victim_id, killer_id ) )
				{
					if( CVAR_PUNISH_TK_KILLS )
					{
						playerxp[dmg_id] -= dmgxp;
					}

				}
				else
				{
					playerxp[dmg_id] += dmgxp;
				}

				if( is_user_connected( dmg_id ) && !is_user_bot( dmg_id ) )
				{
					client_print( dmg_id, print_chat, "[%s] You receive an XP bonus of %d for seriously injuring %s", MOD, dmgxp, name );
				}
			}
		}

		//code by slmclarengt - added by smokey [04-10-2007]
		if ( CVAR_UNDERDOG_ENABLE && ( p_level[killer_id] < p_level[victim_id] ) )
		{
			// Handler for underdog kill XP bonuses
			new lev_diff = ( p_level[victim_id] - p_level[killer_id] );
			new udogxp = ( lev_diff * XPBONUS );
			new udogpenalty = udogxp;

			if ( lev_diff >= 30 )
			{
				udogxp += ( 3 * xpgiven_lev[p_level[victim_id]] );

				if ( CVAR_UNDERDOG_ENABLE_PENALTY )
				{
					udogpenalty += ( CVAR_UNDERDOG_HIGHLVL_MOD * xpgiven_lev[p_level[killer_id]] );
				}

			}
			else if ( lev_diff >= 20 && lev_diff < 30 )
			{
				udogxp += ( 2 * xpgiven_lev[p_level[victim_id]] );

				if ( CVAR_UNDERDOG_ENABLE_PENALTY )
				{
					udogpenalty += floatround( CVAR_UNDERDOG_MIDLVL_MOD * xpgiven_lev[p_level[killer_id]] );
				}

			}
			else if ( lev_diff >= 10 && lev_diff < 20 )
			{
				udogxp += floatround( 1.5 * xpgiven_lev[p_level[victim_id]] );

				if ( CVAR_UNDERDOG_ENABLE_PENALTY )
				{
					udogpenalty += floatround( CVAR_UNDERDOG_LOWLVL_MOD * xpgiven_lev[p_level[killer_id]] );
				}
			}

			//If the cvar is enabled to penalize the higher level for XP then do it
			if ( CVAR_UNDERDOG_ENABLE_PENALTY )
			{
				playerxp[victim_id] -= udogpenalty;

				if( is_user_connected( victim_id ) && !is_user_bot( victim_id ) )
				{
					client_print( victim_id, print_console, "[%s] You lose an Underdog XP penalty of %d for being killed by %s", MOD, udogpenalty, kname );
				}

			}

			//Award the killer ( lower level ) with the underdog XP
			playerxp[killer_id] += udogxp;

			if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
			{
				client_print( killer_id, print_console, "[%s] You receive an Underdog XP bonus of %d for killing %s", MOD, udogxp, name );
			}
		}

		displaylevel( killer_id, 1 );

	}

	if ( victim_id == bombdefuser && killer_id != bombdefuser && get_user_team( victim_id ) != get_user_team( killer_id ) )
	{
		new temp;
		temp = DEFUSER_KILL_BONUS + xpgiven;

		playerxp[killer_id] += temp;

		if ( CVAR_OBJECTIVES )
		{
			new killersname[33];
			get_user_name( killer_id, killersname, 31 );

			if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
			{
				client_print( killer_id, print_console, "[%s] received %s %d XP for killing the bomb defuser", MOD, killersname, temp );
			}
		}
	}

	if ( victim_id == bombCarrier && killer_id != bombCarrier && Util_NotSame_Team ( victim_id, killer_id ) )
	{
		new temp;
		temp = KILL_BOMB_CARRIER + xpgiven;
		playerxp[killer_id] += temp;

		if ( CVAR_OBJECTIVES )
		{
			new killersname[33];
			get_user_name( killer_id, killersname, 31 );

			if( is_user_connected( killer_id ) && !is_user_bot( killer_id ) )
			{
				client_print( killer_id, print_console, "[%s] received %s %d XP for killing the bomb carrier", MOD, killersname, temp );
			}

		}
	}
	else if( Util_NotSame_Team ( victim_id, killer_id ) )
	{
		if( CVAR_PUNISH_TK_KILLS )
		{
			playerxp[killer_id]-= KILL_BOMB_CARRIER + xpgiven;
		}
	}

	if( HasTeamShield[victim_id] )
	{
		new name[32], friend_name[32];
		get_user_name ( victim_id, name, 31 );
		new PlayerShieldedBy = p_PlayerShieldedBy[victim_id];
		get_user_name ( PlayerShieldedBy, friend_name, 31 );

		//Reset their Team Shield
		HasTeamShield[victim_id] = false;
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: death( ) -> TeamShield -> Reset their Team Shield");
			//Tell them its done - No need, they are dead
			client_print ( PlayerShieldedBy, print_chat, "%L", PlayerShieldedBy, "ULTIMATE_SIV_PLAYER_EXPIRED", friend_name);
		}

		//Remove teh Shield Check task
		if( task_exists(TASK_SHIELD_CHECK_ID + victim_id) )
		{
			remove_task( TASK_SHIELD_CHECK_ID + victim_id );
		}

		if( is_user_alive(PlayerShieldedBy) && is_user_connected(PlayerShieldedBy) )
		{
			//Set cooldown
			new cooldownparm[1];
			cooldownparm[0] = PlayerShieldedBy;

			//Now that its done, start the cooldown
			TeamShieldCooldown[PlayerShieldedBy] = 1;
			set_task ( CVAR_TEAMSHIELD_COOLDOWN, "cooldown3", TASK_COOLDOWN3 + PlayerShieldedBy, cooldownparm, 1 );
		}
	}

	if(hasFrostNade[victim_id])
	{
		hasFrostNade[victim_id] = 0;

		if( Util_Should_Msg_Client( victim_id ) )
		{
			message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},victim_id);
			write_byte(0); // status (0=hide, 1=show, 2=flash)
			write_string("dmg_cold"); // sprite name
			write_byte(FROST_R); // red
			write_byte(FROST_G); // green
			write_byte(FROST_B); // blue
			message_end();
		}
	}

	if( isChilled[victim_id] )
		remove_chill( TASK_REMOVE_CHILL + victim_id );

	if( isFrozen[victim_id] )
		remove_freeze( TASK_REMOVE_FREEZE + victim_id );

	return PLUGIN_CONTINUE;
}


public remove_effects ( id )
{
	blessed[id]                		= false;
	unammo[id]						= false;
	badaim[id]						= false;
	slowed[id]						= false;
	stunned[id]						= false;
	isburning[id]					= 0;
	isnburning[id]					= 0;
	ispoisonedss[id] 				= 0;
	isnburning[id]					= 0;
	ispoisonedss[id] 				= 0;
	isdiseasedcb[id] 				= 0;
	CheckCloak[id] 					= true;
	BlockPickup[id] 				= false;
	bIsRotting[id] 					= false;
	iscrippled[id] 					= 0;
	crippletype[id] 				= 0;
	playerCanBuyitem3[id] 			= 1;
	p_ShieldMaxDamageAbsorbed[id] 	= 0;
	UsedTeamShield[id] 				= 0;
	HasTeamShield[id]				= false;

	grab[id]						= 0;
	Remove_Grab( id );


}

public Remove_Grab ( id )
{
	//ID is the id of the player who was grabbed

	//Find all players, and if they are the person release the grab on them
	new pid, numplayers, players[32];
	get_players( players, numplayers );

	for ( new i = 0; i< numplayers; i++ )
	{
		pid = players[i];

		if ( grab[pid] == id )
		{
			ultimateused[pid] = false;
			grab[pid] = 0;

			new cooldownGrabParm[1];
			cooldownGrabParm[0] = pid;
			if( !task_exists( TASK_GRAB_COOLDOWN+pid ) )
			{
				set_task(CVAR_GRAB_COOLDOWN, "cooldownGrab", TASK_GRAB_COOLDOWN+pid, cooldownGrabParm, 1);
			}
		}
	}
}


public do_rot( args[] )
{
	new id = args[0];
	new enemyz = args[1];

	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] do_rot :: bIsRotting - %d", bIsRotting[id]);
	}

	if( !is_user_alive( id ) || bIsRotting[id] == false )
		return PLUGIN_CONTINUE;

	if ( iglow[id][0] < 1 )
	{
		new parm[2];
		parm[0] = id;
		set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
	}

	iglow[id][0] += 25;
	iglow[id][1] = 0;
	iglow[id][2] = 0;
	iglow[id][3] = 0;

	if ( iglow[id][0] > MAXGLOW )
		iglow[id][0] = MAXGLOW;

	if( Util_Should_Msg_Client( id ) )
	{
		message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
		write_short( 1<<10 ); // fade lasts this long duration
		write_short( 1<<10 ); // fade lasts this long hold time
		write_short( 1<<12 ); // fade type ( in / out )
		write_byte( 255 ); // fade red
		write_byte( 255 ); // fade green
		write_byte( 0 ); // fade blue
		write_byte( iglow[id][0] ); // fade alpha
		/*
		REMOVED AS TEST
		write_short ( ROTspr );
		*/
		message_end( );
	}

	set_rendering ( id, kRenderFxGlowShell, 255,255,0, kRenderFxNone, 10 ) ;
	Skill_RotUser_Bleed( id );
	do_damage( id, enemyz, 7, 25, 2, 0, 0, 0 );

	return PLUGIN_CONTINUE;
}


public do_cbdisease( args[] )
{
	new id = args[0];
	new enemyz = args[1];
	
	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] do_cbdisease :: isdiseasedcb - %d", isdiseasedcb[id]);
	}

	if( !is_user_alive( id ) || isdiseasedcb[id] == 0 )
		return PLUGIN_CONTINUE;

	if ( iglow[id][0] < 1 )
	{
		new parm[2];
		parm[0] = id;
		set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
	}

	iglow[id][0] += 45;
	iglow[id][1] = 0;
	iglow[id][2] = 0;
	iglow[id][3] = 0;

	if ( iglow[id][0] > MAXGLOW )
		iglow[id][0] = MAXGLOW;

	if( Util_Should_Msg_Client( id ) )
	{
		message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
		write_short( 1<<10 ); // fade lasts this long duration
		write_short( 1<<10 ); // fade lasts this long hold time
		write_short( 1<<12 ); // fade type ( in / out )
		write_byte( 0 ); // fade red
		write_byte( 255 ); // fade green
		write_byte( 150 ); // fade blue
		write_byte( iglow[id][0] ); // fade alpha
		message_end( );
	}

	new Float:speed = get_user_maxspeed( id );
	if(speed > 1.0 && speed != oldSpeed[id])
	{
		oldSpeed[id] = speed;
	}
	// Set the player to have a slow max speed
	set_user_maxspeed( id, CBSPEED );

	do_damage( id, enemyz, 3, 19, 2, 0, 0, 0 );

	return PLUGIN_CONTINUE;
}

public cripple_user ( id )
{
	new cType = Ult_Cripple( id );
	switch(cType)
	{
		case 0: return 0;
		case 1: return 1;
		case 2: return 2;
	}

	return 0;
}

public do_cripple ( id, enemy, CrippleType )
{
	//If they are not alive, or are already crippled, skip this
	if( !is_user_alive( id ) )
		return PLUGIN_CONTINUE;

	new Float:speed = get_user_maxspeed( id );
	stunned[id] = true;
	new parm[3];
	parm[0] = id;
	parm[1] = floatround(speed);

	new Float:ftime = 3.0;
	iscrippled[id] = 1;

	new name[32];
	get_user_name( enemy, name, 31 );

	new idname[32];
	get_user_name( id, idname, 31 );

	if( CrippleType == 1 )
	{

		if( Util_Should_Msg_Client( id ) )
		{
			client_print( id, print_chat, "%L", id, "ULTIMATE_CRIPPLE_ENEMY1", MOD, name );
			client_print( id, print_center, "%L", id, "ULTIMATE_CRIPPLE_ENEMY4", name );
		}

		if( Util_Should_Msg_Client( enemy ) )
		{
			client_print( enemy, print_chat, "%L", enemy, "ULTIMATE_CRIPPLE_ENEMY6", MOD, idname );
			client_print( enemy, print_center, "%L", enemy, "ULTIMATE_CRIPPLE_ENEMY8", idname );
		}

		if(speed > 1.0 && speed != oldSpeed[id])
		{
			oldSpeed[id] = speed;
		}

		ftime = 2.0;
		set_user_maxspeed ( id, CRIPPLESPEED1 );
		crippletype[id] = 1;
	}

	if( CrippleType == 2 )
	{
		if( Util_Should_Msg_Client( id ) )
		{
			client_print( id, print_chat, "%L", id, "ULTIMATE_CRIPPLE_ENEMY2", MOD, name );
			client_print( id, print_center, "%L", id, "ULTIMATE_CRIPPLE_ENEMY5", name );
		}
		if( Util_Should_Msg_Client( enemy ) )
		{
			client_print( enemy, print_chat, "%L", enemy, "ULTIMATE_CRIPPLE_ENEMY7", MOD, idname );
			client_print( enemy, print_center, "%L", enemy, "ULTIMATE_CRIPPLE_ENEMY9", idname );
		}

		new Float:speed = get_user_maxspeed( id );
		if(speed > 1.0 && speed != oldSpeed[id])
		{
			oldSpeed[id] = speed;
		}

		set_user_maxspeed ( id, CRIPPLESPEED2 );
		ftime = 4.0;
		crippletype[id] = 2;
	}

	parm[0] = id;
	parm[1] = floatround(speed);
	parm[2] = enemy;

	set_task ( ftime, "Task_Reset_Cripple", TASK_RESET_CRIPPLE_ID + id, parm, 3 );
	return PLUGIN_CONTINUE;
}

public do_sspoison( args[] )
{

	new id = args[0];
	new enemyz = args[1];
	
	if (CVAR_DEBUG_MODE)
	{
		log_amx("[UWC3X] do_sspoison :: ispoisonedss - %d", ispoisonedss[id]);
	}

	if( !is_user_alive( id ) || ispoisonedss[id] == 0 )
		return PLUGIN_CONTINUE;

	if ( iglow[id][0] < 1 )
	{
		new parm[2];
		parm[0] = id;
		set_task( 0.01, "ChangeGlow", TASK_CHANGE_GLOW2, parm, 2 );
	}

	iglow[id][0] += 45;
	iglow[id][1] = 0;
	iglow[id][2] = 0;
	iglow[id][3] = 0;

	if ( iglow[id][0] > MAXGLOW )
		iglow[id][0] = MAXGLOW;

	if( Util_Should_Msg_Client( id ) )
	{
		message_begin( MSG_ONE, gmsgFade, { 0, 0, 0 }, id );
		write_short( 1<<10 ); // fade lasts this long duration
		write_short( 1<<10 ); // fade lasts this long hold time
		write_short( 1<<12 ); // fade type ( in / out )
		write_byte( 0 ); // fade red
		write_byte( 255 ); // fade green
		write_byte( 0 ); // fade blue
		write_byte( iglow[id][0] ); // fade alpha
		message_end( );
	}

	do_damage( id, enemyz, 5, 18, 2, 0, 0, 0 );

	return PLUGIN_CONTINUE;
}

public burn_victim_napalm( id, killer, tk )
{

	if( isnburning[id] == 1 )
		return PLUGIN_CONTINUE;

	if ( playeritem[id] == IMMUNITY || hasblink[id] )
		return PLUGIN_CONTINUE;

	new hp, args[4];
	hp = get_user_health( id );

	if( hp > 250 )
		hp = 250;

	// [08-06-04] - Added Fire Resistance Checks - K2mia
	new Float:ftimer = 2.0;
	new bool:do_burn = true;

	if ( USE_ENH && p_resists[id][RESISTIDX_FIRE] )
	{
		new Float:chance_to_avoid = ( p_resists[id][RESISTIDX_FIRE] >= RESIST_MAX_VALUE ) ?
		1.00 : ( float( p_resists[id][RESISTIDX_FIRE] ) / float( RESIST_MAX_VALUE ) );

		new Float:randomnumber = random_float( 0.0, 1.0 );

		//client_print( id, print_console, "DEBUG: fresist=( %d ) chance_to_avoid=( %f ) rnum=( %f )", p_resists[id][RESISTIDX_FIRE], chance_to_avoid, randomnumber );
		if ( randomnumber < chance_to_avoid )
		{
			do_burn = false;

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "[%s] Your fire resistance protects you from a napalm grenade attack", MOD );
			}

			if( is_user_connected( killer ) && !is_user_bot( killer ) )
			{
				client_print( killer, print_chat, "[%s] Your napalm grenade attack is deflected by your target's fire resistance", MOD );
			}

		}
		else if ( ( randomnumber/2.0 ) < chance_to_avoid )
		{
			ftimer = 4.0;

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "[%s] Your fire resistance fails to fully protect you from a napalm grenade attack", MOD );
			}

		}
	}

	if ( do_burn )
	{
		args[0] = id;
		args[1] = killer;
		args[2] = tk;
		
		isnburning[id] = 1;
		SetTaskUnique(ftimer, "on_fire_napalm", TASK_ON_FIRE_NAPALM + id, args, 4, "b");
	}
	else
	{
		isnburning[id] = 0;
	}

	return PLUGIN_CONTINUE;
}

public damage_ent ( vid,id )
{

	if(is_user_alive(id) && is_user_alive(vid))
	{
		new Float:vorigin[3],Float:aorigin[3];
		entity_get_vector(vid,EV_VEC_origin,vorigin);
		entity_get_vector(id,EV_VEC_origin,aorigin);

		new i;
		new jk_knockack = p_jumpkick_push[p_skills[id][SKILLIDX_JUMPKICK]-1];

		//If dexterity is 18 then they get a knock back bonus
		if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_DEX] >= DEX_JUMPKICK_LEVEL ) )
		{
			jk_knockack += DEX_JUMPKICK_KNOCKBACK_BONUS;
		}

		for(i = 0;i <= 2;i++)
		{
			vorigin[i] -= aorigin[i];
			vorigin[i] *= ( jk_knockack * 2);
		}

		new jk_damage = p_jumpkick_damage[p_skills[id][SKILLIDX_JUMPKICK]-1];

		// YOU JUMPKICKED THEM TO DEATH!!!!
		if(get_user_health(vid) < jk_damage )
		{
			Event_Jumpkick_createKill(vid,id,"Jumpkick to the face!");

			new name[32],aname[32];
			get_user_name ( vid, name, 31 );
			get_user_name ( id, aname, 31 );

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "JUMPKICK2", name );
			}

			if( is_user_connected( vid ) && !is_user_bot( vid ) )
			{
				client_print( vid, print_center, "%L", vid, "JUMPKICK1", aname );
			}

			//Since they are dead
			return PLUGIN_CONTINUE;
		}
		else
		{
			fakedamage(vid,"Jumpkick", float(jk_damage) , DMG_CRUSH );

			new clip,ammo,weap;
			weap = get_user_weapon(vid,clip,ammo);

			if ( IsWeaponPrimary( weap ) )
			{
				if( !JumpkickResisted( vid, id ) )
				{

					if( Util_Should_Msg_Client( vid ) )
					{
						if( !BlockPickup[id] )
						{
							client_cmd( vid, "drop" );
							client_print( vid, print_center, "%L", vid, "JUMPKICK_NO_RESIST" );
						}
						else
						{
							//client_cmd( vid, "drop" );
							client_print( vid, print_center, "%L", vid, "JUMPKICK_NO_RESIST_DEPOWER" );
						}

						if ( file_exists( "sound/uwc3x/ninja.wav" ) == 1 )
						{
							emit_sound( vid, CHAN_STATIC, "uwc3x/ninja.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
						}
					}


				}//end resistance check
			}
			//end weapon check
		}

		//They are still alive after the weapon drop and damage, knock them backwards
		entity_set_vector(vid,EV_VEC_velocity,vorigin);

	}

	return PLUGIN_CONTINUE;

}

public WisdomCanResist( id )
{
	if( !Util_Is_Valid_Player( id ) || !Util_IsValid_Team( id ) || !USE_ENH )
		return false;

	return true;
}

public GrabResisted( id, enemy )
{
	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
	{
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug :: GrabResisted -> WisdomCanResist was false for one of two users, return true" );
			client_print( enemy, print_console, "DEBUG :: GrabResisted -> WisdomCanResist was false for one of two users, return true");
		}
		return true;
	}

	if ( CVAR_DEBUG_MODE )
	{
		new name1[32], name2[32];
		get_user_name ( enemy, name2, 31 );
		get_user_name ( id, name1, 31 );
		log_amx( "[UWC3X] Debug :: GrabResisted -> id:%s enemy:%s skill_points=%d", name1, name2, p_skills[enemy][SKILLIDX_GRAB] );
		client_print( enemy, print_console, "DEBUG :: GrabResisted -> id:%s enemy:%s skill_points=%d", name1, name2, p_skills[enemy][SKILLIDX_GRAB] );
	}

	//enemy has no skill points, so they should resist just fine :)
	if( !p_skills[enemy][SKILLIDX_GRAB])
	{
		if ( CVAR_DEBUG_MODE )
		{
			client_print( enemy, print_console, "DEBUG :: GrabResisted -> no skill points, return true");
			log_amx( "[UWC3X] Debug :: GrabResisted -> no skill points, return true" );
		}
		return true;
	}
	new Float:grabchance_base = p_grabchance[p_skills[enemy][SKILLIDX_GRAB]-1];

	if ( CVAR_DEBUG_MODE )
	{
		new name1[32], name2[32];
		get_user_name ( enemy, name2, 31 );
		get_user_name ( id, name1, 31 );
		client_print( enemy, print_console, "DEBUG :: GrabResisted 1 -> id:%s enemy:%s grabchance_base=%f", name1, name2, grabchance_base );
		log_amx( "[UWC3X] Debug :: GrabResisted 1 -> id:%s enemy:%s grabchance_base=%f", name1, name2, grabchance_base );
	}

	//If agility is 18 then they subtract the bonus - if there is one - from the attackers chance
	if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_AGI] > ATTRIB_BASE ) )
	{
		// takes double the difference above the base value and converts to a percentage, subtracts from the previous base
		new Float:agiBonus = float( ( p_attribs[id][ATTRIBIDX_AGI] - ATTRIB_BASE ) * 2) / 100;
		grabchance_base -= agiBonus;
	}

	new Float:randomnumber = random_float( 0.0, 1.0 );

	if ( CVAR_DEBUG_MODE )
	{
		new name1[32], name2[32];
		get_user_name ( enemy, name2, 31 );
		get_user_name ( id, name1, 31 );
		client_print( enemy, print_console, "DEBUG :: GrabResisted 2 -> id:%s enemy:%s grabchance_base=%f randomnumber=%f", name1, name2, grabchance_base, randomnumber );
		log_amx( "[UWC3X] Debug :: GrabResisted 2 -> id:%s enemy:%s grabchance_base=%f randomnumber=%f", name1, name2, grabchance_base, randomnumber );
	}

	if ( randomnumber >= grabchance_base )
	{
		if( Util_Should_Msg_Client(id) )
		{
			new name[32];
			get_user_name ( enemy, name, 31 );
			client_print( id, print_center, "%L", id, "GRAB_RESIST1", name );
			client_print( id, print_chat, "%L", id, "GRAB_RESIST1", name );
		}

		if( Util_Should_Msg_Client(enemy) )
		{
			client_print( enemy, print_chat, "%L", enemy, "GRAB_RESIST2" );
		}

		if ( CVAR_DEBUG_MODE )
		{
			new name1[32], name2[32];
			get_user_name ( enemy, name2, 31 );
			get_user_name ( id, name1, 31 );
			client_print( enemy, print_console, "DEBUG :: GrabResisted 3 -> player %s evades grab by enemy:%s", name1, name2 );
			log_amx( "[UWC3X] Debug :: GrabResisted 3 -> player %s evades grab by enemy:%s", name1, name2  );
		}

		return true;
	}
	else
	{
		//they didnt resist
		if ( CVAR_DEBUG_MODE )
		{
			new name1[32], name2[32];
			get_user_name ( enemy, name2, 31 );
			get_user_name ( id, name1, 31 );
			client_print( enemy, print_console, "DEBUG :: GrabResisted 4 -> player %s failed to evade grab by enemy:%s", name1, name2 );
			log_amx( "[UWC3X] Debug :: GrabResisted 4 -> player %s failed to evade grab by enemy:%s", name1, name2  );
		}

		return false;
	}

	if ( CVAR_DEBUG_MODE )
	{
		new name1[32], name2[32];
		get_user_name ( enemy, name2, 31 );
		get_user_name ( id, name1, 31 );
		client_print( enemy, print_console, "DEBUG :: GrabResisted 5 -> hitting default false... thats bad..." );
		log_amx( "[UWC3X] Debug :: GrabResisted 5 -> hitting default false... thats bad..."  );
	}

	//Need to set a default value in case something bad happens - but we shouldnt get here anyways
	return false;

}

public JumpkickResisted( id, enemy )
{
	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
		return false;

	//player has no skill points, so they should resist just fine :)
	if( !p_skills[enemy][SKILLIDX_JUMPKICK])
		return true;

	new Float:Chance = 0.22 * p_skills[enemy][SKILLIDX_JUMPKICK];

	if( p_wisdom_jumpkickresist[id] )
	{
		Chance -= 0.15;
	}

	new Float:randomnumber = random_float( 0.0, 1.0 );

	if ( randomnumber >= Chance )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "WISDOM_JUMPKICK_RESIST1" );
			client_print( id, print_chat, "%L", id, "WISDOM_JUMPKICK_RESIST1" );
		}

		if( Util_Should_Msg_Client(enemy) )
		{
			client_print( enemy, print_chat, "%L", enemy, "WISDOM_JUMPKICK_RESIST2" );
		}

		return true;
	}
	else
	{
		//random number was under 0.67 so they didnt resist
		return false;
	}

	return false;

}
public ImpaleResisted( id, enemy )
{
	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
		return false;

	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	if( p_wisdom_impaleresist[id] )
	{
		new Float:Chance = 0.67;
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber >= Chance )
		{
			//random number was greater then 0.67, so they resisted

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "WISDOM_IMPALE_RESIST1" );
				client_print( id, print_chat, "%L", id, "WISDOM_IMPALE_RESIST1" );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "WISDOM_IMPALE_RESIST2" );
			}

			return true;
		}
		else
		{
			//random number was under 0.67 so they didnt resist
			return false;
		}

	}
	else
	{
		return false;
	}

	return false;

}
public BanishResisted( id, enemy )
{
	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
		return false;

	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	if( p_wisdom_banishresist[id] )
	{
		new Float:Chance = 0.67;
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber >= Chance )
		{
			//random number was greater then 0.67, so they resisted
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "WISDOM_BANISH_RESIST1" );
				client_print( id, print_chat, "%L", id, "WISDOM_BANISH_RESIST1" );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "WISDOM_BANISH_RESIST2" );
			}

			return true;
		}
		else
		{
			//random number was under 0.67 so they didnt resist
			return false;
		}

	}
	else
	{
		return false;
	}

	return false;

}
public BashResisted( id, enemy )
{
	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
		return false;

	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	if( p_wisdom_bashresist[id] )
	{
		new Float:Chance = 0.67;
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber >= Chance )
		{
			//random number was greater then 0.67, so they resisted
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "WISDOM_BASH_RESIST1" );
				client_print( id, print_chat, "%L", id, "WISDOM_BASH_RESIST1" );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "WISDOM_BASH_RESIST2" );
			}

			return true;
		}
		else
		{
			//random number was under 0.67 so they didnt resist
			return false;
		}
	}
	else
	{
		return false;
	}

	return false;

}
public HexResisted( id, enemy )
{
	//if they are not using enhancements on this server,
	//or not connected, are spectators, etc
	if( !WisdomCanResist( id ) || !WisdomCanResist( enemy ) )
		return false;

	//id is the player doing the RESISTING
	//enemy is the guy ATTACKING

	if( p_wisdom_hexresist[id] )
	{
		new Float:Chance = 0.80;
		new Float:randomnumber = random_float( 0.0, 1.0 );

		if ( randomnumber >= Chance )
		{
			//random number was greater then 0.67, so they resisted
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "WISDOM_HEX_RESIST1" );
				client_print( id, print_chat, "%L", id, "WISDOM_HEX_RESIST1" );
			}

			if( Util_Should_Msg_Client(enemy) )
			{
				client_print( enemy, print_chat, "%L", enemy, "WISDOM_HEX_RESIST2" );
			}

			return true;
		}
		else
		{
			//random number was under 0.67 so they didnt resist
			return false;
		}
	}
	else
	{
		return false;
	}

	return false;

}

//LEGACY - keeping arround just in case
//deal_grenade_damage( attacked, attacker, Float:damage )
//{
//	// do_damage ( enemy, id, actual_damage, 26, 3, 0, 0, 0 );
//
//
//	//DeathMsg 85 -1 BYTE : killer index BYTE : victim index STRING : weapon
//	if ( get_user_health( attacked ) - floatround( damage ) <= 0 )
//	{
//		//Stops the default death message from being displayed
//		catchdeath = true
//		user_kill( attacked )
//
//		//Displays who killed who
//		message_begin( 2, 83 )
//		write_byte( attacker )
//		write_byte( attacked )
//		write_byte( 0 ) //No idea what this does
//		write_string( "grenade" )
//		message_end()
//
//		//Adds a frag to the killer
//		set_user_frags( attacker, get_user_frags( attacker ) + 1 )
//	}
//	else
//		set_user_health( attacked, get_user_health( attacked ) - floatround( damage ) )
//}