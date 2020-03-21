/* SKILLS AND SKILL RELATED FUNCTIONS */

//Sets what levels the skills are available at
public Set_Skill_Mins ( )
{
	skill_minlev[SKILLIDX_FAN]			= 19;
	skill_minlev[SKILLIDX_EQREINC]		= 1;
	skill_minlev[SKILLIDX_PHOENIX]		= 13;
	skill_minlev[SKILLIDX_BLINK]		= 14;
	skill_minlev[SKILLIDX_SERPWARD]		= 6;
	skill_minlev[SKILLIDX_VAMPIRIC]		= 3;
	skill_minlev[SKILLIDX_LEVITATION]	= 1;
	skill_minlev[SKILLIDX_DEVOTION]		= 2;
	skill_minlev[SKILLIDX_SIPHON]		= 2;
	skill_minlev[SKILLIDX_IMPALE]		= 1;
	skill_minlev[SKILLIDX_CARAPACE]		= 3;
	skill_minlev[SKILLIDX_UNHOLY]		= 5;
	skill_minlev[SKILLIDX_BASH]			= 6;
	skill_minlev[SKILLIDX_CRITSTRIKE]	= 9;
	skill_minlev[SKILLIDX_THORNS]		= 8;
	skill_minlev[SKILLIDX_BANISH]		= 7;
	skill_minlev[SKILLIDX_HEX]			= 5;
	skill_minlev[SKILLIDX_EVASION]		= 24;
	skill_minlev[SKILLIDX_TRUESHOT]		= 24;
	skill_minlev[SKILLIDX_HEALWAVE]		= 2;
	skill_minlev[SKILLIDX_CARRION]		= 10;
	skill_minlev[SKILLIDX_SSTRIKE]		= 11;
	skill_minlev[SKILLIDX_CRITGREN]		= 12;
	skill_minlev[SKILLIDX_INVIS]		= 13;
	skill_minlev[SKILLIDX_SUICIDE]		= 17;
	skill_minlev[SKILLIDX_ENTANGLE]		= 16;
	skill_minlev[SKILLIDX_FSTRIKE]		= 16;
	skill_minlev[SKILLIDX_SAMMO]		= 14;
	skill_minlev[SKILLIDX_TELEPORT]		= 8;
	skill_minlev[SKILLIDX_LIGHTNING]	= 15;
	skill_minlev[SKILLIDX_VOODOO]		= 12;
	skill_minlev[SKILLIDX_VENGEANCE]	= 15;
	skill_minlev[SKILLIDX_DISHEX]		= 9;
	skill_minlev[SKILLIDX_LSKIN]		= 2;
	skill_minlev[SKILLIDX_SSKIN]		= 11;
	skill_minlev[SKILLIDX_NAPALM]		= 13;
	skill_minlev[SKILLIDX_REPAIR]		= 4;
	skill_minlev[SKILLIDX_MEND]			= 4;
	skill_minlev[SKILLIDX_DECOY]		= 14;
	skill_minlev[SKILLIDX_GATE]			= 12;

	//new skills add
	skill_minlev[SKILLIDX_JUMPKICK]		= 9;
	skill_minlev[SKILLIDX_MULTIJUMP]	= 3;
	skill_minlev[SKILLIDX_CAT]			= 18;
	skill_minlev[SKILLIDX_ROT]			= 32;
	skill_minlev[SKILLIDX_TEAMSHIELD]	= 15;

	skill_minlev[SKILLIDX_DEPOWER]		= 12;
	skill_minlev[SKILLIDX_CLOAK]		= 4;
	skill_minlev[SKILLIDX_CRIPPLE]		= 36;

	skill_minlev[SKILLIDX_BLIND]		= 6;
	skill_minlev[SKILLIDX_LOCUST]		= 12;

	skill_minlev[SKILLIDX_DISORIENT]	= 36;
	skill_minlev[SKILLIDX_UAMMO]		= 6;
	skill_minlev[SKILLIDX_EARTHQUAKE]	= 40;
	skill_minlev[SKILLIDX_SMITE]		= 36;

	skill_minlev[SKILLIDX_CLUSTERNADE]	= 19;
	skill_minlev[SKILLIDX_ICENADE]		= 27;
	skill_minlev[SKILLIDX_SPLITTER]		= 13;
	
	skill_minlev[SKILLIDX_HOOK]			= 26;
	skill_minlev[SKILLIDX_GRAB]			= 32;
	skill_minlev[SKILLIDX_ROPE]			= 23;
	
	skill_minlev[SKILLIDX_FATAL]		= 24;
	
	skill_minlev[SKILLIDX_BLESS]		= 31;
	skill_minlev[SKILLIDX_MINE]			= 21;
	skill_minlev[SKILLIDX_NEWSKILL16]	= 51;
}


//Sets the max amount of the skill points available per skill
public Set_Skill_Max ( )
{
	//These skills are defined by Cvars
	skill_limits[SKILLIDX_FAN]			= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_IMPALE]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_BANISH]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_HEX]			= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_BLINK]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_PHOENIX]		= MAX_SKILL_LEVEL5;
	skill_limits[SKILLIDX_EVASION]		= MAX_SKILL_LEVEL7;
	skill_limits[SKILLIDX_VAMPIRIC]		= MAX_SKILL_LEVEL8;
	skill_limits[SKILLIDX_LEVITATION]	= MAX_SKILL_LEVEL5;
	skill_limits[SKILLIDX_DEVOTION]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_CARAPACE]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_UNHOLY]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_BASH]			= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_CRITSTRIKE]	= MAX_SKILL_LEVEL8;
	skill_limits[SKILLIDX_THORNS]		= MAX_SKILL_LEVEL8;
	skill_limits[SKILLIDX_TRUESHOT]		= MAX_SKILL_LEVEL8;
	skill_limits[SKILLIDX_HEALWAVE]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_LSKIN]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_CARRION]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_SSTRIKE]		= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_CRITGREN]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_INVIS]		= MAX_SKILL_LEVEL8;
	skill_limits[SKILLIDX_SAMMO]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_SIPHON]		= MAX_SKILL_LEVEL3;

	//These skills have a max set value
	skill_limits[SKILLIDX_EQREINC]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_SERPWARD]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_MEND]			= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_DISHEX]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_SSKIN]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_NAPALM]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_REPAIR]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_DISHEX]		= MAX_SKILL_LEVEL1;

	//new skills add
	skill_limits[SKILLIDX_JUMPKICK]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_MULTIJUMP]	= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_CAT]			= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_ROT]			= MAX_SKILL_LEVEL5;

	skill_limits[SKILLIDX_TEAMSHIELD]	= MAX_SKILL_LEVEL5;
	skill_limits[SKILLIDX_DEPOWER]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_CLOAK]		= MAX_SKILL_LEVEL5;
	skill_limits[SKILLIDX_CRIPPLE]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_FATAL]		= MAX_SKILL_LEVEL5;
	skill_limits[SKILLIDX_MINE]			= MAX_SKILL_LEVEL1;

	//ultimates
	skill_limits[SKILLIDX_SUICIDE]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_ENTANGLE]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_FSTRIKE]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_TELEPORT]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_LIGHTNING]	= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_VOODOO]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_VENGEANCE]	= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_DECOY]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_GATE]			= MAX_SKILL_LEVEL2;
	skill_limits[SKILLIDX_BLIND]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_LOCUST]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_DISORIENT]	= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_UAMMO]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_EARTHQUAKE]	= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_SMITE]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_CLUSTERNADE]	= MAX_SKILL_LEVEL4;
	skill_limits[SKILLIDX_ICENADE]		= MAX_SKILL_LEVEL3;
	skill_limits[SKILLIDX_SPLITTER]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_HOOK]			= MAX_SKILL_LEVEL4;
	skill_limits[SKILLIDX_GRAB]			= MAX_SKILL_LEVEL6;
	skill_limits[SKILLIDX_ROPE]			= MAX_SKILL_LEVEL4;
	
	skill_limits[SKILLIDX_BLESS]		= MAX_SKILL_LEVEL1;
	skill_limits[SKILLIDX_NEWSKILL16]	= MAX_SKILL_LEVEL1;

	// Now set the skill_ultimates list for the ultimate indices

	copy ( skill_ultimates[SKILLIDX_SMITE],			32, "wcsmite"			);
	copy ( skill_ultimates[SKILLIDX_EARTHQUAKE],	32, "wcquake"			);
	copy ( skill_ultimates[SKILLIDX_DISORIENT],		32, "wcdisorient"		);
	copy ( skill_ultimates[SKILLIDX_UAMMO],			32, "wcuammo"			);
	copy ( skill_ultimates[SKILLIDX_BLIND],			32, "wcblind"			);
	copy ( skill_ultimates[SKILLIDX_LOCUST],		32, "wclocust"			);
	copy ( skill_ultimates[SKILLIDX_TEAMSHIELD],	32, "wcshield"			);
	copy ( skill_ultimates[SKILLIDX_CAT],			32, "Passive Ability"	);
	copy ( skill_ultimates[SKILLIDX_SUICIDE],		32, "wcsuicide"			);
	copy ( skill_ultimates[SKILLIDX_ENTANGLE],		32, "wcentangle"		);
	copy ( skill_ultimates[SKILLIDX_FSTRIKE],		32, "wcflame"			);
	copy ( skill_ultimates[SKILLIDX_TELEPORT],		32, "wcteleport"		);
	copy ( skill_ultimates[SKILLIDX_LIGHTNING],		32, "wclightning"		);
	copy ( skill_ultimates[SKILLIDX_VOODOO],		32, "wcvoodoo"			);
	copy ( skill_ultimates[SKILLIDX_VENGEANCE],		32, "Passive Ability"	);
	copy ( skill_ultimates[SKILLIDX_DECOY],			32, "wcdecoy"			);
	copy ( skill_ultimates[SKILLIDX_GATE],			32, "wcgate"			);
	copy ( skill_ultimates[SKILLIDX_DEPOWER],		32, "wcdepower"			);
	copy ( skill_ultimates[SKILLIDX_CRIPPLE],		32, "Passive Ability"	);
	copy ( skill_ultimates[SKILLIDX_SPLITTER],		32, "Passive Ability"	);
	copy ( skill_ultimates[SKILLIDX_HOOK],			32, "wchook"			);
	copy ( skill_ultimates[SKILLIDX_ROPE],			32, "wcrope"			);
	copy ( skill_ultimates[SKILLIDX_GRAB],			32, "wcgrab"			);
	copy ( skill_ultimates[SKILLIDX_MINE],			32, "wcmine"			);
}

