#include "swap.h"

void Swap(char *left, char *right)
{
	char box = *left;
	*left = *right;
	*right = box;
}
