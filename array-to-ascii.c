#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv)
{
	// if no files where passed by argument
	if (argc < 2)
	{
		puts("\tusage <path>");
		return 1;
	}

	// opening file
	FILE* textToConvert;
	textToConvert = fopen(argv[1], "r+");
	if (textToConvert == NULL)
	{
		puts("Failed to open file");
		return 2;
	}

	// used to store the textFile
	// To Do: use malloc()
	char textFile[100][155];

	// stores the text file in the array
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

	// close the file and opens again at the end
	fclose(textToConvert);
	textToConvert = fopen(argv[1], "a");

	// print 10 new line
	for (int count = 0; count < 10; count++)
		fprintf(textToConvert, "\n");
	
	// the program itself
	for (int i = 0; i < lineCount + 1; i++)
	{
		// if there's no character in the line, print a enter and goes to the next line
		if (textFile[i][0] == '\0' || textFile[i][0] == '\n')
		{
			fprintf(textToConvert, "\n");
			continue;
		}

		if (i > 0)
		{
			if (textFile[i - 1][0] == '\n' && (textFile[i][0] != '\n' && textFile[i][0] != '\0'))
				fprintf(textToConvert, "{ ");
		}

		if (i == 0 && textFile[i][0] != '\0' && textFile[i][0] != '\n')
			fprintf(textToConvert, "{ ");


		fprintf(textToConvert, "{");

		for (int j = 0; j < 155; j++)
		{
			if (textFile[i][j] == '\0' || textFile[i][j] == '\n')
				break;

			fprintf(textToConvert, "'%c'", textFile[i][j]);

			if (textFile[i][j + 1] != '\0' && textFile[i][j + 1] != '\n')
				fprintf(textToConvert, ", ");
		}

		if (i + 1 < lineCount + 1)
		{
			if (textFile[i + 1][0] == '\0' || textFile[i + 1][0] == '\n')
				fprintf(textToConvert, "} }\n");

			else
				fprintf(textToConvert, "},\n");
		}
		
		else
			fprintf(textToConvert, "},\n");
	}

	puts("Done!");
	getchar();

	return 0;
}