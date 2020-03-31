
public PrintConnectMessage ( id )
{
	//client_cmd ( id, "echo " );
	//client_cmd ( id, "echo ^" *=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=* ^" " );
	//client_cmd ( id, "echo ^" *=-=        The Yaur.com Community thanks you for playing        ^" " );
	//client_cmd ( id, "echo ^" *=-=                                                           ^" " );
	//client_cmd ( id, "echo ^" *=-=             Ultimate Warcraft3 Expansion ( UWC3X )          ^" " );
	//client_cmd ( id, "echo ^" *=-=             Our Website: http://www.Yaur.com/              ^" " );
	//client_cmd ( id, "echo ^" *=-=                                                           ^" " );
	//client_cmd ( id, "echo ^" *=-=      This is a new expanded version of UWC3X brought       ^" " );
	//client_cmd ( id, "echo ^" *=-=      to you by -=[Yaur]=-  We want your feedback on Skills,  ^" " );
	//client_cmd ( id, "echo ^" *=-=      Shopmenu items and any improvements you think we should^" " );
	//client_cmd ( id, "echo ^" *=-=      make.  We also want you to report any problems and bugs^" " );
	//client_cmd ( id, "echo ^" *=-=                                                             ^" " );
	//client_cmd ( id, "echo ^" *=-=            We also welcome donations of any amount         ^" " );
	//client_cmd ( id, "echo ^" *=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=* ^" " );
	//client_cmd ( id, "echo " );
}

public PrintDisconnectMessage ( id )
{
	//client_cmd ( id, "echo " );
	//client_cmd ( id, "echo ^" *=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=* ^" " );
	//client_cmd ( id, "echo ^" *=-=        The Yaur.com Community thanks you for playing        ^" " );
	//client_cmd ( id, "echo ^" *=-=                                                           ^" " );
	//client_cmd ( id, "echo ^" *=-=             Ultimate Warcraft3 Expansion ( UWC3X )          ^" " );
	//client_cmd ( id, "echo ^" *=-=             Our Website: http://www.Yaur.com/              ^" " );
	//client_cmd ( id, "echo ^" *=-=                                                           ^" " );
	//client_cmd ( id, "echo ^" *=-=      This is a new expanded version of UWC3X brought       ^" " );
	//client_cmd ( id, "echo ^" *=-=      to you by -=[Yaur]=-  We want your feedback on Skills,  ^" " );
	//client_cmd ( id, "echo ^" *=-=      Shopmenu items and any improvements you think we should^" " );
	//client_cmd ( id, "echo ^" *=-=      make.  We also want you to report any problems and bugs^" " );
	//client_cmd ( id, "echo ^" *=-=                                                             ^" " );
	//client_cmd ( id, "echo ^" *=-=            We also welcome donations of any amount         ^" " );
	//client_cmd ( id, "echo ^" *=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=* ^" " );
	//client_cmd ( id, "echo " );
}

