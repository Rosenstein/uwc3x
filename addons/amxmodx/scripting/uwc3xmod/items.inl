/*
	All of the Shared Item Functions will go here
	Each of the Shopmenu Specific items are in their own seperate files
*/

public SetUser_Defined_Item_Values ( )
{
	// Set the custom prices and item effectiveness values for each of the shopmenus
	Set_Shopmenu1_Prices ( );
	Set_Shopmenu1_Values ( );

	Set_Shopmenu2_Prices ( );
	Set_Shopmenu2_Values ( );

	Set_Shopmenu3_Prices ( );
	Set_Shopmenu3_Values ( );

	//Do special stuff for mole
	Initialize_Mole_Custom_Price ( );
}

//item_menu
public Items_Menu( id )
{

	new pos = 0 , menu_body[512];
	new keys = ( 1<<0 )|( 1<<1 )|( 1<<2 )|( 1<<3 )|( 1<<8 )|( 1<<9 );

	pos += format( menu_body[pos] , 511 - pos , "\yItem Options^n^n" );
	pos += format( menu_body[pos] , 511-pos , "\w1. %L ^n" , id, "SHOPMENU" );
	pos += format( menu_body[pos] , 511-pos , "\w2. %L ^n" , id, "SHOPMENU2" );
	pos += format( menu_body[pos] , 511-pos , "\w3. %L ^n" , id, "SHOPMENU3" );
	pos += format( menu_body[pos] , 511-pos , "\w4. %L ^n" , id, "SHOPMENU_SHOW1" );
	pos += format( menu_body[pos] , 511-pos , "\w5. %L ^n" , id, "SHOPMENU_SHOW2" );
	pos += format( menu_body[pos] , 511-pos , "\w6. %L ^n" , id, "SHOPMENU_SHOW3" );
	pos += format( menu_body[pos] , 511-pos , "^n^n\w9. %L" , id, "BACK" );
	pos += format( menu_body[pos] , 511-pos , "^n\w0. %L" , id, "EXIT" );
	show_menu( id , keys , menu_body , -1 );

	return PLUGIN_CONTINUE;
}

//do_itemmenu
public Choose_Items_Menu ( id , key )
{
	switch (key)
	{
		case 0: ShopMenu( id );
		case 1: ShopMenu2( id );
		case 2: ShopMenu3( id );
		case 3: Show_Items_Info1( id );
		case 4: Show_Items_Info2( id );
		case 5: Show_Items_Info3( id );
		//case 8: main_menu( id );
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}


public Shopmenu_canBuy ( id , SHOPMENU , key )
{
	if( CVAR_COMPETITIVE )
	{
		if ( !is_user_alive( id ) )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility( id , print_center , "%L" , id, "ITEM_DEAD" );
			}


			return false;
		}
		else if ( !buytime )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility( id , print_center , "%L" , id, "ITEM_BUYTIME" , ( get_cvar_float( "mp_buytime" ) * 60.0 ) );
			}
			return false;
		}
		else if( !isBuyzone[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print_utility( id , print_center , "%L" , id, "ITEM_BUYZONE" );
			}
			return false;
		}
	}
	else
	{
		if ( SHOPMENU == 0 )
		{
			//nothing goes here , this is just a place holder so that other functions can call this and
			//not go through the validation process below

			return true;
		}
		else
		{
			//The other shopmenu item validations will go here
			//Anything "global" can be set here

			//Can not buy an item as spectator ( your not on ct or t team )
			if( ( get_user_team( id ) != TEAM_T && get_user_team( id ) != TEAM_CT ) )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print_utility( id , print_center , "%L" , id, "ITEM_JOIN_TEAM" );
				}
				return false;
			}

			//Can not buy an item when dead except for tome , scroll and mole
			if( !is_user_alive( id ) )
			{
				if( key != MOLE-1 && key != RESPAWN-1 && key != TOME-1 )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_DEAD" );
					}
					return false;
				}
			}

			if ( key == 9 )
				return false;

			new usermoney = cs_get_user_money( id );

			if ( SHOPMENU == 1 )
			{
				if( key == playeritem[id]-1 && key != TOME-1 )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_OWNS" );
					}
					return false;
				}

				if( key == TOME-1)
				{
					p_tombs = playertombs[id];
					if( CVAR_MAX_TOMES <= p_tombs )
					{
						if( Util_Should_Msg_Client(id) )
						{
							client_print_utility( id , print_center , "%L" , id, "TOO_MANY_TOMES" );
						}
						return false;
					}
				}

				if ( usermoney < itemcost[key] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_NO_MONEY" );
					}
					return false;
				}

			}
			else if( SHOPMENU == 2 )
			{

				if( key == playeritem2[id] -1 && key != REGEN-1 )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_OWNS" );
					}
					return false;
				}

				if( key == RESPAWN-1 && endround )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_ROUND_OVER" );
					}
					return false;
				}

				if ( usermoney < itemcost2[key] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_NO_MONEY" );
					}
					return false;
				}


			}
			else if( SHOPMENU == 3 )
			{
				if( playerCanBuyitem3[id] == 0)
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_WAIT", MOD );
					}
					return false;
				}

				if( key == playeritem3[id] -1 )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_OWNS" );
					}
					return false;
				}

				if ( usermoney < itemcost3[key] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_NO_MONEY" );
					}
					return false;
				}

				if( endround )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "ITEM_ROUND_OVER" );
					}
					return false;
				}

				if( key == DISEASE-1 && !isdiseasedcb[id] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_NO_DISEASE" );
					}
					return false;
				}

				if( key == POISON-1 && !ispoisonedss[id] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_NO_POISON" );
					}
					return false;
				}

				if( key == FIRE-1 && ( isburning[id] == 0 ) && ( isnburning[id] == 0 ) )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_NO_FIRE" );
					}
					return false;
				}
				
				if( key == HEAL-1 )
				{
					if ( !is_user_alive( id ) )
					{
						if( Util_Should_Msg_Client(id) )
						{
							client_print_utility( id , print_center , "%L" , id, "ITEM_DEAD" );
						}

						return false;
					}

					if ( get_user_health ( id ) == maxhealth[id] )
					{
						if( Util_Should_Msg_Client(id) )
						{
							client_print_utility( id , print_center , "%L" , id, "SM3_MAXHEALTH" );
						}
						return false;
					}
				}

				if( key == DEHEX-1 && ( !bHexed[id] ) )
				{
					if( Util_Should_Msg_Client( id ) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_NO_HEX" );
					}

					return false;

				}

				if( key == ROTITEM-1 && !bIsRotting[id] )
				{
					if( Util_Should_Msg_Client(id) )
					{
						client_print_utility( id , print_center , "%L" , id, "SM3_NO_ROT" );
					}
					return false;
				}
			}
		}

	}

	return true;
}


