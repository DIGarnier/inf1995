#ifndef PARCOURS_H
#define PARCOURS_H

#include "config.h"
#include "erreur.h"
#include "roues.h"
#include "capteurs.h"
#include "chemin.h"
#include "del.h"

namespace deplacement {

	const uint8_t vitesseNominale = 140;
	const uint8_t vitesseRotation = 110;
	const uint8_t troisGauche = 0b111;
	const uint8_t troisMilieu = 0b1110;
	const uint8_t troisDroite = 0b11100;
	const uint8_t milieu = 0b100;

	bool estCoinProbleme(uint8_t orientation, uint8_t direction, char node);
	uint8_t calculDifference(uint8_t orientation, uint8_t direction);

	void noeudANoeud(char position0, char position1, uint8_t &orientation);


	void reculerJusquaIntersection();
	void quitterIntersection(bool sansDelai = false);
	void suivreLigne(bool arreterBlanc = false);
	void tournerDroite(bool sauterLigne = false, bool sansDelai = false);
	void tournerGauche(bool sauterLigne = false, bool sansDelai = false);

	bool estInsecte(const char insecte[chemin::MAX_INSECTS], uint8_t nbInsects, char positionCourante);
	void retirerInsecte(char (&insectes)[chemin::MAX_INSECTS], char insecte);

}

#endif /* PARCOURS_H */
