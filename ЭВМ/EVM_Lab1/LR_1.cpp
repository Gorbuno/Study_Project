#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
 
union {
    struct {
        int  int1;
        int  int2;
    };
     double a;
}double_int;
 
int main()
{
    int i;
    int j;
    int x;
    int lent;
    unsigned char locator;
    unsigned char num;
    unsigned char *mass;
    char art;
    unsigned char mask;
    unsigned char res;
    fflush (stdin);
    scanf("%c", &art);
    fflush (stdin);
    mask = 128;
/*печать чара в битовом виде*/
    for (i = 0; i < 8; i++){
        res = art & mask;
        if (res == 0){
            printf("0");
        } else{
            printf("1");
        }
        mask = mask >> 1;
    }
    printf("\n");
/*количество и номера битов, которые надо инвертировать*/
/*по хорошему тут надо добавить ещё проверки на не выход за границы размера чара, то есть записывать мы можем только числа от 0 до 7, и сам x не должен быть больше 8, иначе откуда у нас более большое число бит*/
    scanf("%d", &x);
    mass = malloc(x);
    for (i = 0; i < x; i++){
        scanf("%d", &mass[i]);
    }
/*инверсия для чара*/
    for (i = 0; i < x; i++){
        num = pow(2, mass[i]);
        art = art^num; /*делаем xor с маской num, у которой 1 это номер бита, который мы хотим поменять*/
    }
    mask = 128;
/*снова печать чара в битовом виде*/
    for (i = 0; i < 8; i++){
        res = art & mask;
        if (res == 0){
            printf("0");
        } else{
            printf("1");
        }
        mask = mask >> 1;
    }
    printf("\n");
    printf("%c", art);
    free(mass);
/*теперь дабл*/
    scanf("%lf", &double_int.a);
/*печать дабла в битовом виде*/
    lent = 32;
    for (int i = 0; i < lent; ++i) {
        if ((double_int.int2 & 1 << lent - i - 1) == 0) printf("0");
        else printf("1");
    }
    for (int i = 0; i < lent; ++i) {
        if ((double_int.int1 & 1 << lent - i - 1) == 0) printf("0");
        else printf("1");
    }
    printf("\n");
/*количество и номера битов, которые надо инвертировать*/
/*по хорошему тут надо добавить ещё проверки на не выход за границы размера дабла, то есть записывать мы можем только числа от 0 до 63, и сам x не должен быть больше 64, иначе откуда у нас более большое число бит*/
    scanf("%d", &x);
    mass = malloc(x);
    for (i = 0; i < x; i++){
        scanf("%d", &mass[i]);
    }
/*инверсия для дабла*/
    for (i = 0; i < x; i++){
        if (mass[i] < 32){
            double_int.int1 = double_int.int1 ^ (1 << mass[i]);
        } else {
            double_int.int2 = double_int.int2 ^ (1 << (mass[i]%32));
        }
    }
/*снова печать дабла в битовом виде*/
    lent = 32;
    for (int i = 0; i < lent; ++i) {
        if ((double_int.int2 & 1 << lent - i - 1) == 0) printf("0");
        else printf("1");
    }
    for (int i = 0; i < lent; ++i) {
        if ((double_int.int1 & 1 << lent - i - 1) == 0) printf("0");
        else printf("1");
    }
    printf("\n");
    free(mass);
    printf("%lf", double_int.a);
    return 0;
}