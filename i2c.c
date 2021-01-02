/*
 * Copyright 2017 Google, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int MiarmI2CSetup (const int i2cid,const int devId);

void set_backlight( int fd, int r, int g, int b )
{
  wiringPiI2CWriteReg8( fd, 0, 0 );
  wiringPiI2CWriteReg8( fd, 1, 0 );
  wiringPiI2CWriteReg8( fd, 8, 0xaa );
  wiringPiI2CWriteReg8( fd, 4, r );
  wiringPiI2CWriteReg8( fd, 3, g );
  wiringPiI2CWriteReg8( fd, 2, b );
}

void textCommand(int fd1, int cmd)
{
  wiringPiI2CWriteReg8(fd1, 0x80, cmd);
}

void setText(int fd1, char * text)
{
    int i;
    textCommand(fd1, 0x01); // clear display
    delay(50);
    textCommand(fd1, 0x08 | 0x04); // display on, no cursor
    textCommand(fd1, 0x28); // 2 lines
    delay(50);
    for (i=0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            textCommand(fd1, 0xc0);
	} else {
            wiringPiI2CWriteReg8(fd1, 0x40, text[i]);
	}
    }
}

int i2c_lcd_test (void)
{
  int i;
  int fd;
  int fd1;
  printf ("Tinkerboard i2c test\n") ;

  wiringPiSetup () ;
  fd = MiarmI2CSetup (1, 0x62);    // 0x62 is rgb, 0x3e is text
  fd1 = MiarmI2CSetup (1, 0x3e);

  textCommand( fd1, 0x01 );        // clear display
  delay( 50 );
  textCommand( fd1, 0x08 | 0x04 ); // display on, no cursor
  textCommand( fd1, 0x28 );        // 2 lines
  delay( 50 );

  set_backlight( fd, 255, 0, 0 );
  for (i=0; i<5; i++)
  {
    set_backlight( fd, 255, 0, 0 );
    delay (1000) ;		// mS
    set_backlight( fd, 255, 255, 0 );
    delay (1000) ;		// mS
    set_backlight( fd, 0, 255, 0 );
    delay (1000) ;		// mS
    set_backlight( fd, 0, 255, 255 );
    delay (1000) ;		// mS
    set_backlight( fd, 0, 0, 255 );
    delay (1000) ;		// mS
    set_backlight( fd, 255, 0, 255 );
    delay (1000) ;		// mS
  }
  set_backlight( fd, 128, 255, 0 );
  setText( fd1, "Hello world !\nIt works !\n" );
  return 0 ;
}
