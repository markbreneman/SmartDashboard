#include <Bridge.h>
#include <HttpClient.h>

//RGB LED Pins
int redPin = 7;
int greenPin = 6;
int bluePin = 5;

//User Statuses 
//From Server
int busy; //Heads Down
int avail; //Free to Jam
int needsABreak; //Need Break
int takeALook; //Take A Look

//From Sensor
int busyState = 0;
int availState = 0;
int needsABreakState = 0;
int takeALookState = 0;

int hallEffectPin1 =A0;
int hallEffectPin2 =A1;
int hallEffectPin3 =A2;
int hallEffectPin4 =A3;

////////////////////////////////////////////////////////////////////////
//CONFIGURE SERVER ENDPOINTS
////////////////////////////////////////////////////////////////////////

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is
String userID="id=3";//JUST CHANGE NUMBER PER USER
String serverRoot = "209.68.4.163/~arthurn/yolo";
String setStatusRoute= "/setstatus.php?";
String getStatusRoute= "/getstatus.php?";
String sms="/sms.php";
String docType=" HTML/1.0";
////////////////////////////////////////////////////////////////////////

char inString[32]; // string for incoming Serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?
HttpClient client;

void setup() {
  //Blink LED on YUN during Startup
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);
  
  //SET LED PIN MODE
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  //SET HALL EFFECT PIN MODE
  pinMode(hallEffectPin1, INPUT); // Busy - Heads Down
  pinMode(hallEffectPin2, INPUT); // Available - Free To Jam
  pinMode(hallEffectPin3, INPUT); // Need A Break
  pinMode(hallEffectPin4, INPUT); // Take A Look 
//  while (!Serial);
  
}

void loop() {  
  //SENSOR READINGS
  Serial.println("Sensor 1");
  Serial.println(analogRead(hallEffectPin1));
  busyState=analogRead(hallEffectPin1);
  Serial.println("Sensor 2");
  Serial.println(analogRead(hallEffectPin2));
  availState=analogRead(hallEffectPin2);
  Serial.println("Sensor 3");
  Serial.println(analogRead(hallEffectPin3));
  needsABreakState=analogRead(hallEffectPin3);

  Serial.println("Sensor 4");
  Serial.println(analogRead(hallEffectPin4));
  takeALookState=analogRead(hallEffectPin4);
  
  String pageValue = connectAndRead(); //Connect to the server and read the output

  delay(500); //wait 5 seconds before connecting again
//  Serial.println("I'm finished reading");

  //Based off the Server Set the LED Color  
  
//        Serial.println(busy);//Busy
//        Serial.println(avail);//Available 
//        Serial.println(needsABreak);//Needs A Break
//        Serial.println(takeALook);//Take A Look
        
  if (busy == 49){
    setColor(255,0,0);
//    Serial.println("Red"); 
  }

  else if (avail == 49){
    setColor(0,255,0);
//    Serial.println("Green");
  }

  else if (needsABreak == 49){
    setColor(138,43,226);
//    Serial.println("purple");
  }
 
  else if (takeALook == 49){
    setColor(29,136,180);
//    Serial.println("Purple");
  }

  else {
    setColor(238,240,73);
//    Serial.println("Yellow");// More than one set High or all low - Trouble...
  }

//SET THE USER TO AVAILABLE
  //Is the busy not set to true in the database and the the cube on pin 1;
  //then set busy to true and everything else to false;
  Serial.println("Starting");
  if (busy!=49 && busyState<170) {   
    String busySet="&busy=1&available=0&needsabreak=0&takealook=0";
    String serverTempAddress = serverRoot+setStatusRoute+userID+busySet;
//    Serial.println(serverTempAddress);
    client.get(serverTempAddress);
    client.read();
    Serial.println("Busy Set to True");
    client.flush();
  }

 if (avail!=49 && availState<170) {   
    String availSet="&busy=0&available=1&needsabreak=0&takealook=0";
    String serverTempAddress = serverRoot+setStatusRoute+userID+availSet;
//    Serial.println(serverTempAddress);
    client.get(serverTempAddress);
    client.read();
    Serial.println("Available Set");
    client.flush();
  }

  if (needsABreak!=49 && needsABreakState<170) {   
    String needsABreakSet="&busy=0&available=0&needsabreak=1&takealook=0";
    String serverTempAddress = serverRoot+setStatusRoute+userID+needsABreakSet;
//    Serial.println(serverTempAddress);
    client.get(serverTempAddress);
    client.read();
    Serial.println("Needs A Break Set");
    client.flush();
  } 

  if (takeALook!=49 && takeALookState<170) {   
    String takeALookSet="&busy=0&available=0&needsabreak=0&takealook=1";
    String serverTempAddress = serverRoot+setStatusRoute+userID+takeALookSet;
//    Serial.println(serverTempAddress);
    client.get(serverTempAddress);
    client.read();
    Serial.println("Take A Look Set");
    client.flush();
  }   
}

String connectAndRead(){
//  Connect to Server and Read Status
  Serial.println("Connecting...");
  String serverTempAddress = serverRoot+getStatusRoute+userID;
//  Serial.println(serverTempAddress);
  client.get(serverTempAddress);
  if(client.available()){
    return readPage();
  }
  else{
    return "Connection Failed";
  }
}

String readPage(){
  //read the page, and capture & return everything between '<' and '>'
  while(true){
    if (client.available()) {
      char c = client.read();
      if (c == '<' ) { //'<' is our begining character
        startRead = true; //Ready to start reading the part 
      }
      else if(startRead){
        busy = c;
        client.read(); //this is the comma that we don't care about
        avail = client.read();
        client.read();
        needsABreak = client.read();
        client.read();
        takeALook = client.read();
        //got what we need here! We can disconnect now
        startRead = false;
        Serial.println("Disconnecting.");
        
/////////// SERVER VALUES ////////////////
        Serial.println(busy);//Busy
        Serial.println(avail);//Available 
        Serial.println(needsABreak);//Needs A Break
        Serial.println(takeALook);//Take A Look
        return inString;
//          }
      }
    }
  }
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);  
}

