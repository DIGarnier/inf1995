/**************************************************

	Ce fichier s'occupe de la séquence de détection.

**************************************************/

#include "detection.h"

namespace detection {

	// fait la détection au complet et retourne en référence les insectes détectés
	uint8_t commencer(char (&insectes)[chemin::MAX_INSECTS], volatile uint8_t &quartTours) {
		uint8_t insectes_trouves = 0;
		bool estAllume = true;
		uint8_t ligne = capteurs::lignes();

		quartTours = 0;

		roues::kickDroit();

		while (quartTours < 4) {

			roues::tournerDroite(vitesseDetection);

			uint8_t distance = capteurs::distance();
			ligne = capteurs::lignes();

			if (distance > RAYON_EXTERNE_DROIT && ligne & 0b1110) {

				if (dejaDetecte(insectes, insectes_trouves, quartTours) || insectes_trouves >= 5)
					continue;

				uint8_t bonneLecture = lectureApprofondie();

				ligne = capteurs::lignes();

				if (bonneLecture > RAYON_INTERNE_DROIT && ligne & 0b1110) {

					LCD.clear();
					LCD << bonneLecture;

					insectes[insectes_trouves++] = chemin::indexToChar(quartTours * 2 + 1);
					roues::freiner(vitesseDetection);
					musique::insecte(true);

					roues::kickDroit();

					roues::tournerDroite(vitesseDetection);

					while (ligne != 0)
						ligne = capteurs::lignes();
					_delay_ms(100);

				} else if (bonneLecture > RAYON_EXTERNE_DROIT && ligne & 0b1110) {

					LCD.clear();
					LCD << bonneLecture;

					insectes[insectes_trouves++] = chemin::indexToChar(quartTours * 2 + 9);
					roues::freiner(vitesseDetection);
					musique::insecte(false);

					roues::kickDroit();

					roues::tournerDroite(vitesseDetection);

					while (ligne != 0)
						ligne = capteurs::lignes();
					_delay_ms(100);
				}

			} else if (distance > RAYON_EXTERNE_DIAGONAL && ligne == 0) {
				if (dejaDetecte(insectes, insectes_trouves, quartTours) || insectes_trouves >= 5)
					continue;

				uint8_t bonneLecture = lectureApprofondie();

				ligne = capteurs::lignes();

				if (bonneLecture > RAYON_INTERNE_DIAGONAL && ligne == 0) {

					LCD.clear();
					LCD << bonneLecture;

					insectes[insectes_trouves++] = chemin::indexToChar(quartTours * 2 + 2);
					roues::freiner(vitesseDetection);
					musique::insecte(true);

					roues::kickDroit();

				} else if (bonneLecture > RAYON_EXTERNE_DIAGONAL && ligne == 0) {

					LCD.clear();
					LCD << bonneLecture;

					insectes[insectes_trouves++] = chemin::indexToChar(quartTours * 2 + 10);
					roues::freiner(vitesseDetection);
					musique::insecte(false);

					roues::kickDroit();
				}
			}
		}

		ligne = capteurs::lignes();
		roues::tournerDroite(vitesseDetection);

		if (ligne != 0 && !(ligne & 0b11))
			while (!capteurs::rising_edge(estAllume, deplacement::milieu));

		roues::arreter();

		return insectes_trouves;
	}

	// donne la présente orientation du robot selon les données présentes
	uint8_t orientation(uint8_t lignes) {

		if (capteurs::lignes() == 0)
			return lignes * 2 + 1;
		else
			return lignes * 2;
	}

	// fait une moyenne de 100 lecture
	uint8_t moyenne() {
		uint16_t somme = 0;

		for (uint8_t i = 0; i < 100; i++) {
			somme += capteurs::distance();
		}

		return somme / 100;
	}

	// s'occupe de faire 10 moyennes et de retourner la plus petit
	// donc la plus proche
	uint8_t lectureApprofondie() {
		uint8_t plusHaute = 0;
		uint8_t lecture;

		for (uint8_t i = 0; i < 10; i++) {

			lecture = moyenne();

			if (plusHaute < lecture)
				plusHaute = lecture;
		}

		return plusHaute;
	}

	// nous dit si une détection à déjà été fait dans la direction d'un des insectes
	bool dejaDetecte(char (&insectes)[chemin::MAX_INSECTS], uint8_t insectesTrouves, uint8_t lignes) {
		char insecteInterieur = chemin::indexToChar(orientation(lignes) + 1);
		char insecteExterieur = chemin::indexToChar(orientation(lignes) + 9);

		return deplacement::estInsecte(insectes, insectesTrouves, insecteInterieur) ||
			   deplacement::estInsecte(insectes, insectesTrouves, insecteExterieur);

	}

}