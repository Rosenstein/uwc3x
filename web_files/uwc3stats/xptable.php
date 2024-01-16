<!DOCTYPE html>
<html lang="en">
<head>
<title>XP Table</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="stylesheet" href="./css/style.css">
</head>
<body>
<center><a href="javascript:window.close();">Close Window</a></center><br>
<center><text-block>
	<?php
		require_once("./include/config.php");
		require_once("./include/functions.php");
		ShowXPTable();
	?>
</text-block></center><br>
<center><a href="javascript:window.close();">Close Window</a></center>
</body>
</html>
