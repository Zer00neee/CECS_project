// ----------- UnitTest.c -----------
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "main.h" 


 //Test Suite 1: Valid Data (Happy Path)

void test_standard_valid_data() {
    printf("Testing Suite 1: Standard valid data... ");
    assert(validate_evaluation_data(4, "15", "08", "2025") == 1);
    printf("PASSED \n");
}


 //Test Suite 2: Valid Edge Cases

void test_edge_case_rating_boundaries() {
    printf("Testing Suite 2: Rating is at lower boundary (1)... ");
    assert(validate_evaluation_data(1, "10", "01", "2024") == 1);
    printf("PASSED \n");

    printf("Testing Suite 2: Rating is at upper boundary (5)... ");
    assert(validate_evaluation_data(5, "10", "01", "2024") == 1);
    printf("PASSED \n");
}

void test_edge_case_date_boundaries() {
    printf("Testing Suite 2: Date is first day of year... ");
    assert(validate_evaluation_data(3, "01", "01", "2023") == 1);
    printf("PASSED \n");

    printf("Testing Suite 2: Date is last day of year... ");
    assert(validate_evaluation_data(3, "31", "12", "2023") == 1);
    printf("PASSED \n");

    printf("Testing Suite 2: Date is 31st in a 31-day month... ");
    assert(validate_evaluation_data(3, "31", "07", "2023") == 1);
    printf("PASSED \n");

    printf("Testing Suite 2: Date is 30th in a 30-day month... ");
    assert(validate_evaluation_data(3, "30", "09", "2023") == 1);
    printf("PASSED \n");

    printf("Testing Suite 2: Date is 29th of February... ");
    assert(validate_evaluation_data(3, "29", "02", "2024") == 1);
    printf("PASSED \n");
}


 //Test Suite 3: Invalid Rating

void test_rating_is_too_low() {
    printf("Testing Suite 3: Rating is too low (0)... ");
    assert(validate_evaluation_data(0, "10", "05", "2024") == 0);
    printf("PASSED \n");
}

void test_rating_is_too_high() {
    printf("Testing Suite 3: Rating is too high (6)... ");
    assert(validate_evaluation_data(6, "10", "05", "2024") == 0);
    printf("PASSED \n");
}


 //Test Suite 4: Invalid Date/Time Format

void test_year_format_is_invalid() {
    printf("Testing Suite 4: Year format is too short... ");
    assert(validate_evaluation_data(4, "20", "03", "23") == 0);
    printf("PASSED \n");
}

void test_month_format_is_invalid() {
    printf("Testing Suite 4: Month is out of range (00)... ");
    assert(validate_evaluation_data(4, "20", "00", "2023") == 0);
    printf("PASSED \n");

    printf("Testing Suite 4: Month is out of range (13)... ");
    assert(validate_evaluation_data(4, "20", "13", "2023") == 0);
    printf("PASSED \n");
}

void test_day_format_is_invalid() {
    printf("Testing Suite 4: Day format is not 2 digits... ");
    assert(validate_evaluation_data(3, "1", "11", "2024") == 0);
    printf("PASSED \n");

    printf("Testing Suite 4: Day is out of range (00)... ");
    assert(validate_evaluation_data(3, "00", "11", "2024") == 0);
    printf("PASSED \n");
}


// Test Suite 5: Invalid Day for a Specific Month

void test_day_is_invalid_for_april() {
    printf("Testing Suite 5: Day is invalid for April (31st)... ");
    assert(validate_evaluation_data(5, "31", "04", "2024") == 0);
    printf("PASSED \n");
}

void test_day_is_invalid_for_february() {
    printf("Testing Suite 5: Day is invalid for February (30th)... ");
    assert(validate_evaluation_data(5, "30", "02", "2024") == 0);
    printf("PASSED \n");
}



//Test Suite 6 : Search Functionality

void test_search_functionality() {
    const char* test_filename = "test_search_data.csv";
    
    // 1. Setup: 
    printf("Testing Suite 6: Setting up test file '%s'...\n", test_filename);
    FILE* fp = fopen(test_filename, "w");
    assert(fp != NULL);
    fprintf(fp, "ID,Name,Rating,Day,Month,Year,Feedback\n");
    fprintf(fp, "1,Alice,5,10,01,2025,Good\n");
    fprintf(fp, "2,Bob,4,11,02,2025,Okay\n");
    fprintf(fp, "3,Alice,3,12,03,2025,Average\n");
    fprintf(fp, "4,Charlie,5,13,04,2025,Excellent\n");
    fclose(fp);
    printf("Setup complete.\n");

    // 2. Act & Assert:

    printf("Testing Suite 6: Searching for a name that exists multiple times (Alice)... ");
    int count_alice = perform_search("Alice", test_filename);
    assert(count_alice == 2);
    printf("PASSED  (Found %d)\n", count_alice);

    printf("Testing Suite 6: Searching for a name that exists once (Bob)... ");
    int count_bob = perform_search("Bob", test_filename);
    assert(count_bob == 1);
    printf("PASSED  (Found %d)\n", count_bob);

    printf("Testing Suite 6: Searching for a name that does not exist (David)... ");
    int count_david = perform_search("David", test_filename);
    assert(count_david == 0);
    printf("PASSED  (Found %d)\n", count_david);

    printf("Testing Suite 6: Searching in a non-existent file... ");
    int count_nonexistent = perform_search("Alice", "nonexistentfile.csv");
    assert(count_nonexistent == -1);
    printf("PASSED  (Correctly handled error)\n");

 
    printf("Testing Suite 6: Cleaning up test file... ");
    remove(test_filename);
    printf("Cleanup complete.\n");
}



// --- Test  ---


void Test() {
    printf("\n---  Running Complete Unit & Integration Test Suite  ---\n\n");

    // Suite 1: Happy Path
    test_standard_valid_data();
    printf("--------------------------------------------------\n");

    // Suite 2: Valid Edge Cases
    test_edge_case_rating_boundaries();
    test_edge_case_date_boundaries();
    printf("--------------------------------------------------\n");

    // Suite 3: Invalid Rating
    test_rating_is_too_low();
    test_rating_is_too_high();
    printf("--------------------------------------------------\n");

    // Suite 4: Invalid Format
    test_year_format_is_invalid();
    test_month_format_is_invalid();
    test_day_format_is_invalid();
    printf("--------------------------------------------------\n");

    // Suite 5: Invalid Day for Month
    test_day_is_invalid_for_april();
    test_day_is_invalid_for_february();
    printf("--------------------------------------------------\n");

    // Suite 6: Search Functionality
    test_search_functionality();
    printf("--------------------------------------------------\n");

    printf("\n---  All tests passed successfully!  ---\n\n");
    
    start();
}