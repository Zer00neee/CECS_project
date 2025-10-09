#include <stdio.h>
#include <string.h>
#include "main.h" 
#include "UnitTest.c" 
#include "E2Etest.c" 

#define FILECSV "evaluations.csv"

//VALIDATION LOGIC

int validate_evaluation_data(int rating, const char day[], const char month[], const char year[]){
    const char *maxDayTable[12] = { "31", "29", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};
    if (strlen(year) != 4) { printf("Error: Invalid year format (YYYY).\n"); return 0; }
    if (strlen(month) != 2) { printf("Error: Invalid month format (MM).\n"); return 0; }
    int validMonth = (month[0] == '0' && month[1] >= '1' && month[1] <= '9') || (month[0] == '1' && (month[1] >= '0' && month[1] <= '2'));
    if (!validMonth) { printf("Error: Month must be between 01-12.\n"); return 0; }
    int mIdx = (month[0] - '0') * 10 + (month[1] - '0') - 1;
    const char *maxDayStr = maxDayTable[mIdx];
    if (strlen(day) != 2) { printf("Error: Invalid day format (DD).\n"); return 0; }
    if (day[0] < '0' || (day[0] == '0' && day[1] == '0')) { printf("Error: Day is invalid.\n"); return 0; }
    if (day[0] > maxDayStr[0] || (day[0] == maxDayStr[0] && day[1] > maxDayStr[1])) { printf("Error: Day is out of range for month (max: %s).\n", maxDayStr); return 0; }
    if (rating < 1 || rating > 5) { printf("Error: Rating must be between 1-5.\n"); return 0; }
    return 1;
}

//ADD TO CSV

void addtocsv(const char name[], int rating, const char day[], const char month[], const char year[], const char feedback[]){
    if (!validate_evaluation_data(rating, day, month, year)) {
        printf("\n!!! Data validation failed. Record not added. Please try again. !!!\n");
        return; 
    }

    int fileExists = 0;
    int id = 1;
    FILE *fr = fopen(FILECSV, "r");
    if (fr != NULL) {
        fileExists = 1;
        char line[600];
        if (fgets(line, sizeof(line), fr) != NULL) {
            int count = 0;
            while (fgets(line, sizeof(line), fr) != NULL) {
                count++;
            }
            id = count + 1;
        }
        fclose(fr);
    }

    FILE *fp = fopen(FILECSV, "a");
    if (fp == NULL) {
        printf("Cannot open file %s for writing!\n", FILECSV);
        return;
    }

    if (!fileExists) {
        fprintf(fp, "ID,Name,Rating,Day,Month,Year,Feedback\n");
    }
    fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n", id, name, rating, day, month, year, feedback);
    fclose(fp);

    printf("\n--- Evaluation for '%s' added successfully with ID %d ---\n", name, id);
}

//ADD EVALUATION

void addEvaluation() {
    char name[50], day[3], month[3], year[5], feedback[500];
    int rating;

    printf("\n--- Add New Evaluation ---\n");
    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter score (1-5): ");
    scanf("%d", &rating);
    printf("Enter Day (DD): ");
    scanf("%2s", day);
    printf("Enter Month (MM): ");
    scanf("%2s", month);
    printf("Enter Year (YYYY): ");
    scanf("%4s", year);
    printf("Enter feedback (use_underscore_for_spaces): ");
    scanf("%499s", feedback);

    addtocsv(name, rating, day, month, year, feedback);
    choice();
}


//PERFORM SEARCH

int perform_search(const char* searchName, const char* filename) {
    char line[600];
    int found_count = 0;

    FILE *fr = fopen(filename, "r");
    if (fr == NULL) {
        return -1; 
    }

    if (fgets(line, sizeof(line), fr) == NULL) { 
        fclose(fr);
        return 0; 
    }

    while (fgets(line, sizeof(line), fr) != NULL) {
        char linecpy[600];
        strcpy(linecpy, line);
        strtok(linecpy, ","); 
        char *name = strtok(NULL, ",");

        if (name != NULL && strcmp(name, searchName) == 0) {
            printf("%s", line); 
            found_count++;
        }
    }

    fclose(fr);
    return found_count;
}


//SEARCH EVALUATION

void searchEvaluation() {
    char searchName[50];

    printf("\n--- Search Evaluation by Name ---\n");
    printf("Enter the name to search: ");
    scanf("%49s", searchName);

    printf("\nSearch Results for '%s':\n", searchName);
    printf("--------------------------------------------------\n");
    
    int result_count = perform_search(searchName, FILECSV);

    if (result_count == 0) {
        printf("Record with name '%s' not found.\n", searchName);
    } else if (result_count == -1) {
        printf("Cannot open file or file does not exist!\n");
    }
    
    printf("--------------------------------------------------\n");
    choice();
}



//UPDATE EVALUATION

