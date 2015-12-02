/*
 * Lab9Part2.c
 *
 *  Created on: Dec 1, 2015
 *      Author: Kyle
 */
#include <DSP28x_Project.h>
#include "DSP_KB.h"
#include "Lab9Part2.h"

void outputMax(unsigned int value){
	delayLONG();
	LCDclear();
	float voltage1=0;
	float voltage2=0;
	float voltage3=0;


	int int1=0;
	int int2=0;
	int int3=0;
	char c=0;

	voltage1 = value;

	voltage1 = (float)(voltage1/65535)*3.3;
	int1 = (int)voltage1;
	voltage2 = 10*(voltage1 - int1);
	int2 = (int)voltage2;
	voltage3 = 10*(voltage2-int2);
	int3 = (int)voltage3;
	c = int1 + 0x30;
	char_push(c);
	char_push('.');
	c = int2 + 0x30;
	char_push(c);
	c = int3 + 0x30;
	char_push(c);
	char_push(' ');
	char_push('V');
	char_push(' ');

}



