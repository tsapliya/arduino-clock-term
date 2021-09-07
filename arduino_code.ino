#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#include <LiquidCrystalRus.h>
LiquidCrystalRus lcd0(2, 3, 4, 5, 6, 7);
LiquidCrystalRus lcd1(8, 9, 10, 11, 12, 13);
float t1, t2, t1Old, t2Old;
String oldTime = "";
String newTime = "";
String row0 = "";
String row1 = "";

byte temp[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
};

void setup(void)
{
  sensors.begin();    
  Serial.begin(2000000);
  lcd1.createChar(0, temp);
  lcd1.begin(20, 2);  
   lcd0.begin(20, 2);   
 t1Old = t2Old = 0;
  

}

void loop(void)
{ 

  if (Serial.available() > 0) {
     newTime = Serial.readString();
     if (Serial.read() and oldTime != newTime){
        oldTime = newTime;
        lcd0.clear();
        for (int i = 0; i < newTime.indexOf("|"); i++){
          row0 += newTime[i];
        }
        lcd0.setCursor(0,0);
        lcd0.print(row0);
        for (int i = newTime.indexOf("|") + 2; i < newTime.length(); i++){
          row1 += newTime[i];
        }
        lcd0.setCursor(0,1);
        lcd0.print(row1);
        row1 = row0 = "";  
     }   
  }

  sensors.requestTemperatures(); 
  t1 = sensors.getTempCByIndex(0);
  t2 = sensors.getTempCByIndex(1);
  if (t1 != t1Old or t2 !=t2Old){
    t1Old = t1;
    t2Old = t2;
    lcd1.clear();
    lcd1.setCursor(0,0);
    lcd1.write("outside: ");
    lcd1.print(t1);
    lcd1.write(" ");
    lcd1.write(byte(0));
    lcd1.write("C");
    lcd1.setCursor(0,1);
    lcd1.write("inside : ");
    lcd1.print(t2);
    lcd1.write(" ");
    lcd1.write(byte(0));
    lcd1.write("C");
  }


  

  delay(100);
}
