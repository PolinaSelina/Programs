#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare(const void *str1, const void *str2)
{
	return strcmp(*(const char **)str1, *(const char **)str2);
}

int Error()
{
	fputs("Error", stderr);
      	exit (EXIT_FAILURE);
}
int Fread(size_t result, char * buffer, long lSize, FILE * ptrFile)
{
	result = fread(buffer, sizeof(char), lSize, ptrFile);
	if (result != lSize)
  		Error();
}

int DeclareArrays (int *num, char **s, char *buffer, int lSize, int count)
{
	num = (int*) calloc(sizeof(int), (count+1));
	if (num == NULL)
		Error();
	int j = 1;
	num[0] = -1;
 	for(int i = 0; i < lSize; i++)
		if (buffer[i] == '\n')
		{
			num[j] = i;
			j++;
		}

	for(int i = 0; i < count; i++)
	{
		s[i] = (char*) calloc(sizeof(char), (num[i+1]-num[i]));
		strncpy(s[i], buffer+num[i]+1, num[i+1]-num[i]);
	}

}
void Dump(char **s, int j, FILE * Sorted, int count, char *buffer, int *num)
{
	for (int j = 0; j < count; j++)
	{		
		fwrite(s[j], sizeof(char), strlen(s[j]), Sorted);
		free(s[j]);	
	}	
	free(s);
	free(buffer);
	free(num);
}

int main() 
{
	FILE * ptrFile = fopen ("evgeni.txt", "r");
	FILE * Sorted = fopen ("evgeni_sorted.txt", "w");
	
	if (ptrFile == NULL)
		Error();
	
	fseek(ptrFile, 0, SEEK_END);
	long lSize = ftell(ptrFile);
	rewind (ptrFile);

	char * buffer= (char*) calloc(sizeof(char), lSize);
	if (buffer == NULL)
  		Error();
	
	size_t result;
	Fread(result, buffer, lSize, ptrFile);

	int count = 0;
	for(int i = 0; i < lSize; i++)
	{
		if (buffer[i] == '\n')
			count += 1;
	}
	
	char  **s = (char**) calloc(sizeof(char*), count);
	if (s == NULL)
  		Error();
	
	int *num;
	DeclareArrays(num, s, buffer, lSize, count);
	
	qsort(s, count, sizeof(char*), compare);

	int j;	
	Dump(s, j, Sorted, count, buffer, num);	

	return 0;
}