public Set_Skill_Base ( )
{
	// Now setup skill values for all skill levels
	for ( new i = 0; i < MAX_SKILL_LEVEL10; i++ )
	{
		//These have been tweaked as per Left Nut
		p_vampiric[i]			= 0.07 + ( i * 0.03 );
		p_trueshot[i]			= 0.06 + ( i * 0.01 );
		p_critical[i]			= 0.06 + ( i * 0.01 );
		p_thorns[i]				= 0.07 + ( i * 0.03 );
		p_bash[i]				= 0.07 + ( i * 0.03 );
		p_banish[i]				= 0.07 + ( i * 0.03 );
		p_hex[i]				= 0.07 + ( i * 0.03 );

		p_jumpkick_damage[i]	= 7 + (7 * i);
		p_jumpkick_push[i]		= 15 + (15 * i);
		p_cloakskill[i]			= 0.10 + (i * 0.10);
		p_ShieldMaxDamage[i]	= 20 + ( (i + 1 ) * 10 );
		p_maxjumps[i]			= 0 + i;

		p_vampirichealth[i]		= 120 + ( i * 5 );
		p_unholy[i]				= 260.0 + ( i * 6.0 );
		p_levitation[i]			= 0.8 - ( i * 0.03 );
		p_invisibility[i]		= 205 - ( i * 6 );
		p_devotion[i]			= 110 + ( i * 5 );
		p_grenade[i]			= 1.00 + ( i * 0.15 );
		p_mana[i]				= 0.05 + ( i * 0.01 );
		p_ammo[i]				= 0.05 + ( i * 0.01 );
		p_heal[i]				= 6.0 - ( i * 0.4 );
		p_lskin[i]				= 6.0 - ( i * 0.4 );
		p_shadow[i]				= 0.07 + ( i * 0.03 );
		p_impale[i]				= 0.10 + ( i * 0.02 );
		p_spiked[i]				= 0.05 + ( i * 0.01 );
		p_carrion[i]			= 0.07 + ( i * 0.03 );
		p_hooks[i]				= i;
		p_rotchance[i]			= 0.03 + (i * 0.01);
		
		if( i <= 6 )
		{
			p_fatal_chance[i]		= 0.12 - ( 0.02 * i);  // 12%, 10%, 8%, 6%, 4% - chance to hit
		}
		else
		{
			p_fatal_chance[i]		= 0.00;		
		}
		
		p_fatal_damage[i]		= 1 + (0.2 * i);  // 100%, 120%, 140%, 160%, 180% - bonus damage multiplier
		
		if( i > 0 )
		{
			p_grabs[i]			= floatround( float(i) / 2 ) + 1;
		}
		else
		{
			p_grabs[i]			= i;		
		}
		
		p_grabchance[i]			= CVAR_GRAB_CHANCE + ( 0.05 * i );
		p_ropes[i]				= i;
	}
}

public Set_Skill_Order ( )
{
	new tmp;

	for ( new i = 1; i < MAX_SKILLS; i++ )
	{
		sortedskills[i] = i;
	}

	// Sort the skill list by min. level to train the skill
	for ( new i=1; i < MAX_SKILLS; i++ )
	{
		for ( new j=1; j < MAX_SKILLS -i; j++ )
		{
			if ( skill_minlev[sortedskills[j+1]] < skill_minlev[sortedskills[j]] )
			{
				// Swap the two out of place score positions
				tmp = sortedskills[j];
				sortedskills[j] = sortedskills[j+1];
				sortedskills[j+1] = tmp;
			}
		}
	}
}

public Set_Skill_Limits ( )
{
	//Set the min level for each skill
	Set_Skill_Mins ( );

	//Set the skill order in the sorted list
	Set_Skill_Order ( );

	//Set the max points per skill
	Set_Skill_Max ( );

	//set the base skill effectiveness percentages
	Set_Skill_Base ( );

	log_amx( "[UWC3X] Skill Limits Initialized [OK]");
}
public SetAdminOnlySkills ( )
{
	admin_only[SKILLIDX_MINE] = true;
	// [08-01-04] Admin Only sets skills reserved only for admins
	if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
	{
		if ( CVAR_ADMINSKILL_REPAIR == 1 )
		{
			admin_only[SKILLIDX_REPAIR] = true;
		}
		else
		{
			admin_only[SKILLIDX_REPAIR] = false;
		}

		if ( CVAR_ADMINSKILL_NAPALM == 1 )
		{
			admin_only[SKILLIDX_NAPALM] = true;
		}
		else
		{
			admin_only[SKILLIDX_NAPALM] = false;
		}

		if ( CVAR_ADMINSKILL_VOODOO == 1 )
		{
			admin_only[SKILLIDX_VOODOO] = true;
		}
		else
		{
			admin_only[SKILLIDX_VOODOO] = false;
		}

		if ( CVAR_ADMINSKILL_FANOFKNIVES == 1 )
		{
			admin_only[SKILLIDX_FAN] = true;
		}
		else
		{
			admin_only[SKILLIDX_FAN] = false;
		}

		if ( CVAR_ADMINSKILL_VENGANCE == 1 )
		{
			admin_only[SKILLIDX_VENGEANCE] = true;
		}
		else
		{
			admin_only[SKILLIDX_VENGEANCE] = false;
		}

		if ( CVAR_ADMINSKILL_TRUESHOT == 1 )
		{
			admin_only[SKILLIDX_TRUESHOT] = true;
		}
		else
		{
			admin_only[SKILLIDX_TRUESHOT] = false;
		}

		if ( CVAR_ADMINSKILL_BLINK == 1 )
		{
			admin_only[SKILLIDX_BLINK] = true;
		}
		else
		{
			admin_only[SKILLIDX_BLINK] = false;
		}

		if ( CVAR_ADMINSKILL_SUICIDE == 1 )
		{
			admin_only[SKILLIDX_SUICIDE] = true;
		}
		else
		{
			admin_only[SKILLIDX_SUICIDE] = false;
		}


		if ( CVAR_ADMINSKILL_ICENADE == 1 )
		{
			admin_only[SKILLIDX_ICENADE] = true;
		}
		else
		{
			admin_only[SKILLIDX_ICENADE] = false;
		}


		if ( CVAR_ADMINSKILL_CLUSTERNADE == 1 )
		{
			admin_only[SKILLIDX_CLUSTERNADE] = true;
		}
		else
		{
			admin_only[SKILLIDX_CLUSTERNADE] = false;
		}


		if ( CVAR_ADMINSKILL_SMITE == 1 )
		{
			admin_only[SKILLIDX_SMITE] = true;
		}
		else
		{
			admin_only[SKILLIDX_SMITE] = false;
		}


		if ( CVAR_ADMINSKILL_EARTHQUAKE == 1 )
		{
			admin_only[SKILLIDX_EARTHQUAKE] = true;
		}
		else
		{
			admin_only[SKILLIDX_EARTHQUAKE] = false;
		}

		if ( CVAR_ADMINSKILL_ROPE == 1 )
		{
			admin_only[SKILLIDX_ROPE] = true;
		}
		else
		{
			admin_only[SKILLIDX_ROPE] = false;
		}

		if ( CVAR_ADMINSKILL_HOOK == 1 )
		{
			admin_only[SKILLIDX_HOOK] = true;
		}
		else
		{
			admin_only[SKILLIDX_HOOK] = false;
		}

		if ( CVAR_ADMINSKILL_GRAB == 1 )
		{
			admin_only[SKILLIDX_GRAB] = true;
		}
		else
		{
			admin_only[SKILLIDX_GRAB] = false;
		}
		
	}

}


