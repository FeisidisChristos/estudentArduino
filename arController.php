<?php

require_once 'barcode_config.inc';

include_once 'insert_Values.php';
include_once 'find_Values.php';

$barcode = $_GET["barcode"];
$isTeacher = $_GET["isTeacher"];
$infoLab = $_GET["infoLab"];

if($isTeacher==1) {												//exist prof
	if(findTBarcode($barcode)!='+') {                            
		$list=findTBarcode($barcode);
		$stringCreator="";                                                  
		foreach ($list as $LessonDayLab) {
			$stringCreator=$stringCreator."!".$LessonDayLab.">";
		}
		echo $stringCreator;												//return lesson
	} else {
		echo '+';                                               //non-exist prof
	}
} else {														//exist student
	if(findSBarcode($barcode)!='%') {
		$info=explode("_",$infoLab );              
	    $lid=findLId($info[1],$info[2],$info[0]);                    
	    $theDate = date("Y/m/d");                             
		if(insertPresence($barcode,$lid,$theDate)!='#') {          
			echo '(';                                            //inserted student
		} else {
			echo '#';                                            //non-inserted student
		}
	} else {
		echo '%';                                                //non-exist student
	}
}

?>
