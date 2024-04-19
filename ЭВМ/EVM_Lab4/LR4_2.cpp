#include <conio.h>
#include <dos.h>

int getkey();

int main() {
	int ch, x = 1, y = 1;
	textbackground(8);
	clrscr();
	window(15, 5, 65, 15);
	textbackground(2);
	textcolor(0);
	_setcursortype (_NOCURSOR);
	do {
		 clrscr();
		 gotoxy(x, y);
		 cprintf("*");
		 ch = getkey();
		 switch (ch)
		 {
		 case 77: //->
			 if (x < 50)
				 x++;
			 else if (x == 50 && y <= 10)
			 {
				 y++;
				 x = 1;
			 }
			 break;
		 case 75: //<-
			 if (x > 1)
				 x--;
			 else if (x == 1 && y > 1)
			 {
				 y--;
				 x = 50;
			 }
			 break;
		 default: break;
		 }
	} while (ch != 27);
	return 0;
}

int getkey()
{
	union REGS regs;
	int c = 0, e = 0, res;
	regs.h.ah = 0x7;
	int86(0x21, &regs, &regs);
	c = regs.h.al;
	if (!c) {
		int86(0x21, &regs, &regs);
		e = regs.h.al;
	}
	if (c)
		res = c;
	else
		res = e;
	return res;
}
