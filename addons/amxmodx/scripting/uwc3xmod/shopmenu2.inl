/*
	SHOPMENU 2
*/

public Set_Shopmenu2_Prices ( )
{
	if ( CVAR_SM2_PRICE_RESPAWN )
	{
		itemcost2[RESPAWN-1] = CVAR_SM2_PRICE_RESPAWN;
	}

	if ( CVAR_SM2_PRICE_MOLEPROTECT )
	{
		itemcost2[PROTECTANT-1] = CVAR_SM2_PRICE_MOLEPROTECT;
	}

	if ( CVAR_SM2_PRICE_HELM )
	{
		itemcost2[HELM-1] = CVAR_SM2_PRICE_HELM;
	}

	if ( CVAR_SM2_PRICE_AMULETCAT )
	{
		itemcost2[CAT-1] = CVAR_SM2_PRICE_AMULETCAT;
	}

	if ( CVAR_SM2_PRICE_FEATHER )
	{
		itemcost2[FEATHER-1] = CVAR_SM2_PRICE_FEATHER;
	}

	if ( CVAR_SM2_PRICE_INFERNO )
	{
		itemcost2[INFERNO-1] = CVAR_SM2_PRICE_INFERNO;
	}

	if ( CVAR_SM2_PRICE_RINGS )
	{
		itemcost2[REGEN-1] = CVAR_SM2_PRICE_RINGS;
	}

	if ( CVAR_SM2_PRICE_CHAMELEON )
	{
		itemcost2[CHAMELEON-1] = CVAR_SM2_PRICE_CHAMELEON;
	}
}

public Set_Shopmenu2_Values ( )
{

}


//itemsinfo2( id )
public Show_Items_Info2( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;
	
	new temp[1024] , pos = 0;
	pos += format( temp[pos] , 1024-pos , "<body bgcolor = #000000><font color = #FFB000>" );
	pos += format( temp[pos] , 1024-pos , "%L:<p><ul>" , id, "SHOPMENU2_HEADER" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_SCROLL" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_MP" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_AMULET" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_SOCK" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMEUN2_HELM" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_GLOVE" , CVAR_GLOVE_TIMER );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_RINGS" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU2_CHAMELEON" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li></ul>" , id, "SHOPMENU2_MOLE" );
	
	show_motd( id , temp , "Shopmenu2 Item Information" );
	return PLUGIN_CONTINUE;
}

//shopmenu2
public ShopMenu2( id )
{	
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new pos = 0;
	new keys = (1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6|1<<7|1<<8|1<<9);
	new menu_body[512];
	
	pos += format( menu_body[pos], 511 - pos, "\yBuy An Item\R$ Cost^n^n" );
	
	for ( new i = 0; i < 9; i++ )
	{
		pos += format( menu_body[pos], 511 - pos, "\w%d. %s\y\R%d^n", i + 1, itemname2[i], itemcost2[i] );
	}
	
	pos += format( menu_body[pos], 511 - pos, "^n\w0. %L", id, "EXIT" );
	show_menu( id, keys, menu_body, -1 );
	return PLUGIN_HANDLED;
}

