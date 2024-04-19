#include <conio.h>
#include <dos.h>
void main()
{
	textbackground(10);
	clrscr();
	window(15, 5, 65, 15);
	textbackground(2);
	clrscr();
	textcolor(0);
	char c;
	int x = 1, y = 1;
	gotoxy(x, y);
	cprintf("*");
	_setcursortype (_NOCURSOR);
	do{
		c = getch();
		if ( ((c == 75) || (c == 77)) ){
			switch (c){
			case 75: if(x > 1) {x--;} break;
			case 77: if(x <= 50) {x++;} break;}
			clrscr();
			gotoxy(x, y);
			cprintf("*");}
	} while (c != 27);
}
