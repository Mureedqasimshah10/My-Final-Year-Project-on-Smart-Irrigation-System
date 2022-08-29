
// SMARTKEMBO DISCOVERY SCIENCE //
#include <LiquidCrystal.h> //LCD Library
#include <DHT.h>
#include <DHT_U.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
StaticJsonDocument<200> arduino_packet;
//SoftwareSerial sim800l(A1, 8); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523
#define DHTPIN A3
//#define button1 A3   //GSM
#define motor_pin 8     //motor
#define DHTTYPE    DHT11     // DHT 11
//Initialize sensor's object
DHT_Unified dht(DHTPIN, DHTTYPE);
bool button_State;//GSM


int M_Sensor = A0;
int Q_Sensor = A5;
int S_Sensor = A2;
int T_Sensor = A4;
int W_led = 7;
int P_led = 13;
int Speaker = 9;
int val;
int ldr_value;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{

  dht.begin();  //Initialize DHT11 sensor
  lcd.begin(20, 4);
  lcd.clear();
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
 pinMode(motor_pin, OUTPUT);//motor
 
  //pinMode(8, OUTPUT);//motor
  pinMode(9, OUTPUT);

  //GSM
//  pinMode(button1, INPUT_PULLUP); //The button is always on HIGH level, when pressed it goes LOW
//  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
 //GSM
  Serial.begin(9600);
  Serial.println(F("******************************************************************************"));
  Serial.println("\n");
  Serial.println("***********             WelCome To The Project                   ***********\n");
  Serial.println("\n");
  Serial.println(F("*** IoT Based Smart Irrigation System By EE Students of Namal University ***\n"));
  Serial.println("\n");
  Serial.println(F("***--------------------------------------------------------------------***\n"));
  Serial.println(F("**************************************************************************\n"));
  Serial.println("\n");
  lcd.setCursor(0, 0);
  lcd.print("IoT Based Snart ");
  lcd.setCursor(0, 1);
  lcd.print("Irrigation System By");
  lcd.setCursor(0, 2);
  lcd.print("EE Students of ");
  lcd.setCursor(0, 3);
  lcd.print("Namal University ");
  delay(1000);


  pinMode(6, INPUT);
}

void loop()
{
  lcd.clear();
  //Gsm
//    button_State = digitalRead(button1);//Gsm   //We are constantly reading the button State

  Serial.println("--------------------------------------------------------------------------");
  Serial.print(F("Cureent Value of Tempp,Humidity and Moisture Sensor are Given Below:"));
  Serial.println();
  Serial.println("--------------------------------------------------------------------------");

    //Water Dranige
     if (digitalRead(W_led)==1)
     {
      digitalWrite(motor_pin,HIGH);
      Serial.println();
      Serial.println(F("Button Pressed."));
      Serial.println(F("Motor Pump is ON"));
     }
     

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.println("\n");
    Serial.print(F("Temperature : "));
    Serial.print(event.temperature);
    Serial.println(F(" °C"));
  }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity : "));
    Serial.print(event.relative_humidity);
    Serial.println(F(" %"));
  }

  // Get Moisture event and print its value.
  int rain_sensor = digitalRead(6); // Read the Pin 6
  int Mois = analogRead(M_Sensor);
  int Moist = analogRead(Q_Sensor);// 
  int Moistu = analogRead(S_Sensor);//
  int Moisture = analogRead(T_Sensor);
