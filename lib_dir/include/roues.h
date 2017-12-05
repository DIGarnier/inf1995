

#ifndef ROUES_H
#define ROUES_H

#include "config.h"
#include "erreur.h"

#include<util/delay.h>

namespace roues {

	constexpr uint8_t SENS_G = _BV(PORTD2);
	constexpr uint8_t SENS_D = _BV(PORTD3);

	void setup();

	void vitesseGauche(uint8_t ratio);
	void vitesseDroite(uint8_t ratio);

	void directionGauche(bool avance);
	void directionDroite(bool avance);
	void directionDeuxRoues(bool avancer);
	void inverserDirections();

	void tournerGauche(uint8_t ratio);
	void tournerDroite(uint8_t ratio);

	void kickDroit();
	void boost();
	void freiner(uint8_t vitesse = 0xFF);

	void reculer(uint8_t ratio);
	void avancer(uint8_t ratio);

	void arreter();

	void clearTimer();

}

#endif /* ROUES_H */
