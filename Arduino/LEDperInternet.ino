/*
  Twitter Client with Strings
 
 This sketch connects to Twitter using an Ethernet shield. It parses the XML
 returned, and looks for <text>this is a tweet</text>
 
 You can use the Arduino Ethernet shield, or the Adafruit Ethernet shield, 
 either one will work, as long as it's got a Wiznet Ethernet module on board.
 
 This example uses the DHCP routines in the Ethernet library which is part of the 
 Arduino core from version 1.0 beta 1
 
 This example uses the String library, which is part of the Arduino core from
 version 0019.  
 
 Circuit:
  * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 21 May 2011
 by Tom Igoe
 
 This code is in the public domain.
 
 */
#include <SPI.h>
#include <Ethernet.h>


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip(192,168,178,48); //<<< ENTER YOUR IP ADDRESS HERE!!!

// initialize the library instance:
EthernetClient client;

const int requestInterval = 60000;  // delay between requests

char serverName[] = "spda.vela.uberspace.de";  // twitter URL

boolean requested;                   // whether you've made a request since connecting
long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds
char c;

String currentLine = "";            // string to hold the text from server
String tweet = "";                  // string to hold the tweet
boolean readingTweet = false;       // if you're currently reading the tweet
int red, green, blue;


void setup() {
  
  pinMode(2, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  
  // reserve space for the strings:
  currentLine.reserve(256);
  tweet.reserve(150);

// initialize serial:
  Serial.begin(9600);
  // attempt a DHCP connection:
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Ethernet.begin(mac, ip);
  }
}



void loop()
{
  connectToServer();
  if (client.connected()) {
    if (client.available()) {
      // read incoming bytes:
      while((c = client.read())!=124){
        Serial.print(c);
      }
      
      red = getint();
      green = getint();
      blue = getint();
      Serial.println();
      Serial.println("-----------------------------");
      Serial.print("red: ");
      Serial.println(red);
      Serial.print("green: ");
      Serial.println(green);
      Serial.print("blue: ");
      Serial.println(blue);
      analogWrite(6, red);
      analogWrite(5, green);
      analogWrite(3, blue);
      // close the connection to the server:
      client.stop(); 
    }
  }
  delay(10000);
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(serverName, 80)) {
    Serial.println("making HTTP request...");
  // make HTTP GET request to RGB-Server:
    client.println("GET /rgb/farbe HTTP/1.1");
    client.println("HOST: spda.vela.uberspace.de");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

int getint(){
  boolean minus = false;
  boolean stopper = true;
  int l = 1;
  int number = 0;
  int get[20];
  int i = 0;
  while(stopper){
    get[i] = client.read() - 48;
    if(get[i] < 11){
      if(get[i] == -3){
        minus = true;
      }
      else{
        if(get[i] < 10){
          i++;
        }
      }
    }
    else{
        stopper = false;
     }
      delay(30);
    }
    i--;
    if(i > 0){
      int a = i;
      while(a > 0){
        l *= 10;
        a--;
      }
    }      
    int c = 1;
    while(i>=0){
      number = number + get[i]*c;
      c *= 10;
      i--;
    }
  if(minus){
    number *= -1;
  }
  return number;
}
