#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FILECSV "evaluations.csv"

// ประกาศฟังก์ชันจาก main.c
void addtocsv(char name[], int rating, char day[], char month[], char year[], char feedback[]);

// สร้างฟังก์ชัน record_exists() ไว้ใน UnitTest.c
int record_exists(const char *name, const char *feedback) {
    FILE *f = fopen(FILECSV, "r");
    if (!f) return 0;
    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, name) && strstr(line, feedback)) {
            found = 1;
            break;
        }
    }
    fclose(f);
    return found;
}

// ======= TEST CASES ========

void test_valid_data() {
    printf("Running test_valid_data...\n");
    addtocsv("BankTest", 5, "07", "05", "2568", "GoodService");
    assert(record_exists("BankTest", "GoodService") == 1);
    printf("test_valid_data passed!\n");
}

void test_invalid_rating() {
    printf("Running test_invalid_rating...\n");
    addtocsv("RateZero", 0, "07", "05", "2568", "Invalid");
    assert(record_exists("RateZero", "Invalid") == 0);
    printf("test_invalid_rating passed!\n");
}

void test_invalid_year() {
    printf("Running test_invalid_year...\n");
    addtocsv("YearErr", 4, "07", "05", "25", "BadYear");
    assert(record_exists("YearErr", "BadYear") == 0);
    printf("test_invalid_year passed!\n");
}

void test_invalid_month() {
    printf("Running test_invalid_month...\n");
    addtocsv("MonthErr", 5, "07", "15", "2568", "BadMonth");
    assert(record_exists("MonthErr", "BadMonth") == 0);
    printf("test_invalid_month passed!\n");
}

// ======= MAIN ========
void Test() {
    printf("=========== UNIT TEST START ===========\n");

    test_valid_data();
    test_invalid_rating();
    test_invalid_year();
    test_invalid_month();

    printf("=========== ALL TESTS PASSED! ==========\n");
}
