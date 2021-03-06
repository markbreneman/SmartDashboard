int redPin = 7;
int greenPin = 6;
int bluePin = 5;
int Avail;
int needBreak;
int youHere;
int buttonAvail = 2;
int buttonBusy = 3;
int buttonNeedBreak = 4;

int buttonStateBusy = 0;
int buttonStateAvail = 0;
int buttonStateNeedBreak = 0;
int userState = 0;


//ARDUINO 1.0+ ONLY
#include <Ethernet.h>
#include <SPI.h>

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
byte server[] = {209,68,4,163};
  //  192,168,1,139 }; //ip Address of the server you will connect to

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is
String location = "/~arthurn/yolo/getstatus.php?id=4 HTTP/1.0";
String locationSetFree = "/~arthurn/yolo/setstatus.php?id=4&busy=0 HTTP/1.0";
String locationSetBusy = "/~arthurn/yolo/setstatus.php?id=4&busy=1 HTTP/1.0";
String locationSetNoBreak = "/~arthurn/yolo/setstatus.php?id=4&needsbreak=0 HTTP/1.0";
String locationSetNeedBreak = "/~arthurn/yolo/setstatus.php?id=4&needsbreak=1 HTTP/1.0";
String sendSMS = "/~arthurn/yolo/sms.php?id=4 HTTP/1.0";

// if need to change the MAC address (Very Rare)
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
////////////////////////////////////////////////////////////////////////

EthernetClient client;

char inString[32]; // string for incoming Serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?

void setup(){
  Ethernet.begin(mac);
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonBusy, INPUT);
  pinMode(buttonAvail, INPUT);
  pinMode(buttonNeedBreak, INPUT);
}

void loop(){
  buttonStateBusy = digitalRead(buttonBusy);
  buttonStateAvail = digitalRead(buttonAvail);
  buttonStateNeedBreak = digitalRead(buttonNeedBreak);

  //  Serial.println(buttonStateBusy);

  String pageValue = connectAndRead(); //connect to the server and read the output

  //  ////Serial.println(pageValue); //print out the findings.

  delay(500); //wait 5 seconds before connecting again

  ////Serial.println("I'm finished reading");

  if (needBreak == 49){
    setColor(138,43,226);
    ////Serial.println("purple");
  }
  else if (Avail == 48){
    setColor(0,255,0);
    ////Serial.println("Green");
  }
  else if (Avail == 49){
    setColor(255,0,0);
    ////Serial.println("Red");
  }
  else {
    setColor(255,165,0);
    ////Serial.println("other");
  }

  if (buttonStateAvail == HIGH) {     
    if (client.connect(server, 80)) {
      Serial.println("connected to no break");
      client.print("GET ");
      client.println(locationSetFree);
      client.println();
      client.read();
      ////Serial.println("No Break Set");
      client.stop();

      ////Serial.println(locationSetFree);
    } 
    else {
      ////Serial.println("I didn't connect, yo!");
    }
  } 

  if (buttonStateAvail == HIGH) {     
    if (client.connect(server, 80)) {
      Serial.println("connected to set break");
      client.print("GET ");
      client.println(locationSetNoBreak);
      client.println();
      client.read();
      ////Serial.println("Break Set");
      client.stop();



      ////Serial.println(locationSetNoBreak);
    } 
    else {
      ////Serial.println("I didn't connect, yo!");
    }
  } 

  if (buttonStateBusy == HIGH) {     
    if (client.connect(server, 80)) {
      Serial.println("connected to set busy");
      client.print("GET ");
      client.println(locationSetBusy);
      client.println();
      client.read();
      ////Serial.println("Busy Set");
      client.stop();

      ////Serial.println(locationSetBusy);
    } 
    else {
      Serial.println("I didn't connect, yo!");
    }
  }

  if (buttonStateBusy == HIGH) {     
    if (client.connect(server, 80)) {
      Serial.println("connected to set busy");
      client.print("GET ");
      client.println(locationSetNoBreak);
      client.println();
      client.read();
      ////Serial.println("No Break Set");
      client.stop();

      ////Serial.println(locationSetNoBreak);
    } 
    else {
      ////Serial.println("I didn't connect, yo!");
    }
  }

  if (buttonStateNeedBreak == HIGH) {     
    if (client.connect(server, 80)) {
      Serial.println("connected to set Need Break");
      client.print("GET ");
      client.println(locationSetNeedBreak);
      client.println();
      client.read();
      ////Serial.println("Need Break Set");
      client.stop();
    } 

    if (client.connect(server, 80)) {
      Serial.println("connected to set SendSMS");
      client.print("GET ");
      client.println(sendSMS);
      client.println();
      client.read();
      client.stop();
    } 

    else {
      ////Serial.println("I didn't connect, yo!");
    }
  }

}

String connectAndRead(){
  //connect to the server

  Serial.println("connecting...");

  //port 80 is typical of a www page
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET ");
    client.println(location);
    client.println();

    //Connected - Read the page
    return readPage(); //go and read the output

  }
  else{
    return "connection failed";
  }

}

String readPage(){
  //read the page, and capture & return everything between '<' and '>'
  //  stringPos = 0;
  //  memset( &inString, 0, 32 ); //clear inString memory

  while(true){
    if (client.available()) {
      char c = client.read();
     

      if (c == '<' ) { //'<' is our begining character
        startRead = true; //Ready to start reading the part 
      }
      else if(startRead){

        Avail = c;
        client.read(); //this is the comma that we don't care about
        youHere = client.read();
        client.read();
        needBreak = client.read();

        //        if(c != '>'){ //'>' is our ending character
        //          inString[stringPos] = c;
        //          stringPos ++;
        //        }else{
        //got what we need here! We can disconnect now
        startRead = false;
        client.stop();
        client.flush();

        Serial.println("disconnecting.");
        Serial.println(Avail);
        Serial.println(youHere);
        Serial.println(needBreak);

        return inString;

        //        }

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






