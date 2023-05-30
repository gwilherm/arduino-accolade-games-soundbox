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

#define DOTTED  1.5

// Tempo of the theme
byte tempo = 200;

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

void theme()
{
  play_note(notes[NOTE_FS2], QUAVER);
  play_note(notes[NOTE_FS1], QUAVER);
  for (int i = 0; i < 4; i++)
  {
    play_note(notes[NOTE_A2],  QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_GS2], QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_E2],  QUAVER);
    play_note(notes[NOTE_FS2], QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
  }
  for (int i = 0; i < 4; i++)
  {
    play_note(notes[NOTE_A2],  QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
    play_note(notes[NOTE_GS2], QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
    play_note(notes[NOTE_E2],  QUAVER);
    play_note(notes[NOTE_FS2], QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
  }
  for (int i = 0; i < 2; i++)
  {
    play_note(notes[NOTE_A2],  QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_GS2], QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_E2],  QUAVER);
    play_note(notes[NOTE_FS2], QUAVER);
    play_note(notes[NOTE_FS1], QUAVER);
    play_note(notes[NOTE_CS2], QUAVER);
  }
  for (int i = 0; i < 2; i++)
  {
    play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_CS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_E4],  CROTCHET);
    play_note(notes[NOTE_B3],  CROTCHET*DOTTED);
    play_note(notes[NOTE_CS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_A3],  CROTCHET);
  }
  play_note(notes[NOTE_D4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_E4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET);
  play_note(notes[NOTE_FS4], SEMIBREVE);
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_A4],  CROTCHET);
  play_note(notes[NOTE_A4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET);
  for (int i = 0; i < 2; i++)
  {
    play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_CS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_E4],  CROTCHET);
    play_note(notes[NOTE_B3],  CROTCHET*DOTTED);
    play_note(notes[NOTE_CS4], CROTCHET*DOTTED);
    play_note(notes[NOTE_A3],  CROTCHET);
  }
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_A4],  CROTCHET);
  play_note(notes[NOTE_FS4], SEMIBREVE);
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_A4],  CROTCHET);
  play_note(notes[NOTE_A4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET);
  play_note(notes[NOTE_F4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_GS4], CROTCHET);
  play_note(notes[NOTE_GS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_F4],  CROTCHET);
  play_note(notes[NOTE_A4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET*DOTTED);
  play_note(notes[NOTE_A4],  CROTCHET);
  play_note(notes[NOTE_B4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_A4],  CROTCHET*DOTTED);
  play_note(notes[NOTE_FS4], CROTCHET);
  play_note(notes[NOTE_FS5], SEMIBREVE);
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
}

void loop() {
  vroum();
}
