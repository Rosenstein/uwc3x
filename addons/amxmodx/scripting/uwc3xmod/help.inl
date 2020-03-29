/*
	Help skills

*/

public skills_info( id, tier )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[4096] = "", pos = 0;
	new startidx = ( ( tier - 1 ) * SKILLS_PER_SET ) + 1;
	new endidx = startidx + ( SKILLS_PER_SET - 1 );

	pos+= format( temp[pos], 4096 - pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR );
	pos+= format( temp[pos], 4096 - pos, "<b>Skill Listings: Page %d</b>: <p><ol>", tier );

	for ( new i = startidx; i <= endidx; i++ )
	{
		new j = sortedskills[i];

		switch (j)
		{
			case SKILLIDX_VAMPIRIC:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "VAMPIRIC_DESC", MakeValuesMinMaxFloat(p_vampiric, skill_limits[j]) );
			case SKILLIDX_LEVITATION:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "LEVITATION_DESC", MakeValuesMinMaxFloat(p_levitation, skill_limits[j]) );
			case SKILLIDX_DEVOTION:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "DEVOTION_DESC", MakeValuesMinMax(p_devotion, skill_limits[j], "%d to %d") );
			case SKILLIDX_EQREINC:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "REINCARNATION_DESC", ImplodeSkillValuesFloat(p_ankh, skill_limits[j]) );
			case SKILLIDX_HEALWAVE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "HEALINGWAVE_DESC", MakeValuesMinMaxFloat(p_heal, skill_limits[j], "%.2f sec to %.2f sec", 1.0) );
			case SKILLIDX_SIPHON:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SIPHONMANA_DESC", MakeValuesMinMaxFloat(p_mana, skill_limits[j]) );
			case SKILLIDX_IMPALE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "IMPALE_DESC", MakeValuesMinMaxFloat(p_impale, skill_limits[j]) );
			case SKILLIDX_LSKIN:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "LEATHERSKIN_DESC", MakeValuesMinMaxFloat(p_lskin, skill_limits[j], "%.2f sec to %.2f sec", 1.0) );
			case SKILLIDX_UNHOLY:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "UNHOLY_DESC", MakeValuesMinMaxFloat(p_unholy, skill_limits[j], "%.0f to %.0f", 1.0) );
			case SKILLIDX_BASH:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BASH_DESC", MakeValuesMinMaxFloat(p_bash, skill_limits[j]) );
			case SKILLIDX_CRITSTRIKE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CRITSTRIKE_DESC", MakeValuesMinMaxFloat(p_critical, skill_limits[j]) );
			case SKILLIDX_REPAIR:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "REPAIRARMOR_DESC" );
			case SKILLIDX_BANISH:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BANISH_DESC", MakeValuesMinMaxFloat(p_banish, skill_limits[j]) );
			case SKILLIDX_HEX:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "HEX_DESC", MakeValuesMinMaxFloat(p_hex, skill_limits[j]) );
			case SKILLIDX_SAMMO:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SIPHONAMMO_DESC", MakeValuesMinMaxFloat(p_ammo, skill_limits[j]) );
			case SKILLIDX_CARAPACE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SPIKEDCARAPACE_DESC", MakeValuesMinMaxFloat(p_spiked, skill_limits[j]) );
			case SKILLIDX_MEND:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "MENDWOUNDS_DESC" );
			case SKILLIDX_EVASION:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "EVASION_DESC", MakeValuesMinMaxFloat(p_evasion, skill_limits[j]), DEX_EVADE_BONUS * 100 );
			case SKILLIDX_TRUESHOT:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "TRUESHOT_DESC", MakeValuesMinMaxFloat(p_trueshot, skill_limits[j]) );
			case SKILLIDX_SSKIN:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "STEELSKIN_DESC" );
			case SKILLIDX_CARRION:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CARRIONBEETLES_DESC", MakeValuesMinMaxFloat(p_carrion, skill_limits[j]) );
			case SKILLIDX_SSTRIKE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SHADOWSTRIKE_DESC", MakeValuesMinMaxFloat(p_shadow, skill_limits[j]) );
			case SKILLIDX_ENTANGLE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "ENTANGLEROOTS_DESC" );
			case SKILLIDX_FSTRIKE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "FLAMESTRIKE_DESC" );
			case SKILLIDX_DISHEX:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "DISPELLHEX_DESC" );
			case SKILLIDX_CRITGREN:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CRITICALGRENADE_DESC", MakeValuesMinMaxFloat(p_grenade, skill_limits[j]) );
			case SKILLIDX_SERPWARD:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SEPENTWARD_DESC", ImplodeSkillValues(p_serpent, skill_limits[j]) );
			case SKILLIDX_THORNS:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "THORNSAURA_DESC", MakeValuesMinMaxFloat(p_thorns, skill_limits[j]) ) ;
			case SKILLIDX_INVIS:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "INVISIBILITY_DESC" );
			case SKILLIDX_TELEPORT:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "TELEPORT_DESC" );
			case SKILLIDX_VOODOO:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BIGBADVOODOO_DESC" );
			case SKILLIDX_FAN:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "FANOFKNIVES_DESC", ImplodeSkillValuesFloat(p_fan, skill_limits[j]) );
			case SKILLIDX_VENGEANCE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "VENGANCE_DESC" );
			case SKILLIDX_BLINK:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BLINK_DESC", ImplodeSkillValuesFloat(p_blink, skill_limits[j]) ) ;
			case SKILLIDX_PHOENIX:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "PHEONIX_DESC", ImplodeSkillValuesFloat(p_phoenix, skill_limits[j]) );
			case SKILLIDX_NAPALM:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "NAPALMGRENADE_DESC" );
			case SKILLIDX_SUICIDE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SUICIDEBOMB_DESC" );
			case SKILLIDX_LIGHTNING:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CHAINLIGHTNING_DESC" );
			case SKILLIDX_DECOY:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "DECOY_DESC" );
			case SKILLIDX_TEAMSHIELD:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SIV_DESC", MakeValuesMinMax(p_ShieldMaxDamage, skill_limits[j]) );
			case SKILLIDX_JUMPKICK:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "JKICK_DESC" );
			case SKILLIDX_MULTIJUMP:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "MJUMP_DESC" );
			case SKILLIDX_CAT:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CAT_DESC" );
			case SKILLIDX_ROT:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "ROT_DESC", MakeValuesMinMaxFloat(p_rotchance, skill_limits[j]) );
			case SKILLIDX_DEPOWER:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "DEPOWER_DESC" );
			case SKILLIDX_CLOAK:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CLOAK_DESC" );
			case SKILLIDX_CRIPPLE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CRIPPLE_DESC" );
			case SKILLIDX_BLIND:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BLIND_DESC" );
			case SKILLIDX_LOCUST:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "LOCUST_DESC" );
			case SKILLIDX_DISORIENT:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "DISORIENT_DESC");
			case SKILLIDX_UAMMO:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "UAMMO_DESC" );
			case SKILLIDX_EARTHQUAKE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "EARTHQUAKE_DESC" );
			case SKILLIDX_SMITE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SMITE_DESC" );
			case SKILLIDX_CLUSTERNADE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "CLUSTERNADE_DESC" );
			case SKILLIDX_ICENADE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "ICENADE_DESC" );
			case SKILLIDX_SPLITTER:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "SPLITTER_DESC" );
			case SKILLIDX_HOOK:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "HOOK_DESC" );
			case SKILLIDX_GRAB:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "GRAB_DESC" );
			case SKILLIDX_ROPE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "ROPE_DESC" );
			case SKILLIDX_FATAL:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "FATAL_DESC", MakeValuesMinMaxFloat(p_fatal_chance, skill_limits[j]), MakeValuesMinMaxFloat(p_fatal_damage, skill_limits[j]), CVAR_FATAL_CHANCE * 100 );	
			case SKILLIDX_BLESS:
                pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "BLESS_DESC" );
			case SKILLIDX_MINE:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "MINE_DESC" );
			case SKILLIDX_NEWSKILL16:
				pos+= format( temp[pos], 4096-pos, "<li>%L<p>", id, "NEWSKILL16_DESC" );
		}
	}

	pos+= format( temp[pos], 4096 - pos, "</ol><p>" );

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_skillsdesc%d.html", whofile, tier );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Skills Information" );
	return PLUGIN_HANDLED;
}

