void checkEncoder() {
  encoderPinA_value = digitalRead(encoderPinA);
  if (encoderPinA_value != encoderPinA_prev) { // check if knob is rotating
    // if pin A state changed before pin B, rotation is clockwise
    if (digitalRead(encoderPinB) != encoderPinA_value) {
      count ++;
      bool_CW = true;
    } 
    else {
      // if pin B state changed before pin A, rotation is counter-clockwise
      bool_CW = false;
      count--;
      }
      if (bool_CW) {
        Serial.print("Clockwise | ");
      } else {
        Serial.print("Counter-Clockwise | ");
      }
      Serial.print(count);
      displayCount(count);
      Serial.print(" | ");
  }
  encoderPinA_prev = encoderPinA_value;
  // check if button is pressed (pin SW)
  if (digitalRead(encoderBtn) == LOW){
    btnPressed = false;
    Serial.print("BTN ON");
    running = false;
    digitalWrite(relayPin, HIGH);
    measurmentFinished = false;
  } 
  else {
    btnPressed = true;
  }
}
