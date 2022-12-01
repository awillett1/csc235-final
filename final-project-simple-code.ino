// Amelie Willett
// 11/10/2022
// Final Project: Simple Code
// -----------------------------------------------------------------

// NOTES FOR MYSELF: -----------------------------------------------
// https://robojax.com/learn/arduino/?vid=robojax_touch_counter_V3_TM1637
// https://www.electricalelibrary.com/en/2022/06/16/4-digits-display-tm1637-with-arduino/
// https://lastminuteengineers.com/tm1637-arduino-tutorial/#:~:text=Hooking%20up%20the%20TM1637%20to,pins%202%20and%203%20resp.
// https://forum.arduino.cc/t/rtc-solved-how-to-add-the-leading-0-zero-to-the-rtc-datas/183159/6
// https://forum.arduino.cc/t/if-time-midnight-do/1004927

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
# define CLK 10 // clock pin
# define DIO 11 // data-in-out pin

TM1637Display display(CLK, DIO);
uint8_t blank[] = {(0x0, 0x0, 0x0, 0x0)}; //clear the screen

// ----------------------------------------------------------------

// RTC

// uRTCLib rtc(0x68);
// RTC_DS3231 rtc;
RTC_Millis RTC;

// VARIABLES ------------------------------------------------------
int buttonPinInc = 3;
int buttonPinRes = 4;

// more button pins...

boolean currentReadingInc = false;
boolean prevReadingInc = false;

boolean currentReadingRes = false;
boolean prevReadingRes = false;

// more currentReadings/prevReadings...

int count = 0;
// more count variables...


// what type???
int currentTime;
int prevTime;

// int resetTime = 59;
int resetTime = 16;
// ----------------------------------------------------------------

void setup() {
  Serial.begin(9600);

  RTC.begin(DateTime(__DATE__, __TIME__));

  pinMode(buttonPinInc, INPUT);
  pinMode(buttonPinRes, INPUT);

  display.setBrightness(0x0f); // set brightness
  test();


} // SETUP ---------------------------------------------------------

void loop() {

  DateTime now = RTC.now();
  prevTime = currentTime;
  // currentTime = now.day();
  // currentTime = now.hour();
  currentTime = now.minute();

  String currentStr = "current: " + String(currentTime);
  String prevStr = "prev: " + String(prevTime);

  Serial.println(currentStr);
  Serial.println(prevStr);
  //  Serial.println(currentTime);

  if (currentTime == resetTime) {
    if (currentTime != prevTime) {
      count = 0;
      display.showNumberDec(count); // display count
    }
  }



  // if currentTime (rtc.now()) != prevTime {
  //        count = 0;
  //        reset all counters...
  //      }

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
} // LOOP ----------------------------------------------------------

boolean debounce(int aPin, boolean aPrevState) {
  boolean aButtonReading = digitalRead(aPin);

  if (aButtonReading == HIGH && aPrevState == LOW) {
    delay(15);
  }
  return aButtonReading;
} // DEBOUNCE ------------------------------------------------------

void test() {
  uint8_t data8888[] = { 0xff, 0xff, 0xff, 0xff };  // all segments show
  display.setSegments(data8888); // display 8888 on display for test
  delay(3000);// give time to user to read the display at the beginning
  display.setSegments(blank); // clear the screen from previous values
  display.showNumberDec(0);// display zero
}
