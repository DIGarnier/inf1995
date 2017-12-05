/*
 * Conventions:
 * 
 * 	-Del(verte sur VCC):	PORTC6-7
 * 	-Bouton interne: 		PIND2
 *  -Interruption bouton: 	PIND2
 * 	-PWM Gauche:		 	PORTD4
 * 	-PWM Droite:			PORTD5
 * 	-Roue Gauche:			PORTD2
 * 	-Roue Droite:			PORTD3
 *	-Debug enable:		 	PORTD0-1
 * 	-Mem.  enable:	 		PORTC0-1
 *  -Audio PWM:             PORTC7-8
 * 	
 * 
 * 
 * 
 *	CRITIQUE:
 *  S'assurer de toujours setup USB.
 */


#ifndef CONFIG_H
#define CONFIG_H

#define F_CPU 8000000

#include <avr/io.h>

#define TIMER1_PRESCALER_64 _BV(CS11)|_BV(CS10)
#define TIMER1_PRESCALER_256 _BV(CS12)
#define TIMER1_PRESCALER_1024 _BV(CS12)|_BV(CS10)

#define TIMER0_PRESCALER_1024 _BV(CS02) | _BV(CS00)

#define TIMER2_PRESCALER_1024 _BV(CS22) | _BV(CS21) | _BV(CS20)

// PWM
constexpr uint8_t PWM_G = _BV(PORTD4); //OC1B
constexpr uint8_t PWM_D = _BV(PORTD5); //OC1A

enum Piezo {
	droite,
	gauche,
	deux
};

#endif /* CONFIG_H */