MakeValuesMinMax(values[], len, formatStr[] = "%d to %d")
{
	const size = 32;
	new result[size];
	
	format(result, size, formatStr, values[0], values[len - 1]);
	
	return result;
}

MakeValuesMinMaxFloat(Float:values[], len, formatStr[] = "%.0f%% to %.0f%%", Float:modifier = 100.0)
{
	const size = 32;
	new result[size];
	
	format(result, size, formatStr, values[0] * modifier, values[len - 1] * modifier);
	
	return result;
}

ImplodeSkillValues(values[], len, formatStr[] = "%d")
{
	const outerSize = 64;
	const innerSize = 8;
	new result[outerSize * innerSize];
	new pValues[outerSize][innerSize];
	
	for (new i = 0; i < len; i++)
	{
		format(pValues[i], innerSize, formatStr, values[i]);
	}
	
	implode_strings(pValues, len, ", ", result, sizeof(result));
	
	return result;
}

ImplodeSkillValuesFloat(Float:values[], len, formatStr[] = "%.0f%%", Float:modifier = 100.0)
{
	const outerSize = 64;
	const innerSize = 8;
	new result[outerSize * innerSize];
	new pValues[outerSize][innerSize];
	
	for (new i = 0; i < len; i++)
	{
		format(pValues[i], innerSize, formatStr, values[i] * modifier);
	}
	
	implode_strings(pValues, len, ", ", result, sizeof(result));
	
	return result;
}


//public show_news( id )
//{
//
//	new temp[4096];
//	new pos = 0;
//	pos += format(temp[pos], 4096-pos, "<body scroll='no' bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
//	pos += format(temp[pos], 2048-pos, "<table border=0><tr><td>");
//	pos += format(temp[pos], 2048-pos, "<center><b>Ultimate Warcraft3 Expansion</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>" );
//	pos += format(temp[pos], 4096-pos, "<b>Latest News About Ultimate Warcraft3 Expansion</b><br>");
//	pos += format(temp[pos], 4096-pos, "<b>http://www.Yaur.com/ - See forums for complete ChangeLog</b><br><ul>");
//	pos += format(temp[pos], 4096-pos, "<li>[06-01-07] Added Multi Lingual.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[03-10-07] Added Admin Only skills, enable or disable mole cvar.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[03-10-07] Added DropSkill and revised XP routines for Mend, Repair, Dispell. Added XP Gain for Healing Wave.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[10-30-04] Necklaces no longer protect against serpent wards.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[10-24-04] Testing Teleport Immunity issues bugfix. Testing Mask of Death bugfix. Mirror damage skills/evasion bug fixed. Testing fix for skill/attrib/health known reset issue. Testing bugfix for Vengeance/Phoenix overlap. Fixed Ultimate-status HUD message. Playerskills has been replaced by /who, added /whois playername command to display player character sheets.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[10-10-04] Many run-time errors fixed, thanks to Hellion and Kamikaze for sending their bug reports and error logs!<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-27-04] Fixed objectives bug which awarded XP to dead players (pffft). Skillcount bug should now be fixed, players with incorrect skillsets will be forced to reset.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-23-04] Testing fixes for skillcount being out of sync (auto-reset), insane player health bug. Testing fixes for objective/winning XP award bugs. Version change to v1.0.0RC1 . Fixed /deletexp command. New commands: saveattribs, saveresists, saveskills, saveall<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-14-04] Serious Injury XP bonus bug fixed. Voodoo end of round bug fixed.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-07-04] Big Changes! Attributes and Resistances now have server limits, Beta1 now limits players to 20 attribute pts and 250 resistance pts -- spend them wisely.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-06-04] New animations for Napalm hits and new teleport animations for Gate ultimate. steve modified the Carrion Beetles bubble animation. Medic alert gfx, Armorsmith alert gfx added, live testing.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[9-03-04] Crit strike/Trueshot backfire damage modified. Medic alerts now issues in sprite-mode as well as text-mode. UWC3 welcomes 'steve french' to the plugin dev team, and with him his replacement model for the Entangling Roots effect and replacement Carrion Beetles animated sprite, woot!<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[8-29-04] Equip Reincarnation fixed for failures due to Bomb Explosion, Defusers should always reincarnate now, grenades may still have some erratic respawn issues. Vengeance ultimate cooldown added, so ultimates will become available again after vengeance-based respawn.<p>");
//	pos += format(temp[pos], 4096-pos, "<li>[8-22-04] Testing new bug fix for disease and poison resistance against Carrion Beetles and Shadow Strike<p>");
//	pos += format(temp[pos], 4096-pos, "</ul></td></tr></table>");
//
//	if( CVAR_WRITE_HTML )
//	{
//		new whofile[64];
//		get_configsdir( whofile, 63 );
//		format( whofile, 63, "%s/uwc3x_news.html", whofile );
//
//		if ( file_exists( whofile ) )
//		{
//			delete_file( whofile );
//		}
//
//		write_file( whofile, temp ) ;
//	}
//
//	show_motd( id, temp, "UWC3X News");
//	return PLUGIN_CONTINUE;
//}
//

//public main_menu( id )
//{
//
//	if ( !uwc3x )
//	{
//		return PLUGIN_HANDLED;
//	}
//
//	new pos = 0, menu_body[512];
//	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<9);
//	pos += format(menu_body[pos], 511-pos, "\yUWC3X: Main Menu^n^n");
//	pos += format( menu_body[pos], 511-pos, "\w1. %L^n", id, "MENUITEM1" );
//	pos += format( menu_body[pos], 511-pos, "\w2. %L^n", id, "MENUITEM2" );
//	pos += format( menu_body[pos], 511-pos, "\w3. %L^n", id, "MENUITEM3" );
//	pos += format( menu_body[pos], 511-pos, "\w4. %Ls^n", id, "MENUITEM4" );
//	pos += format( menu_body[pos], 511-pos, "\w5. %L^n", id, "MENUITEM5" );
//	pos += format( menu_body[pos], 511-pos, "\w6. %L^n", id, "MENUITEM6" );
//
//	if ( !CVAR_ADMIN_DISABLE_ADMINMENU && ( get_user_flags( id ) & CVAR_ADMIN_DEFAULT_FLAG ) )
//	{
//		pos += format( menu_body[pos], 511-pos, "\w7. %L^n", id, "MENUITEM7" );
//	}
//
//	pos += format( menu_body[pos], 511-pos, "^n\w0. %L", id, "EXIT" );
//	show_menu( id, keys, menu_body, -1);
//	return PLUGIN_CONTINUE;
//}
//
public uwc3x_menu( id, key )
{
	switch ( key )
	{
		case 0: Menu_Skills( id );
		case 1: Items_Menu( id );
		case 2: help_menu( id );
		case 3: uwc3x_credits( id );
		case 4: uwc3x_commands( id );
		case 5: character_sheet( id );
		case 6: admin_menu( id );
		default: return PLUGIN_HANDLED;
	}
	return PLUGIN_HANDLED;
}

