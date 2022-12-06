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
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords == 1)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else if(isAllRecords == 0)
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }

    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           appoint->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data) // from now on, data is pointer
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
            menuAppointment(data);
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
            displayAllPatients(patient, max, FMT_TABLE);
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
        printf("Edit Patient (%05d)\n"
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
            printf("\n");
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("\n");
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
    else // at least one patient
    {
        
        displayPatientTableHeader();

        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber == 0) // empty record
            {
                // do nothing 
            }
            else
            {
                displayPatientData(&patient[i], fmt); // actual record
            }
        }
    }


    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    char charInput = 0, newLine = 0;
    int isFound = 0;
    int intInput = 0;
    int flag = 1;

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

        while (flag)
        {
            scanf(" %c%c", &charInput, &newLine);
            if (newLine == 10) //because new line ascii code is 10 
            {
                if (charInput == 'y')
                {
                    patient[isFound].patientNumber = 0;

                    // erase array 
                    strcpy(patient[isFound].name, "0");
                    strcpy(patient[isFound].phone.description, "0"); // destination first source next 
                    strcpy(patient[isFound].phone.number, "0");

                    puts("Patient record has been removed!");
                    flag = 0;
                }
                else if (charInput == 'n')
                {
                    puts("Operation aborted.");
                    flag = 0;
                }
                else
                {
                    printf("ERROR: Character must be one of [yn]: ");
                    clearInputBuffer();
                }
            }
            else
            {
                printf("ERROR: Character must be one of [yn]: ");
                clearInputBuffer();
            }
        }

       

    }
    else
    {
        printf("\n");
        puts("ERROR: Patient record not found!");
    }
    printf("\n");
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo: display header + all appointment struct 
void viewAllAppointments(struct ClinicData* data) // pass except for sorting 
{
    int i;
    struct Date inputDate = { 0 };
    int matchingIdx = 0;

    // sorting appointment struct
    selectionSort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&inputDate, ALL_RECS); // when 1st arg is not needed? 
    
    // appoint has date, time, patient number
    // patient has patient number, name, phone 

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {
            matchingIdx = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[matchingIdx], &data->appointments[i], INCD_DATE);
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo: input(year, month, day) + day error handling(29, 30, 31) + display date + header + part of appoint struct
void viewAppointmentSchedule(struct ClinicData* data) // pass except for sorting
{
    int i;
    int year = 0, month = 0, day = 0;
    int flag = 1, startDay = 1, endDay = 0;
    struct Date inputDate = { 0 };
    int matchingIdx = 0;
    int timestamp[MAX_APPOINTMENTS] = { 0 };
    int dataCount = 0;

    printf("Year        : ");
    scanf("%d", &year);
    printf("Month (%d-%d): ", START_MONTH, END_MONTH);
    scanf("%d", &month);

    if (year % 4 == 0) // leap year
    {
        switch (month)
        {
        case 2:
            endDay = 29;
            break;
        case 4:
            endDay = 30;
            break;
        case 6:
            endDay = 30;
            break;
        case 9:
            endDay = 30;
            break;
        case 11:
            endDay = 30;
            break;
        default:
            endDay = 31;
            break;
        }
    }
    else
    {
        switch (month)
        {
        case 2:
            endDay = 28;
            break;
        case 4:
            endDay = 30;
            break;
        case 6:
            endDay = 30;
            break;
        case 9:
            endDay = 30;
            break;
        case 11:
            endDay = 30;
            break;
        default:
            endDay = 31;
            break;
        }
    }

    printf("Day (%d-%d)  : ", startDay, endDay);
    
    while (flag)
    {
        scanf("%d", &day);
        if (day < startDay || day > endDay)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", startDay, endDay);
        }
        else
        {
            flag = 0;
        }
    }
    printf("\n");
    
    clearInputBuffer();

    inputDate.year = year;
    inputDate.month = month;
    inputDate.day = day;

    // generate timestamp array 
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {
            timestamp[i] = data->appointments[i].date.year * 365 * 24 * 60 +
                data->appointments[i].date.month * 12 * 24 * 60 +
                data->appointments[i].date.day * 24 * 60 +
                data->appointments[i].time.hour * 60 +
                data->appointments[i].time.min;

            dataCount += 1;
        }
        
    }

    // sorting appointment struct
    selectionSort(data->appointments, timestamp, dataCount);

    displayScheduleTableHeader(&inputDate, PART_RECS);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {
            if (data->appointments[i].date.year == inputDate.year &&
                data->appointments[i].date.month == inputDate.month &&
                data->appointments[i].date.day == inputDate.day)
            {
                matchingIdx = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
                displayScheduleData(&data->patients[matchingIdx], &data->appointments[i], NOT_INCD_DATE);
            }
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
// Todo: input(pnumber, yy, mm, dd, h, m) + time error handling(slot, interval) + stored data into appoint struct 
void addAppointment(struct Appointment* appoints, int maxAppoints, struct Patient* patients, int maxPatients) // how to pass struct memeber as pointer???
{
    int year = 0, month = 0, day = 0, hour = 0, min = 0;
    int isFull = 0;
    int flag = 1, flag2 = 1;
    int patientNum = 0;
    int i; 
    int freeIdx = 0;

    printf("Patient Number: ");
    scanf("%d", &patientNum);
    clearInputBuffer();

    while (flag)
    {
        isFull = 0;

        printf("Year        : ");
        scanf("%d", &year);
        printf("Month (1-12): ");
        scanf("%d", &month);
        printf("Day (1-31)  : ");
        scanf("%d", &day);
        printf("Hour (0-23)  : ");
        scanf("%d", &hour);
        printf("Minute (0-59): ");
        scanf("%d", &min);
        clearInputBuffer();

        for (i = 0; i < maxAppoints; i++)
        {
            if (appoints[i].patientNumber != 0) 
            {
                if (appoints[i].date.year == year &&
                    appoints[i].date.month == month &&
                    appoints[i].date.day == day &&
                    appoints[i].time.hour == hour &&
                    appoints[i].time.min == min)
                {
                    isFull = 1;
                }
            }
        }
        
        if (isFull == 1) // exact slot full 
        {
            printf("\n");
            printf("ERROR: Appointment timeslot is not available!\n");
            printf("\n");
        }
        else // when slots available
        {
            if (hour >= START_HOUR && hour <= END_HOUR && (min == 0 || min == MIN_INTERVAL) && hour + min <= END_HOUR) // met condition
            {
                // save
                for (i = 0; i < maxAppoints && appoints[i].patientNumber != 0; i++)
                {
                    freeIdx = i + 1;
                }
                appoints[freeIdx].patientNumber = patientNum;
                appoints[freeIdx].date.year = year;
                appoints[freeIdx].date.month = month;
                appoints[freeIdx].date.day = day;
                appoints[freeIdx].time.hour = hour;
                appoints[freeIdx].time.min = min;

                printf("\n");
                printf("*** Appointment scheduled! ***");
                flag = 0;
                flag2 = 0;
            }
            else // NOT met condition
            {
                while (flag2)
                {
                    printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n",
                        START_HOUR, END_HOUR, MIN_INTERVAL);
                    printf("\n");

                    printf("Hour (0-23)  : ");
                    scanf("%d", &hour);
                    printf("Minute (0-59): ");
                    scanf("%d", &min);
                    clearInputBuffer();

                    if (hour >= START_HOUR && hour <= END_HOUR && (min == 0 || min == MIN_INTERVAL) && hour + min <= END_HOUR) // restriction met 
                    {
                        // save
                        for (i = 0; i < maxAppoints && appoints[i].patientNumber != 0; i++)
                        {
                            freeIdx = i + 1;
                        }
                        appoints[freeIdx].patientNumber = patientNum;
                        appoints[freeIdx].date.year = year;
                        appoints[freeIdx].date.month = month;
                        appoints[freeIdx].date.day = day;
                        appoints[freeIdx].time.hour = hour;
                        appoints[freeIdx].time.min = min;

                        printf("\n");
                        printf("*** Appointment scheduled! ***");
                        flag = 0;
                        flag2 = 0;
                    }
                }
            }
        }
    }
    printf("\n\n");
}

