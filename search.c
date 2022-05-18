#include "core.h"
int compare_apartments(apartment ap1, apartment ap2,int * params) {
    if (params[0] == 1 && ap1.apartment_number!=ap2.apartment_number) return 0;
    if (params[1] == 1 && ap1.rooms!=ap2.rooms) return 0;
    if (params[2] == 1 && strcmp(ap1.owner_surname,ap2.owner_surname)!=0) return 0;
    if (params[3] == 1 && ap1.month_payment!=ap2.month_payment) return 0;
    if (params[4] == 1 && ap1.fact_payment!=ap2.fact_payment) return 0;
    return 1;
}
void print_note_to_find(apartment ap, int* params){
    if (params[0] == 1) {
        printf("|%d", ap.apartment_number);
    }
    else{
            printf("|<blank>");
    }
    if(params[1] == 1){
        printf("|%d", ap.rooms);
    }
    else{
        printf("|<blank>");
    }

    if (params[2] == 1){
        printf("|%s", ap.owner_surname);
    }
    else{
        printf("|<blank>");
    }
    if (params[3] == 1){
        printf("|%.2lf",ap.month_payment);
    }
    else{
        printf("|<blank>");
    }
    if (params[4] == 1){
        printf("|%.2lf|",ap.fact_payment);
    }
    else{
        printf("|<blank>|");
    }
    printf("\n");
}
void find_note(const char* filename) {
    apartment ap,ap1;
    int params[]={0,0,0,0,0};
    int i, quit=0;
    double input;
    while(1){
        printf("Choose the parameters of the note\n1.Apartment number\n2.Number of rooms\n3.Owner's surname\n4.Month payment\n5.Actual payment\n6.Start searching\n");
        scanf("%d",&i);
        fflush(stdin);
        switch(i){
            case 1:
                params[i-1]=1;
                printf("Enter apartment's number\n");
                if (scanf("%lf",&input) && is_not_neg_int(input)){
                    ap.apartment_number = (int)input;
                }
                else{
                    printf("Error : Unexpected number");
                    exit(1);
                }
                break;
            case 2:
                params[i-1]=1;
                printf("Enter number of rooms\n");
                if (scanf("%lf",&input) && is_not_neg_int(input)){
                    ap.rooms = (int)input;
                }
                else {
                    printf("Error : Unexpected number");
                    exit(1);
                }
                break;
            case 3:
                params[i-1]=1;
                printf("Enter surname of owner\n");
                scanf("%[^\n]s",ap.owner_surname);
                break;
            case 4:
                params[i-1]=1;
                if(scanf("%lf",&input) && (input>=0)) ap.month_payment = input;
                else {
                    printf("Error: Unexpected number");
                    exit(1);
                }
                break;
            case 5:
                params[i-1]=1;
                if(scanf("%lf",&input) && (input>=0)) ap.fact_payment = input;
                else {
                    printf("Error: Unexpected number");
                    exit(1);
                }
                break;
            default:
                quit = 1;
        }
        print_note_to_find(ap,params);
        if (quit) break;
    }
    FILE* f = fopen(filename,"rb");
    fseek(f,0,SEEK_END);
    unsigned long j,n = ftell(f)/sizeof(apartment);
    rewind(f);
    printf("Notes that follow your criteria\n");
    for (j=0;j<n;j++){
        fread(&ap1,sizeof(apartment),1,f);
        if (compare_apartments(ap,ap1,params)){
            print_apartment(ap1,j+1);
            print_sep();
            quit = 0;
        }
    }
    if (quit){
        printf("\n");
    }
    printf("\n");
    fclose(f);
}