public change_race( id )
{
	new temp[2048], pos = 0;
	pos += format( temp[pos], 2048-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format( temp[pos], 2048-pos, "<table border=0><tr><td>");
	pos += format( temp[pos], 2048-pos, "<center><b>Ultimate Warcraft3 Expansion</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>" );
	pos += format( temp[pos], 2048-pos, "%L<p>", id, "CHANGERACE1" );
	pos += format( temp[pos], 2048-pos, "%L<p>", id, "CHANGERACE2" );
	pos += format( temp[pos], 2048-pos, "%L<p>", id, "CHANGERACE3" );
	pos += format( temp[pos], 2048-pos, "</td></tr></table>");
	show_motd( id, temp, "Ultimate Warcraft3 Expansion" );
	return PLUGIN_CONTINUE;
}

public help_menu( id )
{
	new pos = 0, menu_body[1024];
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9);
	pos += format( menu_body[pos], 1024-pos, "\yHelp Menu^n^n");
	pos += format( menu_body[pos], 1024-pos, "\w1. %L^n", id, "HELPMENU1" );
	pos += format( menu_body[pos], 1024-pos, "\w2. %L^n", id, "HELPMENU2" );
	pos += format( menu_body[pos], 1024-pos, "\w3. %L^n", id, "HELPMENU3" );
	pos += format( menu_body[pos], 1024-pos, "\w4. %L^n", id, "HELPMENU4" );
	pos += format( menu_body[pos], 1024-pos, "\w5. %L^n", id, "HELPMENU5" );
	pos += format( menu_body[pos], 1024-pos, "\w6. %L^n", id, "HELPMENU6" );
	//pos += format( menu_body[pos], 1024-pos, "\w7. %L^n", id, "HELPMENU7" );
	//pos += format( menu_body[pos], 1024-pos, "\w8. %L^n", id, "HELPMENU8" );
	pos += format( menu_body[pos], 1024-pos, "^n^n\w9. %L", id, "BACK" );
	pos += format (menu_body[pos], 1024-pos, "^n\w0. %L", id, "EXIT" );

	show_menu(id,keys,menu_body,-1);
	return PLUGIN_CONTINUE;
}

//public do_helpmenu( id, key )
//{
//	switch ( key )
//	{
//	 case 0: uwc3x_info( id );
//	 case 1: uwc3x_ultimates( id );
//	 //case 2: uwc3x_credits( id );
//	 //case 3: show_news( id );
//	 case 4: uwc3x_attributes( id );
//	 case 5: uwc3x_resistances( id );
//	 //case 6: uwc3x_tips( id );
//	 //case 7: uwc3x_tips2( id );
//	 //case 8: main_menu( id );
//	 default: return PLUGIN_HANDLED;
//	}
//
//	return PLUGIN_HANDLED;
//}

public admin_menu( id )
{
	if (!(get_user_flags(id) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if( id != 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_console, "%L", id, "NO_ACCESS");
			}

			return PLUGIN_HANDLED;
		}
	}

	if ( CVAR_ADMIN_DISABLE_ADMINMENU )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_console, "%L", id, "ADMINMENU_OFF" );
		}

		return PLUGIN_HANDLED;
	}

	new pos = 0, i, menu_body[512], menu_items[3][32];
	new keys = (1<<0)|(1<<1)|(1<<8)|(1<<9);

	menu_items[0]= "Give Individual Players XP";
	menu_items[1]= "Give Multiple Players XP";
	/*menu_items[2]= "Save everyone's XP"*/

	pos += format(menu_body[pos], 511-pos, "\yAdmin Menu^n^n");
	for (i = 0; i<2; i++)
	{
		pos += format(menu_body[pos], 511-pos, "\w%d. %s^n",i+1,menu_items[i]);
	}

	pos += format(menu_body[pos], 511-pos, "^n^n\w9. Back");
	pos += format(menu_body[pos], 511-pos, "^n\w0. Exit");
	show_menu(id,keys,menu_body,-1);

	return PLUGIN_HANDLED;
}

public do_adminmenu( id, key )
{
	switch ( key )
	{
		case 0:
		{
			g_menuOption[id] = 1;
			g_menuSettings[id] = 50;
			playerxp_menu( id, g_menuPosition[id] = 0 );
		}
		case 1:
		{
			g_menuOption[id] = 1;
			g_menuSettings[id] = 50;
			teamxp_menu( id );
		}
		//case 2: server_cmd("amx_savexp @ALL")
		//case 8: main_menu( id );
		default: return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}

public playerxp_menu( id, pos )
{
	if ( pos < 0 )
	{
		admin_menu( id );
		return PLUGIN_CONTINUE;
	}

	get_players( g_menuPlayers[id], g_menuPlayersNum[id] );
	new menuBody[512], b = 0, i, name[32], team[4], start = pos * 7, temp;

	if ( start >= g_menuPlayersNum[id] )
	{
		start = pos = g_menuPosition[id] = 0;
	}

	temp = format(menuBody,511, "\yGive Players XP\R%d/%d^n\w^n",pos+1,(g_menuPlayersNum[id] / 7 + ((g_menuPlayersNum[id] % 7) ? 1 : 0 )));

	new len = temp, end = start + 7, keys = (1<<9)|(1<<7);
	if (end > g_menuPlayersNum[id])
	{
		end = g_menuPlayersNum[id];
	}

	for( new a = start; a < end; ++a )
	{
		i = g_menuPlayers[id][a];
		get_user_name( i, name, 31 );
		get_user_team( i, team, 3 );
		keys |= (1<<b);
		len += format(menuBody[len],511-len,"\w%d. %s^n\w",++b,name);
	}

	len += format( menuBody[len], 511-len, "^n8. Give %d XP^n", g_menuSettings[id] );

	if (end != g_menuPlayersNum[id])
	{
		format(menuBody[len],511-len,"^n9. More...^n0. %s", pos ? "Back" : "Back");
		keys |= (1<<8);
	}
	else
	{
		format(menuBody[len],511-len,"^n0. %s", pos ? "Back" : "Exit");
	}

	show_menu( id, keys, menuBody );
	return PLUGIN_CONTINUE;
}
public do_playerxpmenu(id,key){

	switch(key)
	{
		case 7:
		{
			++g_menuOption[id];
			if (g_menuOption[id]>6)
			{
				g_menuOption[id]=1;
			}
			switch(g_menuOption[id])
			{
				case 1: g_menuSettings[id] = 500;
				case 2: g_menuSettings[id] = 1000;
				case 3: g_menuSettings[id] = 5000;
				case 4: g_menuSettings[id] = 10000;
				case 5: g_menuSettings[id] = 50000;
				case 6: g_menuSettings[id] = 100000;
			}
			playerxp_menu(id,g_menuPosition[id]);
		}
		case 8: playerxp_menu(id,++g_menuPosition[id]);
		case 9: playerxp_menu(id,--g_menuPosition[id]);
		default:
		{
			new player = g_menuPlayers[id][g_menuPosition[id] * 7 + key];

			new name[32];
			new pname[32];
			get_user_name(id, name, 31);
			get_user_name(player, pname, 31);

			log_amx( "[UWC3X] [%s] %s used Admin-Menu XP [%s] for %s", MOD, name, g_menuSettings[id], pname );

			if( Util_Should_Msg_Client(id) )
			{
				client_print(player, print_chat, "[%s] The admin just awarded you %d experience.",MOD,g_menuSettings[id]);
			}

			playerxp[player]+=g_menuSettings[id];
			displaylevel(player,1);
			playerxp_menu(id,g_menuPosition[id]);
		}
	}
	return PLUGIN_HANDLED;
}

public teamxp_menu( id )
{
	new pos = 0, i, menu_body[512], menu_items[3][32];
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<7)|(1<<8)|(1<<9);

	menu_items[0]= "Terrorist";
	menu_items[1]= "Counter-Terrorists";
	menu_items[2]= "Everyone";

	pos += format(menu_body[pos], 511-pos, "\yTeam XP Menu^n^n");
	for (i = 0; i<3; i++)
	{
		pos += format(menu_body[pos], 511-pos, "\w%d. %s^n",i+1,menu_items[i]);
	}
	pos += format(menu_body[pos], 511-pos,"^n8. Give %d XP^n",g_menuSettings[id]);
	pos += format(menu_body[pos], 511-pos, "^n^n\w9. Back");
	pos += format(menu_body[pos], 511-pos, "^n\w0. Exit");
	show_menu(id,keys,menu_body,-1);

	return PLUGIN_CONTINUE;
}

