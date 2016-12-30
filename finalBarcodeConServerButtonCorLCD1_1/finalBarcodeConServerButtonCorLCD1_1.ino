/*
 

 This sketch communicates with a server using
 an Arduino Wiznet Ethernet shield.It sends barcodes 
 number which are scanned with barcode reader and other data to the
 server.The server do its job.If it have a error,it will return a 
 message which print it to LCD.And if all goes well it will return 
 some data which are accessible with buttons.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 The circuit of LCD:
 * LCD Vss pin to ground
 * LCD Vdd pin to +5V
 * LCD Vo pin through 1K resistor to ground
 * LCD RS pin to digital pin 9
 * LCD Rw pin to ground
 * LCD Enable pin to digital pin 1
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 7
 * LCD D7 pin to digital pin 2
 * LCD A pin to ground
 * LCD K pin to +5V
 The circuit of Ps/2 barcode reader:
 * ps/2 pin 1 to digital pin 8
 * ps/2 pin 3 to ground
 * ps/2 pin 4 to +5Volts
 * ps/2 pin 5 to digital pin 3
 The circuit of pushbuttonover:
 *One pin of the button to +5Volts and the other
  pin through 10K resistor to ground.Before the
  resistor connect with a wire to analog pin 1.
 The circuit of pushbuttondown:
 *One pin of the button to +5Volts and the other
  pin through 10K resistor to ground.Before the
  resistor connect with a wire to analog pin 0.
  The circuit of pushbuttonselect:
 *One pin of the button to +5Volts and the other
  pin through 10K resistor to ground.Before the
  resistor connect with a wire to analog pin 2. 
 
 created  2013-2014
 by Christos I. Feizidis

 */

#include <PS2Keyboard.h>

#include <SPI.h>
#include <Ethernet.h>

#include <LiquidCrystal.h>

//barcode reader values
int DataPin = 8;
int IRQpin =  3;
// Initialize the PS2Keyboard library
PS2Keyboard barCodeScanner;
String newBarCodeNumber = "";
//ethernet values
byte mac[] = {  ###, ###, ###, ###, ###, ### };         //Put the mac adress of your ethernet shield
char serverName[] = "########";                         //Put your server name without any more details (www.****.com)
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
int isT=1;
String barcodeToSend="";
String infoLab="";
//buttons values & server's answer values
int counterOfArray=0;
String stringCreator="";
String item[]={"","","","","","","","","",""}; 
int iteratorOfCells=0;
String chosenItemOnArray="";

int endStep=0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 1, 5, 6, 7, 2);
//administrator's barcode
String admin="202721081081";                              

