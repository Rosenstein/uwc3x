/*
	SHOPMENU
*/

//set prices
public Set_Shopmenu1_Prices ( )
{
	// [07-31-04] Check for shop item cost overrides from config file
	if ( CVAR_SM1_PRICE_ANKH )
	{
		itemcost[ANKH-1] = CVAR_SM1_PRICE_ANKH;
	}

	if ( CVAR_SM1_PRICE_BOOTS )
	{
		itemcost[BOOTS-1] = CVAR_SM1_PRICE_BOOTS;
	}

	if ( CVAR_SM1_PRICE_CLAWS )
	{
		itemcost[CLAWS-1] = CVAR_SM1_PRICE_CLAWS;
	}

	if ( CVAR_SM1_PRICE_CLOAK )
	{
		itemcost[CLOAK-1] = CVAR_SM1_PRICE_CLOAK;
	}

	if ( CVAR_SM1_PRICE_MASK )
	{
		itemcost[MASK-1] = CVAR_SM1_PRICE_MASK;
	}

	if ( CVAR_SM1_PRICE_NECKLACE )
	{
		itemcost[IMMUNITY-1] = CVAR_SM1_PRICE_NECKLACE;
	}

	if ( CVAR_SM1_PRICE_FROST )
	{
		itemcost[FROST-1] = CVAR_SM1_PRICE_FROST;
	}

	if ( CVAR_SM1_PRICE_HEALTH )
	{
		itemcost[HEALTH-1] = CVAR_SM1_PRICE_HEALTH;
	}

	if ( CVAR_SM1_PRICE_TOMEXP )
	{
		itemcost[TOME-1] = CVAR_SM1_PRICE_TOMEXP;
	}
}

public Set_Shopmenu1_Values ( )
{
	// [07-31-04] Check for other setting overrides from config file
	if ( CVAR_SM1_ITEM_BOOT_SPEED )
	{
		BOOTSPEED = CVAR_SM1_ITEM_BOOT_SPEED;
	}

	if ( CVAR_SM1_ITEM_FROST_SPEED )
	{
		FROSTSPEED = CVAR_SM1_ITEM_FROST_SPEED;
	}

	if ( CVAR_SM1_ITEM_MASK_PERCENT )
	{
		MASKPERCENT = CVAR_SM1_ITEM_MASK_PERCENT;
	}

	if ( CVAR_SM1_ITEM_CLAWS_DAMAGE )
	{
		CLAWSOFATTACK = CVAR_SM1_ITEM_CLAWS_DAMAGE;
	}

	if ( CVAR_SM1_ITEM_CLOAK_INVIS )
	{
		CLOAKINVISIBILITY = CVAR_SM1_ITEM_CLOAK_INVIS;
	}

	if ( CVAR_SM1_ITEM_HEATH_BONUS )
	{
		HEALTHBONUS = CVAR_SM1_ITEM_HEATH_BONUS;
	}
}

//itemsinfo
public Show_Items_Info1( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;
	
	new temp[1024] , pos = 0;
	pos += format( temp[pos] , 1024-pos , "<body bgcolor = #000000><font color = #FFB000>" );
	pos += format( temp[pos] , 1024-pos , "%L:<p><ul>", id, "SHOPMENU1_HEADER" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_ANKH" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_BOOTS" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_CLAWS" , CLAWSOFATTACK );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_CLOAK" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_MASK" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_NECKLACE" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_ORB" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li>" , id, "SHOPMENU1_PERIPHAT" );
	pos += format( temp[pos] , 1024-pos , "<li>%L</li></ul>" , id, "SHOPMENU1_TOME" );

	show_motd( id , temp , "Shopmenu Item Information" );
	return PLUGIN_CONTINUE;
}

//shopmenu
public ShopMenu( id )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new pos = 0;
	new keys = (1<<0|1<<1|1<<2|1<<3|1<<4|1<<5|1<<6|1<<7|1<<8|1<<9);
	new menu_body[512];
	
	pos += format( menu_body[pos], 511 - pos, "\yBuy Item\R$ Cost^n^n" );
	
	for ( new i = 0; i < 9; i++ )
	{
		pos += format( menu_body[pos], 511 - pos, "\w%d. %s\y\R%d^n", i + 1 , itemname[i], itemcost[i] );
	}
	
	pos += format( menu_body[pos], 511 - pos, "^n\w0. Exit" );
	show_menu( id, keys, menu_body, -1 );
	return PLUGIN_HANDLED;
}

//buy_item
public Buy_Item( id , key )
{
	
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( !Shopmenu_canBuy ( id, 1, key ) )
		return PLUGIN_HANDLED;
	
	new usermoney = cs_get_user_money( id );

	if ( key == TOME - 1 )
	{
		cs_set_user_money( id, usermoney - itemcost[key], 1 );
		new p_tomes = playertombs[id];
		p_tomes++;

		if ( CVAR_DEBUG_MODE )
		{
			new tempVar[64];
			get_user_name ( id, tempVar, 63 );
			log_amx( "[UWC3X] DEBUG :: Buy_Item: Buy Tome -> Player: %s Current Amount: %d New Amount: %d", tempVar, playertombs[id], p_tomes);
		}

		playertombs[id] = p_tomes;

		// Give XP bonus for buying Tome of Experience
		xpgiven = xpgiven_lev[p_level[id]];
		new iXP = ( XPBONUS + xpgiven );
		playerxp[id] += iXP;
	
		if( Util_Should_Msg_Client(id) )
		{
			if ( file_exists( "sound/uwc3x/tomes.wav" ) == 1 )
				emit_sound( id, CHAN_ITEM, "uwc3x/tomes.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );

			//client_print_utility ( id, print_chat, "%L", id, "SHOPMENU1_TOME2", MOD, iXP );
			hudchat_show(id, "%L", id, "SHOPMENU1_TOME2", iXP);
			hudchat_update(id);
		}
	
		displaylevel( id, 3 );
		return PLUGIN_HANDLED;
	}
	else
	{
	
		cs_set_user_money( id, usermoney - itemcost[key], 1 );
	
		// Remove health bonus after buying new item
		if ( playeritem[id] == HEALTH )
			set_user_health_log( id, get_user_health( id ) - HEALTHBONUS );
	
		playeritem[id]= key + 1;
	
		if ( playeritem[id] == HEALTH )
		{
			// Give health bonus for buying periapt of health
			set_user_health_log( id, get_user_health( id ) + HEALTHBONUS );
	
			if ( CVAR_DEBUG_MODE )
			{
				new name[32];
				get_user_name(id, name, 31);
				log_amx( "[UWC3X] DEBUG :: In buy_item() :: [%s] Bought Health Has=(%d) Max=(%d)",name, get_user_health(id), maxhealth[id] );
			}
		}
	}

	if( Util_Should_Msg_Client(id) )
	{
		if ( file_exists( "sound/uwc3x/shopmenu/sm_pickupitem.wav" ) == 1 )
			emit_sound (id, CHAN_STATIC, "uwc3x/shopmenu/sm_pickupitem.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
	}

	displaylevel( id, 3 );	
	return PLUGIN_HANDLED;
}
