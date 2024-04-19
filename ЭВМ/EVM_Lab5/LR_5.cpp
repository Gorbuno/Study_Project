#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#ifdef __cplusplus
#define __CPPARGS ...
#else
#define __CPPARGS
#endif
void interrupt (*old9)(__CPPARGS);
void interrupt new9(__CPPARGS);

void main()
{
char string[10000];
clrscr();
old9=getvect(9);
setvect(9,new9);
printf("\n----> ");
scanf("%s",string);
setvect(9,old9);
}

void interrupt new9(__CPPARGS)
{
    unsigned char a = inportb(0x60);
    unsigned char oldvectport;
    unsigned char c;
    switch (a){
        case(1):
            (*old9)(__CPPARGS); 
            break;
        case 30:  printf("z");break;
        case 48:  printf("y");break;
        case 46:  printf("x");break;
        case 32:  printf("w");break;
        case 18:  printf("v");break;
        case 33:  printf("u");break;
        case 34:  printf("t");break;
        case 35:  printf("s");break;
        case 23:  printf("r");break;
        case 36:  printf("q");break;
        case 37:  printf("p");break;
        case 38:  printf("o");break;
        case 50:  printf("n");break;
        case 49:  printf("m");break;
        case 24:  printf("l");break;
        case 25:  printf("k");break;
        case 16:  printf("j");break;
        case 19:  printf("i");break;
        case 31:  printf("h");break;
        case 20:  printf("g");break;
        case 22:  printf("f");break;
        case 47:  printf("e");break;
        case 17:  printf("d");break;
        case 45:  printf("c");break;
        case 21:  printf("b");break;
        case 44:  printf("a");break;
        default:  (*old9)(__CPPARGS); break;
    }
c=inportb(0x61);
outportb(0x61,c|0x80);
outportb(0x61,c);
outportb(0x20,0x20);
}
