
public Initialize_Mole_Custom_Price ( )
{
	if ( CVAR_ENABLE_MOLE ) 
	{
		if ( CVAR_SM2_PRICE_MOLE )
		{
			itemcost2[MOLE-1] = CVAR_SM2_PRICE_MOLE;
		}
	} 
}

public Amx_GiveMole( id, level, cid )
{
	if ( !( get_user_flags( id ) & CVAR_ADMIN_DEFAULT_FLAG ) ) 
	{
		if( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility( id, print_console, "%L", id, "NO_ACCESS");
			}
		
			return PLUGIN_HANDLED;
		}
	}

	new arg[32];
	read_argv( 1,arg,31 );

	if(equali(arg,"@ALL"))
	{
	new players[32], inum;
	get_players(players,inum);

	for( new a = 0; a < inum; ++a )
	{
		playeritem2[players[a]] = MOLE;
		hasmole[players[a]] = true;
		displaylevel( id, 0 );
	}

	return PLUGIN_HANDLED;

	}
	else if ( arg[0] == '@' )
	{
		new players[32], inum;
		get_players( players, inum, "e", arg[1] );

		if ( inum == 0 )
		{
			console_print( id, "%L", id, "NO_MATCHING_CLIENTS" );
			return PLUGIN_HANDLED;
		}

		for( new a = 0; a < inum; ++a )
		{
			playeritem2[players[a]] = MOLE;
			hasmole[players[a]] = true;
			displaylevel( id, 0 );
		}
	}
	else
	{
		new player = cmd_target2( id, arg );
		
		if ( !player ) 
		{
			return PLUGIN_HANDLED;
		}

		playeritem2[player] = MOLE;
		hasmole[player] = true;
		displaylevel( player, 0 );
	}

	return PLUGIN_HANDLED;
}

public mole_T( id )
{
	new numplayers = 0;
	new Float:vicinity = 96.0;
	new Float:origin[3], porigin[3], entsFound[1];
	new szEnt[32] = "info_player_deathmatch";

	new bool:spotOpen = false;
	new teamnumber = get_user_team( id );
	new curEnt = find_ent_by_class( -1, szEnt );

	while ( curEnt > 0 )
	{
		numplayers = 0;

		entity_get_vector( curEnt, EV_VEC_origin, origin );
		numplayers = find_sphere_class( 0, "player", vicinity, entsFound, 1, origin );

		if ( numplayers == 0 )
		{
			spotOpen = true;
			break;
		}

		curEnt = find_ent_by_class( curEnt, szEnt );
	}

	if ( spotOpen )
	{
		porigin[0] = floatround( origin[0] );
		porigin[1] = floatround( origin[1] );
		porigin[2] = floatround( origin[2] );

		new parm2[6];
		parm2[0] = porigin[0];
		parm2[1] = porigin[1];
		parm2[2] = porigin[2];
		parm2[3] = 0;
		parm2[4] = teamnumber;
		parm2[5] = id;
		set_task( 0.1, "Task_Transport2", 2, parm2, 6 );
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility( id, print_chat, "%L", id, "MOLE_NO_SLOT_T" );
		}

	}

	return PLUGIN_HANDLED;
}

public mole_CT( id )
{
	new numplayers = 0;
	new Float:vicinity = 96.0;
	new entsFound[1], Float:origin[3], porigin[3];
	new szEnt[32] = "info_player_start";
	new bool:spotOpen = false;

	new teamnumber = get_user_team( id );
	new curEnt = find_ent_by_class( -1, szEnt );

	while ( curEnt > 0 )
	{
		numplayers = 0;

		entity_get_vector( curEnt, EV_VEC_origin, origin );
		numplayers = find_sphere_class( 0, "player", vicinity, entsFound, 1, origin );

		if (numplayers == 0)
		{
			spotOpen = true;
			break;
		}

		curEnt = find_ent_by_class( curEnt, szEnt );
	}

	if (spotOpen){
		porigin[0] = floatround( origin[0] );
		porigin[1] = floatround( origin[1] );
		porigin[2] = floatround( origin[2] );

		new parm2[6];
		parm2[0] = porigin[0];
		parm2[1] = porigin[1];
		parm2[2] = porigin[2];
		parm2[3] = 0;
		parm2[4] = teamnumber;
		parm2[5] = id;
		set_task( 0.1, "Task_Transport2", 2, parm2, 6 );
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility( id, print_chat, "%L", id, "MOLE_NO_SLOT_CT" );
		}
	}

	return PLUGIN_HANDLED;
}