//Give_Items
public Give_Items( parm[2] )
{

	new id = parm[0];

	if ( !is_user_connected( id ) )
		return PLUGIN_CONTINUE;

	// If spawned from vengeance
	if ( p_skills[id][SKILLIDX_VENGEANCE] && !spawnedfromitem[id] )
	{

		//Set vengeance state to completed respawn
		vengeance_state[id] = VENG_DONE;

		new health = ( maxhealth[id] / 2 );

		if ( health < 50 )
			health = 50;

		set_user_health_log( id, health );

	}
	else if( p_skills[id][SKILLIDX_DEVOTION] )
	{
		// Devotion Aura
		set_user_health_log( id, p_devotion[p_skills[id][SKILLIDX_DEVOTION]-1] );
	}
	else
	{
		// All other cases
		set_user_health_log( id , 100 );
	}

	Set_Blink( parm[0] );
	give_items[parm[0]] = true;

	// Give weapons back
	set_task( 0.1 , "weapon_controller" , TASK_WEAPOM_CONTROLLER , parm , 2 );

	give_item( id , "item_suit" );
	give_item( id , "weapon_knife" );

	// [08-29-04] Makes sure defusers get reincarnated - K2mia
	if ( hasdefuse[id] )
		give_item( id , "item_thighpack" );

	// [10-14-04] Makes sure Nightvision get reincarnated - K2mia
	if ( hasnvision[id] )
		cs_set_user_nvg( id , 1 );

	// The following code decides if pistols should be given
	if ( !givepistol )
		return PLUGIN_CONTINUE;

	new wpnList[32] = 0 , number = 0 , foundGlock = false , foundUSP = false;
	get_user_weapons( id , wpnList , number );

	for ( new i = 0; i < number; i++)
	{
		if ( wpnList[i] == CSW_GLOCK18 )
			foundGlock = true;

		if ( wpnList[i] == CSW_USP )
			foundUSP = true;
	}

	if ( get_user_team( id ) == TEAM_T )
	{
		if ( foundGlock )
		{
			return PLUGIN_CONTINUE;
		}
		else
		{
			give_item( id , "weapon_glock18" );
			give_item( id , "ammo_9mm" );
			give_item( id , "ammo_9mm" );
			give_item( id , "ammo_9mm" );
		}
	}

	if ( get_user_team( id ) == TEAM_CT )
	{
		if ( foundUSP )
		{
			return PLUGIN_CONTINUE;
		}
		else
		{
			give_item( id , "weapon_usp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
			give_item( id , "ammo_45acp" );
		}
	}

	return PLUGIN_CONTINUE;
}


public weapon_controller( parm[2] )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new id = parm[0], origin[3] = 0, iweapons[32] = 0 , wpname[32] = 0 , inum = 0;
	new weaponid = 0 , weaponname[20] = 0 , ammoname[20] = 0;
	new bool:reincarnate;
	get_user_weapons( id , iweapons , inum );

	reincarnate = false;

	// Save weapons of people who survived: otherwise the stripper will nab them...
	if( diedlastround[id] == false )
	{
		// LIVED LAST ROUND
		reincarnate = false;
	}

	// Equipement & Eligibility Check for Re-Incarnation
	//if ( diedlastround[id] && ( p_skills[id][SKILLIDX_EQREINC] > 0 ) )
	if ( diedlastround[id] )
	{
		// DIED LAST ROUND
		new Float:randomnumber = random_float( 0.0 , 1.0 );

		if ( p_skills[id][SKILLIDX_EQREINC] && randomnumber <= p_ankh[p_skills[id][SKILLIDX_EQREINC]-1] )
		{
			reincarnate = true;
		}
		else if( give_items[id] )
		{
			reincarnate = true;
			give_items[id] = false;
		}
		else if ( playeritem[id] == ANKH )
		{
			reincarnate = true;
		}
	}

	// Equipement Re-Incarnation: Includes pistols. Also , living ppl
	// need to be re-incarnated.
	if ( reincarnate )
	{
		if( Util_Should_Msg_Client(id) )
		{
			if ( file_exists( "sound/uwc3x/reincarnation.wav" ) == 1 )
				emit_sound( id , CHAN_ITEM , "uwc3x/reincarnation.wav" , 1.0 , ATTN_NORM , 0 , PITCH_NORM );
		}

		// Disarm and Isolate Player Before Re-Incarnation
		get_user_origin( id , origin );
		origin[2] -= 2000;
		set_user_origin( id , origin );

		for( new a = 0; a < inum; ++a )
		{
			if( iweapons[a] != CSW_C4 )
			{
				get_weaponname( iweapons[a] , wpname , 31 );
				engclient_cmd( id , "drop" , wpname );
			}
		}

		engclient_cmd( id , "weapon_knife" );
		origin[2] += 2005;

		if ( armorondeath[id] )
		{
			if ( helmet[id] )
			{
				give_item( id , "item_assaultsuit" );
			}
			else
			{
				give_item( id , "item_kevlar" );
			}

			set_user_armor_log( id , armorondeath[id] );
		}

		if ( playerhasspawned[id] && !reincarnate )
		{
			return PLUGIN_HANDLED;
		}

		if ( hasdefuse[id] )
		{
			give_item( id , "item_thighpack" );
		}

		// [10-14-04] Makes sure Nightvision get reincarnated - K2mia
		if ( hasnvision[id] )
		{
			cs_set_user_nvg( id , 1 );
		}

		new weapon;
		for ( new j = 0; ( j < savednumber[id] ) && ( j < 32 ); ++j )
		{
			weapon = savedweapons[id][j];

			if ( weapon == CSW_M3 || weapon == CSW_XM1014 || weapon == CSW_MP5NAVY ||
			weapon == CSW_TMP || weapon == CSW_P90 || weapon == CSW_MAC10 || weapon == CSW_UMP45 ||
			weapon == CSW_AK47 || weapon == CSW_SG552 || weapon == CSW_M4A1 || weapon == CSW_AUG ||
			weapon == CSW_SCOUT || weapon == CSW_AWP || weapon == CSW_G3SG1 ||
			weapon == CSW_SG550 || weapon == CSW_M249 )
			{
				gotShield[id] = false;
			}
		}

		for ( new j = 0; ( j < savednumber[id] ) && ( j < 32 ); ++j )
		{
			weaponid = savedweapons[id][j];

			if( weaponid == CSW_USP )
			{
				weaponname = "weapon_usp";
				ammoname = "ammo_45acp";
			}
			else if( weaponid == CSW_ELITE )
			{
				weaponname = "weapon_elite";
				ammoname = "ammo_9mm";
			}
			else if( weaponid == CSW_FIVESEVEN )
			{
				weaponname = "weapon_fiveseven";
				ammoname = "ammo_57mm";
			}
			else if( weaponid == CSW_GLOCK18 )
			{
				weaponname = "weapon_glock18";
				ammoname = "ammo_9mm";
			}
			else if( weaponid == CSW_DEAGLE )
			{
				weaponname = "weapon_deagle";
				ammoname = "ammo_50ae";
			}
			else if( weaponid == CSW_P228 )
			{
				weaponname = "weapon_p228";
				ammoname = "ammo_357sig";
			}
			else if ( weaponid == 3 )
			{
				weaponname = "weapon_scout";
				ammoname = "ammo_762nato";
			}
			else if ( weaponid == 4 )
			{
				give_item( id , "weapon_hegrenade" );
			}
			else if ( weaponid == 5 )
			{
				weaponname = "weapon_xm1014";
				ammoname = "ammo_buckshot";
			}
			else if ( weaponid == 7 )
			{
				weaponname = "weapon_mac10";
				ammoname = "ammo_45acp";
			}
			else if ( weaponid == 8 )
			{
				weaponname = "weapon_aug";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 9 )
			{
				give_item( id , "weapon_smokegrenade" );
			}
			else if ( weaponid == 12 )
			{
				weaponname = "weapon_ump45";
				ammoname = "ammo_45acp";
			}
			else if ( weaponid == 13 )
			{
				weaponname = "weapon_sg550";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 14 )
			{
				weaponname = "weapon_galil";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 15 )
			{
				weaponname = "weapon_famas";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 18 )
			{
				weaponname = "weapon_awp";
				ammoname = "ammo_338magnum";
			}
			else if ( weaponid == 19 )
			{
				weaponname = "weapon_mp5navy";
				ammoname = "ammo_9mm";
			}
			else if ( weaponid == 20 )
			{
				weaponname = "";
				ammoname = "";
			}
			else if ( weaponid == 21 )
			{
				weaponname = "weapon_m3";
				ammoname = "ammo_buckshot";
			}
			else if ( weaponid == 22 )
			{
				weaponname = "weapon_m4a1";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 23 )
			{
				weaponname = "weapon_tmp";
				ammoname = "ammo_9mm";
			}
			else if ( weaponid == 24 )
			{
				weaponname = "weapon_g3sg1";
				ammoname = "ammo_762nato";
			}
			else if ( weaponid == 25 )
			{
				if( flashg[id] == 1 )
				{
					give_item( id , "weapon_flashbang" );
				}
				else
				{
					give_item( id , "weapon_flashbang" );
					give_item( id , "weapon_flashbang" );
				}
			}
			else if ( weaponid == 27 )
			{
				weaponname = "weapon_sg552";
				ammoname = "ammo_556nato";
			}
			else if ( weaponid == 28 )
			{
				weaponname = "weapon_ak47";
				ammoname = "ammo_762nato";
			}
			else if ( weaponid == 30 )
			{
				weaponname = "weapon_p90";
				ammoname = "ammo_57mm";
			}
			else
			{
				weaponname = "";
				ammoname = "";
			}

			if ( contain( weaponname , "weapon_" ) == 0 )
			{
				// -1 if no match found , 0 if match
				give_item( id , weaponname );
				give_item( id , ammoname );
				give_item( id , ammoname );
				give_item( id , ammoname );
				give_item( id , ammoname );
				give_item( id , ammoname );
				give_item( id , ammoname );
				give_item( id , ammoname );
			}
		}

		if ( iglow[id][1] < 1 )
		{
			parm[0] = id;
			set_task( 0.1 , "ChangeGlow" , TASK_CHANGE_GLOW2 , parm , 2 );
		}

		iglow[id][1] += 100;
		iglow[id][0] = 0;
		iglow[id][2] = 0;
		iglow[id][3] = 0;

		if ( iglow[id][1]>MAXGLOW )
			iglow[id][1] = MAXGLOW;

		if( Util_Should_Msg_Client( id ) )
		{
			if (CVAR_DMESSAGES)
			{
				log_amx("[UWC3X]::DEBUG_MESSAGES::weapon_controller:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, gmsgFade, id);
			}
			message_begin( MSG_ONE , gmsgFade , {0 , 0 , 0} , id );
			write_short( 1<<10 ); // fade lasts this long duration
			write_short( 1<<10 ); // fade lasts this long hold time
			write_short( 1<<12 ); // fade type ( in / out )
			write_byte( 0 ); // fade red
			write_byte( 255 ); // fade green
			write_byte( 0 ); // fade blue
			write_byte( iglow[id][1] ); // fade alpha
			message_end( );
		}

		// Restore Re-Incarnated Player to the map
		set_user_origin( id , origin );
	}

	if ( is_user_connected( id ) )
	{
		if ( !cs_get_user_nvg( id ) )
			hasnvision[id] = false;

		if ( !cs_get_user_defuse( id ) )
			hasdefuse[id] = false;
	}

	item_functions( parm );
	return PLUGIN_HANDLED;
}

public item_functions( parm[] )
{
	new id = parm[0];

	if ( !is_user_connected( id ) )
		return PLUGIN_CONTINUE;

	if( !hasrespawned[id] && hasmole[id] )
	// [08-19-04] Fixed to prevent respawn Moling from item
	set_task( 0.1 , "Check_spot" , TASK_CHECK_SPOT + 12 , parm , 2 );

	if( diedlastround[id] )
	{
		playeritem[id] = 0;
		playeritem2[id] = 0;
		playeritem3[id] = 0;
		displaylevel( id , 3 );
	}

	diedlastround[id] = false;

	if( get_cvar_num( "sv_gravity" )>650 )
	{
		if ( p_skills[id][SKILLIDX_LEVITATION] && playeritem2[id] != FEATHER )
		{
			// Levitation
			if ( get_user_gravity( id ) != p_levitation[p_skills[id][SKILLIDX_LEVITATION]-1] )
			{
				set_user_gravity( id , p_levitation[p_skills[id][SKILLIDX_LEVITATION]-1] );
			}
		}
		else if ( playeritem2[id] == FEATHER )
		{
			set_user_gravity( id , 0.35 );
		}
		else
		{
			set_user_gravity( id , 1.0 );
		}
	}
	else
	{
		set_user_gravity( id , 1.0 );
	}

	if ( playeritem2[id] == CAT )
	{
		set_user_footsteps( id , 1 );
	}
	else
	{
		set_user_footsteps( id , 0 );
	}

	if( playeritem2[id] != CHAMELEON && skinchanged[id] )
	{
		changeskin( id , 1 );
	}

	if ( task_exists( TASK_REGENERATE + id ) && playeritem2[id] != REGEN )
	{
		remove_task( TASK_REGENERATE + id );
	}

	if ( playeritem[id] == HEALTH )
	{
		set_user_health_log( id , get_user_health( id ) + HEALTHBONUS );
	}

	if( playeritem2[id] == REGEN && !task_exists( 9000 + id ) )
	{
		regenerate( parm );
	}

	if ( playeritem2[id] == HELM )
	{
		set_user_hitzones( 0 , id , 253 );
	}
	else
	{
		set_user_hitzones( 0 , id , 255 );
	}

	if ( playeritem2[id] == CHAMELEON && is_user_alive( id ) )
	{
		changeskin( id , 0 );
	}

	return PLUGIN_CONTINUE;
}


//items
public Show_Items( parm2[2] )
{

	new id = parm2[0];

	//No need to do this for bots, they cant see it anyways
	if( is_user_bot ( id ) )
	{
		return;
	}

	new temp2[300] = "" ;
	new temp3[32] = "";

	if ( ultlearned[id] && !ultimateused[id] && !freezetime )
	{
		format( temp3 , 31 , "[ %L ] ", id, "ULTIMATE_READY" );
	}
	else if ( ultlearned[id] )
	{
		format( temp3 , 31 , "[ %L ] ", id, "ULTIMATE_NOT_READY" );
	}

	/*
		Set default values to false - this assumes that they have nothing to start with, and we will find
		out for sure what they have a little farther down.
	*/

	new bool:bShopMenu1 = false;
	new bool:bShopMenu2 = false;
	new bool:bShopMenu3 = false;

	new bool:HasOne = false;
	new bool:HasTwo = false;
	new bool:HasThree = false;

	if ( playeritem[id] != 0 )
		bShopMenu1 = true;

	if ( playeritem2[id] != 0 )
		bShopMenu2 = true;

	if ( playeritem3[id] != 0 )
		bShopMenu3 = true;

	if( bShopMenu1 )
	{
		HasOne = true;

		if( bShopMenu2 )
		{
			HasTwo = true;

			if( bShopMenu3 )
			{
				HasThree = true;
			}
		}
		else if( bShopMenu3 )
		{
			HasTwo = true;
		}
	}
	else if( bShopMenu2 )
	{
		HasOne = true;

		if( bShopMenu3 )
		{
			HasTwo = true;
		}
	}
	else if( bShopMenu3 )
	{
		HasOne = true;
	}

	/*
		Start building the HUD display message
	*/
	if( HasThree )
	{
		//has items from all three

		//Check if regen so we can display ring count
		if ( playeritem2[id] == REGEN )
		{
			format( temp2 , 127 , "%sMagic Items: %s , %ss x%d and %s" , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"" , rings[id], playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
		}
		else
		{
			format( temp2 , 127 , "%sMagic Items: %s , %s and %s" , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"", playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
		}
	}
	if( HasTwo )
	{
		//has items from two of the three
		if( bShopMenu2 && bShopMenu1 )
		{
			//Check if regen so we can display ring count
			if ( playeritem2[id] == REGEN )
			{
				format( temp2 , 127 , "%sMagic Items: %s and %ss x%d" , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"" , rings[id] );
			}
			else
			{
				format( temp2 , 127 , "%sMagic Items: %s and %s" , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"" );
			}
		}
		else if( bShopMenu2 && bShopMenu3 )
		{
			//Check if regen so we can display ring count
			if ( playeritem2[id] == REGEN )
			{
				format( temp2 , 127 , "%sMagic Items: %ss x%d and %s" , temp3 , playeritem2[id]?shortitemname[playeritem2[id]-1]:"" , rings[id], playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
			}
			else
			{
				format( temp2 , 127 , "%sMagic Items: %s and %s" , temp3 , playeritem2[id]?shortitemname[playeritem2[id]-1]:"" , playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
			}
		}
		else if( bShopMenu1 && bShopMenu3 )
		{
			format( temp2 , 127 , "%sMagic Items: %s and %s" , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" , playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
		}
	}
	else if( HasOne )
	{
		//Only has one shopmenu item, doesnt really matter which one it is, but placing these three just in case

		//we want to change one of them later
		if( bShopMenu1 )
		{
			format( temp2 , 127 , "%sMagic Item: %s " , temp3 , playeritem[id]?shortitemname[playeritem[id]-1]:"" );
		}
		else if( bShopMenu2 )
		{
			//Check if regen so we can display ring count
			if ( playeritem2[id] == REGEN )
			{
				format( temp2 , 127 , "%sMagic Item: %ss x%d " , temp3 , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"", rings[id] );
			}
			else
			{
				format( temp2 , 127 , "%sMagic Item: %s " , temp3 , playeritem2[id]?shortitemname2[playeritem2[id]-1]:"" );
			}
		}
		else if( bShopMenu3 )
		{
			format( temp2 , 127 , "%sMagic Item: %s " , temp3 , playeritem3[id]?shortitemname3[playeritem3[id]-1]:"" );
		}
	}
	else
	{
		//has no items
		format( temp2 , 127 , "%sNo Magic Items ( say /shopmenu )" , temp3 );
	}

	itemsrunning[id] = true;

	// Hud message set based on lowres setting
	if ( lowres[id] )
	{
		set_hudmessage( 255 , 255 , 255 , 0.05 , 0.75 , 2 , 0.02 , 10.0 , 0.01 , 0.1 , 2 );
	}
	else
	{
		set_hudmessage( 255 , 255 , 255 , 0.025 , 0.80 , 2 , 0.02 , 10.0 , 0.01 , 0.1 , 2 );
	}

	if ( is_user_alive( id ) && !endround )
	{
		if( Util_Should_Msg_Client(id) )
		{
			show_hudmessage( id , temp2 );
		}

	}

	set_task( 1.0 , "Show_Items" , TASK_SHOW_ITEMS + id , parm2 , 2 );
}



public In_BuyZone( id )
{
	if( !isBuyzone[id] )
	{
		return false;
	}

	return true;
}


//flashbuy
public Buy_Flash ( id )
{
	if( !In_BuyZone( id ) )
	{
		return PLUGIN_HANDLED;
	}

	return PLUGIN_CONTINUE;
}


//hebuy
public Buy_HE ( id )
{
	if( CVAR_GRENADE_PROTECTION == 0 )
	{
		return PLUGIN_CONTINUE;
	}

	if( !In_BuyZone( id ) )
	{
		return PLUGIN_HANDLED;
	}

	if ( he[id] > 0 )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print_utility( id , print_center , "%L", id, "ONE_NADE" );
		}

		return PLUGIN_HANDLED;
	}
	else
	{
		++he[id];
		return PLUGIN_CONTINUE;
	}

	return PLUGIN_HANDLED;
}


public got_defuse( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	hasdefuse[id] = true;
	return PLUGIN_CONTINUE;
}

public armor_type( id )
{

	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	if ( read_data( 1 ) )
	{
		helmet[id] = true;
		hassuit[id] = true;
	}
	else
	{
		helmet[id] = false;
		hassuit[id] = true;
	}

	// Check if helmet helps w/ skin bonus
	Task_Check_Skin_Bonus( id );

	return PLUGIN_CONTINUE;
}

public check_weap( id )
{
	new weapon = ( read_data( 1 ) );

	if ( weapon == 25 )
	{
		 ++flashg[id];
	}

	if ( weapon == CSW_M3 || weapon == CSW_XM1014 || weapon == CSW_MP5NAVY || weapon == CSW_TMP ||
	weapon == CSW_P90 || weapon == CSW_MAC10 || weapon == CSW_UMP45 || weapon == CSW_AK47 ||
	weapon == CSW_SG552 || weapon == CSW_M4A1 || weapon == CSW_AUG || weapon == CSW_SCOUT ||
	weapon == CSW_AWP || weapon == CSW_G3SG1 || weapon == CSW_SG550 || weapon == CSW_M249 )
	{
		gotShield[id] = false;
	}

	new wpnid = read_data(2);
	new name[32];
	get_user_name( id , name, 31);

	if(unammo[id])
	{
		new clip = read_data(3);

		if( ( IsWeaponPrimary( wpnid ) || IsWeaponSecondary( wpnid ) ) && (clip == 0) )
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug:: check_weap ->unammo [ %s ] = Primary or Secondary weapon - Reloading", name );
			}

			reloadAmmo(id);
		}
		else
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug:: check_weap ->unammo [ %s ] = NOT Primary or Secondary weapon", name );
			}

		}
	}

	//See if the have the ice bomb skill
	if( p_skills[id][SKILLIDX_ICENADE] )
	{
		//If they dont already have one, check to see if they do
		if( !hasFrostNade[id] )
			CheckFrostNades( id );

		//If the weapon is a smoke grenade
		if( IsWeaponSmokeGrenade( wpnid ) && hasFrostNade[id] )
		{

			if( Util_Should_Msg_Client( id ) )
			{
				// flash icon if frost grenade is out
				if (CVAR_DMESSAGES)
				{
					log_amx("[UWC3X]::DEBUG_MESSAGES::check_weap:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, gmsgStatusIcon, id);
				}
				message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},id);
				write_byte(2); // status (0=hide, 1=show, 2=flash)
				write_string("dmg_cold"); // sprite name
				write_byte(FROST_R); // red
				write_byte(FROST_G); // green
				write_byte(FROST_B); // blue
				message_end();
			}
		}
		//Else they just have it, but its not out
		else if(hasFrostNade[id])
		{

			if( Util_Should_Msg_Client( id ) )
			{
				if (CVAR_DMESSAGES)
				{
					log_amx("[UWC3X]::DEBUG_MESSAGES::check_weap:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, gmsgStatusIcon, id);
				}
				message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},id);
				write_byte(1); // status (0=hide, 1=show, 2=flash)
				write_string("dmg_cold"); // sprite name
				write_byte(FROST_R); // red
				write_byte(FROST_G); // green
				write_byte(FROST_B); // blue
				message_end();
			}
		}
	}

	if(isChilled[id])
		chill_player(id);

	if(isFrozen[id])
		freeze_player(id);

	return PLUGIN_CONTINUE;
}

