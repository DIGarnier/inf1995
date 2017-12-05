#ifndef DETECTION_H
#define DETECTION_H


#include "capteurs.h"
#include "roues.h"
#include "chemin.h"
#include "deplacement.h"
#include "musique.h"

namespace detection {

	const uint8_t RAYON_INTERNE_DROIT = 150;
	const uint8_t RAYON_EXTERNE_DROIT = 60;
	const uint8_t RAYON_INTERNE_DIAGONAL = 80;
	const uint8_t RAYON_EXTERNE_DIAGONAL = 45;

	const uint8_t vitesseDetection = 100;

	uint8_t commencer(char (&insectes)[chemin::MAX_INSECTS], volatile uint8_t &quartTours);

	uint8_t orientation(uint8_t lignes);

	uint8_t moyenne();
	uint8_t lectureApprofondie();

	bool dejaDetecte(char (&insectes)[chemin::MAX_INSECTS], uint8_t insectesTrouves, uint8_t lignes);
}


#endif // DETECTION_H

