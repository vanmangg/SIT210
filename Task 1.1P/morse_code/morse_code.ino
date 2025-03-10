void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void short_blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void long_blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}



void loop() {
  // My name is Van therefore the morse code for that is ..._ ._ _.
  // v
  short_blink();
  short_blink();
  short_blink();
  long_blink();
  delay(500);
  // a
  short_blink();
  long_blink();
  delay(500);
  // n
  long_blink();
  short_blink();
  delay(5000); // long delay to make end of morse code easier to notice
  
}