public do_teamxpmenu(id,key){

  // [10-08-04] Added logging of amx_givexp() command - K2mia
  new name[32];
  get_user_name(id, name, 31);

  switch(key){
   case 0:{
     log_amx( "[UWC3X] [%s] %s used Admin-Menu XP [%d] for team Terrorist", MOD, name, g_menuSettings[id] );
     server_cmd("amx_givexp @TERRORIST %d", g_menuSettings[id]);
     teamxp_menu(id);
   }
   case 1:{
     log_amx( "[UWC3X] [%s] %s used Admin-Menu XP [%d] for team CT", MOD, name, g_menuSettings[id] );
     server_cmd("amx_givexp @CT %d",g_menuSettings[id]);
     teamxp_menu(id);
   }
   case 2:{
     log_amx( "[UWC3X] [%s] %s used Admin-Menu XP [%d] for EVERYONE", MOD, name, g_menuSettings[id] );
     server_cmd("amx_givexp @ALL %d",g_menuSettings[id]);
     teamxp_menu(id);
   }
   case 7:{
     ++g_menuOption[id];
     if (g_menuOption[id]>6){
      g_menuOption[id]=1;
     }
     switch(g_menuOption[id]){
      case 1: g_menuSettings[id] = 50;
      case 2: g_menuSettings[id] = 100;
      case 3: g_menuSettings[id] = 500;
      case 4: g_menuSettings[id] = 1000;
      case 5: g_menuSettings[id] = 5000;
      case 6: g_menuSettings[id] = 10000;
     }
     teamxp_menu(id);
   }
   case 8: admin_menu(id);
   case 9: return PLUGIN_HANDLED;
   default: return PLUGIN_HANDLED;
  }

  return PLUGIN_HANDLED;
}

public uwc3x_commands( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[4096], pos = 0;

	pos += format(temp[pos], 4096-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 4096-pos, "<center><table border=1 cellpadding=3 cellspacing=3><tr><td>");
	pos += format(temp[pos], 4096-pos, "<center><b>Ultimate Warcraft3 Expansion</center><p>" );
	pos += format(temp[pos], 4096-pos, "<center><b>%L</b></center><p>", id, "COMMANDS_HEADER" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HEADER2" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP3" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP4" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP5" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP6" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP7" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP8" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP9" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP10" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP11" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP25" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP17" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP18" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP21" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP22" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP23" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP24" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP19" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP20" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP13" );
	pos += format(temp[pos], 4096-pos, "%L<br>", id, "COMMANDS_HELP12" );
	pos += format(temp[pos], 4096-pos, "</td></tr></table></center>" );

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_commands.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Commands");
	return PLUGIN_CONTINUE;

}

public uwc3x_credits( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[4096], pos = 0;

	pos += format(temp[pos], 4096-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 4096-pos, "<center><table border=1 cellpadding=3 cellspacing=3><tr><td>");
	pos += format(temp[pos], 4096-pos, "<center><b>Ultimate Warcraft3 Expansion</b><br></center>");
	pos += format(temp[pos], 4096-pos, "<p>*************************************************************************************");
	pos += format(temp[pos], 4096-pos, "*<center>Original by K2mia with portions by Dumb and the Yaur.com community ");
	pos += format(temp[pos], 4096-pos, "<br />Modifed by and maintained by -=[Yaur]=--<br />");
	pos += format(temp[pos], 4096-pos, "<b><a href='http://www.Yaur.com'>http://www.Yaur.com</a></b><br />");
	pos += format(temp[pos], 4096-pos, "</center>*************************************************************************************");
	pos += format(temp[pos], 4096-pos, "<br />* <br />* This plugin is a modified version of Ultimate Warcraft 3 which is a new ");
	pos += format(temp[pos], 4096-pos, "approach to the War3 and&nbsp;<br />* ");
	pos += format(temp[pos], 4096-pos, "War3FT plugins created bySpaceDude and Pimp Daddy. UWC3 provides a raceless, skill/level based");
	pos += format(temp[pos], 4096-pos, "<br />* system. Much of the internal workings of Warcraft3FT skills and items were");
	pos += format(temp[pos], 4096-pos, "kept intact from Pimp Daddy&#39;s<br />");
	pos += format(temp[pos], 4096-pos, "* version, though the overall player structures ");
	pos += format(temp[pos], 4096-pos, "have been changed to allow a flexible skill-based system.");
	pos += format(temp[pos], 4096-pos, "<br />*<br />*************************************************************************************");
	pos += format(temp[pos], 4096-pos, "<br />* Credits to:<br />* Original Ultimate uwc3 by K2mia ( Andrew Cowan )");
	pos += format(temp[pos], 4096-pos, "<br />* Original War3FT by Pimp Daddy ( OoTOAoO )<br />* Spacedude ( for War3 MOD )");
	pos += format(temp[pos], 4096-pos, "<br />* Ludwig Van ( for flamethrower )<br />* OLO ( for spectating rank info )<br />* JGHG for the mole code");
	pos += format(temp[pos], 4096-pos, "<br />* [AOL]Demandred, [AOL]LuckyJ for help coding it for steam<br />* [AOL]Demandred for freezetime exploit fix");
	pos += format(temp[pos], 4096-pos, "<br />* Denkkar for some of his code ( ie. STEAM_POWERED )<br />* Everyone at amxmod.net for help");
	pos += format(temp[pos], 4096-pos, "<br />* joecool12321 for various health related fixes<br />* Tri Moon for various improvements ( No Race, war3menu, etc... )");
	pos += format(temp[pos], 4096-pos, "<br />* xeroblood for spotting some bugs for me : )<br />* bad-at-this for contributing the status bar code used for godmode ( big bad voodoo )");
	pos += format(temp[pos], 4096-pos, "<br />* kamikaze for help w/testing version before release<br />* lui for the delayed ultimate code<br />* the original UWC3 DEV team");
	pos += format(temp[pos], 4096-pos, "<br />* Left Nut for all his hard work on balancing the skills<br />* Hawk552 for his work on jumpkick<br />* twistedeuphoria for his work on multijump");
	pos += format(temp[pos], 4096-pos, "<br />* the developers of DIABLO MOD for inspiring us on the Syv Shield skill<br />* (--eRRoR--) from the StormZone community for their work on finding bugs and ");
	pos += format(temp[pos], 4096-pos, "some of the new sprites and sounds<br />* Dantallion for fatal strike and bug replication as well as help with some sounds");
	pos += format(temp[pos], 4096-pos, "<br />* A special THANKS to the YAUR community for their work and inspiration<br />*<br />");
	pos += format(temp[pos], 4096-pos, "&nbsp;*************************************************************************************/ <br>");
	pos += format(temp[pos], 4096-pos, "</td></tr></table></center>");
	
	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_credits.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Credits");
	return PLUGIN_CONTINUE;

}

