#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


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
	FILE* textFile;
	textFile = fopen(argv[1], "r+");
	if (textFile == NULL)
	{
		puts("Failed to open file");
		return 2;
	}

	// set the program mode
	char* prompt = malloc(3 * sizeof(char));
	if (argc == 3 && (argv[2][0] == '1' || argv[2][0] == '0'))
	{
		mode = argv[2][0] - '0';
	}

	else
	{
		puts("Which mode:\n1- array initialization. E.g.: {'E', 'x'}\n2- individual array assignament. E.g.: array_0[0][0] = 'E';");
		fgets(prompt, 3, stdin);
		if (prompt[0] == '2' || prompt[0] == '1')
			mode = prompt[0] - '1';
	}
	free(prompt);

	// creates the variable to store the text file
	// and stores it
	size_t* fileSize = malloc(sizeof(size_t));
	fseek(textFile, 0L, SEEK_END);
	*fileSize = ftell(textFile);
	fseek(textFile, 0L, SEEK_SET);

	char* textToConvert = malloc(*fileSize);
	//fgets(textToConvert, fileSize + 1, textFile);

	size_t* cursor = malloc(sizeof(size_t));

	*fileSize = 0;
	do
	{
		textToConvert[*fileSize] = fgetc(textFile);
		(*fileSize)++;
	} while (textToConvert[(*fileSize) - 1] != EOF);

	(*fileSize) -= 1;
	textToConvert[*fileSize] = '\0';

	fseek(textFile, 0L, SEEK_END);	

	// print 10 new line
	for (int count = 0; count < 10; count++)
		fprintf(textFile, "\n");
	
	// the program itself

	if (mode == 0)
	{
		for (size_t count = 0; count < *fileSize + 1; count++)
		{
			// if there's no character in the line, print a enter and goes to the next line
			if (textToConvert[count] == '\0' || textToConvert[count] == '\n')
			{
				fprintf(textFile, "\n");
				continue;
			}

			// looks if there's a empty line before a non-empty line to put a open bracket
			if (count > 0)
			{
				if (textToConvert[count - 1] == '\n' && (textToConvert[count] != '\n' && textToConvert[count] != '\0'))
					fprintf(textFile, "{ ");
			}

			// if the file doesn't start with an empy line, put the open bracket
			if (count == 0 && textToConvert[count] != '\0' && textToConvert[count] != '\n')
				fprintf(textFile, "{ ");

			// print the line bracket
			fprintf(textFile, "{");

			// the algorithm. It'll get a string and trasnform in a "initializable string"
			// putting the ' before and after the character, spliting the caracter with commas
			// something like "Example" to "'E', 'x', 'a', 'm', 'p', 'l', 'e'"
			for (; count < *fileSize; count++)
			{
				// if the line is empty, go to the next
				if (textToConvert[count] == '\0' || textToConvert[count] == '\n')
					break;

				// if th echaracter is a backslash or a quote, put a backslash before it
				if (textToConvert[count] == '\\' || textToConvert[count] == '\"')
					fprintf(textFile, "'\\%c'", textToConvert[count]);

				// prints the character betwen '
				else
					fprintf(textFile, "'%c'", textToConvert[count]);

				// if the next line isn't empty, print the comma
				if (textToConvert[count + 1] != '\0' && textToConvert[count + 1] != '\n')
					fprintf(textFile, ", ");
			}

			// looks if the lineCount won't be surpassed, so 
			// the next instructions can be done safely
			if (count + 1 < *fileSize + 2)
			{
				// if the next line is empty, prints the close bracket of the line bracket 
				// and the close bracket from the array initializer
				if (textToConvert[count + 1] == '\0' || textToConvert[count + 1] == '\n')
					fprintf(textFile, "} }\n");

				// else, print the close bracket of the line and a comma
				else
					fprintf(textFile, "},\n");
			}

			// else, we're in the end of the file, just
			// print the end brackets
			else
				fprintf(textFile, "} }\n");
		}
	}

	if (mode == 1)
	{
		// using size_t because it can hold the maximum value (32/64 bits)
		size_t arrayCounter = 0;
		size_t lineCounter = 0;
		for (size_t count = 0; count < *fileSize + 1; count++)
		{
			// if there's no character in the line, print a enter and goes to the next line
			if (textToConvert[count] == '\0' || textToConvert[count] == '\n')
			{
				fprintf(textFile, "\n");
				lineCounter++;
				continue;
			}

			// will update the array index, so the number in array_x updates
			if (count > 1)
			{
				if (textToConvert[count - 1] == '\n' && textToConvert[count - 2] == '\n' && textToConvert[count] != '\n' && textToConvert[count] != '\0')
					arrayCounter++;
			}

			// the algorithm. It'll get a string and trasnform in a "initializable string"
			// putting the ' before and after the character, spliting the caracter with commas
			// something like "E" to array_0[0][0] = 'E';
			for (; count < *fileSize + 1; count++)
			{
				// if the end of the line was reached, get out of the loop
				if (textToConvert[count] == '\0' || textToConvert[count] == '\n') 
					break;

				// prints the satrt of the assignment
				fprintf(textFile, "array_%i[%i][%i] = ", arrayCounter, lineCounter, count);

				// if th echaracter is a backslash or a quote, put a backslash before it
				if (textToConvert[count] == '\\' || textToConvert[count] == '\"')
					fprintf(textFile, "'\\%c'", textToConvert[count]);

				// prints the character betwen '
				else
					fprintf(textFile, "'%c'", textToConvert[count]);

					fprintf(textFile, ";\n");
			}

			lineCounter++;
		}
	}

	free(fileSize);
	fclose(textFile);
	puts("Done!");
	fgets(textToConvert, 5, stdin); // freezes the execution so the console window doens't close
	free(textToConvert);

	return 0;
}