
public GetStorageType()
{
	new tempDBTYpe = 1;

	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] Debug:: GetStorageType() : CVAR_SAVE_XP_SQL=%d", CVAR_SAVE_XP_SQL );	
	}

	if ( CVAR_SAVE_XP_SQL == 1 )
	{
		tempDBTYpe = 1;
	}
	else if ( CVAR_SAVE_XP_SQL == 2 )
	{
		tempDBTYpe = 2;
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in GetStorageType - default to MySQL");
	}

	return tempDBTYpe;
}

public LoadXPConfig()
{

	if ( GetStorageType() == 1 )
	{
		log_amx("[UWC3X] Initializing MySQL for storage.");
		SQL_SetAffinity("mysql")
		LoadSQLVars();
		SkillSetsMySQL_Table();
		log_amx( "[UWC3X] XP Config Initialized [OK]");
	}
	else if ( GetStorageType() == 2 )
	{
		log_amx("[UWC3X] Initializing SQLite for storage.");
		SQL_SetAffinity("sqlite")
		LoadSQLLiteConfig();	
		SkillSetsSqlLite_Table();	
		log_amx( "[UWC3X] XP Config Initialized [OK]");
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in LoadXPConfig");
		log_amx( "[UWC3X] XP Config Initialized [FAILED]");
	}
}

public LoadXPCommand( id )
{
	LoadXP ( id );
	return PLUGIN_CONTINUE;
}
public LoadXP ( id )
{
	if ( GetStorageType() == 1 )
	{
		//Load SQL Stuff
		LoadXPMySQL2 ( id );	
	}
	else if ( GetStorageType() == 2 )
	{
		//Load SQL Lite Stuff
		LoadXPSQLLite ( id );	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in LoadXP");
	}

	new speedparm[1];
	speedparm[0] = id;
	Set_Speed( speedparm );

	return PLUGIN_CONTINUE;
}
public LoadSkillSet( id, skillsetIDX )
{
	if ( GetStorageType() == 1 )
	{
		//Load SQL Stuff
		LoadSkillSetMySQL ( id, skillsetIDX );	
	}
	else if ( GetStorageType() == 2 )
	{
		//Load SQL Lite Stuff
		LoadSkillSetSQLLite ( id, skillsetIDX );	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in LoadXP");
	}

	new speedparm[1];
	speedparm[0] = id;
	Set_Speed( speedparm );

	return PLUGIN_CONTINUE;
}

public DeleteSkillSet( id, skillsetIDX )
{
	if ( GetStorageType() == 1 )
	{
		//Load SQL Stuff
		DeleteSkillSetMySQL ( id, skillsetIDX );	
	}
	else if ( GetStorageType() == 2 )
	{
		//Load SQL Lite Stuff
		DeleteSkillSetSQLLite ( id, skillsetIDX );	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in DeleteSkillSet");
	}

	return PLUGIN_CONTINUE;
}

public SaveSkillSet( id, skillsetIDX )
{
	if ( GetStorageType() == 1 )
	{
		//Load SQL Stuff
		SaveSkillSetMySQL ( id, skillsetIDX );	
	}
	else if ( GetStorageType() == 2 )
	{
		//Load SQL Lite Stuff
		SaveSkillSetSQLLite ( id, skillsetIDX );	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in SaveSkillSet");
	}

	return PLUGIN_CONTINUE;
}
public SaveXP ( id )
{

	if ( GetStorageType() == 1 )
	{
		//Load SQL Stuff
		SaveXPMySQL ( id );	
	}
	else if ( GetStorageType() == 2 )
	{
		//Load SQL Lite Stuff
		SaveXPSQLLite ( id );	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in SaveXP");
	}

	return PLUGIN_CONTINUE;
}

public SaveSinglePlayerXP ( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_HANDLED;
	}

	if ( !CVAR_SAVE_XP )
	{
		if( Util_Should_Msg_Client(id) )
		{
			//client_print ( id,print_chat,"%L", id, "SAVE_XP_DISABLED", MOD );
			hudchat_show(id, "%L", id, "SAVE_XP_DISABLED");
			hudchat_update(id);
		}
	
		return PLUGIN_CONTINUE;
	}

	if( Util_Should_Msg_Client(id) )
	{
		//client_print ( id,print_chat, "%L", id, "SAVING_XP_NOW", MOD );
		hudchat_show(id, "%L", id, "SAVING_XP_NOW");
		hudchat_update(id);
	}

	SaveXP( id );	
	return PLUGIN_HANDLED;
}
public ShowSaveText ( id )
{	
	if( Util_Should_Msg_Client(id) )
	{
		//set_hudmessage ( 200, 100, 0, -1.0, 0.35, 0, 1.0, 7.0, 0.1, 0.2, 2 );
		//show_hudmessage ( id, "Your XP, Skills, Attributes and Resistances will be saved when you disconnect, and on a map change." );
		//client_print ( id, print_chat, "[%s] %L", id, MOD, "SAVEXP_CLIENT_MESSAGE" );
		hudchat_show(id, "%L", id, "SAVEXP_CLIENT_MESSAGE");
		hudchat_update(id);
	}

	return PLUGIN_CONTINUE;
}

public SaveAllPlayersXP ( )
{
	
	if ( !uwc3x )
	{
		return PLUGIN_HANDLED;
	}

	if ( !CVAR_SAVE_XP )
	{
		return PLUGIN_CONTINUE;
	}
	
	new players[32], numofplayers;
	
	get_players ( players, numofplayers );
	
	for ( new i=0; i < numofplayers; i++ )
	{
		SaveXP ( players[i] );
	}
	
	return PLUGIN_CONTINUE;
}

public CloseDB ( )
{
	if ( GetStorageType() == 1 )
	{
		//close SQL Stuff
		MySQLClose();	
	}
	else if ( GetStorageType() == 2 )
	{
		//close SQL Lite Stuff
		SQLLiteClose();	
	}
}

public SkillSets_Table()
{
	if ( GetStorageType() == 1 )
	{
		SkillSetsMySQL_Table();
	}
	else if ( GetStorageType() == 2 )
	{
		SkillSetsSqlLite_Table();	
	}
	else
	{
		log_amx( "[UWC3X] ERROR:: Could not determine Storage Type in LoadXPConfig");
		log_amx( "[UWC3X] XP Config Initialized [FAILED]");
	}
}