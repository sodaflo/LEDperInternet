<?php
$handle = fopen("farbe","w");
fwrite($handle, '|');
fwrite($handle,$_GET["red"]);
fwrite($handle,'|');
fwrite($handle,$_GET["green"]);
fwrite($handle,'|');
fwrite($handle,$_GET["blue"]);
fwrite($handle,'|');
fclose($handle);
?>
<!doctype html>
<html>
<head>
	<meta charset="utf-8" />
	<title>LEDperInternet</title>
	<style>
		*{
			font-family:sans-serif;
			color:black;
		}
		body{
			width:70%;
			margin:100px auto;
		}
		table, td{
			border:0px solid lightgray;
		}
		#farbe{
			width:100px;
			height:100px;
			background-color:rgb(<?php echo $_GET["red"] . ", " . $_GET["green"] . ", " . $_GET["blue"]; ?>);
		}
	</style>
<body>
	<a href="https://github.com/sodaflo/LEDperInternet"><img style="position: absolute; top: 0; right: 0; border: 0;" src="./forkme.png" alt="Fork me!" /></a>
	<h1>LED eingestellt!</h1>
	<p>
		Folgende Farbe wird nun angezeigt:
	</p>
	
	<div id="farbe"></div>
	
	<p>
		<a href="./set.html">Eine neue Farbe einstellen</a>
	</p>
</body>
</html>