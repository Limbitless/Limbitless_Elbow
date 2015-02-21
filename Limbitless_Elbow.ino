/**
 * Limbitless Solutions
 * EMG Pulse Flex Test
 * 
 * Josh Kaplan <jk@joshkaplan.org>
 * October 25, 2014
 * 
 * Takes an analog input from an EMG sensor
 * and prints out which pulse it read.
 *
 * Current code supports two types of pulses:
 *   1. Long Pulse 
 *   2. Two short Pulses
 */

#define EMG_THRESH 40       // Higher? Lower? Dependent on person?
#define SHORT_PULSE_MIN 3   // Length of time for a short pulse in terms of "threshold_count"
#define LONG_PULSE_MIN 9    // Length of time for a long pulse in terms of "threshold_count"


// vars
int emg_pin = 0;                // EMG signal pin 
int val = 0;                    // EMG value
int thresh_count = 0;           // threshold counter
int short_pulse_count = 0;      // number of short pulses detected
int short_pulse_interval = 0;   // tracks time between short pulses

void setup() 
{ 
  Serial.begin(9600);
} 

void loop() 
{ 
  // reset the counter outside the while loop
  thresh_count = 0;
 
  Serial.println("Interval");
  Serial.println(short_pulse_interval);
  delay(500);
    
  while ((val = analogRead(emg_pin)) > EMG_THRESH) 
  {
    Serial.println("Val");
    Serial.println(val);
    Serial.println("Thresh count");
    Serial.println(thresh_count);
 
    delay(800);
    
    // long pulse detection
    if(thresh_count > LONG_PULSE_MIN) 
    {
      short_pulse_count = 0;                    
      thresh_count = 0;                         
      Serial.println("Long Pulse");
      break;
    }
    thresh_count++;
    delay(10); 
  }
  
  // short pulse detections
  if(thresh_count > SHORT_PULSE_MIN) 
  {
    if(++short_pulse_count == 2)            // if two pulses are recognized
    {
      short_pulse_count = 0;                
      short_pulse_interval = 0;
      Serial.println("Short Pulse");
    }
  }

  if (short_pulse_count > 0)
    short_pulse_interval++;

  if (short_pulse_interval > SHORT_PULSE_MIN)
  {
    short_pulse_count = 0;
    short_pulse_interval = 0;
  }
}


