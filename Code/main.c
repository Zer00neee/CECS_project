#include<stdio.h>
#include<string.h>
#define FILECSV "evaluations.csv"
void start();
void addEvaluation();
void searchEvaluation();    
void updateEvaluation();

void addtocsv(char name[], int rating, char day[], char month[], char year[], char feedback[]){
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
        if(month[1] == '2' && day[0] <= '2' && day[1] <= '9'){
            
        }else{
            if(month[1] == '4' && day[0] <= '3' && day[1] <= '0'){
                
            }else{
                if(month[1] == '6' && day[0] <= '3' && day[1] <= '0'){
                    
                }else{
                    if(month[1] == '9' && day[0] <= '3' && day[1] <= '0'){
                        
                    }else{
                        if(month[1] == '1' || month[1] == '3' || month[1] == '5' || month[1] == '7' || month[1] == '8' || month[1] == '0'){
                            if(day[0] <= '3' && day[1] <= '1'){
                                
                            }else{
                                printf("!!!day (01-31)!!!!\n");
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
                        }else{
                            if(month[1] == '2'){
                                if(day[0] <= '2' && day[1] <= '9'){
                                    
                                }else{
                                    printf("!!!day (01-29)!!!!\n");
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
                            }else{
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
                            }
                        }
                    }
                }
            }
        }
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
        fprintf(fp, "EvaluatorName,ServiceRating,Day,Month,Year,Feedback\n");
    }

    fprintf(fp, "%s,%d,%s,%s,%s,%s\n", name, rating, day,month,year, feedback);
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
