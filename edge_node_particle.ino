/* Samsung ARTIK 5 Returning Sensor Data from Edge Devices [P008.2] : http://rdiot.tistory.com/16 [RDIoT Demo] */

// This #include statement was automatically added by the Particle IDE.
#include "MQTT/MQTT.h"

int B = 2; // OUTPUT PIN blue
int R = 3; // OUTPUT PIN red
int G = 4; // OUTPUT PIN green

int photoresistor = A0; 
String analogvalue;
int power = A5; // This is the other end of your photoresistor. The other side is plugged into the "photoresistor" pin (above).

byte server[] = { 192,168,0,9 };
void callback(char* topic, byte* payload, unsigned int length);
MQTT client(server, 1883, callback);

void callback(char* topic, byte* payload, unsigned int length) {
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    String message(p);

    if (message.equals("RED"))    
    {
        RGB.color(255, 0, 0);
        
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH);
        
    }
    else if (message.equals("GREEN"))   
    {
        RGB.color(0, 255, 0);
         
        digitalWrite(R, HIGH);
        digitalWrite(G, LOW);
        digitalWrite(B, HIGH);
        
        delay(1000);
        
    }
    else if (message.equals("BLUE"))    
    {
        RGB.color(0, 0, 255);
        
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
        
    }
    else    
    {
        RGB.color(255, 255, 255);
        
        digitalWrite(B, HIGH);
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
 
    }
    delay(1000);
}

void setup() {
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);    
    pinMode(photoresistor,INPUT);  // Our photoresistor pin is input (reading the photoresistor)
    pinMode(power,OUTPUT); // The pin powering the photoresistor is output (sending out consistent power)
    digitalWrite(power,HIGH);

    RGB.control(true);
    client.connect(System.deviceID());
    if (client.isConnected()) {
        client.subscribe("color");
    }
}

void loop() {
    if (client.isConnected())
        client.loop();
        
    analogvalue = String(analogRead(photoresistor));
    client.publish("brightness", analogvalue );
    delay(1000);

}