public select_skill(id, page)
{
	if ( !uwc3x )
	{
		return PLUGIN_CONTINUE;
	}

	new skillname[32] = "";
	new message[2048] = "";
	//new temp[512] = "";
	new temp2[256] = "";
	new temp3[32] = "";

	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9);

	page = (page > 0) ? page : 1;
	nSkillsPage[id] = page;

	// Calculate how many skill points can be spent
	new skillpts = get_availskillpts( id );
	new whichset[32] = "";

	format(whichset, 31, "/skillsinfo%d", page);

	format(temp2, 256,"\ySelect Skill: (pg-%d) [%d pts remaining]\w^n", page, skillpts);
	add(message, 2048, temp2);

	format(temp2, 256, "\y(say %s for info about skills on this page) \w^n", whichset );
	add(message, 2048, temp2);

	if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
	{
		format(temp2, 256, "\y[AS] = Admin-Reserved Skills\w^n" );
		add(message, 2048, temp2);
	}

	new startidx = ((page-1) * SKILLS_PER_SET) + 1;
	new endidx = startidx + (SKILLS_PER_SET - 1);

	for (new i=startidx; i <= endidx; i++)
	{
		new vis_i = (i - startidx) + 1;
		new j = sortedskills[i];
		new idx = j;

		new sLevelText[32] = "";
		new admstr[32] = "";

		if (skill_minlev[j] == 0)
		continue;

		if (j <= 8) copy(skillname, 31, skillset1[j]);
		else if (j <= 16) copy(skillname, 31, skillset2[j-8]);
		else if (j <= 24) copy(skillname, 31, skillset3[j-16]);
		else if (j <= 32) copy(skillname, 31, skillset4[j-24]);
		else if (j <= 40) copy(skillname, 31, skillset5[j-32]);
		else if (j <= 48) copy(skillname, 31, skillset6[j-40]);
		else if (j <= 56) copy(skillname, 31, skillset7[j-48]);
		else if (j <= 64) copy(skillname, 31, skillset8[j-56]);

		if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS && admin_only[idx])
		{
			if ( p_level[id] < skill_minlev[idx] )
				format(admstr, 32, "\r[AS] \d");
			else
				format(admstr, 32, "\r[AS] \w");
		}

		if ( p_level[id] < skill_minlev[idx] )
		{
			// Blank out option of level not high enough to train
			format(temp3, 32, "\d");
			add(message, 2048, temp3);

			if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
				format(sLevelText, 32, "[ Lvl %d ]", skill_minlev[idx]);
			else
				format(sLevelText, 32, "[Lvl %d required]", skill_minlev[idx]);

			if (equali(skillname,"NOSKILL"))
				copy(skillname, 31, "coming soon");

			format(temp2, 256, "\d^n%d. %s %s %s  %s\w", vis_i, admstr, skillname, " - ", sLevelText);
		}
		else if (idx == SKILLIDX_SERPWARD)
		{
			// Special ability
			format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key wcward) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if (idx == SKILLIDX_VENGEANCE)
		{
			// Passive ultimate ability - special case
			format(temp2, 256, "^n%d. %s %s %s %d/%d (Passive Ability) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if (idx == SKILLIDX_CAT)
		{
			// Passive ultimate ability - special case
			format(temp2, 256, "^n%d. %s %s %s %d/%d (Passive Ability) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if (idx == SKILLIDX_CRIPPLE)
		{
			// Passive ultimate ability - special case
			format(temp2, 256, "^n%d. %s %s %s %d/%d (Passive Ability) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if ( idx == SKILLIDX_SPLITTER)
		{
			// Passive ultimate ability - special case
			format(temp2, 256, "^n%d. %s %s %s %d/%d (Passive Ability) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if ( idx == SKILLIDX_HOOK )
		{
			// Ultimate with Bind
			format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key wchook) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if ( idx == SKILLIDX_ROPE )
		{
			// Ultimate with Bind
			format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key wcrope) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if ( idx == SKILLIDX_GRAB )
		{
			// Ultimate with Bind
			format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key wcgrab) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if ( idx == SKILLIDX_BLESS )
		{
			// Skill with Bind
			format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key wcbless) %s\w", vis_i,
			admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}
		else if (equali(skillname,"NOSKILL")){
			// Special Case - skill not ready yet
			format(temp2, 256, "^n%d. skill being developed \w", vis_i);
		}
		else
		{
			if (skill_ultimates[idx][0])
				format(temp2, 256, "^n%d. %s %s %s %d/%d (bind key %s) %s\w", vis_i, admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], skill_ultimates[idx], sLevelText);
			else
				format(temp2, 256, "^n%d. %s %s %s %d/%d %s\w", vis_i, admstr, skillname, " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
			}

		add(message, 2048, temp2);
	}

	format(temp3, 32, "^n^n9. Next Page");
	add(message, 2048, temp3);

	format(temp3, 32, "^n^n0. Exit");
	add(message, 2048, temp3);

	show_menu(id, keys, message, -1);

	return PLUGIN_HANDLED;
}

public set_skill ( id, key )
{

	new name[32];
	new skillname[32];
	get_user_name(id, name, 31);


	// Calculate how many skill points can be spent
	new skillpts = get_availskillpts( id );

	if ( (key >= 0) && (key <= 7) )
	{
		// Player chose one of the skill training keys
		new sorted_idx = ((nSkillsPage[id]-1) * SKILLS_PER_SET) + key + 1;
		new skill_idx = sortedskills[sorted_idx];
		new j = skill_idx;

		if (j <= 8)
			copy(skillname, 31, skillset1[j]);
		else if (j <= 16)
			copy(skillname, 31, skillset2[j-8]);
		else if (j <= 24)
			copy(skillname, 31, skillset3[j-16]);
		else if (j <= 32)
			copy(skillname, 31, skillset4[j-24]);
		else if (j <= 40)
			copy(skillname, 31, skillset5[j-32]);
		else if (j <= 48)
			copy(skillname, 31, skillset6[j-40]);
		else if (j <= 56)
			copy(skillname, 31, skillset7[j-48]);
		else if (j <= 64)
			copy(skillname, 31, skillset8[j-56]);

		if ( CVAR_DEBUG_MODE )
		{
			new mapname[32];
			get_mapname(mapname,31);
			new skillcount = get_skillcount( id );
			log_amx( "[UWC3X] DEBUG #4: In set_skill() Mapname=(%s) Player=(%s) skill_key=(%d)<%s> Level=(%d) #Skills=(%d), skillpts=(%d)", mapname, name, key, skillname, p_level[id], skillcount, skillpts );
		}

		// Prevent player from selecting new skills after dropping them - Marticus
		if (dropskill[id])
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_WAIT", MOD);
			}

			return PLUGIN_HANDLED;
		}

		// One of the skills was selected, check applicability
		if ( skillpts <= 0 )
		{
			// Player has no skill pts to spend
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "NO_SKILL_POINTS", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// [08-01-04] Admin-Reserved Skills Check
		if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS && admin_only[skill_idx])
		{
			if (!(get_user_flags(id) & CVAR_ADMIN_SKILL_FLAG ) )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "ADMIN_ONLY_RESERVED" );
				}

				return PLUGIN_HANDLED;
			}
		}

		// [06-08-2004] Changed skills training system, all skills have min. level
		if (p_level[id] < skill_minlev[skill_idx])
		{
			// Player is not yet allowed to train this skill
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SKILL_CANT_LEARN", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// Check if player is trained to the max in this skill
		if (p_skills[id][skill_idx] >= skill_limits[skill_idx])
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SKILL_AT_MAX", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// [07-13-04] More restrictive training system, can only put 1 skill pt into
		// a skill for each level over (or equal) to the min. level to train it
		new allowed_pts = (p_level[id] - skill_minlev[skill_idx] + 1);
		if ((skill_limits[skill_idx] > 1) && (p_skills[id][skill_idx] >= allowed_pts))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SKILL_MAX_TRAINED", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// Specific skill-restrictions follow (some skills dont work with others)
		// [06-10-2004] K2mia - Only allow Steel Skin if Vampiric and Leather Skin trained
		if (skill_idx == SKILLIDX_SSKIN && ((p_skills[id][SKILLIDX_LSKIN] < 3) || !(p_skills[id][SKILLIDX_VAMPIRIC])))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "STEAL_SKIN_NOTICE", MOD);
			}
			return PLUGIN_HANDLED;
		}

		//Can only have one damage based skill, crit strike, fatal strike, true shot
		if ((skill_idx == SKILLIDX_CRITSTRIKE) && ( p_skills[id][SKILLIDX_FATAL] ) )
		{
			if( p_skills[id][SKILLIDX_FATAL] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CRIT_NO_FATAL", MOD);
					client_print(id, print_center, "%L", id, "CRIT_NO_FATAL", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_FATAL) && (p_skills[id][SKILLIDX_CRITSTRIKE] || p_skills[id][SKILLIDX_TRUESHOT] ) )
		{
			if( p_skills[id][SKILLIDX_CRITSTRIKE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "FATAL_NO_CRIT", MOD);
					client_print(id, print_center, "%L", id, "FATAL_NO_CRIT", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_TRUESHOT] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "FATAL_NO_TRUE", MOD);
					client_print(id, print_center, "%L", id, "FATAL_NO_TRUE", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_TRUESHOT) && (p_skills[id][SKILLIDX_FATAL] ) )
		{
			if( p_skills[id][SKILLIDX_FATAL] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "TRUE_NO_FATAL", MOD);
					client_print(id, print_center, "%L", id, "TRUE_NO_FATAL", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}  

		//Cripple -> 2 points in true shot, 3 points in bash
		if (skill_idx == SKILLIDX_CRIPPLE && ( ( p_skills[id][SKILLIDX_BASH] < 3) || ( p_skills[id][SKILLIDX_TRUESHOT] < 2) ) )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "CRIPPLE_NOTICE", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// [06-09-2004] Obe - Allow only one siphon skill
		if ((skill_idx == SKILLIDX_SIPHON) && (p_skills[id][SKILLIDX_SAMMO]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SYPHON_MANA_NOAMMO", MOD);
				client_print(id, print_center, "%L", id, "SYPHON_MANA_NOAMMO", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_SAMMO) && (p_skills[id][SKILLIDX_SIPHON]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SYPHON_AMMO_NOMANA", MOD);
				client_print(id, print_center, "%L", id, "SYPHON_AMMO_NOMANA", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// [06-09-2004] K2mia - Allow only one damage shield skill
		if ((skill_idx == SKILLIDX_CARAPACE) && (p_skills[id][SKILLIDX_THORNS]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "CARAPACE_NO_THORNS", MOD);
				client_print(id, print_center, "%L", id, "CARAPACE_NO_THORNS", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_THORNS) && (p_skills[id][SKILLIDX_CARAPACE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "THORNS_NO_CARAPACE", MOD);
				client_print(id, print_center, "%L", id, "THORNS_NO_CARAPACE", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// [06-09-2004] K2mia - Allow only one of Shadow Strike / Carrion Beetles / ROT / CRIPPLE
		if ((skill_idx == SKILLIDX_SSTRIKE) && ( p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			if( p_skills[id][SKILLIDX_CARRION] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "SHADOW_NO_CARION", MOD);
					client_print(id, print_center, "%L", id, "SHADOW_NO_CARION", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_ROT] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_ROT", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_ROT", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_CRIPPLE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "NO_CRIPPLE", MOD);
					client_print(id, print_center, "%L", id, "NO_CRIPPLE", MOD);
				}
			}

			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_CARRION) && (p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			if( p_skills[id][SKILLIDX_SSTRIKE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_SHADOW", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_SHADOW", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_ROT] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_ROT", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_ROT", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_CRIPPLE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "NO_CRIPPLE", MOD);
					client_print(id, print_center, "%L", id, "NO_CRIPPLE", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}
		
		if ( (skill_idx == SKILLIDX_ROT) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			if( p_skills[id][SKILLIDX_CARRION] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "SHADOW_NO_CARION", MOD);
					client_print(id, print_center, "%L", id, "SHADOW_NO_CARION", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_SSTRIKE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_SHADOW", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_SHADOW", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_CRIPPLE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "NO_CRIPPLE", MOD);
					client_print(id, print_center, "%L", id, "NO_CRIPPLE", MOD);
				}
			}
		
			return PLUGIN_HANDLED;
		}

		if ( (skill_idx == SKILLIDX_CRIPPLE) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_ROT] ) )
		{
			if( p_skills[id][SKILLIDX_CARRION] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "SHADOW_NO_CARION", MOD);
					client_print(id, print_center, "%L", id, "SHADOW_NO_CARION", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_SSTRIKE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_SHADOW", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_SHADOW", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_ROT] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "CARION_NO_ROT", MOD);
					client_print(id, print_center, "%L", id, "CARION_NO_ROT", MOD);
				}
			}

			return PLUGIN_HANDLED;
		}


		//Can only have one - rope, hook or grab
		if ((skill_idx == SKILLIDX_ROPE) && ( p_skills[id][SKILLIDX_HOOK] || p_skills[id][SKILLIDX_GRAB]  ) )
		{
			if( p_skills[id][SKILLIDX_HOOK] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "ROPE_NO_HOOK", MOD);
					client_print(id, print_center, "%L", id, "ROPE_NO_HOOK", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_GRAB] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "ROPE_NO_GRAB", MOD);
					client_print(id, print_center, "%L", id, "ROPE_NO_GRAB", MOD);
				}
			}

			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_HOOK) && (p_skills[id][SKILLIDX_ROPE] || p_skills[id][SKILLIDX_GRAB] ) )
		{
			if( p_skills[id][SKILLIDX_ROPE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "HOOK_NO_ROPE", MOD);
					client_print(id, print_center, "%L", id, "HOOK_NO_ROPE", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_GRAB] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "HOOK_NO_GRAB", MOD);
					client_print(id, print_center, "%L", id, "HOOK_NO_GRAB", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_GRAB) && (p_skills[id][SKILLIDX_HOOK] || p_skills[id][SKILLIDX_ROPE] ) )
		{
			if( p_skills[id][SKILLIDX_HOOK] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "GRAB_NO_HOOK", MOD);
					client_print(id, print_center, "%L", id, "GRAB_NO_HOOK", MOD);
				}
			}
			else if( p_skills[id][SKILLIDX_ROPE] )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "GRAB_NO_ROPE", MOD);
					client_print(id, print_center, "%L", id, "GRAB_NO_ROPE", MOD);
				}
			}
			return PLUGIN_HANDLED;
		}


		// [07-02-2004] K2mia - Allow only one of Vengeance / Suicide Bomber
		if ((skill_idx == SKILLIDX_VENGEANCE) && (p_skills[id][SKILLIDX_SUICIDE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "VENG_NO_SUICIDE", MOD);
				client_print(id, print_center, "%L", id, "VENG_NO_SUICIDE", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_SUICIDE) && (p_skills[id][SKILLIDX_VENGEANCE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SUICICDE_NO_VENG", MOD);
				client_print(id, print_center, "%L", id, "SUICICDE_NO_VENG", MOD);
			}
			return PLUGIN_HANDLED;
		}

		//Napalmn nade or Ice nade
		if ((skill_idx == SKILLIDX_NAPALM) && (p_skills[id][SKILLIDX_ICENADE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "ICE_NO_NAPALM", MOD);
				client_print(id, print_center, "%L", id, "ICE_NO_NAPALM", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_ICENADE) && (p_skills[id][SKILLIDX_NAPALM]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "NAPALM_NO_ICE", MOD);
				client_print(id, print_center, "%L", id, "NAPALM_NO_ICE", MOD);
			}
			return PLUGIN_HANDLED;
		}

		//Crit nade or cluster nade
		if ((skill_idx == SKILLIDX_CLUSTERNADE) && (p_skills[id][SKILLIDX_CRITGREN]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "CRIT_NO_CLUSTER", MOD);
				client_print(id, print_center, "%L", id, "CRIT_NO_CLUSTER", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_CRITGREN) && (p_skills[id][SKILLIDX_CLUSTERNADE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "CLUSTER_NO_CRIT", MOD);
				client_print(id, print_center, "%L", id, "CLUSTER_NO_CRIT", MOD);
			}
			return PLUGIN_HANDLED;
		}
		
		// Allow only one of Fan of Knives / Suicide bomber
		if ((skill_idx == SKILLIDX_SUICIDE) && (p_skills[id][SKILLIDX_FAN]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SUICIDE_NO_FAN", MOD);
				client_print(id, print_center, "%L", id, "SUICIDE_NO_FAN", MOD);
			}
			return PLUGIN_HANDLED;
		}
		else if ((skill_idx == SKILLIDX_FAN) && (p_skills[id][SKILLIDX_SUICIDE]))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "FAN_NO_SUICIDE", MOD);
				client_print(id, print_center, "%L", id, "FAN_NO_SUICIDE", MOD);
			}
			return PLUGIN_HANDLED;
		}		

		// If we make it here the player is able to train this skill

		//Make sure they are not adding an additional point into an existing ultimate
		//Becuase if they are, then they should not get this message as it doesnt count as an additional ultimate
		if ((ultlearned[id] >= p_maxultimates[id]) && ( skill_ultimates[skill_idx][0] ) && p_skills[id][skill_idx] == 0)
		{
			// Player has trained maximum # of ultimate skills
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "ULTIMATE_MAX_ALLOWED", MOD, p_maxultimates[id]);
			}
			return PLUGIN_HANDLED;
		}

		if(equali(skillname,"NOSKILL"))
		{
			// Prevent player from blowing a point on a non-existant skill
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "SKILL_NO_SKILL", MOD);
			}
			return PLUGIN_HANDLED;
		}

		if (p_skills[id][skill_idx])
		{
			if (p_skills[id][skill_idx] == (skill_limits[skill_idx] - 1))
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(0, print_chat, "%L", 0, "NOTICE_MASTERED", MOD, name, skillname);
				}
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "NOTICE_SKILL_TRAINED", MOD, skillname);
				}
			}
		}
		else
		{
			new utext[128] = "";
			if (skill_ultimates[skill_idx][0] && (skill_idx != SKILLIDX_VENGEANCE) )
			{
				format(utext, 128, "%L", id, "NOTICE_ULT_BIND", skill_ultimates[skill_idx]);
			}

			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "NOTICE_SKILL_TRAINED2", MOD, skillname, utext);
			}
		}

		// Increase the player's skill in the skill at index skill_idx
		p_skills[id][skill_idx] += 1;

		//See what adjustments are needed for new skill
		Skills_Check( id, false);
		new utext[128] = "";
		
		if (skill_ultimates[skill_idx][0] && p_skills[id][skill_idx] == 0)
		{

			// Player learned an ultimate skill
			ultimateused[id] = false;
			ultlearned[id]++;
			Set_Ult_Count( id );

			if ( skill_idx == SKILLIDX_VENGEANCE )
			{
				format(utext, 128, "%L", id, "ULTIMATE_VENGANCE" );
			}
			else
			{
				if( IsPassiveSkill(skill_idx) )
				{
					format(utext, 128, "%L", id, "NOTICE_ULT_PASSIVE1" );
				}
				else
				{
					format(utext, 128, "%L", id, "NOTICE_ULT_BIND2", skill_ultimates[skill_idx]);
				}
			}

			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 7.0, 0.1, 0.2, 3);
				show_hudmessage(id, utext);
			}

			icon_controller( id );
		}
		//If they already have a skill point in that ultimate, dont add another ultimate,
		else if ( skill_ultimates[skill_idx][0] && p_skills[id][skill_idx] > 0 )
		{
			if( IsPassiveSkill(skill_idx) )
			{
				format(utext, 128, "%L", id, "NOTICE_ULT_PASSIVE1" );
			}
			else
			{
				format(utext, 128, "%L", id, "NOTICE_ULT_BIND2", skill_ultimates[skill_idx]);
			}

			ultimateused[id] = false;
			if( Util_Should_Msg_Client(id) )
			{
				set_hudmessage(200, 100, 0, -1.0, 0.3, 0, 1.0, 7.0, 0.1, 0.2, 3);
				show_hudmessage(id, utext);
			}

			icon_controller( id );
		}

		displaylevel(id, 3);

		if (skillpts > 1)
		{
			// Player still has skillpts to spend, return to skill menu
			select_skill(id, nSkillsPage[id]);
			Set_Ult_Count( id );
			return PLUGIN_HANDLED;
		}
	}

	if (key == 8)
	{
		// Set global skills page variable
		nSkillsPage[id] = (nSkillsPage[id] < MAX_SKILL_PAGES) ? nSkillsPage[id] + 1 : 1;
		select_skill(id, nSkillsPage[id]);
		return PLUGIN_HANDLED;
	}

	return PLUGIN_HANDLED;
}

