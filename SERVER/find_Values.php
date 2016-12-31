<?php

function findTBarcode($TBarcode) {
	$con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	mysql_select_db(DB_DATABASE,$con) or die ('Can\'t use the database : ' . mysql_error());
	$sql="SELECT Lab.DayLab, Lab.TimeLab, Lesson.LAliasName FROM Lab INNER JOIN Lesson ON Lab.LsId = Lesson.LsId WHERE TBarcode = '$TBarcode'";
	$result = mysql_query($sql);
	if( mysql_num_rows($result)==0) {
		return '+';
		exit;
	} else {
		$i=0;
		$d=array();
		while($row = mysql_fetch_array($result) ) {
			$d[$i]=$row['LAliasName']."_".$row['DayLab']."_".$row['TimeLab'];
			$i++;
		}
		$found=$d;
		return $found;
	}
	mysql_close($con);
}

function findSBarcode($SBarcode) {
	$con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	mysql_select_db(DB_DATABASE,$con) or die(mysql_error());
	$sql="SELECT * FROM student WHERE SBarcode='$SBarcode'";
	$result = mysql_query($sql);
	if( mysql_num_rows($result)==0) {
		return "%";
	} else {
		return "(";
	}
	mysql_close($con);
}

function findLId($DayLab,$TimeLab,$LAliasName) {
	$con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	mysql_select_db(DB_DATABASE,$con) or die(mysql_error());
	$sql="SELECT lab.LId FROM Lab INNER JOIN Lesson ON Lab.LsId = Lesson.LsId WHERE lab.DayLab = '$DayLab' AND lab.TimeLab = '$TimeLab' AND Lesson.LAliasName = '$LAliasName'";
	$result = mysql_query($sql);
	if( mysql_num_rows($result)==0) {
		die('Could not connect:'.mysql_error());
	} else {
		$s= mysql_fetch_assoc($result);
		return $s['LId'];
	}
	mysql_close($con);
}

function findPrWithAEM($aem) {   	
	$con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	mysql_select_db(DB_DATABASE,$con) or die(mysql_error());
	$sql="SELECT lab.DayLab, lab.TimeLab, lab.TBarcode, lesson.LName, presence.PresenseDate FROM presence INNER JOIN lab ON presence.LId = lab.LId INNER JOIN lesson ON lesson.LsId = lab.LsId WHERE SBarcode=(SELECT SBarcode FROM student where AEM='$aem')"; 
	$result = mysql_query($sql);
	if (mysql_num_rows($result) == 0) { 
		return $result;           
	} else {
		return $result;	    	
	}     		
	mysql_close($con);
}     

function findPrWithBarcode($SBarcode) {   	
	$con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	mysql_select_db(DB_DATABASE,$con) or die(mysql_error());
	$sql="SELECT lab.DayLab, lab.TimeLab, lab.TBarcode, lesson.LName, presence.PresenseDate FROM presence INNER JOIN lab ON presence.LId = lab.LId INNER JOIN lesson ON lesson.LsId = lab.LsId WHERE SBarcode='$SBarcode'"; 
	$result = mysql_query($sql);
	if (mysql_num_rows($result) == 0) { 
		return $result;           
	} else {
		return $result;	    	
	}     		
	mysql_close($con);
}     

?>