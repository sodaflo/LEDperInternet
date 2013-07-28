<?php
$handle = fopen("farbe","w");
fwrite($handle,$_POST["red"]);
fwrite($handle,'|');
fwrite($handle,$_POST["green"]);
fwrite($handle,'|');
fwrite($handle,$_POST["blue"]);
fwrite($handle,'|');
fclose($handle);
?>
