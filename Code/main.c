#include<stdio.h>
#include<string.h>
#define FILECSV "evaluations.csv"

void addtocsv(char name[], int rating, char date[], char feedback[]){
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
        }
    else{
         int fileExists = 0;
    FILE *fr = fopen("evaluation.csv", "r");
    if(fr != NULL){
        fileExists = 1;
        fclose(fr);
    }
    FILE *fp = fopen("evaluation.csv", "a");
    if(fp == NULL){
        printf("Cannot open file!\n");
    }
    if(fileExists == 0){
        fprintf(fp, "EvaluatorName,ServiceRating,EvaluatorDate,Feedback\n");
    }

    fprintf(fp, "%s,%d,%s,%s\n", name, rating, date, feedback);
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
   
}

void addEvaluation() {
    char name[50];
    int rating;
    char date[11];
    char feedback[500];

    printf("Enter name: ");
    scanf("%49s", name);
    printf("Enter score(1-5): ");
    scanf("%d", &rating);
    printf("EnterDate(DD-MM-YYYY):");
    scanf("%10s", date);
    printf("Enter feedblack: ");
    scanf("%499s", feedback);
    addtocsv(name, rating, date, feedback);
}

void searchEvaluation() {
    char searchName[50];
    char line[600];
    int found = 0; 
    printf("Enter the name to search: ");
    scanf("%49s", searchName);
    FILE *fr = fopen("evaluation.csv", "r");
    if(fr == NULL) {
        printf("Cannot open file!\n");
    }
    fgets(line, sizeof(line), fr);
    printf("Search Results:\n");
    while(fgets(line, sizeof(line), fr) != NULL){
        char linecpy[600];
        strcpy(linecpy, line);
        char *name = strtok(linecpy, ",");
        if(strcmp(name, searchName) == 0) {
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
void updateEvaluation() {

}
void start(){
     int choice;
    printf("Customer Service Evaluation Data Management System\n");
    printf("1. Add evaluation\n");
    printf("2. Search evaluation\n");
    printf("3. Update evaluation\n");
    printf("Select menu: ");
    scanf("%d", &choice);
    switch(choice) {
    case 1: addEvaluation(); break; 
    case 2: searchEvaluation(); break;
    }
}

int main() {
   start();
}
