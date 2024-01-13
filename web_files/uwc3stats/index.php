<?php

	include_once("include/header.php");

	$start = isset($_GET["s"]) ;		// first player on the page
	$ppp = isset($_GET["per"]) ;		// how many players per page if not specified
	$sortby = isset($_GET["sortby"]);
	$order = isset($_GET["order"]);

	if (!$start) $start = 0;
	if (!$ppp) $ppp = $playersPerPage;

	if (!$sortby)
	{
		$sortby = 'xp';
	}
	else
	{
		switch(strtolower($sortby))
		{
			case "steamid":
				$sortby = 'steamid';
				break;
			case "mtime":
				$sortby = 'mtime';
				break;
			case "xp";
				$sortby = 'xp';
				break;
			case "name";
				$sortby = 'name';
				break;
			default:
				$sortby = 'xp';
				break;
		}
	}

	$SortDesc = true;

	if (!$order)
	{
		$order = 'DESC';
	}
	else
	{
		switch(strtolower($order))
		{
			case "desc":
				$order = 'DESC';
				break;
			case "asc":
				$order = 'ASC';
				$SortDesc = false;
				break;
			default:
				$order = 'DESC';
				break;
		}
	}

	if ( $order == "DESC" )
	{
		$newsort = "ASC";
	}
	elseif ( $order == "ASC" )
	{
		$newsort = "DESC";
	}
	else
	{
		$newsort = "DESC";
	}

	// get the mysql
	$link = GetConnection($host, $username, $pass, $dbname);
	$query = "SELECT xp, mtime, steamid, name FROM $tbname WHERE xp > '0' ORDER BY $sortby $order";
	$result = GetResult($query);

	if(!$result)
	{
		exit;
	}

	$totalPlayers = mysqli_num_rows($result);

	// initialize some variables here for easier editing
	if (!$start || $start > $totalPlayers) $start = 0;
	if (!$ppp || $ppp > $maxPlayersPerPage) $ppp = $playersPerPage;

	$limit = $start + $ppp;
	if ( ($start + $ppp) > $totalPlayers) $limit = $totalPlayers ;

	$currentPage = ceil($start / $ppp) + 1;
	$totalPages = floor($totalPlayers / $ppp) + 1;

?>
<br />
<p />&nbsp;&nbsp;<table class="table" align="center" width="90%" cellpadding="5" cellspacing="1" border="0">
	<tr>
		<th class="tbl-hdr">#</th>
		<th class="tbl-hdr">
			<?php
				if($sortby != 'name')
				{
					$newsort = "DESC";
				}
				else
				{
					if($order == "DESC")
						$newsort = "ASC";
				}
			?>

		<a href="<?php echo $STATS_PAGE_NAME;?>?sortby=name&order=<?php echo $newsort;?>"> Name</a>

		</th>
		<th class="tbl-hdr">
			<?php
				if($sortby != 'steamid')
				{
					$newsort = "DESC";
				}
				else
				{
					if($order == "DESC")
						$newsort = "ASC";
				}
			?>

		<a href="<?php echo $STATS_PAGE_NAME;?>?sortby=steamid&order=<?php echo $newsort;?>"> SteamId</a>

		</th>
		<th class="tbl-hdr">
			<?php
				if($sortby != 'xp')
				{
					$newsort = "DESC";
				}
				else
				{
					if($order == "DESC")
						$newsort = "ASC";
				}
			?>

		<a href="<?php echo $STATS_PAGE_NAME;?>?sortby=xp&order=<?php echo $newsort;?>"> XP</a></th>
		<?php
			//<th>Rank</th>
		?>
		<th class="tbl-hdr">

			<?php
				if($sortby != 'mtime')
				{
					$newsort = "DESC";
				}
				else
				{
					if($order == "DESC")
						$newsort = "ASC";
				}
			?>
		<a href="<?php echo $STATS_PAGE_NAME;?>?sortby=mtime&order=<?php echo $newsort;?>"> Last Connected</a></th>

		<th class="tbl-hdr">Level</th>
		<th class="tbl-hdr">#</th>
	</tr>

	<!-- Players start here -->


