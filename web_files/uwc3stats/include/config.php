<?php

/* replace the below with your stuff */

$host = "";
$username = "";
$pass = "";
$dbname = "";
$tbname = "uwc3x";

$SiteTitle = 'My UWC3 Server Stats';
$player_info_page = 'player_info.php';			//this is the default and you should not need to change it, but in case you do...

$UseXPMultiplier = true;
$XPMultiplier = 0.3;

$MaxResists = 20;							//This is the maximum amount of points PER resistance, not total
$playersPerPage = 20;						// default number of players per page
$maxPlayersPerPage = 100;					// maxinum number of players per page (to prevent someone viewing all 3000
$pagesAhead = 12;							// how many pages to show around the current page at the bottom

$_REAL_SCRIPT_DIR = realpath(dirname($_SERVER['SCRIPT_FILENAME'])); 	// filesystem path of this page's directory (page.php)
$_REAL_BASE_DIR = realpath(dirname(__FILE__)); 							// filesystem path of this file's directory (config.php)
$_MY_PATH_PART = substr( $_REAL_SCRIPT_DIR, strlen($_REAL_BASE_DIR)); 	// just the subfolder part between <installation_path> and the page

$INSTALLATION_PATH = $_MY_PATH_PART
	? substr( dirname($_SERVER['SCRIPT_NAME']), 0, -strlen($_MY_PATH_PART) )
	: dirname($_SERVER['SCRIPT_NAME'])
	; 								// we subtract the subfolder part from the end of <installation_path>, leaving us with just <installation_path> :)

?>