//buy_item2
public Buy_Item2( id , key )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( !Shopmenu_canBuy ( id , 2 , key ) )
		return PLUGIN_HANDLED;
	
	new usermoney = cs_get_user_money( id );

	if ( playeritem2[id] == CAT )
	{
		set_user_footsteps( id , 0 );
	}

	if ( playeritem2[id] == FEATHER )
	{
		set_user_gravity( id , 1.0 );
	}

	if ( playeritem2[id] == HELM )
	{
		set_user_hitzones( 0 , id , 255 );
	}
	
	if ( playeritem2[id] == CHAMELEON )
	{
		changeskin( id , 1 );
	}
	
	if ( playeritem2[id] != REGEN )
	{
		if( task_exists( TASK_REGENERATE + id ) )
			remove_task( TASK_REGENERATE + id );
			
		rings[id] = 0;
	}

	if ( playeritem2[id] != INFERNO )
	{
		if( task_exists( TASK_NADE_TIMER + id ) )
			remove_task( TASK_NADE_TIMER + id );
	}
	
	playeritem2[id] = key + 1;
	
	if ( playeritem2[id] == CHAMELEON && is_user_alive( id ) )
	{
		changeskin( id , 0 );
	}
	
	if ( playeritem2[id] == HELM )
	{
		set_user_hitzones( 0 , id , 253 );
	}
	
	if ( playeritem2[id] == CAT )
	{
		set_user_footsteps( id , 1 );
	}
	
	if ( playeritem2[id] == FEATHER )
	{
		set_user_gravity( id , 0.35 );
	}
	
	if ( playeritem2[id] == RESPAWN && !is_user_alive( id ) )
	{
		if( get_user_team( id ) == TEAM_T || get_user_team( id ) == TEAM_CT )
		{
			new parm[2];
			parm[0] = id;
			parm[1] = 6;
			set_task( 0.2 , "func_spawn" , 2 , parm , 2 );
			spawnedfromitem[id] = true;
			playeritem2[id] = 0;
			playeritem[id] = 0;
			playeritem3[id] = 0;
		}
	}
		
	if ( playeritem2[id] == INFERNO )
	{
		if ( UWC3X_MapDisableCheck( "gloves.cfg" ) )
		{
			if( !givenade )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print_utility ( id, print_chat, "%L", id, "GLOVES_ITEM_DISABLED", MOD );
					emit_sound( id, CHAN_ITEM, "uwc3x/ultimateerror.wav", 0.8, ATTN_NORM, 0, PITCH_NORM );
				}
			
				// Fix for Gloves bug which still allowed it to be bought
				playeritem2[id] = 0;
				return PLUGIN_HANDLED;
			}
			else
			{
				new parm[2];
				parm[0] = id;
				Gloves_Give_Nade( parm );
				nadetime[id] = CVAR_GLOVE_TIMER;
			}
		}
		else
		{
			new parm[2];
			parm[0] = id;
			Gloves_Give_Nade( parm );
			nadetime[id] = CVAR_GLOVE_TIMER;
		}
	}
	
	if ( playeritem2[id] == REGEN )
	{
		new parm[2];
		parm[0] = id;
		if ( rings[id]<5 )
		{
			++rings[id];

			if( !task_exists( TASK_REGENERATE + id ) )
			{
				regenerate( parm );
			}
		}
		else
		{
			if( Util_Should_Msg_Client(id) )
			{
				hudchat_show(id, "%L", id, "RINGS_X5_MORE");
				hudchat_update(id);
				//client_print_utility( id , print_center , "%L", id, "RINGS_X5_MORE" );
			}
		
			return PLUGIN_HANDLED;
		}
	}
	
	if ( playeritem2[id] == MOLE )
	{
		
		if( CVAR_ENABLE_MOLE )
		{
			hasmole[id] = true;
		}
		else
		{
			if( CVAR_ADMINSKILL_BUY_MOLE )
			{
				if ( !( get_user_flags( id )& CVAR_ADMIN_SKILL_FLAG ) ) 
				{
					hasmole[id] = false;
					if( Util_Should_Msg_Client(id) )
					{
						hudchat_show(id, "%L", id, "MOLE_DISABLED_ADMIN");
						hudchat_update(id);
						//client_print_utility( id , print_center , "%L", id, "MOLE_DISABLED_ADMIN" );
					}
					
					return PLUGIN_HANDLED;
				}
				else
				{
					hasmole[id] = true;
				}
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					//client_print_utility( id , print_center , "%L", id, "MOLE_DISABLED_PLAYER" );
					hudchat_show(id, "%L", id, "MOLE_DISABLED_PLAYER");
					hudchat_update(id);
				}
			
				return PLUGIN_HANDLED;
			}
		} 
	}
	
	cs_set_user_money( id , usermoney - itemcost2[key] , 1 );
	
	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists( "sound/uwc3x/shopmenu/sm_pickupitem.wav" ) == 1 )
			emit_sound( id , CHAN_STATIC , "uwc3x/shopmenu/sm_pickupitem.wav" , 1.0 , ATTN_NORM , 0 , PITCH_NORM );
	}
	
	displaylevel( id , 3 );
	return PLUGIN_HANDLED;
}


