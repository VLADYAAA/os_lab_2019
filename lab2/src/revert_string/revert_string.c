#include "revert_string.h"

void RevertString(char *str)
{
	int len = strlen(str);
	char* box = malloc((len + 1) * sizeof(char));
	for(int i = len; i >= 0; i--){
		box[len - i - 1] = str[i];
	}
	for (int i = 0; i < len; i++){
		str[i] = box[i];
	}
	free(box);
}

