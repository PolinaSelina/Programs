#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare(const void *str1, const void *str2);
int SizeFile(FILE* ptrFile);
int QuantStr(int lSize, char *buffer);
int Error();
int Fread(size_t result, char * buffer, long lSize, FILE * ptrFile);
void DeclareArrays (int *num, char **s, char *buffer, int lSize, int count);
void Dump(char **s, FILE * Sorted, int count, char *buffer, int *num);
void Free(char **s, char *buffer, int *num);

int main() 
{
	FILE * ptrFile = fopen ("evgeni.txt", "r");
	FILE * Sorted = fopen ("evgeni_sorted.txt", "w");
	
	if (ptrFile == NULL)
		Error();
	
	int lSize = SizeFile(ptrFile);	

	char * buffer= (char*) calloc(sizeof(char), lSize);
	if (buffer == NULL)
  		Error();
	
	size_t result;
	Fread(result, buffer, lSize, ptrFile);

	int count = QuantStr(lSize, buffer);
	
	char  **s = (char**) calloc(sizeof(char*), count);
	if (s == NULL)
  		Error();
	
	int *num = 0;
	DeclareArrays(num, s, buffer, lSize, count);
	
	qsort(s, count, sizeof(char*), compare);

	Dump(s, Sorted, count, buffer, num);	

	Free(s, buffer, num);

	return 0;
}

int compare(const void *str1, const void *str2)
{
	return strcmp(*(const char **)str1, *(const char **)str2);
}

int SizeFile(FILE* ptrFile)
{
	fseek(ptrFile, 0, SEEK_END);
	long lSize = ftell(ptrFile);
	rewind (ptrFile);
	return lSize;
}


int QuantStr(int lSize, char *buffer)
{
	int count = 0;
		for(int i = 0; i < lSize; i++)
		{
			if (buffer[i] == '\n')
				count += 1;
		}
	return count;
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

void DeclareArrays (int *num, char **s, char *buffer, int lSize, int count)
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

void Dump(char **s, FILE * Sorted, int count, char *buffer, int *num)
{
	for (int j = 0; j < count; j++)
	{		
		fwrite(s[j], sizeof(char), strlen(s[j]), Sorted);
		free(s[j]);	
	}	
}

void Free(char **s, char *buffer, int *num)
{
	free(s);
	free(buffer);
	free(num);
}