public IsPassiveSkill( SKILLIDX )
{

	if( (SKILLIDX == SKILLIDX_SPLITTER ) || (SKILLIDX == SKILLIDX_CAT ) || ( SKILLIDX == SKILLIDX_ROT ) || (SKILLIDX == SKILLIDX_CRIPPLE ) || (SKILLIDX == SKILLIDX_VENGEANCE ) )
	{
		return true;
	}

	return false;

}

public drop_skill(id, page )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new skillname[32] = "";
	new keys = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9);
	new message[2048] = "";
	new temp2[256] = "";
	new temp3[32] = "";

	page = (page > 0) ? page : 1;
	nSkillsPage[id] = page;

	format(temp2, 256,"\yDrop Skill: (pg-%d)\w^n", page);
	add(message, 2048, temp2);

	new startidx = ((page-1) * SKILLS_PER_SET) + 1;
	new endidx = startidx + (SKILLS_PER_SET - 1);

	for (new i=startidx; i <= endidx; i++)
	{
		new vis_i = (i - startidx) + 1;
		new j = sortedskills[i];
		new idx = j;

		new sLevelText[32] = "";
		new admstr[32] = "";

		if (skill_minlev[j] == 0) continue;
		if (j <= 8) copy(skillname, 31, skillset1[j]);
		else if (j <= 16) copy(skillname, 31, skillset2[j-8]);
		else if (j <= 24) copy(skillname, 31, skillset3[j-16]);
		else if (j <= 32) copy(skillname, 31, skillset4[j-24]);
		else if (j <= 40) copy(skillname, 31, skillset5[j-32]);
		else if (j <= 48) copy(skillname, 31, skillset6[j-40]);
		else if (j <= 56) copy(skillname, 31, skillset7[j-48]);
		else if (j <= 64) copy(skillname, 31, skillset8[j-56]);

		if ( p_level[id] < skill_minlev[idx] ){
			// Blank out option of level not high enough to train
			format(temp3, 32, "\d");
			add(message, 2048, temp3);

			if ( CVAR_ENABLE_ADMIN_ONLY_SKILLS )
				format(sLevelText, 32, "[ Lvl %d ]", skill_minlev[idx]);
			else
				format(sLevelText, 32, "[Lvl %d required]", skill_minlev[idx]);

			if (equali(skillname,"NOSKILL"))
				copy(skillname, 31, "coming soon");

			format(temp2, 256, "\d^n%d. %s %s %s  %s\w", vis_i, admstr, skillname, " - ", sLevelText);
		}else if (equali(skillname,"NOSKILL")){
			// Special Case - skill not ready yet
			format(temp2, 256, "^n%d. skill being developed \w", vis_i);
		}else{
			format(temp2, 256, "^n%d. %s %s %s %d/%d %s\w", vis_i, admstr, skillname,
			 " - ", p_skills[id][idx], skill_limits[idx], sLevelText);
		}

		add(message, 2048, temp2);
	}

	format(temp3, 32, "^n^n9. Next Page");
	add(message, 2048, temp3);

	format(temp3, 32, "^n^n0. Exit");
	add(message, 2048, temp3);

	show_menu(id, keys, message, -1);

	return PLUGIN_HANDLED;
}

