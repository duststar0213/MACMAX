int player1Pins = 5;
int player1Pin [] = {2, 3, 4, 5, 6};
int lastButtonStates [] = {LOW, LOW, LOW, LOW, LOW};
int player2Pins = 5;
int player2Pin [] = {7, 8, 9, 10, 11};
int buttonState1 = 0;
int buttonState2 = 0;
int lastButtonState1 = 0;
int lastButtonState2 = 0;
int buttonPushTimes = 0;
int count = 0;
int i = 0;
int j = 0;
int lastp1Score, lastp2Score;
int currentMillis = 0;
int interval = 3000;
int green = 0;
int red = 0;
int tie = 0;

boolean first = false;
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < player1Pins; i++) {
    pinMode(player1Pin[i], INPUT);
  }
  for (int i = 0; i < player2Pins; i++) {
    pinMode(player2Pin[i], INPUT);
  }
}

void loop() {
 

  //any of p1 and any of p2 is pressed => compare
  // any of p1 or any of p2 is released => reset

  int p1Score = player1ActivatePins();
  delay(1);
  int p2Score = player2ActivatePins();
  delay(3000);
  
  if (first != false) {
    if (p1Score != lastp1Score || p2Score != lastp2Score) {
      
      ///Serial.print("Green:");
      ///Serial.print(p1Score);
     // delay(5000);
      ///Serial.print("; Red:");
      ///Serial.print(p2Score);
      ///Serial.print(": ");
      //delay(5000);
      compare(p1Score, p2Score);
    }

  }
  lastp1Score = p1Score;
  lastp2Score = p2Score;

}


int player1ActivatePins() {

  /////////////////
  boolean anyPressed = false;

  for (int i = 0; i < player1Pins; i++) {

    int buttonState = digitalRead(player1Pin[i]);
    
    // if button state changes
    if (buttonState != lastButtonStates[i]) {
      first = true;
      anyPressed = true;

      // if button pressed, print out pin num and increment pushtimes
      if (buttonState == HIGH) {
        buttonPushTimes++;
        lastButtonStates[i] = HIGH;

      }

      // if the button is unpressed, decrement pushtimes
      else {
        buttonPushTimes--;
        lastButtonStates[i] = LOW;
      }

    } // end of if button state changes
   
  } // end of for i = 0


  boolean anyIsNotLow = false;
  for (int i = 0; i < 5; i++) {
    if (lastButtonStates[i] != LOW) {
      anyIsNotLow = true;
    }
  }

  // anything is pressed and any is pressed
  if (anyPressed && anyIsNotLow && buttonPushTimes != 128) {
    return buttonPushTimes;
  }

}

int player2ActivatePins() {
  boolean anyPressed = false;

  for (int i = 0; i < player2Pins; i++) {

    int buttonState = digitalRead(player2Pin[i]);

    // if button state changes
    if (buttonState != lastButtonStates[i]) {
      // first = true;
      anyPressed = true;
      
      // if button pressed, print out pin num and increment pushtimes
      if (buttonState == HIGH) {
        buttonPushTimes++;
        lastButtonStates[i] = HIGH;
      }

      // if the button is unpressed, reset pushtimes
      else {
        buttonPushTimes--;
        lastButtonStates[i] = LOW;
      }

    } // end of if button state changes

  } // end of for i = 0


  boolean anyIsNotLow = false;
  for (int i = 0; i < 5; i++) {
    if (lastButtonStates[i] != LOW) {
      anyIsNotLow = true;
    }
  }
  if (anyPressed && anyIsNotLow) {
    return buttonPushTimes;
  }
}

void compare(int x, int y) {

  if (x > y) {
    Serial.println("Green won");
    green++;
  }
  if (x == y) {
    Serial.println("Tie");
    tie++;
  }

  if (x < y) {
    Serial.println("Red won");
    red++;
  }

  Serial.println();

  // print result
  if ((green + red + tie) == 5) {

    Serial.print("Result: ");
    //delay(5000);
    Serial.print("green: ");
    Serial.print(green);
    //delay(5000);
    Serial.print("; red: ");
    //delay(5000);
    Serial.println(red);
    //delay(5000);

    if (green > red) {
      Serial.println("Green won!");
      //delay(5000);
    }
    else if (green < red) {
      Serial.println("Red won!");
      //delay(5000);
    }
    else {
      Serial.println("They tied.");
      //delay(5000);
    }
   // Serial.println("----- -----\n");

    // delay so the new game won't start right away
    //delay(2000);
    
    // reset result
    red = 0;
    green = 0;
    tie = 0;
  }
  
}
