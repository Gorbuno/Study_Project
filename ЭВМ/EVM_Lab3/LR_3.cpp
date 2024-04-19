#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define pi 3.14159265
#define dx 100
#define dy 100
#define x0 10
#define y0 10
#define Mixxi 1.5
#define Maxxi 16
int main() {
    int graph_driver, graph_mode, midx,midy;
    char str [3];
    char str2[16];
    int graph_error_code, k,j,i;
    double x1,y1,max=0,tabx=dx/pi,x,y;
    clrscr();
    graph_driver = DETECT;
    initgraph (&graph_driver, &graph_mode, "C:\\TURBOC3\\BGI");
    graph_error_code = graphresult();
    if (graph_error_code != grOk){
        printf("ERROR");
        getch();
        return 1;
    }
    midx=getmaxx();
    midy = getmaxy()/2-y0*x0;
    setviewport(0,0,midx,midy,1);
    line (x0,midy,x0,0);
    line (x0,midy,midx,midy);
    k=0;
    for (i=dx;k<=Maxxi;i+=dx){
        k++;
        sprintf (str,"%dpi",k);
        outtextxy(i-15,midy-20,str);
        line (i,midy+5,i,midy-5);
    }
    k=1;
    for (j=y0+28;k>=-1;j+=dy){
        sprintf (str,"%d",k);
        outtextxy(0,j-7,str);
        line (x0,j,x0+5,j);
        k--;
    }
    setviewport(0,0,midx,midy,0);
    x1=Mixxi*pi;
    do {
        y1 = sin(x1/2)*sin(x1/2)*sin(x1/2)-sqrt(x1);
        x= x1*tabx;
        y=y1*dy;
        putpixel (x, midy-y,5);
        if (y1>max) max= y1;
        x1+=0.0001;
    }
    while (x<=Maxxi*dx);
    sprintf (std2, "Max is %f\n", max);
    outtextxy(0, midy+midx, str2);
    getchar();
    closegraph();
    return 0;
}