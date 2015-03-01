/*! \file button.c
  \brief Example: get state of a button.

  This file contains an example on how to use libpruio to get the state
  of a button connetect to a GPIO pin on the beaglebone board. Here pin 7
  on header P8 is used as input with pullup resistor. Connect the button
  between P8_07 (GPIO input) and P8_01 (GND).

Licence: GPLv3

Copyright 2014 by Thomas{ dOt ]Freiherr[ At ]gmx[ DoT }net


Compile by: `gcc -Wall -o button button.c -lpruio`

 */


//! Message for the compiler.
#define _GNU_SOURCE 1
#include "stdio.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "../c_wrapper/pruio.h"
#include "../c_wrapper/pruio_pins.h"

//! The header pin to use.
#define PIN P8_16

/*! \brief Wait for keystroke or timeout.
  \param mseconds Timeout value in milliseconds.
  \returns 0 if timeout, 1 if input available, -1 on error.

  Wait for a keystroke or timeout and return which of the events happened.

 */
int isleep(unsigned int mseconds)
{
	fd_set set;
	struct timeval timeout;

	/* Initialize the file descriptor set. */
	FD_ZERO(&set);
	FD_SET(STDIN_FILENO, &set);

	/* Initialize the timeout data structure. */
	timeout.tv_sec = 0;
	timeout.tv_usec = mseconds * 1000;

	return TEMP_FAILURE_RETRY(select(FD_SETSIZE,
				&set, NULL, NULL,
				&timeout));
}

//! The main function.
int main(int argc, char **argv)
{
	pruIo *io = pruio_new(PRUIO_DEF_ACTIVE, 0x98, 0, 1); //! create new driver structure

	int high, low;
	int count = 0;

	do {
		if (io->Errr) {
			printf("initialisation failed (%s)\n", io->Errr); break;}

		if (pruio_config(io, 1, 0x1FE, 0, 4)) {
			printf("config failed (%s)\n", io->Errr); break;}

		while(!isleep(1)) { //                      run loop until keystroke
		//while(count++ < 100) { //                      run loop until keystroke
			low = 0;
			high = 0;

			while(((int) pruio_gpio_Value(io, PIN)) == 1) {
				if(low++ > 900000) 
					break;
			}//close while low

			while(((int) pruio_gpio_Value(io, PIN)) == 0) {
				if(high++ > 900000) 
					break;
			}//close while low

			//usleep(120);
			printf("%d %d\n", low, high);
		}//close while sleep
	} while (0);

	printf("killed!\n");
	pruio_destroy(io);       /* destroy driver structure */
	return 0;
}