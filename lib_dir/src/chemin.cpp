/**************************************************

	Ce fichier s'occupe de construire le chemin le
 	plus court entre plusieurs noeuds (la position
 	des insectes en l'occurence).

**************************************************/

#include "chemin.h"

namespace chemin {

	// Permet de trouver la direction cardinale d'un noeud
	// par rapport à un autre (retourne 0xFF s'il n'est pas
	// un voisin immédiat).
	uint8_t findDirection(char current, char next) {
		for (uint8_t i = 0; i < 8; i++) {
			if (NODES[charToIndex(current)][i] == next)
				return i;
		}

		return 255;
	}

	// Convertit un noeud "caratère" en noeud "entier".
	uint8_t charToIndex(char toConvert) {
		uint8_t resultat = 40; // 'Z'

		if (toConvert >= '0' && toConvert <= '8')
			resultat = toConvert - '0';

		if (toConvert >= 'A' && toConvert <= 'H')
			resultat = 9 + toConvert - 'A';

		switch (toConvert) {
			case ('Q'):
				resultat = 20;
				break;
		}

		return resultat;
	}

	// Convertit un noeud "entier" en noeud "caractère".
	char indexToChar(uint8_t toConvert) {
		char result = 'Z';

		if (toConvert <= 8)
			result = char(toConvert + '0');

		if (toConvert >= 9 && toConvert <= 16)
			result = char(toConvert - 9 + 'A');

		return result;
	}

	// Compare deux caractères et indique lequel vient en premier
	// dans l'ordre alphanumérique.
	int compareStrings(const void *a, const void *b) {
		return (*(char *) a - *(char *) b);
	}

	// Copie une liste d'insecte dans une autre.
	void copyInsect(char (&source)[MAX_INSECTS], char (&destination)[MAX_INSECTS]) {
		for (int i = 0; i < MAX_INSECTS; ++i)
			destination[i] = source[i];
	}

	// Vérifie s'il reste des noeuds non visités.
	bool isEmpty(const bool (&visited)[NB_NODES]) {
		uint8_t size = sizeof(visited) / sizeof(visited[0]);
		for (uint8_t i = 0; i < size; i++) {
			if (!visited[i])
				return false;
		}

		return true;
	}

	// Renvoie le neoud le plus proche non visité.
	uint8_t closestUnvisited(uint8_t (&distance)[NB_NODES], bool (&visited)[NB_NODES]) {
		uint8_t potentialClosest = 0;
		uint8_t smallestDistance = 0xFF;
		uint8_t size = sizeof(distance) / sizeof(distance[0]);

		for (uint8_t i = 0; i < size; i++) {
			if (visited[i])
				continue;

			if (distance[i] < smallestDistance) {
				smallestDistance = distance[i];
				potentialClosest = i;
			}
		}

		return potentialClosest;
	}

	// https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
	// Code traduit depuis du Java

	// Renvoie par référence la prochaine permutation ordonnée (la fonction
	// renvoie false s'il n'en reste plus).
	bool nextPermutation(char (&insects)[MAX_INSECTS], uint8_t elements) {
		int8_t i = elements - 1;

		while (i > 0 && insects[i - 1] >= insects[i])
			i--;

		if (i <= 0)
			return false;

		int8_t j = elements - 1;
		while (insects[j] <= insects[i - 1])
			j--;

		char temp = insects[i - 1];
		insects[i - 1] = insects[j];
		insects[j] = temp;

		j = elements - 1;
		while (i < j) {
			temp = insects[i];
			insects[i] = insects[j];
			insects[j] = temp;
			i++;
			j--;
		}

		return true;
	}

	// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
	// Code traduit depuis du pseudo-code