public unset_skill( id, key )
{

	new skillname[32] ;

	if ( (key >= 0) && (key <= 7) )
	{
		// Player chose one of the skill dropping keys
		new sorted_idx = ((nSkillsPage[id]-1) * SKILLS_PER_SET) + key + 1;
		new skill_idx = sortedskills[sorted_idx];
		new j = skill_idx ;

		if (j <= 8)
			copy(skillname, 31, skillset1[j]);
		else if (j <= 16)
			copy(skillname, 31, skillset2[j-8]);
		else if (j <= 24)
			copy(skillname, 31, skillset3[j-16]);
		else if (j <= 32)
			copy(skillname, 31, skillset4[j-24]);
		else if (j <= 40)
			copy(skillname, 31, skillset5[j-32]);
		else if (j <= 48)
			copy(skillname, 31, skillset6[j-40]);
		else if (j <= 56)
			copy(skillname, 31, skillset7[j-48]);
		else if (j <= 64)
			copy(skillname, 31, skillset8[j-56]);

		if (!get_skillcount(id))
		{
			// Player has no skill pts to drop

			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_NOSKILLS", MOD);
			}

			return PLUGIN_HANDLED;
		}

		//[06-16-07] No longer have to spend all your points before you can drop more skills
		/*
		if ( get_availskillpts(id) && !dropskill[id])
		{
			// Player has no skill pts to drop
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_SPENDFIRST", MOD);
			}
			return PLUGIN_HANDLED;
		}
		*/

		// Fix Steel Skin Bug: do not drop vamp or leather below steel skin
		// prerequisites. -Marticus, 19 Feb 2006
		if ((p_skills[id][SKILLIDX_SSKIN] == 1) && (((skill_idx == SKILLIDX_LSKIN) && (p_skills[id][SKILLIDX_LSKIN] == 3)) || ((skill_idx == SKILLIDX_VAMPIRIC) && (p_skills[id][SKILLIDX_VAMPIRIC] == 1))))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_STEALSKIN", MOD);
			}
			return PLUGIN_HANDLED;
		}

		if ((p_skills[id][SKILLIDX_CRIPPLE] == 1) && (((skill_idx == SKILLIDX_TRUESHOT) && (p_skills[id][SKILLIDX_TRUESHOT] == 2)) || ((skill_idx == SKILLIDX_BASH) && (p_skills[id][SKILLIDX_BASH] == 3))))
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_CRIPPLE", MOD);
			}
			return PLUGIN_HANDLED;
		}

		// Do not drop below 0 in index skill_idx
		if ( p_skills[id][skill_idx] == 0 )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print(id, print_chat, "%L", id, "DROPSKILL_NOPOINTS", MOD, skillname);
			}
			return PLUGIN_HANDLED;
		}
		else
		{

			// Prevent skill points from being reselected this round
			dropskill[id] = true;

			// Decrease the player's skill level in the skill at index skill_idx
			p_skills[id][skill_idx] -= 1;

			//************************************
			//* Added code by lantz69 BEGIN
			//************************************

			// if its an ultimate we are dropping - Lantz69, 22 Feb 2006
			if (skill_ultimates[skill_idx][0])
			{
				ultlearned[id]--;
				Set_Ult_Count( id );
			}

			//Hide the icon for ice bomb
			if( ( skill_idx == SKILLIDX_ICENADE ) && !p_skills[id][SKILLIDX_ICENADE] )
			{
				hasFrostNade[id] = 0;


				if( Util_Should_Msg_Client( id ) )
				{

					message_begin(MSG_ONE,gmsgStatusIcon,{0,0,0},id);
					write_byte(0); // status (0=hide, 1=show, 2=flash)
					write_string("dmg_cold"); // sprite name
					write_byte(FROST_R); // red
					write_byte(FROST_G); // green
					write_byte(FROST_B); // blue
					message_end();
				}
			}

			//************************************
			//* Added code by lantz69 END
			//************************************

			if ( p_skills[id][skill_idx] == 0 )
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "DROPSKILL_UNTRAINED", MOD, skillname) ;
				}
			}
			else
			{
				if( Util_Should_Msg_Client(id) )
				{
					client_print(id, print_chat, "%L", id, "DROPSKILL_DECREASED", MOD, skillname) ;
				}
			}

			if (get_skillcount(id))
			{
				// Player still has skillpts to drop, return to skill menu
				drop_skill(id, nSkillsPage[id]);
				Set_Ult_Count( id );
				return PLUGIN_HANDLED ;
			}
		}
	}

	if (key == 8)
	{
		// Set global skills page variable
		nSkillsPage[id] = (nSkillsPage[id] < MAX_SKILL_PAGES) ? nSkillsPage[id] + 1 : 1;
		drop_skill(id, nSkillsPage[id]);
		return PLUGIN_HANDLED ;
	}

	return PLUGIN_HANDLED ;

}

public get_skillcount( id )
{

	new skillcount = 0;
	for (new j=0; j<MAX_SKILLS; j++)
	{
		if( p_skills[id][j] > 0 )
		{
			skillcount += p_skills[id][j];
		}
	}

	return skillcount;
}

public get_availskillpts( id )
{
	new skillptsavail = 0;
	new skillcount = get_skillcount(id);

	if (skillcount < (CVAR_SKILLPOINTS_PER_LEVEL * p_level[id]) )
	{
		skillptsavail = ( (CVAR_SKILLPOINTS_PER_LEVEL * p_level[id]) - skillcount);
	}

	return skillptsavail;
}

public Skills_Check_SkillSet( id )
{
	if ( !uwc3x )
	return PLUGIN_CONTINUE;

	read_argv(1,str_skillset[id], 255);

	if ( !contain(str_skillset[id],"#") || !contain(str_skillset[id],"-") )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_console, "%L", id, "SKILLSET_BAD" );
		}
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_console, "%L", id, "SKILLSET_RESET_NR");
		}

		resetskill[id] = true;
		set_skillset[id] = true;
	}

	Set_Ult_Count( id );
	return PLUGIN_HANDLED;
}

public Skills_Reset( id )
{
	Reset_Reload( id, true );
}

public Delete_SkillSet( id, skillsetIDX )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( CVAR_SAVED_SKILLSETS )
	{
		if( loadskillset[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "SKILLSET_CANT_DEL_LOAD" );
			}

			return PLUGIN_HANDLED;
		}

		if( saveskillset[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "SKILLSET_CANT_DEL_SAVE" );
			}

			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "DELSKILLSET_ON" );
		}

		deleteskillset[id] = true;
		s_deleteskillset[id] = skillsetIDX;
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "SAVESKILLSET_OFF");
		}

	}

	return PLUGIN_HANDLED;
}
public Save_SkillSet( id, skillsetIDX )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( CVAR_SAVED_SKILLSETS )
	{
		if( loadskillset[id] )
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "SKILLSET_CANT_LOAD_SAVE" );
			}

			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "SAVESKILLSET_ON" );
		}

		saveskillset[id] = true;
		s_saveskillset[id] = skillsetIDX;

	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "SAVESKILLSET_OFF");
		}

	}

	return PLUGIN_HANDLED;

}

public Load_SkillSet( id, skillsetIDX )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( CVAR_SAVED_SKILLSETS )
	{

		if( saveskillset[id] )
		{

			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "SKILLSET_CANT_SAVE_LOAD" );
			}

			return PLUGIN_HANDLED;
		}

		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "LOADSKILLSET_ON" );
		}

		loadskillset[id] = true;
		s_loadskillset[id] = skillsetIDX;

	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "LOADSKILLSET_OFF");
		}
	}

	return PLUGIN_HANDLED;

}

public Skills_Reload( id )
{
	Reset_Reload( id, false );
}

public Reset_Reload ( id, Reset )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if ( CVAR_RESET_SKILLS )
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print( id, print_center, "%L", id, "RESETSKILLS_ON" );
		}

		if( Reset )
		{
			reloadskill[id]=true;
		}
		else
		{
			resetskill[id] = true;
		}
	}
	else
	{
		if( Util_Should_Msg_Client(id) )
		{
			client_print(id, print_center, "%L", id, "RESETSKILLS_OFF");
		}

		if(Reset)
		{
			reloadskill[id] = false;
		}
		else
		{
			resetskill[id] = false;
		}
	}

	return PLUGIN_HANDLED;
}
public Skills_AdminLoad( id )
{
	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	if (!(get_user_flags(id) & CVAR_ADMIN_DEFAULT_FLAG ) )
	{
		if(id != 0)
		{
			if( Util_Should_Msg_Client(id) )
			{
				client_print( id, print_center, "%L", id, "NO_ACCESS");
			}
			return PLUGIN_HANDLED;
		}
	}

	new arg[32];
	read_argv( 1, arg, 31 );

	new set = str_to_num( arg );

	if (set < 1 || set > 4)
	{
		// set will allow multiple skillsets to be saved and retrieved
		set = 1;
	}

	return PLUGIN_HANDLED;
}

public Skills_Check_Tasks( id )
{

	new parm[2];
	parm[0] = id;

	if ( !is_user_connected( id ) )
		return PLUGIN_CONTINUE;

	if (task_exists(TASK_HEAL_IT_NOW + id))
		remove_task(TASK_HEAL_IT_NOW + id);

	if (task_exists( id + TASK_LEATHER_SKIN ) )
		remove_task( id + TASK_LEATHER_SKIN );

	if (p_skills[id][SKILLIDX_HEALWAVE])
	{
		// Healing Wave
		if (task_exists(TASK_HEAL_IT_NOW + id))
			remove_task(TASK_HEAL_IT_NOW + id);

		set_task( 1.0, "Heal_It_Now", TASK_HEAL_IT_NOW + id, parm, 2 );
	}

	if (p_skills[id][SKILLIDX_LSKIN])
	{
		// Leather Skin
		if (get_user_armor( id ) <= 0)
		{
			if (p_skills[id][SKILLIDX_SSKIN])
				give_item( id, "item_assaultsuit" );
			else
				give_item( id, "item_kevlar" );
		}

		set_task( 1.0, "Do_Leather_Skin", id + TASK_LEATHER_SKIN, parm, 2 );
	}

	if(!task_exists( 600 + id ) )
		walker( parm );

	if (!task_exists(50+id))
	{
		if ( CVAR_BLINK_START_DISABLED )
		{
			blinkdelayed[id] = true;
			set_task( CVAR_BLINK_DELAY , "cooldown2", TASK_COOLDOWN2 + id, parm, 1 );
		}
	}

	return PLUGIN_CONTINUE;
}

public Set_Mine_Count( id )
{

	if( is_user_bot( id ) )
	{
		player_b_mine[id] = 0;
	}
	else
	{
		log_amx( "[UWC3X] Setting Mine Count" );
		if (p_skills[id][SKILLIDX_MINE])
		{ 
			player_b_mine[id] = p_mines[p_skills[id][SKILLIDX_MINE]-1];
		}
		else
		{
			player_b_mine[id] = 0;
		}

		log_amx( "[UWC3X] Mine Count = %d", player_b_mine[id] );
	}

	return PLUGIN_CONTINUE;
}

public Set_Ward_Count( id )
{
	if( is_user_bot( id ) )
	{
		serpents[id] = 0;
	}
	else
	{
		if (p_skills[id][SKILLIDX_SERPWARD])
		{
			serpents[id] = p_serpent[p_skills[id][SKILLIDX_SERPWARD]-1];
			if (USE_ENH && (p_attribs[id][ATTRIBIDX_INT] >= INT_SERPENT_LEVEL))
			{
				serpents[id] += INT_SERPENT_BONUS;
			}
		}
		else
		{
			serpents[id] = 0;
		}
	}

	return PLUGIN_CONTINUE;
}

public Set_Blink( id )
{

	if ( p_skills[id][SKILLIDX_BLINK] )
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:blink_chance = p_blink[p_skills[id][SKILLIDX_BLINK]-1];

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug ->Set_Blink :: id=%d randomnumber=%f chance=%f",id , randomnumber, blink_chance);
		}
		
		if ( randomnumber <= blink_chance )
		{
			hasblink[id] = true;
		}
		else
		{
			hasblink[id] = false;
		}
	}
	else
	{
		hasblink[id] = false;
	}
}