lcd.setCursor(0, 0);
lcd.print("T:");
lcd.print(event.temperature);
lcd.print("C");
lcd.setCursor(9, 0);
lcd.print(" M1:");
lcd.print(Mois);
lcd.setCursor(0, 1);
lcd.print("H:");
lcd.print(event.relative_humidity);
lcd.print("%");
lcd.setCursor(9, 1);
lcd.print(" M2:");
lcd.print(Moisture);
lcd.setCursor(0, 2);
lcd.print("M3:");
lcd.print(Moist);
lcd.setCursor(8, 2);
lcd.print("M4:");
lcd.print(Moistu);
  //Read Moisture Sensor Value
  Serial.print("M_Moisture Value : ");
  Serial.print(Mois);
  Serial.println("\n");
  Serial.print("Q_Moisture Value : ");
  Serial.print(Moist);
  Serial.println("\n");  
  Serial.print("S_Moisture Value : ");
  Serial.print(Moistu);
  Serial.println("\n"); 
  Serial.print("T_Moisture Value : ");
  Serial.print(Moisture);
  Serial.println("\n"); 
  if (rain_sensor == 1)
  {
    lcd.setCursor(0, 3);
    lcd.print(F("Raining"));
    Serial.print("\n");
    Serial.println(F("Rain Status: Its Raining In Your Area "));
    Serial.print("\n");
    delay(500);
  }
  if (rain_sensor == 0)
  {
    lcd.setCursor(0, 3);
    lcd.print(F("No Raining"));
    Serial.print("\n");
    Serial.println(F("Rain Status: No Raining In Your Area "));
    Serial.print("\n");
    delay(500);
  }



  //Soil Moisture Value to Control Motor Pump

 if (Mois>700 && rain_sensor==0)   // for dry soil
  { 
    if (Moist>700 && Moistu>700)
    {
      if(Moisture>700)
      {
       if (digitalRead(W_led)==1) //test the availability of water in storage
       {
         digitalWrite(13, HIGH);
        lcd.setCursor(15, 2);
        lcd.print("MOTOR");
        lcd.setCursor(15, 3);
        lcd.print("ON");
        Serial.print("\n");
        Serial.println(F("As All the 4 Moisture Limit is >700 which means Complete Soil is DRY & There is no Raining"));
        Serial.print("\n");
        Serial.print("\n");
        Serial.println(F("So Motor Pump will ON & Irrigation will Start."));
        Serial.println();
        Serial.println("---------------------------------------------------------------------------");
        Serial.println();
       }
       else
       {
         digitalWrite(13, LOW);
         lcd.setCursor(0,1);
         lcd.print("PUMP:OFF");
           
           tone(Speaker, NOTE_C4, 500); 
           delay(500); 
           tone(Speaker, NOTE_D4, 500);
           delay(500); 
           tone(Speaker, NOTE_E4, 500); 
           delay(500); 
           tone(Speaker, NOTE_F4, 500); 
           delay(500); 
           tone(Speaker, NOTE_G4, 500); 
           delay(500);
       }
      }
    }
    }
   
    else if (Moisture> 700 && rain_sensor==1)   // for dry soil
  { 
      if (Moist>700 && Moistu>700)
    {
      if(Moisture>700)
      {
 //GSM
  if (button_State == LOW) {            //And if it's pressed
    Serial.println("Button pressed");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    
//    SendSMS();                          //And this function is called

 }
 
//  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
//    Serial.write(sim800l.read()); 
//  }
  //GSM
       if (digitalRead(W_led)==1) //test the availability of water in storage
       {
         digitalWrite(13, LOW);
        lcd.setCursor(15, 2);
        lcd.print("MOTOR");
        lcd.setCursor(15, 3);
        lcd.print("OFF");
        Serial.print("\n");
        Serial.println(F("As Moisture Limit is >700 which means Soil is DRY but Rain has Started"));
        Serial.print("\n");
        Serial.print("\n");
        Serial.println(F("So Motor Pump Will remain OFF & Irrigation will Stop."));
        Serial.println();
        Serial.println("---------------------------------------------------------------------------");
        Serial.println();
       }
       else
       {
         digitalWrite(13, LOW);
         lcd.setCursor(0,1);
         lcd.print("PUMP:OFF");
           
           tone(Speaker, NOTE_C4, 500); 
           delay(500); 
           tone(Speaker, NOTE_D4, 500);
           delay(500); 
           tone(Speaker, NOTE_E4, 500); 
           delay(500); 
           tone(Speaker, NOTE_F4, 500); 
           delay(500); 
           tone(Speaker, NOTE_G4, 500); 
           delay(500);
       }
    }
    }
  }





  if (Moisture >= 300 && Moisture <= 700) //for Moist Soil
  {
    if(Mois >= 300 && Mois <=700)
    {
      if (Moist >= 300 && Moist <=700)
      {
       if (Moistu >= 300 && Moistu <=700)
       { 
        if(rain_sensor == 0)
        {
      digitalWrite(13, HIGH);
      lcd.setCursor(15, 2);
      lcd.print("MOTOR");
      lcd.setCursor(15, 3);
      lcd.print("ON");
    
    Serial.println(F("As Moisture Limit is between 300 & 700 So Its mean MOIST SOIL"));
    Serial.print("\n");
    Serial.print("\n");
    Serial.println(F("There is a  need for Irrigation so Motor Pump will ON and Irrigation will Start.”"));
    Serial.print("\n");
    Serial.println();
    Serial.println("--------------------------------------------------------------------");
    Serial.println();
  }
      }
    }
  }
  }

   if (Moisture >= 300 && Moisture <= 700) //for Moist Soil
  {
    if(Mois >= 300 && Mois <=700)
    {
      if (Moist >= 300 && Moist <=700)
      {
       if (Moistu >= 300 && Moistu <=700)
       { 
        if(rain_sensor == 1)
        {
             //GSM
  if (button_State == LOW) {            //And if it's pressed
    Serial.println("Button pressed");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    
//    SendSMS();                          //And this function is called

 }
 
//  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
//    Serial.write(sim800l.read()); 
//  }
  //GSM
      digitalWrite(13, LOW);
      lcd.setCursor(15, 2);
      lcd.print("MOTOR");
      lcd.setCursor(15, 3);
      lcd.print("OFF");
    
    Serial.println(F("As Moisture Limit is between 300 & 700 So Its mean MOIST SOIL"));
    Serial.print("\n");
    Serial.print("\n");
    Serial.println(F("There is need of Irrigation But Rain Has Started So Motor Pump will OFF and Irrigation will Start."));
    Serial.print("\n");
    Serial.println();
    Serial.println("--------------------------------------------------------------------");
    Serial.println();
  }
      }
    }
  }
  }

  if (Moisture < 300)  // For wet soil
  {
    if (Mois<300)
    {
      if (Moist<300)
      {
       if (Moistu<300)
       {
      digitalWrite(13, LOW);
      lcd.setCursor(15, 2);
      lcd.print("MOTOR");
      lcd.setCursor(15, 3);
      lcd.print("OFF");
    

    Serial.print(F("As Moisture is < 300 So Its mean Wet Soil"));
    Serial.println();
    Serial.println(F("There is no need of Irrigation so Motor Pump will remain OFF."));
    Serial.println();
    Serial.println("--------------------------------------------------------------------");
    Serial.println();
  }
  delay(1000);
      }
    }
  }

