public IsDBConnected ( )
{
	if( bDBConn )
	{
		return true;
	}
	
	return false;
}

public LoadSQLVars ( )
{
	//Load the Cvars into locally used strings
	log_amx( "[UWC3X] SQL PCVARS :: Config Report: host= ( %s ) user= ( %s ) pass= ( * ) db= ( %s )", CVAR_MYSQL_HOSTNAME, CVAR_MYSQL_USERNAME, CVAR_MYSQL_DATABASE );
	
	//Create handle and then the connection
	g_SqlTuple = SQL_MakeDbTuple ( CVAR_MYSQL_HOSTNAME, CVAR_MYSQL_USERNAME, CVAR_MYSQL_PASSWORD, CVAR_MYSQL_DATABASE );
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );
	
	//Check for an error
	if ( !SqlConnection )
	{
		log_amx( "[UWC3X] Error connecting to SQL database : %s", g_Error );
		bDBConn = false;
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQL :: Connected [OK]" );
		bDBConn = true;
	}
	
	format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s` ( `steamid` VARCHAR ( 32 ) NOT NULL, `xp` INT, `ip` ", CVAR_MYSQL_TABLE );
	format ( squery, 5096, "%s%s", squery, "VARCHAR ( 32 ), `mtime` VARCHAR ( 32 ), `skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill3` SMALLINT DEFAULT '0', `skill4` SMALLINT DEFAULT '0', `skill5` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', `skill7` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', `skill10` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', `skill13` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 5096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` " );
	format ( squery, 5096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill24` SMALLINT DEFAULT '0', `skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT " ) ;
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0' , `skill27` SMALLINT DEFAULT '0', `skill28` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', `skill31` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 5096, "%s%s", squery, "`skill39` SMALLINT DEFAULT '0', `skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill42` SMALLINT DEFAULT '0', `skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill45` SMALLINT DEFAULT '0', `skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill48` SMALLINT DEFAULT '0', `skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill51` SMALLINT DEFAULT '0', `skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill54` SMALLINT DEFAULT '0', `skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill57` SMALLINT DEFAULT '0', `skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill60` SMALLINT DEFAULT '0', `skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`skill63` SMALLINT DEFAULT '0', `skill64` SMALLINT DEFAULT '0', " );
	format ( squery, 5096, "%s%s", squery, "`att1` SMALLINT DEFAULT '0', `att2` SMALLINT DEFAULT '0', `att3` SMALLINT DEFAULT '0', `att4` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `att5` SMALLINT DEFAULT '0', `att6` SMALLINT DEFAULT '0', `res1` SMALLINT DEFAULT '0', `res2` SMALLINT " );
	format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `res3` SMALLINT DEFAULT '0', `res4` SMALLINT DEFAULT '0', `res5` SMALLINT DEFAULT '0', `res6` SMALLINT DEFAULT '0', `res7` SMALLINT " );
	
	//If save by = 2 (by name) primary key is the name
	if( CVAR_SAVE_BY == 2 )
	{
		format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `name` VARCHAR ( 64 ) DEFAULT NULL, PRIMARY KEY ( `name` ) ) ENGINE=MyISAM;" );
	}
	else
	{
		format ( squery, 5096, "%s%s", squery, "DEFAULT '0', `name` VARCHAR ( 64 ) DEFAULT NULL, PRIMARY KEY ( `steamid` ) ) ENGINE=MyISAM;" );
	}
	
	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );
	
	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQL :: Error creating table" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}
	
	return PLUGIN_CONTINUE;
}

public SkillSetsMySQL_Table ( )
{
	if( CVAR_SAVED_SKILLSETS )
	{
		log_amx( "[UWC3X] SQL :: Using Saved Skill Sets [OK]" );
		//Create handle and then the connection
		g_SqlTuple = SQL_MakeDbTuple ( CVAR_MYSQL_HOSTNAME, CVAR_MYSQL_USERNAME, CVAR_MYSQL_PASSWORD, CVAR_MYSQL_DATABASE );
		
		//Try and connect
		SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );
		
		//Check for an error
		if ( !SqlConnection )
		{
			log_amx( "[UWC3X] SQL :: Created Skill Sets Table [FAILED]" );
			log_amx( "[UWC3X] Error connecting to SQL database : %s", g_Error );
			bDBConn = false;
			return PLUGIN_CONTINUE;
		}
		
		log_amx( "[UWC3X] SQL :: Connected [OK]" );
		
		if( CVAR_SAVE_BY == 2 )
		{
			format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s_SkillSets` ( `name` VARCHAR(64), `skillsetid` INTEGER , ", CVAR_MYSQL_TABLE );
		}
		else
		{
			format ( squery, 5096, "CREATE TABLE IF NOT EXISTS `%s_SkillSets` ( `steamid` VARCHAR(32), `skillsetid` INTEGER , ", CVAR_MYSQL_TABLE );
		} 
		
		format ( squery, 5096, "%s%s", squery, "`skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT DEFAULT '0', `skill3` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill4` SMALLINT DEFAULT '0', `skill5` SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill7` SMALLINT DEFAULT '0', `skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill10` SMALLINT DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill13` SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', `skill24` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT DEFAULT '0', `skill27` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill28` SMALLINT DEFAULT '0', `skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill31` SMALLINT DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', `skill39` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', `skill42` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', `skill45` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', `skill48` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', `skill51` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', `skill54` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', `skill57` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', `skill60` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', `skill63` SMALLINT DEFAULT '0', " );
		format ( squery, 5096, "%s%s", squery, "`skill64` SMALLINT DEFAULT '0' ) ENGINE=MyISAM;" );
		
		//Set the Query
		Query = SQL_PrepareQuery ( SqlConnection, squery );
		
		// run the query
		if ( !Query || !SQL_Execute ( Query ) )
		{
			// if there were any problems
			SQL_QueryError ( Query, g_Error, 511 );
			log_amx( "[UWC3X] SQL :: Error creating table" );
			log_amx( "[UWC3X] Error:: %s", g_Error );
			log_amx( "[UWC3X] Query:: %s", squery );
		}
		else
		{
			//Free the stuff
			SQL_FreeHandle ( Query );
			SQL_FreeHandle ( SqlConnection );
		}
		
		log_amx( "[UWC3X] SQL :: Created Skill Sets Table [OK]" );
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQL :: Using Saved Skill Sets [NO]" );
		return PLUGIN_CONTINUE;
	}
	
	return PLUGIN_CONTINUE;
}

