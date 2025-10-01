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
    FILE *fp = fopen(FILECSV, "a");  // a คือเพิ่มข้อมูลต่อท้าย //
    if (!fp) {                         
        printf("Cannot open the file\n");
}
    fprintf(fp,"EvaluationNAME, ServiceRating, EvaluationDate, Comment\n");
   
    printf("Enter evaluator's name: ");
    scanf(" %s", &e.name);

    printf("Enter score (1-5): ");
    scanf("%d", &e.rating);

    printf("Enter date (XXXX-XX-XX): ");
    scanf(" %s", &e.date);

    printf("Enter comment: ");
    scanf(" %s", &e.comment);

    fprintf(fp, "%s,%d,%s,%s\n", e.name, e.rating, e.date, e.comment); 
}
//.................................//
       // สร้างFuntionอ่านข้อมูล//

int readEvaluation(){
    struct Evaluation e;
    FILE *fp = fopen(FILECSV, "r");  // r คืออ่านอย่างเดียว //
     if (!fp) {                         
        printf("Cannot open the file\n");
}
    char line[1000];
    printf("Reading evaluation\n");
    while (fgets(line, sizeof(line), fp)) {
        struct Evaluation e;
        sscanf(line, "%s,%d,%s,%s\n", e.name, e.rating, e.date, e.comment);
        printf("Name %s rating %d date %s commet %s\n", e.name, e.rating, e.date, e.comment);
}
fclose(fp);
}

int main() {
    struct Evaluation e;   
        printf("Customer Service Evaluation Data Management System\n");
        printf("1. Add evaluation data\n");
        printf("2. Read evaluation\n");
        printf("Select menu: ");
        scanf("%d", &choice);
    switch (choice) {
        case 1: addEvaluation(); break;
        case 2: readEvaluation(); break;

        
}
}
