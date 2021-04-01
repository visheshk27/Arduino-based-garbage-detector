
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define TRIGGERPIN D1
#define ECHOPIN    D2
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "67307562c69f46f9bdd6ddcf1d7d8ef4";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Dialog 4G";
char pass[] = "sparkle ";

WidgetLCD lcd(V1);
WidgetLED ledgreen(V2);
WidgetLED ledred(V3);

void setup()
{
  // Debug console
  Serial.begin(9600);
pinMode(TRIGGERPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

 // lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  //Blynk.email("kavindufonseka@gmail.com","GARBAGE NOTIFICATION","Please collect your garbage bins");
  // Please use timed events when LCD printintg in void loop to avoid sending too many commands
  // It will cause a FLOOD Error, and connection will be dropped
}

void loop()
{
  //lcd.clear();
 // lcd.print(0, 0, "Distance in cm"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  long t, distance;
  digitalWrite(TRIGGERPIN, LOW);  
  delayMicroseconds(3); 
  
  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12); 
  
  digitalWrite(TRIGGERPIN, LOW);


   t=pulseIn(ECHOPIN,HIGH);
   distance= t*340/20000;
  delay(1000);
//long cm=t / 29 / 2;
 Serial.print(distance);
  Serial.println("cm");
  
  
  //lcd.print(0, 0,cm);

  if(distance<5)
  {
    Serial.print("basket is full\n");
     lcd.print(1,1,"full");
     ledred.on();
     ledgreen.off();
     Blynk.notify("you may collect your garbage bins now");
     Blynk.email("kavindufonseka@gmail.com","GARBAGE NOTIFICATION","Please collect your garbage bins");
  }else
  {
    Serial.print("basket is empty\n");
     lcd.print(1,1,"empty");
     ledgreen.on();
     ledred.off();
     
  }
  Blynk.run();

  delay(1000);

}