public uwc3x_info(id)
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[2048], pos = 0;

	pos += format(temp[pos], 2048-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 2048-pos, "<center><table border=1 cellpadding=3 cellspacing=3><tr><td>");
	pos += format(temp[pos], 2048-pos, "<center><b>Ultimate Warcraft3 Expansion</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>" );

	pos += format(temp[pos], 2048-pos, "%L<p>", id, "WAR3INFO1" );
	pos += format(temp[pos], 2048-pos, "%L<br><p>", id, "WAR3INFO2" );
	pos += format(temp[pos], 2048-pos, "%L<p>", id, "WAR3INFO3" );
	pos += format(temp[pos], 2048-pos, "%L<br>", id, "WAR3INFO4" );
	pos += format(temp[pos], 2048-pos, "%L<br>", id, "WAR3INFO5" );
	pos += format(temp[pos], 2048-pos, "%L<br>", id, "WAR3INFO6" );
	pos += format(temp[pos], 2048-pos, "%L<p>", id, "WAR3INFO7" );
	pos += format(temp[pos], 2048-pos, "%L<p>", id, "WAR3INFO8" );
	pos += format(temp[pos], 2048-pos, "%L<p>", id, "WAR3INFO9" );
	pos += format(temp[pos], 2048-pos, "</td></tr></table></center>");

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_info.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}


	show_motd( id, temp, "Ultimate Warcraft3 Expansion Player Help");
	return PLUGIN_CONTINUE;

}

public uwc3x_tips( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[2048], pos = 0;

	pos += format(temp[pos], 2048-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 2048-pos, "<table border=0><tr><td>");
	pos += format(temp[pos], 2048-pos, "<center><b>%L</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>", id, "UWC3" );

	//TRANSLATE BELOW HERE
	pos += format(temp[pos], 2048-pos, "<b>Tips for Playing UWC3X</b><p>");
	pos += format(temp[pos], 2048-pos, "This is not the Warcraft3 plugin you are used to, the favorite race you want to play isn't here, but all your favorite skills and abiltiies are, plus many more. The following are some helpful tips for players new to WC3 and veterans of WC3 alike.<p>");
	pos += format(temp[pos], 2048-pos, "<li>There is no race menu, all skills are available via the skillsmenu by saying <b>/selectskill</b> <p>");
	pos += format(temp[pos], 2048-pos, "<li>Each page of skills has a corresponding page with info about each skills listed, page 1 skills info is accessed by saying <b>/skillsinfo1</b>, ... page 5 skills are accessed by saying <b>/skillsinfo5</b> <p>");
	pos += format(temp[pos], 2048-pos, "<li>In Ultimate Warcraft3 Expansion you gain levels and skills by earning experience. You earn experience by killing your enemies or seriously injuring them (assisting a teammate in killing), performing game objectives like planting the bomb or rescuring hostages, and other skill based methods such as healing your teamates or repairing their armor.<p>");
	pos += format(temp[pos], 2048-pos, "<li>Ultimate skills in UWC3X each have a unique command to bind to a key, the skillsmenu (/selectskill) displays these commands next to Ultimate skills. <p>");
	pos += format(temp[pos], 2048-pos, "</td></tr></table>");
	show_motd( id, temp, "Ultimate Warcraft3 Expansion Tips" );

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_tips.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}


	return PLUGIN_HANDLED;
}

public uwc3x_tips2( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[2048], pos = 0;

	pos += format(temp[pos], 2048-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 2048-pos, "<table border=0><tr><td>");
	pos += format(temp[pos], 2048-pos, "<center><b>%L</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>", id, "UWC3" );

	//TRANSLATE BELOW HERE
	pos += format(temp[pos], 2048-pos, "<b>Tips for Playing Ultimate Warcraft3 Expansion - page 2</b><p>");
	pos += format(temp[pos], 2048-pos, "<li>Abilities are also bound like Ultimates in UWC3X and their commands are also displayed next to their skill name in the menu<p>");
	pos += format(temp[pos], 2048-pos, "<li>There are 3 shops in UWC3X where magical items can be bought, these range from items that increase your speed or attack abilities to some that will disguise you like the enemy or allow you to spawn in the enemy camp at the start of a round. More information is available by saying <b>/itemsinfo</b> and <b>/itemsinfo2</b>  and <b>/itemsinfo2</b>.<p>");
	pos += format(temp[pos], 2048-pos, "<li>One <b>VERY</b> important item in the shop that should always be bought when money allows is the <b>Necklace of Immunity</b>. The necklace will protect you from all Ultimate skill effects as well as some other nasty skills such as Napalm Grenades or Serpant Wards. If money is tight I will generally purchase a Necklace in place of Armor, but thats just me. :)<p>");
	pos += format(temp[pos], 2048-pos, "<li>One skill that is new to UWC3X is called Mend Wounds and beside being useful to your team by allowing you to heal damage, cure poison and ease burns, it also provides a reliable source of earning experience.  Those types of skills are important - mend wounds, repair armor, dispell hex, vengance, etc all give lots of XP and help your team a great deal!<p>");
	pos += format(temp[pos], 2048-pos, "<li>You can reset your current skills by saying <b>/resetskills</b> - at the start of the next round your points will be returned and you may retrain a new set of skills.<p>");
	pos += format(temp[pos], 2048-pos, "<li>UWC3X now offers a complete line of player Attributes and Resistances you can train along with your skills. Complete information about Attributes, Resistances and Skills are available at our website -- <b>http://www.Yaur.com</b><p>");
	pos += format(temp[pos], 2048-pos, "</td></tr></table>");

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_tips2.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Tips pg. 2" );
	return PLUGIN_HANDLED;
}

public uwc3x_ultimates( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[3072], pos = 0;

	pos += format(temp[pos], 3072-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 3072-pos, "<table border=0><tr><td>");
	pos += format(temp[pos], 3072-pos, "<center><b>%L</b><br><a href='http://www.Yaur.com'><b>http://www.Yaur.com</b></a></center><p>", id, "uwc3" );

	//TRANSLATE BELOW HERE
	pos += format(temp[pos], 3072-pos, "<b>Important Information About UWC3X Ultimates</b><p>");
	pos += format(temp[pos], 3072-pos, "Unlike previous versions of the Warcraft3 and Warcraft Frozen Throne plugins,<br>Ultimate Warcraft3 Expansion allows players to train in up to 5 ultimate skills.<p>");
	pos += format(temp[pos], 3072-pos, "In order to make use of the ultimate skills in UWC3X you will need<br>to bind a key for each ultimate and each ultimate has a unique command to be bound. Special abilities are also handled the same way in UWC3X. <p>");
	pos += format(temp[pos], 3072-pos, "<table border=1 cellpadding=4 cellspacing=4><tr><th>Ultimate or Ability</th><th>Bind Command</th></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Suicide Bomber</td><td>bind key wcsuicide</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Teleport</td><td>bind key wcteleport</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Chain Lightning</td><td>bind key wclightning</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Entangle Roots</td><td>bind key wcentangle</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Flame Strike</td><td>bind key wcflame</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Big Bad Voodoo</td><td>bind key wcvoodoo</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Vengeance</td><td>Passive Ability</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Total Blindness</td><td>bind key wcblind</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Locust Swarm</td><td>bind key wclocust</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Decoy</td><td>bind key wcdecoy</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Gate</td><td>bind key wcgate</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>ROT</td><td>Passive Ability</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Wind Walker</td><td>Passive Ability</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Syv Shield</td><td>bind key wcshield</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Cripple</td><td>Passive Ability</td></tr>");

	pos += format(temp[pos], 3072-pos, "<tr><td>Ability: Mend Wounds</td><td>bind key wcmend</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Ability: Repair Armor</td><td>bind key wcrepair</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Ability: Serpant Ward</td><td>bind key wcward</td></tr>");
	pos += format(temp[pos], 3072-pos, "<tr><td>Ability: Bless</td><td>bind key wcbless</td></tr>");
	pos += format(temp[pos], 3072-pos, "</td></tr></table>");

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_ultimates.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Ultimates");
	return PLUGIN_CONTINUE;
}

