
public Initialize_Enhancements ( )
{
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] Debug:: Initialize_Enhancements() : CVAR_ENABLE_ENHANCEMENTS=%d", CVAR_ENABLE_ENHANCEMENTS );
	}

	// If attribute enhancements allowed but no min. level set use default
	if ( CVAR_ENABLE_ENHANCEMENTS == 1 )
	{
		USE_ENH = 1;
		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug:: CVAR_ENHANCEMENT_MIN_LEVEL=%d", CVAR_ENHANCEMENT_MIN_LEVEL );
		}

		if ( CVAR_ENHANCEMENT_MIN_LEVEL )
		{
			enh_minlevel = CVAR_ENHANCEMENT_MIN_LEVEL;
		}
		else
		{
			enh_minlevel = ENH_MIN_LEVEL;
		}

		log_amx( "[UWC3X] Enhancements ON with minimum level set to [%d]", enh_minlevel );

		if ( CVAR_RESIST_MAX_TRAINABLE )
		{
			RESIST_MAX_VALUE = CVAR_RESIST_MAX_TRAINABLE;
			log_amx( "[UWC3X] Override Detected : Max Resist Value [%d]", RESIST_MAX_VALUE );
		}

		if ( CVAR_ATTRIBS_MAX_POINTS )
		{
			ATTRIB_MAX_PTS = CVAR_ATTRIBS_MAX_POINTS;
			log_amx( "[UWC3X] Override Detected : Max Attrib Pts [%d]", ATTRIB_MAX_PTS );
		}

		if ( CVAR_RESIST_MAX_POINTS )
		{
			RESIST_MAX_PTS = CVAR_RESIST_MAX_POINTS;
			log_amx( "[UWC3X] Override Detected : Max Resist Pts [%d]", RESIST_MAX_PTS );
		}
	}
	else
	{
		log_amx( "[UWC3X] Enhancements are DISABLED" );
		USE_ENH = 0;
	}

	log_amx( "[UWC3X] Enhancements Initialized [OK]");

}

