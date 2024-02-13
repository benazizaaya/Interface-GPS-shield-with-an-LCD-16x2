
#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
 SoftwareSerial SIM900(19, 18);

// initialiser la bibliothèque LiquidCrystal avec les numéros des pin de l'Arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Création d'une instance pour l'objet TinyGPS
TinyGPS gps;
float latitude, longitude;
// This is where you declare prototypes for the functions that will be 
// using the TinyGPS library.
// Ceci est l'endroit où nous déclarons le prototypes pour la fonction 
// qui utilisera la bibliothéque TinyGPS et controlera l'affichage 
void getgps(TinyGPS &gps);
 
void setup()
{
  Serial.begin(9600);
  SIM900.begin(9600);  
 
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(2,1);//Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.(col,row)
  lcd.print("* OPEN HARDWARE *");
  lcd.setCursor(4,2);
  lcd.print("** TUNISIE **");
  delay(1000);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("En attente ...");
}
 
// La fonction get gps va obtenir et imprimer les valeurs que nous voulons
void getgps(TinyGPS &gps)
{
  // Définir les variables qui seront utilisées
  //float latitude, longitude;
  // appelle de la fonction qui récupère la latitude et la longitude
  gps.f_get_position(&latitude, &longitude);
  
  // clear LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Lat: "); 
  lcd.print(latitude,5); 
  lcd.setCursor(0,1); 
  lcd.print("Long: "); 
  lcd.print(longitude,5);
  
  // la même opération pour la date et le temps
 int annee;
  byte mois, jour, heure, minute, seconde, millieme;//A byte stores an 8-bit unsigned number, from 0 to 255
  gps.crack_datetime(&annee,&mois,&jour,&heure,&minute,&seconde,&millieme);
  
  lcd.setCursor(1,2);
  lcd.print(heure,DEC);
  lcd.print(":");
  if (minute<10)
  {
    lcd.print("0");
    lcd.print(minute, DEC);
  } 
  else if (minute>=10)
  {
    lcd.print(minute, DEC);
  }
  lcd.print(":");
  if (seconde<10)
  {
    lcd.print("0");
    lcd.print(seconde,DEC);
  } 
  else if (seconde>=10)
  {
    lcd.print(seconde,DEC);
  }
  lcd.print(" ");
  lcd.print(jour);
  lcd.print("/");
  lcd.print(mois,DEC);
  lcd.print("/");
  lcd.print(annee,DEC);
  lcd.setCursor(0,3);
  lcd.print(gps.f_altitude()); // reading and altitude display
  lcd.print("m ");             // lecture et affichage de l'altitude
  
  lcd.print(gps.f_speed_kmph()); // reading and speed display
  lcd.print("km/h");             // lecture et affichage de la vitesse */
 
}
   void SendSMS()
{ 
  
  SIM900.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  SIM900.println("AT+CMGS=\"+21621242393\"\r"); //Change to destination phone number 
  delay(1000);
  SIM900.print("https://www.google.com/maps/?q=");
  //Serial.print("Latitude :");
  SIM900.print(latitude, 6);
  //Serial.print("Longitude:");
  SIM900.print(",");
  SIM900.print(longitude, 6);
  delay(1000);
  SIM900.println((char)26); //the stopping character Ctrl+Z
  delay(1000);  
}
 
 
void loop()
{
  byte a;
  float latitude, longitude;
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c)) {
        newData = true;   
      getgps(gps); // grab the data and display it on the LCD
                   // saisir les données et les afficher sur l'écran LCD
 
  SendSMS() ; }}}}
