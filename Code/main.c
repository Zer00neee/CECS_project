
#include<stdio.h>
#include<string.h>
#define FILECSV "evaluations.csv"

void start();
void addEvaluation();
void searchEvaluation();    
void updateEvaluation();
void addtocsv(char name[], int rating, char day[], char month[], char year[], char feedback[]){
    const char *maxDayTable[12] = {
        "31", "29", "31", "30", "31", "30", "31", "31", "30", "31", "30", "31"};
    int mIdx = (month[0] - '0') * 10 + (month[1] - '0') - 1;
    int validMonth = (month[0] == '0' && month[1] >= '1' && month[1] <= '9') || (month[0] == '1' && (month[1] == '0' || month[1] == '1' || month[1] == '2'));
    if(strlen(year) != 4) {
        printf("!!!year (YYYY)!!!!\n");
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    if(strlen(month) != 2) {
        printf("!!!month (01-12)!!!!\n");
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    if(strlen(day) != 2) {
        printf("!!!day (01-%s)!!!!\n", maxDayTable[0]);
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    if(!validMonth) {
        printf("!!!month (01-12)!!!!\n");
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    const char *maxDayStr = maxDayTable[mIdx];
    if(day[0] < '0' || day[0] > '3' || day[1] < '0' || day[1] > '9' || (day[0] == '0' && day[1] == '0')) {
        printf("!!!day (01-%s)!!!!\n", maxDayStr);
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    if(day[0] > maxDayStr[0] || (day[0] == maxDayStr[0] && day[1] > maxDayStr[1])) {
        printf("!!!day (01-%s)!!!!\n", maxDayStr);
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    if(rating < 1 || rating > 5) {
        printf("!!!rating (1-5)!!!!\n");
        printf("Enter again y = yes / n = no / r = retun\n");
        char type;
        scanf(" %c", &type);
        if(type == 'y'){
            addEvaluation();
        }
        if(type == 'n'){
            printf("Thank you\n");
        }
        if(type == 'r'){
            start();
        }
        return;
    }
    int fileExists = 0;
    int id = 1;  
FILE *fr = fopen(FILECSV, "r");
if(fr != NULL){
    fileExists = 1;
    char line[600];
    int count = 0;
    fgets(line, sizeof(line), fr); 
    while(fgets(line, sizeof(line), fr) != NULL){
        count++;
    }
    id = count + 1; 
    fclose(fr);
}
FILE *fp = fopen(FILECSV, "a");
if(fp == NULL){
    printf("Cannot open file!\n");
    return;
}
if(fileExists == 0){
    fprintf(fp, "ID,Name,Rating,Day,Month,Year,Feedback\n");
}
fprintf(fp, "%d,%s,%d,%s,%s,%s,%s\n", id, name, rating, day, month, year, feedback);
fclose(fp);

    char choice;
    printf("add more y = yes / n = no / r = retun: ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        addEvaluation();
    }
    if(choice == 'n'){
        printf("Thank you\n");
    }
    if(choice == 'r'){
        start();
    }
}

void addEvaluation() {
    char name[50];
    int rating;
    char day[3], month[3], year[5];
    char feedback[500];

    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter score(1-5): ");
    scanf("%d", &rating);
    printf("EnterDay(DD):");
    scanf("%3s", day);
    printf("EnterMonth(MM):");
    scanf("%3s", month);
    printf("EnterYear(YYYY):");
    scanf("%5s", year);
    printf("Enter feedblack: ");
    scanf("%499s", feedback);
    addtocsv(name, rating, day, month, year, feedback);
}

void searchEvaluation() {
    char searchName[50];
    char line[600];
    int found = 0; 
    printf("Enter the name to search: ");
    scanf("%49s", searchName);
    FILE *fr = fopen(FILECSV, "r");
    if(fr == NULL) {
        printf("Cannot open file!\n");
        return;
    }
    if(fgets(line, sizeof(line), fr) == NULL) {
        printf("No records found.\n");
        fclose(fr);
        return;
    }
    printf("Search Results:\n");
    while(fgets(line, sizeof(line), fr) != NULL){
        char linecpy[600];
        strcpy(linecpy, line);
        char *ID = strtok(linecpy, ",");
        char *name = strtok(NULL, ",");
        if(name && strcmp(name, searchName) == 0) {
            printf("%s", line);
            found = 1;
        }
    }
    if(found != 1) {
        printf("Not found %s\n", searchName);
    }
    fclose(fr);
    char choice;
    printf("search more y = yes / n = no / r = retun: ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        searchEvaluation();
    }
    if(choice == 'n'){
        printf("Thank you\n");
    }
    if(choice == 'r'){
        start();
    }
}
void updateEvaluationByID() {
    char idStr[10];
    char line[600], tempFile[] = "temp.csv";
    int found = 0;

    printf("Enter ID to update: ");
    scanf("%9s", idStr);

    FILE *fr = fopen(FILECSV, "r");
    FILE *fw = fopen(tempFile, "w");
    if (!fr || !fw) {
        printf("Cannot open file!\n");
        return;
    }

    fgets(line, sizeof(line), fr);
    fprintf(fw, "%s", line);
    while(fgets(line, sizeof(line), fr) != NULL) {
        char lineCopy[600];
        strcpy(lineCopy, line);
        char *currID = strtok(lineCopy, ",");
        char *currName = strtok(NULL, ",");
        char *currRating = strtok(NULL, ",");
        char *currDay = strtok(NULL, ",");
        char *currMonth = strtok(NULL, ",");
        char *currYear = strtok(NULL, ",");
        char *currFeedback = strtok(NULL, "\n");

        if (strcmp(currID, idStr) == 0) {
            found = 1;
            printf("Old:\n");
            printf("Name: %s\nRating: %s\nDay: %s\nMonth: %s\nYear: %s\nFeedback: %s\n",currName, currRating, currDay, currMonth, currYear, currFeedback);
            char newName[50], newDay[3], newMonth[3], newYear[5], newFeedback[500];
            int newRating;
            printf("Enter new name: ");
            scanf("%49s", newName);
            printf("Enter new rating (1-5): ");
            scanf("%d", &newRating);
            printf("Enter new day (DD): ");
            scanf("%2s", newDay);
            printf("Enter new month (MM): ");
            scanf("%2s", newMonth);
            printf("Enter new year (YYYY): ");
            scanf("%4s", newYear);
            printf("Enter new feedback: ");
            scanf("%499s", newFeedback);

            fprintf(fw, "%s,%s,%d,%s,%s,%s,%s\n", currID, newName, newRating, newDay, newMonth, newYear, newFeedback);
        } else {
            fprintf(fw, "%s", line);
        }
    }

    fclose(fr);
    fclose(fw);

    if (found) {
        remove(FILECSV);
        rename(tempFile, FILECSV);
        printf("Record updated successfully.\n");
    } else {
        remove(tempFile);
        printf("ID not found.\n");
    }
}

void deleteEvaluationByID() {
    char idStr[10];
    char line[600], tempFile[] = "temp.csv";
    int found = 0;

    printf("Enter ID to mark as deleted: ");
    scanf("%9s", idStr);

    FILE *fr = fopen(FILECSV, "r");
    FILE *fw = fopen(tempFile, "w");
    if (!fr || !fw) {
        printf("Cannot open file!\n");
        return;
    }

    fgets(line, sizeof(line), fr);
    fprintf(fw, "%s", line);

    while(fgets(line, sizeof(line), fr) != NULL) {
        char lineCopy[600];
        strcpy(lineCopy, line);
        char *currID = strtok(lineCopy, ",");

        if (strcmp(currID, idStr) == 0) {
            found = 1;

            char confirm;
            printf("Are you sure you want to delete record ID %s as deleted? (y/n): ", idStr);
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                fprintf(fw, "%s,-,-,-,-,-,-\n", currID);
                printf("Record with ID %s deleted.\n", idStr);
            } else {
                fprintf(fw, "%s", line);
                printf("Operation canceled.\n");
            }
        } else {
            fprintf(fw, "%s", line);
        }
     }

    fclose(fr);
    fclose(fw);

    if (found) {
        remove(FILECSV);
        rename(tempFile, FILECSV);
    } else {
        remove(tempFile);
        printf("ID not found.\n");
    }
    char choice;
    printf("add more y = yes / n = no / r = retun: ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        addEvaluation();
    }
    if(choice == 'n'){
        printf("Thank you\n");
    }
    if(choice == 'r'){
        start();
    }
}

void readevaluation() {
    FILE *fr = fopen(FILECSV, "r");
    if (!fr) {
        printf("Cannot open file!\n");
        return;
    }

    char line[600];
    int lineNum = 0;

    while (fgets(line, sizeof(line), fr) != NULL) {
        lineNum++;
        if (lineNum == 1) {
            printf("%s", line);
            continue;
        }

        printf("%s", line);
    }

    fclose(fr);
    char choice;
    printf("add more y = yes / n = no / r = retun: ");
    scanf(" %c", &choice);
    if(choice == 'y'){
        addEvaluation();
    }
    if(choice == 'n'){
        printf("Thank you\n");
    }
    if(choice == 'r'){
        start();
    }
}


void start(){
     int choice;
    printf("Customer Service Evaluation Data Management System\n");
    printf("1. Add evaluation\n");
    printf("2. Search evaluation\n");
    printf("3. Update evaluation\n");
    printf("4. Delete evaluation\n");
    printf("5. Read evaluation\n");
    printf("Select menu: ");
    scanf("%d", &choice);
    switch(choice) {
    case 1: addEvaluation(); break; 
    case 2: searchEvaluation(); break;
    case 3: updateEvaluationByID(); break;
    case 4: deleteEvaluationByID(); break;
    case 5: readevaluation(); break;
    }
    
}

int main() {
   start();
}
