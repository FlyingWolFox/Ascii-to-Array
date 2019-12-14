#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main(int argc, char** argv)
{
	// work mode
	// 0 -> arrray initialization. Ex: {'E', 'x'}
	// 1 -> individual array assignament. Ex: array_0 [0][0] = 'E'; 
	int mode = 0;

	// if no files where passed by argument
	if (argc < 2)
	{
		puts("\tusage <path> <mode>\n\tif the last argument is ommited, there'll be a prompt on execution");
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

	// set the program mode

	if (argc == 3 && (argv[2][0] == '1' || argv[2][0] == '0'))
	{
		mode = argv[2][0] - '0';
	}

	else
	{
		puts("Which mode:\n1- arrray initialization. Ex: {'E', 'x'}\n2- individual array assignament. Ex: array_0[0][0] = 'E';");
		fgets(textFile[0], 5, stdin);
		if (textFile[0][0] == '2' || textFile[0][0] == '1')
			mode = textFile[0][0] - '1';
	}

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

	if (mode == 0)
	{
		for (int i = 0; i < lineCount + 1; i++)
		{
			// if there's no character in the line, print a enter and goes to the next line
			if (textFile[i][0] == '\0' || textFile[i][0] == '\n')
			{
				fprintf(textToConvert, "\n");
				continue;
			}

			// looks if there's a empty line before a non-empty line to put a open bracket
			if (i > 0)
			{
				if (textFile[i - 1][0] == '\n' && (textFile[i][0] != '\n' && textFile[i][0] != '\0'))
					fprintf(textToConvert, "{ ");
			}

			// if the file doesn't start with an empy line, put the open bracket
			if (i == 0 && textFile[i][0] != '\0' && textFile[i][0] != '\n')
				fprintf(textToConvert, "{ ");

			// print the line bracket
			fprintf(textToConvert, "{");

			// the algorithm. It'll get a string and trasnform in a "initializable string"
			// putting the ' before and after the character, spliting the caracter with commas
			// something like "Example" to "'E', 'x', 'a', 'm', 'p', 'l', 'e'"
			for (int j = 0; j < 155; j++)
			{
				// if the line is empty, go to the next
				if (textFile[i][j] == '\0' || textFile[i][j] == '\n')
					break;

				// if th echaracter is a backslash or a quote, put a backslash before it
				if (textFile[i][j] == '\\' || textFile[i][j] == '\"')
					fprintf(textToConvert, "'\\%c'", textFile[i][j]);

				// prints the character betwen '
				else
					fprintf(textToConvert, "'%c'", textFile[i][j]);

				// if the next line isn't empty, print the comma
				if (textFile[i][j + 1] != '\0' && textFile[i][j + 1] != '\n')
					fprintf(textToConvert, ", ");
			}

			// looks if the lineCount won't be surpassed, so 
			// the next instructions can be done safely
			if (i + 1 < lineCount + 1)
			{
				// if the next line is empty, prints the close bracket of the line bracket 
				// and the close bracket from the array initializer
				if (textFile[i + 1][0] == '\0' || textFile[i + 1][0] == '\n')
					fprintf(textToConvert, "} }\n");

				// else, print the close bracket of the line and a comma
				else
					fprintf(textToConvert, "},\n");
			}

			// else, we're in the end of the file, just
			// print the end brackets
			else
				fprintf(textToConvert, "} }\n");
		}
	}

	if (mode == 1)
	{
		int arrayCounter = 0;
		for (int i = 0; i < lineCount + 1; i++)
		{
			// if there's no character in the line, print a enter and goes to the next line
			if (textFile[i][0] == '\0' || textFile[i][0] == '\n')
			{
				fprintf(textToConvert, "\n");
				continue;
			}

			// will update the array index, so the number in array_x updates
			if (i > 0)
			{
				if (textFile[i - 1][0] == '\n' && textFile[i][0] != '\n' && textFile[i][0] != '\0')
					arrayCounter++;
			}

			// the algorithm. It'll get a string and trasnform in a "initializable string"
			// putting the ' before and after the character, spliting the caracter with commas
			// something like "E" to array_0[0][0] = 'E';
			for (int j = 0; j < 155; j++)
			{
				// if the end of the line was reached, get out of the loop
				if (textFile[i][j] == '\0' || textFile[i][j] == '\n') 
					break;

				// prints the satrt of the assignment
				fprintf(textToConvert, "array_%i[%i][%i] = ", arrayCounter, i, j);

				// if th echaracter is a backslash or a quote, put a backslash before it
				if (textFile[i][j] == '\\' || textFile[i][j] == '\"')
					fprintf(textToConvert, "'\\%c'", textFile[i][j]);

				// prints the character betwen '
				else
					fprintf(textToConvert, "'%c'", textFile[i][j]);

					fprintf(textToConvert, ";\n");
			}
		}
	}

	puts("Done!");
	fgets(textFile[99], 5, stdin); // freezes the execution so the console window doens't close

	return 0;
}