public CreateTable ( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	if( FailState )
	{
		new sQuery[4096];
		new sFunction[32];
		copy(sFunction, 31, "CreateTable");
		SQL_GetQueryString( Query, sQuery, 255 );
		LogError( Query, sQuery, Error, Errcode, FailState, sFunction );
	}
	return PLUGIN_CONTINUE;
}

public RunQuerry ( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	if( FailState )
	{
		new sQuery[4096];
		new sFunction[32];
		copy(sFunction, 31, "RunQuerry");
		SQL_GetQueryString( Query, sQuery, 255 );
		LogError( Query, sQuery, Error, Errcode, FailState, sFunction );
	}
	return PLUGIN_CONTINUE;
}

public _LoadXP ( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	new id = player_id;
	new ip[32];
	new xp = 0;
	new pid[32];
	new skills[MAX_SKILLS] = 0;
	new att[MAX_ATTRIBS] = 0;
	new res[MAX_RESISTS] = 0;
	new tempVar[64];
	
	new tempVar44[64], tempVar55[64];
	get_user_name ( id, tempVar44, 63 );
	get_user_authid ( id, tempVar55, 63 );
	
	//if ( CVAR_DEBUG_MODE )
	//{
	log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: Attempting to load XP " );
	//}
	
	// error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in LoadXPHandle.");
		
		if( Util_Should_Msg_Client(id) )
		{
			//client_print(id, print_chat, "%L", id, "LOAD_XP_FAILURE" );
			hudchat_show(id, "%L", id, "LOAD_XP_FAILURE");
			hudchat_update(id);
		}
		log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> :: [END]^n" );
		return PLUGIN_HANDLED;
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in LoadXPHandle");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		
		if( Util_Should_Msg_Client(id) )
		{
			//client_print(id, print_chat, "%L", id, "LOAD_XP_FAILURE" );
			hudchat_show(id, "%L", id, "LOAD_XP_FAILURE");
			hudchat_update(id);
		}
		
		log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> :: [END]^n" );
		return PLUGIN_HANDLED;
	}
	
	if(Errcode)
	{
		log_amx( "[UWC3X] Error:_LoadXP - %d", Errcode);
		log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> :: [END]^n" );
		return PLUGIN_HANDLED;
	}
	
	//if ( CVAR_DEBUG_MODE )
	//{
	get_user_name ( id, tempVar, 63 );
	log_amx( "[UWC3X] Debug :: _LoadXP : No error, attepting to load XP and skills for %s", tempVar );
	//}
	
	//Now that we have no errors, I will reset the xp loading var, this is in case there are
	//errors so that it will continue to retry
	NumResults = SQL_NumResults(Query);
	
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG :: MySQL->_LoadXP: NumResults=%d", NumResults);
	}
	
	if ( !NumResults || NumResults == 0 || is_user_bot( id ) )
	{
		//no data exists
		if( Util_Should_Msg_Client(id) )
		{
			//client_print ( id, print_chat, "%L", id, "LOAD_XP_NO_DATA", MOD );
			hudchat_show(id, "%L", id, "LOAD_XP_NO_DATA");
			hudchat_update(id);
		}
		
		if ( CVAR_DEBUG_MODE && is_user_bot( id ) )
		{
			log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: Player is a bot");
		}
		
		if ( CVAR_ENABLE_STARTING_SYSTEM )
		{
			if( CVAR_STARTING_METHOD == 1 )
			{
				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: No Records, client %s given %d starting XP ", tempVar, CVAR_STARTING_XP);
				}
				
				if( Util_Should_Msg_Client(id) )
				{
					//client_print(id, print_chat, "%L", id, "LOAD_XP_STARTING_XP", MOD, CVAR_STARTING_XP );
					hudchat_show(id, "%L", id, "LOAD_XP_STARTING_XP", CVAR_STARTING_XP);
					hudchat_update(id);
				}
				
				playerxp[id] = CVAR_STARTING_XP;
			}
			else
			{
				
				//Override default level if its a bot and use the bot level cvar
				if( is_user_bot(id) )
				{
					if ( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: Player is BOT - > BOT %s set to level %d", tempVar, CVAR_BOT_LEVEL);
					}
					
					playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
				}
				else
				{
					if ( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: No Records, client %s set to level %d", tempVar, CVAR_STARTING_LEVEL);
					}
					
					if( Util_Should_Msg_Client(id) )
					{
						//client_print(id, print_chat, "%L", id, "LOAD_XP_STARTING_LEVEL", MOD, CVAR_STARTING_LEVEL );
						hudchat_show(id, "%L", id, "LOAD_XP_STARTING_LEVEL", CVAR_STARTING_LEVEL);
						hudchat_update(id);
					}
					
					playerxp[id] = xplevel_lev[CVAR_STARTING_LEVEL];
				}
			}
		}
		
		Set_Ult_Count( id );
		xpreadytoload[id] = 0;
		log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> name %s auth %s :: [END]^n", tempVar44, tempVar55 );
		return PLUGIN_CONTINUE;
		
	}
	else
	{
		new sName[64];
		
		//They have data, lets load it
		//Set the PlayerID, XP, IP, and Last time
		SQL_ReadResult ( Query, 0, pid, 31 );
		xp = SQL_ReadResult ( Query, 1 );
		SQL_ReadResult ( Query, 2, ip, 31 );
		SQL_ReadResult ( Query, 3, mtimet, 31 );
		SQL_ReadResult ( Query, 72, sName, 63 );
		
		//Now loading based on field name, and not on position
		new temp[32], sqlField;
		
		//Start setting the skills
		for ( new k = 1; k < (MAX_SKILLS); k++ )
		{
			format( temp, 31, "skill%d", k);
			sqlField = SQL_FieldNameToNum(Query, temp)
			skills[k] = SQL_ReadResult ( Query, sqlField );
		}
		
		//Set the attributes
		for ( new k = 1; k < (MAX_ATTRIBS); k++ )
		{
			format( temp, 31, "att%d", k);
			sqlField = SQL_FieldNameToNum(Query, temp)
			att[k] = SQL_ReadResult ( Query, sqlField );
			
			//If the attrib is less then the base, or greater then max, reset to base
			if( ( ATTRIB_MAX_VALUE < att[k] ) || ( att[k] < ATTRIB_BASE ) )
				att[k] = ATTRIB_BASE;
		}
		
		//Set the resistances
		for ( new k = 1; k < (MAX_RESISTS); k++ )
		{
			format( temp, 31, "res%d", k);
			sqlField = SQL_FieldNameToNum(Query, temp)
			res[k] = SQL_ReadResult ( Query, sqlField );
		}
		
		//If starting XP is enabled, do the check
		if ( CVAR_ENABLE_STARTING_SYSTEM )
		{
			if( CVAR_STARTING_METHOD == 1 )
			{
				//It is enabled and its set to XP based, so check to see if the starting XP is higher then what they have now
				if ( xp < CVAR_STARTING_XP )
				{
					//it must be, so lets set their XP and let them know
					xp = CVAR_STARTING_XP;
					
					if( Util_Should_Msg_Client(id) )
					{
						//client_print ( id, print_chat, "[%s] %L", id, MOD, "STARTING_XP_MESSAGE", CVAR_STARTING_XP );
						hudchat_show(id, "%L", id, "STARTING_XP_MESSAGE", CVAR_STARTING_XP);
						hudchat_update(id);
					}
				}
			}
			else
			{
				//Override default level if its a bot and use the bot level cvar
				if( is_user_bot(id))
				{
					xp = xplevel_lev[CVAR_BOT_LEVEL];
				}
				else
				{
					//It is enabled and its set to XP based, so check to see if the starting XP is higher then what they have now
					if ( xp < xplevel_lev[CVAR_STARTING_LEVEL] )
					{
						//it must be, so lets set their XP and let them know
						xp = xplevel_lev[CVAR_STARTING_LEVEL];
						if( Util_Should_Msg_Client(id) )
						{
							//client_print ( id, print_chat, "[%s] %L", id, MOD, "STARTING_LEVEL_MESSAGE", xp );
							hudchat_show(id, "%L", id, "STARTING_LEVEL_MESSAGE", xp);
							hudchat_update(id);
						}
					}
				}
			}
		}
		
		playerxp[id] = xp;
		displaylevel ( id, 0 );
		p_attribs[id] = att;
		p_resists[id] = res;
	}
	
	p_skills[id] = skills;
	
	//Check for admin only skills, if they have any, dont add them to the users skill array
	for ( new i = 1; i < MAX_SKILLS; i++ )
	{
		if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
		{
			if ( !admin_only[p_skills[id][i]] || (get_user_flags(id) & CVAR_ADMIN_SKILL_FLAG ) )
			{
				skills[i] = p_skills[id][i];
			}
		}
		
		if ( ( p_skills[id][i] >= 1 ) && ( skill_ultimates[i][0] ) && ( !admin_only[p_skills[id][i]] || (get_user_flags(id) & CVAR_ADMIN_SKILL_FLAG ) ) )
		{
			
			if( Util_Should_Msg_Client(id) )
			{
				client_print ( id, print_console, "%L", id, "ULTIMATE_RETRIEVED", MOD, skill_ultimates[i][0] );
			}
			
			ultlearned[id]++;
			Set_Ult_Count( id );
		}
	}
	
	Set_Ult_Count( id );
	p_skills[id] = skills;
	xpreadytoload[id] = 0;
	log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> name %s auth %s :: [END]^n", tempVar44, tempVar55 );
	
	return PLUGIN_CONTINUE;
}

