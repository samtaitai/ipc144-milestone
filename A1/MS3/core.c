/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : So Yon Lee
Student ID#: 179142211
Email      : slee550@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "core.h"
#include "clinic.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

//Validate if it's int
int inputInt(void)
{
	int intInput = 0, result = 0, flag = 1;
	char newLine = 0;

	while (flag)
	{
		scanf("%d%c", &intInput, &newLine);
		if (newLine == 10) //because new line ascii code is 10 
		{
			result = intInput;
			flag = 0;
		}
		else
		{
			printf("Error! Input a whole number: ");
			clearInputBuffer();
		}
	}

	return result;
};

//Validate if it's positive int
int inputIntPositive(void)
{
	int intInput = 0, result = 0, flag = 1;

	while (flag)
	{
		scanf("%d", &intInput);
		if (intInput > 0)
		{
			result = intInput;
			flag = 0;
		}
		else
		{
			printf("ERROR! Value must be > 0: ");
		}
	}

	return result;
};

//Validate if int is between min and max
int inputIntRange(int min, int max)
{
	int result = 0, flag = 1;

	while (flag)
	{
		result = inputInt();

		if (result >= min && result <= max)
		{
			flag = 0;
		}
		else
		{
			printf("ERROR! Value must be between %d and %d inclusive: ", min, max);
		}
	}

	return result;
};

//Validate char input
char inputCharOption(const char	validChar[VALIDCHAR + 1])
{
	char inputChar = 0, result = 0;
	int isIncluded = 0, flag = 1;
	int i;

	while (flag)
	{
		scanf(" %c", &inputChar);

		for (i = 0; i < VALIDCHAR + 1; i++)
		{
			if (inputChar == validChar[i])
			{
				isIncluded = 1;
			}
		}

		if (isIncluded == 1)
		{
			result = inputChar;
			flag = 0;
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", validChar);
		}
	}


	return result;

};

//Validate string input
void inputCString(char givenStr[], int minLen, int maxLen)
{
	int lenCounter = 0;
	int flag = 1;
	char tempStr[512] = { 0 };

	while (flag)
	{
		lenCounter = 0;
		scanf("%[^\n]s", tempStr); // get whitespace as well
		clearInputBuffer(); // avoid eternal loop

		lenCounter = strlen(tempStr);

		// exact length finder
		if (minLen == maxLen)
		{
			if (lenCounter == minLen && lenCounter == maxLen)
			{
				givenStr = strcpy(givenStr, tempStr);
				flag = 0;
			}
			else
			{
				//printf("ERROR: String length must be exactly %d chars: ", minLen);
				printf("Invalid %d-digit number! Number: ", minLen);
			}
		}
		else
		{
			if (lenCounter > maxLen)
			{
				printf("ERROR: String length must be no more than %d chars: ", maxLen);
			}
			else if (lenCounter < minLen)
			{
				printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);

			}
			else
			{
				givenStr = strcpy(givenStr, tempStr);
				flag = 0;
			}
		}

	}

};

//Validate phone number 
void displayFormattedPhone(const char phoneNum[])
{
	int counter = 0;
	int i;
	int toInt = 0;

	if (phoneNum != NULL)
	{
		//every char is digit? 
		for (i = 0; phoneNum[i] != '\0'; i++)
		{
			toInt = (int)phoneNum[i];

			if (toInt >= 48 && toInt <= 57) //char should be 0 to 9  
			{
				counter += 1;
			}
			else
			{
				counter = counter;
			}
		}
		if (counter == 10)
		{
			printf("(");
			for (i = 0; i < 3; i++)
			{
				printf("%c", phoneNum[i]);
			}
			printf(")");
			for (i = 3; i < 6; i++)
			{
				printf("%c", phoneNum[i]);
			}
			printf("-");
			for (i = 6; i < 10; i++)
			{
				printf("%c", phoneNum[i]);
			}
		}
		else
		{
			printf("(___)___-____");
		}
	}
	else
	{
		printf("(___)___-____");
	}
};
