

stock __HUDCHAT_R = 255;
stock __HUDCHAT_G = 255;
stock __HUDCHAT_B = 255;

stock __HUDCHAT_CHANNEL = 2;

stock Float:__HUDCHAT_REMOVETIME = 5.0;

stock Array:__HUDCHAT_MESSAGES[33];
stock __HUDCHAT_MSGCOUNT[33];

stock __HUDCHAT_MAXPLAYERS;

stock hudchat_init()
{
	__HUDCHAT_MAXPLAYERS = get_maxplayers();
	
	for(new i = 1; i <= __HUDCHAT_MAXPLAYERS; i++)
	{
		__HUDCHAT_MESSAGES[i] = ArrayCreate(__HUDCHAT_MAXMSGLEN);
		__HUDCHAT_MSGCOUNT[i] = 0;
	}
}

stock hudchat_end()
{
	for(new i = 1; i <= __HUDCHAT_MAXPLAYERS; i++)
	{
		ArrayDestroy(__HUDCHAT_MESSAGES[i]);
		__HUDCHAT_MSGCOUNT[i] = 0;
		
		remove_task(i + __HUDCHAT_TASKID_REMOVE);
		remove_task(i + __HUDCHAT_TASKID_UPDATE);
	}
}

stock hudchat_update(id)
{
	if(id)
	{
		new taskid = id + __HUDCHAT_TASKID_UPDATE;
		
		__TaskShowHudChat(taskid);
		
		remove_task(taskid);
		set_task(__HUDCHAT_UPDATEINTERVAL, "__TaskShowHudChat", taskid, .flags = "b");
	}
	else
	{
		for(id = 1; id <= __HUDCHAT_MAXPLAYERS; id++)
		{
			hudchat_update(id);
		}
	}
}

stock hudchat_get_maxlines()
{
	return __HUDCHAT_MAXLINES;
}

stock hudchat_set_color(r, g, b)
{
	__HUDCHAT_R = (r & 255);
	__HUDCHAT_G = (g & 255);
	__HUDCHAT_B = (b & 255);
}

stock hudchat_get_color(&r, &g, &b)
{
	r = __HUDCHAT_R;
	g = __HUDCHAT_G;
	b = __HUDCHAT_B;
}

stock hudchat_set_removetime(Float:_time)
{
	if(_time > 0.0 )
	{
		__HUDCHAT_REMOVETIME = _time;
	}
}

stock Float:hudchat_get_removetime()
{
	return __HUDCHAT_REMOVETIME;
}

stock hudchat_set_channel(channel)
{
	__HUDCHAT_CHANNEL = channel;
}

stock hudchat_get_channel()
{
	return __HUDCHAT_CHANNEL;
}

stock hudchat_show(id, const msg[], any:...)
{
	new message[__HUDCHAT_MAXMSGLEN];
	vformat(message, charsmax(message), msg, 3);
	
	if(id)
	{
		while(__HUDCHAT_MSGCOUNT[id] >= __HUDCHAT_MAXLINES)
		{
			ArrayDeleteItem(__HUDCHAT_MESSAGES[id], 0);
			__HUDCHAT_MSGCOUNT[id]--;
		}
		
		ArrayPushString(__HUDCHAT_MESSAGES[id], message);
		__HUDCHAT_MSGCOUNT[id]++;
		
		new taskid = id + __HUDCHAT_TASKID_REMOVE;
		
		remove_task(taskid);
		set_task(__HUDCHAT_REMOVETIME, "__TaskRemoveHudChat", taskid);
	}
	else
	{
		for(id = 1; id <= __HUDCHAT_MAXPLAYERS; id++)
		{
			hudchat_show(id, "%s", message);
		}
	}
}

stock hudchat_clear(id)
{
	if(id)
	{
		ArrayClear(__HUDCHAT_MESSAGES[id]);
		__HUDCHAT_MSGCOUNT[id] = 0;
		
		remove_task(id + __HUDCHAT_TASKID_REMOVE);
		remove_task(id + __HUDCHAT_TASKID_UPDATE);
	}
	else
	{
		for(id = 1; id <= __HUDCHAT_MAXPLAYERS; id++)
		{
			hudchat_clear(id);
		}
	}
}

stock user_spawn( index )
{
	return spawn(index);
}
stock cmd_target2 ( id,const arg[] ) 
{
	new player = find_player ( "bl", arg );

	if ( player )
	{
		if ( player != find_player ( "blj", arg ) )
		{
			console_print ( id,"There are more clients matching to your argument" );
			return 0;
		}
	}
	else if ( ( player = find_player ( "c",arg ) )==0 && arg[0]=='#' && arg[1] )
	{
		player = find_player ( "k",str_to_num ( arg[1] ) );
	}

	if ( !player )
	{
		console_print ( id, "Client with that name or userid not found" );
		return 0;
	}

	return player;
}