public _SaveXP ( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	// error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in SaveXPHandle.");
		if( is_user_connected( player_id ) && !is_user_bot( player_id ) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "SAVE_XP_FAILURE" );
			hudchat_show(player_id, "%L", player_id, "SAVE_XP_FAILURE");
			hudchat_update(player_id);
		}
		return PLUGIN_HANDLED;
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in SaveXPHandle");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		
		if( is_user_connected( player_id ) && !is_user_bot( player_id ) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "SAVE_XP_FAILURE" );
			hudchat_show(player_id, "%L", player_id, "SAVE_XP_FAILURE");
			hudchat_update(player_id);
		}
		return PLUGIN_HANDLED;
	}
	else
	{
		if( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: MySQL _SaveXP -> No Error" );
		}
	}
	
	if(Errcode )
	{
		log_amx( "[UWC3X] Error:SaveXPHandle - %s",Error);
		return PLUGIN_HANDLED;
	}
	
	return PLUGIN_CONTINUE;
}


public LoadXPMySQL2( id )
{
	
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	new tempVar[64], tempVar2[64];
	get_user_name ( id, tempVar2, 63 );
	
	log_amx( "[UWC3X] SQL :: Loading XP for user %s :: [Start]", tempVar2);
	
	if( CVAR_SAVE_BY == 2 )
	{
		copy( tempVar, 32, "name");
		get_user_name ( id, tempVar2, 63 );
		
		remove_quotes(tempVar2);
		while(replace(tempVar2,63,"'","")) { }
		while(replace(tempVar2,63,")","")) { }
		while(replace(tempVar2,63,"(","")) { }
		while(replace(tempVar2,63,";","")) { }
	}
	else
	{
		copy( tempVar, 32, "steamid");
		get_user_authid ( id, tempVar2, 63 );
	}
	
	format ( squery, 4096, "SELECT steamid, xp, ip, mtime, skill1, skill2, skill3," );
	format ( squery, 4096, "%s skill4, skill5, skill6, skill7, skill8, skill9, skill10, ", squery );
	format ( squery, 4096, "%s skill11, skill12, skill13, skill14, skill15, skill16, skill17,", squery );
	format ( squery, 4096, "%s skill18, skill19, skill20, skill21, skill22, skill23, skill24,", squery );
	format ( squery, 4096, "%s skill25, skill26, skill27, skill28, skill29, skill30, skill31,", squery );
	format ( squery, 4096, "%s skill32, skill33, skill34, skill35, skill36, skill37, skill38,", squery );
	format ( squery, 4096, "%s skill39, skill40, skill41, skill42, skill43, skill44, skill45,", squery );
	format ( squery, 4096, "%s skill46, skill47, skill48, skill49, skill50, skill51, skill52,", squery );
	format ( squery, 4096, "%s skill53, skill54, skill55, skill56, skill57, skill58, skill59,", squery );
	format ( squery, 4096, "%s skill60, skill61, skill62, skill63, skill64,", squery );
	format ( squery, 4096, "%s att1, att2, att3, att4, att5, att6, res1, res2,", squery );
	format ( squery, 4096, "%s res3, res4, res5, res6, res7, name FROM %s WHERE %s = '%s';", squery, CVAR_MYSQL_TABLE, tempVar, tempVar2 );
	
	player_id = id;
	
	//Create handle and then the connection
	g_SqlTuple = SQL_MakeDbTuple ( CVAR_MYSQL_HOSTNAME, CVAR_MYSQL_USERNAME, CVAR_MYSQL_PASSWORD, CVAR_MYSQL_DATABASE );
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );
	
	//Check for an error
	if ( !SqlConnection )
	{
		log_amx( "[UWC3X] SQL :: Loading XP :: Connected [FAILED]" );
		log_amx( "[UWC3X] Error connecting to SQL database : %s", g_Error );
		return PLUGIN_CONTINUE;
	}
	
	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );
	
	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQL :: Error Loading players XP" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
	}
	else
	{
		new id = player_id;
		new ip[32];
		new xp = 0;
		new pid[32];
		new skills[MAX_SKILLS] = 0;
		new att[MAX_ATTRIBS] = 0;
		new res[MAX_RESISTS] = 0;
		
		//Now that we have no errors, I will reset the xp loading var, this is in case there are
		//errors so that it will continue to retry
		NumResults = SQL_NumResults(Query);
		
		if ( CVAR_DEBUG_MODE && is_user_bot( id ) )
		{
			log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: NumResults=%d", NumResults);
		}
		
		
		if ( !NumResults || NumResults == 0 || is_user_bot( id ) )
		{
			//no data exists
			if( Util_Should_Msg_Client(id) )
			{
				//client_print ( id, print_chat, "%L", id, "LOAD_XP_NO_DATA", MOD );
				hudchat_show(player_id, "%L", player_id, "LOAD_XP_NO_DATA");
				hudchat_update(player_id);
			}
			
			//If the enable starting XP is turned on, then give them the XP
			// this is for new players who do not yet exist in the database, existing players are below
			
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: Player is a bot or has no results from query");
			}
			
			//If starting XP is enabled, do the check
			if ( CVAR_ENABLE_STARTING_SYSTEM )
			{
				if( CVAR_STARTING_METHOD == 1 )
				{
					//It is enabled and its set to XP based, so check to see if the starting XP is higher then what they have now
					if ( xp < CVAR_STARTING_XP )
					{
						//it must be, so lets set their XP and let them know
						xp = CVAR_STARTING_XP;
						if( Util_Should_Msg_Client(id) )
						{
							//client_print ( id, print_chat, "[%s] %L", id, MOD, "STARTING_XP_MESSAGE", CVAR_STARTING_XP );
							hudchat_show(player_id, "%L", player_id, "STARTING_XP_MESSAGE", CVAR_STARTING_XP);
							hudchat_update(player_id);
						}
					}
				}
				else
				{
					//Override default level if its a bot and use the bot level cvar
					if( is_user_bot(id))
					{
						xp = xplevel_lev[CVAR_BOT_LEVEL];
					}
					else
					{
						//It is enabled and its set to XP based, so check to see if the starting XP is higher then what they have now
						if ( xp < xplevel_lev[CVAR_STARTING_LEVEL] )
						{
							//it must be, so lets set their XP and let them know
							xp = xplevel_lev[CVAR_STARTING_LEVEL];
							if( Util_Should_Msg_Client(id) )
							{
								//client_print ( id, print_chat, "[%s] %L", id, MOD, "STARTING_LEVEL_MESSAGE", xp );
								hudchat_show(player_id, "%L", player_id, "STARTING_LEVEL_MESSAGE", xp);
								hudchat_update(player_id);
							}
						}
					}
				}
				
				playerxp[id] = xp;
				if ( CVAR_DEBUG_MODE )
				{
					log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: Set xp to %d", xp);
				}
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					//client_print ( id, print_chat, "[%s] %L", id, MOD, "STARTING_XP_DISABLED" );
					hudchat_show(player_id, "%L", player_id, "STARTING_XP_DISABLED");
					hudchat_update(player_id);
				}
			}
			
			xpreadytoload[id] = 0;
		}
		else
		{
			new sName[64];
			new temp[32], sqlField;
			
			//They have data, lets load it
			//Set the PlayerID, XP, IP, and Last time
			SQL_ReadResult ( Query, 0, pid, 31 );
			xp = SQL_ReadResult ( Query, 1 );
			SQL_ReadResult ( Query, 2, ip, 31 );
			SQL_ReadResult ( Query, 3, mtimet, 31 );
			
			copy( temp, 31, "name");
			sqlField = SQL_FieldNameToNum(Query, temp)
			SQL_ReadResult ( Query, sqlField, sName, 63 );
			
			//Start setting the skills
			for ( new k = 1; k < (MAX_SKILLS); k++ )
			{
				format( temp, 31, "skill%d", k);
				sqlField = SQL_FieldNameToNum(Query, temp)
				skills[k] = SQL_ReadResult ( Query, sqlField );
			}
			
			//Set the attributes
			for ( new k = 1; k < (MAX_ATTRIBS); k++ )
			{
				format( temp, 31, "att%d", k);
				sqlField = SQL_FieldNameToNum(Query, temp)
				att[k] = SQL_ReadResult ( Query, sqlField );
				
				//If the attrib is less then the base, or greater then max, reset to base
				if( ( ATTRIB_MAX_VALUE < att[k] ) || ( att[k] < ATTRIB_BASE ) )
					att[k] = ATTRIB_BASE;
			}
			
			//Set the resistances
			for ( new k = 1; k < (MAX_RESISTS); k++ )
			{
				format( temp, 31, "res%d", k);
				sqlField = SQL_FieldNameToNum(Query, temp)
				res[k] = SQL_ReadResult ( Query, sqlField );
			}
			
			if ( CVAR_ENABLE_STARTING_SYSTEM )
			{
				if( CVAR_STARTING_METHOD == 1 )
				{
					if ( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] DEBUG: MySQL->_LoadXP: No Records, client %s given %d starting XP ", tempVar, CVAR_STARTING_XP);
					}
					
					if( Util_Should_Msg_Client(id) )
					{
						//client_print(id, print_chat, "%L", "LOAD_XP_STARTING_XP", MOD, CVAR_STARTING_XP );
						hudchat_show(id, "%L", id, "LOAD_XP_STARTING_XP", CVAR_STARTING_XP);
						hudchat_update(id);
					}
					
					playerxp[id] = CVAR_STARTING_XP;
					
				}
				else
				{
					//Override default level if its a bot and use the bot level cvar
					if( is_user_bot(id))
					{
						playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
					}
					else
					{
						if( Util_Should_Msg_Client(id) )
						{
							//client_print(id, print_chat, "%L", "LOAD_XP_STARTING_LEVEL", MOD, CVAR_STARTING_LEVEL );
							hudchat_show(id, "%L", id, "LOAD_XP_STARTING_LEVEL", CVAR_STARTING_LEVEL);
							hudchat_update(id);
						}
						
						playerxp[id] = xplevel_lev[CVAR_STARTING_LEVEL];
					}
				}
			}
			
			playerxp[id] = xp;
			displaylevel ( id, 0 );
			p_attribs[id] = att;
			p_resists[id] = res;
			
		}
		
		//Set Player Value
		Set_Wisdom_Bonuses( id );
		p_skills[id] = skills;
		
		//Check for admin only skills, if they have any, dont add them to the users skill array
		for ( new i = 1; i < MAX_SKILLS; i++ )
		{
			if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
			{
				if ( !admin_only[p_skills[id][i]] )
				{
					skills[i] = p_skills[id][i];
				}
			}
			
			if ( ( p_skills[id][i] >= 1 ) && ( skill_ultimates[i][0] ) && ( !admin_only[p_skills[id][i]] ) )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print ( id, print_console, "%L", id, "ULTIMATE_RETRIEVED", MOD, skill_ultimates[i][0] );
				}
			}
		}
		
		Set_Ult_Count( id );
		
		p_skills[id] = skills;
		xpreadytoload[id] = 0;
		
		if( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] DEBUG :: MySQL -> Ultimates allowed after loading = %d", ultlearned[id] );
		}
		
		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}
	
	log_amx( "[UWC3X] SQL :: Loading XP :: [Done]" );
	return PLUGIN_CONTINUE;
	
}

