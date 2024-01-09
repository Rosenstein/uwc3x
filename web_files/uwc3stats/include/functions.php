<?php
		
		$MAX_LEVEL = 50;
		$g_link = false;
		$g_result;

		$Skills = array("Name" => array("Vampiric Aura", "Levitation", "Devotion Aura", "Equipment Reincarnation", "Healing Wave", "Siphon Mana", 
		"Impale", "Leather Skin", "Unholy Aura", "Bash", "Critical Strike", "Repair Armor", "Banish","Hex", "Spiked Carapace", "Mend Wounds", 
		"Evasion", "Trueshot Aura", "Steel Skin", "Carrion Beetles", "Shadow Strike", "Entangle Roots", "Flame Strike", "Dispell Hex", 
		"Critical Grenade", "Serpent Ward", "Thorns Aura", "Invisibility", "Teleport", "Big Bad Voodoo", "Fan of Knives", "Vengeance" , 
		"Siphon Ammo", "Blink", "Phoenix", "Napalm Grenades", "Gate", "Suicide Bomber", "Chain Lightning", "Decoy", "Jump Kick", "Multi Jump", 
		"Wind Walker", "Rot", "Syv Shield", "Depower", "Cloak of the chameleon", "Cripple", "Flash of Light", "Locust Swarm", "Disorient", 
		"Endless Ammo", "Earth Quake", "Smite", "Cluster Bomb", "Ice Bombs", "NEWSKILL9", "NEWSKILL10", "NEWSKILL11", "NEWSKILL12", 
		"NEWSKILL13", "NEWSKILL14", "NEWSKILL15", "NEWSKILL16"),
		
		"MaxPoints" =>  array(10,10,10,3,10,3,10,10,10,10,5,1,10,10,10,3,5,10,10,10,10,1,1,1,10,3,10,10,1,1,3,1,3,5,5,1,1,1,1,1,3,
			3,1,1,5,1,5,1,1,1,1,1,3,1,4,1,1,1,1,1,1,1,1,1));
		
		$Levels = array( "xp" => array() );
						
		$RankTitles = array( "Orc Fodder", "Elf Acolyte", "Human Squire", "Undead Soldier", "Skilled Combatant", "Crypt Lord Zealot", "Arch Lich", "Blood Elf Champion", "Demon Hunter", "Emissary of Death", "Warchief", "World Destroyer" );
		$XP_PER_LEVEL_BASE_LT = 38400;
		$XP_PER_LEVEL_LT = 12800;
		$xplevel_base_LT = array(0,150,300,600,1100,2000,3600,6400,12800,25600,38400);

		$XPAmount = 0;
		$XPGiven = 0;
		$XP_BASE = 60;
		$XP_ADD_LEVEL = 20;

		$xplevel_lev = array();
		$xpgiven_lev = array();

		  $counter = 0;

		  for ($j = 0; $j < $MAX_LEVEL; $j++)
		  {

		   if ($j <= 10)
		   {
			$xplevel_lev[$j] = $xplevel_base_LT[$j];
		   }
		   else
		   {
			$xplevel_lev[$j] = $XP_PER_LEVEL_BASE_LT + ( ($j - 10) * $XP_PER_LEVEL_LT) + round( (($j/20) * $XP_PER_LEVEL_LT));
		   }

		   $xpgiven_lev[$j] = ( $XP_BASE + ($j * $XP_ADD_LEVEL) ) / 4;

		   if ( $UseXPMultiplier )
		   {
			$xplevel_lev[$j] = round( ($xplevel_lev[$j] * $XPMultiplier) );

			if ($j >= 30)
			{
			 $xplevel_lev[$j] = $xplevel_lev[$j] + round( $xplevel_lev[$j-1] * 1.25 );
			}
			else if ($j >= 20)
			{
			 $xplevel_lev[$j] = $xplevel_lev[$j] + round( $xplevel_lev[$j-1] * 1.00 );
			}
			else if ($j >= 10)
			{
			 $xplevel_lev[$j] = $xplevel_lev[$j] + round( $xplevel_lev[$j-1] * 0.75 );
			}
			else
			{
			 if ($j >= 1)
			 {
				 $xplevel_lev[$j] = $xplevel_lev[$j] + round( $xplevel_lev[$j-1] * 0.50 );
			 }
			}
		   }

		   $Levels["xp"][$j] = $xplevel_lev[$j];
		   //echo '<br />' . "$j.) " . $Levels["xp"][$j];
		   $counter++;
		  }

		  $LevelSize = $counter;


    function GetConnection($dbhost, $dbuser, $dbpass, $dbname)
    {
        global $g_link;

        if( $g_link )
            return $g_link;

        $g_link = mysql_connect( $dbhost, $dbuser, $dbpass);

		if (!$g_link)
		{
			die('Could not connect: <br />' . mysql_error() . '<br /><br /> Please make sure that you have properly configured your config.php file');
		}

        mysql_select_db($dbname, $g_link) or die('Could not select database. <br />' . mysql_error());

        return $g_link;
    }

	function GetResult($query)
	{
		global $g_result;
		global $g_link;

		if($g_result)
		{
			CleanUpResult();
		}

		if(!$g_link)
			die("Not connected to the database, can not run query");

		$query = mysql_prepare($query);
		$g_result = mysql_query($query) or die("Query failed : " . mysql_error());

		return $g_result;

	}

	function CleanUpResult()
	{
		global $g_result;

		if($g_result)
		{
			mysql_free_result($g_result);
		}

		$g_result = false;

	}

	function DoDBCleanUP()
	{
		CleanUpResult();
		CleanUpDB();
	}

    function CleanUpDB()
    {
        global $g_link;

        if( $g_link )
		{
            mysql_close($g_link);
		}

        $g_link = false;
    }

	function mysql_prepare ($query, $phs = array())
	{
		$phs = array_map(create_function('$ph', 'return "\'".mysql_real_escape_string($ph)."\'";'), $phs);
		$curpos = 0;
		$curph  = count($phs)-1;

		for ($i=strlen($query)-1; $i>0; $i--)
		{

			if ($query[$i] !== '?')
			{
				continue;
			}

			if ($curph < 0 || !isset($phs[$curph]))
			{
				$query = substr_replace($query, 'NULL', $i, 1);
			}
			else
			{
				$query = substr_replace($query, $phs[$curph], $i, 1);
			}

			$curph--;
		}

		unset($curpos, $curph, $phs);
		return $query;
	}

	function getCellColor(&$where)
	{
		if ($where%2) {
			$color="tbl-shade1" ;
		} else {
			$color="tbl-shade2" ;
		}
		$where++ ;

		return $color;
	}

	function formatTime($time)
	{
		$_Time = explode(" ", $time);
		$_Date = explode("/", $_Time[0]);

		$ampm = 'am';

		$temp = explode(":",$_Time[1]);

		if( (int)$temp[0] > 12 )
		{
			$hour = (int)$temp[0] - 12;
			$ampm = 'PM';
		}
		else
		{
			$ampm = 'AM';
			$hour = (int)$temp[0];
		}

		$RealTime = "$hour:$temp[1] $ampm";

		$str = "$_Date[1]/$_Date[0]/$_Date[2] $RealTime";
		return $str;
	}

	function true_url_path()
	{
		return $_ENV['SCRIPT_URL'];
	}

	function GetXPForNextLevel ($playerlevel )
	{
		global $Levels;
		global $LevelSize;

		if ( $playerlevel > 0 )
		{
			return $Levels["xp"][$playerlevel +1];
		}
		else
		{
			return 1;
		}

	}

	function GetXPForLevel ( $playerlevel )
	{
		global $Levels;

		if ( $playerlevel > 0 )
		{
			return $Levels["xp"][$playerlevel];
		}
		else
		{
			return 1;
		}

	}

	function GetXPDifference ( $xpHas, $xpNeeded )
	{
		return ($xpNeeded - $xpHas);
	}

	function ShowXPTable()
	{
		global $Levels;
		global $MAX_LEVEL;

		for ($j=1; $j<$MAX_LEVEL; $j++)
		{
			echo '[level ' . $j . ']  XP: ' . ( $Levels["xp"][$j] - $Levels["xp"][$j-1] ) . '  Total XP: ' . $Levels["xp"][$j] . '<br />';
		}
	}

	function GetPlayerLevel($xp)
	{
		global $Levels;
		global $xplevel_lev;
		global $MAX_LEVEL;
		$player_level = 0;

		if ( $xp < 0 )
		{
			$xp = 0;
		}

		if ($xp >= $xplevel_lev[1])
		{
			for ($i=1; $i<$MAX_LEVEL; $i++)
			{
				if ($xp >= $xplevel_lev[$i])
				{
					$player_level = $i;
				}
			}
		}

		return $player_level;
	}

	function GetPlayerRank($Level)
	{
		global $RankTitles;

		$RANK2_LEVEL = 5;    // Level needed for 2nd rank
		$RANK3_LEVEL = 8;   // Level needed for 3rd rank
		$RANK4_LEVEL = 12;    // Level needed for 4th rank
		$RANK5_LEVEL = 16;    // Level needed for 5th rank
		$RANK6_LEVEL = 20;    // Level needed for 6th rank
		$RANK7_LEVEL = 24;    // Level needed for 7th rank
		$RANK8_LEVEL = 28;    // Level needed for 8th rank
		$RANK9_LEVEL = 30;    // Level needed for 9th rank
		$RANK10_LEVEL = 32;   // Level needed for 10th rank
		$RANK11_LEVEL = 34;   // Level needed for 11th rank
		$RANK12_LEVEL = 38;   // Level needed for 12th rank

		$PlayerRank =  $RankTitles[0];

		// Set the player's rank title
		if ( intval( $Level ) >= $RANK12_LEVEL )
			$PlayerRank =  $RankTitles[11];
		else if ( intval( $Level ) >= $RANK11_LEVEL )
			$PlayerRank =  $RankTitles[10];
		else if ( intval( $Level ) >= $RANK10_LEVEL )
			$PlayerRank =  $RankTitles[9];
		else if ( intval( $Level ) >= $RANK9_LEVEL )
			$PlayerRank =  $RankTitles[8];
		else if ( intval( $Level ) >= $RANK8_LEVEL )
			$PlayerRank =  $RankTitles[7];
		else if ( intval( $Level ) >= $RANK7_LEVEL )
			$PlayerRank =  $RankTitles[6];
		else if ( intval( $Level ) >= $RANK6_LEVEL )
			$PlayerRank =  $RankTitles[5];
		else if ( intval( $Level ) >= $RANK5_LEVEL )
			$PlayerRank =  $RankTitles[4];
		else if ( intval( $Level ) >= $RANK4_LEVEL )
			$PlayerRank =  $RankTitles[3];
		else if ( intval( $Level ) >= $RANK3_LEVEL )
			$PlayerRank =  $RankTitles[2];
		else if ( intval( $Level ) >= $RANK2_LEVEL )
			$PlayerRank =  $RankTitles[1];

		return $PlayerRank;
	}

	function IsValidSteamID($SteamID)
	{
		if($SteamID == NULL)
			return false;

		$SteamID = strtoupper($SteamID);

		if(substr($SteamID,0,6) != 'STEAM_')
			return false;

		$_temp = explode(":", $SteamID);

		if(sizeof($_temp) != 3)
			return false;

		return true;
	}






?>