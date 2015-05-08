/*
 *Author: gaburiero
 *Based on Derek Malloy's software
 *
*/ 

#ifndef BBBGPIO_H_
#define BBBGPIO_H_

#define MAX 64
#define GPIO_LOCATION "/sys/class/gpio"

enum PIN_DIR {
	INPUT  = 0;
	OUTPUT = 1;
};

enum PIN_VALUE {
	LOW  = 0;
	HIGH = 1;
};

void gpioExport(unsigned int gpio);
void gpioUnexport(unsigned int gpio);
void gpioSetDirection(unsigned int gpio, PIN_DIR flag);
void gpioSetValue(unsigned int gpio, PIN_VALUE value);

#endif
