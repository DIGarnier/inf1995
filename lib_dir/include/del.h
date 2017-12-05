// DEL COULEUR SUR PORTC6-C7


#ifndef DEL_H
#define DEL_H

#include "config.h"
#include "erreur.h"

#include<util/delay.h>


namespace del {

	constexpr uint8_t P1 = _BV(PORTB1);
	constexpr uint8_t P2 = _BV(PORTB0);
	constexpr uint8_t PS = (P1 | P2);

	void setup();

	/*
	void allumer(uint8_t choix);
	void eteindre(uint8_t choix);
	*/

	void rouge();
	void vert();
	void ambre();

	void eteindre();

}

#endif /* DEL_H */