// Worst Cases 1 for Our Project
  if (rain_sensor==0 && (Moisture>700) || (Mois>700) ||( Moist>700) || (Moistu>700))  
  {     if (rain_sensor == 0) 
  {                  
      digitalWrite(13, HIGH);
      lcd.setCursor(15, 2);
      lcd.print("MOTOR");
      lcd.setCursor(15, 3);
      lcd.print("ON");
    

    Serial.print(F("One Part of the Soil is Completely Dry"));
    Serial.println();
    Serial.println(F("So Motor Pump will ON & Irrigation will Start."));
    Serial.println();
    Serial.println("--------------------------------------------------------------------");
    Serial.println();
  }
  delay(1000);
  }
 // Worst case 2 for our project

   if ((Moisture>700) || (Mois>700) ||( Moist>700) || (Moistu>700))  
  {  
    if (rain_sensor == 1)
    {                    
       //GSM
  if (button_State == LOW) {            //And if it's pressed
    Serial.println("Button pressed");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    
//    SendSMS();                          //And this function is called

 }
 
//  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
//    Serial.write(sim800l.read()); 
//  }
  //GSM
      digitalWrite(13, LOW);
      lcd.setCursor(15, 2);
      lcd.print("MOTOR");
      lcd.setCursor(15, 3);
      lcd.print("OFF");
    

    Serial.print(F("One Part of the Soil is Completely Dry But Rain has Started"));
    Serial.println();
    Serial.println(F("So Motor Pump will Remain OFF & Irrigation will Stop."));
    Serial.println();
    Serial.println("--------------------------------------------------------------------");
    Serial.println();
  }
  delay(1000);
      }
      delay(10000);
}
 

void SendSMS()
{
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+923037526845\"\r");  //Your phone number 
  delay(500);
  sim800l.print("Hi Sir! Rain Started but You don't need to worry about your field as Motor Pump Turned OFF because of Rain. When you got free please have a visit of Your Field.");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}
