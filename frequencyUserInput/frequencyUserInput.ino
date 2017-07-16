// See the code in action! : https://youtu.be/_92P-MsB0yQ

#include "Waveforms.h"

int wave0 = 0;
int i = 0;
int sample;
int uSec = 50;

float baseTimeTick = 6.84;
float steps = 120;
float outputFrequency;
float outputPeriod;

String inString = "";    // string to hold input
int temp;


void setup() {
  
  analogWriteResolution(12);  // set the analog output resolution to 12 bit (4096 levels)
  analogReadResolution(12);   // set the analog input resolution to 12 bit 
  Serial.begin(9600);
  
}

void loop() {
  
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar == '\n') {
      Serial.print("Value:");
      temp = inString.toInt();
      Serial.println(temp);
      uSec = temp;
      Serial.println(uSec);
      outputPeriod = (steps*baseTimeTick + steps*((float)uSec));
      Serial.print("Output period in us is:   ");
      Serial.print(outputPeriod);
      outputFrequency = 1.0/ (outputPeriod*0.000001);
      Serial.print("      Output frequency in Hz is:   "); 
      Serial.print(outputFrequency);  
      //Serial.print("String: ");
      //Serial.println(inString);
      Serial.print("\n");
      // clear the string for new input:
      inString = "";
    }
  }


  analogWrite(DAC0, waveformsTable[wave0][i]);  // write the selected waveform on DAC0
  i++;
  
  if(i == maxSamplesNum){  // Reset the counter to repeat the wave
    i = 0;
  }
  delayMicroseconds(uSec);
}
