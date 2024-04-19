Ы#include <conio.h>
#include <dos.h>
 
 
 
void scroll(char x1, char y1, char x2, char y2, char attr)
{
union REGS r;
r.h.al=1;
r.h.ah=6;
r.h.ch = x1;
r.h.cl = y1;
r.h.dh = x2;
r.h.dl = y2;
r.h.bh = attr;
int86(0x10,&r,&r);
}
 
int main()
{
char colors_names[][16] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
 
char black_rus[] = "\227\205\220\215\233\211";
char blue_rus[] = "\221\210\215\210\211";
char green_rus[] = "\207\205\213\205\215\233\211";
char cyan_rus[] = "\221\210\215\205-\207\205\213\205\215\233\211";
char red_rus[] = "\212\220\200\221\215\233\211";
char magenta_rus[] = "\212\220\200\221\215\216-\221\210\215\210\211";
char brown_rus[] = "\212\216\220\210\227\215\205\202\233\211";
char lightgrey_rus[] = "\221\202\205\222\213\216-\221\205\220\233\211";
char darkgrey_rus[] = "\222\205\214\215\216-\221\205\220\233\211";
char lightblue_rus[] = "\237\220\212\216-\221\210\215\210\211";
char lightgreen_rus[] = "\237\220\212\216-\207\205\213\205\215\233\211";
char lightcyan_rus[] = "\237\220\212\210\211 \221\210\215\205-\207\205\213\205\215\233\211";
char lightred_rus[] = "\237\220\212\216-\212\220\200\221\215\233\211";
char lightmagenta_rus[] = "\237\220\212\210\211 \212\220\200\221\215\216-\221\210\215\210\211";
char yellow_rus[] = "\206\205\213\222\233\211";
char white_rus[] = "\201\205\213\233\211";
 
int atr_cnt=0;
window(15,5,65,15);
for(int i=0;i<8;i++)
{
	for(int j=0;j<16;j++)
	{
		textcolor(j);
		textbackground(i);
		clrscr();
		gotoxy(1,11);
		cprintf("Background:%s\n ", colors_names[i]);
		cprintf("Text:");
		switch(j)
        {
            case 0: cprintf("%s",black_rus); break;
            case 1: cprintf("%s",blue_rus); break;
            case 2: cprintf("%s",green_rus); break;
            case 3: cprintf("%s",cyan_rus); break;
            case 4: cprintf("%s",red_rus); break;
            case 5: cprintf("%s",magenta_rus); break;
            case 6: cprintf("%s",brown_rus); break;
            case 7: cprintf("%s",lightgrey_rus); break;
            case 8: cprintf("%s",darkgrey_rus); break;
            case 9: cprintf("%s",lightblue_rus); break;
            case 10: cprintf("%s",lightgreen_rus); break;
            case 11: cprintf("%s",lightcyan_rus); break;
            case 12: cprintf("%s",lightred_rus); break;
            case 13: cprintf("%s",lightmagenta_rus); break;
            case 14: cprintf("%s",yellow_rus); break;
            case 15: cprintf("%s",white_rus); break;
 
        }
	delay(100);
	for (int k = 0; k<2;k++) scroll(4,14,14,64,atr_cnt);
        atr_cnt++;
	}
}
return 0;
}
