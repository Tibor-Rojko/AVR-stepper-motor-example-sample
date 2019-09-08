/***********************************************************************************************
 * Stepper Motor Control example/sample program                                       
 * main.c 
 * 2019, Tibor Rojko
 *
 * For driving stepper motor, use ULN2003 darlington transistors array!
 * Different types of stepping modes:
 * - Wave drive
 * - Full drive
 * - Half drive
 *
 * connections:
 * MCU Board to ULN2003 module
 * PD4(D4) to IN1
 * PD5(D5) to IN2
 * PD6(D6) to IN3
 * PD7(D7) to IN4
 **********************************************************************************************/


#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

/*** Global variables & definitions ***/
#define IN1						PIND4
#define IN2						PIND5
#define IN3						PIND6	
#define IN4						PIND7
#define STEPPER_PORT			PORTD
#define STEPPER_PORT_DIRECTION	DDRD

int main(void)
{
	/*** set all stepper control pin as output ***/
	STEPPER_PORT_DIRECTION = (1 << IN1) |(1 << IN2) |(1 << IN3) | (1 << IN4);
    
	while (1) 
    {
		/*
		Wave drive:
		1 stator electromagnet is energized
		For 360 degree rotation, 2048 steps are required! (2048/4=512)
		*/
		for(int i = 0; i<=512; i++)
		{
			/*** to vary the RPM change delays beetween steps ***/

			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(4);					// wait 6 ms
		
			STEPPER_PORT &= ~(1 << IN1);		
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(4);					// wait 6 ms
			
			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);		
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(4);					// wait 6 ms
			
			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);		
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(4);					// wait 6 ms	
		}

		_delay_ms(1000);

		/*
		Full drive:
		2 stator electromagnet is energized
		For 360 degree rotation, 2048 steps are required! (2048/4=512)
		*/
		for(int i = 0; i<=512; i++)
		{
			/*** to vary the RPM change delays beetween steps ***/

			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms
			
			STEPPER_PORT &= ~(1 << IN1);		
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms
			
			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);		
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms
			
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);		
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms	
		}

		_delay_ms(1000);

		/* if we want to rotate the motor by a particular angle i.e 10 deg, use this formula (90/(360/512)) = 128 
		   if you want to rotate anti clockwise, just change the sequence queue 	
		*/
		for(int i = 0; i<=128; i++)
		{
			/*** to vary the RPM change delays beetween steps ***/
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

				
			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

				
			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms
		}
		
		_delay_ms(1000);

		/*
		Half drive:
		*/
		for(int i = 0; i<=512; i++)
		{
			/*** to vary the RPM change delays beetween steps ***/
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);	
			_delay_ms(2);					// wait 2 ms

			
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms
		}

		_delay_ms(2000);

		/*
		Half drive, degree 180
		*/
		for(int i = 0; i<=256; i++)
		{
			/*** to vary the RPM change delays beetween steps ***/
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);	
			_delay_ms(2);					// wait 2 ms

			
			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT |= (1 << IN2);		// IN2 to HIGH
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT &= ~(1 << IN4);
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT |= (1 << IN3);		// IN3 to HIGH
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT &= ~(1 << IN1);
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms

			STEPPER_PORT |= (1 << IN1);		// IN1 to HIGH
			STEPPER_PORT &= ~(1 << IN2);
			STEPPER_PORT &= ~(1 << IN3);
			STEPPER_PORT |= (1 << IN4);		// IN4 to HIGH
			_delay_ms(2);					// wait 2 ms
		}

		_delay_ms(2000);

    }

	return 0;

}

