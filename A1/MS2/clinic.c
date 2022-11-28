/*
*****************************************************************************
                        Assignment 1 - Milestone 2
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

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else if (fmt == FMT_TABLE)
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayPatientTableHeader();
            displayAllPatients(patient, max, FMT_TABLE); // add &? Nope
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (0%4d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int isEmpty = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            isEmpty += 1;
        }
    }
    if (isEmpty == max)
    {
        puts("*** No records found ***");

    }
    else
    {
        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber == 0)
            {
                // printf(""); do nothing 
            }
            else
            {
                displayPatientData(&patient[i], fmt);
            }
        }
    }

    
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection = 0;
    int flag = 1;

    while (flag)
    {
        //printf("\n");
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selection);
        clearInputBuffer();
        if (selection == 1)
        {
            printf("\n");
            searchPatientByPatientNumber(patient, max);
            printf("\n");
            suspend();
        }
        else if (selection == 2)
        {
            printf("\n");
            searchPatientByPhoneNumber(patient, max);
            printf("\n");
            suspend();

        }
        else if (selection == 0)
        {
            flag = 0;
        }
    }
    printf("\n");

}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) 
{
    int isRoom = 0;
    int freeIdx = 0;
    int i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            isRoom = 1; // yes one is empaty at least
        }
    }

    if (isRoom != 0)
    {
        for (i = 0; i < max && patient[i].patientNumber != 0; i++)
        {
            freeIdx = i + 1;
        }

        patient[freeIdx].patientNumber = nextPatientNumber(patient, max); //nextPatientNumber() is working 
        inputPatient(&patient[freeIdx]); // inputPatient(inputPhoneData) 
        printf("\n");
        printf("*** New patient record added ***");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!");

    }
    printf("\n");
    printf("\n");

}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int intInput = 0;
    int isFound = 0;

    printf("Enter the patient number: ");
    scanf("%d", &intInput);
    clearInputBuffer();
    isFound = findPatientIndexByPatientNum(intInput, patient, max); // 3 

    if (isFound != -1) // -1 is not found
    {
        printf("\n");
        menuPatientEdit(&patient[isFound]);
    }
    else
    {
        puts("ERROR: Patient record not found!");   
    }


}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    char charInput = 0;
    int isFound = 0;
    int intInput = 0;

    printf("Enter the patient number: ");
    scanf("%d", &intInput);
    clearInputBuffer();
    isFound = findPatientIndexByPatientNum(intInput, patient, max); // return matching index

    if (isFound != -1) // -1 is not found
    {
        printf("\n"); // Enter the patient number: 1040 new line
        displayPatientData(&patient[isFound], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &charInput);
        clearInputBuffer();
        if (charInput == 'y')
        {
            patient[isFound].patientNumber = 0; 

            // erase array 
            strcpy(patient[isFound].name, "0");
            strcpy(patient[isFound].phone.description, "0"); // destination first source next 
            strcpy(patient[isFound].phone.number, "0");

            puts("Patient record has been removed!");

        }
        else
        {
            puts("Operation aborted.");
        }

    }
    else
    {
        printf("\n");
        puts("ERROR: Patient record not found!");
    }
    printf("\n");
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int intInput = 0;
    int isFound = 0;

    printf("Search by patient number: ");
    scanf("%d", &intInput); 
    clearInputBuffer();

    isFound = findPatientIndexByPatientNum(intInput, patient, max);

    if (isFound != -1) // if there is matching case
    {
        printf("\n");
        displayPatientData(&patient[isFound], FMT_FORM);
    }
    else
    {
        printf("\n");
        puts("*** No records found ***");
    }

}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char strInput[PHONE_LEN+1] = {0};
    int isFound = 0;
    char isMatch = 0;
    int i;

    printf("Search by phone number: ");
    scanf("%s", strInput);
    clearInputBuffer();

    printf("\n");
    printf("Pat.# Name            Phone#\n");
    printf("----- --------------- --------------------\n");

    // see if any single match result
    for (i = 0; i < max; i++)
    {
        isMatch = strcmp(strInput, patient[i].phone.number);
        if (isMatch == 0)
        {
            isFound = 1;
        }

    }

    if (isFound == 1)
    {
        for (i = 0; i < max; i++)
        {
            isMatch = strcmp(strInput, patient[i].phone.number);

            if (isMatch == 0) // only if matching case, call displayPatientData()
            {
                displayPatientData(&patient[i], FMT_TABLE);

            }
        }
    }
    else
    {
        printf("\n");
        puts("*** No records found ***");
    }

}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int findMax = 0;
    int result = 0;
  
    // find max
    findMax = patient[0].patientNumber; 
    for (i = 0; i < max; i++)
    {
        if (findMax < patient[i].patientNumber)
        {
            findMax = patient[i].patientNumber;
        }
    }
    
    result = findMax + 1;
    //printf("your result is %d\n", result);

    return result;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) 
{
    int i;
    int result = 0;
    int isMatch = 0;

    // see if at least one matching case is there 
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            isMatch = 1;
        }
    }

    if (isMatch != 0)
    {
        for (i = 0; i < max && patient[i].patientNumber != patientNumber; i++)
        {
            result = i + 1;
        }
    }
    else
    {
        result = -1;
    }

    
    return result;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char strInput[NAME_LEN+1] = {0};

    puts("Patient Data Input");
    puts("------------------");
    printf("Number: 0%4d\n", patient->patientNumber);
    printf("Name  : ");
    scanf("%[^\n]s", strInput); 
    clearInputBuffer();
    strcpy(patient->name, strInput);
    printf("\n");
    inputPhoneData(&patient->phone); // patient isn't already addr? why put & again
};

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int intInput = 0;
    char phoneNum[PHONE_LEN+1] = { 0 };

    puts("Phone Information");
    puts("-----------------");
    puts("How will the patient like to be contacted?");
    puts("1. Cell");
    puts("2. Home");
    puts("3. Work");
    puts("4. TBD");
    printf("Selection: ");
    scanf("%d", &intInput);
    clearInputBuffer();
    switch (intInput)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("\n");
        printf("Contact: %s\n", phone->description);
        //printf("Number : %s\n", phone->number);
        printf("Number : ");
        scanf("%s", phoneNum);
        clearInputBuffer();
        strcpy(phone->number, phoneNum);
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("\n");

        printf("Contact: %s\n", phone->description);
        //printf("Number : %s\n", phone->number);
        printf("Number : ");
        scanf("%s", phoneNum);
        clearInputBuffer();
        strcpy(phone->number, phoneNum);
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("\n");

        printf("Contact: %s\n", phone->description);
        //printf("Number : %s\n", phone->number);
        printf("Number : ");
        scanf("%s", phoneNum);
        clearInputBuffer();
        strcpy(phone->number, phoneNum);
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }
}
