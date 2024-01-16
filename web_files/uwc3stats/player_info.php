<?php

	include_once("./include/header.php");
	
	$SteamID = $_GET["steamid"] ?? null;

	if($SteamID == NULL )
		$SteamID = $_POST["steamid"] ?? null;

	$bValid = IsValidSteamID( $SteamID );
	$bFoundPlayer = false;
	$NumResults = 0;

	if($bValid)
	{
		// get the mysql
		$link = GetConnection($host, $username, $pass, $dbname);
		$query = "SELECT * FROM $tbname WHERE steamid='$SteamID'";
		$result = GetResult($query);
		$NumResults = mysqli_num_rows($result);
	}

?>

<div align="center">
  <p class="tbl-hdr"><font size="4"><strong><a href="./">CharSheet</a></strong></font></p>
  <table width="600" border="0" cellpadding="3" >
    <tr class="row1">
      <td class="text" colspan="2">

	  <p align="center"><strong><font size="3">
		<?php

			if(!$bValid)
			{
				echo 'You have entered or searched for a player using an invalid Steam ID.';
				echo '<br>Please correct the error and try again.';
				echo '<br><a href="index.php">Back</a>';
				$NumResults = 0;
			}
			else
			{

				if( $NumResults != 0 )
				{

					$Name = mysql_result($result, 0, "name"); //mysql_result deprecated since PHP 7.* , using polyfill
					$xp = mysql_result($result, 0, "xp");
					$level = GetPlayerLevel($xp);
					$xpNextlevel = GetXPForNextLevel($level+1);
					$xpDiff = GetXPDifference($xp, $xpNextlevel);
					$rank = GetPlayerRank($level);

					echo '<br><a href="index.php">Back</a><br>';

					?>

					<table cellpadding="5" cellspacing="5" class="table">
						<tr class="tbl-hdr">
							<th  class="label" colspan="2" align="center"><a href="">User Info</a></th>
						</tr>
						<tr>
							<td>Name</td>
							<td><?php echo $Name;?></td>
						</tr>
						<tr>
							<td>ID</td>
							<td><?php echo $SteamID;?></td>
						</tr>
						<tr>
							<td>XP</td>
							<td><?php echo $xp;?>/<?php echo $xpNextlevel;?></td>
						</tr>
						<tr>
							<td>XP needed to Level</td>
							<td><?php echo $xpDiff;?></td>
						</tr>
						<tr>
							<td colspan="2" align="center"> <a href="" onClick="openpopup('xptable.php')">View XP Table</a></td>
						</tr>
						<tr>
							<td>Level</td>
							<td><?php echo $level;?></td>
						</tr>
						<tr>
							<td>Rank</td>
							<td><?php echo $rank;?></td>
						</tr>
					</table>

					<?php

				}
				else
				{
					echo 'Your search for ' . $SteamID . ' did not find any data - Please try again.';
					echo '<br><a href="index.php">Back</a>';
				}
			}

		?>
		</font></strong></p></td>
    </tr>

	<?php
		if( $NumResults != 0 )
		{
		?>
    <tr class="tbl-hdr">
      <th class="label" width="50%"><font size="4"><a href="javascript:openpopup('attributes.htm')">Attributes</a></font></th>
      <th class="label"><font size="4"><font size="4"><a href="javascript:openpopup('resistances.htm')">Resistances</a></font></th>
    </tr>
    <tr class="row1">
      <td class="text"><p align="center"><strong>
      	  Strength: <?php echo mysql_result($result, 0, "att1");?>/18<br>
          Intellect: <?php echo mysql_result($result, 0, "att2");?>/18<br>
          Dexterity: <?php echo mysql_result($result, 0, "att3");?>/18<br>
          Agillity: <?php echo mysql_result($result, 0, "att4");?>/18<br>
          Constitution: <?php echo mysql_result($result, 0, "att5");?>/18<br>
          Wisdom: <?php echo mysql_result($result, 0, "att6");?>/18</strong></p></td>
      <td class="text"><p align="center"><strong> Poison: <?php echo mysql_result($result, 0, "res1");?>/<?php echo $MaxResists;?><br>
          Disease: <?php echo mysql_result($result, 0, "res2");?>/<?php echo $MaxResists;?><br>
          Electricity: <?php echo mysql_result($result, 0, "res3");?>/<?php echo $MaxResists;?><br>
          Fire: <?php echo mysql_result($result, 0, "res4");?>/<?php echo $MaxResists;?><br>
          Magic: <?php echo mysql_result($result, 0, "res5");?>/<?php echo $MaxResists;?><br>
          Rot: <?php echo mysql_result($result, 0, "res6");?>/<?php echo $MaxResists;?><br>
          </strong></p></td>
    </tr>
    <tr class="text">
      <th colspan="2">&nbsp;</th>
    </tr>
    <tr class="tbl-hdr">
      <th class="label" colspan="2"><font size="4"><a href="javascript:openpopup('skills.htm')">Skills Trained</a></font></th>
    </tr>

	<?php


		for($i = 0; $i + 24 <= sizeof($Skills["Name"] ) -1; $i++)
		{
			$j = $i + 24;

			$ii = $i + 1;
			$jj = $j + 1;

			echo '<tr class="row1">
			  <td><strong>' . $ii .'. ' . $Skills["Name"][$i] . ': ' . mysql_result($result, 0,'skill' . $ii) . '/' . $Skills["MaxPoints"][$i] . '</strong></td>
			  <td><strong>' . $jj .'. ' . $Skills["Name"][$j] . ': ' . mysql_result($result, 0,'skill' . $jj) . '/' . $Skills["MaxPoints"][$j] . '</strong></td>
			</tr>';
		}
	}

	?>

    <tr class="row1">
      <td colspan="2" align="center"><br><a href="index.php">Back</a><br></td>
    </tr>
  </table>
</div>


<?php

include_once("include/footer.php");

?>