//Set wisdom bonuses
public Set_Wisdom_Bonuses( id )
{
	if( is_user_bot(id) || !is_user_connected(id) )
	{
		return PLUGIN_HANDLED;
	}

	//Set the base values
	p_maxultimates[id] = MAX_ULTIMATES;
	p_wisdom_lightningdamagebonus[id] = 0;
	p_wisdom_firedamagebonus[id] = 0;
	p_wisdom_banishresist[id] = 0;
	p_wisdom_bashresist[id] = 0;
	p_wisdom_jumpkickresist[id] = 0;
	p_wisdom_impaleresist[id] = 0;
	p_wisdom_hexresist[id] = 0;

	//If its 10 or less, then bail out
	if( p_attribs[id][ATTRIBIDX_WIS] <= 10 )
	{
		return PLUGIN_CONTINUE;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 18 )
	{
		p_maxultimates[id] = MAX_ULTIMATES + WIS_ULTIMATEBONUS;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 17 )
	{
		p_wisdom_bashresist[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 16 )
	{
		p_wisdom_banishresist[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 15 )
	{
		p_wisdom_jumpkickresist[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 14 )
	{
		p_wisdom_lightningdamagebonus[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 13 )
	{
		p_wisdom_firedamagebonus[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 12 )
	{
		p_wisdom_impaleresist[id] = 1;
	}

	if( p_attribs[id][ATTRIBIDX_WIS] >= 11 )
	{
		p_wisdom_hexresist[id] = 1;
	}

	return PLUGIN_CONTINUE;
}

//select_attrib
public Select_Attrib ( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( !USE_ENH )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "ENH_OFF" );
		}
	
		return PLUGIN_HANDLED;
	}

	if ( p_level[id] < enh_minlevel )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "ENH_MIN_LEVEL", MOD, enh_minlevel );
		}
		return PLUGIN_HANDLED;
	}

	// Calculate how many attrib points can be spent
	new apts = get_availattribpts( id );
	new pos = 0, i, menu_body[512], menu_items[MAX_ATTRIBS][32];

	format(menu_items[0], 31, "Strength   [ %d/%d ]", p_attribs[id][ATTRIBIDX_STR], ATTRIB_MAX_VALUE);
	format(menu_items[1], 31, "Intellect  [ %d/%d ]", p_attribs[id][ATTRIBIDX_INT], ATTRIB_MAX_VALUE);
	format(menu_items[2], 31, "Dexterity  [ %d/%d ]", p_attribs[id][ATTRIBIDX_DEX], ATTRIB_MAX_VALUE);
	format(menu_items[3], 31, "Agility   [ %d/%d ]", p_attribs[id][ATTRIBIDX_AGI], ATTRIB_MAX_VALUE);
	format(menu_items[4], 31, "Constitution [ %d/%d ]", p_attribs[id][ATTRIBIDX_CON], ATTRIB_MAX_VALUE);
	format(menu_items[5], 31, "Wisdom [ %d/%d ]", p_attribs[id][ATTRIBIDX_WIS], ATTRIB_MAX_VALUE);

	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<8)|(1<<9);

	pos += format(menu_body[pos], 511, 	"\ySelect an Attribute to enhance [%d pts remaining]: \w^n", apts );
	pos += format(menu_body[pos], 511, "\y(say /attribinfo for info about attributes) \w^n^n" );

	for (i = 0; i< (MAX_ATTRIBS-1); i++)
	{
		pos += format(menu_body[pos], 511-pos, "\w%d. %s^n",i+1,menu_items[i]);
	}
	pos += format(menu_body[pos], 511-pos, "^n^n\w9. Resistances Menu");
	pos += format(menu_body[pos], 511-pos, "^n\w0. Exit");

	show_menu( id, keys, menu_body, -1 );
	return PLUGIN_CONTINUE;
}
//do_attribmenu
public Attrib_Menu( id, key )
{

	new name[32];
	get_user_name( id, name, 31 );

	if ( key == 8 )
	{
		Select_Resist( id );
		return PLUGIN_CONTINUE;
	}

	if ( ( key >= 0 ) && ( key <= 7 ) )
	{
		if ( p_attribs[id][key+1] >= ATTRIB_MAX_VALUE )
		{
			// Player has trained the maximum for this attribute
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "ENH_MAX_LEVEL", MOD );
			}
		
			return PLUGIN_HANDLED;
		}

		new extra_xp = ( playerxp[id] - xplevel_lev[enh_minlevel] );
		if ( extra_xp < 0 )
			extra_xp = 0;

		new exp = ( extra_xp / 10 );

		// Calculate how many attrib points can be spent
		new acount = get_attribcount( id );
		new apts = get_availattribpts( id );

		if (apts <= 0)
		{
			if (acount < ATTRIB_MAX_PTS)
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "ENH_NO_POINTS", MOD );
				}
			
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "ENH_LIMIT_REACHED", MOD );
				}
			}

			return PLUGIN_HANDLED;
		}

		// An enhancement pt was spent
		p_attribs[id][key+1] += 1;
		new aname[32];

		if ( (key+1) == ATTRIBIDX_STR )
		{
			copy(aname, 31, "Strength");
		}
		else if ( (key+1) == ATTRIBIDX_INT )
		{
			copy(aname, 31, "Intellect");
		}
		else if ( (key+1) == ATTRIBIDX_DEX )
		{
			copy(aname, 31, "Dexterity");
		}
		else if ( (key+1) == ATTRIBIDX_AGI )
		{
			copy(aname, 31, "Agility");
		}
		else if ( (key+1) == ATTRIBIDX_CON )
		{
			copy(aname, 31, "Constitution");
		}
		else if ( (key+1) == ATTRIBIDX_WIS )
		{
			copy(aname, 31, "Wisdom");
		}
		
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "ENH_SPEND", MOD, aname );
		}

		// Determine if there are additional E-XP pts to spend
		apts = ( exp / attrib_pt_cost ) - ( acount + 1 );

		// See what adjustments are needed for new skill
		if ( (key+1) == ATTRIBIDX_STR )
		{
			Event_SetMaxHealth( id, false ) ;
		}
		else if ( ( key + 1 ) == ATTRIBIDX_CON )
		{
			Task_Check_Const_Regen( id );
		}
		else if ( ( key + 1 ) == ATTRIBIDX_AGI )
		{
			new parm[1];
			parm[0] = id;
			Set_Speed( parm );
		}
		else if( ( key + 1) == ATTRIBIDX_WIS )
		{
			Set_Wisdom_Bonuses( id );
		}

		if (apts > 0)
		{
			Select_Attrib( id );
		}
	}

	return PLUGIN_HANDLED;
}
//select_resist
public Select_Resist ( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	if (!USE_ENH)
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "ENH_OFF" );
		}
	
		return PLUGIN_HANDLED;
	}

	if ( p_level[id] < enh_minlevel )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "ENH_MIN_LEVEL", MOD, enh_minlevel );
		}
	
		return PLUGIN_HANDLED;
	}

	// Calculate how many attrib/resist points can be spent
	new rpts = get_availresistpts( id );
	new pos = 0, i, menu_body[1024], menu_items[7][64];

	format(menu_items[0], 63, "Poison Resistance   [ %d/%d ]", p_resists[id][RESISTIDX_POISON], RESIST_MAX_VALUE);
	format(menu_items[1], 63, "Disease Resistance   [ %d/%d ]", p_resists[id][RESISTIDX_DISEASE], RESIST_MAX_VALUE);
	format(menu_items[2], 63, "Electricity Resistance [ %d/%d ]", p_resists[id][RESISTIDX_ELECTRIC], RESIST_MAX_VALUE);
	format(menu_items[3], 63, "Fire Resistance    [ %d/%d ]", p_resists[id][RESISTIDX_FIRE], RESIST_MAX_VALUE);
	format(menu_items[4], 63, "Magic Resistance    [ %d/%d ]", p_resists[id][RESISTIDX_MAGIC], RESIST_MAX_VALUE);
	format(menu_items[5], 63, "Rot Resistance    [ %d/%d ]", p_resists[id][RESISTIDX_ROT], RESIST_MAX_VALUE);
	format(menu_items[6], 63, "Ice Resistance    [ %d/%d ]", p_resists[id][RESISTIDX_ICE], RESIST_MAX_VALUE);

	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<8)|(1<<9);

	pos += format(menu_body[pos], 1023, "\ySelect a Resistance to enhance [%d pts remaining]: \w^n", rpts );
	pos += format(menu_body[pos], 1023, "\y(say /resistinfo for info about resistances) \w^n^n" );

	for (i = 0; i< (MAX_RESISTS-1); i++)
	{
		pos += format(menu_body[pos], 1023-pos, "\w%d. %s^n",i+1,menu_items[i]);
	}
	pos += format(menu_body[pos], 1023-pos, "^n^n\w9. Attributes Menu");
	pos += format(menu_body[pos], 1023-pos, "^n\w0. Exit");

	show_menu( id, keys, menu_body, -1 );
	return PLUGIN_HANDLED;
}
//do_resistmenu
public Resist_Menu ( id, key )
{
	new name[32];
	get_user_name( id, name, 31 );

	if ( key == 8 )
	{
		Select_Attrib( id );
		return PLUGIN_CONTINUE;
	}

	if ( (key >= 0) && (key <= 7) )
	{
		if ( p_resists[id][key+1] >= RESIST_MAX_VALUE )
		{
			// Player has trained the maximum for this resist
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_chat, "%L", id, "RESIST_MAX", MOD );
			}
			
			return PLUGIN_HANDLED;
		}

		new extra_xp = ( playerxp[id] - xplevel_lev[enh_minlevel] );
		if ( extra_xp < 0 )
		{
			extra_xp = 0;
		}

		new exp = ( extra_xp / 10 );

		// Calculate how many resist points can be spent
		new rcount = get_resistcount( id );
		new rpts = get_availresistpts( id );

		if (rpts <= 0 )
		{
			if ( rcount < RESIST_MAX_PTS )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "RESIST_NONE", MOD );
				}
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print( id, print_chat, "%L", id, "RESIST_MAX_POINTS", MOD );
				}
			}

			return PLUGIN_HANDLED;
		}

		// An enhancement pt was spent
		p_resists[id][key+1] += 1;
		new rname[32];
		if ( ( key + 1 ) == RESISTIDX_POISON )
		{
			copy(rname, 31, "Poison Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_DISEASE )
		{
			copy(rname, 31, "Disease Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_ELECTRIC )
		{
			copy(rname, 31, "Electricity Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_FIRE )
		{
			copy(rname, 31, "Fire Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_MAGIC )
		{
			copy( rname, 31, "Magic Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_ROT )
		{
			copy( rname, 31, "Rot Resistance");
		}
		else if ( ( key + 1 ) == RESISTIDX_ICE )
		{
			copy( rname, 31, "Ice Resistance");
		}
		
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_chat, "%L", id, "RESIST_SPEND", MOD, rname );
		}

		// Determine if there are additional E-XP pts to spend
		rpts = ( exp / resist_pt_cost ) - ( rcount + 1 );

		if ( rpts > 0 )
		{
			Select_Resist( id );
		}
	}

	return PLUGIN_HANDLED;
}

public get_attribcount( id )
{

	new acount = 0;

	for ( new j = 1; j < MAX_ATTRIBS; j++ )
	{
		acount += ( p_attribs[id][j] - ATTRIB_BASE );
	}

	return acount;
}

public get_resistcount( id )
{

	new rcount = 0;
	for ( new j = 1; j < MAX_RESISTS; j++ )
	{
		rcount += p_resists[id][j];
	}

	return rcount;
}

public get_availattribpts( id )
{

	// [11-01-04] To prevent divide by 0 errors - K2mia
	if ( attrib_pt_cost <= 0 )
	{
		return 0;
	}

	// Calculate how many attrib/resist points can be spent
	new extra_xp = ( playerxp[id] - xplevel_lev[enh_minlevel] );
	if ( extra_xp < 0 )
	{
		extra_xp = 0;
	}

	new exp = ( extra_xp / 10 );
	new acount = get_attribcount( id );
	new apts = ( ( exp / attrib_pt_cost ) > ATTRIB_MAX_PTS ) ? ( ATTRIB_MAX_PTS - acount ) :
	( ( exp / attrib_pt_cost ) - acount );

	// Prevent players from getting attrib points beyond their max allowed
	if ( ( acount >= ( ( MAX_ATTRIBS - 1 ) * ( ATTRIB_MAX_VALUE - ATTRIB_BASE ) ) ) || ( acount >= ATTRIB_MAX_PTS ) )
	{
		apts = 0;
	}

	if (apts > ( ( MAX_ATTRIBS - 1 ) * ( ATTRIB_MAX_VALUE - ATTRIB_BASE ) ) )
	{
		apts = ( ( MAX_ATTRIBS - 1 ) * ( ATTRIB_MAX_VALUE - ATTRIB_BASE ) ) - acount;
	}

	return apts;
}

public get_availresistpts( id )
{

	// [11-01-04] To prevent divide by 0 errors - K2mia
	if ( resist_pt_cost <= 0 )
	{
		return 0;
	}

	// Calculate how many attrib/resist points can be spent
	new extra_xp = ( playerxp[id] - xplevel_lev[enh_minlevel] );
	if (extra_xp < 0)
	{
		extra_xp = 0;
	}

	new exp = (extra_xp / 10);
	new rcount = get_resistcount(id);
	new rpts = ( ( exp / resist_pt_cost ) > RESIST_MAX_PTS ) ? ( RESIST_MAX_PTS - rcount ) :
	( ( exp / resist_pt_cost ) - rcount );

	// Prevent players from getting resist points beyond their max allowed
	if ( ( rcount >= ( ( MAX_RESISTS - 1 ) * RESIST_MAX_VALUE ) ) || ( rcount >= RESIST_MAX_PTS ) )
	{
		rpts = 0;
	}

	if ( rpts > ( ( MAX_RESISTS - 1 ) * RESIST_MAX_VALUE ) )
	{
		rpts = ( ( MAX_RESISTS - 1 ) * RESIST_MAX_VALUE ) - rcount;
	}

	return rpts;
}

//resetattribs(id)
public Reset_Attribs ( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	if ( CVAR_RESET_SKILLS )
	{
		
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "RESET_ATTRIB");
		}
	
		resetattrib[id] = true;
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "RESETATTRIBS_OFF");
		}
		resetattrib[id] = false;
	}

	return PLUGIN_HANDLED;
}

//resetresists(id)
public Reset_Resists ( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( CVAR_RESET_SKILLS )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "RESET_RESIST");
		}
		resetresist[id] = true;
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "RESETRESISTS_OFF");
		}
		resetresist[id] = false;
	}

	return PLUGIN_HANDLED;
}