void updateEvaluationByID() {
    int targetID;
    int found = 0;
    char line[600];
    char recordToUpdate[600] = ""; 

    printf("\n--- Update Evaluation by ID ---\n");
    printf("Enter the ID of the record to update: ");
    scanf("%d", &targetID);

    FILE *fr = fopen(FILECSV, "r");
    if (fr == NULL) {
        printf("Error: Cannot open data file!\n");
        choice();
        return;
    }

    fgets(line, sizeof(line), fr);

    while (fgets(line, sizeof(line), fr) != NULL) {
        int currentID;
        if (sscanf(line, "%d,", &currentID) == 1 && currentID == targetID) {
            strcpy(recordToUpdate, line); 
            found = 1;
            break; 
        }
    }
    fclose(fr);

    if (!found) {
        printf("\nRecord with ID %d not found.\n", targetID);
        choice();
        return;
    }

    printf("\n--- Current Data for ID %d ---\n", targetID);
    printf("ID,Name,Rating,Day,Month,Year,Feedback\n");
    printf("%s", recordToUpdate);
    printf("-------------------------------------------\n");

    char name[50], day[3], month[3], year[5], feedback[500];
    int rating;

    printf("\n--- Enter New Data ---\n");
    printf("Enter new name: ");
    scanf("%49s", name);
    printf("Enter new score (1-5): ");
    scanf("%d", &rating);
    printf("Enter new Day (DD): ");
    scanf("%2s", day);
    printf("Enter new Month (MM): ");
    scanf("%2s", month);
    printf("Enter new Year (YYYY): ");
    scanf("%4s", year);
    printf("Enter new feedback (use_underscore_for_spaces): ");
    scanf("%499s", feedback);

    if (!validate_evaluation_data(rating, day, month, year)) {
        printf("\n!!! New data is invalid. Update cancelled. !!!\n");
        choice();
        return;
    }

    fr = fopen(FILECSV, "r");
    FILE *fw = fopen("temp.csv", "w");
    if (fr == NULL || fw == NULL) {
        printf("Error: Could not process file for update.\n");
        choice();
        return;
    }

    if (fgets(line, sizeof(line), fr) != NULL) {
        fputs(line, fw);
    }
    
    while (fgets(line, sizeof(line), fr) != NULL) {
        int currentID;
        sscanf(line, "%d,", &currentID);
        if (currentID == targetID) {
            fprintf(fw, "%d,%s,%d,%s,%s,%s,%s\n", targetID, name, rating, day, month, year, feedback);
        } else {
            fputs(line, fw);
        }
    }
    
    fclose(fr);
    fclose(fw);

    remove(FILECSV); 
    rename("temp.csv", FILECSV); 

    printf("\n--- Record ID %d updated successfully! ---\n", targetID);
    choice();
}


//DELETE EVALUATION

void deleteEvaluationByID() {
    int targetID, currentID;
    int found = 0;

    printf("\n--- Mark Record as Deleted by ID ---\n");
    printf("Enter the ID of the record to mark as deleted: ");
    scanf("%d", &targetID);

    FILE *fr = fopen(FILECSV, "r");
    if (fr == NULL) {
        printf("Error: Cannot open data file!\n");
        choice();
        return;
    }

    FILE *fw = fopen("temp.csv", "w");
    if (fw == NULL) {
        printf("Error: Could not create temporary file.\n");
        fclose(fr);
        choice();
        return;
    }

    char line[600];
    if (fgets(line, sizeof(line), fr) != NULL) {
        fputs(line, fw);
    }

    while (fgets(line, sizeof(line), fr) != NULL) {
        if (sscanf(line, "%d,", &currentID) == 1) {
            if (currentID != targetID) {
                fputs(line, fw); 
            } else {
                found = 1; 
                fprintf(fw, "%d,-,-,-,-,-,-\n", targetID);
            }
        }
    }

    fclose(fr);
    fclose(fw);

    if (!found) {
        printf("\nRecord with ID %d not found.\n", targetID);
        remove("temp.csv"); 
    } else {
        remove(FILECSV);
        rename("temp.csv", FILECSV); 
        printf("\n--- Record with ID %d has been marked as deleted successfully! ---\n", targetID);
    }
    
    choice();
}

// READ EVALUATION

void readevaluation() {
    FILE *fr = fopen(FILECSV, "r");
    if (!fr) {
        printf("\nCannot open file or file is empty!\n");
        choice();
        return;
    }

    char line[600];
    printf("\n--- All Evaluation Records ---\n");
    while (fgets(line, sizeof(line), fr) != NULL) {
        printf("%s", line);
    }
    printf("------------------------------\n");
    fclose(fr);
    choice();
}


//CHOICE

void choice() {
    char user_choice;
    printf("\nContinue? (m = Main Menu / any other key = Exit): ");
    scanf(" %c", &user_choice);

    if (user_choice == 'm' || user_choice == 'M') {
        start();
    } else {
        printf("\nThank you for using the system. Goodbye!\n");
    }
}


//START

void start() {
    int choice_num;
    printf("\n===== Customer Service Evaluation System =====\n");
    printf("1. Add evaluation\n");
    printf("2. Search evaluation\n");
    printf("3. Update evaluation\n");
    printf("4. Delete evaluation\n");
    printf("5. Read all evaluations\n");
    printf("6. Run Tests\n");
    printf("7. Run End-to-End (E2E) Test\n");
    printf("8. Exit\n");
    printf("============================================\n");
    printf("Select menu: ");
    scanf("%d", &choice_num);

    switch(choice_num) {
        case 1: addEvaluation(); break;
        case 2: searchEvaluation(); break;
        case 3: updateEvaluationByID(); break;
        case 4: deleteEvaluationByID(); break;
        case 5: readevaluation(); break;
        case 6: Test(); break;
        case 7: E2Etest(); break;
        case 8: printf("\nGoodbye!\n"); break;
        default:
            printf("\nInvalid choice, please try again.\n");
            start();
            break;
    }
}


//MAIN

int main() {
    start();
    return 0;
}