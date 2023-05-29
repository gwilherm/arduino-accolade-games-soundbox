#include "notes.h"

// HW
int KNOB_PIN   = A0;    // select the input pin for the potentiometer
int BUZZ_PIN   = 13;    // select the pin for the LED
int BUTTON_PIN = 5;
int DATA_PIN   = 6;     // Data pin (SER) of 74HC595 is connected to Digital pin 6
int LATCH_PIN  = 7;     // Latch pin (RCLK) of 74HC595 is connected to Digital pin 7
int CLOCK_PIN  = 8;     // Clock pin (SRCLK) of 74HC595 is connected to Digital pin 8

// SW
#define REST_NOTE 0

#define SEMIBREVE      240000
#define MINIM          SEMIBREVE / 2
#define CROTCHET       MINIM / 2
#define QUAVER         CROTCHET / 2
#define SEMIQUAVER     QUAVER / 2

// Tempo of the theme
byte tempo = 160;

byte leds = 0;         // Variable to hold the pattern of which LEDs are currently turned on or off
byte buttonValue = 0;
int  knobValue   = 0;  // variable to store the value coming from the sensor
int  gearcpt     = 0;

void buzz(int buzzer_pin, long freq, long length) {
  long delay_us = 1000000 / freq / 2;
  long nbCycles = freq * length / 1000;

  for (long i = 0; i < nbCycles; i++)
  {
    digitalWrite(buzzer_pin, HIGH);
    delayMicroseconds(delay_us);
    digitalWrite(buzzer_pin, LOW);
    delayMicroseconds(delay_us);
  }
}

void play_note(float note, float length){
  if (tempo) length = length / tempo;

  if (note != REST_NOTE)
  {
    buzz(BUZZ_PIN, note, length);
  }
  else
  {
    delay(length);
  }
}

void theme_pattern(int times, int pitch)
{
  for (int i = 0; i < times; i++)
  {
    play_note(notes[NOTE_FS2 + pitch], QUAVER);
    play_note(notes[NOTE_CS3 + pitch], QUAVER);
    play_note(notes[NOTE_FS3 + pitch], QUAVER);
    play_note(notes[NOTE_FS2 + pitch], QUAVER);
    play_note(notes[NOTE_E3  + pitch], QUAVER);
    play_note(notes[NOTE_FS2 + pitch], SEMIQUAVER);
    play_note(notes[NOTE_DS3 + pitch], QUAVER);
    play_note(notes[NOTE_FS2 + pitch], SEMIQUAVER);
    play_note(notes[NOTE_CS3 + pitch], QUAVER);
  }
}

void theme()
{
  theme_pattern(4, 0);
  theme_pattern(4, 12);
  theme_pattern(2, 12 + 5);
  theme_pattern(2, 12);
  theme_pattern(1, 7);
  theme_pattern(1, 12 + 5);
  theme_pattern(2, 12);
}

void boitier()
{
  int newVal = digitalRead(BUTTON_PIN);
  if (newVal != buttonValue)
  {
    if (newVal == 1)  gearcpt++;
    if (gearcpt == 6) gearcpt = 0;

    buttonValue = newVal;
  }
}

void vroum()
{
  int len = 50;
  // read the value from the sensor:
  knobValue = analogRead(KNOB_PIN);
  boitier();
  int buzz_freq = (knobValue * 1) - (gearcpt * 100);
  if (buzz_freq < 0) buzz_freq = 0;
  Serial.println(buzz_freq);
  // turn the BUZZ_PIN on
  buzz(BUZZ_PIN, buzz_freq, len);
  delay(len);
}

void updateShiftRegister()
{
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, leds);
  digitalWrite(LATCH_PIN, HIGH);
}

void top_depart()
{
  int len = 500;

  leds = 0;
  updateShiftRegister();
  delay(len);

  leds = 0b001;
  updateShiftRegister();
  buzz(BUZZ_PIN, notes[NOTE_C4], len);
  delay(len);

  leds = 0b011;
  updateShiftRegister();
  buzz(BUZZ_PIN, notes[NOTE_C4], len);
  delay(len);

  leds = 0b111;
  updateShiftRegister();
  buzz(BUZZ_PIN, notes[NOTE_C5], len);
  delay(len);

  leds = 0;
  updateShiftRegister();
}

void setup() {
  Serial.begin(115200);

  // declare the BUZZ_PIN as an OUTPUT:
  pinMode(BUZZ_PIN, OUTPUT);
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN,  OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  pinMode(BUTTON_PIN,  INPUT);

  updateShiftRegister();
  
  theme();
  top_depart();
}

void loop() {
  vroum();
}