public LoadXPMySQL ( id )
{
	
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	new tempVar[64], tempVar2[64];
	get_user_name ( id, tempVar, 63 );
	get_user_authid ( id, tempVar2, 63 );
	log_amx( "[UWC3X] DEBUG :: MySQL LoadXPMySQL -> name %s auth %s :: [Start]", tempVar, tempVar2 );
	
	if( CVAR_SAVE_BY == 2 )
	{
		copy( tempVar, 32, "name");
		get_user_name ( id, tempVar2, 63 );
		
		remove_quotes(tempVar2);
		while(replace(tempVar2,63,"'","")) { }
		while(replace(tempVar2,63,")","")) { }
		while(replace(tempVar2,63,"(","")) { }
		while(replace(tempVar2,63,";","")) { }
		
	}
	else
	{
		copy( tempVar, 32, "steamid");
		get_user_authid ( id, tempVar2, 63 );
	}
	
	format ( squery, 4096, "SELECT steamid, xp, ip, mtime, skill1, skill2, skill3," );
	format ( squery, 4096, "%s skill4, skill5, skill6, skill7, skill8, skill9, skill10, ", squery );
	format ( squery, 4096, "%s skill11, skill12, skill13, skill14, skill15, skill16, skill17,", squery );
	format ( squery, 4096, "%s skill18, skill19, skill20, skill21, skill22, skill23, skill24,", squery );
	format ( squery, 4096, "%s skill25, skill26, skill27, skill28, skill29, skill30, skill31,", squery );
	format ( squery, 4096, "%s skill32, skill33, skill34, skill35, skill36, skill37, skill38,", squery );
	format ( squery, 4096, "%s skill39, skill40, skill41, skill42, skill43, skill44, skill45,", squery );
	format ( squery, 4096, "%s skill46, skill47, skill48, skill49, skill50, skill51, skill52,", squery );
	format ( squery, 4096, "%s skill53, skill54, skill55, skill56, skill57, skill58, skill59,", squery );
	format ( squery, 4096, "%s skill60, skill61, skill62, skill63, skill64,", squery );
	format ( squery, 4096, "%s att1, att2, att3, att4, att5, att6, res1, res2,", squery );
	format ( squery, 4096, "%s res3, res4, res5, res6, res7, name FROM %s WHERE %s = '%s';", squery, CVAR_MYSQL_TABLE, tempVar, tempVar2 );
	
	player_id = id;
	SQL_ThreadQuery ( g_SqlTuple, "_LoadXP", squery );
	return PLUGIN_CONTINUE;
	
}
public SaveXPMySQL ( id )
{
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	new tempVar[64];
	get_user_name ( id, tempVar, 63 );
	get_user_authid ( id, steamid, 34 );
	remove_quotes(tempVar);
	while(replace(tempVar,63,"'","")) { }
	while(replace(tempVar,63,")","")) { }
	while(replace(tempVar,63,"(","")) { }
	while(replace(tempVar,63,";","")) { }
	
	if ( CVAR_ENABLE_STARTING_SYSTEM )
	{
		if( CVAR_STARTING_METHOD == 1 )
		{
			if ( playerxp[id] <= CVAR_STARTING_XP )
			{
				playerxp[id] = CVAR_STARTING_XP;
			}
		}
		else
		{
			if( is_user_bot( id ))
			{			
				if ( playerxp[id] <= xplevel_lev[CVAR_BOT_LEVEL] )
				{
					playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
				}			
			}
			else
			{
				//If they are a bot, then dont save, always use the bot level insetead to set XP
				if( is_user_bot( id ))
				{
					playerxp[id] = xplevel_lev[CVAR_BOT_LEVEL];
					if( CVAR_DEBUG_MODE )
					{
						log_amx( "[UWC3X] DEBUG :: MySQL SaveXPMySQL -> is_user_bot1 name %s auth %s xp %d", tempVar, steamid, playerxp[id] );
					}
				}
				else
				{
					//if( CVAR_DEBUG_MODE )
					//{
					log_amx( "[UWC3X] DEBUG :: MySQL SaveXPMySQL -> User is Human - name %s auth %s xp %d", tempVar, steamid, playerxp[id] );
					//}
					
					if ( playerxp[id] <= xplevel_lev[CVAR_STARTING_LEVEL] )
					{
						playerxp[id] = xplevel_lev[CVAR_STARTING_LEVEL];
					}
				}
			}
		}
	}
	
	get_time ( "%d/%m/%Y %H:%M:%S", mtimet, 31 );
	
	format ( squery, 4096, "REPLACE INTO `%s` SET steamid='%s', xp='%d',", CVAR_MYSQL_TABLE, steamid, playerxp[id] );
	format ( squery, 4096, "%s mtime='%s' , skill1='%d' , skill2='%d' ,", squery, mtimet, p_skills[id][1], p_skills[id][2] ) ;
	format ( squery, 4096, "%s skill3='%d' , skill4='%d' , skill5='%d' ,", squery,p_skills[id][3], p_skills[id][4], p_skills[id][5] );
	format ( squery, 4096, "%s skill6='%d' , skill7='%d' , skill8='%d' ,", squery,p_skills[id][6], p_skills[id][7], p_skills[id][8] );
	format ( squery, 4096, "%s skill9='%d' , skill10='%d', skill11='%d',", squery,p_skills[id][9], p_skills[id][10], p_skills[id][11] );
	format ( squery, 4096, "%s skill12='%d', skill13='%d', skill14='%d',", squery,p_skills[id][12], p_skills[id][13], p_skills[id][14] );
	format ( squery, 4096, "%s skill15='%d', skill16='%d', skill17='%d',", squery,p_skills[id][15], p_skills[id][16], p_skills[id][17] ) ;
	format ( squery, 4096, "%s skill18='%d', skill19='%d', skill20='%d',", squery,p_skills[id][18], p_skills[id][19], p_skills[id][20] );
	format ( squery, 4096, "%s skill21='%d', skill22='%d', skill23='%d',", squery,p_skills[id][21], p_skills[id][22], p_skills[id][23] );
	format ( squery, 4096, "%s skill24='%d', skill25='%d', skill26='%d',", squery,p_skills[id][24], p_skills[id][25], p_skills[id][26] );
	format ( squery, 4096, "%s skill27='%d', skill28='%d', skill29='%d',", squery,p_skills[id][27], p_skills[id][28], p_skills[id][29] );
	format ( squery, 4096, "%s skill30='%d', skill31='%d', skill32='%d',", squery,p_skills[id][30], p_skills[id][31], p_skills[id][32] );
	format ( squery, 4096, "%s skill33='%d', skill34='%d', skill35='%d',", squery,p_skills[id][33], p_skills[id][34], p_skills[id][35] );
	format ( squery, 4096, "%s skill36='%d', skill37='%d', skill38='%d',", squery,p_skills[id][36], p_skills[id][37], p_skills[id][38] );
	format ( squery, 4096, "%s skill39='%d', skill40='%d', skill41='%d',", squery,p_skills[id][39], p_skills[id][40], p_skills[id][41] );
	format ( squery, 4096, "%s skill42='%d', skill43='%d', skill44='%d',", squery,p_skills[id][42], p_skills[id][43], p_skills[id][44] );
	format ( squery, 4096, "%s skill45='%d', skill46='%d', skill47='%d',", squery,p_skills[id][45], p_skills[id][46], p_skills[id][47] );
	format ( squery, 4096, "%s skill48='%d', skill49='%d', skill50='%d',", squery,p_skills[id][48], p_skills[id][49], p_skills[id][50] );
	format ( squery, 4096, "%s skill51='%d', skill52='%d', skill53='%d',", squery,p_skills[id][51], p_skills[id][52], p_skills[id][53] );
	format ( squery, 4096, "%s skill54='%d', skill55='%d', skill56='%d',", squery, p_skills[id][54],p_skills[id][55], p_skills[id][56] );
	format ( squery, 4096, "%s skill57='%d', skill58='%d', skill59='%d',", squery,p_skills[id][57], p_skills[id][58], p_skills[id][59] );
	format ( squery, 4096, "%s skill60='%d', skill61='%d', skill62='%d',", squery,p_skills[id][60], p_skills[id][61], p_skills[id][62] );
	format ( squery, 4096, "%s skill63='%d', skill64='%d', ", squery, p_skills[id][63],p_skills[id][64] );
	format ( squery, 4096, "%s att1='%d' , att2='%d' , att3='%d' , att4='%d' ,", squery, p_attribs[id][ATTRIBIDX_STR], p_attribs[id][ATTRIBIDX_INT], p_attribs[id][ATTRIBIDX_DEX], p_attribs[id][ATTRIBIDX_AGI] );
	format ( squery, 4096, "%s att5='%d' , att6='%d' , res1='%d' , res2='%d' ,", squery, p_attribs[id][ATTRIBIDX_CON], p_attribs[id][ATTRIBIDX_WIS], p_resists[id][RESISTIDX_POISON], p_resists[id][RESISTIDX_DISEASE] );
	format ( squery, 4096, "%s res3='%d' , res4='%d' , res5='%d' , res6='%d', res7='%d', name='%s' ;", squery, p_resists[id][RESISTIDX_ELECTRIC], p_resists[id][RESISTIDX_FIRE], p_resists[id][RESISTIDX_MAGIC], p_resists[id][RESISTIDX_ROT],p_resists[id][RESISTIDX_ICE], tempVar );
	
	player_id = id;
	SQL_ThreadQuery ( g_SqlTuple, "_SaveXP", squery );
	return PLUGIN_CONTINUE;
}

