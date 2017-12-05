/**************************************************

	Ce fichier s'occupe de déplacer le robot de façon
 	intelligente tout en suivant un chemin (celui
 	construit par chemin.cpp en l'occurence).

**************************************************/

#include "deplacement.h"

namespace deplacement {
	//Sert à identifier si le demi-tour doit se faire dans le sens inverse
	bool estCoinProbleme(uint8_t orientation, uint8_t direction, char node) {
		if (orientation == 0 && direction == 4 && node == 'H')
			return true;
		if (orientation == 2 && direction == 6 && node == 'B')
			return true;
		if (orientation == 4 && direction == 0 && node == 'D')
			return true;
		if (orientation == 6 && direction == 2 && node == 'F')
			return true;
		return false;
	}

	//Calcule la différence entre la direction et l'orientation, ramené entre 0 et 7 si négative
	uint8_t calculDifference(uint8_t orientation, uint8_t direction) {
		uint8_t difference;
		difference = direction - orientation + 8;
		if (difference >= 8)
			difference -= 8;

		assert_expr(difference < 8, __LINE__, __FILE__);

		return difference;
	}

	//Donne les directive pour atteindre le noeud suivant
	void noeudANoeud(char position0, char position1, uint8_t &orientation) {
		uint8_t direction = chemin::findDirection(position0, position1);

		if (direction == 255)
			return;

		uint8_t difference = calculDifference(orientation, direction);
		uint8_t lineData = capteurs::lignes();

		LCD.clear();
		LCD << "Je suis à " << position0 << " je vais à " << position1;

		/* Le comportement du robot est prévisible en fonction de la difference
		 * entre l'orientation et la destination, ce qui donne une direction 
		 * dans le référentiel du robot Si l'orientation est impaire
		 * le robot est sur un coin et le comportement varie.*/
		if (orientation % 2 == 0) {
			switch (difference) {
				case 0:
					break;
				case 1:
					// edge-case
					if (lineData == 0)
						tournerDroite(false);

					break;
				case 2:
					tournerDroite(false);
					break;
				case 3:
					tournerDroite(true);
					break;
				case 4:
					if (estCoinProbleme(orientation, direction, position0))
						tournerGauche(true);
					else
						tournerDroite(true);
					break;
				case 5:
					tournerGauche(true);
					break;
				case 6 :
					tournerGauche(false);
					break;
				case 7 :
					// edge-case
					if (lineData == 0)
						tournerGauche(false);

					break;
			}
		} else {
			assert_expr(difference % 2 == 1 || difference == 4, __LINE__, __FILE__);
			switch (difference) {
				case 1:
				case 3:
					tournerDroite(false);
					break;
				case 5:
				case 7:
					tournerGauche(false);
					break;
				case 4:
					// edge-case
					if (!(lineData & 0x10) && !(lineData & 0b1110))
						tournerDroite(false);

					tournerDroite(true); //Demi-tour
					break;
			}
		}

		suivreLigne();

		orientation = direction;
	}

	//Fait reculer le robot jusqu'à l'intersection précédente
	void reculerJusquaIntersection() {

		bool ancienEtatDroit = capteurs::extractAndCompare(capteurs::lignes(), troisDroite);
		bool ancienEtatMilieu = capteurs::extractAndCompare(capteurs::lignes(), troisMilieu);
		bool ancienEtatGauche = capteurs::extractAndCompare(capteurs::lignes(), troisGauche);


		roues::reculer(vitesseNominale);

		while (!(capteurs::rising_edge(ancienEtatDroit, troisDroite) ||
				 capteurs::rising_edge(ancienEtatMilieu, troisMilieu) ||
				 capteurs::rising_edge(ancienEtatGauche, troisGauche)));

		roues::freiner();
	}
	
	//Avance pour ne plus être à l'intersection
	void quitterIntersection(bool sansDelai) {

		bool ancienEtatDroit = capteurs::extractAndCompare(capteurs::lignes(), troisDroite);
		bool ancienEtatMilieu = capteurs::extractAndCompare(capteurs::lignes(), troisMilieu);
		bool ancienEtatGauche = capteurs::extractAndCompare(capteurs::lignes(), troisGauche);

		if (ancienEtatDroit || ancienEtatGauche || ancienEtatMilieu) {

			roues::avancer(vitesseNominale);

			while (!(capteurs::falling_edge(ancienEtatDroit, troisDroite) ||
					 capteurs::falling_edge(ancienEtatMilieu, troisMilieu) ||
					 capteurs::falling_edge(ancienEtatGauche, troisGauche)));
			if (!sansDelai)
				_delay_ms(600);
		}

		roues::arreter();
	}
	
