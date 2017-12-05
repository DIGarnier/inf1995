/**************************************************

	Ce fichier s'occupe de la configuration et
 	de la gestion des capteurs de lignes et de
 	distance.

**************************************************/

#include "capteurs.h"

namespace capteurs {

	static bool estSetup = false;
	can converter;
	
	//Initialise le portA pour le can et le capteur de ligne
	void setup() {
		DDRA = 0;
		estSetup = true;
	}

	//Fait une lecture du capteur de distance
	uint8_t distance() {
		assert_expr(estSetup, __LINE__, __FILE__);

		return converter.lecture(7) >> 2;
	}

	//Fait une lecture du capteur de ligne
	uint8_t lignes() {
		assert_expr(estSetup, __LINE__, __FILE__);

		return LIGNES & PINA;
	}

	//Detecte un front montant du capteur de ligne
	bool rising_edge(bool &ancienEtat, uint8_t etatDesire) {
		bool nouvelEtat = extractAndCompare(capteurs::lignes(), etatDesire);

		if (ancienEtat == nouvelEtat)
			return false;
		else {
			ancienEtat = nouvelEtat;
			return ancienEtat;
		}
	}

	//Detecte un front descendant du capteur de ligne
	bool falling_edge(bool &ancienEtat, uint8_t etatDesire) {
		bool nouvelEtat = extractAndCompare(capteurs::lignes(), etatDesire);

		if (ancienEtat == nouvelEtat)
			return false;
		else {
			ancienEtat = nouvelEtat;
			return !ancienEtat;
		}
	}

	//Compare une première valeur avec un masque
	bool extractAndCompare(uint8_t one, uint8_t two) {
		return (one & two) == two;
	}
}
