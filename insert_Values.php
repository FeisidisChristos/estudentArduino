<?php

  function insertTeacher($TBarcode,$TFirstName,$TLastName,$TEmail,$TCity,$TPhone)
    {

	     $con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD);

	     if(!$con)
	      die('Could not connect:'.mysql_error());

	      mysql_select_db(DB_DATABASE,$con);

  		  $sql="INSERT INTO Teacher
  		  (TBarcode,TFirstName,TLastName,TEmail,TCity,TPhone)
           VALUES ($TBarcode,'$TFirstName','$TLastName','$TEmail','$TCity','$TPhone')";

		 if(mysql_query($sql,$con))
  		    {
   	    echo "Teacher inserted";
   	    }
		 else
		    {
	        echo "problem with Teacher create".mysql_error();
	        }

	     mysql_close($con);
    }
  function insertLab($DayLab,$TimeLab,$TBarcode,$LsId)
    {

	     $con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD);

	     if(!$con)
	      die('Could not connect:'.mysql_error());

	      mysql_select_db(DB_DATABASE,$con);

  		  $sql="INSERT INTO Lab
  		  (DayLab,TimeLab,TBarcode,LsId)
           VALUES ($DayLab,'$TimeLab',$TBarcode,$LsId)";

		 if(mysql_query($sql,$con))
  		    {
   	    echo "Lab inserted";
   	    }
		 else
		    {
	        echo "problem with Lab create".mysql_error();
	        }

	     mysql_close($con);
    }
  function insertLesson($LName,$LSemester,$LAliasName)
    {

	     $con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD);

	     if(!$con)
	      die('Could not connect:'.mysql_error());

	      mysql_select_db(DB_DATABASE,$con);

  		  $sql="INSERT INTO Lesson
  		  (LName,LSemester,LAliasName)
           VALUES ('$LName',$LSemester,'$LAliasName')";

		 if(mysql_query($sql,$con))
  		    {
   	    echo "Lesson inserted";
   	    }
		 else
		    {
	        echo "problem with Lesson create".mysql_error();
	        }

	     mysql_close($con);
    }
   function insertPresence($SBarcode,$LId,$PresenseDate)
    {
	      $con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD) or die('Could not connect:'.mysql_error());
	      mysql_select_db(DB_DATABASE,$con);
  		  $sql="INSERT INTO Presence
  		  (SBarcode,LId,PresenseDate)
           VALUES ($SBarcode,$LId,'$PresenseDate')";
		 if(mysql_query($sql,$con)){
   	         return "(";
   	        }
		 else{
	         return "#";
	        }
	     mysql_close($con);
    }
   function insertStudent($SBarcode,$FirstName,$LastName,$FatherName,$AEM,$Semester,$Email,$City,$School)
    {

	     $con = mysql_connect(DB_HOST,DB_USER,DB_PASSWORD);

	     if(!$con)
	      die('Could not connect:'.mysql_error());

	      mysql_select_db(DB_DATABASE,$con);

  		  $sql="INSERT INTO Student
  		  (SBarcode,FirstName,LastName,FatherName,AEM,Semester,Email,City,School)
           VALUES ($SBarcode,'$FirstName','$LastName','$FatherName',$AEM,$Semester,'$Email','$City','$School')";

		 if(mysql_query($sql,$con))
  		    {
   	    echo "Student inserted";
   	    }
		 else
		    {
	        echo "problem with Student create".mysql_error();
	        }

	     mysql_close($con);
    }

?>