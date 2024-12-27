//Smart_led_thermometer
//Il progetto mira a creare un termometro scrivendo su uno schermo LCD temperatura e umidità rilevata da un sensore, per poi accendere il corretto led colorato in base alla temperatura.
//Autore: Tommaso Mattei
//Data di creazione: 11/12/2024
//Librerue utilizzate: DHT sensor library by Adafruit, LiquidCrystal by Arduino, Adafruit

#include "DHT.h" //inlcudiamo la libreria DHT per la rilevazione di umidità e temperatura
#include <LiquidCrystal.h> //includiamo la libreria per gestire lo schermo LCD

#define DHTPIN 9 //definiamo la pin associata per le informazioni relative al DHT

#define DHTTYPE DHT11 //definiamo la tipologia specifica di DHT

DHT dht(DHTPIN, DHTTYPE); //inizializziamo il DHT che useremo in seguito

#define LED_PINR 6 //inizializzo la pin per il led rosso
#define LED_PINY 7 //inizializzo la pin per il led giallo
#define LED_PINB 8 //inizializzo la pin per il led blu


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //variabili necessarie per lo schermo LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //inizializzo lo schermo LCD


void setup() {
  dht.begin(); // attivo il DHT

  lcd.begin(16, 2); //dò il numero di righe e colonne allo schermo LCD

  pinMode(LED_PINB, OUTPUT); //i pin definiti vengono messi come output
  pinMode(LED_PINR, OUTPUT); //i pin definiti vengono messi come output
  pinMode(LED_PINY, OUTPUT); //i pin definiti vengono messi come output

}

void loop() {

  delay(2000); //un delay per la misurazione dell'ambiente e l'aggiornamento

  float h = dht.readHumidity(); // lettura dell'umidità
 
  float t = dht.readTemperature(); //lettura della temperatura

  if (isnan(h) || isnan(t)) { //se l'umidità e la temperatura non sono numeri allora si ritorna un messaggio di errore
    Serial.println(F("La lettura del sensore DHT è fallita!"));
    return;
  }

  //i vari print delle informazioni ottenute
  lcd.print("Umidita': ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1); //ci si posiziona in basso a sinistra nello schermo LCD nella seconda riga
  lcd.print("Gradi: ");
  lcd.print(t);
  lcd.print(" C ");
  lcd.setCursor(0, 0); //si riposiziona il cursore in cima per aggiornare

  if (t <= 12.00){ //se la temperatura è sotto la soglia:
    digitalWrite(LED_PINB, HIGH); //illumina il led blu e spegni i restanti
    digitalWrite(LED_PINY, LOW);
    digitalWrite(LED_PINR, LOW);
  }
  if (t > 12.00 && t < 28.00){//se la temperatura è nell'intervallo
    digitalWrite(LED_PINY, HIGH); //illumina il led giallo e spegni i restanti
    digitalWrite(LED_PINB, LOW);
    digitalWrite(LED_PINR, LOW);
  }
  if (t > 28.00){//se la temperatura supera la soglia
    digitalWrite(LED_PINR, HIGH); //illumina il led rosso e spegni i restanti
    digitalWrite(LED_PINB, LOW);
    digitalWrite(LED_PINY, LOW);
  }


}
