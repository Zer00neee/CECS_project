#include<stdio.h>
#include<string.h>
#define FILECSV "evaluations.csv"
int choice;

//.................................//
  // สร้างStruct ขึ้นมาเก็บข้อมูลในcsv //

struct Evaluation{
    char name[100];
    int rating;
    char date[30];
    char comment[500];
};

//.................................//
       // สร้างFuntionกรอกข้อมูล//

int addEvaluation(){
    struct Evaluation e;
    FILE *fp = fopen(FILECSV, "a+");  
    if (!fp) {                         
        printf("Cannot open the file\n");
}
    fprintf(fp,"EvaluationNAME, ServiceRating, EvaluationDate, Comment\n");
   
    printf("Enter evaluator's name: ");
    scanf(" %s", &e.name);

    printf("Enter score (1-5): ");
    scanf("%d", &e.rating);

    printf("Enter date (XXXX-XX-XX): ");
    scanf(" %s", e.date);

    printf("Enter comment: ");
    scanf(" %s", e.comment);

    fprintf(fp, "%s,%d,%s,%s\n", e.name, e.rating, e.date, e.comment);
}


int main() {
    struct Evaluation e;   
        printf("Customer Service Evaluation Data Management System\n");
        printf("1. Add evaluation data\n");
        printf("Select menu: ");
        scanf("%d", &choice);
    switch (choice) {
        case 1: addEvaluation(); break;

        
}
}
