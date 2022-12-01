// Amelie Willett
// 11/17/2022
// Final Project: Complex Code
// -----------------------------------------------------------------

//    FOR RTC: --------------------------------------------------------
//      if currentTime (rtc.now()) != prevTime {
//        counter = 0;
//        reset all counters...
//      }

// ----------------------------------------------------------------

#include <Arduino.h>
#include <TM1637Display.h>
# include <RTClib.h>
// #include "uRTCLib.h"

// TM1637 ---------------------------------------------------------
// first display

# define CLK 10 // clock pin
# define DIO 11 // data-in-out pin

TM1637Display display(CLK, DIO);
uint8_t blank[] = {(0x0, 0x0, 0x0, 0x0)}; //clear the screen

// second display

# define CLK2 12 // clock pin
# define DIO2 13 // data-in-out pin

TM1637Display display2(CLK2, DIO2);

// third display

# define CLK3 A14 // clock pin
# define DIO3 A15 // data-in-out pin

TM1637Display display3(CLK3, DIO3);

// ----------------------------------------------------------------

// RTC
RTC_Millis RTC;

// VARIABLES ------------------------------------------------------

// button pins
int buttonPinInc = 7;
int buttonPinRes = 8;

int buttonPinInc2 = 5;
int buttonPinRes2 = 6;

int buttonPinInc3 = 3;
int buttonPinRes3 = 4;

// current/previous readings

boolean currentReadingInc = false;
boolean prevReadingInc = false;

boolean currentReadingRes = false;
boolean prevReadingRes = false;

// part 2
boolean currentReadingInc2 = false;
boolean prevReadingInc2 = false;

boolean currentReadingRes2 = false;
boolean prevReadingRes2 = false;

// part 3
boolean currentReadingInc3 = false;
boolean prevReadingInc3 = false;

boolean currentReadingRes3 = false;
boolean prevReadingRes3 = false;
// more currentReadings/prevReadings...

int count = 0;
int count2 = 0;
int count3 = 0;

// rtc times
int currentTime;
int prevTime;

// int resetTime = 59;
int resetTime = 18; // change based on time needed
// ----------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  RTC.begin(DateTime(__DATE__, __TIME__));

  pinMode(buttonPinInc, INPUT);
  pinMode(buttonPinRes, INPUT);

  pinMode(buttonPinInc2, INPUT);
  pinMode(buttonPinRes2, INPUT);

  pinMode(buttonPinInc3, INPUT);

  display.setBrightness(0x0f); // set brightness
  display2.setBrightness(0x0f); // set brightness
  display3.setBrightness(0x0f); // set brightness

  test(display);
  test(display2);
  test(display3);

} // SETUP ---------------------------------------------------------

void loop() {

  DateTime now = RTC.now();
  prevTime = currentTime;
  // currentTime = now.day();
  // currentTime = now.hour();
  currentTime = now.minute();

  String currentStr = "current: " + String(currentTime);
  String prevStr = "prev: " + String(prevTime);

  // if now.hour == 0 and now.minute == 0 {
  // }

  Serial.println(currentStr);
  Serial.println(prevStr);
  //  Serial.println(currentTime);

  if (currentTime == resetTime) {
    if (currentTime != prevTime) {
      count = 0;
      display.showNumberDec(count); // display count
      display2.showNumberDec(count);
      display3.showNumberDec(count);
    }
  }

  prevReadingInc = currentReadingInc;
  currentReadingInc = debounce(buttonPinInc, prevReadingInc);

  if (currentReadingInc == HIGH && prevReadingInc == LOW) {
    Serial.println("inc button");

    count++; // increment count
    display.setSegments(blank); // clear screen from prev values
    display.showNumberDec(count); // display count
    Serial.println("Current count is: ");
    Serial.println(count);
  } // INCREMENT BUTTON 1

  prevReadingRes = currentReadingRes;
  currentReadingRes = debounce(buttonPinRes, prevReadingRes);

  if (currentReadingRes == HIGH && prevReadingRes == LOW) {
    // Serial.println("res button");

    count = 0; // reset counter
    display.setSegments(blank); // clear screen from prev values
    display.showNumberDec(count); // display count
    Serial.println("Counter reset.");
  } // RESET BUTTON 1

  prevReadingInc2 = currentReadingInc2;
  currentReadingInc2 = debounce(buttonPinInc2, prevReadingInc2);

  if (currentReadingInc2 == HIGH && prevReadingInc2 == LOW) {
    Serial.println("inc2 button");

    count2++; // increment count
    display2.setSegments(blank); // clear screen from prev values
    display2.showNumberDec(count2); // display count
    Serial.println("Current count (2) is: ");
    Serial.println(count2);
  } // INCREMENT BUTTON 2

  prevReadingRes2 = currentReadingRes2;
  currentReadingRes2 = debounce(buttonPinRes2, prevReadingRes2);

  if (currentReadingRes2 == HIGH && prevReadingRes2 == LOW) {
    // Serial.println("res2 button");

    count2 = 0; // reset counter
    display2.setSegments(blank); // clear screen from prev values
    display2.showNumberDec(count2); // display count
    Serial.println("Counter (2) reset.");
  } // RESET BUTTON 2

  prevReadingInc3 = currentReadingInc3;
  currentReadingInc3 = debounce(buttonPinInc3, prevReadingInc3);

  if (currentReadingInc3 == HIGH && prevReadingInc3 == LOW) {
    Serial.println("inc3 button");

    count3++; // increment count
    display3.setSegments(blank); // clear screen from prev values
    display3.showNumberDec(count3); // display count
    Serial.println("Current count (3) is: ");
    Serial.println(count3);
  } // INCREMENT BUTTON 3

  prevReadingRes3 = currentReadingRes3;
  currentReadingRes3 = debounce(buttonPinRes3, prevReadingRes3);

  if (currentReadingRes3 == HIGH && prevReadingRes3 == LOW) {
    Serial.println("res 3 button");

    count3 = 0; // reset counter
    display3.setSegments(blank); // clear screen from prev values
    display3.showNumberDec(count3); // display count
    Serial.println("Counter (3) reset.");
  } // RESET BUTTON 3
} // LOOP ----------------------------------------------------------

boolean debounce(int aPin, boolean aPrevState) {
  boolean aButtonReading = digitalRead(aPin);

  if (aButtonReading == HIGH && aPrevState == LOW) {
    delay(15);
  }
  return aButtonReading;
} // DEBOUNCE ------------------------------------------------------

void test(TM1637Display ds) {
  uint8_t data8888[] = { 0xff, 0xff, 0xff, 0xff };  // all segments show
  ds.setSegments(data8888); // display 8888 on display for test
  delay(3000);// give time to user to read the display at the beginning
  ds.setSegments(blank); // clear the screen from previous values
  ds.showNumberDec(0);// display zero
}
