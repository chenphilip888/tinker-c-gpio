/*
 * pwm.c:
 *	This tests the hardware PWM channel.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "pitches.h"

#define servopin 26
#define buzzpin 26
#define pwmpin 26

int pwm_led_test (void)
{
  int i;
  int bright ;

  printf ("Tinkerboard wiringPi PWM test program\n") ;
  wiringPiSetup();
  pinMode (pwmpin, PWM_OUTPUT) ;
  for (i=0; i<10; i++)
  {
    for (bright = 0 ; bright < 1024 ; bright=bright+4)
    {
      pwmWrite (pwmpin, bright) ;
      delay (5) ;
    }

    for (bright = 1023 ; bright >= 0 ; bright=bright-4)
    {
      pwmWrite (pwmpin, bright) ;
      delay (5) ;
    }
  }

  return 0 ;
}

/*
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
*/
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, 0,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
};

void tone(int melody, int duration) {
  if (melody == 0) {
     usleep(duration);
  } else {
     pwmToneWrite(buzzpin, melody);
     pwmWrite(buzzpin, melody / 2);
     usleep(duration);
     pwmWrite(buzzpin, 0);
  }
  usleep(duration * 0.8);
}

int tongsong (void)
{
  int bright ;

  printf ("Tinkerboard wiringPi PWM test program\n") ;
  wiringPiSetup();
  pinMode (buzzpin, PWM_OUTPUT) ;

  for (int thisNote = 0; thisNote < 48; thisNote++) {
     int noteDuration = 1000000 / noteDurations[thisNote];
     tone(melody[thisNote], noteDuration);
  }
  return 0 ;
}

int servo (void)
{
  int i;

  printf ("Tinkerboard wiringPi servo test program\n") ;
  wiringPiSetup();
  pinMode (servopin, PWM_OUTPUT) ;
  pwmSetMode (PWM_MODE_MS) ;
  pwmSetClock (445);    // 74.25 MHz / 445 / 1024 = 163 Hz
  pwmSetRange (1024);
  pwmWrite( servopin, 205 );   // min 205 = 0 degree, max 845 = 180 degree

  for (i=0; i<3; i++)
  {
    pwmWrite( servopin, 205);
    printf("0 degree\n");
    delay(1000);
    pwmWrite( servopin, 525);
    printf("90 degree\n");
    delay(1000);
    pwmWrite( servopin, 845);
    printf("180 degree\n");
    delay(1000);
    pwmWrite( servopin, 525);
    printf("90 degree\n");
    delay(1000);
  }

  pwmWrite( servopin, 0 );
  return 0 ;
}
