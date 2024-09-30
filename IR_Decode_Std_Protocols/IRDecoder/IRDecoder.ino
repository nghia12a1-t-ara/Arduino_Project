
#include <IRremote.h>

int IRPIN = 2;
int led = 13;

void setup()
{
  Serial.begin(9600);
  Serial.println("Enabling IRin");  
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  Serial.println("Enabled IRin");
  pinMode(led, OUTPUT);
}

void loop()
{
  int status = 0;
  if (IrReceiver.decode())
  {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
    status ^= status;
    if(status)
    {
      digitalWrite(led, HIGH);   // bật đèn led sáng
    }
    else
    {
      digitalWrite(led, LOW);
    }  
  }
  delay(500);
}
