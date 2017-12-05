/**************************************************

	Ce fichier s'occupe de la configuration et
 	de la gestion des deux piezos.

**************************************************/

#include "audio.h"

namespace audio {

	bool estSetup = false;

	//initialise les piezos
	void setup() {

		// Piezo de droite
		DDRD |= PWM_DROITE | GROUND_DROITE;
		PORTD &= ~GROUND_DROITE;
		TCCR2A = _BV(WGM21);
		TCCR2B = TIMER2_PRESCALER_1024;

		// Piezo de gauche
		DDRB |= PWM_GAUCHE | GROUND_GAUCHE;
		PORTB &= ~GROUND_GAUCHE;
		TCCR0A = _BV(WGM01);
		TCCR0B = TIMER0_PRESCALER_1024;

		estSetup = true;
		arreter();
	}

	//Calcule la fréquence selon la note MIDI
	uint16_t calculerFrequence(uint8_t note) {
		uint16_t reference = 440;
		float exposant = (note - 69) / 12.0f;
		uint16_t frequence = uint16_t(pow(2.0f, exposant) * reference + 0.5f);
		return frequence;
	}

	//Calcul la valeur de comparaison pour obtenir la fréquence
	uint8_t calculerTop(uint8_t note) {
		uint16_t frequence = calculerFrequence(note);
		float top = FCPU_DIV_2PS / frequence + 0.5f;
		return uint8_t(top - 1);
	}
	
	//Active le piezo voulu avec la note voulu
	void jouerNote(uint8_t note, Piezo choix) {
		assert_expr(estSetup, __LINE__, __FILE__);

		if (!noteEstPossible(note))
			return;

		switch (choix) {
			case Piezo::droite :
				activer(choix);
				TCNT2 = 0;
				OCR2A = calculerTop(note);
				break;
			case Piezo::gauche :
				activer(choix);
				TCNT0 = 0;
				OCR0A = calculerTop(note);
				break;
			case Piezo::deux :
				jouerNote(note, Piezo::droite);
				jouerNote(note, Piezo::gauche);
				break;
		}
	}

	//Active les piezo pour qu'il puisse émettre un son
	void activer(Piezo choix) {

		switch (choix) {
			case Piezo::droite :
				TCCR2A |= _BV(COM2A0);
				TCCR2A &= ~(_BV(COM2A1));
				break;
			case Piezo::gauche :
				TCCR0A |= _BV(COM0A0);
				TCCR0A &= ~(_BV(COM0A1));
				break;
			case Piezo::deux :
				activer(Piezo::droite);
				activer(Piezo::gauche);
				break;
		}
	}

	//arrête les piezo d'émettre du son
	void arreter(Piezo choix) {

		switch (choix) {
			case Piezo::droite :
				TCCR2A &= ~(_BV(COM2A0));
				TCCR2A &= ~(_BV(COM2A1));
				TCNT2 = 0;
				OCR2A = 0;
				break;
			case Piezo::gauche :
				TCCR0A &= ~(_BV(COM0A0));
				TCCR0A &= ~(_BV(COM0A1));
				TCNT0 = 0;
				OCR0A = 0;
				break;
			case Piezo::deux :
				arreter(Piezo::droite);
				arreter(Piezo::gauche);
				break;
		}
	}

	//Vérifie si la note demandé est possible sur le piezo
	bool noteEstPossible(uint8_t note) {
		return (note >= NOTE_MIN && note <= NOTE_MAX);
	}
}
