

#ifndef ERREUR_H
#define ERREUR_H

#include "lcd.h"
#include "bouton.h"

#define DEBUG_ENABLE 0

void assert_expr(bool expression, uint8_t line, const char file[]);

#endif /* ERREUR_H */
