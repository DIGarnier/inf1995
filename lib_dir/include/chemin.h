
#ifndef PATH_H
#define PATH_H

#include "config.h"
#include <stdlib.h>

namespace chemin {

	const char NODES[][8] = {{'1', 'Z', '3', 'Z', '5', 'Z', '7', 'Z'},  // Origine
							 {'A', 'Z', '2', 'Z', '0', 'Z', '8', 'Z'},  // 1
							 {'Z', 'B', 'Z', 'Z', '3', 'Z', '1', 'Z'},  // 2
							 {'2', 'Z', 'C', 'Z', '4', 'Z', '0', 'Z'},  // 3
							 {'3', 'Z', 'Z', 'D', 'Z', 'Z', '5', 'Z'},  // 4
							 {'0', 'Z', '4', 'Z', 'E', 'Z', '6', 'Z'},  // 5
							 {'7', 'Z', '5', 'Z', 'Z', 'F', 'Z', 'Z'},  // 6
							 {'8', 'Z', '0', 'Z', '6', 'Z', 'G', 'Z'},  // 7
							 {'Z', 'Z', '1', 'Z', '7', 'Z', 'Z', 'H'},  // 8
							 {'Q', 'Z', 'B', 'Z', '1', 'Z', 'H', 'Z'},  // A
							 {'Z', 'Z', 'Z', 'Z', 'C', '2', 'A', 'Z'},  // B
							 {'B', 'Z', 'Q', 'Z', 'D', 'Z', '3', 'Z'},  // C
							 {'C', 'Z', 'Z', 'Z', 'Z', 'Z', 'E', '4'},  // D
							 {'5', 'Z', 'D', 'Z', 'Q', 'Z', 'F', 'Z'},  // E
							 {'G', '6', 'E', 'Z', 'Z', 'Z', 'Z', 'Z'},  // F
							 {'H', 'Z', '7', 'Z', 'F', 'Z', 'Q', 'Z'},  // G
							 {'Z', 'Z', 'A', '8', 'G', 'Z', 'Z', 'Z'}}; // H

	const uint8_t COSTS[][8] = {{5,   255, 5,   255, 5,   255, 5,   255},    // Origine
								{5,   255, 5,   255, 5,   255, 5,   255},    // 1
								{255, 7,   255, 255, 5,   255, 5,   255},    // 2
								{5,   255, 5,   255, 5,   255, 5,   255},    // 3
								{5,   255, 255, 7,   255, 255, 5,   255},    // 4
								{5,   255, 5,   255, 5,   255, 5,   255},    // 5
								{5,   255, 5,   255, 255, 7,   255, 255},    // 6
								{5,   255, 5,   255, 5,   255, 5,   255},    // 7
								{255, 255, 5,   255, 5,   255, 255, 7},    	 // 8
								{5,   255, 10,  255, 5,   255, 10,  255},    // A
								{255, 255, 255, 255, 10,  7,   10,  255},    // B
								{10,  255, 5,   255, 10,  255, 5,   255},    // C
								{10,  255, 255, 255, 255, 255, 10,  7},    	 // D
								{5,   255, 10,  255, 5,   255, 10,  255},    // E
								{10,  7,   10,  255, 255, 255, 255, 255},    // F
								{10,  255, 5,   255, 10,  255, 5,   255},    // G
								{255, 255, 10,  7,   10,  255, 255, 255}};   // H

	constexpr uint8_t NB_NODES = sizeof(NODES) / sizeof(NODES[0]);
	const uint8_t MAX_INSECTS = 5;
	const uint8_t PATH_SIZE = 20;

	uint8_t findDirection(char current, char next);

	uint8_t charToIndex(char toConvert);

	char indexToChar(uint8_t toConvert);

	int compareStrings(const void *a, const void *b);

	void copyInsect(char (&source)[MAX_INSECTS], char (&destination)[MAX_INSECTS]);

	bool isEmpty(const bool (&visited)[NB_NODES]);

	uint8_t closestUnvisited(uint8_t (&distance)[NB_NODES], bool (&visited)[NB_NODES]);

	bool nextPermutation(char (&insects)[MAX_INSECTS], uint8_t elements);

	uint8_t dijkstra(uint8_t (&previous)[NB_NODES], char source, char target = 'Z');

	void cheapestPath(char (&insects)[MAX_INSECTS], uint8_t elements);

	void constructPath(char (&insects)[MAX_INSECTS], char (&path)[PATH_SIZE], uint8_t nbElement,
					   char startingPosition = '0');

	void closestExit(char (&path)[PATH_SIZE], char currentPosition, uint8_t orientation);

}

#endif /* PATH_H */
