
public IsSQLiteConnected ( )
{
	if( bDBConn )
	{
		return true;
	}

	return false;
}



public LoadSQLLiteConfig ( )
{
	//No configs to load for sqlite
	log_amx( "[UWC3X] SQLite :: Loading Config..." );
	LoadSQLLiteVars();
	return PLUGIN_CONTINUE;
}


public LoadSQLLiteVars ( )
{
	//Load the Cvars into locally used strings
	log_amx( "[UWC3X] SQLite :: Setting Vars..." );

	//Create handle and then the connection
	g_SqlTuple = SQL_MakeDbTuple ( "", "", "", CVAR_MYSQL_DATABASE );

	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Check for an error
	if ( !SqlConnection )
	{
		log_amx( "[UWC3X] Error connecting to SQLite database : %s", g_Error );
		bDBConn = false;
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQLite :: Connected [OK]" );
		bDBConn = true;
	}

	format ( squery, 4096, "CREATE TABLE IF NOT EXISTS `%s` ( `steamid` VARCHAR ( 32 ) NOT NULL, `xp` INT, `ip` ", CVAR_MYSQL_TABLE );
	format ( squery, 4096, "%s%s", squery, "VARCHAR ( 32 ), `mtime` VARCHAR ( 32 ), `skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill3` SMALLINT DEFAULT '0', `skill4` SMALLINT DEFAULT '0', `skill5` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', `skill7` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', `skill10` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', `skill13` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 4096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` " );
	format ( squery, 4096, "%s%s", squery, "SMALLINT DEFAULT '0', `skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill24` SMALLINT DEFAULT '0', `skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT " ) ;
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0' , `skill27` SMALLINT DEFAULT '0', `skill28` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', `skill31` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', " ) ;
	format ( squery, 4096, "%s%s", squery, "`skill39` SMALLINT DEFAULT '0', `skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill42` SMALLINT DEFAULT '0', `skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill45` SMALLINT DEFAULT '0', `skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill48` SMALLINT DEFAULT '0', `skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill51` SMALLINT DEFAULT '0', `skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill54` SMALLINT DEFAULT '0', `skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill57` SMALLINT DEFAULT '0', `skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill60` SMALLINT DEFAULT '0', `skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`skill63` SMALLINT DEFAULT '0', `skill64` SMALLINT DEFAULT '0', " );
	format ( squery, 4096, "%s%s", squery, "`att1` SMALLINT DEFAULT '0', `att2` SMALLINT DEFAULT '0', `att3` SMALLINT DEFAULT '0', `att4` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `att5` SMALLINT DEFAULT '0', `att6` SMALLINT DEFAULT '0', `res1` SMALLINT DEFAULT '0', `res2` SMALLINT " );
	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `res3` SMALLINT DEFAULT '0', `res4` SMALLINT DEFAULT '0', `res5` SMALLINT DEFAULT '0', `res6` SMALLINT DEFAULT '0', `res7` SMALLINT " );

	format ( squery, 4096, "%s%s", squery, "DEFAULT '0', `name` VARCHAR ( 64 ) DEFAULT NULL, PRIMARY KEY ( `name` ));" );

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error creating table" );
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

public SkillSetsSqlLite_Table ( )
{
	if( CVAR_SAVED_SKILLSETS )
	{
		log_amx( "[UWC3X] SQLite :: Using Saved Skill Sets [OK]" );
		//Create handle and then the connection
		g_SqlTuple = SQL_MakeDbTuple ( "", "", "", CVAR_MYSQL_DATABASE );

		//Try and connect
		SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

		//Check for an error
		if ( !SqlConnection )
		{
			log_amx( "[UWC3X] SQLite :: Created Skill Sets Table [FAILED]" );
			log_amx( "[UWC3X] Error connecting to SQLite database : %s", g_Error );
			bDBConn = false;
			return PLUGIN_CONTINUE;
		}

		log_amx( "[UWC3X] SQLite :: Connected [OK]" );

		format ( squery, 4096, "CREATE TABLE IF NOT EXISTS `%s_SkillSets` ( `name` VARCHAR(64), `steamid` VARCHAR(32), `skillsetid` INTEGER , ", CVAR_MYSQL_TABLE );

		format ( squery, 4096, "%s%s", squery, "`skill1` SMALLINT DEFAULT '0', `skill2` SMALLINT DEFAULT '0', `skill3` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill4` SMALLINT DEFAULT '0', `skill5` SMALLINT DEFAULT '0', `skill6` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill7` SMALLINT DEFAULT '0', `skill8` SMALLINT DEFAULT '0', `skill9` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill10` SMALLINT DEFAULT '0', `skill11` SMALLINT DEFAULT '0', `skill12` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill13` SMALLINT DEFAULT '0', `skill14` SMALLINT DEFAULT '0', `skill15` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill16` SMALLINT DEFAULT '0', `skill17` SMALLINT DEFAULT '0', `skill18` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill19` SMALLINT DEFAULT '0', `skill20` SMALLINT DEFAULT '0', `skill21` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill22` SMALLINT DEFAULT '0', `skill23` SMALLINT DEFAULT '0', `skill24` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill25` SMALLINT DEFAULT '0', `skill26` SMALLINT DEFAULT '0', `skill27` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill28` SMALLINT DEFAULT '0', `skill29` SMALLINT DEFAULT '0', `skill30` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill31` SMALLINT DEFAULT '0', `skill32` SMALLINT DEFAULT '0', `skill33` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill34` SMALLINT DEFAULT '0', `skill35` SMALLINT DEFAULT '0', `skill36` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill37` SMALLINT DEFAULT '0', `skill38` SMALLINT DEFAULT '0', `skill39` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill40` SMALLINT DEFAULT '0', `skill41` SMALLINT DEFAULT '0', `skill42` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill43` SMALLINT DEFAULT '0', `skill44` SMALLINT DEFAULT '0', `skill45` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill46` SMALLINT DEFAULT '0', `skill47` SMALLINT DEFAULT '0', `skill48` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill49` SMALLINT DEFAULT '0', `skill50` SMALLINT DEFAULT '0', `skill51` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill52` SMALLINT DEFAULT '0', `skill53` SMALLINT DEFAULT '0', `skill54` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill55` SMALLINT DEFAULT '0', `skill56` SMALLINT DEFAULT '0', `skill57` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill58` SMALLINT DEFAULT '0', `skill59` SMALLINT DEFAULT '0', `skill60` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill61` SMALLINT DEFAULT '0', `skill62` SMALLINT DEFAULT '0', `skill63` SMALLINT DEFAULT '0', " );
		format ( squery, 4096, "%s%s", squery, "`skill64` SMALLINT DEFAULT '0' );" );

		//Set the Query
		Query = SQL_PrepareQuery ( SqlConnection, squery );

		// run the query
		if ( !Query || !SQL_Execute ( Query ) )
		{
			// if there were any problems
			SQL_QueryError ( Query, g_Error, 511 );
			log_amx( "[UWC3X] SQLite :: Error creating table" );
			log_amx( "[UWC3X] Error:: %s", g_Error );
			log_amx( "[UWC3X] Query:: %s", squery );
		}
		else
		{
			//Free the stuff
			SQL_FreeHandle ( Query );
			SQL_FreeHandle ( SqlConnection );
		}

		log_amx( "[UWC3X] SQLite :: Created Skill Sets Table [OK]" );
		return PLUGIN_CONTINUE;
	}
	else
	{
		log_amx( "[UWC3X] SQLite :: Using Saved Skill Sets [NO]" );
		return PLUGIN_CONTINUE;
	}

	return PLUGIN_CONTINUE;
}




public LoadXPSQLLite ( id )
{

	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}


	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	new tempVar[64], tempVar2[64];
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
	g_SqlTuple = SQL_MakeDbTuple ( "", "", "", CVAR_MYSQL_DATABASE );

	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Check for an error
	if ( !SqlConnection )
	{
		log_amx( "[UWC3X] SQLLite :: Loading XP :: Connected [FAILED]" );
		log_amx( "[UWC3X] Error connecting to SQLLite database : %s", g_Error );
		return PLUGIN_CONTINUE;
	}

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Loading players XP" );
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
		
			if ( CVAR_DEBUG_MODE && is_user_bot( id ) )
			{
				log_amx( "[UWC3X] DEBUG: SQLLite->_LoadXP: Player is a bot");
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
					log_amx( "[UWC3X] DEBUG: SQLLite->_LoadXP: Set xp to %d", xp);
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
			return PLUGIN_CONTINUE;
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
						log_amx( "[UWC3X] DEBUG: SQLLite->_LoadXP: No Records, client %s given %d starting XP ", tempVar, CVAR_STARTING_XP);
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
			log_amx( "[UWC3X] DEBUG :: SQLLite -> Ultimates allowed after loading = %d", ultlearned[id] );
		}

		//Free the stuff
		SQL_FreeHandle ( Query );
		SQL_FreeHandle ( SqlConnection );
	}

	log_amx( "[UWC3X] SQLLite :: Loading XP :: [Done]" );
	return PLUGIN_CONTINUE;

}

