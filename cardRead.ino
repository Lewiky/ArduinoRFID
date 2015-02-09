/**
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
* Script is based on the script of Miguel Balboa.
* The card number is read and printed to the serial port, as well as the verification status
* of the card. But only if the pressure sensor is engaged.
*
* @version 0.3
* @author Lewis Bell
* @based on software by Henri de Jong
* @since 10-11-14
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

// Setup variables:
	int serNum0;
	int serNum1;
	int serNum2;
	int serNum3;
	int serNum4;
	int redPin = 3;
	int greenPin = 6;
	int sensorPin =2;
	int sensorState = 0;
	int buzzerPin = 4;
	int i;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  rfid.antennaOn();
  pinMode(sensorPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);  	//setup pins as inputs or outputs, start the antenna and start serial processes.
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  i = 0;

 
}

void loop()
{
   if(digitalRead(sensorPin) == LOW){
 	for(i; i < 1; i++){
  	if (rfid.isCard()) {
    	if (rfid.readCardSerial()) {
        	if (rfid.serNum[0] != serNum0
            	&& rfid.serNum[1] != serNum1
            	&& rfid.serNum[2] != serNum2   //detect if the currently stored number is the same as the newly detected one
            	&& rfid.serNum[3] != serNum3
            	&& rfid.serNum[4] != serNum4
        	) {

            	//Serial.println(" ");
            	Serial.println("Cardnumber:");
            	Serial.print("Dec: ");
   	 Serial.print(rfid.serNum[0],DEC);
            	Serial.print(", ");
   	 Serial.print(rfid.serNum[1],DEC);
            	Serial.print(", ");
   	 Serial.print(rfid.serNum[2],DEC);
            	Serial.print(", ");
   	 Serial.print(rfid.serNum[3],DEC);
            	Serial.print(", ");
   	 Serial.print(rfid.serNum[4],DEC);
            	Serial.println(" ");
           	 
           	//Equate the intergers and array members.
           	// serNum0 = rfid.serNum[0];
            	//serNum1 = rfid.serNum[1];
            	//serNum2 = rfid.serNum[2];   
            	//serNum3 = rfid.serNum[3];
            	//serNum4 = rfid.serNum[4];        	 
         	} else {
           	/* If we have the same ID, just write a dot. */
           	Serial.print(".");
         	}
           	 
         	// Serial.println("The first part is: " + rfid.serNum[0]);

     	 
          	//autherisation logic
          	if(rfid.serNum[0] == 181){
            	Serial.println("Authorisation complete");
            	digitalWrite(greenPin, HIGH);
            	delay(2000);
          	}
          	else{
            	digitalWrite(redPin, HIGH);
           	// digitalWrite(buzzerPin, HIGH);
            	delay(2000);
            	Serial.println("Authorisation Failed");
      	 
                              	 
          	digitalWrite(greenPin, LOW);
          	digitalWrite(redPin, LOW);
          	//digitalWrite(buzzerPin, LOW);
        	}
	 
    	}
    
  	rfid.halt();
  	}
 	}
   }
}