public Set_Hook_Count( id )
{
	has_hook[id]=false;
	has_grab[id]=false;
	has_rope[id]=false;
	
	new RopeSkills = p_skills[id][SKILLIDX_ROPE];
	new GrabSkills = p_skills[id][SKILLIDX_GRAB];
	new HookSkills = p_skills[id][SKILLIDX_HOOK];
	
	new RopesAvail = p_ropes[p_skills[id][SKILLIDX_ROPE]];
	new GrabsAvail = p_grabs[p_skills[id][SKILLIDX_GRAB]];
	new HooksAvail = p_hooks[p_skills[id][SKILLIDX_HOOK]];

	if( HookSkills > 0 )
	{
		HookCount[id] = HooksAvail;
		has_hook[id]=true
	}
	if( GrabSkills > 0 )
	{
		GrabCount[id] = GrabsAvail;
		has_grab[id]=true
	}
	if( RopeSkills > 0 )
	{
		RopeCount[id] = RopesAvail;
		has_rope[id]=true
	}
	
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		client_print( id, print_console, "[%s DEBUG] Set_Hook_Count -> Player:%s Points: GRAB:%d HOOK:%d ROPE:%d Available GRAB:%d HOOK:%d ROPE:%d", MOD, debugname,GrabSkills,HookSkills,RopeSkills,GrabsAvail,HooksAvail,RopesAvail );
		log_amx( "[UWC3X] DEBUG :: Set_Hook_Count -> Player:%s Points: GRAB:%d HOOK:%d ROPE:%d Available GRAB:%d HOOK:%d ROPE:%d", debugname,GrabSkills,HookSkills,RopeSkills,GrabsAvail,HooksAvail,RopesAvail );
	}
	
	return PLUGIN_CONTINUE;
}

public Set_Gate_Count( id )
{
	if (p_skills[id][SKILLIDX_GATE])
	{
		// Gate Ultimate, determine number of gates this round by level
		if (p_level[id] >= 30)
			numgates[id] = 3;
		else if (p_level[id] >= 20)
			numgates[id] = 2;
		else
			numgates[id] = 1;
	}

	if( p_skills[id][SKILLIDX_GATE] > 1 )
	{
		numgates[id] = numgates[id] * 2;
	}
	
	gateused[id] = false;
	return PLUGIN_CONTINUE;
}

public Set_Phoenix_Count( id )
{

	if (p_skills[id][SKILLIDX_PHOENIX] && is_user_alive(id))
	{
		new Float:randomnumber = random_float( 0.0, 1.0 );
		new teamnumber = get_user_team( id );
		new Float:pheonix_chance = p_phoenix[p_skills[id][SKILLIDX_PHOENIX]-1];

		if ( CVAR_DEBUG_MODE )
		{
			log_amx( "[UWC3X] Debug ->Set_Phoenix_Count :: id=%d randomnumber=%f teamnumber=%d chance=%f pheonixexistsT=%d pheonixexistsCT=%d",id , randomnumber, teamnumber, pheonix_chance, pheonixexistsT, pheonixexistsCT);
		}
		
		if ( randomnumber <= pheonix_chance )
		{
			phoenix[id] = true;

			if ( teamnumber == TEAM_T)
			{
				pheonixexistsT++;
			}
			else if ( teamnumber == TEAM_CT)
			{
				pheonixexistsCT++;
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public Set_Cat_Footsteps ( id )
{

	if( is_user_bot( id ) )
	{
		return PLUGIN_CONTINUE;
	}

	if( !is_user_connected( id ) )
		return PLUGIN_HANDLED;

	//If they have the skill, and are alive then set their footsteps
	if (p_skills[id][SKILLIDX_CAT])
	{
		if( is_user_alive(id) )
		{
			set_user_footsteps( id , 1 );
		}
	}
	else if ( playeritem2[id] == CAT )
	{
		set_user_footsteps( id , 1 );
	}
	else
	{
		//They do not have the skill - if they are alive set their skills
		if( is_user_alive(id) )
		{
			set_user_footsteps( id , 0 );
		}
	}

	return PLUGIN_CONTINUE;
}

/* Cloak of the chameleon
	Make a Determination based on their percentage chance if they get a cloak at spawn
*/
public Skills_Cloak_Awarded_Sound( parm[1] )
{
	new id = parm[0];

	if( !is_user_connected( id ) || !is_user_alive( id ) )
		return PLUGIN_HANDLED;

	if( Util_Should_Msg_Client_Alive(id) )
	{
		if ( file_exists ( "sound/uwc3x/bond.wav" ) == 1 )
		{
			emit_sound ( id, CHAN_ITEM, "uwc3x/bond.wav", 1.0, ATTN_NORM, 0, PITCH_NORM );
		}

		client_print(id, print_chat, "%L", id, "CLOAK_SKILL_AWARDED", MOD) ;
	}

	return PLUGIN_CONTINUE;
}
public Skills_Award_Cloak ( id )
{

	if( !is_user_connected( id ) || !is_user_alive( id ) )
		return PLUGIN_HANDLED;

	if( !CheckCloak[id] )
	{
		return PLUGIN_CONTINUE;
	}

	//Make sure they have the skill first
	if ( p_skills[id][SKILLIDX_CLOAK] )
	{
		CheckCloak[id] = false;

		new Float:randomnumber = random_float( 0.0, 1.0 );
		new Float:CloakChance = p_cloakskill[p_skills[id][SKILLIDX_CLOAK]-1];

		if ( randomnumber <= CloakChance )
		{
			//If they already have teh chameleon shopmenu2 item, dont do anything
			if ( playeritem2[id] == CHAMELEON )
			{
				if( Util_Should_Msg_Client_Alive(id) )
				{
					client_print(id, print_chat, "%L", id, "CLOAK_SKILL_HAVE_ITEM", MOD) ;
				}
			}
			else
			{
				new parm[1];
				parm[0]=id;

				if( Util_Should_Msg_Client_Alive(id) )
				{
					client_print(id, print_chat, "%L", id, "CLOAK_SKILL_AWARDED", MOD) ;
					client_print(id, print_center, "%L", id, "CLOAK_SKILL_AWARDED2" ) ;
				}

				//Becuase the sound doesnt get played properly at this point, set a task to play it in 2 seconds instead
				//Removed sound and replaced with a client message instead
				//set_task( 2.0, "Skills_Cloak_Awarded_Sound", TASK_CLOAK_AWARD_SOUND, parm, 1 );
				Cloak_changeskin( id );
			}
		}
	}

	return PLUGIN_CONTINUE;
}

public Skills_Check( id, sethealth )
{
	if( !is_user_bot( id ))
	{
		log_amx( "[UWC3X] Entering Skills_Check" );
	}

	new parm[2];
	parm[0] = id;

	if( !is_user_connected( id ) || !is_user_alive( id ) || ( get_user_team ( id ) == SPEC ) )
		return PLUGIN_HANDLED;

	Set_Wisdom_Bonuses( id );

	// Set user id's maxhealth[] for the round
	Event_SetMaxHealth( id, sethealth );

	// Check if constitution regen should be started
	Task_Check_Const_Regen( id );

	// Set user id's maxarmor[] for the round
	Task_Check_Skin_Bonus( id );

	// Check if user id gets blink active this round
	Set_Blink( id );

	// Check for task cleanup/restarts
	Skills_Check_Tasks (id );

	// Give serpant wards if necessary
	Set_Ward_Count( id );

	//Set mine count
	Set_Mine_Count( id );

	// Count phoenixes for each team
	Set_Phoenix_Count( id );

	//Set the hook count for a user
	Set_Hook_Count( id );

	// Set Gate Counts
	Set_Gate_Count( id );

	//Set users footsteps if they have cat skill
	Set_Cat_Footsteps( id );

	icon_controller( id );

	new speedparm[1];
	speedparm[0] = id;
	Set_Speed( speedparm );

	return PLUGIN_CONTINUE;
}

public Set_Speed( parm[1] )
{

	if ( !uwc3x )
		return PLUGIN_CONTINUE;

	new id = parm[0];
	new Float:speed = CVAR_NORMAL_SPEED;

	if ( !is_user_connected( id ) )
		return PLUGIN_CONTINUE;

	if ( p_skills[id][SKILLIDX_UNHOLY] )
	{
		speed = p_unholy[p_skills[id][SKILLIDX_UNHOLY]-1] + ((playeritem[id] == BOOTS) ? 25.0 : 0.00);
	}
	else
	{
		speed = ( playeritem[id] == BOOTS ) ? BOOTSPEED : CVAR_NORMAL_SPEED;
	}

	if ( USE_ENH && ( p_attribs[id][ATTRIBIDX_AGI] > ATTRIB_BASE ) )
	{
		new eagi = ( p_attribs[id][ATTRIBIDX_AGI] - ATTRIB_BASE );
		new Float:espeed = ( float( eagi ) * 8.0 );
		speed += espeed;
	}
	
	if ( !freezetime && !slowed[id] && !stunned[id] && !bIsRotting[id] && !isdiseasedcb[id] && !iscrippled[id]  )
	{
		set_user_maxspeed( id, speed );
	}
	else
	{
		if(speed > 1.0 && speed != oldSpeed[id])
		{
			oldSpeed[id] = speed;
		}

		if ( stunned[id] )
		{
			set_user_maxspeed( id, 1.0 );
			return PLUGIN_HANDLED;
		}
		else if (slowed[id])
		{
			set_user_maxspeed( id, FROSTSPEED );
		}
		else if ( bIsRotting[id] )
		{
			set_user_maxspeed( id, ROTTINGSPEED );
		}
		else if ( isdiseasedcb[id] )
		{
			set_user_maxspeed( id, CBSPEED);
		}
		else if ( iscrippled[id] )
		{
			if( crippletype[id] == 1 )
			{
				set_user_maxspeed( id, CRIPPLESPEED1);
			}
			else if ( crippletype[id] == 2 )
			{
				set_user_maxspeed( id, CRIPPLESPEED2);
			}
		}
		else if (get_user_maxspeed(id) > 10 && !freezetime && ( get_user_maxspeed( id ) < speed ) )
		{
			set_user_maxspeed( id, speed );
		}
	}

	return PLUGIN_CONTINUE;
}

public Skill_Rot_Handler ( id )
{

	new Float:speed = get_user_maxspeed( id );
	if(speed > 1.0 && speed != oldSpeed[id])
	{
		oldSpeed[id] = speed;
	}

	//Set them to stunned, in 2 seconds at the set task it will reset to slowed rotting speed anyways
	set_user_maxspeed( id, 1.0 );

	//SET THEIR ROTTING SPEED
	new parm[1];
	parm[0] = id;
	set_task( 2.0, "Set_Speed", TASK_RESET_MAXSPEED+id, parm, 1 );

}
public Skill_RotUser_Bleed( id )
{
	new color = 248;
	new origin[3];
	get_user_origin(id,origin);

	new dx, dy, dz;

	for(new i = 0; i < 3; i++)
	{
		dx = random_num(-15,15);
		dy = random_num(-15,15);
		dz = random_num(-20,25);

		for(new j = 0; j < 2; j++)
		{
			message_begin(MSG_BROADCAST,SVC_TEMPENTITY);
			write_byte(TE_BLOODSPRITE);
			write_coord(origin[0]+(dx*j));
			write_coord(origin[1]+(dy*j));
			write_coord(origin[2]+(dz*j));
			write_short(sprite_blood_spray);
			write_short(sprite_blood_drop);
			write_byte(color); // color index
			write_byte(8); // size
			message_end();
		}
	}
}


/* HOOK */
public HOOK_beamentpoint(id)
{
	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte( TE_BEAMENTPOINT );
	write_short( id );
	write_coord( hooklocation[id][0] );
	write_coord( hooklocation[id][1] );
	write_coord( hooklocation[id][2] );
	write_short( beam );   // sprite index
	write_byte( 0 );      // start frame
	write_byte( 0 );      // framerate
	write_byte( BEAMLIFE );   // life
	write_byte( 15 );   // width
	write_byte( 2 );     // noise
	write_byte( 255 );   // r, g, b
	write_byte( 255 );   // r, g, b
	write_byte( 255 );   // r, g, b
	write_byte( 150 );   // brightness
	write_byte( 0 );      // speed
	message_end( );
	beamcreated[id] = get_gametime();
	
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: HOOK_beamentpoint -> player %s ", debugname );
	}
	
}

public HOOK_killbeam(id)
{
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: HOOK_killbeam -> player %s ", debugname );
	}

	message_begin( MSG_BROADCAST, SVC_TEMPENTITY );
	write_byte( TE_KILLBEAM );
	write_short( id );
	message_end();
}

public HOOK_release(id)
{

	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: HOOK_release -> player %s pressed wchook bind key twice", debugname );
	}

	hooked[id] = false;
	HOOK_killbeam(id);
	set_user_gravity(id);
	
	if( task_exists(TASK_HOOK + id) )
	{
		remove_task( TASK_HOOK + id);
	}
}

public Hook_boost(id)
{
	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: Hook_boost -> player %s ", debugname );
	}

	new user_origin[3], velocity[3], null[3], A[3];
	get_user_origin(id, user_origin);
	get_entity_velocity(id, velocity);

	null[0] = 0;
	null[1] = 0;
	null[2] = 0;

	A[0] = hooklocation[id][0] - user_origin[0];
	A[1] = hooklocation[id][1] - user_origin[1];
	A[2] = hooklocation[id][2] - user_origin[2];

	velocity[0] += A[0] * BOOSTPOWER / get_distance(null,A);
	velocity[1] += A[1] * BOOSTPOWER / get_distance(null,A);
	velocity[2] += A[2] * BOOSTPOWER / get_distance(null,A);

	set_entity_velocity(id, velocity);
}

