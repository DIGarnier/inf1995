/**************************************************

	Ce fichier s'occupe de la configuration et
 	de la gestion des roues.

**************************************************/

#include "roues.h"

namespace roues {

	// nous dit si on a fait l'initialisation
	static bool estSetup = false;

	// fonction d'initialisation
	// s'occupe de mettre les bonnes valeurs dans les bons registres
	void setup() {
		DDRD |= PWM_D | PWM_G | SENS_D | SENS_G;
		PORTD |= SENS_D | SENS_G;

		TCNT1 = 0;
		TCCR1A = _BV(WGM10);
		TCCR1A |= _BV(COM1A1) | _BV(COM1B1);
		TCCR1B = TIMER1_PRESCALER_64;
		TCCR1C = 0;
		OCR1A = 0;
		OCR1B = 0;

		estSetup = true;
	}

	// change la vitesse de la roue gauche
	void vitesseGauche(uint8_t ratio) {
		assert_expr(estSetup, __LINE__, __FILE__);

		OCR1B = ratio;
	}

	// change la vitesse de la roue droite
	void vitesseDroite(uint8_t ratio) {
		assert_expr(estSetup, __LINE__, __FILE__);

		OCR1A = ratio;
	}

	// change la direction de la roue gauche
	// vrai = avance, faux = recule
	void directionGauche(bool avance) {
		assert_expr(estSetup, __LINE__, __FILE__);

		if (avance)
			PORTD |= SENS_G;
		else
			PORTD &= ~SENS_G;
	}

	// change la direction de la roue droite
	// vrai = avance, faux = recule
	void directionDroite(bool avance) {
		assert_expr(estSetup, __LINE__, __FILE__);

		if (avance)
			PORTD |= SENS_D;
		else
			PORTD &= ~SENS_D;
	}

	// tourner a gauche sur soi-meme avec une vitesse en entree
	void tournerGauche(uint8_t ratio) {
		directionDroite(true);
		directionGauche(false);
		vitesseDroite(ratio);
		vitesseGauche(ratio);
	}

	// une poussée initiale pour les moteurs
	void kickDroit() {
		tournerDroite(0xff);
		_delay_ms(25);
	}

	// tourner a droite sur soi-meme avec une vitesse en entree
	void tournerDroite(uint8_t ratio) {
		directionDroite(false);
		directionGauche(true);
		vitesseDroite(ratio);
		vitesseGauche(ratio);
	}

	// imobilise le robot
	void arreter() {
		vitesseDroite(0);
		vitesseGauche(0);
	}

	// fait reculer le robot avec une vitesse ratio
	void reculer(uint8_t ratio) {
		directionDeuxRoues(false);
		vitesseGauche(ratio);
		vitesseDroite(ratio);
	}

	// fait avance le robot avec une vitesse ratio
	void avancer(uint8_t ratio) {
		directionDeuxRoues(true);
		vitesseGauche(ratio);
		vitesseDroite(ratio);
	}

	// inverse la direction des deux roues
	void inverserDirections() {
		// extrait la valeur directement a partir du registre PIND
		directionDroite(!(PIND & SENS_D));
		directionGauche(!(PIND & SENS_G));
	}

	// change la direction pour les deux roues pour les mettre dans le meme
	// direction. vrai = avancer, false = reculer
	void directionDeuxRoues(bool avancer) {
		directionGauche(avancer);
		directionDroite(avancer);
	}

	// fait freiner le robot inversant sa direction et faisant marcher
	// les roues avec une petites impulsions
	void freiner(uint8_t vitesse) {
		vitesseDroite(vitesse);
		vitesseGauche(vitesse);

		inverserDirections();
		_delay_ms(150);
		arreter();
		inverserDirections();
	}

	// remet le timer1 a 0
	void clearTimer() {
		TCNT1 = 0;
	}

	// donne une petite poussée vers l'avant au robot
	void boost() {
		roues::avancer(0xFF);
		_delay_ms(200);
		roues::arreter();
		_delay_ms(100);
	}
}
