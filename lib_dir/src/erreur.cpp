/**************************************************

	Ce fichier s'occupe (si activé) d'arrêter
 	l'exécution du programme et d'afficher une erreur
 	si une condition n'est pas remplie.

**************************************************/

#include "erreur.h"

void assert_expr(bool expression, uint8_t line, const char file[]) {
	if (DEBUG_ENABLE) {
		if (!(expression)) {
			LCD.clear();
			LCD << "L:" << line << ":" << file;

			attendreClic();
		}
	}
}