	// Renvoie la distance la plus courte entre deux noeuds ansi que le chemin
	// pour passer d'un noeud à un autre.
	uint8_t dijkstra(uint8_t (&previous)[NB_NODES], char source, char target) {
		bool visited[NB_NODES];
		uint8_t distance[NB_NODES];
		uint8_t sourceIndex = charToIndex(source);

		for (uint8_t i = 0; i < NB_NODES; i++) {
			distance[i] = 0xFF;
			previous[i] = 40; // 'Z'
			visited[i] = false;
		}

		distance[sourceIndex] = 0;

		while (!isEmpty(visited)) {
			uint8_t closest = closestUnvisited(distance, visited);
			visited[closest] = true;

			if (target != 'Z' && closest == charToIndex(target))
				return distance[charToIndex(target)];

			for (uint8_t i = 0; i < 8; i++) {
				const char &neighbor = NODES[closest][i];
				uint8_t neighborIndex = charToIndex(neighbor);

				if (neighbor == 'Z' || visited[neighborIndex])
					continue;

				uint16_t alternative = distance[closest] + COSTS[closest][i];

				if (alternative < distance[neighborIndex]) {
					// cette opération est safe, car on ne va jamais
					// dépasser 255 si on rentre dans cette condition
					distance[neighborIndex] = uint8_t(alternative);
					previous[neighborIndex] = closest;
				}
			}
		}

		if (target != 'Z')
			return distance[charToIndex(target)];
		else
			return 0xFF;
	}

	// Renvoie le chemin la permutation d'insectes la moins couteuse.
	void cheapestPath(char (&insects)[MAX_INSECTS], uint8_t elements) {

		char bestInsects[MAX_INSECTS];
		uint8_t previous[NB_NODES];
		uint8_t bestCost = 0xFF;

		qsort(insects, elements, sizeof(char), compareStrings);

		do {
			uint8_t bufferCost = 0;

			for (uint8_t j = 0; j < elements; ++j) {
				if (j == 0)
					bufferCost += dijkstra(previous, '0', insects[j]);
				else
					bufferCost += dijkstra(previous, insects[j - 1], insects[j]);
			}

			if (bufferCost < bestCost) {
				copyInsect(insects, bestInsects);
				bestCost = bufferCost;
			}

		} while (nextPermutation(insects, elements));

		copyInsect(bestInsects, insects);
	}

	// Renvoie le chemin le plus court entre 0 à 5 insectes.
	void constructPath(char (&insects)[MAX_INSECTS],
					   char (&path)[PATH_SIZE],
					   uint8_t nbElement,
					   char startingPosition) {

		uint8_t indexPath = 0;
		uint8_t previous[NB_NODES];

		path[indexPath++] = startingPosition;

		for (uint8_t i = 0; i < nbElement; i++) {
			char source;
			char target;

			if (i > 0) {
				source = insects[i];
				target = insects[i - 1];
			} else {
				source = insects[0];
				target = startingPosition;
			}

			dijkstra(previous, source, target);

			uint8_t previousIndex = charToIndex(target);

			while (previous[previousIndex] != charToIndex('Z')) {
				path[indexPath++] = indexToChar(previous[previousIndex]);
				previousIndex = previous[previousIndex];
			}
		}

		path[indexPath] = '\0';
	}

	// Renvoie le chemin vers la sortie la plus proche.
	void closestExit(char (&path)[PATH_SIZE], char currentPosition, uint8_t orientation) {

		uint8_t bestCost = 0xFF;
		uint8_t bestExit = 9;
		uint8_t previous[NB_NODES];

		uint8_t nbNoeuds = 0;


		for (uint8_t sortie = 9; sortie < NB_NODES; sortie += 2) {

			uint8_t cost = dijkstra(previous, currentPosition, indexToChar(sortie));
			if (bestCost > cost) {
				bestCost = cost;
				bestExit = sortie;
			}

		}

		char nodesToVisit[MAX_INSECTS];

		char potentialExit = NODES[charToIndex(currentPosition)][orientation];

		if (charToIndex(currentPosition) > 8 && potentialExit != 'Q') {

			nodesToVisit[nbNoeuds++] = indexToChar(charToIndex(currentPosition) - 8);

		}

		nodesToVisit[nbNoeuds++] = indexToChar(bestExit);

		constructPath(nodesToVisit, path, nbNoeuds, currentPosition);


	}

}
