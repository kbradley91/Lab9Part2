/*
 * main.c
 */
#include <DSP28x_Project.h>
#include "DSP_KB.h"
#include "Lab9Part2.h"
#include <math.h>

#define M_PI 3.14159265358979323846
interrupt void sampleP2_ISR(void);
static int bufferFull = 0;
static unsigned int bufferValue = 0;
unsigned long ISRvalue = &sampleP2_ISR;
static unsigned int sampleArray[64];
static float x_Temp[64];
static float x_Real[64];
static float mag[64];

void calculateAmplitude(void);


int main(void) {
	
	DisableDog();
	CPUinit();
	EALLOW;
	outputEnable();
	LCDinit();
	LCDclear();
	initADC();
	DAC_init();
//	SRAMwrite(0);
//	SRAMaddress = 0x260000; //shouldn't need SRAM here

	timerINIT(ISRvalue, samplingRate);

	while(1){
		if(bufferFull){
			DFT();
			calculateAmplitude();
			//run algorithm on values;
		}
		else{
			//do nothing
		}


	}


	return 0;
}

interrupt void sampleP2_ISR(void){

	unsigned int input = ADC_get();
	sampleArray[bufferValue] = input;
	bufferValue++;


	if(bufferValue>63){
		bufferValue = 0;
		bufferFull = 1;
		DINT;
	}

}

void DFT(){
	int N = 64;
	int k, i;
	for(k=0;k<64;k++){
		x_Real[k] = 0;
		x_Temp[k] = 0;
		for(i = 0;i<64;i++){

			x_Real[k] += sampleArray[i]*cos(2*M_PI*k*i/64);

			x_Temp[k] -= sampleArray[i]*sin(2*M_PI*k*i/64);

		}
		mag[k] = x_Real[k]*x_Real[k]+x_Temp[k]*x_Temp[k];

	}

}

void calculateAmplitude(void){
	unsigned int amp;
	unsigned int freq;
	float tempFreq;
	int i;
	float x1, x2;
	int j = 0; //j will hold the index value for the frequency
	float temp;
	float max = 0;
	for(i = 0;i < 64; i++){
		temp = mag[i];
		if(temp>max){
			max = temp;
			j = i;
		}
	}

	tempFreq = samplingRate*j/64;

	outputMax(max);

}





