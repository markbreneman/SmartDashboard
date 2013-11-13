#include <Bridge.h>
#include <HttpClient.h>

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

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////

//The location to go to on the server
//make sure to keep HTTP/1.0 at the end, this is telling it what type of file it is
//String location = "/getstatus.php?id=4 HTTP/1.0";
//String locationSetFree = "/setstatus.php?id=4&busy=0 HTTP/1.0";
//String locationSetBusy = "/setstatus.php?id=4&busy=1 HTTP/1.0";
//String locationSetNoBreak = "/setstatus.php?id=4&needsbreak=0 HTTP/1.0";
//String locationSetNeedBreak = "/setstatus.php?id=4&needsbreak=1 HTTP/1.0";

// if need to change the MAC address (Very Rare)
//byte mac[] = { 
//  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
////////////////////////////////////////////////////////////////////////

//EthernetClient client;

char inString[32]; // string for incoming Serial data
int stringPos = 0; // string index counter
boolean startRead = false; // is reading?
HttpClient client;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonBusy, INPUT);
  pinMode(buttonAvail, INPUT);
  pinMode(buttonNeedBreak, INPUT);
}

void loop() {
  buttonStateBusy = digitalRead(buttonBusy);
  buttonStateAvail = digitalRead(buttonAvail);
  buttonStateNeedBreak = digitalRead(buttonNeedBreak);


  String pageValue = connectAndRead(); //connect to the server and read the output

  //  delay(500); //wait 5 seconds before connecting again
  Serial.println(needBreak);
  Serial.println("I'm finished reading");
  
  if (needBreak == 49){
    setColor(138,43,226);
//    Serial.println("purple");
  }
  else if (Avail == 48){
    setColor(0,255,0);
//    Serial.println("Green");
  }
  else if (Avail == 49){
    setColor(255,0,0);
//    Serial.println("Red"); 
  }
  else {
    setColor(255,165,0);
//    Serial.println("other");
  }

  if (buttonStateAvail == HIGH) {     
    client.get("192.168.1.94:8888/setstatus.php?id=4&busy=0");
    client.read();
    Serial.println("No Break Set");
    client.flush();
  } 
  else {
    //      Serial.println("I didn't connect, yo!");
  }


  if (buttonStateAvail == HIGH) {     
    client.get("192.168.1.94:8888/setstatus.php?id=4&needsbreak=0");
    client.read();
    Serial.println("Break Set");
    client.flush();
  } 
  else {
    //      Serial.println("I didn't connect, yo!");
  }

  if (buttonStateBusy == HIGH) {     
    client.get("192.168.1.94:8888/setstatus.php?id=4&busy=1");
    client.read();
    Serial.println("Busy Set");
    client.flush();
  } 
  else {
    //      Serial.println("I didn't connect, yo!");
  }

  if (buttonStateBusy == HIGH) {     
    client.get("192.168.1.94:8888/setstatus.php?id=4&needsbreak=0");
    client.read();
    Serial.println("Busy Set");
    client.flush();
  } 
  else {
    //      Serial.println("I didn't connect, yo!");
  }

  if (buttonStateNeedBreak == HIGH) { 
//    Serial.println("fired");   
    client.get("192.168.1.94:8888/setstatus.php?id=4&needsbreak=1");
    client.read();
    Serial.println("Need Break Set");
    client.flush();
  }  
  else {
    ////Serial.println("I didn't connect, yo!");
  }

}

String connectAndRead(){
  //connect to the server
  Serial.println("connecting...");
  //LETS NOT HARDCODE THIS LATER
  client.get("192.168.1.94:8888/getstatus.php?id=4");

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
//        Serial.println("disconnecting.");
//        Serial.println(Avail);
//        Serial.println(youHere);
//        Serial.println(needBreak);

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