public SaveXPSQLLite ( id )
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
						log_amx( "[UWC3X] DEBUG :: SQLLite SaveXPSQLLite -> is_user_bot1 name %s auth %s xp %d", tempVar, steamid, playerxp[id] );
					}
				}
				else
				{
					if ( playerxp[id] <= xplevel_lev[CVAR_STARTING_LEVEL] )
					{
						playerxp[id] = xplevel_lev[CVAR_STARTING_LEVEL];
					}
				}
			}
		}
	}

	get_time ( "%d/%m/%Y %H:%M:%S", mtimet, 31 );
	format ( squery, 4096, "REPLACE INTO `%s` (steamid, xp, mtime, ", CVAR_MYSQL_TABLE)
	for ( new k = 1; k < (MAX_SKILLS); k++ )
	{
		format( squery, 4096, "%s skill%d,", squery, k);
	}
	
	for (  new k = 1; k < (MAX_ATTRIBS); k++ )
	{
		format( squery, 4096, "%s att%d,", squery, k);
	}
	
	for (  new k = 1; k < (MAX_RESISTS); k++ )
	{
		format( squery, 4096, "%s res%d,", squery, k);
	}

	format ( squery, 4096, "%s name) VALUES ('%s' , '%d' , '%s' ,", squery, steamid, playerxp[id], mtimet);

	for ( new k = 1; k < (MAX_SKILLS); k++ )
	{
		format( squery, 4096, "%s '%d',", squery, p_skills[id][k]);
	}
	
	for (  new k = 1; k < (MAX_ATTRIBS); k++ )
	{
		format( squery, 4096, "%s '%d',", squery, p_attribs[id][k]);
	}
	
	for (  new k = 1; k < (MAX_RESISTS); k++ )
	{
		format( squery, 4096, "%s '%d',", squery, p_resists[id][k]);
	}	

	format ( squery, 4096, "%s '%s');", squery, tempVar) ;
	player_id = id;
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Saving player XP" );
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