//giveheifnothas( parm[2] ) 
public Gloves_Give_Nade ( parm[2] ) 
{
	new id = parm[0];
	new wpnList[32] = 0, number = 0, foundNade = false;
	get_user_weapons( id , wpnList , number );
	
	for ( new i = 0; i < number && !foundNade; i++ ) 
	{
		if ( wpnList[i] == CSW_HEGRENADE )
			foundNade = true;
	}

	if ( !foundNade && is_user_alive( id ) )
	{
		if( Util_Should_Msg_Client(id) )
		{
			//set_hudmessage( 0, 100, 0, 0.05, 0.65, 2, 0.02, 3.0, 0.01, 0.1, 3);
			//show_hudmessage( id , "%L", id, "GLOVE_NADE_GIVEN" );
			hudchat_show(id, "%L", id, "GLOVE_NADE_GIVEN");
			hudchat_update(id);
		}
	
		give_item( id , "weapon_hegrenade" );
	}

	justgivennade[id] = false;
	return PLUGIN_CONTINUE;
}

//nadetimer
public Nade_Timer ( parm[2] )
{
	new id = parm[0];
	set_hudmessage( 0, 100, 0, 0.05, 0.65, 2, 0.02, 10.0, 0.01, 0.1, 3);
	
	if( playeritem2[id] != INFERNO )
	{
		if( Util_Should_Msg_Client(id) )
		{
			show_hudmessage( id , "" );
		}
	
		return PLUGIN_HANDLED;
	}
	
	if( nadetime[parm[0]] != 0 )
	{
		if( Util_Should_Msg_Client(id) )
		{
			//show_hudmessage( id , "%L", id, "GLOVE_TIMER", nadetime[parm[0]] );
			hudchat_show(id, "%L", id, "GLOVE_TIMER", nadetime[parm[0]]);
			hudchat_update(id);
		}
	}
	
	nadetime[parm[0]] -= 1;
	
	if ( !is_user_alive( id ) )
	{
		if( Util_Should_Msg_Client(id) )
		{
			//show_hudmessage( id , "If you could manage to stay alive I could provide you with more nades!" );
			hudchat_show(id, "%L", id, "GLOVE_DIED");
			hudchat_update(id);
		}
	
	}
	
	if ( nadetime[parm[0]] != -1 && is_user_alive( parm[0] ) )
	{
		set_task( 1.0 , "Nade_Timer" , TASK_NADE_TIMER + id , parm , 2 );
	}
	
	if ( nadetime[parm[0]] == -1 )
	{
		Gloves_Give_Nade( parm );
		nadetime[id] = CVAR_GLOVE_TIMER;
		return PLUGIN_HANDLED;
	}
	
	return PLUGIN_CONTINUE;
}

public rings5( id )
{
	if ( !is_user_alive( id ) )
	{
		return PLUGIN_HANDLED;
	}
	
	new usermoney, parm[2];
	parm[0] = id;
	
	if ( playeritem2[id] == CAT )
	{
		set_user_footsteps( id , 0 );
	}
		
	if ( playeritem2[id] == FEATHER )
	{
		set_user_gravity( id , 1.0 );
	}
	
	if ( playeritem2[id] == HELM )
	{
		set_user_hitzones( 0 , id , 255 );
	}
	
	if ( playeritem2[id] == CHAMELEON )
	{
		changeskin( id , 1 );
	}
	

	while(rings[id]<5)
	{
		usermoney = cs_get_user_money(id);

		if(usermoney<itemcost2[REGEN-1])
			break;

		cs_set_user_money(id,usermoney-itemcost2[REGEN-1],1);
		++rings[id];
		playeritem2[id]=REGEN;

		if(!task_exists(TASK_REGENERATE+id))
			regenerate(parm);
	}

	displaylevel(id,3);
	return PLUGIN_HANDLED;
}

