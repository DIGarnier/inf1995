#include "del.h"
#include "audio.h"
#include "roues.h"
#include "deplacement.h"
#include "musique.h"
#include "detection.h"

#include <avr/interrupt.h>


// Variable globale, mise volatile pour forcer avr-gcc à les garder
volatile uint16_t counter = 0;
volatile uint8_t quartTour = 0;

// ISR répondant à l'intérruption du timer0 pour la détection de la sortie
// potentielle
ISR(TIMER0_COMPA_vect) {
	counter++;
}

// Répond à un interrupt lancé par le capteur du milieu du détecteur de ligne
// et augmente le nombre de ligne visité
ISR(PCINT0_vect) {
	if (capteurs::lignes() & 0x10 && quartTour < 4)
		quartTour++;
}

// Fonction d'initialisation regroupant toutes les autres
void setup() {
	cli();
	audio::setup();
	roues::setup();
	del::setup();
	capteurs::setup();
	sei();
}

int main() {

	setup();

	_delay_ms(3000);

	/*
	 * 				ANALYSE
	 *
	 * En ne pivotant que sur lui-même, le robot devra effectuer une analyse
	 * de la toile pour identifier où se trouvent les insectes (poteaux) pris
	 * au piège. À chaque fois qu’il détectera un poteau, le robot devra s’arrêter,
	 * émettre un son aigu et allumer sa DEL. La DEL sera en vert si l’objet détecté
	 * est sur le carré intérieur, en rouge s’il est sur le carré extérieur. La DEL et
	 * le son doivent être actifs pendant trois secondes, après quoi ils s’éteignent et
	 * le robot poursuit son analyse. Lorsqu’il a terminé son analyse, le robot reprend
	 * son orientation initiale, allume sa DEL d'une couleur ambrée puis se met en attente.
	 *
	 */

	// rend Karl sensible à un interruption personnalisé répondant à un changement
	// de valeur sur la broche du capteur du milieu du capteur de ligne
	PCMSK0 = _BV(PCINT4);
	PCICR = _BV(PCIE0);

	// Effectuons la détections
	char insectes[chemin::MAX_INSECTS];
	uint8_t nbInsectes = detection::commencer(insectes, quartTour);

	// on enlève la sensibilité à l'interruption
	PCMSK0 = 0;
	PCICR = 0;

	/*
	 * 				ATTENTE
	 */

	attendreClic();

	/*
	 * 				RÉCUPÉRATION
	 *
	 * À la sortie de son état d'attente, le robot éteint sa DEL,
	 * ensuite n’effectue rien pendant trois secondes puis poursuit
	 * finalement avec sa procédure de récupération. Il devra alors
	 * visiter chaque point où un poteau a été trouvé. Lorsque son
	 * nez arrive sur un de ces points, le robot s’arrête pendant
	 * trois secondes. Pendant ce délai, il émet un son aigu et sa
	 * DEL s’illumine. Elle devient verte si le point est sur le carré
	 * intérieur, ou rouge s’il est sur le carré extérieur. Après le délai,
	 * le robot passe au point suivant. Lorsqu’il n’y a plus de point à
	 * visiter, le robot reste à l'arrêt et sa DEL prend la couleur ambrée.
	 * Il se met ensuite en attente.
	 *
	 */

	_delay_ms(3000);

	char chemin[chemin::PATH_SIZE];

	chemin::cheapestPath(insectes, nbInsectes);
	chemin::constructPath(insectes, chemin, nbInsectes);

	// assume un orientation arbitraire, fait face aux noeuds "A" et "1"
	uint8_t orientation = 0;
	uint8_t emplacement;

	// consomme le chemin donner et mange les insectes
	for (emplacement = 0; chemin[emplacement + 1] != '\0'; emplacement++) {
		roues::boost();

		deplacement::noeudANoeud(chemin[emplacement], chemin[emplacement + 1], orientation);
		if (deplacement::estInsecte(insectes, nbInsectes, chemin[emplacement + 1])) {
			roues::freiner();
			musique::insecte(chemin::charToIndex(chemin[emplacement + 1]) <= 8);
			deplacement::retirerInsecte(insectes, chemin[emplacement + 1]);
		}
	}

	/*
	 * 				SORTIE
	 *
	 * Le robot doit maintenant se rendre au point de sortie. Pour se faire,
	 * l’évaluateur appuiera sur le bouton Interrupt de la carte mère pour le
	 * faire sortir de son état d'attente. À ce moment, le robot éteint sa DEL,
	 * attend trois secondes à ne rien faire, puis se met à la recherche du point
	 * de sortie. Lorsqu’il arrive à au point de sortie, le robot s’arrête. Une
	 * courte mélodie de quelques secondes doit ensuite être jouée. La mélodie doit
	 * être jouée avec deux instruments en même temps (deux piezos). À l'écoute, il
	 * doit être facile de distinguer les deux instruments.
	 *
	 */

	attendreClic();
	_delay_ms(3000);

	// trouve et construit le chemin vers la sortie la plus proche
	chemin::closestExit(chemin, chemin[emplacement], orientation);

	// se rendre a la sortie la plus proche
	for (emplacement = 0; chemin[emplacement + 1] != '\0'; emplacement++) {
		roues::boost();

		deplacement::noeudANoeud(chemin[emplacement], chemin[emplacement + 1], orientation);
	}

	// si nous ne somme pas déjà à la sortie freiner
	if(chemin[1] != '\0'){
		roues::freiner(deplacement::vitesseNominale);
		_delay_ms(150);
	}

	// partir timer
	TCNT0 = 0;
	OCR0A = 0xFF;
	TIMSK0 = _BV(OCIE0A);
	counter = 0;

	deplacement::suivreLigne(true);

	_delay_ms(150);


	// identifions la sortie
	uint8_t lignes = capteurs::lignes();
	bool bonChemin = false;
	char position = '0';

	if (lignes == 0) {
		if (counter < 100) {
			orientation = 0;
			position = 'A';
		} else {
			bonChemin = true;
		}
	} else if (lignes & 0b1) {
		orientation = 4;
		position = 'C';
		roues::boost();
		_delay_ms(300);
		deplacement::tournerDroite(false, true);

	} else {
		orientation = 4;
		position = 'G';
		roues::boost();
		_delay_ms(300);
		deplacement::tournerGauche(false, true);
	}

	_delay_ms(200);

	// si on est pas à E, aller à E

	if (!bonChemin) {
		insectes[0] = 'E';
		chemin::constructPath(insectes, chemin, 1, position);

		for (emplacement = 0; chemin[emplacement + 1] != '\0'; emplacement++)
			deplacement::noeudANoeud(chemin[emplacement], chemin[emplacement + 1], orientation);

		switch (orientation) {
			case 2:
				deplacement::tournerDroite();
				break;
			case 6:
				deplacement::tournerGauche();
				break;
		}
	}


	// Redondance, car il arrive qu'il s'arrete en
	// plein milieu de la grosse ligne malgré l'anti-rebond..
	deplacement::suivreLigne(true);
	_delay_ms(100);
	deplacement::suivreLigne(true);

	audio::setup();
	roues::arreter();
	musique::fin();

	return 0;
}