// Remove an appointment record from the appointment array
// Todo: input(pnumber) + show yy, mm, dd, patient struct, sure to delete? 
void removeAppointment(struct Appointment* appoints, int maxAppoints, struct Patient* patients, int maxPatients) // think about it... 
{
    int patientNum = 0;
    int isFound = 0, matchingIdx = 0, matchingPatient = 0;
    int year = 0, month = 0, day = 0;
    int i;
    char confirmDel = 0;
    int timestamp[MAX_APPOINTMENTS] = { 0 };
    int dataCount = 0;

    printf("Patient Number: ");
    scanf("%d", &patientNum);
    clearInputBuffer();

    for (i = 0; i < maxAppoints; i++)
    {
        if (appoints[i].patientNumber == patientNum) 
        {
            isFound = 1; 
        }
    }

    if (isFound == 1) // appointment with the patient record exists
    {
        printf("Year        : ");
        scanf("%d", &year);
        printf("Month (1-12): ");
        scanf("%d", &month);
        printf("Day (1-29)  : ");
        scanf("%d", &day);
        clearInputBuffer();

        for (i = 0; i < maxAppoints; i++)
        {
            if (appoints[i].patientNumber == patientNum &&
                appoints[i].date.year == year &&
                appoints[i].date.month == month &&
                appoints[i].date.day == day)
            {
                matchingIdx = i; // same date booking location
            }
        }

        matchingPatient = findPatientIndexByPatientNum(patientNum, patients, maxPatients);

        printf("\n");
        printf("Name  : %s\n", patients[matchingPatient].name);
        printf("Number: 0%d\n", patients[matchingPatient].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patients[matchingPatient].phone.number);
        printf(" (%s)\n", patients[matchingPatient].phone.description);
        printf("Are you sure you want to remove this appointment (y,n): ");
        scanf(" %c", &confirmDel);
        clearInputBuffer();

        if (confirmDel == 'y')
        {
            appoints[matchingIdx].patientNumber = 0;
            appoints[matchingIdx].date.year = 0;
            appoints[matchingIdx].date.month = 0;
            appoints[matchingIdx].date.day = 0;
            appoints[matchingIdx].time.hour = 0;
            appoints[matchingIdx].time.min = 0;
            printf("\n");
            printf("Appointment record has been removed!\n");
        }
        
    }
    else // appointment with the patient record NOT exists
    {
        printf("ERROR: Patient record not found!\n");
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
    char strInput[PHONE_LEN + 1] = { 0 };
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

// sort
void selectionSort(struct Appointment* appoints,  int itemCount)
{
    int i, j, minIdx = 0;
    int timeMin =0, timeIdx = 0;
    int temp = 0;
    struct Appointment tempAppoint = { 0 };

    for (i = 0; i < itemCount; i++)
    {
        minIdx = i;

        for (j = i + 1; j < itemCount; j++)
        {
            timeIdx = appoints[j].date.year * 365 * 24 * 60 +
                appoints[j].date.month * 12 * 24 * 60 +
                appoints[j].date.day * 24 * 60 +
                appoints[j].time.hour * 60 +

                appoints[j].time.min;
            
            timeMin = appoints[minIdx].date.year * 365 * 24 * 60 +
                appoints[minIdx].date.month * 12 * 24 * 60 +
                appoints[minIdx].date.day * 24 * 60 +
                appoints[minIdx].time.hour * 60 +
                appoints[minIdx].time.min;

            if (timeIdx < timeMin) 
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            tempAppoint = appoints[i]; // appointment struct swap 
            appoints[i] = appoints[minIdx];
            appoints[minIdx] = tempAppoint;
        }
    }
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char strInput[NAME_LEN + 1] = { 0 };

    puts("Patient Data Input");
    puts("------------------");
    printf("Number: 0%4d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(strInput, 1, 15);
    strcpy(patient->name, strInput);
    printf("\n");
    inputPhoneData(&patient->phone); 
};

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int intInput = 0;
    char phoneNum[PHONE_LEN + 1] = { 0 };

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
        printf("Number : ");
        inputCString(phoneNum, 10, 10);
        strcpy(phone->number, phoneNum);
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("\n");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phoneNum, 10, 10);
        strcpy(phone->number, phoneNum);
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("\n");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phoneNum, 10, 10);
        strcpy(phone->number, phoneNum);
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    struct Patient tempPatient = { 0 }; 
    
    //read the datafile
    FILE* fpPatient = fopen(datafile, "r");

    //store the data to the second argument
    if (fpPatient != NULL)
    {
        //"%d|%[^|]|%[^|]|%[^\n]"
        while (i < max && fscanf(fpPatient, "%d|%[^|]|%[^|]|%[^\n]", // %[^|]s or %[^|]?? 
            &tempPatient.patientNumber,
            tempPatient.name,
            tempPatient.phone.description,
            tempPatient.phone.number) >= 3 )
        {

            if (&tempPatient.phone.number != 0) // NOT TBD
            {
                patients[i] = tempPatient;
                strcpy(tempPatient.phone.number, "0"); // set blank again
            } 
            else // TBD
            {
                patients[i] = tempPatient;
                strcpy(patients[i].phone.number, "0");
            }
            i++;
        }

        if (fclose(fpPatient) == EOF) // if fclose error, exit with EOF
        {
            printf("<<< ERROR:  FAILED TO CLOSE FILE >>>\n");
        }
        fpPatient = NULL;
    }
    else
    {
        printf("cannot open the file\n");

    }

    return i;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    struct Appointment tempAppoint = { 0 };

    //read the datafile
    FILE* fpAppoint = fopen(datafile, "r");

    //store the data to the second argument
    if (fpAppoint != NULL)
    {
        
        while (i < max && fscanf(fpAppoint, "%d,%d,%d,%d,%d,%d", // if char matches delimeter, it is discarded *** error ***
            &tempAppoint.patientNumber,
            &tempAppoint.date.year,
            &tempAppoint.date.month,
            &tempAppoint.date.day,
            &tempAppoint.time.hour,
            &tempAppoint.time.min) == 6)
        {
            appoints[i] = tempAppoint;
            i++;

        }
        
        if (fclose(fpAppoint) == EOF)
        {
            printf("<<< ERROR:  FAILED TO CLOSE FILE >>>\n");
        }
        fpAppoint = NULL;
    }
    else
    {
        printf("cannot open the file\n");

    }
    return i;
}