public LogError( Handle:Query, sQuery[], sError[], iErrNum, failstate, sFunction[] )
{
	log_amx( "[UWC3X] Threaded query error, location: %s", sFunction );
	log_amx( "[UWC3X] Message: %s (%d)", sError, iErrNum );
	log_amx( "[UWC3X] Query statement: %s ", sQuery );
	
	// Connection failed
	if ( failstate == TQUERY_CONNECT_FAILED )
	{
		log_amx( "[UWC3X] Fail state: Connection Failed" );
	}
	
	// Query failed
	else if ( failstate == TQUERY_QUERY_FAILED )
	{
		log_amx( "[UWC3X] Fail state: Query Failed" );
	}
	
	// Free the handle
	SQL_FreeHandle( Query );
}
public MySQLClose()
{
	if ( g_SqlTuple )
	{
		SQL_FreeHandle( g_SqlTuple );
	}
	
	if ( SqlConnection )
	{
		SQL_FreeHandle( SqlConnection );
	}
}



public TableHandle(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	
	// lots of error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in TableHandle.");
		set_fail_state("Could not connect to SQL database in TableHandle.");
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error creating table.");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		set_fail_state("Could not execute query in TableHandle.");
	}
	
	if(Errcode)
		log_amx( "[UWC3X] TableHandle - Error on query: %s",Error);
	
	return PLUGIN_CONTINUE;
}

