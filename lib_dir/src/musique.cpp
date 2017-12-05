/**************************************************

	Ce fichier utilise les fonctionnalité de l'audio
 	pour jouer différentes séquences musicales.

**************************************************/

#include "musique.h"

namespace musique{
	//Musique pour la détection d'insecte, selon s'il est dans le cerlce interieur ou extérieur
	void insecte(bool estInterieur) {
		if (estInterieur) {
			del::vert();
			audio::jouerNote(70, Piezo::droite);
		}
		else{
			del::rouge();
			audio::jouerNote(80, Piezo::droite);
		}

		_delay_ms(3000);

		audio::arreter();
		del::eteindre();
	}

	//Musique finale
	void fin(){
		uint8_t m = 180;
				audio::jouerNote(51, Piezo::gauche);
		audio::jouerNote(75, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(70, Piezo::droite);
		_delay_ms(3*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(72, Piezo::droite);
		_delay_ms(1*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(55, Piezo::gauche);
		audio::jouerNote(74, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(67, Piezo::droite);
		_delay_ms(2*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(67, Piezo::droite);
		_delay_ms(2*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);

				audio::jouerNote(56, Piezo::gauche);
		audio::jouerNote(72, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(70, Piezo::droite);
		_delay_ms(3*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(68, Piezo::droite);
		_delay_ms(1*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(55, Piezo::gauche);
		audio::jouerNote(70, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(63, Piezo::droite);
		_delay_ms(2*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(63, Piezo::droite);
		_delay_ms(2*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);

				audio::jouerNote(53, Piezo::gauche);
		audio::jouerNote(65, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(65, Piezo::droite);
		_delay_ms(3*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(67, Piezo::droite);
		_delay_ms(1*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(51, Piezo::gauche);
		audio::jouerNote(68, Piezo::droite);
		_delay_ms(4*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(68, Piezo::droite);
		_delay_ms(3*m);
		audio::arreter(Piezo::droite);
		_delay_ms(20);
		audio::jouerNote(70, Piezo::droite);
		_delay_ms(1*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);

				audio::jouerNote(51, Piezo::gauche);
		audio::jouerNote(72, Piezo::droite);
		_delay_ms(4*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(50, Piezo::gauche);
		audio::jouerNote(74, Piezo::droite);
		_delay_ms(2*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(48, Piezo::gauche);
		audio::jouerNote(75, Piezo::droite);
		_delay_ms(2*m);
			audio::arreter(Piezo::deux);
			_delay_ms(20);
				audio::jouerNote(46, Piezo::gauche);
		audio::jouerNote(77, Piezo::droite);
				_delay_ms(2*m);
				audio::arreter(Piezo::gauche);
				_delay_ms(20);
				audio::jouerNote(56, Piezo::gauche);
				_delay_ms(2*m);
				audio::arreter(Piezo::gauche);
				_delay_ms(20);
				audio::jouerNote(55, Piezo::gauche);
				_delay_ms(2*m);
				audio::arreter(Piezo::gauche);
				_delay_ms(20);
				audio::jouerNote(53, Piezo::gauche);
				_delay_ms(2*m);
			audio::arreter(Piezo::deux);

	}
}
