#include "core.h"


void print_apartment(apartment ap,unsigned long num) {
    printf("|%-5lu|%-11d|%-6d|%-25s|%-15.2lf|%-15.2lf|\n",num ,ap.apartment_number,ap.rooms,ap.owner_surname,ap.month_payment,ap.fact_payment);
}
void print_line(){
    int j;
    printf("|");
    for(j=0;j<82;j++){
        printf("-");
    }
    printf("|\n");
}
void print_sep(){
    int j;
    for(j=0;j<83;j++){
        if (j==0 || j==6 || j==18 || j==25 || j==51 || j==67){
            printf("|");
        }
        else{
            printf("-");
        }
    }
    printf("|\n");
}
void print_database(const char* filename){
    FILE* f= fopen(filename,"rb");
    fseek(f,0,SEEK_END);
    apartment ap;
    unsigned long i,n = ftell(f)/sizeof(apartment);
    rewind(f);
    print_line();
    printf("|№    |Apartment №|#rooms|Owner's Surname          |Month Payment  |Actual Payment |\n");
    print_sep();
    for(i=0;i<n;i++){
        fread(&ap,sizeof(apartment),1,f);
        print_apartment(ap,i+1);
        if (i==n-1){
            print_line();
        }
        else{
            print_sep();
        }
    }
    printf("\n");
    fclose(f);
}
void swap(FILE *f,unsigned long i, unsigned long j){
    apartment a1,a2;//переменная для временного хранения
    fseek(f,i*sizeof(apartment),SEEK_SET);//отступаем от начала на i чисел типа double
    fread(&a1, sizeof(apartment),1,f);//считываем два последовательных числа
    fseek(f,j*sizeof(apartment),SEEK_SET);//отступаем от начала на i чисел типа double
    fread(&a2, sizeof(apartment),1,f);
    fseek(f,i*sizeof(apartment),SEEK_SET);//отступаем на 2 назад от текущий позицией
    fwrite(&a2,sizeof (apartment),1,f);//записываем числа в файл в обратном порядке
    fseek(f,j*sizeof(apartment),SEEK_SET);//отступаем от начала на i чисел типа double
    fwrite(&a1,sizeof (apartment),1,f);
}
void swap_to_the_end(FILE* f,unsigned long pos) {
    fseek(f,0,SEEK_END);
    unsigned long i, n=ftell(f)/sizeof(apartment);//счетчик
    for(i=pos; i < (n-1); i++) {//от index до предпоследнего элемента
        swap(f,i,i+1);
    }
}
int is_not_neg_int(double a){
    return (int)a==a && a>=0;
}
apartment read_apartment(){
    apartment ap;
    double input;
    printf("Enter apartment's number\n");
    if (scanf("%lf",&input) && is_not_neg_int(input)){
        ap.apartment_number = (int)input;
    }
    else{
        printf("Error : Unexpected number");
        exit(1);
    }
    printf("Enter number of rooms\n");
    if (scanf("%lf",&input) && is_not_neg_int(input)){
        ap.rooms = (int)input;
    }
    else {
        printf("Error : Unexpected number");
        exit(1);
    }
    fflush(stdin);//отчистка входного буфера
    printf("Enter surname of owner\n");
    scanf("%[^\n]s",ap.owner_surname);//ввод фамилии владельца
    printf("Enter month payment\n");
    if(scanf("%lf",&input) && (input>=0)) ap.month_payment = input;
    else {
        printf("Error: Unexpected number");
        exit(1);
    }
    printf("Enter actual payment\n");

    if(scanf("%lf",&input) && (input>=0)) ap.fact_payment = input;
    else {
        printf("Error: Unexpected number");
        exit(1);
    }
    return ap;
}
void delete_note(const char *filename){
    printf("Enter the number of note, which you want to delete\n");
    print_database(filename);
    FILE * f = fopen(filename,"r+b");
    fseek(f,0,SEEK_END);
    unsigned long i, n=ftell(f)/sizeof(apartment);
    scanf("%lu",&i);
    if (i-1<n) {
        swap_to_the_end(f, i - 1);
        fclose(f);
        truncate(filename, (n - 1) * sizeof(apartment));
    }
    else{
        printf("An error occurred\n");
    }
    printf("\n");
}
void change_note(const char* filename){
    printf("Enter the number of note, which you want to change\n");
    print_database(filename);
    FILE * f = fopen(filename,"r+b");
    fseek(f,0,SEEK_END);
    unsigned long i,n=ftell(f)/sizeof(apartment);
    int choose,quit=0;
    double input;
    apartment ap;
    scanf("%lu",&i);
    if (i-1<n) {
        fseek(f, (i - 1) * sizeof(apartment), SEEK_SET);
        fread(&ap, sizeof(apartment), 1, f);
        while (1) {
            printf("What you want to change?\n1.Apartment number\n2.Number of rooms\n3.Owner's surname\n4.Month payment\n5.Actual payment\n6.Apply changes\n7.Decline changes\n");
            if (!scanf("%d", &choose)) {
                printf("An error occurred\n");
                exit(1);
            }
            fflush(stdin);
            switch (choose) {
                case 1:
                    printf("Enter apartment's number\n");
                    if (scanf("%lf", &input) && is_not_neg_int(input)) {
                        ap.apartment_number = (int) input;
                    } else {
                        printf("Error : Unexpected number");
                        fclose(f);
                        exit(1);
                    }
                    break;
                case 2:
                    printf("Enter number of rooms\n");
                    if (scanf("%lf", &input) && is_not_neg_int(input)) {
                        ap.rooms = (int) input;
                    } else {
                        printf("Error : Unexpected number");
                        fclose(f);
                        exit(1);
                    }
                    break;
                case 3:
                    printf("Enter surname of owner\n");
                    scanf("%[^\n]s", ap.owner_surname);
                    break;
                case 4:
                    printf("Enter month payment\n");
                    if (scanf("%lf", &input) && (input >= 0)) ap.month_payment = input;
                    else {
                        printf("Error: Unexpected number");
                        fclose(f);
                        exit(1);
                    }
                    break;
                case 5:
                    printf("Enter actual payment\n");
                    if (scanf("%lf", &input) && (input >= 0)) ap.fact_payment = input;
                    else {
                        printf("Error: Unexpected number");
                        fclose(f);
                        exit(1);
                    }
                    break;
                case 6:
                    quit = 1;
                    break;
                case 7:
                    quit = 2;
                    break;
                default:
                    printf("An error occurred\n");
                    exit(1);
            }
            if (quit) break;
            printf("Currently the note is:\n");
            print_apartment(ap, i);
        }
        if (quit == 1) {
            fseek(f, (i - 1) * sizeof(apartment), SEEK_SET);
            fwrite(&ap, sizeof(apartment), 1, f);
        }
    }
    else{
        printf("An error occurred\n");
    }
    printf("\n");
    fclose(f);
}
void database_push(const char * filename){
    FILE* f=fopen(filename,"ab");
    apartment ap =read_apartment();
    fwrite(&ap,sizeof(apartment),1,f);
    printf("\n");
    fclose(f);
}
void menu(){
    const char * filepath = "data_base.bin";
    int i=0, quit = 0;
    while (1) {
        printf("Choose the action:\n1.Show data base\n2.Sort data base\n3.Find note\n4.Add note\n5.Delete note\n6.Change note\n7.Exit\n");
        if (scanf("%d", &i)) {
            switch (i) {
                case 1:
                    print_database(filepath);
                    break;
                case 2:
                    sort_database(filepath);
                    break;
                case 3:
                    find_note(filepath);
                    break;
                case 4:
                    database_push(filepath);
                    break;
                case 5:
                    delete_note(filepath);
                    break;
                case 6:
                    change_note(filepath);
                    break;
                default:
                    quit = 1;
                    break;
            }
        }
        else{
            printf("An error occurred\n");
            exit(1);
        }
        if (quit) break;
    }
}