public uwc3x_attributes( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[8096], pos = 0;
	pos += format(temp[pos], 8096-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 8096-pos, "<p><b>%L</b></p>", id, "ATTRIB_MENU1" );
	//pos += format(temp[pos], 8096-pos, "<p>%L</p>", id, "ATTRIB_MENU2" );
	pos += format(temp[pos], 8096-pos, "<ol>" );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_STR" );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_INT", INT_IMPALE_BONUS * 100, INT_SIPHON_BONUS * 100, INT_BANISH_BONUS * 100 );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_INT2", INT_HEX_BONUS * 100, INT_BASH_BONUS * 100, INT_TRUESHOT_BONUS * 100, INT_SERPENT_BONUS, INT_TELEPORT_COOL, INT_VOODOO_BONUS );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_DEX" );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_AGI" );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_CON" );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_WIS", WIS_HEXRESIST * 100, WIS_IMPALERESIST * 100, WIS_FIREDAMAGEBONUS * 100 );
	pos += format(temp[pos], 8096-pos, "%L", id, "ATTRIB_MENU1_WIS2", WIS_LIGHTNINGDAMAGEBONUS * 100, WIS_JUMPKICKRESIST * 100, WIS_BANISHBONUS * 100, WIS_BASHBONUS * 100, WIS_ULTIMATEBONUS );
	pos += format(temp[pos], 8096-pos, "</ol></body>" );

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_attributes.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Attributes Information");
	return PLUGIN_HANDLED;
}