<?php

	$_PlayerNum = $start +1;

	$query = "SELECT xp, mtime, steamid, name FROM $tbname WHERE xp > '0' ORDER BY $sortby $order LIMIT $start, $ppp";
	$result = GetResult($query);

	if(!$result)
	{
		exit;
	}

	while ($uwc3 = mysqli_fetch_array($result, MYSQLI_ASSOC))
	{
		$_CellColor = getCellColor($player);
		$SteamID = $uwc3["steamid"];
		$XP = $uwc3["xp"];
		$Name = $uwc3["name"];
		$MTime = formatTime($uwc3["mtime"]);
		$PlayerLevel = GetPlayerLevel($XP);

		echo "<tr class=\"$_CellColor\">" ;
		echo "<td>$_PlayerNum</td>" ;
		echo "<td><a href=\"$player_info_page?steamid=$SteamID&nset=1\"><b>$Name</b></a></td>";
		echo "<td><a href=\"$player_info_page?steamid=$SteamID&nset=1\"><b>$SteamID</b></a></td>";
		echo "<td>$XP</td>" ;
		echo "<td>$MTime</td>";
		echo "<td>$PlayerLevel</td>" ;
		echo "<td>$_PlayerNum</td>" ;
		echo "</tr>" ;

		$_PlayerNum++;
	}

?>
	<tr>
		<td align="center" colspan="8">
			<?php

			// All of the page count stuff is here.  There may be a better way, but this looks good and works well

			// skip back a few
			$skip = ($currentPage - 2 - $pagesAhead * 2) * $ppp ;
			if ($skip < 0) $skip = 0 ;

			// skip to beginning
			if($currentPage != 1)
			{
				echo "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=0\"><<</a>&nbsp;&nbsp;" ;
				echo "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=".$skip."&per=".$ppp."\"><</a>&nbsp;&nbsp;" ;
			}
			else
			{
				echo '<<&nbsp;&nbsp;' ;
				echo '<&nbsp;&nbsp;' ;
			}

			// keep track of how many page links are at the bottom
			$counter = $pagesAhead ;
			// move back one page
			$str = "" ;
			for ($i = $currentPage - 1; $i > 0;  $i--)
			{
				$str = "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=".( ($i - 1) * $ppp)."&per=".$ppp."\">".$i."</a>&nbsp;&nbsp;".$str;

				$counter--;
				if ($counter <= 0)
					break;
			}
			echo $str;

			// write the current page
			echo "<b>".$currentPage."</b>&nbsp;&nbsp;" ;

			// reset how many page links are at the bottom
			$counter = $pagesAhead;
			// move ahead one page
			for ($i = $currentPage + 1; $i < $totalPages;  $i++)
			{

				echo "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=".( ($i - 1) * $ppp)."&per=".$ppp."\">".$i."</a>&nbsp;&nbsp;";

				$counter--;
				if ($counter <= 0)
					break;
			}

			// skip ahead a few
			$skip = ($currentPage + $pagesAhead * 2) * $ppp ;

			if ($skip > (($totalPages - 1) * $ppp))
				$skip = ($totalPages - 1) * $ppp ;

			// skip to the end
			if($currentPage != $totalPages)
			{
				echo "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=".$skip."&per=".$ppp."\">></a>&nbsp;&nbsp;" ;
				echo "<a href=\"$STATS_PAGE_NAME?sortby=$sortby&order=$order&s=".($totalPages - 1) * $ppp."&per=".$ppp."\">>></a>";
			}
			else
			{
				echo '>>&nbsp;&nbsp;' ;
				echo '>&nbsp;&nbsp;' ;
			}

			?>
		</td>
	</tr>
	<tr>
		<td align="center" colspan="8">
			Page <?php echo $currentPage?>, Showing Players <?php echo $start +1 ;?> - <?php echo $_PlayerNum;?>
		</td>
	</tr>
</table>

<?php

include_once("include/footer.php");

?>