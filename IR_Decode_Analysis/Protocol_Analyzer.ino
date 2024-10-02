
int maximum=500;  // you can extend the limit to around 800. But most of the remote's protocol will be covered in 500 bits.

unsigned int data[500],low[450],high[450]; 
unsigned int x = 0;
 
void setup(void)
{
  Serial.begin(115200); 
  attachInterrupt(0, Rec_Interrupt, CHANGE);
}

void loop(void)
{
  // put your main code here, to run repeatedly:

  Serial.println(F("Press the button once"));
  delay(5000);
  if (x) { //if a signal is captured
    Serial.println();
    Serial.print(F("Raw: (")); //dump raw header format - for library
    Serial.print((x - 1));
    Serial.print(F(") "));
    detachInterrupt(0);//stop interrupts & capture until finshed here
    int j=0;
    for (int i = 1; i < x; i++) 
    { 
        //now dump the times
        if(i%2==0)
        {
          low[j]=data[i] - data[i - 1];
          j++;
          Serial.print("LOW ");
          Serial.println(data[i] - data[i - 1]);
        }
        else
        {
          high[j]=(data[i] - data[i - 1]);
          j++;
          Serial.print("HIGH ");
          Serial.println(data[i] - data[i - 1]);
        }
    }
    x = 0;
    Serial.println();
    Serial.println();
    attachInterrupt(0, Rec_Interrupt, CHANGE);//re-enable ISR for receiving IR signal
  }
}

void Rec_Interrupt() {
  if (x > maximum)
    return; //ignore if exceeds maximum
  data[x++] = micros(); //record

}
  