public uwc3x_resistances( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new temp[2048], pos = 0;

	pos += format(temp[pos], 2048-pos, "<body bgcolor=#000000 text=#%s>", CVAR_HTML_TEXT_COLOR);
	pos += format(temp[pos], 2048-pos, "<b>%L</b><p>", id, "RESIST_MENU1" );
	pos += format(temp[pos], 2048-pos, "<p>%L</p><ol>", id, "RESIST_MENU2" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_POISON" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_DISEASE" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_ELECTRIC" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_FIRE" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_ICE" );
	pos += format(temp[pos], 2048-pos, "%L", id, "RESIST_MENU1_MAGIC" );
	pos += format(temp[pos], 2048-pos, "%L</ol>", id, "RESIST_MENU1_ROT" );

	if( CVAR_WRITE_HTML )
	{
		new whofile[64];
		get_configsdir( whofile, 63 );
		format( whofile, 63, "%s/uwc3x_resistances.html", whofile );

		if ( file_exists( whofile ) )
		{
			delete_file( whofile );
		}

		write_file( whofile, temp ) ;
	}

	show_motd( id, temp, "Ultimate Warcraft3 Expansion Resistances Information");
	return PLUGIN_HANDLED;
}

public character_sheet( id )
{
	show_motd(id, BuildCharsheet(id), "Your Character Sheet");
}



public cmd_whois( id, arg[] )
{
	new pid = cmd_target(id, arg, 0);

	if (!pid)
	{
		hudchat_show(id, "%L", id, "WHOIS_NOTFOUND", arg);
		hudchat_update(id);
		return PLUGIN_HANDLED;
	}
	
	new mtitle[64];
	new name[32];
	get_user_name(pid, name, 31);
	format(mtitle, 64, "Character Sheet of %s", name);
    
	show_motd(id, BuildCharsheet(pid), mtitle);
	return PLUGIN_HANDLED;
}  


BuildCharsheet(pid)
{
	new name[32], j = 0;
	new message[4096] = "", temp[1024] = "", stemp[1024] = "", temp2[64] = "", sname[64] = "";
	new bool:bHasASkill = false;
	
	get_user_name(pid, name, 31);

	// Calculate how many attrib/resist points can be spent
	new extra_xp = (playerxp[pid] - xplevel_lev[enh_minlevel]);

	if (extra_xp < 0)
		extra_xp = 0;

	new exp = (extra_xp / 10);

	format( stemp, 4096, "<body bgcolor=#000000 text=#%s background=^"%s^" style=^"background-size: 100%%^">", CVAR_HTML_TEXT_COLOR, CVAR_HTML_BACKGROUND_URL_WHOIS );
	add( message, 4096, stemp );
	format( stemp, 1024, "<center><b>Character Sheet: %s</b></center><p>", name );
	add( message, 4096, stemp );
	add( message, 4096, "<center><table width=465 border=1 cellpadding=2 cellspacing=2>" );
	add( message, 4096, "<tr><td width=50%>" );
	format( stemp, 1024, "Name: %s<br>", name );
	add( message, 4096, stemp );
	format( stemp, 1024, "Level: %d<br>", p_level[pid] );
	add( message, 4096, stemp );
	format( stemp, 1024, "Ultimates: %d/%d<br>", ultlearned[pid], p_maxultimates[pid] );
	add( message, 4096, stemp );
	add( message, 4096, "</td><td width=50%>" );
	
	if (p_level[pid] == (MAX_LEVEL-1))
	{
		format( stemp, 1024, "XP: %d<br>", playerxp[pid] );
	}
	else
	{
		format( stemp, 1024, "XP: %d / %d<br>", playerxp[pid], xplevel_lev[p_level[pid]+1] );
	}

	add( message, 4096, stemp );
	if (p_level[pid] == (MAX_LEVEL-1))
	{
		add( message, 4096, "Max Level Achieved<br>" );
	}
	else
	{
		format( stemp, 1024, "XP Needed: %d<br>", (xplevel_lev[p_level[pid]+1] - playerxp[pid]) );
		add( message, 4096, stemp );
	}
	
	format( stemp, 1024, "Enhancement XP: %d <br>", exp );
	add( message, 4096, stemp );
	add( message, 4096, "</td></tr><tr><td>" );
	add( message, 4096, "<b>Attributes:</b><p>" );
	format( stemp, 1024, "Strength: %d/%d<br>", p_attribs[pid][ATTRIBIDX_STR], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Intellect: %d/%d<br>", p_attribs[pid][ATTRIBIDX_INT], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Dexterity: %d/%d<br>", p_attribs[pid][ATTRIBIDX_DEX], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Agility: %d/%d<br>", p_attribs[pid][ATTRIBIDX_AGI], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Constitution: %d/%d<br>", p_attribs[pid][ATTRIBIDX_CON], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Wisdom: %d/%d<br>", p_attribs[pid][ATTRIBIDX_WIS], ATTRIB_MAX_VALUE );
	add( message, 4096, stemp );
	add( message, 4096, "</td><td>" );
	add( message, 4096, "<b>Resistances:</b><p>" );
	format( stemp, 1024, "Poison: %d/%d<br>", p_resists[pid][RESISTIDX_POISON], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Disease: %d/%d<br>", p_resists[pid][RESISTIDX_DISEASE], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Electricity: %d/%d<br>", p_resists[pid][RESISTIDX_ELECTRIC], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Fire: %d/%d<br>", p_resists[pid][RESISTIDX_FIRE], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Magic: %d/%d<br>", p_resists[pid][RESISTIDX_MAGIC], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Rot: %d/%d<br>", p_resists[pid][RESISTIDX_ROT], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	format( stemp, 1024, "Ice: %d/%d<br>", p_resists[pid][RESISTIDX_ICE], RESIST_MAX_VALUE );
	add( message, 4096, stemp );
	add( message, 2047, "</td></tr><tr><td colspan=2>" );
	add( message, 2047, "<b>Skills</b><p>" );
	
	for ( j = 1; j < MAX_SKILLS; j++ )
	{
		//counter++;
		if (j <= 8)
			copy(sname, 31, skillset1[j]);
		else if (j <= 16)
			copy(sname, 31, skillset2[j-8]);
		else if (j <= 24)
			copy(sname, 31, skillset3[j-16]);
		else if (j <= 32)
			copy(sname, 31, skillset4[j-24]);
		else if (j <= 40)
			copy(sname, 31, skillset5[j-32]);
		else if (j <= 48)
			copy(sname, 31, skillset6[j-40]);
		else if (j <= 56)
			copy(sname, 31, skillset7[j-48]);
		else if (j <= 64)
			copy(sname, 31, skillset8[j-56]);

		if (p_skills[pid][j])
		{
			bHasASkill = true;
			format(temp2,64,"%s [%d/%d]<br>", sname, p_skills[pid][j], skill_limits[j] );
			add(temp,1024,temp2);
		}
	}

	if (!bHasASkill)
	{
		add(temp,1024, "No skills trained");
	}
    
	add( message, 2048, temp );
	add( message, 2048, "</td></tr>" );
    	add( message,2048,"</table></center><br /><br />^n^n" );
    
	return message;
}


public set_rankstring( id )
{

	p_rank[id] = "";

	// Set the player's rank title
	if ( p_level[id] >= RANK13_LEVEL )
		copy(p_rank[id], 18, ranktitles[12]);
	else if ( p_level[id] >= RANK12_LEVEL )
		copy(p_rank[id], 18, ranktitles[11]);
	else if ( p_level[id] >= RANK11_LEVEL )
		copy(p_rank[id], 18, ranktitles[10]);
	else if ( p_level[id] >= RANK10_LEVEL )
		copy(p_rank[id], 18, ranktitles[9]);
	else if ( p_level[id] >= RANK9_LEVEL )
		copy(p_rank[id], 18, ranktitles[8]);
	else if ( p_level[id] >= RANK8_LEVEL )
		copy(p_rank[id], 18, ranktitles[7]);
	else if ( p_level[id] >= RANK7_LEVEL )
		copy(p_rank[id], 18, ranktitles[6]);
	else if ( p_level[id] >= RANK6_LEVEL )
		copy(p_rank[id], 18, ranktitles[5]);
	else if ( p_level[id] >= RANK5_LEVEL )
		copy(p_rank[id], 18, ranktitles[4]);
	else if ( p_level[id] >= RANK4_LEVEL )
		copy(p_rank[id], 18, ranktitles[3]);
	else if ( p_level[id] >= RANK3_LEVEL )
		copy(p_rank[id], 18, ranktitles[2]);
	else if ( p_level[id] >= RANK2_LEVEL )
		copy(p_rank[id], 18, ranktitles[1]);
	else
		copy(p_rank[id], 18, ranktitles[0]);

	return PLUGIN_CONTINUE;
}

public displaylevel( id, hide )
{
	if ( !id || !is_user_connected(id) )
		return PLUGIN_CONTINUE;

	new parm2[2];
	parm2[0] = id;

	if (!itemsrunning[id] && !endround)
	{
		Show_Items( parm2 );
	}

	new bool:bLvled = false;
	new skillptsavail = 0, addskillmesg = 0, xpstring[511] = "", name[32];
	get_user_name(id, name, 31);

	if ( playerxp[id] < 0 )
	{
		playerxp[id] = 0;
	}

	if ((p_level[id] < (MAX_LEVEL-1)) && (playerxp[id] >= xplevel_lev[p_level[id]+1]))
	{
		for (new i=(p_level[id]+1); i<MAX_LEVEL; ++i)
		{
			if (playerxp[id] >= xplevel_lev[i])
			{
				// Level Gain
				bLvled = true;
				p_level[id]=i;
			}
		}
	}

	// Set the player's rank string
	set_rankstring( id );

	if (hide != 3)
	{
		// [08-06-04] - Now checks/displays attrib/resist pts avail before skills - K2mia
		// hide != 3 specifies available attrib/resist/skill pts can be displayed

		new acount = get_attribcount( id );
		new apts = get_availattribpts( id );
		new rcount = get_resistcount( id );
		new rpts = get_availresistpts( id );

		if ( (apts > 0) && (acount < ((MAX_ATTRIBS-1) * (ATTRIB_MAX_VALUE-ATTRIB_BASE))) && (acount < ATTRIB_MAX_PTS) )
		{
			if( Util_Should_Msg_Client(id) )
			{
				// Display attribpts available message
				set_hudmessage(200, 100, 0, 0.35, -1.00, 0, 1.0, 5.0, 0.1, 0.2, 2);
				show_hudmessage(id,"You have %d attribute points available (use /selectattrib)", apts);
			}
		}
		else if ( (rpts > 0) && (rcount < ((MAX_RESISTS-1) * RESIST_MAX_VALUE)) && (rcount < RESIST_MAX_PTS) )
		{
			if( Util_Should_Msg_Client(id) )
			{
				// Display resistpts available message
				set_hudmessage(200, 100, 0, 0.35, -1.00, 0, 1.0, 5.0, 0.1, 0.2, 2);
				show_hudmessage(id, "You have %d resistance points available (use /selectresist)", rpts);
			}
		}
		else
		{
			// Determine if player has skills that can be learned
			skillptsavail = get_availskillpts( id );

			if (skillptsavail)
			{
				addskillmesg = 1;
				if( Util_Should_Msg_Client(id) )
				{
					// Display skillpts available message
					set_hudmessage(200, 100, 0, 0.35, -1.00, 0, 1.0, 5.0, 0.1, 0.2, 2);
					show_hudmessage(id, "You have %d skillpoints available (use /selectskill)", skillptsavail);
				}
			}
		}
	}

	if( CVAR_SHOW_ITEMS_IN_HUD )
	{
		if( playeritem2[id] == 0 )
		{
			format(xpstring,511,"Rank: %s [%d] XP: %d", p_rank[id], p_level[id], playerxp[id]);
		}
		else
		{
			format(xpstring,511,"Rank: %s [%d] XP: %d", p_rank[id], p_level[id], playerxp[id]);
		}
	}
	else
	{
		new temp2[128] = "";
		new temp3[128] = "";

		if (addskillmesg)
			format(temp3, 127, "[%d skillpts]", skillptsavail);

		format(xpstring,1023,"Rank: %s [%d] XP: %d %s %s", p_rank[id], p_level[id], playerxp[id], temp2, temp3);
	}

	if( Util_Should_Msg_Client( id ) )
	{
		message_begin( MSG_ONE, gmsgStatusText, {0,0,0}, id);
		write_byte(0);
		write_string(xpstring);
		message_end();
	}

	if (bLvled)
	{
		set_hudmessage(200, 100, 0, -1.0, 0.35, 0, 1.0, 7.0, 0.1, 0.2, 2);

		if (loadedlevel[id])
		{
			if( Util_Should_Msg_Client(id) )
			{
				show_hudmessage(id, "Congratulations - You gained a level");
			}

			client_print(0, print_chat, "[%s] Announcement :: Congratulations %s for gaining a level", MOD, name );
		}
		else
		{
			// Now player has initial levels loaded from saved XP
			loadedlevel[id] = 1;
			if( Util_Should_Msg_Client(id) )
			{
				show_hudmessage(id, "Status :: Saved XP and Levels Loaded");
			}
		}

		if( Util_Should_Msg_Client(id) )
		{
			if (file_exists("sound/uwc3x/levelupcaster.wav")==1 && is_user_alive(id))
			{
				emit_sound(id,CHAN_ITEM, "uwc3x/levelupcaster.wav", 1.0, ATTN_NORM, 0, PITCH_NORM);
			}
			else if ( is_user_alive(id) )
			{
				emit_sound(id,CHAN_ITEM, "plats/elevbell1.wav", 1.0, ATTN_NORM, 0, PITCH_LOW);
			}
		}
	}

	if (hide!=1 && hide!=3)
	{
		new temp[64] = "";
		new message[2048] = "";

		if (p_level[id] < (MAX_LEVEL-1))
		{
			format(temp,64,"^n%s %s [%d] XP: %d/%d","Your Rank:", p_rank[id], p_level[id], playerxp[id], xplevel_lev[p_level[id]+1]);
		}
		else
		{
			format(temp,64,"^n%s %s [%d] XP: %d","Your Rank:", p_rank[id], p_level[id], playerxp[id] );
		}

		add(message,2048,temp);
		add(message, 2048, "^n(Say /charsheet for your complete info)");
		set_hudmessage(255, 255, 255, -1.0, 0.3, 0, 3.0, 7.0, 0.1, 0.2, 2);

		if( Util_Should_Msg_Client(id) )
		{
			show_hudmessage(id,message);
		}
	}

	if ( !is_user_connected( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	if ( get_cvar_num( "sv_gravity" ) > 650 )
	{
		if (p_skills[id][SKILLIDX_LEVITATION] && playeritem2[id]!=FEATHER)
		{
			// Levitation
			if (get_user_gravity(id)!=p_levitation[p_skills[id][SKILLIDX_LEVITATION]-1])
			{
				set_user_gravity(id,p_levitation[p_skills[id][SKILLIDX_LEVITATION]-1]);
			}
			else if (playeritem2[id] == FEATHER)
			{
				set_user_gravity(id,0.35);
			}
			else if (get_user_gravity(id)!=1.0)
			{
				set_user_gravity(id,1.0);
			}
		}
	}
	else
	{
		set_user_gravity(id,1.0);
	}

	if (p_skills[id][SKILLIDX_INVIS] && playeritem[id]==CLOAK)
	{
		// Invisibility
		new Float:tmpInvis = float(cloakstack[p_skills[id][SKILLIDX_INVIS]-1]);
		new Float:tmpCloak = float(CLOAKINVISIBILITY);
		new tmpBoth = floatround(tmpCloak - tmpInvis);

		if (knifeselected[id])
		{
			new invisibility = tmpBoth/2;
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,invisibility);
		}
		else
		{
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,tmpBoth+INVIS_STACK_OFFSET);
		}
	}
	else if (p_skills[id][SKILLIDX_INVIS])
	{
		if (knifeselected[id])
		{
			new invisibility = p_invisibility[p_skills[id][SKILLIDX_INVIS]-1];
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,invisibility);
		}
		else
		{
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,p_invisibility[p_skills[id][SKILLIDX_INVIS]-1]);
		}
	}
	else if (playeritem[id]==CLOAK)
	{
		if (knifeselected[id])
		{
			new invisibility = CLOAKINVISIBILITY/2;
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,invisibility);
		}
		else
		{
			set_user_rendering(id,kRenderFxNone, 0,0,0, kRenderTransTexture,CLOAKINVISIBILITY);
		}
	}
	else
	{
		set_user_rendering(id);
	}

	// Unholy Aura handler next - Call unholy routine
	new parm[1];
	parm[0]=id;
	Set_Speed(parm);

	if (!levelredirection)
	{
		return PLUGIN_CONTINUE;
	}

	if (is_user_admin(id))
	{
		return PLUGIN_CONTINUE;
	}

	new servergoto[128];

	// If they are above 'forwardontolevel' move them onto another server.
	if (p_level[id] > forwardontolevel[0])
	{
		if (p_level[id] > forwardontolevel[2])
		{
			if (forwardontoserver[2][0])
			{
				client_print(id, print_console, "You are being re-directed to a new server. [%s]", forwardontoserver[2]);
				format(servergoto, 128, "disconnect; connect %s", forwardontoserver[2]);
				client_cmd(id, servergoto);
			}
		}
		else if (p_level[id] > forwardontolevel[1])
		{
			if (forwardontoserver[1][0])
			{
				client_print(id, print_console, "You are being re-directed to a new server. [%s]", forwardontoserver[1]);
				format(servergoto, 128, "disconnect; connect %s", forwardontoserver[1]);
				client_cmd(id, servergoto);
			}
		}
		else
		{
			if (forwardontoserver[0][0])
			{
				client_print(id, print_console, "You are being re-directed to a new server. [%s]", forwardontoserver[0]);
				format(servergoto, 128, "disconnect; connect %s", forwardontoserver[0]);
				client_cmd(id, servergoto);
			}
		}
	}
	return PLUGIN_CONTINUE;
}