public Initialize_CLCMD ( )
{

	// [09-13-04] Nasty exploit, this prevents it - K2mia
	register_clcmd ( "fullupdate",		"fullupdate" );
	register_clcmd ( "say",			"check_say" );
	register_clcmd ( "say_team",		"check_say" );

 
	// Client command entries follow
	//register_clcmd ( "war3menu",		"main_menu",		-1,			"-Display the UWC3X Main Menu" );
	//register_clcmd ( "wc3menu",		"main_menu",		-1,			"-Display the UWC3X Main Menu" );
	//register_clcmd ( "warcraft",		"main_menu",		-1,			"-Display the UWC3X Main Menu" );
	
	register_clcmd ( "help",			"uwc3x_info",		-1,			"-Displays the main help menu" );
	//register_clcmd ( "news",			"show_news",		-1,			"-Displays news about the Ultimate Warcraft3 Expansion plugin" );
	register_clcmd ( "war3help",		"uwc3x_info",		-1,			"-Displays help information for the UWC3X module" );
	register_clcmd ( "charsheet",		"character_sheet",	-1,			"-Displays your character sheet" );
	register_clcmd ( "savexp",			"ShowSaveText",		-1,			"-In long term XP mode, saves your XP" );
	register_clcmd ( "saveattribs",		"ShowSaveText",		-1,			"-In long term XP mode, saves your Attributes" );
	register_clcmd ( "saveresists",		"ShowSaveText",		-1,			"-In long term XP mode, saves your Resistances" );
	register_clcmd ( "saveall",			"SaveSinglePlayerXP",-1,		"-In long term XP mode, saves your XP / Skills / Attributes / Resistances" );
	register_clcmd ( "resetskills",		"Skills_Reset",		-1,			"-Resets your skills while keeping your XP" );
	register_clcmd ( "resetattribs",	"Reset_Attribs",	-1,			"-Resets your attributes while keeping your XP" );
	register_clcmd ( "resetresists",	"Reset_Resists",	-1,			"-Resets your resistances while keeping your XP" );
	register_clcmd ( "deletexp",		"XP_DeleteXP",		-1,			"-Deletes all skills and sets your XP to 0" );
	register_clcmd ( "saveskills",		"ShowSaveText",		-1,			"-In long term XP mode, saves your skills" );
	register_clcmd ( "reloadskills",	"Skills_Reload",	-1,			"-Reloads the default saved set of skills" );
	register_clcmd ( "reloadxp",		"XP_Reload",		-1,			"-Reloads your XP in case it didnt load properly" );
	register_clcmd ( "toggle_lowres",	"toggle_lowres",	-1,			"-Toggle low-res mode on/off" );
	register_clcmd ( "xp_table",		"XP_ShowTable",		-1,			"-Displays the XP table" );

	register_clcmd ( "admin_loadskills",	"Skills_AdminLoad",	ADMIN_MENU, "-Loads a saved set of skills" );
	register_clcmd ( "wc3start",			"restart_round",	ADMIN_MENU,	"-Restarts the UWC3X mod fresh" );
	register_clcmd ( "admin_showxp",		"XP_AdminShowXP",	ADMIN_MENU,	"-Admin Cmd: Displays a player's XP" );

	// ******************** TEST COMMANDS *******************
	//register_clcmd ( "admin_loadxp",		"ShowSaveText",		ADMIN_MENU, "-Debug cmd for testing load data from vault routine" );
	//register_clcmd ( "debug_info",		"debug_info",		ADMIN_MENU, "-Dumps some debug info to the admin" );
	//register_clcmd ( "debuginfo",			"debug_info",		ADMIN_MENU, "-Dumps some debug info to the admin" );
	register_clcmd ( "loc",					"admin_loc",		ADMIN_MENU, "-Displays your coordinate location" );
	// ****************** END TEST COMMANDS ******************

	register_clcmd ( "changerace",			"change_race",		-1, 	"-Display UWC3X info" );
	register_clcmd ( "/changerace",			"change_race",		-1, 	"-Display UWC3X info" );
	register_clcmd ( "selectrace",			"change_race",		-1, 	"-Display UWC3X info" );
	register_clcmd ( "/selectrace",			"change_race",		-1, 	"-Display UWC3X info" );
	register_clcmd ( "selectskill",			"select_skill",		-1, 	"-Displays the skills menu" );
	register_clcmd ( "/selectskill",		"select_skill",		-1, 	"-Displays the skills menu" );
	register_clcmd ( "selectattrib",		"Select_Attrib",	-1, 	"-Displays the attributes menu" );
	register_clcmd ( "/selectattrib",		"Select_Attrib",	-1, 	"-Displays the attributes menu" );
	register_clcmd ( "dropskill",			"drop_skill",		-1, 	"-Displays the drop skills menu" );
	register_clcmd ( "/dropskill",			"drop_skill",		-1, 	"-Displays the drop skills menu" );
	register_clcmd ( "selectresist",		"Select_Resist",	-1, 	"-Displays the resistances menu" );
	register_clcmd ( "/selectresist",		"Select_Resist",	-1, 	"-Displays the resistances menu" );
	register_clcmd ( "shopmenu",			"ShopMenu",			-1, 	"shopmenu" );
	register_clcmd ( "/shopmenu",			"ShopMenu",			-1, 	"shopmenu" );
	register_clcmd ( "shopmenu2",			"ShopMenu2",		-1, 	"shopmenu2" );
	register_clcmd ( "/shopmenu2",			"ShopMenu2",		-1, 	"shopmenu2" );
	register_clcmd ( "shopmenu3",			"ShopMenu3",		-1, 	"shopmenu3" );
	register_clcmd ( "/shopmenu3",			"ShopMenu3",		-1, 	"shopmenu3" );
	register_clcmd ( "rings",				"rings5",			-1, 	"-Saying this allows you to buy 5 rings" );

	// Ultimate skills - client commands to bind
	register_clcmd ( "wcentangle",		"Ult_Entangle",			-1,		"-Entangle Ultimate" );
	register_clcmd ( "wcsuicide",		"Ult_Suicide_Bomber",	-1,		"-Suicide Bomber Ultimate" );
	register_clcmd ( "wcteleport",		"Ult_Teleport",			-1,		"-Teleport Ultimate Skill" );
	register_clcmd ( "wclightning",		"Ult_ChainLightning",	-1,		"-Chain Lightning Ultimate" );
	register_clcmd ( "wcflame",			"Ult_FlameStrike",		-1,		"-Flame Strike Ultimate Skill" );
	register_clcmd ( "wcvoodoo",		"Ult_VooDoo",			-1,		"-Big Bad Voodoo Ultimate Skill" );
	register_clcmd ( "wcdecoy",			"Ult_Decoy",			-1,		"-Decoy Ultimate Skill, spawns a decoy to briefly fool your enemies" );
	register_clcmd ( "wcgate",			"Ult_Gate",				-1,		"-Gate Ultimate Skill, Opens a gateway back to your spawn" );
	register_clcmd ( "wcshield",		"Ult_TeamShield",		-1,		"-Team Shield Ultimate Skill" );
	register_clcmd ( "wcdepower",		"Ult_DePower",			-1,		"-Depower Ultimate Skill" );
	register_clcmd ( "wcblind",			"Ult_Flash",			-1,		"-Total Blindness Ultimate Skill" );
	register_clcmd ( "wclocust",		"Ult_Locust",			-1,		"-Locust Swarm Ultimate Skill" );
	register_clcmd ( "wcsmite",			"Ult_Smite",			-1,		"-Smite Ultimate Skill" );
	register_clcmd ( "wcuammo",			"Ult_UnlimitedAmmo",	-1,		"-Unlimited Ammo Ultimate Skill" );
	register_clcmd ( "wcdisorient",		"Ult_BadAim",			-1,		"-Disorientation Ultimate Skill" );
	register_clcmd ( "wcquake",			"Ult_EarthQuake",		-1,		"-Earth Quake Ultimate Skill" );
	register_concmd ( "wcgrab", 		"Ult_Grab", 			-1,		"-Grab Ultimate");
	register_concmd ( "wchook", 		"Ult_Hook2", 			-1,		"-Hook Ultimate");
	register_concmd ( "wcrope", 		"Ult_Rope", 			-1,		"-Rope Ultimate");
	register_concmd ( "wcmine", 		"Use_Mine", 			-1,		"-Mine Skill");

	register_clcmd ( "wcdispell",		"ability_wcdispell",	-1,		"-Special Ability: Dispell Hex ( aim at teammate and trigger the wcdispell cmd )" );
	register_clcmd ( "wcward",			"ability_wcward",		-1,		"-Serpant Ward Ultimate Skill" );
	register_clcmd ( "wcrepair",		"ability_wcrepair",		-1,		"-Special Ability: Repair Armor ( aim at teammate and trigger the wcrepair cmd )" );
	register_clcmd ( "wcmend",			"ability_wcmend",		-1,		"-Special Ability: Mend Wounds ( aim at teammate and trigger the wcmend command )" );
	register_clcmd ( "wcbless",         "ability_wcbless",      -1,     "-Special Ability: Blessing ( aim at teammate and trigger the wcbless command )" );	
	
	//register_clcmd ( "flash", "Buy_Flash" );
	register_clcmd ( "hegren", "Buy_HE" );     

	//For Depower - block dropping of the TMP
	register_clcmd ( "drop", "hookDrop", 0 );     
	
	// Console command entries follow
	register_concmd ( "amx_restartround", 	"amx_restartround",			-1,		"-Console command used to restart the round");	
	register_concmd ( "amx_givexp",			"amx_givexp",				-1,		"-Console command used to GIVE XP" );
	register_concmd ( "amx_setlevel",		"amx_setlevel",				-1,		"-Console command used to set a players level" );
	register_concmd ( "amx_resetskills",	"amx_resetskills",			-1,		"-Console command used to reset a players skills" );
	register_concmd ( "amx_resetresists",	"amx_resetresists",			-1,		"-Console command used to reset a players resists" );
	register_concmd ( "amx_resetattribs",	"amx_resetattribs",			-1,		"-Console command used to reset a players attribs" );
	register_concmd ( "amx_reseteverything","amx_reseteverything",		-1,		"-Console command used to reset a players skills, resists, and attribs" );
	register_concmd ( "amx_takexp",			"amx_takexp",				-1,		"-Console command used to TAKE XP" );
	register_concmd ( "amx_givemole",		"Amx_GiveMole",				-1,		"-Admin make a mole command" );
	register_concmd ( "playerskills",		"player_skills",			-1,		"-Displays the players rank and skills" );
	register_concmd ( "setskillset",		"Skills_Check_SkillSet",	-1,		"-Displays the players rank and skills" );
	register_concmd ( "amx_maxresists",		"amx_maxresists",			-1,		"-Console command used to max players resists" );
	register_concmd ( "amx_maxattribs",		"amx_maxattribs",			-1,		"-Console command used to max players resists" );
}