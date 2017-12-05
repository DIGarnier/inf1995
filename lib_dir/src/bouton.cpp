/**************************************************

	Ce fichier s'occupe de mettre le robot en état
 	d'attente au besoin.

**************************************************/

#include "bouton.h"

//Fait attendre le robot jusqu'à l'appuie de l'interrupteur
void attendreClic() {
	uint8_t ancinnesValeurs = PIND;
	uint8_t ancienMode = DDRD;

	PORTD = 0;
	DDRD = 0;

	while (!(PIND & _BV(PIND2)))
		del::ambre();

	DDRD = ancienMode;
	PORTD = ancinnesValeurs;

	del::eteindre();
}