public QueryHandle(FailState,Handle:Query,Error[],Errcode,Data[],DataSize)
{
	// lots of error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in QueryHandle.");
		set_fail_state("Could not connect to SQL database in QueryHandle.");
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in QueryHandle");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		set_fail_state("Could not execute query in QueryHandle.");
	}
	
	if(Errcode)
		log_amx( "[UWC3X] Error: QueryHandle - Code %d", ErrorCode);
	
	return PLUGIN_CONTINUE;
}

public _SaveSkillSet( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	
	// lots of error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in _SaveSkillSet.");
		
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "SAVESKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "SAVESKILLSET_ERROR");
			hudchat_update(player_id);
		}
		
		return PLUGIN_HANDLED;
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in _SaveSkillSet");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "SAVESKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "SAVESKILLSET_ERROR");
			hudchat_update(player_id);
		}
		return PLUGIN_HANDLED;
	}
	
	if(Errcode)
	{
		log_amx( "[UWC3X] Error:_SaveSkillSet - %d", Errcode);
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_DEBUG_MODE )
	{
		new tempVar[64];
		get_user_name ( player_id, tempVar, 63 );
		log_amx( "[UWC3X] Debug:: MySQL->_SaveSkillSet : No error, attepting to Save skillset %d for %s", skills_id, tempVar );
	}
	
	if( Util_Should_Msg_Client(player_id) )
	{
		//client_print(player_id, print_chat, "%L", player_id, "SAVESKILLSET", MOD, skills_id );
		hudchat_show(player_id, "%L", player_id, "SAVESKILLSET", skills_id);
		hudchat_update(player_id);
	}
	
	return PLUGIN_CONTINUE;
}
public _LoadSkillSet( FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	
	new skills[MAX_SKILLS] = 0;
	new tempVar[64];
	
	// lots of error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in _LoadSkillSet.");
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "LOADSKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "LOADSKILLSET_ERROR", MOD);
			hudchat_update(player_id);
		}
		
		return PLUGIN_HANDLED;
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in _LoadSkillSet");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "LOADSKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "LOADSKILLSET_ERROR", MOD);
			hudchat_update(player_id);
		}
		return PLUGIN_HANDLED;
	}
	
	if(Errcode)
	{
		log_amx( "[UWC3X] Error:_LoadSkillSet - %d", Errcode);
		return PLUGIN_HANDLED;
	}
	
	//Now that we have no errors, I will reset the xp loading var, this is in case there are
	//errors so that it will continue to retry
	NumResults = SQL_NumResults(Query);
	
	if ( CVAR_DEBUG_MODE )
	{
		get_user_name ( player_id, tempVar, 63 );
	}
	
	if ( !NumResults || NumResults == 0 )
	{
		//No results, tell them and then exit
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "LOADSKILLSET_NODATA", MOD, skills_id);
			hudchat_show(player_id, "%L", player_id, "LOADSKILLSET_NODATA", skills_id);
			hudchat_update(player_id);
		}
		return PLUGIN_CONTINUE;
	}
	else
	{
		
		//Since they are resetting their skills, and choosing new ones
		//Zero out anything they had previously so that the new ones can take effect
		for ( new j=0; j<MAX_SKILLS; j++ )
		{
			// Set all skills to 0
			p_skills[player_id][j]=0;
		}
		
		ultlearned[player_id] = 0;
		
		if( p_attribs[player_id][ATTRIBIDX_WIS] >= 18 )
		{
			p_maxultimates[player_id] = MAX_ULTIMATES + 1;
		}
		else
		{
			p_maxultimates[player_id] = MAX_ULTIMATES;
		}
		
		new name[32];
		get_user_name ( player_id, name, 31 );
		
		new temp[32], sqlField;
		//Start setting the skills
		for ( new k = 1; k < (MAX_SKILLS); k++ )
		{
			format( temp, 31, "skill%d", k);
			sqlField = SQL_FieldNameToNum(Query, temp)
			skills[k] = SQL_ReadResult ( Query, sqlField );
			
			if( skill_ultimates[k][0] && ( ultlearned[player_id] < p_maxultimates[player_id] ) )
			{
				if( Util_Should_Msg_Client(player_id) )
				{
					client_print ( player_id, print_console, "%L", player_id, "ULTIMATE_RETRIEVED", MOD, skill_ultimates[k][0] );
				}
				
				ultlearned[player_id]++;
				Set_Ult_Count(player_id);
			}
		}
	}
	
	p_skills[player_id] = skills;
	xpreadytoload[player_id] = 0;
	
	if( Util_Should_Msg_Client(player_id) )
	{
		//client_print(player_id, print_chat, "%L", player_id, "LOADSKILLSET", MOD, skills_id );
		hudchat_show(player_id, "%L", player_id, "LOADSKILLSET", skills_id);
		hudchat_update(player_id);
	}
	
	return PLUGIN_CONTINUE;
}

