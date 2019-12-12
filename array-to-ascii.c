#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
	if (argc < 2)
	{
		puts("\tusage <path>");
		return 1;
	}

	FILE* textToConvert;
	textToConvert = fopen(argv[1], "r+");
	if (textToConvert == NULL)
	{
		puts("Failed to open file");
		return 2;
	}

	char textFile[100][155];

	int lineCount;
	for (lineCount = 0; lineCount < 100; lineCount++)
	{
		if (fgets(textFile[lineCount], 155, textToConvert) == NULL)
			break;

		if (textFile[lineCount][154] == '\0')
			printf("Possible line too big (more than 154 characters). Line %i\n", lineCount);

		if (lineCount + 1 == 100)
			puts("File bigger than supported, last succeful line: 100");
	}

	fclose(textToConvert);
	textToConvert = fopen(argv[1], "a");

	for (int count = 0; count < 10; count++)
		fprintf(textToConvert, "\n");

	for (int i = 0; i < lineCount + 1; i++)
	{
		if (textFile[i][0] == '\0' || textFile[i][0] == '\n')
		{
			fprintf(textToConvert, "\n");
			continue;
		}

		fprintf(textToConvert, "{");

		for (int j = 0; j < 155; j++)
		{
			if (textFile[i][j] == '\0' || textFile[i][j] == '\n')
				break;

			fprintf(textToConvert, "%c", textFile[i][j]);

			if (textFile[i][j + 1] != '\0' && textFile[i][j + 1] != '\n')
				fprintf(textToConvert, ",");
		}

		fprintf(textToConvert, "},\n");
	}

	puts("Done!");
	getchar();

	return 0;
}