public Hook_DEBUG( id )
{

	if( CVAR_DEBUG_MODE )
	{
		new debugname[32];
		get_user_name ( id, debugname, 31 );
		log_amx( "[UWC3X] DEBUG :: Hook_DEBUG -> player %s ", debugname );
	}


}

//Classic hooking function from orginal plugin
public hookstyle_classic(id) 
{

	if ( !hooked[id] ) 
		return;

	if ( !is_user_alive(id) ) 
	{
		HOOK_release(id);
		return;
	}

	Hook_DEBUG( id );
	
	new user_origin[3];
	new A[3], D[3];
	new acceleration, velocity_TA, desired_velocity_TA, distance;
	new velocity[3], null[3];

	if (beamcreated[id] + BEAMLIFE/10 <= get_gametime()) 
	{
		HOOK_beamentpoint(id);
	}

	null[0] = 0;
	null[1] = 0;
	null[2] = 0;

	get_user_origin(id, user_origin);
	get_entity_velocity(id, velocity);

	if (get_distance(user_origin,hooklocation[id]) <= hooklength[id]) 
	{
		hooklength[id] = get_distance(user_origin,hooklocation[id]);
		velocity[2] -= floatround(global_gravity * DELTA_T);
	}
	else 
	{
		A[0] = hooklocation[id][0] - user_origin[0];
		A[1] = hooklocation[id][1] - user_origin[1];
		A[2] = hooklocation[id][2] - user_origin[2];

		D[0] = A[0]*A[2] / get_distance(null,A);
		D[1] = A[1]*A[2] / get_distance(null,A);
		D[2] = -(A[1]*A[1] + A[0]*A[0]) / get_distance(null,A);

		//Fixed Below for runtime error
		//acceleration = - global_gravity * D[2] / get_distance(null,D);

		distance = get_distance(null,D) ? get_distance(null,D) : 1;
		acceleration = - global_gravity * D[2] / distance;

		velocity_TA = (velocity[0] * A[0] + velocity[1] * A[1] + velocity[2] * A[2]) / get_distance(null,A);
		desired_velocity_TA = get_distance(hooklocation[id],user_origin) - hooklength[id];

		velocity[0] += floatround((acceleration * DELTA_T * D[0]) / get_distance(null,D));
		velocity[1] += floatround((acceleration * DELTA_T * D[1]) / get_distance(null,D));
		velocity[2] += floatround((acceleration * DELTA_T * D[2]) / get_distance(null,D));

		velocity[0] += ((desired_velocity_TA - velocity_TA) * A[0]) / get_distance(null,A);
		velocity[1] += ((desired_velocity_TA - velocity_TA) * A[1]) / get_distance(null,A);
		velocity[2] += ((desired_velocity_TA - velocity_TA) * A[2]) / get_distance(null,A);
	}
	set_entity_velocity(id, velocity);
}

//Modes 1 and 2 hook style from spiderman/batgirl on shero
//SpaceDudes reel and SpaceDudes autoreel
public hookstyle_reel(id, bool:autoReel)
{

	if ( !hooked[id] ) 
		return;

	if (!is_user_alive(id)) 
	{
		HOOK_release(id);
		return;
	}

	Hook_DEBUG( id );

	new user_origin[3], user_look[3], user_direction[3], move_direction[3];
	new A[3], D[3], buttonadjust[3];
	new acceleration, velocity_TA, desired_velocity_TA,distance;
	new velocity[3], null[3];

	if ( beamcreated[id] + BEAMLIFE/10 <= get_gametime() ) 
	{
		HOOK_beamentpoint(id);
	}

	null[0] = 0;
	null[1] = 0;
	null[2] = 0;

	get_user_origin(id, user_origin);
	get_user_origin(id, user_look,2);
	get_entity_velocity(id, velocity);

	buttonadjust[0]=0;
	buttonadjust[1]=0;

	if (get_user_button(id)&IN_FORWARD) 
	{
		buttonadjust[0]+=1;
	}
	if (get_user_button(id)&IN_BACK) 
	{
		buttonadjust[0]-=1;
	}
	if (get_user_button(id)&IN_MOVERIGHT) 
	{
		buttonadjust[1]+=1;
	}
	if (get_user_button(id)&IN_MOVELEFT) 
	{
		buttonadjust[1]-=1;
	}
	if (get_user_button(id)&IN_JUMP || (autoReel && !(get_user_button(id) & IN_DUCK) ) )
	{
		buttonadjust[2]+=1;
	}
	if (get_user_button(id)&IN_DUCK) 
	{
		buttonadjust[2]-=1;
	}

	if (buttonadjust[0] || buttonadjust[1]) 
	{
		user_direction[0] = user_look[0] - user_origin[0];
		user_direction[1] = user_look[1] - user_origin[1];

		move_direction[0] = buttonadjust[0]*user_direction[0] + user_direction[1]*buttonadjust[1];
		move_direction[1] = buttonadjust[0]*user_direction[1] - user_direction[0]*buttonadjust[1];
		move_direction[2] = 0;

		velocity[0] += floatround(move_direction[0] * (1.0 * CVAR_HOOK_MOVEACC) * DELTA_T / get_distance(null,move_direction));
		velocity[1] += floatround(move_direction[1] * (1.0 * CVAR_HOOK_MOVEACC) * DELTA_T / get_distance(null,move_direction));
	}
	if (buttonadjust[2] ) 
	{
		hooklength[id] -= floatround(buttonadjust[2] * CVAR_HOOK_REELSPEED * DELTA_T);
	}
	if (hooklength[id] < 100) 
	{
		(hooklength[id]) = 100; // Minimum (rope) size...
	}

	A[0] = hooklocation[id][0] - user_origin[0];
	A[1] = hooklocation[id][1] - user_origin[1];
	A[2] = hooklocation[id][2] - user_origin[2];

	D[0] = A[0]*A[2] / get_distance(null,A);
	D[1] = A[1]*A[2] / get_distance(null,A);
	D[2] = -(A[1]*A[1] + A[0]*A[0]) / get_distance(null,A);

	//Fixed Below for runtime error
	//acceleration = - get_cvar_num("sv_gravity") * D[2] / get_distance(null,D)

	distance = get_distance(null,D) ? get_distance(null,D) : 1;
	acceleration = - global_gravity * D[2] / distance;

	velocity_TA = (velocity[0] * A[0] + velocity[1] * A[1] + velocity[2] * A[2]) / get_distance(null,A);
	desired_velocity_TA = (get_distance(user_origin,hooklocation[id]) - hooklength[id] /*- 10*/) * 4;

	if (get_distance(null,D)>10) 
	{
		velocity[0] += floatround((acceleration * DELTA_T * D[0]) / get_distance(null,D));
		velocity[1] += floatround((acceleration * DELTA_T * D[1]) / get_distance(null,D));
		velocity[2] += floatround((acceleration * DELTA_T * D[2]) / get_distance(null,D));
	}

	velocity[0] += ((desired_velocity_TA - velocity_TA) * A[0]) / get_distance(null,A);
	velocity[1] += ((desired_velocity_TA - velocity_TA) * A[1]) / get_distance(null,A);
	velocity[2] += ((desired_velocity_TA - velocity_TA) * A[2]) / get_distance(null,A);

	set_entity_velocity(id, velocity);
}

//Cheap kids reel from batgirl on shero
//Cheat Web - just drags you where you shoot it...
public hookstyle_cheapreel(id) 
{

	if ( !hooked[id] ) 
		return;

	if (!is_user_alive(id)) 
	{
		HOOK_release(id);
		return;
	}


	Hook_DEBUG( id );

	new velocity[3];
	new user_origin[3];
	new oldvelocity[3];

	get_user_origin(id, user_origin);
	get_entity_velocity(id, oldvelocity);
	new distance = get_distance( hooklocation[id], user_origin );
	if ( distance > 10 ) 
	{
		velocity[0] = floatround( (hooklocation[id][0] - user_origin[0]) * ( 1.0 * CVAR_HOOK_CREELSPEED / distance ) );
		velocity[1] = floatround( (hooklocation[id][1] - user_origin[1]) * ( 1.0 * CVAR_HOOK_CREELSPEED / distance ) );
		velocity[2] = floatround( (hooklocation[id][2] - user_origin[2]) * ( 1.0 * CVAR_HOOK_CREELSPEED / distance ) );
	}
	else 
	{
		velocity[0]=0;
		velocity[1]=0;
		velocity[2]=0;
	}

	set_entity_velocity(id, velocity);
}



