public _DelSkillSet(FailState, Handle:Query, Error[], Errcode, Data[], DataSize )
{
	// lots of error checking
	if(FailState == TQUERY_CONNECT_FAILED)
	{
		log_amx( "[UWC3X] Error: Could not connect to SQL database in _DelSkillSet.");
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "DELETESKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "DELETESKILLSET_ERROR");
			hudchat_update(player_id);
		}
		
		return PLUGIN_HANDLED;
	}
	else if(FailState == TQUERY_QUERY_FAILED)
	{
		log_amx( "[UWC3X] SQL :: Error in _DelSkillSet");
		SQL_QueryError(Query,g_Error,511);
		log_amx( "[UWC3X] ERROR %s",g_Error);
		if( Util_Should_Msg_Client(player_id) )
		{
			//client_print(player_id, print_chat, "%L", player_id, "DELETESKILLSET_ERROR", MOD);
			hudchat_show(player_id, "%L", player_id, "DELETESKILLSET_ERROR");
			hudchat_update(player_id);
		}
		return PLUGIN_HANDLED;
	}
	
	if(Errcode)
	{
		log_amx( "[UWC3X] Error:_DelSkillSet - %d", Errcode);
		return PLUGIN_HANDLED;
	}
	
	if( Util_Should_Msg_Client(player_id) )
	{
		//client_print( player_id, print_chat, "%L", player_id, "DELETESKILLSET_OK", MOD, skills_id );
		hudchat_show(player_id, "%L", player_id, "DELETESKILLSET_OK", skills_id);
		hudchat_update(player_id);
	}
	
	return PLUGIN_CONTINUE;
	
}