stock ExplodeString ( p_szOutput[][], p_nMax, p_nSize, p_szInput[], p_szDelimiter )
{
	new nIdx = 0, l = strlen ( p_szInput );
	new nLen = ( 1 + copyc ( p_szOutput[nIdx], p_nSize, p_szInput, p_szDelimiter ) );

	while ( ( nLen < l ) && ( ++nIdx < p_nMax ) )
	{
		nLen += ( 1 + copyc ( p_szOutput[nIdx], p_nSize, p_szInput[nLen], p_szDelimiter ) );
	}

	return;
}

stock sq ( num ) 
{
	return ( num * num );
}

stock diff ( num,num2 )
{
	if ( num>num2 )
	{
		return ( num-num2 );
	}
	else
	{
		return ( num2-num );
	}

	return 0;
}

stock str_break ( const String[], Left[], Right[], lMax, rMax )
{
	new bool:quote_flag = false;
	new bool:done_flag = false;
	new left_pos = 0;
	new right_pos = 0;
	new i;
	new hold[] = "'^"x";

	copy ( Left, lMax, "" );
	copy ( Right, rMax, "" );

	for ( i=0; i<=strlen ( String )-1; i++ ) 
	{
		if ( equali ( String[i], "^"", 1 ) ) 
		{
			quote_flag = true;
		}
		else if ( ( equali ( String[i], "^"", 1 ) ) && ( quote_flag ) ) 
		{
			quote_flag = false;
		}

		if ( ( equali ( String[i], " ", 1 ) ) && ( !quote_flag ) && ( !done_flag ) ) 
		{
			done_flag = true;
			i++;
		}

		if ( !done_flag && !equali ( String[i], "^"", 1 ) ) 
		{
			if ( left_pos < lMax ) 
			{
				setc ( Left[left_pos], 1, String[i] )
				if ( equali ( Left[left_pos], "'", 1 ) ) 
				{
					setc ( Left[left_pos], 1, hold[1] );
				}
				left_pos++;
			}
		}
		else
		{
			if ( right_pos < rMax && !equali ( String[i], "^"", 1 ) ) 
			{
				setc ( Right[right_pos], 1, String[i] );

				if ( equali ( Right[right_pos], "'", 1 ) ) 
				{
					setc ( Right[right_pos], 1, hold[1] );
				}

				right_pos++;
			}
		}
	}

	Left[left_pos] = 0;
	Right[right_pos] = 0;

	return true;
}


stock replaceall ( text[], const LEN, const WHAT[], const WITH[] ) 
{
	while ( contain ( text, WHAT ) != -1 )
	{
		server_print ( "replacing a ' ..." );
		replace ( text, LEN, WHAT, WITH );
	}
}

stock getMaxClipAmmo(wpnid)
{
	new clipammo = 0;
	switch (wpnid)
	{
		case CSW_P228 : clipammo = 13;
		case CSW_SCOUT : clipammo = 10;
		case CSW_HEGRENADE : clipammo = 0;
		case CSW_XM1014 : clipammo = 7;
		case CSW_C4 : clipammo = 0;
		case CSW_MAC10 : clipammo = 30;
		case CSW_AUG : clipammo = 30;
		case CSW_SMOKEGRENADE : clipammo = 0;
		case CSW_ELITE : clipammo = 15;
		case CSW_FIVESEVEN : clipammo = 20;
		case CSW_UMP45 : clipammo = 25;
		case CSW_SG550 : clipammo = 30;
		case CSW_GALI : clipammo = 35;
		case CSW_FAMAS : clipammo = 25;
		case CSW_USP : clipammo = 12;
		case CSW_GLOCK18 : clipammo = 20;
		case CSW_AWP : clipammo = 10;
		case CSW_MP5NAVY : clipammo = 30;
		case CSW_M249 : clipammo = 100;
		case CSW_M3 : clipammo = 8;
		case CSW_M4A1 : clipammo = 30;
		case CSW_TMP : clipammo = 30;
		case CSW_G3SG1 : clipammo = 20;
		case CSW_FLASHBANG : clipammo = 0;
		case CSW_DEAGLE : clipammo = 7;
		case CSW_SG552 : clipammo = 30;
		case CSW_AK47 : clipammo = 30;
		case CSW_KNIFE : clipammo = 0;
		case CSW_P90 : clipammo = 50;
	}
	return clipammo;
}

public add_grenade_owner( owner ) 
{
	for ( new i = 0; i < 32; i++ ) 
	{
		if ( grenade[i] == 0 ) 
		{
			grenade[i] = owner;
			return;
		}
	}
}

stock get_grenade_owner() 
{
	new which = grenade[0]
	for ( new i = 1; i < 32; i++ ) 
	{
		grenade[i - 1] = grenade[i];
	}

	grenade[31] = 0;

	return which;
}

//
//Stocks ripped from xtrafun.inc for AMXx
//
//Gets the velocity of an entity */
stock get_entity_velocity(index, velocity[3]) 
{
	new Float:vector[3];
	entity_get_vector(index, EV_VEC_velocity, vector);
	FVecIVec(vector, velocity);
}

//Sets the velocity of an entity
stock set_entity_velocity(index, velocity[3]) 
{
	new Float:vector[3];
	IVecFVec(velocity, vector);
	entity_set_vector(index, EV_VEC_velocity, vector);
}

stock set_rendering2(index, fx=kRenderFxNone, r=255, g=255, b=255, render=kRenderNormal, amount=16)
{
#if defined engine
	return set_rendering(index,fx,r,g,b,render,amount)
#else
	set_pev(index, pev_renderfx, fx);
	new Float:RenderColor[3];
	RenderColor[0] = float(r);
	RenderColor[1] = float(g);
	RenderColor[2] = float(b);
	set_pev(index, pev_rendercolor, RenderColor);
	set_pev(index, pev_rendermode, render);
	set_pev(index, pev_renderamt, float(amount));
	return 1;
#endif
}

stock Spawn_Ent(const classname[]) 
{
	new ent = engfunc(EngFunc_CreateNamedEntity, engfunc(EngFunc_AllocString, classname))
	set_pev(ent, pev_origin, {0.0, 0.0, 0.0})    
	dllfunc(DLLFunc_Spawn, ent)
	return ent
}

stock Float:Vec2DLength( Float:Vec[2] )  
{ 
	return floatsqroot(Vec[x1]*Vec[x1] + Vec[y1]*Vec[y1] )
}

stock bool:UTIL_In_FOV(id,target)
{
	if (Find_Angle(id,target,9999.9) > 0.0)
		return true
	
	return false
}
stock Float:Find_Angle(Core,Target,Float:dist)
{
	new Float:vec2LOS[2]
	new Float:flDot	
	new Float:CoreOrigin[3]
	new Float:TargetOrigin[3]
	new Float:CoreAngles[3]
	
	pev(Core,pev_origin,CoreOrigin)
	pev(Target,pev_origin,TargetOrigin)
	
	if (get_distance_f(CoreOrigin,TargetOrigin) > dist)
		return 0.0
	
	pev(Core,pev_angles, CoreAngles)
	
	for ( new i = 0; i < 2; i++ )
		vec2LOS[i] = TargetOrigin[i] - CoreOrigin[i]
	
	new Float:veclength = Vec2DLength(vec2LOS)
	
	//Normalize V2LOS
	if (veclength <= 0.0)
	{
		vec2LOS[x1] = 0.0
		vec2LOS[y1] = 0.0
	}
	else
	{
		new Float:flLen = 1.0 / veclength;
		vec2LOS[x1] = vec2LOS[x1]*flLen
		vec2LOS[y1] = vec2LOS[y1]*flLen
	}
	
	//Do a makevector to make v_forward right
	engfunc(EngFunc_MakeVectors,CoreAngles)
	
	new Float:v_forward[3]
	new Float:v_forward2D[2]
	get_global_vector(GL_v_forward, v_forward)
	
	v_forward2D[x1] = v_forward[x1]
	v_forward2D[y1] = v_forward[y1]
	
	flDot = vec2LOS[x1]*v_forward2D[x1]+vec2LOS[y1]*v_forward2D[y1]
	
	if ( flDot > 0.5 )
	{
		return flDot
	}
	
	return 0.0	
}


/**
 * Joins an array of strings into one string, with a "join" string inserted in
 * between each given string.  This function complements ExplodeString.
 *
 * @param strings       An array of strings.
 * @param numStrings    Number of strings in the array.
 * @param join          The join string to insert between each string.
 * @param buffer        Output buffer to write the joined string to.
 * @param maxLength     Maximum length of the output buffer.
 * @return              Number of bytes written to the output buffer.
 */
stock implode_strings(const strings[][], numStrings, const join[], buffer[], maxLength)
{
	new total, length, part_length;
	new join_length = strlen(join);
	for (new i=0; i<numStrings; i++)
	{
		length = copy(buffer[total], maxLength-total, strings[i]);
		total += length;
		if (length < part_length)
		{
			break;
		}
		if (i != numStrings - 1)
		{
			length = copy(buffer[total], maxLength-total, join);
			total += length;
			if (length < join_length)
			{
				break;
			}
		}
	}
	return total;
}