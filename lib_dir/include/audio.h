

#ifndef AUDIO_H
#define AUDIO_H

#include "config.h"
#include "erreur.h"

#include <math.h>

namespace audio {

	const uint8_t NOTE_MIN = 45;
	const uint8_t NOTE_MAX = 81;
	const float FCPU_DIV_2PS = F_CPU / (1024.f * 2);

	const uint8_t PWM_DROITE = _BV(PORTD7); //OC2A
	const uint8_t GROUND_DROITE = _BV(PORTD6);

	const uint8_t PWM_GAUCHE = _BV(PORTB3); //OC0A
	const uint8_t GROUND_GAUCHE = _BV(PORTB2);

	void setup();

	uint16_t calculerFrequence(uint8_t note);
	uint8_t calculerTop(uint8_t note);

	void jouerNote(uint8_t note, Piezo choix = Piezo::deux);
	bool noteEstPossible(uint8_t note);

	void activer(Piezo choix = Piezo::deux);
	void arreter(Piezo choix = Piezo::deux);
}

#endif /* AUDIO_H */
