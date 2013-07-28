/*
Florian Albrecht

based on Twitter Client by Tino Inge
 */
#include <SPI.h>
#include <Ethernet.h>

/*MAC und IP-Adresse definieren, IP-Adresse muss je
nach Netzwerk angepasst werden*/
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip(192,168,178,48);

//Ethernerlibrary initialisieren
EthernetClient client;

//Domain definieren
char serverName[] = "spda.vela.uberspace.de";

char c;
int red, green, blue;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  //Ethernetshield starten
  Ethernet.begin(mac, ip);
}

void loop()
{
  //Verbindung aufbauen
  connectToServer();
  if (client.connected()) {
    if (client.available()) {
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
      
      // Verbindung schließen
      client.stop(); 
    }
  }
  delay(5000);
}

void connectToServer() {
  Serial.println("Verbindung aufbauen.");
  if (client.connect(serverName, 80)) {
    Serial.println("Verbunden. HTTP-Anfrage starten.");
    client.println("GET /rgb/farbe HTTP/1.1");
    client.println("HOST: spda.vela.uberspace.de");
    client.println();
  }
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
