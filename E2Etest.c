// ----------- E2Etest.c -----------
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "main.h"

int delete_record_by_username_for_test(const char* username, const char* filename) {
    FILE *fp_read = fopen(filename, "r");
    if (fp_read == NULL) {
        return 1; 
    }

    FILE *fp_write = fopen("temp.csv", "w");
    if (fp_write == NULL) {
        fclose(fp_read);
        printf("Error: Could not create temp file.\n");
        return 0;
    }

    char line[600];
    int deleted_count = 0;

    if (fgets(line, sizeof(line), fp_read) != NULL) {
        fputs(line, fp_write);
    }

    while (fgets(line, sizeof(line), fp_read) != NULL) {
        if (strstr(line, username) == NULL) {
            fputs(line, fp_write);
        } else {
            deleted_count++;
        }
    }

    fclose(fp_read);
    fclose(fp_write);

    remove(filename);
    rename("temp.csv", filename);

    return deleted_count; 
}

// E2E Test 

void E2Etest() {
    const char* main_filename = "evaluations.csv"; 
    const char* test_user = "E2E_TEMP_USER_999"; 

    printf("\n---  Running E2E Test on Real Data File  ---\n\n");

    printf("[SETUP] Ensuring no leftover test data exists...\n");
    delete_record_by_username_for_test(test_user, main_filename);
    printf(" -> Cleanup complete. Starting test.\n");

    printf("[ACTION] Adding a temporary record to '%s'...\n", main_filename);
    addtocsv(test_user, 5, "10", "10", "2025", "This is a temporary E2E test record.");
    
    printf("[ASSERT] Verifying that the record was added...\n");
    int search_result_after_add = perform_search(test_user, main_filename);
    assert(search_result_after_add >= 1); 
    printf(" -> Record added and found successfully. PASSED \n");

    printf("[TEARDOWN] Removing temporary test record...\n");
    int delete_result = delete_record_by_username_for_test(test_user, main_filename);
    assert(delete_result >= 1); 
    printf(" -> Temporary record removed.\n");

    printf("[VERIFY] Ensuring the test record is gone...\n");
    int search_result_after_delete = perform_search(test_user, main_filename);
    assert(search_result_after_delete == 0); 
    printf(" -> Cleanup verified. PASSED \n");


    printf("\n---  E2E TEST COMPLETED SUCCESSFULLY!  ---\n\n");
    
    start();
}