public Bot_Pick_Skills( id )
{
	if( !is_user_bot(id) || !is_user_connected(id) )
	{
		return PLUGIN_HANDLED;
	}

	new name[32];
	get_user_name(id, name, 31);

	// Calculate how many skill points can be spent
	//new skillpts = get_availskillpts( id );
	new skillptamount = CVAR_SKILLPOINTS_PER_LEVEL * p_level[id];
	
	//while( skillpts > 0 )
	while( get_availskillpts( id ) > 0 )
	{
		//if( skillpts >= skillptamount )
		if( get_skillcount( id ) == skillptamount )
			break;

		// Player chose one of the skill training keys
		new key = random_num( 1, 8);
		nSkillsPage[id] = random_num( 1, MAX_SKILL_PAGES );
		new sorted_idx = ((nSkillsPage[id]-1) * SKILLS_PER_SET) + key;

		if( ( MAX_SKILLS -1 ) < sorted_idx )
		{
			continue;
		}

		new skill_idx = sortedskills[sorted_idx];
		//new allowed_pts = ( p_level[id] - skill_minlev[skill_idx] + 1);
		
		if (p_level[id] < skill_minlev[skill_idx])
		{
			continue;
		}
		
		if (p_skills[id][skill_idx] >= skill_limits[skill_idx])
		{
			continue;
		}

		//Changed to look at the limits of the skill in points, and compare to how many they already have
		//This should stop more skill points being spent in an item then there are to spend
		//new allowed_pts = ( skill_limits[skill_idx] );
		new allowed_pts = (p_level[id] - skill_minlev[skill_idx] + 1);

		if ( p_skills[id][skill_idx] >= allowed_pts )
		{
			continue;
		}

		new j = skill_idx;
		new skillname[32];

		if (j <= 8)
			copy(skillname, 31, skillset1[j]);
		else if (j <= 16)
			copy(skillname, 31, skillset2[j-8]);
		else if (j <= 24)
			copy(skillname, 31, skillset3[j-16]);
		else if (j <= 32)
			copy(skillname, 31, skillset4[j-24]);
		else if (j <= 40)
			copy(skillname, 31, skillset5[j-32]);
		else if (j <= 48)
			copy(skillname, 31, skillset6[j-40]);
		else if (j <= 56)
			copy(skillname, 31, skillset7[j-48]);
		else if (j <= 64)
			copy(skillname, 31, skillset8[j-56]);

		new parm[1];
		copy( parm[0], 31, skillname );

		//If it has a bind, skip it
		if( SkillHasBind( parm ) || !SkillForBot ( parm ) )
		{
			continue;
		}

		if (skill_idx == SKILLIDX_SSKIN && ((p_skills[id][SKILLIDX_LSKIN] < 3) || !(p_skills[id][SKILLIDX_VAMPIRIC])))
		{
			continue;
		}

		if (skill_idx == SKILLIDX_CRIPPLE && ( ( p_skills[id][SKILLIDX_BASH] < 3) || ( p_skills[id][SKILLIDX_TRUESHOT] < 2) ) )
		{
			continue;
		}

		if ((skill_idx == SKILLIDX_CARAPACE) && (p_skills[id][SKILLIDX_THORNS]))
		{
			continue;
		}
		else if ((skill_idx == SKILLIDX_THORNS) && (p_skills[id][SKILLIDX_CARAPACE]))
		{
			continue;
		}

		if ((skill_idx == SKILLIDX_SSTRIKE) && ( p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			continue;
		}
		else if ((skill_idx == SKILLIDX_CARRION) && (p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_ROT] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			continue;
		}

		if ( (skill_idx == SKILLIDX_ROT) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_CRIPPLE] ) )
		{
			continue;
		}

		if ( (skill_idx == SKILLIDX_CRIPPLE) && ( p_skills[id][SKILLIDX_SSTRIKE] || p_skills[id][SKILLIDX_CARRION] || p_skills[id][SKILLIDX_ROT] ) )
		{
			continue;
		}

		// [07-02-2004] K2mia - Allow only one of Vengeance / Suicide Bomber
		if ((skill_idx == SKILLIDX_VENGEANCE) && (p_skills[id][SKILLIDX_SUICIDE]))
		{
			continue;
		}
		else if ((skill_idx == SKILLIDX_SUICIDE) && (p_skills[id][SKILLIDX_VENGEANCE]))
		{
			continue;
		}

		//Napalmn nade or Ice nade
		if ((skill_idx == SKILLIDX_NAPALM) && (p_skills[id][SKILLIDX_ICENADE]))
		{
			continue;
		}
		else if ((skill_idx == SKILLIDX_ICENADE) && (p_skills[id][SKILLIDX_NAPALM]))
		{
			continue;
		}

		//Crit nade or cluster nade
		if ((skill_idx == SKILLIDX_CLUSTERNADE) && (p_skills[id][SKILLIDX_CRITGREN]))
		{
			continue;
		}
		else if ((skill_idx == SKILLIDX_CRITGREN) && (p_skills[id][SKILLIDX_CLUSTERNADE]))
		{
			continue;
		}

		//no mines
		if (skill_idx == SKILLIDX_MINE)
		{
			continue;
		}

		// If they have trueshot or crit strike, dont let them get a backfire
		//Instead add another point into what they already have
		if ((skill_idx == SKILLIDX_TRUESHOT) && (p_skills[id][SKILLIDX_CRITSTRIKE]))
		{
			skill_idx = SKILLIDX_CRITSTRIKE;
		}
		else if ((skill_idx == SKILLIDX_CRITSTRIKE) && (p_skills[id][SKILLIDX_TRUESHOT]))
		{
			skill_idx = SKILLIDX_TRUESHOT;
		}

		// If we make it here the player is able to train this skill
		if ((ultlearned[id] >= p_maxultimates[id]) && (skill_ultimates[skill_idx][0]))
		{
			continue;
		}

		if(equali(skillname,"NOSKILL"))
		{
			// Prevent player from blowing a point on a non-existant skill
			continue;
		}

		// Increase the player's skill in the skill at index skill_idx
		p_skills[id][skill_idx] += 1;
		//skillpts--;
	}
	
	//See what adjustments are needed for new skills
	Skills_Check( id, false);
	Set_Ult_Count( id );

	return PLUGIN_CONTINUE;

}

public Skills_PickBotStuff( id )
{
	if( !is_user_bot(id) || !is_user_connected(id) )
	{
		return PLUGIN_HANDLED;
	}

	//pick resists
	Bot_Pick_Resists( id );

	//pick attribs
	Bot_Pick_Attribs( id );

	//pick skills
	Bot_Pick_Skills( id );

	return PLUGIN_CONTINUE;

}
public SkillForBot( parm[1] )
{
	new skillname[32];
	copy( skillname, 31, parm[0]);

	for(new i=0; i < sizeof(SkillsNotForBots); i++)
	{
		if( equali( skillname, SkillsNotForBots[i] ) )
		{
			return false;
		}
	}

	return true;
}
public SkillHasBind( parm[1] )
{
	new skillname[32];
	copy( skillname, 31, parm[0]);

	for(new i=0; i < sizeof(BindSkills); i++)
	{
		if( equali( skillname, BindSkills[i] ) )
		{
			return true;
		}
	}

	return false;
}

public item_mine(id)
{

	if( !player_b_mine[id])
	{
		hudchat_show(id,"%L", id, "MINE_UNTRAINED")
		hudchat_update(id)
		return PLUGIN_CONTINUE
	}

	new count = 0
	new ents = -1
	ents = find_ent_by_owner(ents,"Mine",id)
	while (ents > 0)
	{
		count++
		ents = find_ent_by_owner(ents,"Mine",id)
	}
	
	if (count >= player_b_mine[id])
	{
		hudchat_show(id,"%L", id, "MINE_MAX", player_b_mine[id])
		hudchat_update(id)
		return PLUGIN_CONTINUE
	}

	new origin[3]
	pev(id,pev_origin,origin)
		
	new ent = Spawn_Ent("info_target")
	set_pev(ent,pev_classname,"Mine")
	set_pev(ent,pev_owner,id)
	set_pev(ent,pev_movetype,MOVETYPE_TOSS)
	set_pev(ent,pev_origin,origin)
	set_pev(ent,pev_solid,SOLID_BBOX)
	
	engfunc(EngFunc_SetModel, ent, "models/mine.mdl")  
	engfunc(EngFunc_SetSize,ent,Float:{-16.0,-16.0,0.0},Float:{16.0,16.0,2.0})
	
	drop_to_floor(ent)
	entity_set_float(ent,EV_FL_nextthink,halflife_time() + 0.01) 
	use_addtofullpack = true
	
	new cargs[2];
	cargs[0] = id;
	cargs[1] = ent;
	set_task ( 15.0, "TASK_Cleanup_Mine", TASK_CLEANUP_MINE+id, cargs, 2 );

	hudchat_show(id,"%L", id, "MINE_PLACED")
	hudchat_update(id)
	return PLUGIN_CONTINUE
}



public Use_Mine(id)
{		
	if (!is_user_alive(id) || freezetime)
		return PLUGIN_CONTINUE
	
	/*See if USE button is used for anything else..
	1) Close to bomb
	2) Close to hostage
	3) Close to switch
	4) Close to door
	*/
	
	new Float:origin[3]
	pev(id, pev_origin, origin)
	
	//Func door and func door rotating
	new aimid, body
	get_user_aiming ( id, aimid, body ) 
	
	if (aimid > 0)
	{
		new classname[32]
		pev(aimid,pev_classname,classname,31)
		
		if (equal(classname,"func_door_rotating") || equal(classname,"func_door") || equal(classname,"func_button"))
		{
			new Float:doororigin[3]
			pev(aimid, pev_origin, doororigin)
			
			if (get_distance_f(origin, doororigin) < 70 && UTIL_In_FOV(id,aimid))
				return PLUGIN_CONTINUE
		}
	}
	
	//Bomb condition
	new bomb
	if ((bomb = find_ent_by_model(-1, "grenade", "models/w_c4.mdl"))) 
	{
		new Float:bombpos[3]
		pev(bomb, pev_origin, bombpos)
			
		//We are near the bomb and have it in FOV.
		if (get_distance_f(origin, bombpos) < 100 && UTIL_In_FOV(id,bomb))
			return PLUGIN_CONTINUE
	}

	//Hostage
	new hostage = engfunc(EngFunc_FindEntityByString, -1,"classname", "hostage_entity")
	while (hostage)
	{
		new Float:hospos[3]
		pev(hostage, pev_origin, hospos)
		if (get_distance_f(origin, hospos) < 70 && UTIL_In_FOV(id,hostage))
			return PLUGIN_CONTINUE
		
		hostage = engfunc(EngFunc_FindEntityByString, hostage,"classname", "hostage_entity")
	}
	
	item_mine(id)
	return PLUGIN_CONTINUE
}