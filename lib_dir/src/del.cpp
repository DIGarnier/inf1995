

/**************************************************

	Ce fichier s'occupe de la configuration et
 	de la gestion de la DEL.

**************************************************/

#include"del.h"

namespace del {

	static bool estSetup = false;

	//initialise le portB pour la DEL
	void setup() {
		DDRB |= PS;
		estSetup = true;
		eteindre();
	}
	//Allume la DEL en rouge
	void rouge() {
		assert_expr(estSetup, __LINE__, __FILE__);

		PORTB |= P1;
		PORTB &= ~P2;
	}
	//Allume la DEL en vert
	void vert() {
		assert_expr(estSetup, __LINE__, __FILE__);

		PORTB &= ~P1;
		PORTB |= P2;
	}
	//Allume la DEL en ambré, doit être mis dans une boucle
	void ambre() {
		assert_expr(estSetup, __LINE__, __FILE__);

		vert();
		_delay_us(4000); //Le delais est présent pour une plus belle couleur ambré
		rouge();
		_delay_us(1000);
	}

	//Éteint la DEL
	void eteindre() {
		assert_expr(estSetup, __LINE__, __FILE__);
		PORTB &= ~(P1 | P2);
	}
}
