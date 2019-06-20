#include "Structs.h"

BitStream *newBitStream() {
	BitStream *tmp = (BitStream*)malloc(sizeof(BitStream));
	tmp->byte = 0;
	tmp->size = 0;
	return tmp;
}