public cmd_who( id )
{
	new message[4096] = "", pos = 0, name[32], team[32], players[32], numplayers, i, playerid;
	get_players(players, numplayers);

	pos += format( message[pos], 4096-pos, "<body bgcolor=#000000 text=#%s background=^"%s^" style=^"background-size: 100%%^">^n", CVAR_HTML_TEXT_COLOR, CVAR_HTML_BACKGROUND_URL_WHO );
	pos += format( message[pos], 4096-pos, "<center><b>The following players are online</b></center><p>^n" );
	pos += format( message[pos], 4096-pos, "<center><table width=600 border=1 cellpadding=2 cellspacing=2>^n" );
	pos += format( message[pos], 4096-pos, "<tr><td>Name</td><td>Team</td><td>Level</td></tr>^n" );

	for ( i = 0; i < numplayers; i++ )
	{
		playerid = players[i];

		if ( get_user_team(playerid) == TEAM_T )
		{
			team = "Terrorist";
		}
		else if ( get_user_team(playerid) == TEAM_CT )
		{
			team = "CT";
		}
		else
		{
			team = "Spectator";
		}

		get_user_name( playerid, name, 31 );
		pos += format( message[pos], 4096-pos, "<tr><td>%s</td><td>%s</td><td>%d</td></tr>^n", name, team, p_level[playerid], name);
	}

	pos += format( message[pos], 4096-pos, "</table></center><br />^n^n" );

	new whofile[64];
	get_configsdir( whofile, 63 );
	format( whofile, 63, "%s/uwc3x_who.txt", whofile );

	if ( file_exists( whofile ) )
	{
		delete_file( whofile );
	}

	write_file( whofile, message ) ;
	show_motd( id, whofile, "Ultimate Warcraft3 Expansion Players Online" );
	return PLUGIN_CONTINUE;
}

public player_skills( id )
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	if( Util_Should_Msg_Client(id) )
	{
		hudchat_show(id, "%L", id, "PLAYERSKILLS");
		hudchat_update(id);
		//client_print( id, print_chat, "%L", id, "PLAYERSKILLS", MOD);
	}

	return PLUGIN_CONTINUE;
}