	//Avance en suivant la ligne jusqu'à la prochaine intersection,
	//ou jusqu'à le fin de la ligne si le bool est true
	void suivreLigne(bool arreterBlanc) {

		quitterIntersection();

		uint8_t lineData = capteurs::lignes();

		roues::avancer(vitesseNominale);

		while (!(capteurs::extractAndCompare(lineData, troisDroite) ||
				 capteurs::extractAndCompare(lineData, troisMilieu) ||
				 capteurs::extractAndCompare(lineData, troisGauche))) {

			if (capteurs::lignes() == 0 && arreterBlanc) {
				// anti-rebond
				_delay_ms(25);
				if (capteurs::lignes() == 0) {
					break;
				}
			}

			if (lineData & milieu)
				roues::avancer(vitesseNominale);
			else if (lineData == 0b1) {
				roues::directionGauche(false);
				roues::directionDroite(true);
				roues::vitesseGauche(vitesseRotation);
				roues::vitesseDroite(90);
			} else if (lineData == 0x10) {
				roues::directionGauche(true);
				roues::directionDroite(false);
				roues::vitesseGauche(90);
				roues::vitesseDroite(vitesseRotation);
			} else if (capteurs::extractAndCompare(lineData, 0b11)) {
				roues::directionDeuxRoues(true);
				roues::vitesseDroite(vitesseNominale);
				roues::vitesseGauche(vitesseNominale - 60);
			} else if (capteurs::extractAndCompare(lineData, 0b10)) {
				roues::directionDeuxRoues(true);
				roues::vitesseDroite(vitesseNominale);
				roues::vitesseGauche(vitesseNominale - 40);
			} else if (capteurs::extractAndCompare(lineData, 0b11000)) {
				roues::directionDeuxRoues(true);
				roues::vitesseGauche(vitesseNominale);
				roues::vitesseDroite(vitesseNominale - 60);
			} else if (capteurs::extractAndCompare(lineData, 0b1000)) {
				roues::directionDeuxRoues(true);
				roues::vitesseGauche(vitesseNominale);
				roues::vitesseDroite(vitesseNominale - 40);
			}

			lineData = capteurs::lignes();
		}

		if (!arreterBlanc) {
			roues::avancer(vitesseNominale);
			_delay_ms(300);
		}

		roues::arreter();

	}

	//Tourne à droite, en sautant une ligne si sauterLigne est à true
	void tournerDroite(bool sauterLigne, bool sansDelai) {

		quitterIntersection(sansDelai);

		roues::vitesseDroite(vitesseRotation);
		roues::vitesseGauche(vitesseRotation);
		roues::directionDroite(false);
		roues::directionGauche(true);

		bool ancienEtat = capteurs::extractAndCompare(capteurs::lignes(), 0x10);

		if (sauterLigne) {

			while (!(capteurs::rising_edge(ancienEtat, 0x10)));
		}

		while (!(capteurs::rising_edge(ancienEtat, 0x10)));

		roues::arreter();
		_delay_ms(100);
	}

	//Tourne à gauche, en sautant une ligne si sauterLigne est à true
	void tournerGauche(bool sauterLigne, bool sansDelai) {

		quitterIntersection(sansDelai);

		roues::vitesseDroite(vitesseRotation);
		roues::vitesseGauche(vitesseRotation);
		roues::directionDroite(true);
		roues::directionGauche(false);

		bool ancienEtat = capteurs::extractAndCompare(capteurs::lignes(), 1);

		if (sauterLigne) {
			while (!(capteurs::rising_edge(ancienEtat, 1)));
		}

		while (!(capteurs::rising_edge(ancienEtat, 1)));

		roues::arreter();
		_delay_ms(100);
	}

	//Vérifie si le noeud actuel contien un insecte
	bool estInsecte(const char insecte[chemin::MAX_INSECTS], uint8_t nbInsects, char positionCourante) {

		for (uint8_t i = 0; i < nbInsects; i++) {

			if (insecte[i] == positionCourante)
				return true;

		}

		return false;

	}

	//Retire l'instecte du tableau d'insecte à dévorer
	void retirerInsecte(char (&insectes)[chemin::MAX_INSECTS], char insecte) {

		for (uint8_t i = 0; i < chemin::MAX_INSECTS; i++) {

			if (insectes[i] == insecte) {
				insectes[i] = 'Z';
				return;
			}
		}
	}

}

