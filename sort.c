#include "core.h"

int cmp_apartment_number(const apartment  ap1, const apartment  ap2){
    return ap1.apartment_number - ap2.apartment_number;
}
int cmp_rooms(const apartment  ap1, const apartment  ap2){
    return ap1.rooms - ap2.rooms;
}
int cmp_owner(const apartment  ap1, const apartment  ap2){
    return strcmp(ap1.owner_surname,ap2.owner_surname);
}
int cmp_month_payment(const apartment  ap1, const apartment  ap2){
    return (int)(ap1.month_payment - ap2.month_payment);
}
int cmp_fact_payment(const apartment  ap1, const apartment  ap2){
    return (int)(ap1.fact_payment - ap2.fact_payment);
}
void sort_database(const char* filename){
    FILE* f=fopen(filename,"r+b");
    apartment ap1,ap2;
    fseek(f,0,SEEK_END);
    unsigned long i, j=0,n= ftell(f)/sizeof(apartment);
    int choose, sign, swapped;
    int (*cmp_apartments)(const apartment ,const apartment );
    printf("Choose field:\n1.Apartment number\n2.Number of rooms\n3.Owner's surname\n4.Monthly payment\n5.Actual payment\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            cmp_apartments = cmp_apartment_number;
            break;
        case 2:
            cmp_apartments = cmp_rooms;
            break;
        case 3:
            cmp_apartments = cmp_owner;
            break;
        case 4:
            cmp_apartments = cmp_month_payment;
            break;
        case 5:
            cmp_apartments = cmp_fact_payment;
            break;
        default:
            printf("Error: Unexpected number\n");
            exit(1);
    }
    printf("Choose order:\n1.Straight\n2.Reversed\n");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            sign = 1;
            break;
        case 2:
            sign = -1;
            break;
        default:
            printf("Error: Unexpected number\n");
            exit(1);
    }
    while (1){
        swapped = 0;
        for(i=0;i<n-j-1;i++){
            fseek(f,i * sizeof(apartment),SEEK_SET);
            fread(&ap1, sizeof(apartment),1,f);
            fread(&ap2, sizeof(apartment),1,f);
            if(sign * cmp_apartments(ap1,ap2) > 0){
                swap(f,i,i+1);
                swapped = 1;
            }
        }
        j++;
        if (!swapped) break;
    }
    fclose(f);
}
