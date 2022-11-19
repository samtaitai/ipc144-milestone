#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "core.h"


// As demonstrated in the course notes: 
// https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
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

//1.pass
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

//2.pass
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

//3.pass
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
			printf("ERROR! Value must be between %d and %d inclusive: ", MIN, MAX);
		}
	}

	return result;
};

//4.pass
char inputCharOption(const char	validChar[VALIDCHAR+1])
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
			printf("ERROR: Character must be one of [qwErty]: ");
		}
	}
	

	return result;

}; 


//5.
void inputCString(char givenStr[], int minLen, int maxLen)
{
	//clearInputBuffer(); // avoid skip 1st input -> cause ask \n twice in the 2nd test
	while ((getchar()) == '\n') // fix above? erase previous remaining new line..? 
	{
	};

	int lenCounter = 0;
	int flag = 1;
	int i;
	char tempStr[512] = { 0 };
	
	while (flag)
	{
		lenCounter = 0;
		scanf("%[^\n]s", tempStr); // get whitespace as well
		clearInputBuffer(); // avoid eternal loop

		
		for (i = 0; tempStr[i] != 0; i++);
		{
			lenCounter = i;
		}

		// exact length finder
		if (minLen == maxLen)
		{
			if (lenCounter == minLen && lenCounter == maxLen)
			{

				sprintf(givenStr, "%s", tempStr); // copy without strcpy
				flag = 0;
			}
			else
			{
				printf("ERROR: String length must be exactly 6 chars: ");

			}
		}
		else
		{
			if (lenCounter > maxLen)
			{
				printf("ERROR: String length must be no more than 6 chars: ");
			}
			else if (lenCounter < minLen)
			{
				printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);

			}
			else
			{
				sprintf(givenStr, "%s", tempStr);
				flag = 0;
			}
		}
		
	}

};

//6.
void displayFormattedPhone(const char phoneNum[])
{
	int counter = 0;
	int i;
	int toInt = 0;

	if (phoneNum != NULL)
	{
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