public DeleteSkillSetSQLLite ( id, skillsetIDX )
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
		format ( squery, 4096, "DELETE FROM `%s_SkillSets` WHERE name='%s' AND skillsetid='%d';", CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "DELETE FROM `%s_SkillSets` WHERE steamid='%s' AND skillsetid='%d';", CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}

	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLIte->DeleteSkillSetSQLLite" );
	}
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Deleting player skill set" );
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
public SaveSkillSetSQLLite( id, skillsetIDX )
{

	if ( CVAR_ENABLE_UWC3X != 1 )
	{
		return PLUGIN_HANDLED;
	}

	if ( CVAR_SAVE_XP != 1 )
	{
		return PLUGIN_CONTINUE;
	}

	format ( squery, 4096, "REPLACE INTO `%s_SkillSets` (name, steamid, skillsetid", CVAR_MYSQL_TABLE)

	for ( new k = 1; k < (MAX_SKILLS); k++ )
	{
		format( squery, 4096, "%s, skill%d", squery, k);
	}

	new userName[63];
	get_user_name ( id, userName, 63 );
	new steamid[34];
	get_user_authid ( id, steamid, 34 );

	format ( squery, 4096, "%s) VALUES ('%s', '%s', '%d'", squery, userName, steamid, skillsetIDX);

	for ( new k = 1; k < (MAX_SKILLS); k++ )
	{
		format( squery, 4096, "%s, '%d'", squery, p_skills[id][k]);
	}

	format ( squery, 4096, "%s);", squery) ;
	player_id = id;
	skills_id = skillsetIDX;
	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLLite->SaveSkillSetSQLLite: Set SQL_ThreadQuery" );
	}
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Saving player skill set" );
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

public LoadSkillSetSQLLite( id, skillsetIDX )
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
		format ( squery, 4096, "%s FROM `%s_SkillSets` WHERE name = '%s' AND skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, userName, skillsetIDX );
	}
	else
	{
		get_user_authid ( id, steamid, 34 );
		format ( squery, 4096, "%s FROM `%s_SkillSets` WHERE steamid = '%s' AND skillsetid = '%d';", squery, CVAR_MYSQL_TABLE, steamid, skillsetIDX );
	}
	
	player_id = id;
	skills_id = skillsetIDX;
	new skills[MAX_SKILLS] = 0;
	new tempVar[64];

	if ( CVAR_DEBUG_MODE )
	{
		log_amx( "[UWC3X] DEBUG: SQLLite->LoadSkillSetSQLLite: Set SQL_ThreadQuery" );
	}
	
	//Try and connect
	SqlConnection = SQL_Connect ( g_SqlTuple, ErrorCode, g_Error, 511 );

	//Set the Query
	Query = SQL_PrepareQuery ( SqlConnection, squery );

	// run the query
	if ( !Query || !SQL_Execute ( Query ) )
	{
		// if there were any problems
		SQL_QueryError ( Query, g_Error, 511 );
		log_amx( "[UWC3X] SQLLite :: Error Saving player XP" );
		log_amx( "[UWC3X] Error:: %s", g_Error );
		log_amx( "[UWC3X] Query:: %s", squery );
		return PLUGIN_CONTINUE;
	}
	else
	{
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
	}

	//Free the stuff
	SQL_FreeHandle ( Query );
	SQL_FreeHandle ( SqlConnection );
	return PLUGIN_CONTINUE;
}



public SQLLiteClose ( )
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


