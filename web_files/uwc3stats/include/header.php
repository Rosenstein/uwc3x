<?php

require_once("./include/config.php");
require_once("./include/functions.php");

$STATS_PAGE_NAME = $_SERVER['SCRIPT_NAME'];

?>

<!DOCTYPE html>
<html lang="en">
<head>
	<title><?php echo $SiteTitle; ?></title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE">
	<meta HTTP-EQUIV="Pragma" CONTENT="no-cache">
	<link rel="stylesheet" href="./css/style.css">
</head>
<body>

<script type="text/javascript">
	function openpopup(popurl){
	var winpops=window.open(popurl,"","width=650,height=1000,status,scrollbars,resizable")
}
</script>

<table width="70%" border="0" align="center" cellpadding="0" cellspacing="0" class="main-canvas">
  <tr>
    <td class="main-left"><img src="./images/spacer.gif" width="1" height="1"></td>
    <td>
      <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="main-bg">
        <tr>
          <td class="main-top"><img src="./images/spacer.gif" width="1" height="1"></td>
        </tr>
        <tr>
          <td align="left" valign="middle" height="20">
		<table align="center" width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr><td align="center">
				&nbsp;

<table align="center">

<form name="form" method="POST" action="<?php echo $player_info_page; ?>">
<input type="hidden" value="searchpost" />
  <tr class='row1'>
    <th align='center'>&nbsp;Search for Player by STEAM ID</th>
    <td >&nbsp;
    	<input type="text" name="steamid" size="20" class="skugga" />
    </td>
    <td>&nbsp;
    	<input type="submit" value="Search" name="B2" />&nbsp;
    </td>
 </tr>
</form>
</table>



			</td>
		</tr>
	</table>
       </td>
      </tr>
      <tr>
       <td class="main-bottom"><img src="./images/spacer.gif" width="1" height="1"></td>
      </tr>
    </table>
<table align="center" width="100%" cellspacing="0" cellpadding="0">
  	<tr><td colspan="4"><img src="./images/spacer.gif" height="6" width="1" alt="" /></td></tr>
</table>

<table width="100%" border="0" cellspacing="10" cellpadding="0">
	<tr valign="top">
      		<td width="100%" align="center">
<table width="100%" border="0" cellpadding="1" cellspacing="0" class="tbl-frame1">
	<tr>
	<td>
		<table width="100%" border="0" cellpadding="5" cellspacing="0" class="tbl-shade1">
    	<tr>
    		<td class="text">
		<table width="100%" border="0" cellpadding="1" cellspacing="0" class="tbl-frame1">
        	<tr><td width="100%">
        		<table width="100%" border="0" cellpadding="0" cellspacing="0" class="tbl-shade4">
          		<tr><td class="text">

