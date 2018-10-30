#include <stdio.h>
#include <stdlib.h>
const double tolerance = 3e-8;
char* data_file = "U_I.txt";
char* output_file = "R.txt";
int   r_file_w_array2 (char * data_file , double ** array1 , double ** array2);
int   write_result (double ** array1 ,double ** array2,double ** array_division_1_2,int *chr);
int   Tolerans_number_for_zerro (double Test_number);
//int   print_arr(double * array);
//void canary (double ** array , double  nsmb  );
/*.........................................*/

#define NOT_OPEN_1      -1
#define NOT_OPEN_2      -2
#define ERROR_TOLERANCE -3
#define GOOD_TOLERANCE   1
#define GOOD_JOB         0
#define NULL_ARRAY_1    -4
#define NULL_ARRAY_2    -5
#define TEST_NUMBER    228
/*.........................................*/
int main ()
{
    int line_U_I = 0;
    int cod = 0 ;
    double * I;
    double * U;
    double * R;
    line_U_I = r_file_w_array2 (data_file , &I , &U);
    cod_mistake(line_U_I);
    cod = write_result (&I , &U , &R , &line_U_I);
    cod_mistake(cod);
    free(I);
    free(U);
    return GOOD_JOB;
}
/*........................................*/
int r_file_w_array2 (char * data_file , double ** array1 , double ** array2)
{
    int chr = 0;
    FILE* file=fopen(data_file, "r");
    if (!file)
    {
        return NOT_OPEN_1;
    }
    fseek(file,0,SEEK_END);
    chr = ftell(file);
    fseek( file , 0 , SEEK_SET );
    *array1 = (double *) calloc(chr/2 + 3,sizeof(double));
    *array2 = (double *) calloc(chr/2 + 3,sizeof(double));
    //canary( array1 , chr/2);
    //canary( array2 , chr/2);
    if (!(*array1))
    {
        return NULL_ARRAY_1;
    }
    if (!(*array2))
    {
        return NULL_ARRAY_2;
    }
    for (int i = 1 ; i < chr /2 ; i++)
    {
        fscanf (file, "%lg %lg", *array1 + i, *array2 + i);
    }
    fclose(file);
    return chr ;
}
/*..................................................*/
int  write_result (double ** array1 ,double ** array2,double ** array_division_1_2,int *chr)
{
    FILE* file=fopen(output_file, "w");
    if (!file)
    {
        printf("Cannot open R.txt\n");
        return NOT_OPEN_2;
    }
    int i = 0;
    *array_division_1_2 = (double *) calloc (*chr/2 + 1,sizeof(double));
    while ( i < (*chr/2) )
    {
        if (Tolerans_number_for_zerro (*(*array2+i))== GOOD_TOLERANCE)
        {
            *(*array_division_1_2 + i) = (*(*array1+i)/(*(*array2+i)));
        }
        else if (Tolerans_number_for_zerro (*(*array2+i))== ERROR_TOLERANCE)
        {
            *(*array_division_1_2 + i) = ERROR_TOLERANCE ;
        }
        i++;
    }
    fclose(file);
    return GOOD_JOB;
}
/*.....................................................*/
int Tolerans_number_for_zerro (double Test_number)
{
    if (Test_number > 0.0 - tolerance && Test_number < 0.0 + tolerance)
    {
        return ERROR_TOLERANCE;//вернёт -3 если делить нельзя
    }
    else
    {
        return GOOD_TOLERANCE; // вернёт 1 если делить можно
    }
}
/*.....................................................*/
/*void print_arr (double * array ,  int chr)
{
    for(int i = 0; i < chr ; i++)
    {
        printf("%lg\n",array[i]);
        i++;
    }
}*/
/*...................................................*/

/*void canary (double ** array , double  nsmb  )
{
    *(*array+0) = TEST_NUMBER;
    *(*array+(nsmb+1)) = TEST_NUMBER;
}*/
void cod_mistake (int cod )
{
    switch (cod)
    {
        case NOT_OPEN_1   : printf ("Not open %s\n",data_file);break;
        case NOT_OPEN_2   : printf ("Not open %s\n",output_file);break;
        case NULL_ARRAY_1 : printf (" no memory allocated for the first array\n");break;
        case NULL_ARRAY_2 : printf ("no memory allocated for the second array\n");break;
        case GOOD_JOB     : printf ("Good Job\n");break;
    }
}

