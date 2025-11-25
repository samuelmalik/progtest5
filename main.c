#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Structs

typedef struct TRecord {
    int id;
    char rz[1001];
    char mon[4];
    int day;
    int hour;
    int min;
}TRECORD;

typedef struct TSearch {
    char rz[1001];
    char mon[4];
    int day;
    int hour;
    int min;
}TSEARCH;

typedef struct TArray {
    TRECORD *data;
    int size; // describes total items in array
    int capacity;
}TARRAY;

// Functions

void initArray(TARRAY *arr) {
    arr->data = (TRECORD*)malloc(sizeof(TRECORD));
    arr->size = 0;
    arr->capacity = 1;
}

void freeArray(TARRAY *arr) {
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
    arr->data = NULL;
}

void appendArray(TARRAY *arr, TRECORD record) {
    if (arr->size  == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (TRECORD*)realloc(arr->data, arr->capacity * sizeof(TRECORD));
    }
    arr->data[arr->size] = record;
    arr->size++;
}

bool isTimeValid(char mon[4], int day, int hr, int min) {
    //check valid month
    if (strcmp(mon, "Jan") && strcmp(mon, "Feb") && strcmp(mon, "Mar") && strcmp(mon, "Apr") && strcmp(mon, "May") && strcmp(mon, "Jun") && strcmp(mon, "Jul") && strcmp(mon, "Aug") && strcmp(mon, "Sep") && strcmp(mon, "Oct") && strcmp(mon, "Nov") && strcmp(mon, "Dec")) return false;
    //check valid hour and minute
    if (hr > 23 || hr < 0 || min > 59 || min < 0) return false;
    //check valid day
    if (day > 31 || day <=0) return false;
    if (!strcmp(mon, "Feb")&& day > 28) return false;
    if ((!strcmp(mon, "Apr") || !strcmp(mon, "Jun") || !strcmp(mon, "Sep") || !strcmp(mon, "Nov"))&&day>30) return false;
    return true;
}

int readData(TARRAY *arr) {
    TRECORD rec;
    char c1,c2=',';

    printf("Data z kamer:\n");
    if (scanf("%c",&c1)!=1 || c1!='{') return 1;

    while (c2==',') {
        int res = scanf(" %d : %1000s %3s %d %d : %d %c",&rec.id,rec.rz,rec.mon,&rec.day,&rec.hour,&rec.min,&c2);
        if (res != 7 || rec.id <=0 || !isTimeValid(rec.mon,rec.day,rec.hour,rec.min)) {
            return 1;
        }
        appendArray(arr,rec);
    }
    return 0;
}

int readRequests(TARRAY arr) {
    printf("Hledani:\n");
    while (true) {
        TSEARCH src;
        //Check for valid search data
        int res = scanf(" %1000s %3s %d %d : %d",src.rz,src.mon,&src.day,&src.hour,&src.min);
        if (res == EOF) return 0;
        if (res != 5) return 1;

        //Function to make result
    }
}

int main(void) {
    // Initialization of array
    TARRAY arr;
    initArray(&arr);

    // Reading data
    if (readData(&arr)) {
        printf("Nespravny vstup");
        return 1;
    }

    // Process requests
    if (readRequests(arr)) {
        printf("Nespravny vstup");
        return 1;
    };
    printf("KONEC\n");
    return 0;
}