public DeleteSkillSetMySQL ( id, skillsetIDX )
{
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 4096, "Delete from `%s_SkillSets` where name='%s' and skillsetid='%d',", CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "Delete from `%s_SkillSets` where steamid='%s' and skillsetid='%d',", CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: MySQL->DeleteSkillSetMySQL: Set SQL_ThreadQuery" );
	}
	
	SQL_ThreadQuery ( g_SqlTuple, "_DelSkillSet", squery );
	return PLUGIN_CONTINUE;
	
}
public SaveSkillSetMySQL( id, skillsetIDX )
{
	
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 5096, "REPLACE INTO `%s_SkillSets` SET name='%s', skillsetid='%d',", CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 5096, "REPLACE INTO `%s_SkillSets` SET steamid='%s', skillsetid='%d',", CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	format ( squery, 4096, "%s skill1='%d' , skill2='%d' ,", squery, p_skills[id][1], p_skills[id][2] ) ;
	format ( squery, 4096, "%s skill3='%d' , skill4='%d' , skill5='%d' ,", squery,p_skills[id][3], p_skills[id][4], p_skills[id][5] );
	format ( squery, 4096, "%s skill6='%d' , skill7='%d' , skill8='%d' ,", squery,p_skills[id][6], p_skills[id][7], p_skills[id][8] );
	format ( squery, 4096, "%s skill9='%d' , skill10='%d', skill11='%d',", squery,p_skills[id][9], p_skills[id][10], p_skills[id][11] );
	format ( squery, 4096, "%s skill12='%d', skill13='%d', skill14='%d',", squery,p_skills[id][12], p_skills[id][13], p_skills[id][14] );
	format ( squery, 4096, "%s skill15='%d', skill16='%d', skill17='%d',", squery,p_skills[id][15], p_skills[id][16], p_skills[id][17] ) ;
	format ( squery, 4096, "%s skill18='%d', skill19='%d', skill20='%d',", squery,p_skills[id][18], p_skills[id][19], p_skills[id][20] );
	format ( squery, 4096, "%s skill21='%d', skill22='%d', skill23='%d',", squery,p_skills[id][21], p_skills[id][22], p_skills[id][23] );
	format ( squery, 4096, "%s skill24='%d', skill25='%d', skill26='%d',", squery,p_skills[id][24], p_skills[id][25], p_skills[id][26] );
	format ( squery, 4096, "%s skill27='%d', skill28='%d', skill29='%d',", squery,p_skills[id][27], p_skills[id][28], p_skills[id][29] );
	format ( squery, 4096, "%s skill30='%d', skill31='%d', skill32='%d',", squery,p_skills[id][30], p_skills[id][31], p_skills[id][32] );
	format ( squery, 4096, "%s skill33='%d', skill34='%d', skill35='%d',", squery,p_skills[id][33], p_skills[id][34], p_skills[id][35] );
	format ( squery, 4096, "%s skill36='%d', skill37='%d', skill38='%d',", squery,p_skills[id][36], p_skills[id][37], p_skills[id][38] );
	format ( squery, 4096, "%s skill39='%d', skill40='%d', skill41='%d',", squery,p_skills[id][39], p_skills[id][40], p_skills[id][41] );
	format ( squery, 4096, "%s skill42='%d', skill43='%d', skill44='%d',", squery,p_skills[id][42], p_skills[id][43], p_skills[id][44] );
	format ( squery, 4096, "%s skill45='%d', skill46='%d', skill47='%d',", squery,p_skills[id][45], p_skills[id][46], p_skills[id][47] );
	format ( squery, 4096, "%s skill48='%d', skill49='%d', skill50='%d',", squery,p_skills[id][48], p_skills[id][49], p_skills[id][50] );
	format ( squery, 4096, "%s skill51='%d', skill52='%d', skill53='%d',", squery,p_skills[id][51], p_skills[id][52], p_skills[id][53] );
	format ( squery, 4096, "%s skill54='%d', skill55='%d', skill56='%d',", squery, p_skills[id][54],p_skills[id][55], p_skills[id][56] );
	format ( squery, 4096, "%s skill57='%d', skill58='%d', skill59='%d',", squery,p_skills[id][57], p_skills[id][58], p_skills[id][59] );
	format ( squery, 4096, "%s skill60='%d', skill61='%d', skill62='%d',", squery,p_skills[id][60], p_skills[id][61], p_skills[id][62] );
	format ( squery, 4096, "%s skill63='%d', skill64='%d' ;", squery, p_skills[id][63],p_skills[id][64] );
	
	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: MySQL->SaveSkillSetMySQL: Set SQL_ThreadQuery" );
	}
	
	SQL_ThreadQuery ( g_SqlTuple, "_SaveSkillSet", squery );
	return PLUGIN_CONTINUE;
	
}

public LoadSkillSetMySQL( id, skillsetIDX )
{
	
	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}
	
	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}
	
	if( CVAR_SAVE_BY == 2 )
	{
		format ( squery, 4096, "SELECT name, skill1, skill2, skill3," );
	}
	else
	{
		format ( squery, 4096, "SELECT steamid, skill1, skill2, skill3," );
	}
	
	format ( squery, 4096, "%s skill4, skill5, skill6, skill7, skill8, skill9, skill10, ", squery );
	format ( squery, 4096, "%s skill11, skill12, skill13, skill14, skill15, skill16, skill17,", squery );
	format ( squery, 4096, "%s skill18, skill19, skill20, skill21, skill22, skill23, skill24,", squery );
	format ( squery, 4096, "%s skill25, skill26, skill27, skill28, skill29, skill30, skill31,", squery );
	format ( squery, 4096, "%s skill32, skill33, skill34, skill35, skill36, skill37, skill38,", squery );
	format ( squery, 4096, "%s skill39, skill40, skill41, skill42, skill43, skill44, skill45,", squery );
	format ( squery, 4096, "%s skill46, skill47, skill48, skill49, skill50, skill51, skill52,", squery );
	format ( squery, 4096, "%s skill53, skill54, skill55, skill56, skill57, skill58, skill59,", squery );
	format ( squery, 4096, "%s skill60, skill61, skill62, skill63, skill64 ", squery );
	
	if( CVAR_SAVE_BY == 2 )
	{
		new userName[63];
		get_user_name ( id, userName, 63 );
		format ( squery, 4096, "%s FROM %s_SkillSets WHERE name = '%s' and skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "%s FROM %s_SkillSets WHERE steamid = '%s' and skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: MySQL->LoadSkillSetMySQL: Set SQL_ThreadQuery" );
	}
	
	SQL_ThreadQuery ( g_SqlTuple, "_LoadSkillSet", squery );
	return PLUGIN_CONTINUE;
}