public magic_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_MAGIC] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_MAGIC] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
	}

	return 0;
}

public ice_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_ICE] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_ICE] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
	}

	return 0;
}
public rot_saving_throw( id )
{
	if ( USE_ENH && p_resists[id][RESISTIDX_ROT] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_ROT] ) / float( RESIST_MAX_VALUE );
		
		if ( randomnumber <= tosave )
			return 1;
		else
			return 0;
	}

	return 0;
}
public fire_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_FIRE] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_FIRE] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
		else
			return 0;
	}

	return 0;
}
public poison_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_POISON] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_POISON] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
		else
			return 0;
	}

	return 0;
}
public disease_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_DISEASE] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_DISEASE] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
		else
			return 0;
	}

	return 0;
}
public electricity_saving_throw( id )
{

	if ( USE_ENH && p_resists[id][RESISTIDX_ELECTRIC] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:tosave = float( p_resists[id][RESISTIDX_ELECTRIC] ) / float( RESIST_MAX_VALUE );

		if ( randomnumber <= tosave )
			return 1;
		else
			return 0;
	}

	return 0;
}






public Bot_Pick_Attribs( id )
{
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: Bot_Pick_Attribs -> Bot is picking Attributes" );
	}

	//new acount = get_attribcount( id );
	new apts = get_availattribpts( id );
	new attrib_max = MAX_ATTRIBS-1;

	while( apts > 0 )
	{
		new attrib_num = random_num( 1, attrib_max);
		
		if( p_attribs[id][attrib_num] == ATTRIB_MAX_VALUE )
			continue;
		
		p_attribs[id][attrib_num] += 1;
		apts--;

		//if ( CVAR_DEBUG_MODE )
		//{
		//	log_amx( "[UWC3X] DEBUG :: Bot_Pick_Attribs -> attrib_num=%d, apts=%d", attrib_num, apts);
		//}

		switch( attrib_num )
		{
			case ATTRIBIDX_STR: Event_SetMaxHealth( id, false ) ;
			case ATTRIBIDX_CON: Task_Check_Const_Regen( id );
			case ATTRIBIDX_AGI: 
				{
					// Call routine to set user runspeed
					new parm[1];
					parm[0] = id;
					Set_Speed( parm );
				}
			case ATTRIBIDX_WIS: Set_Wisdom_Bonuses( id );
		}
	}

	return PLUGIN_CONTINUE;
}
public Bot_Pick_Resists( id )
{
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: Bot_Pick_Resists -> Bot is picking Resistances" );
	}

	//new acount = get_resistcount( id );
	new rpts = get_availresistpts( id );
	new res_max = MAX_RESISTS-1;
	
	while( rpts > 0 )
	{
		new res_num = random_num( 1, res_max);
		
		if( p_resists[id][res_num] == RESIST_MAX_VALUE )
			continue;
			
		p_resists[id][res_num] += 1;
		rpts--;
	}

	return PLUGIN_CONTINUE;
}