void setup()
{ //start barcode reader
  barCodeScanner.begin(DataPin, IRQpin);
  delay(100);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  delay(100);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0)
    {
    lcd.print("Failed DHCP");
  // no point in carrying on, so do nothing forevermore:
    while(true);
    }
  delay(100);
  //Print a message in first line
  lcd.setCursor(0, 0);
  lcd.print("Scan barcode");
}
void loop()
{ 
 /*
  In this If statement read and complete a string with barcode number.
  If this number is admin's number then open cd-rom case else print 
  it to lcd and send it to the server.The connection with the server 
  accomplish in another part of the program with a function.  
*/ 
if (barCodeScanner.available())
  {      
    char c = barCodeScanner.read();
    if (c == PS2_ENTER) 
      {
      if(newBarCodeNumber == admin)
        {
          lcd.clear();
          lcd.setCursor(0, 0);  
          lcd.print("Open the case..");
          lcd.setCursor(0, 1);
          lcd.print("Admin...");
          delay(1000);
          pinMode(A5,OUTPUT);      
          digitalWrite(A5, HIGH);
          delay(10000);
          digitalWrite(A5, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);  
          lcd.print("You can close");
          lcd.setCursor(0, 1);
          lcd.print("the case & scan");
          newBarCodeNumber = "";
        }
      else
        {  
      lcd.clear();
      lcd.setCursor(0, 0);      
      lcd.print(newBarCodeNumber);    
      barcodeToSend=newBarCodeNumber;
      newBarCodeNumber = "";
      connectionToServer(barcodeToSend,isT,infoLab);      
        }   
      } 
    else
      {
      newBarCodeNumber.concat(c);
      }
  }
/*
  In this If statement read the answer of the server and depending
  the response do some works.If it response with "!" ,it will start to 
  connect to a string every incoming character and it will stop to connect 
  when it read ">" character and put it to a array.The character "+" means
  that was an error in the the server side which is mean the barcode number
  don't match to a professor.Another errors is the character "%" which is 
  mean the barcode number don't match to a student,the character "#" which
  is mean during the procedure it can't save the presence to database.And 
  when all it goes well it products the character "(". 
*/
if (client.available())
 {
  char c = client.read();
  if(isT==1)
    { 
    if(c=='!')
      {
      stringCreator="";
      c = client.read();
      counterOfArray=counterOfArray;
      }
    else if(c=='+')
      {
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("non-exist prof..");
      lcd.setCursor(0, 1);
      lcd.print("scan...");
      stringCreator="";
      }  
    if(c=='>')
      {
      item[counterOfArray]=stringCreator;
      c = client.read();
      counterOfArray=counterOfArray+1;             
      stringCreator="";       
      c = client.read();
      }  
    }
  else
  { 
    if(c=='(')
    {
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("inserted student");
    lcd.setCursor(0, 1);
    lcd.print("scan...");
    stringCreator="";
    
    }
    else if(c=='%')
    {
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("non-exist ");
    lcd.setCursor(0, 1);
    lcd.print("student scan...");
    stringCreator="";
   
    }
    else if(c=='#')
    {
    lcd.clear();
    lcd.setCursor(0, 0);  
    lcd.print("non-inserted ");
    lcd.setCursor(0, 1);
    lcd.print("student scan...");
    stringCreator="";
    }
  }
  stringCreator.concat(c);
 }
/*
  In this part of If statement works when the client isn't 
  available.It print the first cell of the array and if one 
  of the three button pushed do something.When pushbuttonover
  pushed ,it goes to the next cell of the array and print it 
  and the opposite result has the putting of the pushbuttondown.
  The pushbuttonselect choose the string in this cell and it open 
  the next step of the program.
*/
else
 {
  if(isT==1)
    {
    delay(100);
    if(iteratorOfCells==0 && counterOfArray!=0)
      {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lesson_Day_Time");  
      lcd.setCursor(0, 1);
      lcd.print(item[0]);
      }
    if(onPushButtonDown()==1 && iteratorOfCells>0)
      {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Lesson_Day_Time");
      iteratorOfCells=iteratorOfCells-1;
      lcd.setCursor(0, 1);
      lcd.print(item[iteratorOfCells]);
      delay(100);
      }
    if(onPushButtonOver()==1 && iteratorOfCells < counterOfArray-1)
      { 
      lcd.clear();
      lcd.setCursor(0, 0);  
      lcd.print("Lesson_Day_Time");
      iteratorOfCells=iteratorOfCells+1;
      lcd.setCursor(0, 1);
      lcd.print(item[iteratorOfCells]);
      delay(100);
      }
    if(onPushButtonSelect()==1 && counterOfArray!=0)
      {  
      chosenItemOnArray=item[iteratorOfCells];
      iteratorOfCells=-1;
      endStep=1; 
      }     
    }
 }
/*
  In this If statement stop the connection to the server.
*/
if(!client.connected())
  {
  client.stop();          
  }
/*
  In this If statement create a big string with two sting the 
  the infoLab and the above choise.Also it print a
  message to lcd.
*/
if(endStep==1)
  {
  endStep=0;
  isT=0;
  infoLab="&infoLab=";
  infoLab.concat(chosenItemOnArray);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("student..");
  lcd.setCursor(0, 1);
  lcd.print("Scan next");
  }
}
/*
This function makes the connection to the server.The Definitions are
* b is the barcode number
* isT is a number 0 or 1.It is 1 if the program must take a professor
  barcode and 0 if the program must take a student barcode.
* info is the whole string which is created at the above statement.
The function don't return any value. 
  
  At the beginning if it connects to server at 80 port and then
  report it to lcd.After it create a http reqeust with full path
  of the main file at the server.If there isn't a connection to 
  server it create a message. 
*/
void connectionToServer(String b,int isT,String info)
{
  String teacherPart="&isTeacher=";
  String path="GET http://###/arController.php?barcode=";              //Put your server name with the exactly directory of your files.

  if (client.connect(serverName, 80)) 
    {
    lcd.setCursor(0, 1);  
    lcd.print("connected");
    path.concat(b);
    path.concat(teacherPart);
    path.concat(isT);
    path.concat(info);    
    client.println(path);
    client.println();
    }
  else 
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("connection fail");
    lcd.setCursor(0, 1);
    lcd.print("try scan again");
    }
}
/*
  This fuction works when pushed the pushbuttonover.There aren't 
  any definitions but it has an integer returned value.It takes 
  the value in the analog pin 1 and convert it to voltage.If the
  result is from 0.5 to 5 Volts return 1 else return 0. 
*/
int onPushButtonOver(){
  // read the input on analog pin 1:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //check the value and return 1 if it is between 0.5 and 5 Volts otherwise return 0
  if(voltage>0.5 && voltage<=5){
                              return 1;
                              }
  else{
  
      return 0;
  
      }
      
      
}
/*
  This fuction works when pushed the pushbuttondown.There aren't 
  any definitions but it has an integer returned value.It takes 
  the value in the analog pin 0 and convert it to voltage.If the
  result is from 0.5 to 5 Volts return 1 else return 0. 
*/
int onPushButtonDown(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //check the value and return 1 if it is between 0.5 and 5 Volts otherwise return 0
  if(voltage>0.5 && voltage<=5){
                              return 1;
                              }
  else{
  
      return 0;
  
      }      
}
/*
  This fuction works when pushed the pushbuttonselect.There aren't 
  any definitions but it has an integer returned value.It takes 
  the value in the analog pin 2 and convert it to voltage.If the
  result is from 0.5 to 5 Volts return 1 else return 0. 
*/
int onPushButtonSelect(){
  // read the input on analog pin 2:
  int sensorValue = analogRead(A2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //check the value and return 1 if it is between 0.5 and 5 Volts otherwise return 0
  if(voltage>0.5 && voltage<=5){
                              return 1;
                              }
  else{
  
      return 0;
  
      }
}