public change_weapon( id )
{

	if ( !uwc3x || !is_user_connected( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	if (freezetime || !is_user_alive(id))
	{
		return PLUGIN_HANDLED;
	}

	if ( playeritem2[id] == INFERNO )
	{
		// Gives person a grenade if they weren't just given one
		new wpnList[32] = 0, number = 0, foundNade = false, parm[2];
		get_user_weapons( id , wpnList , number );

		for ( new i = 0; i < number && !foundNade; i++ )
		{
			if ( wpnList[i] == CSW_HEGRENADE )
			{
				foundNade = true;
			}
		}

		parm[0] = id;

		if( !justgivennade[id] && !foundNade )
		{
			justgivennade[id] = true;
			Nade_Timer( parm );
		}
	// End nade giving segment
	}

	new clipamount = 0;
	new ammoamount = 0;
	new weaponnum = 0;
	weaponnum = ( get_user_weapon( id , clipamount , ammoamount ) );

	if ( !is_user_connected( id ) )
		return PLUGIN_CONTINUE;

	if ( p_skills[id][SKILLIDX_INVIS] && playeritem[id] == CLOAK )
	{
		// Invisibility now uses the cloakstack array to get the ammount to remove from the cloak ( obe )
		new Float:tmpInvis = float( cloakstack[p_skills[id][SKILLIDX_INVIS]-1] );
		new Float:tmpCloak = float( CLOAKINVISIBILITY );
		new tmpBoth = floatround( tmpCloak - tmpInvis );

		if ( weaponnum == 29 )
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , tmpBoth/2 );
			knifeselected[id] = true;
		}
		else
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , tmpBoth + INVIS_STACK_OFFSET );
			knifeselected[id] = false;
		}

	}
	else if ( p_skills[id][SKILLIDX_INVIS] )
	{
		// Invisibility
		if ( weaponnum == 29 )
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , p_invisibility[p_skills[id][SKILLIDX_INVIS]-1]/2 );
			knifeselected[id] = true;
		}
		else
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , p_invisibility[p_skills[id][SKILLIDX_INVIS]-1] );
			knifeselected[id] = false;
		}
	}
	else if ( playeritem[id] == CLOAK )
	{
		if ( weaponnum == 29 )
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , CLOAKINVISIBILITY/2 );
			knifeselected[id] = true;
		}
		else
		{
			set_user_rendering( id , kRenderFxNone , 0 , 0 , 0 , kRenderTransTexture , CLOAKINVISIBILITY );
			knifeselected[id] = false;
		}
	}
	else
	{
		set_user_rendering( id );
	}

	#if STEAM_POWERED

	 if ( !freezetime && !slowed[id] && !stunned[id] )
	 {
		//scout
		if ( weaponnum == 3 )
		{
			if ( zoomed[id] == 1 )
			{
				set_user_maxspeed( id , 220.0 );
			}
			else
			{
				set_user_maxspeed( id , 260.0 ); //220 zoomed
			}
		}
		else if ( weaponnum == 4 ){ //hegrenad
			set_user_maxspeed( id , 260.0 );
		}
		else if ( weaponnum == 5 ){ //xm1014
			set_user_maxspeed( id , 230.0 );
		}
		else if ( weaponnum == 7 ){ //mac10
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 8 ){ //aug - bollup
			set_user_maxspeed( id , 240.0 );
		}
		else if ( weaponnum == 9 ){ //smokegrenade
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 12 ){ //ump45
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 13 )
		{
			//sg550
			if ( zoomed[id] == 1 )
				set_user_maxspeed( id , 150.0 );
			else
				set_user_maxspeed( id , 210.0 ); //150 zoomed
		}
		else if ( weaponnum == 18 )
		{
			//awp
			if ( zoomed[id] == 1 )
				set_user_maxspeed( id , 150.0 );
			else
				set_user_maxspeed( id , 210.0 ); //150 zoomed
		}
		else if ( weaponnum == 19 ){ //mp5
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 20 ){ //m249
			set_user_maxspeed( id , 220.0 );
		}
		else if ( weaponnum == 21 ){ //auto-shotty ( m3 )
			set_user_maxspeed( id , 240.0 );
		}
		else if ( weaponnum == 14 ){ //galil
			set_user_maxspeed( id , 240.0 );
		}
		else if ( weaponnum == 15 ){ //famas
			set_user_maxspeed( id , 240.0 );
		}
		else if ( weaponnum == 22 ){ //M4A1
			set_user_maxspeed( id , 230.0 );
		}
		else if ( weaponnum == 23 ){ //TMP
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 24 ){ //G3SG1
			if ( zoomed[id] == 1 )
				set_user_maxspeed( id , 150.0 );
			else
				set_user_maxspeed( id , 210.0 ); //150 zoomed
		}
		else if ( weaponnum == 25 ){ //flashbang
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 27 ){ //sg552
			set_user_maxspeed( id , 235.0 );
		}
		else if ( weaponnum == 28 ){ //AK47
			set_user_maxspeed( id , 221.0 );
		}
		else if ( weaponnum == 30 ){ //P90
			set_user_maxspeed( id , 245.0 );
		}
		else if ( weaponnum == 1 ){ //p228
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 10 ){ //elite
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 11 ){ //fiveseven
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 26 ){ //deagle
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 16 ){ //usp
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 17 ){ //glock
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 29 ){ //knife
			set_user_maxspeed( id , 250.0 );
		}
		else if ( weaponnum == 6 ){ //BOMB
			set_user_maxspeed( id , 250.0 );
		}
	}
	#endif

	new parm[1];
	parm[0] = id;
	Set_Speed( parm );
	new wpnid = read_data(2);
	new name[32];
	get_user_name( id , name, 31);

	if(unammo[id])
	{
		new clip = read_data(3);

		if( ( IsWeaponPrimary( wpnid ) || IsWeaponSecondary( wpnid ) ) && (clip == 0) )
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug:: check_weap ->unammo [ %s ] = Primary or Secondary weapon - Reloading", name );
			}

			reloadAmmo(id);
		}
		else
		{
			if ( CVAR_DEBUG_MODE )
			{
				log_amx( "[UWC3X] Debug:: check_weap ->unammo [ %s ] = NOT Primary or Secondary weapon", name );
			}

		}
	}

	//See if the have the ice bomb skill
	if( p_skills[id][SKILLIDX_ICENADE] )
	{
		//If they dont already have one, check to see if they do
		if( !hasFrostNade[id] )
			CheckFrostNades( id );

		//If the weapon is a smoke grenade
		if( IsWeaponSmokeGrenade( wpnid ) )
		{
			// flash icon if frost grenade is out
			if( hasFrostNade[id] )
			{
				if( Util_Should_Msg_Client( id ) )
				{
					if (CVAR_DMESSAGES)
					{
						log_amx("[UWC3X]::DEBUG_MESSAGES::change_weapon:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, gmsgStatusIcon, id);
					}
					message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},id);
					write_byte(2); // status (0=hide, 1=show, 2=flash)
					write_string("dmg_cold"); // sprite name
					write_byte(FROST_R); // red
					write_byte(FROST_G); // green
					write_byte(FROST_B); // blue
					message_end();
				}
			}
		}
		else if(hasFrostNade[id])
		{
			if( Util_Should_Msg_Client( id ) )
			{
				if (CVAR_DMESSAGES)
				{
					log_amx("[UWC3X]::DEBUG_MESSAGES::change_weapon:: dest=%d; msg_type=%d; player=%d;", MSG_ONE, gmsgStatusIcon, id);
				}
				message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},id);
				write_byte(1); // status (0=hide, 1=show, 2=flash)
				write_string("dmg_cold"); // sprite name
				write_byte(FROST_R); // red
				write_byte(FROST_G); // green
				write_byte(FROST_B); // blue
				message_end();
			}
		}
	}

	if(isChilled[id])
		chill_player(id);

	if(isFrozen[id])
		freeze_player(id);

	return PLUGIN_CONTINUE;
}

public saveweapons( id )
{
	armorondeath[id] = get_user_armor( id );

	// Equipment Reincarnation
	for ( new i = 0; i<32; ++i )
	{
		savedweapons[id][i] = 0;
	}

	savednumber[id] = 0;
	get_user_weapons( id , savedweapons[id] , savednumber[id] );

	return PLUGIN_CONTINUE;
}

public hook_drop( id )
{
	new parm[1];
	parm[0] = id;
	remove_task( 2300 + id , 0 );
	set_task( 0.1 , "check_shield2" , 2300 + id , parm , 1 );

	return PLUGIN_CONTINUE;
}