#include <stdio.h>
#include <stdlib.h>

typedef char* str;

void syntax();
void environment(int, str[]);

int year_start(int);
void structure(int, str[], str[]);
void format();

int frame[] = {0, 0, 0};

int main(int argc, str argv[]){
    environment(argc, argv);
    format();

    return 0;
}

void syntax(){
    puts("\n\n}-----------[ ERROR ... INTERRUPTION ]-----------{\n\n");
    puts("[ PROGRAM_NAME ] [ YEAR ] [ MONTH_1 ] [ MONTH_2 ]\n");
    puts("1. YEAR & MONTH must be of type INTEGER.");
    puts("2. MONTH must be between 1 & 12, INCLUSIVELY.\n");
    puts("TRY: no command-line input.");
    puts("\n\n}-----------[ ERROR ... INTERRUPTION ]-----------{\n\n");
    exit(0);
}
void environment(int count, str args[]){
    int year, month_1, month_2, cond;
    switch(--count){
        case 0:
            frame[0] = 2024;
            frame[1] = 1;
            frame[2] = 12;
            break;
        case 1:
            year = atoi(args[1]);
            if(year) frame[0] = year;
            else syntax();
            break;
        case 2:
            year = atoi(args[1]);
            month_1 = atoi(args[2]);
            cond = year && month_1;
            if(cond)
                cond = (month_1 > 0) && (month_1 < 13);
            if(cond){ 
                frame[0] = year;
                frame[1] = month_1;
                frame[2] = month_1;
            } else syntax();
            break;
        case 3:
            year = atoi(args[1]);
            month_1 = atoi(args[2]);
            month_2 = atoi(args[3]);
            cond = year && month_1 && month_2;
            if(cond)
                cond = (month_1 > 0) && (month_1 < 13) && (month_2 > 0) && (month_2 < 13);
            if(cond){ 
                frame[0] = year;
                frame[1] = month_1;
                frame[2] = month_2;
            } else syntax();
            break;
        default:
            syntax();
    }
}

int year_start(int year){
    int remainder = (year % 28),\
        fix = 1 - ((remainder - 1) / 4);
    remainder = (remainder - fix) % 7;
    if(remainder < 0) remainder += 6;
    return remainder;
}
void structure(int gap, str months[], str days[]){
    puts("\n");
    int exception = 29,\
        limit = 31,\
        year = frame[0];
    if((!(year % 100) && (year % 400)) || (year % 4))
        exception = 28;
    for(int month = 0; month < 12;){
        int space = gap, drop = 7 - space;
        printf("\n\n[ %s %i ]\n\n", months[month], year);
        for(int day = 0; day < 7; day++){
            if(day < 6) printf("| %s |  ", days[day]);
            else printf("| %s |\n", days[day]);
        }
        if(++month < 8){
            if(month == 2) limit = exception;
            else if(!(month % 2)) limit = 30;
            else limit = 31;
        } else if(month % 2) limit = 30;
        else limit = 31;
        for(int date = 0; date < limit; space++){
            while((gap && gap--)) printf("         ");
            if(++date < 10) printf("|  0%i |  ", date);
            else printf("|  %i |  ", date);
            if(!--drop && date < limit){ 
                printf("\n");
                drop = 7;
            }
        }
        gap = space % 7;
    }
    puts("\n");
}
void format(){
    int year = frame[0],\
        gap = year_start(year);
    if(!(--year % 100) && (year % 400)){
        gap--;
        if(gap < 0) gap += 7;
    }
    str months[] = {
        "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY",
        "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"    
    };
    str days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    structure(gap, months, days);
}