int buffer [512];  // 1k Input Buffer
int sample, lastSample;
int pot1, triggerVoltage;
int triggerTimeout = 1000; // Time until Auto-Trigger
unsigned long triggerStart;
char triggerType = '2';

void setup(){
  Serial.begin(115200);
  pinMode(13,OUTPUT);

  //set up fast sampling mode
  ADCSRA = (ADCSRA & 0xf8) | 0x04; 
}

void loop(){
  if( triggerType != '2' ){
    trigger(); // Get a trigger;
  }
  digitalWrite(13,HIGH); // Timing Marker
  for(int i=0; i<512; i++){
    buffer[i] =analogRead(0);
  }
  digitalWrite(13,LOW); // Timing Marker
  pot1 = analogRead(2); // Switch channel to cursor pot
  for(int i=0; i<512; i++){
    Serial.write(buffer[i]>>8);
    Serial.write(buffer[i] & 0xff);
  }

  //  Send back pot values for cursors
  pot1 = analogRead(2);
  analogRead(3);
  Serial.write(pot1>>8);
  Serial.write(pot1 & 0xff);
  triggerVoltage = analogRead(4);
  
  pot1 = analogRead(0); // Prepare for next sample run.
  Serial.write(triggerVoltage >> 8);
  Serial.write(triggerVoltage & 0xff);

  while(Serial.available() == 0){} // wait for next request
  triggerType = Serial.read();     // See what trigger to use
  while(Serial.available() != 0){
    Serial.read();
    // Remove any other bytes in buffer
  }
}

void trigger(){
  // Trigger at rising zero crossing
  triggerStart = millis();
  sample =analogRead(0);
  do{
    lastSample = sample;
    sample = analogRead(0);
  }
  while(!((lastSample < triggerVoltage) && (sample > triggerVoltage)) &&  (millis()- triggerStart < triggerTimeout));
  
}
