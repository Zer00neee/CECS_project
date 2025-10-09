// ----------- main.h -----------

#ifndef MAIN_H
#define MAIN_H

//จาก main.c 
void start(void);
void addEvaluation(void);
void searchEvaluation(void);
void updateEvaluationByID(void);
void deleteEvaluationByID(void);
void readevaluation(void);
void choice(void);
void addtocsv(const char name[], int rating, const char day[], const char month[], const char year[], const char feedback[]);
int validate_evaluation_data(int rating, const char day[], const char month[], const char year[]);

// จาก UnitTest.c
void Test(void); 
int perform_search(const char* username, const char* filename); 

// จาก E2Etest.c
int delete_record_by_username_for_test(const char* username, const char* filename);



#endif