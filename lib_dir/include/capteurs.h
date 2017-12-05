
#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "can.h"
#include "erreur.h"

namespace capteurs {

	const uint8_t LIGNES = 0x1F;

	void setup();

	uint8_t distance();

	uint8_t lignes();

	bool rising_edge(bool &ancienEtat, uint8_t etatDesire);
	bool falling_edge(bool &ancienEtat, uint8_t etatDesire);
	bool extractAndCompare(uint8_t one, uint8_t two);

}

#endif /* CAPTEURS_H */
