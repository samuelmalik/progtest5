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

typedef struct TIdArray {
    int *data;
    int size; // describes total items in array
    int capacity;
}TID_ARRAY;

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

void initIdArray(TID_ARRAY *arr) {
    arr->data = (int*)malloc(sizeof(int));
    arr->size = 0;
    arr->capacity = 1;
}

void freeIdArray(TID_ARRAY *arr) {
    free(arr->data);
    arr->size = 0;
    arr->capacity = 0;
    arr->data = NULL;
}

void appendIdArray(TID_ARRAY *arr, int id) {
    if (arr->size  == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, arr->capacity * sizeof(int));
    }
    arr->data[arr->size] = id;
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

int dateToMins(char mon[4], int day, int hr, int min) {
    if (!strcmp(mon, "Jan")) {
        return (day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Feb")) {
        return (31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Mar")) {
        return (31+28+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Apr")) {
        return (31+28+31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Maj")) {
        return (31+28+31+30+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Jun")) {
        return (31+28+31+30+31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Jul")) {
        return (31+28+31+30+31+30+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Aug")) {
        return (31+28+31+30+31+30+31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Sep")) {
        return (31+28+31+30+31+30+31+31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Oct")) {
        return (31+28+31+30+31+30+31+31+30+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Nov")) {
        return (31+28+31+30+31+30+31+31+30+31+day-1)*24*60 + hr*60 + min;
    } if (!strcmp(mon, "Dec")) {
        return (31+28+31+30+31+30+31+31+30+31+30+day-1)*24*60 + hr*60 + min;
    }
    return 0;
}

int readData(TARRAY *arr) {
    TRECORD rec;
    char c1,c2=',';

    printf("Data z kamer:\n");
    if (scanf(" %c",&c1)!=1 || c1!='{') return 1;

    while (c2==',') {
        int res = scanf(" %d : %1000s %3s %d %d : %d %c",&rec.id,rec.rz,rec.mon,&rec.day,&rec.hour,&rec.min,&c2);
        if (res != 7 || rec.id <=0 || !isTimeValid(rec.mon,rec.day,rec.hour,rec.min)) {
            return 1;
        }
        appendArray(arr,rec);
    }
    return 0;
}

void searchRecord(TARRAY arr, TSEARCH *src) {
    int diffA=-1, diffB=-1,countA=0, countB=0, countP=0, indexP, indexA, indexB;
    int diff, srcTime, itemTime;
    bool isMatched=false;

    TID_ARRAY arrB,arrA,arrP;

    //printf("\n====Hladam: %s ", src->rz);
    //printf("Pocet minut hladaneho: %d\n", dateToMins(src->mon,src->day,src->hour,src->min));

    initIdArray(&arrA);
    initIdArray(&arrB);
    initIdArray(&arrP);
    for (int i = 0 ; i < arr.size; i++) {
        // only searched vehoicles
        if (strcmp(src->rz,arr.data[i].rz)==0) {
            //printf("Polozka: %s ", arr.data[i].rz);
            //printf("Pocet minut polozky: %d\n", dateToMins(arr.data[i].mon,arr.data[i].day,arr.data[i].hour,arr.data[i].min));
            // porovnat diff
            itemTime = dateToMins(arr.data[i].mon,arr.data[i].day,arr.data[i].hour,arr.data[i].min);
            srcTime = dateToMins(src->mon,src->day,src->hour,src->min);
            diff = abs(itemTime-srcTime);

            if (diff==0) {
                isMatched=true;
                countP++;
                indexP=i;
                appendIdArray(&arrP,arr.data[i].id);
            }

            if ((diff < diffA||diffA==-1) && itemTime > srcTime) {
                diffA = diff;
                countA=1;
                indexA=i;
                freeIdArray(&arrA);
                initIdArray(&arrA);
                appendIdArray(&arrA,arr.data[i].id);
            } else if ((diff < diffB||diffB==-1) && itemTime < srcTime) {
                diffB = diff;
                countB=1;
                indexB=i;
                freeIdArray(&arrB);
                initIdArray(&arrB);
                appendIdArray(&arrB,arr.data[i].id);
            } else if (diffA == diff) {
                countA++;
                appendIdArray(&arrA,arr.data[i].id);
            } else if (diffB == diff) {
                countB++;
                appendIdArray(&arrB,arr.data[i].id);
            }
        }
    }
    /*TEST ARRAYOV*/
    /*
    printf("\nKamery pred: ");
    for (int i = 0 ; i < arrB.size; i++) {
        printf("%d,", arrB.data[i]);
    }
    printf("\nKamery po: ");
    for (int i = 0 ; i < arrA.size; i++) {
        printf("%d,", arrA.data[i]);
    }
    printf("\nKamery presne: ");
    for (int i = 0 ; i < arrP.size; i++) {
        printf("%d,", arrP.data[i]);
    }
    */
    /*KONIEC TESTU*/

    if (isMatched) {
        printf("> Presne: %s %d %02d:%02d, %dx [",arr.data[indexP].mon,arr.data[indexP].day,arr.data[indexP].hour, arr.data[indexP].min ,countP);
        // Printing cameras id
        for (int i = 0 ; i < arrP.size; i++) {
            if (arrP.size-1==i) {
                printf("%d]\n", arrP.data[i]);
            } else {
                printf("%d, ", arrP.data[i]);
            }
        }
    }else if (countA==0 && countB==0) {
        printf("> Automobil nenalezen.\n");
    }else {
        if (countB==0) {
            printf("> Predchazejici: N/A\n");
        } else {
            printf("> Predchazejici: %s %d %02d:%02d, %dx [",arr.data[indexB].mon,arr.data[indexB].day,arr.data[indexB].hour, arr.data[indexB].min ,countB);
            // Printing cameras id
            for (int i = 0 ; i < arrB.size; i++) {
                if (arrB.size-1==i) {
                    printf("%d]\n", arrB.data[i]);
                } else {
                    printf("%d, ", arrB.data[i]);
                }
            }
        }
        if (countA==0) {
            printf("> Pozdejsi: N/A\n");
        } else {
            printf("> Pozdejsi: %s %d %02d:%02d, %dx [",arr.data[indexA].mon,arr.data[indexA].day,arr.data[indexA].hour, arr.data[indexA].min ,countA);
            // Printing cameras id
            for (int i = 0 ; i < arrA.size; i++) {
                if (arrA.size-1==i) {
                    printf("%d]\n", arrA.data[i]);
                } else {
                    printf("%d, ", arrA.data[i]);
                }
            }
        }
    }
    freeIdArray(&arrA);
    freeIdArray(&arrB);
    freeIdArray(&arrP);
}

int readRequests(TARRAY arr) {
    printf("Hledani:\n");
    while (true) {
        TSEARCH src;
        //Check for valid search data
        int res = scanf(" %1000s %3s %d %d : %d",src.rz,src.mon,&src.day,&src.hour,&src.min);
        if (res == EOF) return 0;
        if (res != 5 || !isTimeValid(src.mon,src.day,src.hour,src.min)) return 1;

        //Function to make result
        searchRecord(arr, &src);
    }
}

int main(void) {
    // Initialization of array
    TARRAY arr;
    initArray(&arr);

    // Reading data
    if (readData(&arr)) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    // Process requests
    if (readRequests(arr)) {
        printf("Nespravny vstup.\n");
        return 1;
    };
    return 0;
}

/*
{10: ABC-12-34 Oct 1 7:30,
289: XYZ-98-76 Oct 10 15:40,
25: ABC-12-34 Oct 1 8:50,
42: Slartibartfast Dec 21 6:00,
11: ABC-12-34 Oct 1 10:50,
10: ABC-12-34 Oct 1 7:30,
17: ABC-12-34 Oct 1 7:30}
ABC-12-34 Oct 1 9:30
ABC-12-34 Oct 1 8:30
ABC-12-34 Oct 1 7:30
XYZ-98-76 Nov 30 0:00
abc-12-34 Oct 12 1:23
Slartibartfast Jan 24 10:42
 */
