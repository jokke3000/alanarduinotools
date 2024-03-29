/*
* Rapide7seg_Test.c
*
* Created: 2012/12/09 23:52:15
*  Author: Alan
*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#define DIGIT_DOT	0b01111111
#define DIGIT_0		0b11000000
#define DIGIT_1		0b11111001
#define DIGIT_2		0b10100100
#define DIGIT_3		0b10110000
#define DIGIT_4		0b10011001
#define DIGIT_5		0b10010010
#define DIGIT_6		0b10000010
#define DIGIT_7		0b11111000
#define DIGIT_8		0b10000000
#define DIGIT_9		0b10010000
#define DIGIT_A		0b10001000
#define DIGIT_B		0b10000011
#define DIGIT_C		0b11000110
#define DIGIT_D		0b10100001
#define DIGIT_E		0b10000110
#define DIGIT_F		0b10001110

uint8_t DIGITS[] = {
	DIGIT_0,
	DIGIT_1,
	DIGIT_2,
	DIGIT_3,
	DIGIT_4,
	DIGIT_5,
	DIGIT_6,
	DIGIT_7,
	DIGIT_8,
	DIGIT_9,
	DIGIT_A,
	DIGIT_B,
	DIGIT_C,
	DIGIT_D,
	DIGIT_E,
	DIGIT_F
};

//one value, one digit, left to right
uint8_t mDisplayTab[4];


#define POV_DURATION 5
//Shows the in-memory table of 4 7segs
//Says from which to start and till which to go (0= leftmost, 3= rightmost)
void showDisplayTab(uint8_t pFromLeft, uint8_t pToRight){
	if (pFromLeft <= 0 && pToRight >= 0){
		PORTD = mDisplayTab[0];
		PORTC = 0x01;
		_delay_ms(POV_DURATION);
	}

	if (pFromLeft <= 1 && pToRight >= 1){
		PORTD = mDisplayTab[1];
		PORTC = 0x02;
		_delay_ms(POV_DURATION);
	}
	
	if (pFromLeft <= 2 && pToRight >= 2){
		PORTD = mDisplayTab[2];
		PORTC = 0x04;
		_delay_ms(POV_DURATION);
	}

	if (pFromLeft <= 3 && pToRight >= 3){
		PORTD = mDisplayTab[3];
		PORTC = 0x08;
		_delay_ms(POV_DURATION);
	}
}

#define POV_ITERATIONS 10
void showNumber(uint16_t pNumber, uint8_t pFromLeft, uint8_t pToRight){
	//display on the 3 leftmost digits
	mDisplayTab[3] = DIGITS[pNumber % (uint16_t)10];
	mDisplayTab[2] = DIGITS[(pNumber / (uint16_t)10) % (uint16_t)10];
	mDisplayTab[1] = DIGITS[(pNumber / (uint16_t)100) % (uint16_t)10];
	mDisplayTab[0] = DIGITS[(pNumber / (uint16_t)1000) % (uint16_t)10];
			
	for (uint16_t vPOV = 0; vPOV < POV_ITERATIONS; vPOV++){
		showDisplayTab(pFromLeft,pToRight);
	}	
}

int main(void)
{
	//factory settings is to divide internal clock 8MHz by 8.
	//don't, and just run at 8 MHz (set the clock divider to 1 so no effect)
	CLKPR = (1<<CLKPCE);
	CLKPR = 0; // Divide by 1
	
	//Driver of the common anode is from PC0 (1st 7seg) to PC3 (4th 7seg)
	//Lower 4 go output
	DDRC = 0x0F;
	//all segments on
	PORTC = 0xFF;
	
	//the 7seg legs are driven by pins PIND
	//all pins are output
	DDRD = 0xFF;
	
	while(1)
	{
		/* 
		for (uint8_t i= 0; i < (uint8_t)4; i++){
			
			PORTD = DIGIT_9;
			_delay_ms(1000);
		}
		*/

		/*
		//count 0-F all digits
		for (uint8_t vCount = 0; vCount < (uint8_t)16; vCount++ ){
			for (uint8_t i= 0; i < (uint8_t)4; i++){
				
				PORTD = DIGITS[vCount];
				_delay_ms(1000);
			}
		}
		*/
/*
		for (uint16_t vNumber = 0; vNumber < 1000; vNumber++){
			uint16_t vVal = vNumber * 10;
			
			//display on the 3 leftmost digits
			mDisplayTab[3] = DIGITS[vVal % (uint16_t)10];
			mDisplayTab[2] = DIGITS[(vVal / (uint16_t)10) % (uint16_t)10];
			mDisplayTab[1] = DIGITS[(vVal / (uint16_t)100) % (uint16_t)10];
			mDisplayTab[0] = DIGITS[(vVal / (uint16_t)1000) % (uint16_t)10];
			
			for (uint16_t vPOV = 0; vPOV < 10; vPOV++){
				showDisplayTab(0,2);
			}
		}
*/		
		for (uint16_t vNumber = 0; vNumber < 1000; vNumber++){
			uint16_t vVal = vNumber * 10;
			showNumber(vVal, 0, 2);
		}
	}
}

