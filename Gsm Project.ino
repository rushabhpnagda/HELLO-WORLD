 #include<SoftwareSerial.h>
SoftwareSerial mySerial(3,2);//tx and rx
int microwave=10;
int microwave_value;
int sms_count=0;
int smoke=11;
float smoke_Value;



void setup()
{
 
  delay(30000);
pinMode(microwave,INPUT);
pinMode(smoke,INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(12,LOW);
digitalWrite(13,HIGH);

Serial.begin(9600);
mySerial.begin(9600);
delay(10000);
Serial.println("start");
}

void loop()

{
Check_Burglar();
delay(10000);
Check_Smoke();
}


void Check_Burglar()
{
microwave_value=digitalRead(microwave); // Reading sensor value from pin 7
if(microwave_value==HIGH) // Checking if PIR sensor sends a HIGH signal to Arduino 
 {
    {  
       Serial.print("microwave_DECET");
       SendCall();// Function to send AT Commands to GSM module
     
    }
 }
}

void Check_Smoke()
{
  smoke_Value = analogRead(smoke); // read analog input pin 0
  
  Serial.print("Sensor Value: ");

  Serial.print(smoke_Value);
  
  if(smoke_Value > 350)
  {
    Serial.print("smoke detect");
    SendCall();// Function to send AT Commands to GSM module
  }
  
  Serial.println("");
  delay(2000); // wait 2s for next 

}




void SendTextMessage()
{
 
   mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+918975958999\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("Gas Leaking!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
}

void SendCall()
{
   
  
  mySerial.println("ATD+ +918975958999;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
  updateSerial();
  
}




void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
